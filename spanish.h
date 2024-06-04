#pragma once
#include "platform/jwin_platform.h"
#include "platform/jfont.h"
#include "text_input.h"
#include "platform/random.h"

struct question_card_list {
  u32 Question;
  question_card_list* Next;
  question_card_list* Previous;
};

struct application_state
{
  b32 Initialized;

  s32 QuestionLanguage;
  s32 AnswerLanguage;
  u32 QuestionCardCount;
  question_card_list Sentinel;
  question_card_list* QueueCards;

  utf8_string_buffer InputBuffer;
  library Library;

  jfont::sdf_font Font;
  r32 TextPixelSize;
  s32 OnedgeValue;
  r32 PixelDistanceScale;
  r32 FontRelativeScale;

  random_generator Generator;
};

application_state* GlobalState = 0;