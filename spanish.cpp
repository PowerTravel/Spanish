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

  u32 StartChar = 0x20;
  u32 EndChar = 0x100;
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
    GlobalState->Language = 1;
    GlobalState->InputBuffer = Utf8StringBuffer(BufferSize, Buffer);
    GlobalState->Initialized = true;
    midx SizeToAlloc = EndChar - StartChar;
    GlobalState->Font = jfont::LoadSDFFont(PushArray(PersistentArena, EndChar - StartChar, jfont::sdf_fontchar),
    StartChar, EndChar, FontPath, GlobalState->TextPixelSize, Padding, GlobalState->OnedgeValue, GlobalState->PixelDistanceScale);
    GlobalState->Library = LoadLibrary(PersistentArena);
  }
  jwin::keyboard_input* Keyboard = &Input->Keyboard;
  
  #if 0
  b32 ReloadFont = false;
  if(Pushed(Keyboard->Key_UP) && (!Active(Keyboard->Key_LCTRL) && !Active(Keyboard->Key_RCTRL)))
  {
    GlobalState->FontRelativeScale *= 1.1f;
    Platform.DEBUGPrint("FontRelativeScale %f\n", GlobalState->FontRelativeScale);
  }else if(Pushed(Keyboard->Key_DOWN) && (!Active(Keyboard->Key_LCTRL) && !Active(Keyboard->Key_RCTRL))){
    GlobalState->FontRelativeScale *= 0.9f;
    Platform.DEBUGPrint("FontRelativeScale %f\n", GlobalState->FontRelativeScale);
  }else if(Pushed(Keyboard->Key_UP) && (Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL))){
    GlobalState->TextPixelSize = GlobalState->TextPixelSize*2.f;
    Platform.DEBUGPrint("PixelSize %f\n", GlobalState->TextPixelSize);
    ReloadFont = true;
  }else if(Pushed(Keyboard->Key_DOWN) && (Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL)))
  {
    GlobalState->TextPixelSize = GlobalState->TextPixelSize <= 1 ? 1 : GlobalState->TextPixelSize/2.f;
    Platform.DEBUGPrint("PixelSize %f\n", GlobalState->TextPixelSize);
    ReloadFont = true;
  }else if(Pushed(Keyboard->Key_LEFT) && (!Active(Keyboard->Key_LCTRL) && !Active(Keyboard->Key_RCTRL)))
  {
    GlobalState->OnedgeValue = GlobalState->OnedgeValue <= 1 ? 1 : GlobalState->OnedgeValue/2;
    Platform.DEBUGPrint("OnedgeValue %d\n", GlobalState->OnedgeValue);
    ReloadFont = true;
  }else if(Pushed(Keyboard->Key_RIGHT) && (!Active(Keyboard->Key_LCTRL) && !Active(Keyboard->Key_RCTRL))){
    GlobalState->OnedgeValue = GlobalState->OnedgeValue*2;
    Platform.DEBUGPrint("OnedgeValue %d\n", GlobalState->OnedgeValue);
    ReloadFont = true;
  }else if(Pushed(Keyboard->Key_LEFT) && (Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL)))
  {
    GlobalState->PixelDistanceScale = GlobalState->PixelDistanceScale <= 1 ? 1 : GlobalState->PixelDistanceScale/2.f;
    Platform.DEBUGPrint("PixelDistanceScale %f\n", GlobalState->PixelDistanceScale);
    ReloadFont = true;
  }else if(Pushed(Keyboard->Key_RIGHT) && (Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL)))
  {
    GlobalState->PixelDistanceScale = GlobalState->PixelDistanceScale*2.f;
    Platform.DEBUGPrint("PixelDistanceScale %f\n", GlobalState->PixelDistanceScale);
    ReloadFont = true;
  }else if (Pushed(Keyboard->Key_P))
  {
    Platform.DEBUGPrint("FontRelativeScale %f\n", GlobalState->FontRelativeScale);
    Platform.DEBUGPrint("PixelSize %f\n", GlobalState->TextPixelSize);
    Platform.DEBUGPrint("PixelDistanceScale %f\n", GlobalState->PixelDistanceScale);
    Platform.DEBUGPrint("OnedgeValue %d\n", GlobalState->OnedgeValue);
  }

  if(ReloadFont)
  {
    GlobalState->Font = jfont::LoadSDFFont(PushArray(PersistentArena, EndChar - StartChar, jfont::sdf_fontchar),
    StartChar, EndChar, FontPath, GlobalState->TextPixelSize, Padding, GlobalState->OnedgeValue, GlobalState->PixelDistanceScale);
  }
  #endif

  char EggWhiteR = 0xF0;
  char EggWhiteG = 0xF8;
  char EggWhiteB = 0xFF;
  char SublR = 0x30;
  char SublG = 0x38;
  char SublB = 0x41;
  DrawRectangle(OffscreenBuffer, 0, 0, (r32)OffscreenBuffer->Width, (r32)OffscreenBuffer->Height, SublR/255.f, SublG/255.f, SublB/255.f );

  utf8_string_buffer* InputBuffer = &GlobalState->InputBuffer;

  int PushedKeyCount = 0;
  for (int i = 0; i < jwin::KeyboardButton_COUNT; ++i)
  {
    if(jwin::Pushed(Keyboard->Keys[i]))
    {
      ++PushedKeyCount;
    }
  }

  if(jwin::Pushed(Keyboard->Key_BACK) && InputBuffer->Position > 0)
  {
    EraseFromBuffer(InputBuffer, 1);
  }

  jfont::bitmap StbBitmap = {};
  StbBitmap.Pixels  = (u32*) OffscreenBuffer->Memory;
  StbBitmap.Width   = OffscreenBuffer->Width;
  StbBitmap.Height  = OffscreenBuffer->Height;

  library* Library = &GlobalState->Library;

  if(Pushed(Keyboard->Key_TAB) && (Active(Keyboard->Key_RSHIFT) || Active(Keyboard->Key_LSHIFT)))
  {
    GlobalState->Language++;
    GlobalState->Language = GlobalState->Language % Library->LanguageCount;
    Platform.DEBUGPrint("%d\n", GlobalState->Language);
  }
  int QuestionLanguage = GlobalState->Language;
  int InputLanguage    = (QuestionLanguage+1) % Library->LanguageCount;
  
  local_persist int ProgramState = 0;
  local_persist int NounSelect = 0;

  int inputStartWidth = 3*StbBitmap.Width/4.f;
  if(jwin::Pushed(Keyboard->Key_ENTER)) {
    ProgramState = (ProgramState+1) % 2;
    Platform.DEBUGPrint("%d\n", ProgramState);
  }
  int NounQuestion = NounSelect*Library->LanguageCount + QuestionLanguage;
  int NounAnswer = NounSelect*Library->LanguageCount + InputLanguage;

  utf8_string_buffer NounBuffer = CreateTempStringBuffer(2048);
  AppendStringToBuffer(Library->Nouns[NounQuestion], &NounBuffer);
  utf8_string_buffer AnswerBuffer = CreateTempStringBuffer(2048);

  switch(ProgramState) {
    case 0: {
      if(jwin::Pushed(Keyboard->Key_ENTER)) {
        ClearBuffer(InputBuffer);
        NounSelect++;
      }
      r32 TextHeight,TextWidth;
      u32 TmpBuff[2048] = {};
      u32 TmpLen = ConvertToUnicode(NounBuffer.Buffer, TmpBuff, GlobalState->Language);
      jfont::GetTextDim(&GlobalState->Font, GlobalState->FontRelativeScale, &TextWidth, &TextHeight, TmpBuff);
      if( inputStartWidth + TextWidth + 100 < OffscreenBuffer->Width)
      {
        PushInputToBuffer(Keyboard, InputBuffer, InputLanguage);
      }
    }break;
  }

  AppendStringToBuffer((const utf8_byte*)" => ", &NounBuffer);

  utf8_string_buffer PrintBuffer = CreateTempStringBuffer(2048);
  CopyBufferContent(InputBuffer, &PrintBuffer);
  if(ProgramState == 0)
  {
    if(!(((s32) Input->Time) % 2) || 
      Keyboard->LastPushedKey != jwin::KeyboardButton_COUNT != 0 || 
      Keyboard->LastPushedKeyHoldTime < 1.f)
    {
      AppendStringToBuffer((const utf8_byte*) "_", &PrintBuffer);
    }
  }
  AppendStringToBuffer(PrintBuffer.Buffer, &NounBuffer);

  if(ProgramState == 1)
  {
    u32 Q[128] = {};
    ConvertToUnicode(Library->Nouns[NounAnswer], Q, GlobalState->Language);
    u32 A[128] = {};
    ConvertToUnicode(InputBuffer->Buffer, A, GlobalState->Language);
    int Index = 0;
    while(Q[Index] && A[Index] && Q[Index] == A[Index])
    {
      Index++;
    }

    bool CorrectAnswer = (Q[Index] == '\0') && (A[Index] == '\0');
    if(CorrectAnswer)
    {
      AppendStringToBuffer((const utf8_byte*)" OK!", &NounBuffer);
    }else{
      AppendStringToBuffer((const utf8_byte*)" != ", &NounBuffer);
      AppendStringToBuffer(Library->Nouns[NounAnswer], &NounBuffer);
    }
  }

  u32 NounBuff[2048] = {};
  u32 NounLen = ConvertToUnicode(NounBuffer.Buffer, NounBuff, GlobalState->Language);
  jfont::PrintText(&GlobalState->Font, &StbBitmap, GlobalState->FontRelativeScale, (StbBitmap.Width)/4.f, (StbBitmap.Height)/2.f, NounLen, NounBuff);
  u32 AnsBuff[2048] = {};
  u32 AnsLen = ConvertToUnicode(AnswerBuffer.Buffer, AnsBuff, GlobalState->Language);
  jfont::PrintText(&GlobalState->Font, &StbBitmap, GlobalState->FontRelativeScale, (StbBitmap.Width)/2.f, StbBitmap.Height/5.f, AnsLen, AnsBuff);
}