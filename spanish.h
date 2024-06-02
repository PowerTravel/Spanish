#pragma once
#include "platform/jwin_platform.h"
#include "platform/jfont.h"
#include "text_input.h"

struct application_state
{
  b32 Initialized;

  jfont::sdf_font Font;
  s32 Language;
  utf8_string_buffer InputBuffer;

  r32 TextPixelSize;
  s32 OnedgeValue;
  r32 PixelDistanceScale;
  r32 FontRelativeScale;

  library Library;
};

application_state* GlobalState = 0;