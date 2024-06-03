#include "spanish.h"

#include "platform/jwin_platform_memory.cpp"
#include "platform/jwin_platform_input.h"
#include "platform/jfont.cpp"
#include "text_input.cpp"

inline s32 
TruncateReal32ToInt32( r32 Real32 )
{
  s32 Result = (s32) Real32;
  return Result;
}

internal void
DrawRectangle( platform_offscreen_buffer* Buffer, r32 RealMinX, r32 RealMinY, r32 Width, r32 Height, r32 R, r32 G, r32 B )
{
  s32 MinX = (s32) Round( RealMinX );
  s32 MinY = (s32) Round( RealMinY );
  s32 MaxX = (s32) Round( RealMinX + Width);
  s32 MaxY = (s32) Round( RealMinY + Height);

  if( MinX < 0 )
  {
    MinX = 0;
  }
  if( MinY < 0 )
  {
    MinY = 0;
  }
  if( MaxX > Buffer->Width )
  {
    MaxX = Buffer->Width;
  }
  if( MaxY > Buffer->Height )
  {
    MaxY = Buffer->Height;
  }

  u8* Row = ( (u8*) Buffer->Memory + MinX*Buffer->BytesPerPixel + MinY*Buffer->Pitch );
  for( s32 Y = MinY; Y < MaxY; ++Y )
  {
    u32* Pixel = (u32*) Row;
    for( s32 X = MinX; X < MaxX; ++X )
    {
      *Pixel++ = ( (TruncateReal32ToInt32( R*255.f ) << 16 ) |
                 (  TruncateReal32ToInt32( G*255.f ) << 8  ) |
                 (  TruncateReal32ToInt32( B*255.f ) << 0  ) );
    }
    Row += Buffer->Pitch;
  }
}

u32 CharCount(utf8_byte* Chars)
{
  u32 Result = 0;
  while(*Chars++)
  {
    Result++;
  }
  return Result;
}

u32 GetRand(u32 Seed, u32 Multiplyer, u32 Increment, u32 Modulus)
{
  return ((Seed%Modulus)*Multiplyer + Increment) % Modulus;
}

