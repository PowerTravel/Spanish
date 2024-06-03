#pragma once
#include "platform/jwin_types.h"
#include "platform/jwin_string.h"


enum LanguageType
{
  SPANISH,
  SWEDISH,
  ENGLISH,
  LANGUAGE_COUNT
};

struct utf8_string_buffer {
  s32 Position;
  midx BufferSize;
  utf8_byte* Buffer;
};

#define CreateTempStringBuffer(Size)  Utf8StringBuffer(Size, PushArray(TransientArena, Size, utf8_byte))

void LanguageToUtf8String(u32 Language, utf8_byte* Output);
midx PushInputToBuffer(jwin::keyboard_input* Keyboard, utf8_string_buffer* StringBuffer, s32 Language);
void CopyBufferContent(utf8_string_buffer* SrcBuf, utf8_string_buffer* DstBuff);
void ConcatinateBuffers(utf8_string_buffer* BuffA, utf8_string_buffer* BuffB, utf8_string_buffer* DstBuffer);
void AppendStringToBuffer(const utf8_byte* String, utf8_string_buffer* StringBuffer);
void EraseFromBuffer(utf8_string_buffer* StringBuffer, s32 Utf8CharsToErase);
void ClearBuffer(utf8_string_buffer* StringBuffer);
u32 ConvertToUnicode(utf8_byte *utf8Input, u32* unicodeOutput);

utf8_string_buffer Utf8StringBuffer(midx ByteCount, utf8_byte* Memory)
{
  utf8_string_buffer Result = {};
  Result.BufferSize = ByteCount;
  Result.Buffer = Memory;
  Result.Position = 0;
  return Result;
}

typedef utf8_byte* string;

struct library
{
  u32 LanguageCount;
  u32 NounCount;
  utf8_byte** Languages;
  utf8_byte** Nouns;
};

library LoadLibrary(memory_arena* Arena)
{
  debug_read_file_result TextFile = Platform.DEBUGPlatformReadEntireFile("..\\Nouns.csv");
  midx TextSize = TextFile.ContentSize+1;
  utf8_byte* Text = (utf8_byte*) PushSize(Arena, TextSize);
  utils::Copy(TextSize-1, TextFile.Contents, Text);
  Platform.DEBUGPlatformFreeFileMemory(TextFile.Contents);

  utf8_byte* Cursor = Text;
  u32 LineCount = 1;
  do{
    if(*Cursor == '\n')
    {
      LineCount++;
    }
  }while(*++Cursor);

  Cursor = Text;
  u32 LanguageCount = 1;
  do{
    if(*Cursor == ',')
    {
      LanguageCount++;
    }
  Cursor++;
  }while(*Cursor != '\n');

  utf8_byte** Nouns = PushArray(Arena, LanguageCount * LineCount, utf8_byte*);
  u32 LineIndex = 0;
  Cursor = Text;
  u32 WordIndex = 0;
  u32 WordCountInLine = 0;
  // The file is a comma separated list.
  // Newline is \n or \r\n
  // Every line _needs_ to have the same amount of commas.

  // TODO: Handle , and ""
  //  Any '"' in the word is repressented with ""
  //  If a , or '"' appears in the word, the whole word needs to be wrapped between " the, "" word "
  //  Ex "The , Word" -> """The , Word"""
  do
  {
    utf8_byte* WordStart = Cursor;

    while(*Cursor && *Cursor != '\r' && *Cursor != '\n')
    {
      if(*Cursor == ',')
      {
        if((Cursor - WordStart) > 0)
        {
          Nouns[WordIndex] = WordStart;
          *Cursor = '\0';
        }
        WordIndex++;
        WordStart = Cursor+1;  
      }
      Cursor++;
    }

    // End of line (last word)
    if((Cursor - WordStart) > 0)
    {
      Nouns[WordIndex] = WordStart;
    }
    WordIndex++;
    if(*Cursor)
    {
      *Cursor++ = '\0';
      if(*Cursor == (*Cursor != '\r' || *Cursor != '\n'))
      {
        *Cursor++ = '\0';
      }
    }
  }while(*Cursor++);

  library Result = {};
  Result.LanguageCount = LanguageCount;
  Result.NounCount = (LineCount-1) * LanguageCount;
  Result.Languages = Nouns;
  Result.Nouns = Nouns+LanguageCount;
  return Result;
}