// void ApplicationUpdateAndRender(application_memory* Memory, platform_offscreen_buffer* OffscreenBuffer, jwin::device_input* Input)
extern "C" JWIN_UPDATE_AND_RENDER(ApplicationUpdateAndRender)
{
  GlobalState = JwinBeginFrameMemory(application_state);

  u32 CharCount = 0x100;
  int Padding = 3;
  char FontPath[] = "C:\\Windows\\Fonts\\consola.ttf";

  if(!GlobalState->Initialized)
  {
    GlobalState->TextPixelSize = 32;
    GlobalState->OnedgeValue = 128;
    GlobalState->PixelDistanceScale = 32.0;
    GlobalState->FontRelativeScale = 1.f;
    midx BufferSize = 2048;
    utf8_byte* Buffer = PushArray(PersistentArena, BufferSize, utf8_byte);
    GlobalState->QuestionLanguage = 0;
    GlobalState->AnswerLanguage = 1;
    GlobalState->InputBuffer = Utf8StringBuffer(BufferSize, Buffer);
    GlobalState->Initialized = true;
    GlobalState->Font = jfont::LoadSDFFont(PushArray(PersistentArena, CharCount, jfont::sdf_fontchar),
      CharCount, FontPath,  GlobalState->TextPixelSize, Padding, GlobalState->OnedgeValue, GlobalState->PixelDistanceScale);
    GlobalState->Library = LoadLibrary(PersistentArena);
  }
  jwin::keyboard_input* Keyboard = &Input->Keyboard;
  
  char EggWhiteR = 0xF0;
  char EggWhiteG = 0xF8;
  char EggWhiteB = 0xFF;
  char SublR = 0x30;
  char SublG = 0x38;
  char SublB = 0x41;
  DrawRectangle(OffscreenBuffer, 0, 0, (r32)OffscreenBuffer->Width, (r32)OffscreenBuffer->Height, SublR/255.f, SublG/255.f, SublB/255.f );

  jfont::bitmap StbBitmap = {};
  StbBitmap.Pixels  = (u32*) OffscreenBuffer->Memory;
  StbBitmap.Width   = OffscreenBuffer->Width;
  StbBitmap.Height  = OffscreenBuffer->Height;


  utf8_string_buffer* InputBuffer = &GlobalState->InputBuffer;
  s32& QuestionLanguage = GlobalState->QuestionLanguage;
  s32& AnswerLanguage = GlobalState->AnswerLanguage;

  if(jwin::Pushed(Keyboard->Key_BACK) && InputBuffer->Position > 0)
  {
    EraseFromBuffer(InputBuffer, 1);
  }

  library* Library = &GlobalState->Library;

  
  local_persist int ProgramState = 0;
  local_persist int NounSelect = 0;

  
  if(jwin::Pushed(Keyboard->Key_ENTER)) {
    ProgramState = (ProgramState+1) % 2;
  }

  if(Pushed(Keyboard->Key_TAB) && Active(Keyboard->Key_LSHIFT) && !Active(Keyboard->Key_RSHIFT))
  {
    QuestionLanguage = (QuestionLanguage+1)%Library->LanguageCount;
    if(AnswerLanguage == QuestionLanguage)
    {
      QuestionLanguage = (QuestionLanguage+1)%Library->LanguageCount;
    }
  }else if(Pushed(Keyboard->Key_TAB) && !Active(Keyboard->Key_LSHIFT) && Active(Keyboard->Key_RSHIFT)){
    u32 Tmp = AnswerLanguage;
    AnswerLanguage = QuestionLanguage;
    QuestionLanguage = Tmp;
  }

  int NounQuestion = NounSelect*Library->LanguageCount + QuestionLanguage;
  int NounAnswer = NounSelect*Library->LanguageCount + AnswerLanguage;

  int PrintStartPosX = StbBitmap.Width/4.f;
  int PrintStartPosY = StbBitmap.Height/2.f;

  utf8_string_buffer PrintBuffer = CreateTempStringBuffer(1024);
  AppendStringToBuffer(Library->Nouns[NounQuestion], &PrintBuffer);
  AppendStringToBuffer((const utf8_byte*)" => ", &PrintBuffer);
  CopyBufferContent(InputBuffer, &PrintBuffer);

  if(ProgramState == 0)
  {
    if(jwin::Pushed(Keyboard->Key_ENTER)) {
      ClearBuffer(InputBuffer);
      NounSelect++;
    }

    int MaxInputCharLength = 32;
    if( InputBuffer->Position < MaxInputCharLength)
    {
      PushInputToBuffer(Keyboard, InputBuffer, AnswerLanguage);
    }

    if(!(((s32) Input->Time) % 2) || 
      Keyboard->LastPushedKey != jwin::KeyboardButton_COUNT != 0 || 
      Keyboard->LastPushedKeyHoldTime < 1.f)
    {
      AppendStringToBuffer((const utf8_byte*) "_", &PrintBuffer);
    }
  }else if(ProgramState == 1)
  {

    u32 Facit[128] = {};
    ConvertToUnicode(Library->Nouns[NounAnswer], Facit);
    u32 Answer[128] = {};
    ConvertToUnicode(InputBuffer->Buffer, Answer);
    int Index = 0;
    while(Facit[Index] && Answer[Index] && Facit[Index] == Answer[Index])
    {
      Index++;
    }

    bool CorrectAnswer = (Facit[Index] == '\0') && (Answer[Index] == '\0');
    if(CorrectAnswer)
    {
      AppendStringToBuffer((const utf8_byte*)" OK!", &PrintBuffer);
    }else{
      AppendStringToBuffer((const utf8_byte*)" != ", &PrintBuffer);
      AppendStringToBuffer(Library->Nouns[NounAnswer], &PrintBuffer);
    }
  }

  utf8_string_buffer Language = CreateTempStringBuffer(1024);
  AppendStringToBuffer(Library->Languages[QuestionLanguage], &Language);
  AppendStringToBuffer((const utf8_byte*)" => ", &Language);
  AppendStringToBuffer(Library->Languages[AnswerLanguage], &Language);
  u32 LanguageBuffer[1024] = {};
  u32 LanguageLen = ConvertToUnicode(Language.Buffer, LanguageBuffer);
  r32 TextWidth, TextHeight;
  jfont::GetTextDim(&GlobalState->Font, GlobalState->FontRelativeScale, &TextWidth, &TextHeight, LanguageBuffer);
  jfont::PrintText(&GlobalState->Font, &StbBitmap, GlobalState->FontRelativeScale, 10, StbBitmap.Height-10-TextHeight, LanguageLen, LanguageBuffer);

  u32 NounBuff[1024] = {};
  u32 NounLen = ConvertToUnicode(PrintBuffer.Buffer, NounBuff);
  jfont::PrintText(&GlobalState->Font, &StbBitmap, GlobalState->FontRelativeScale, (StbBitmap.Width)/4.f, (StbBitmap.Height)/2.f, NounLen, NounBuff);
}