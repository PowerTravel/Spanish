#include "platform/jwin_platform_input.h"
#include "platform/jwin_string.h"
#include "platform/utf8.h"

void LanguageToUtf8String(u32 Language, utf8_byte* Output)
{
  Language = Language % LANGUAGE_COUNT;
  switch(Language)
  {
    case ENGLISH: Utf8("English", Output); break;
    case SPANISH: Utf8("Español", Output); break;
    case SWEDISH: Utf8("Svenska", Output); break;
  }
}

internal size_t
KeyboardButtonEnglish(jwin::keyboard_input* Keyboard, s32 ButtonCode, utf8_byte* OutputBuffer)
{
  b32 Shift = Active(Keyboard->Key_LSHIFT) || Active(Keyboard->Key_RSHIFT);
  b32 Alt = Active(Keyboard->Key_LALT) || Active(Keyboard->Key_RALT);
  b32 Ctrl = Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL);
  b32 ShiftMod = (!Toggled(Keyboard->Key_CPSLCK) && Shift) || (Toggled(Keyboard->Key_CPSLCK) && !Shift);
  b32 NumLock = Toggled(Keyboard->Key_NP_NMLK);
  switch(ButtonCode)
  {
    case jwin::KeyboardButton_SPACE:    {return !(Alt || Ctrl) ? Utf8(" ", OutputBuffer) : 0;} break;
    case jwin::KeyboardButton_TAB:      {return !(Alt || Ctrl || Shift) ? Utf8("\t", OutputBuffer) : 0;} break;
    case jwin::KeyboardButton_1:        {return Shift ? Utf8("!", OutputBuffer) : Utf8("1", OutputBuffer);} break;
    case jwin::KeyboardButton_2:        {return Shift ? Utf8("@", OutputBuffer) : Utf8("2", OutputBuffer);} break;
    case jwin::KeyboardButton_3:        {return Shift ? Utf8("#", OutputBuffer) : Utf8("3", OutputBuffer);} break;
    case jwin::KeyboardButton_4:        {return Shift ? Utf8("$", OutputBuffer) : Utf8("4", OutputBuffer);} break;
    case jwin::KeyboardButton_5:        {return Shift ? Utf8("%", OutputBuffer) : Utf8("5", OutputBuffer);} break;
    case jwin::KeyboardButton_6:        {return Shift ? Utf8("^", OutputBuffer) : Utf8("6", OutputBuffer);} break;
    case jwin::KeyboardButton_7:        {return Shift ? Utf8("&", OutputBuffer) : Utf8("7", OutputBuffer);} break;
    case jwin::KeyboardButton_8:        {return Shift ? Utf8("*", OutputBuffer) : Utf8("8", OutputBuffer);} break;
    case jwin::KeyboardButton_9:        {return Shift ? Utf8("(", OutputBuffer) : Utf8("9", OutputBuffer);} break;
    case jwin::KeyboardButton_0:        {return Shift ? Utf8(",", OutputBuffer) : Utf8("0", OutputBuffer);} break;
    case jwin::KeyboardButton_A:        {return ShiftMod ? Utf8("A", OutputBuffer) : Utf8("a", OutputBuffer);} break;
    case jwin::KeyboardButton_B:        {return ShiftMod ? Utf8("B", OutputBuffer) : Utf8("b", OutputBuffer);} break;
    case jwin::KeyboardButton_C:        {return ShiftMod ? Utf8("C", OutputBuffer) : Utf8("c", OutputBuffer);} break;
    case jwin::KeyboardButton_D:        {return ShiftMod ? Utf8("D", OutputBuffer) : Utf8("d", OutputBuffer);} break;
    case jwin::KeyboardButton_E:        {return ShiftMod ? Utf8("E", OutputBuffer) : Utf8("e", OutputBuffer);} break;
    case jwin::KeyboardButton_F:        {return ShiftMod ? Utf8("F", OutputBuffer) : Utf8("f", OutputBuffer);} break;
    case jwin::KeyboardButton_G:        {return ShiftMod ? Utf8("G", OutputBuffer) : Utf8("g", OutputBuffer);} break;
    case jwin::KeyboardButton_H:        {return ShiftMod ? Utf8("H", OutputBuffer) : Utf8("h", OutputBuffer);} break;
    case jwin::KeyboardButton_I:        {return ShiftMod ? Utf8("I", OutputBuffer) : Utf8("i", OutputBuffer);} break;
    case jwin::KeyboardButton_J:        {return ShiftMod ? Utf8("J", OutputBuffer) : Utf8("j", OutputBuffer);} break;
    case jwin::KeyboardButton_K:        {return ShiftMod ? Utf8("K", OutputBuffer) : Utf8("k", OutputBuffer);} break;
    case jwin::KeyboardButton_L:        {return ShiftMod ? Utf8("L", OutputBuffer) : Utf8("l", OutputBuffer);} break;
    case jwin::KeyboardButton_M:        {return ShiftMod ? Utf8("M", OutputBuffer) : Utf8("m", OutputBuffer);} break;
    case jwin::KeyboardButton_N:        {return ShiftMod ? Utf8("N", OutputBuffer) : Utf8("n", OutputBuffer);} break;
    case jwin::KeyboardButton_O:        {return ShiftMod ? Utf8("O", OutputBuffer) : Utf8("o", OutputBuffer);} break;
    case jwin::KeyboardButton_P:        {return ShiftMod ? Utf8("P", OutputBuffer) : Utf8("p", OutputBuffer);} break;
    case jwin::KeyboardButton_Q:        {return ShiftMod ? Utf8("Q", OutputBuffer) : Utf8("q", OutputBuffer);} break;
    case jwin::KeyboardButton_R:        {return ShiftMod ? Utf8("R", OutputBuffer) : Utf8("r", OutputBuffer);} break;
    case jwin::KeyboardButton_S:        {return ShiftMod ? Utf8("S", OutputBuffer) : Utf8("s", OutputBuffer);} break;
    case jwin::KeyboardButton_T:        {return ShiftMod ? Utf8("T", OutputBuffer) : Utf8("t", OutputBuffer);} break;
    case jwin::KeyboardButton_U:        {return ShiftMod ? Utf8("U", OutputBuffer) : Utf8("u", OutputBuffer);} break;
    case jwin::KeyboardButton_V:        {return ShiftMod ? Utf8("V", OutputBuffer) : Utf8("v", OutputBuffer);} break;
    case jwin::KeyboardButton_W:        {return ShiftMod ? Utf8("W", OutputBuffer) : Utf8("w", OutputBuffer);} break;
    case jwin::KeyboardButton_X:        {return ShiftMod ? Utf8("X", OutputBuffer) : Utf8("x", OutputBuffer);} break;
    case jwin::KeyboardButton_Y:        {return ShiftMod ? Utf8("Y", OutputBuffer) : Utf8("y", OutputBuffer);} break;
    case jwin::KeyboardButton_Z:        {return ShiftMod ? Utf8("Z", OutputBuffer) : Utf8("z", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_0:     {return NumLock  ? Utf8("0", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_1:     {return NumLock  ? Utf8("1", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_2:     {return NumLock  ? Utf8("2", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_3:     {return NumLock  ? Utf8("3", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_4:     {return NumLock  ? Utf8("4", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_5:     {return NumLock  ? Utf8("5", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_6:     {return NumLock  ? Utf8("6", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_7:     {return NumLock  ? Utf8("7", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_8:     {return NumLock  ? Utf8("8", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_9:     {return NumLock  ? Utf8("9", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_STAR:  {return Utf8("*", OutputBuffer)                       ;} break;
    case jwin::KeyboardButton_NP_PLUS:  {return Utf8("+", OutputBuffer)                       ;} break;
    case jwin::KeyboardButton_NP_DASH:  {return Utf8("-", OutputBuffer)                       ;} break;
    case jwin::KeyboardButton_NP_SLASH: {return Utf8("/", OutputBuffer)                       ;} break;
    case jwin::KeyboardButton_NP_DEL:   {return NumLock ? Utf8(".", OutputBuffer)  : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_COLON:    {return Shift   ? Utf8(":", OutputBuffer)  : Utf8(";", OutputBuffer) ;} break;
    case jwin::KeyboardButton_EQUAL:    {return Shift   ? Utf8("+", OutputBuffer)  : Utf8("=", OutputBuffer) ;} break;
    case jwin::KeyboardButton_COMMA:    {return Shift   ? Utf8("<", OutputBuffer)  : Utf8(",", OutputBuffer) ;} break;
    case jwin::KeyboardButton_DASH:     {return Shift   ? Utf8("_", OutputBuffer)  : Utf8("-", OutputBuffer) ;} break;
    case jwin::KeyboardButton_DOT:      {return Shift   ? Utf8(">", OutputBuffer)  : Utf8(".", OutputBuffer) ;} break;
    case jwin::KeyboardButton_FSLASH:   {return Shift   ? Utf8("?", OutputBuffer)  : Utf8("/", OutputBuffer) ;} break;
    case jwin::KeyboardButton_TILDE:    {return Shift   ? Utf8("~", OutputBuffer)  : Utf8("`", OutputBuffer) ;} break;
    case jwin::KeyboardButton_LBRACKET: {return Shift   ? Utf8("{", OutputBuffer)  : Utf8("[", OutputBuffer) ;} break;
    case jwin::KeyboardButton_RBRACKET: {return Shift   ? Utf8("}", OutputBuffer)  : Utf8("]", OutputBuffer) ;} break;
    case jwin::KeyboardButton_RBSLASH:  {return Shift   ? Utf8("\\", OutputBuffer) : Utf8("|", OutputBuffer) ;} break;
    case jwin::KeyboardButton_QUOTE:    {return Shift   ? Utf8("\'", OutputBuffer) : Utf8("\"", OutputBuffer);} break;
    case jwin::KeyboardButton_LBSLASH:  {return Shift   ? Utf8("|", OutputBuffer)  : Utf8("\"", OutputBuffer);} break;
  }
  return 0;
}

internal size_t
KeyboardButtonSpanish(jwin::keyboard_input* Keyboard, s32 ButtonCode, utf8_byte* OutputBuffer)
{
  b32 Shift = Active(Keyboard->Key_LSHIFT) || Active(Keyboard->Key_RSHIFT);
  b32 Alt = Active(Keyboard->Key_LALT) || Active(Keyboard->Key_RALT);
  b32 Ctrl = Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL);
  b32 ShiftMod = (!Toggled(Keyboard->Key_CPSLCK) && Shift) || (Toggled(Keyboard->Key_CPSLCK) && !Shift);
  b32 NumLock = Toggled(Keyboard->Key_NP_NMLK);
  switch(ButtonCode)
  {
    case jwin::KeyboardButton_SPACE:    {return !(Alt || Ctrl) ? Utf8(" ", OutputBuffer) : 0;} break;
    case jwin::KeyboardButton_TAB:      {return !(Alt || Ctrl || Shift) ? Utf8("\t", OutputBuffer) : 0;} break;
    case jwin::KeyboardButton_1:        {return Shift ? Utf8("!", OutputBuffer) : Utf8("1", OutputBuffer) ;} break;
    case jwin::KeyboardButton_2:        {return Shift ? Utf8("\"", OutputBuffer) : Utf8("2", OutputBuffer) ;} break;
    case jwin::KeyboardButton_3:        {return Shift ? Utf8("·", OutputBuffer) : Utf8("3", OutputBuffer) ;} break;
    case jwin::KeyboardButton_4:        {return Shift ? Utf8("$", OutputBuffer) : Utf8("4", OutputBuffer) ;} break;
    case jwin::KeyboardButton_5:        {return Shift ? Utf8("%", OutputBuffer) : Utf8("5", OutputBuffer) ;} break;
    case jwin::KeyboardButton_6:        {return Shift ? Utf8("&", OutputBuffer) : Utf8("6", OutputBuffer) ;} break;
    case jwin::KeyboardButton_7:        {return Shift ? Utf8("/", OutputBuffer) : Utf8("7", OutputBuffer) ;} break;
    case jwin::KeyboardButton_8:        {return Shift ? Utf8("(", OutputBuffer) : Utf8("8", OutputBuffer) ;} break;
    case jwin::KeyboardButton_9:        {return Shift ? Utf8(",", OutputBuffer) : Utf8("9", OutputBuffer) ;} break;
    case jwin::KeyboardButton_0:        {return Shift ? Utf8("=", OutputBuffer) : Utf8("0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_A:        {return ShiftMod ? Utf8("A", OutputBuffer) : Utf8("a", OutputBuffer);} break;
    case jwin::KeyboardButton_B:        {return ShiftMod ? Utf8("B", OutputBuffer) : Utf8("b", OutputBuffer);} break;
    case jwin::KeyboardButton_C:        {return ShiftMod ? Utf8("C", OutputBuffer) : Utf8("c", OutputBuffer);} break;
    case jwin::KeyboardButton_D:        {return ShiftMod ? Utf8("D", OutputBuffer) : Utf8("d", OutputBuffer);} break;
    case jwin::KeyboardButton_E:        {return ShiftMod ? Utf8("E", OutputBuffer) : Utf8("e", OutputBuffer);} break;
    case jwin::KeyboardButton_F:        {return ShiftMod ? Utf8("F", OutputBuffer) : Utf8("f", OutputBuffer);} break;
    case jwin::KeyboardButton_G:        {return ShiftMod ? Utf8("G", OutputBuffer) : Utf8("g", OutputBuffer);} break;
    case jwin::KeyboardButton_H:        {return ShiftMod ? Utf8("H", OutputBuffer) : Utf8("h", OutputBuffer);} break;
    case jwin::KeyboardButton_I:        {return ShiftMod ? Utf8("I", OutputBuffer) : Utf8("i", OutputBuffer);} break;
    case jwin::KeyboardButton_J:        {return ShiftMod ? Utf8("J", OutputBuffer) : Utf8("j", OutputBuffer);} break;
    case jwin::KeyboardButton_K:        {return ShiftMod ? Utf8("K", OutputBuffer) : Utf8("k", OutputBuffer);} break;
    case jwin::KeyboardButton_L:        {return ShiftMod ? Utf8("L", OutputBuffer) : Utf8("l", OutputBuffer);} break;
    case jwin::KeyboardButton_M:        {return ShiftMod ? Utf8("M", OutputBuffer) : Utf8("m", OutputBuffer);} break;
    case jwin::KeyboardButton_N:        {return ShiftMod ? Utf8("N", OutputBuffer) : Utf8("n", OutputBuffer);} break;
    case jwin::KeyboardButton_O:        {return ShiftMod ? Utf8("O", OutputBuffer) : Utf8("o", OutputBuffer);} break;
    case jwin::KeyboardButton_P:        {return ShiftMod ? Utf8("P", OutputBuffer) : Utf8("p", OutputBuffer);} break;
    case jwin::KeyboardButton_Q:        {return ShiftMod ? Utf8("Q", OutputBuffer) : Utf8("q", OutputBuffer);} break;
    case jwin::KeyboardButton_R:        {return ShiftMod ? Utf8("R", OutputBuffer) : Utf8("r", OutputBuffer);} break;
    case jwin::KeyboardButton_S:        {return ShiftMod ? Utf8("S", OutputBuffer) : Utf8("s", OutputBuffer);} break;
    case jwin::KeyboardButton_T:        {return ShiftMod ? Utf8("T", OutputBuffer) : Utf8("t", OutputBuffer);} break;
    case jwin::KeyboardButton_U:        {return ShiftMod ? Utf8("U", OutputBuffer) : Utf8("u", OutputBuffer);} break;
    case jwin::KeyboardButton_V:        {return ShiftMod ? Utf8("V", OutputBuffer) : Utf8("v", OutputBuffer);} break;
    case jwin::KeyboardButton_W:        {return ShiftMod ? Utf8("W", OutputBuffer) : Utf8("w", OutputBuffer);} break;
    case jwin::KeyboardButton_X:        {return ShiftMod ? Utf8("X", OutputBuffer) : Utf8("x", OutputBuffer);} break;
    case jwin::KeyboardButton_Y:        {return ShiftMod ? Utf8("Y", OutputBuffer) : Utf8("y", OutputBuffer);} break;
    case jwin::KeyboardButton_Z:        {return ShiftMod ? Utf8("Z", OutputBuffer) : Utf8("z", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_0:     {return NumLock ? Utf8("0", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_1:     {return NumLock ? Utf8("1", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_2:     {return NumLock ? Utf8("2", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_3:     {return NumLock ? Utf8("3", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_4:     {return NumLock ? Utf8("4", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_5:     {return NumLock ? Utf8("5", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_6:     {return NumLock ? Utf8("6", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_7:     {return NumLock ? Utf8("7", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_8:     {return NumLock ? Utf8("8", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_9:     {return NumLock ? Utf8("9", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_STAR:  {return Utf8("*", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_PLUS:  {return Utf8("+", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_DASH:  {return Utf8("-", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_SLASH: {return Utf8("/", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_DEL:   {return NumLock ? Utf8(".", OutputBuffer) : Utf8("\0", OutputBuffer);} break;
    case jwin::KeyboardButton_COLON:    {return Shift ? Utf8("Ñ", OutputBuffer) : Utf8("ñ", OutputBuffer) ;} break;
    case jwin::KeyboardButton_EQUAL:    {return Shift ? Utf8("¿", OutputBuffer)  : Utf8("¡", OutputBuffer) ;} break;
    case jwin::KeyboardButton_COMMA:    {return Shift ? Utf8(";", OutputBuffer)  : Utf8(",", OutputBuffer) ;} break;
    case jwin::KeyboardButton_DASH:     {return Shift ? Utf8("?", OutputBuffer)  : Utf8("\'", OutputBuffer) ;} break;
    case jwin::KeyboardButton_DOT:      {return Shift ? Utf8(":", OutputBuffer)  : Utf8(".", OutputBuffer);} break;
    case jwin::KeyboardButton_FSLASH:   {return Shift ? Utf8("_", OutputBuffer)  : Utf8("-", OutputBuffer);} break;
    case jwin::KeyboardButton_TILDE:    {return Shift ? Utf8("ª", OutputBuffer)  : Utf8("º", OutputBuffer);} break;
    case jwin::KeyboardButton_LBRACKET: {return Shift ? Utf8("^", OutputBuffer)  : Utf8("`", OutputBuffer);} break;
    case jwin::KeyboardButton_RBRACKET: {return Shift ? Utf8("*", OutputBuffer)  : Utf8("+", OutputBuffer);} break;
    case jwin::KeyboardButton_RBSLASH:  {return Shift ? Utf8("Ç", OutputBuffer)  : Utf8("ç", OutputBuffer);} break;
    case jwin::KeyboardButton_QUOTE:    {return Shift ? Utf8("¨", OutputBuffer)  : Utf8("´", OutputBuffer);} break;
    case jwin::KeyboardButton_LBSLASH:  {return Shift ? Utf8(">", OutputBuffer)  : Utf8("<", OutputBuffer);} break;
  }
  return 0;
}

internal size_t
KeyboardButtonSwedish(jwin::keyboard_input* Keyboard, s32 ButtonCode, utf8_byte* OutputBuffer)
{
  b32 Shift = Active(Keyboard->Key_LSHIFT) || Active(Keyboard->Key_RSHIFT);
  b32 Alt = Active(Keyboard->Key_RALT);
  b32 Ctrl = Active(Keyboard->Key_LCTRL) || Active(Keyboard->Key_RCTRL);
  b32 ShiftMod = (!Toggled(Keyboard->Key_CPSLCK) && Shift) || (Toggled(Keyboard->Key_CPSLCK) && !Shift);
  b32 NumLock = Toggled(Keyboard->Key_NP_NMLK);
  switch(ButtonCode)
  {
    case jwin::KeyboardButton_SPACE:    {return !(Alt || Ctrl) ? Utf8(" ", OutputBuffer) : 0;} break;
    case jwin::KeyboardButton_TAB:      {return !(Alt || Ctrl || Shift) ? Utf8("\t", OutputBuffer) : 0;} break;
    case jwin::KeyboardButton_1:        {return Shift ? Utf8("!", OutputBuffer) : Utf8("1", OutputBuffer) ;} break;
    case jwin::KeyboardButton_2:        {return (Shift && !Alt) ? Utf8("\"", OutputBuffer) : ((!Shift && Alt) ? Utf8("@", OutputBuffer) : Utf8("2", OutputBuffer));} break;
    case jwin::KeyboardButton_3:        {return (Shift && !Alt) ? Utf8("#", OutputBuffer) : ((!Shift && Alt) ? Utf8("£", OutputBuffer) : Utf8("3", OutputBuffer));} break;
    case jwin::KeyboardButton_4:        {return (Shift && !Alt) ? Utf8("¤", OutputBuffer) : ((!Shift && Alt) ? Utf8("$", OutputBuffer) : Utf8("4", OutputBuffer));} break;
    case jwin::KeyboardButton_5:        {return (Shift && !Alt) ? Utf8("%", OutputBuffer) : ((!Shift && Alt) ? Utf8("€", OutputBuffer) : Utf8("5", OutputBuffer));} break;
    case jwin::KeyboardButton_6:        {return Shift ? Utf8("&", OutputBuffer) : Utf8("6", OutputBuffer) ;} break;
    case jwin::KeyboardButton_7:        {return (Shift && !Alt) ? Utf8("/", OutputBuffer) : ((!Shift && Alt) ? Utf8("{", OutputBuffer) : Utf8("7", OutputBuffer));} break;
    case jwin::KeyboardButton_8:        {return (Shift && !Alt) ? Utf8("(", OutputBuffer) : ((!Shift && Alt) ? Utf8("[", OutputBuffer) : Utf8("8", OutputBuffer));} break;
    case jwin::KeyboardButton_9:        {return (Shift && !Alt) ? Utf8(",", OutputBuffer) : ((!Shift && Alt) ? Utf8("]", OutputBuffer) : Utf8("9", OutputBuffer));} break;
    case jwin::KeyboardButton_0:        {return (Shift && !Alt) ? Utf8("=", OutputBuffer) : ((!Shift && Alt) ? Utf8("}", OutputBuffer) : Utf8("0", OutputBuffer));} break;
    case jwin::KeyboardButton_A:        {return ShiftMod ? Utf8("A", OutputBuffer) : Utf8("a", OutputBuffer);} break;
    case jwin::KeyboardButton_B:        {return ShiftMod ? Utf8("B", OutputBuffer) : Utf8("b", OutputBuffer);} break;
    case jwin::KeyboardButton_C:        {return ShiftMod ? Utf8("C", OutputBuffer) : Utf8("c", OutputBuffer);} break;
    case jwin::KeyboardButton_D:        {return ShiftMod ? Utf8("D", OutputBuffer) : Utf8("d", OutputBuffer);} break;
    case jwin::KeyboardButton_E:        {return ShiftMod ? Utf8("E", OutputBuffer) : Utf8("e", OutputBuffer);} break;
    case jwin::KeyboardButton_F:        {return ShiftMod ? Utf8("F", OutputBuffer) : Utf8("f", OutputBuffer);} break;
    case jwin::KeyboardButton_G:        {return ShiftMod ? Utf8("G", OutputBuffer) : Utf8("g", OutputBuffer);} break;
    case jwin::KeyboardButton_H:        {return ShiftMod ? Utf8("H", OutputBuffer) : Utf8("h", OutputBuffer);} break;
    case jwin::KeyboardButton_I:        {return ShiftMod ? Utf8("I", OutputBuffer) : Utf8("i", OutputBuffer);} break;
    case jwin::KeyboardButton_J:        {return ShiftMod ? Utf8("J", OutputBuffer) : Utf8("j", OutputBuffer);} break;
    case jwin::KeyboardButton_K:        {return ShiftMod ? Utf8("K", OutputBuffer) : Utf8("k", OutputBuffer);} break;
    case jwin::KeyboardButton_L:        {return ShiftMod ? Utf8("L", OutputBuffer) : Utf8("l", OutputBuffer);} break;
    case jwin::KeyboardButton_M:        {return ShiftMod ? Utf8("M", OutputBuffer) : Utf8("m", OutputBuffer);} break;
    case jwin::KeyboardButton_N:        {return ShiftMod ? Utf8("N", OutputBuffer) : Utf8("n", OutputBuffer);} break;
    case jwin::KeyboardButton_O:        {return ShiftMod ? Utf8("O", OutputBuffer) : Utf8("o", OutputBuffer);} break;
    case jwin::KeyboardButton_P:        {return ShiftMod ? Utf8("P", OutputBuffer) : Utf8("p", OutputBuffer);} break;
    case jwin::KeyboardButton_Q:        {return ShiftMod ? Utf8("Q", OutputBuffer) : Utf8("q", OutputBuffer);} break;
    case jwin::KeyboardButton_R:        {return ShiftMod ? Utf8("R", OutputBuffer) : Utf8("r", OutputBuffer);} break;
    case jwin::KeyboardButton_S:        {return ShiftMod ? Utf8("S", OutputBuffer) : Utf8("s", OutputBuffer);} break;
    case jwin::KeyboardButton_T:        {return ShiftMod ? Utf8("T", OutputBuffer) : Utf8("t", OutputBuffer);} break;
    case jwin::KeyboardButton_U:        {return ShiftMod ? Utf8("U", OutputBuffer) : Utf8("u", OutputBuffer);} break;
    case jwin::KeyboardButton_V:        {return ShiftMod ? Utf8("V", OutputBuffer) : Utf8("v", OutputBuffer);} break;
    case jwin::KeyboardButton_W:        {return ShiftMod ? Utf8("W", OutputBuffer) : Utf8("w", OutputBuffer);} break;
    case jwin::KeyboardButton_X:        {return ShiftMod ? Utf8("X", OutputBuffer) : Utf8("x", OutputBuffer);} break;
    case jwin::KeyboardButton_Y:        {return ShiftMod ? Utf8("Y", OutputBuffer) : Utf8("y", OutputBuffer);} break;
    case jwin::KeyboardButton_Z:        {return ShiftMod ? Utf8("Z", OutputBuffer) : Utf8("z", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_0:     {return NumLock ? Utf8("0", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_1:     {return NumLock ? Utf8("1", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_2:     {return NumLock ? Utf8("2", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_3:     {return NumLock ? Utf8("3", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_4:     {return NumLock ? Utf8("4", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_5:     {return NumLock ? Utf8("5", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_6:     {return NumLock ? Utf8("6", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_7:     {return NumLock ? Utf8("7", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_8:     {return NumLock ? Utf8("8", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_9:     {return NumLock ? Utf8("9", OutputBuffer) : Utf8("\0", OutputBuffer) ;} break;
    case jwin::KeyboardButton_NP_STAR:  {return Utf8("*", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_PLUS:  {return Utf8("+", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_DASH:  {return Utf8("-", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_SLASH: {return Utf8("/", OutputBuffer);} break;
    case jwin::KeyboardButton_NP_DEL:   {return NumLock ? Utf8(".", OutputBuffer) : Utf8("\0", OutputBuffer);} break;  
    case jwin::KeyboardButton_COLON:    {return Shift ? Utf8("Ö", OutputBuffer)  : Utf8("ö", OutputBuffer) ;} break;
    case jwin::KeyboardButton_EQUAL:    {return Shift ? Utf8("`", OutputBuffer)  : Utf8("´", OutputBuffer) ;} break;
    case jwin::KeyboardButton_COMMA:    {return Shift ? Utf8(";", OutputBuffer)  : Utf8(",", OutputBuffer) ;} break;
    case jwin::KeyboardButton_DASH:     {return Shift ? Utf8("+", OutputBuffer)  : Utf8("?", OutputBuffer) ;} break;
    case jwin::KeyboardButton_DOT:      {return Shift ? Utf8(":", OutputBuffer)  : Utf8(".", OutputBuffer) ;} break;
    case jwin::KeyboardButton_FSLASH:   {return Shift ? Utf8("_", OutputBuffer)  : Utf8("-", OutputBuffer) ;} break;
    case jwin::KeyboardButton_TILDE:    {return Shift ? Utf8("½", OutputBuffer)  : Utf8("§", OutputBuffer) ;} break;
    case jwin::KeyboardButton_LBRACKET: {return Shift ? Utf8("Å", OutputBuffer)  : Utf8("å", OutputBuffer) ;} break;
    case jwin::KeyboardButton_RBRACKET: {return Shift ? Utf8("^", OutputBuffer)  : Utf8("¨", OutputBuffer) ;} break;
    case jwin::KeyboardButton_RBSLASH:  {return Shift ? Utf8("*", OutputBuffer)  : Utf8("\'", OutputBuffer) ;} break;
    case jwin::KeyboardButton_QUOTE:    {return Shift ? Utf8("Ä", OutputBuffer)  : Utf8("ä", OutputBuffer) ;} break;
    case jwin::KeyboardButton_LBSLASH:  {return Shift ? Utf8(">", OutputBuffer)  : Utf8("<", OutputBuffer) ;} break;
  }
  return 0;
}

internal size_t
KeyboardButtonUTF8(jwin::keyboard_input* Keyboard, s32 ButtonCode, s32 Language, utf8_byte* OutputBuffer)
{
  switch(Language)
  {
    case SPANISH: {return KeyboardButtonSpanish(Keyboard, ButtonCode, OutputBuffer); } break;
    case SWEDISH: {return KeyboardButtonSwedish(Keyboard, ButtonCode, OutputBuffer); } break;
    default: {return KeyboardButtonEnglish(Keyboard, ButtonCode, OutputBuffer); } break;
  }
  return 0;
}

void ClearBuffer(utf8_string_buffer* StringBuffer)
{
  utils::ZeroSize(StringBuffer->Position, StringBuffer->Buffer);
  StringBuffer->Position = 0;
}

void EraseFromBuffer(utf8_string_buffer* StringBuffer, s32 Utf8CharsToErase)
{
  jwin_Assert(StringBuffer->Buffer[StringBuffer->Position] == 0);
  short FirstCharOffset = utf8_getOffsetToFirstChar(&StringBuffer->Buffer[StringBuffer->Position-1])-1;
  while(Utf8CharsToErase-- > 0 && StringBuffer->Position > 0)
  {
    size_t ByteCount = utf8_getByteCountForChar(&StringBuffer->Buffer[StringBuffer->Position + FirstCharOffset]);
    for(int Index = 0; Index < ByteCount; Index++)
    {
      StringBuffer->Buffer[StringBuffer->Position-ByteCount + Index] = 0;
    }
    jwin_Assert(StringBuffer->Position >= ByteCount);
    StringBuffer->Position-=ByteCount;
  }
}

void CopyBufferContent(utf8_string_buffer* SrcBuf, utf8_string_buffer* DstBuf)
{
  jwin_Assert(DstBuf->BufferSize < (DstBuf->Position + SrcBuf->Position)); 
  for (int i = 0; i < SrcBuf->Position; ++i)
  {
    DstBuf->Buffer[DstBuf->Position++] = SrcBuf->Buffer[i];
  }
}

void ConcatinateBuffers(utf8_string_buffer* BuffA, utf8_string_buffer* BuffB, utf8_string_buffer* DstBuf)
{
  CopyBufferContent(BuffA, DstBuf);
  CopyBufferContent(BuffB, DstBuf);
}

void AppendStringToBuffer(const utf8_byte* String, utf8_string_buffer* Buf)
{  
  utf8_byte* Scan = (utf8_byte*) String;
  midx StringByteLength = 0;
  while(*Scan != 0)
  {
    Buf->Buffer[Buf->Position++] = *Scan;
    Scan++;
  }
}

midx PushInputToBuffer(jwin::keyboard_input* Keyboard, utf8_string_buffer* StringBuffer, s32 Language)
{
  midx BytesRead = 0;
  if(StringBuffer->Position+8 <= StringBuffer->BufferSize)
  {
    for(u32 ButtonCode = 0; ButtonCode < jwin::KeyboardButton_COUNT; ++ButtonCode)
    {
      jwin::binary_signal_state Button = Keyboard->Keys[ButtonCode];
      if(Pushed(Button))
      {
        utf8_byte TempBuf[8] = {};
        BytesRead += KeyboardButtonUTF8(Keyboard, ButtonCode, Language, TempBuf);
        AppendStringToBuffer(TempBuf, StringBuffer);
      }
    }
  }
  return BytesRead;
}


u32 ConvertToUnicodeEnglish(utf8_byte *utf8Input, u32* unicodeOutput)
{
  int i = 0;
  while(utf8Input[i])
  {
    unicodeOutput[i] = Utf8ToUnicode(&utf8Input[i]);
    i += utf8_getByteCountForChar(&utf8Input[i]);
  } 
  return i;
}

b32 CompareStr(utf8_byte* StrA, const char* StrB)
{
  while(*StrB)
  {
    char a = *StrA;
    char b = *StrB;
    if(a != b)
    {
      return false;
    }
    StrA++;
    StrB++;
  }
  return true;
}

#define KEK_(str)  unicodeOutput[j] = Utf8ToUnicode((const utf8_byte*)(str));  i += ni + utf8_getByteCountForChar(&utf8Input[i+ni]);

u32 ConvertToUnicodeAccented(utf8_byte *utf8Input, u32* unicodeOutput)
{
  u32 i = 0;
  u32 j = 0;
  while (utf8Input[i])
  {
    const char* a = "`";
    const char* b = "´";
    utf8_byte CurrentChar = utf8Input[i];
    if(utf8Input[i+1] != '\0')
    {
      u32 ni = utf8_getByteCountForChar(&utf8Input[i]);
      utf8_byte NextChar = utf8Input[i+ni];
      if(CompareStr(&utf8Input[i], "´"))
      {
        switch(NextChar)
        {
          case 'a':{ KEK_("á"); }break;
          case 'e':{ KEK_("é"); }break;
          case 'i':{ KEK_("í"); }break;
          case 'o':{ KEK_("ó"); }break;
          case 'u':{ KEK_("ú"); }break;
          case 'y':{ KEK_("ý"); }break;
          case 'A':{ KEK_("Á"); }break;
          case 'E':{ KEK_("É"); }break;
          case 'I':{ KEK_("Í"); }break;
          case 'O':{ KEK_("Ó"); }break;
          case 'U':{ KEK_("Ú"); }break;
          case 'Y':{ KEK_("Ý"); }break;
          default: { 
            unicodeOutput[j] = Utf8ToUnicode(&utf8Input[i]);
            i += utf8_getByteCountForChar(&utf8Input[i]);
          } break;
        }
      }
      else if(CompareStr(&utf8Input[i], "`"))
      {
        switch(NextChar)
        {
          case 'a':{ KEK_("à"); }break;
          case 'e':{ KEK_("è"); }break;
          case 'i':{ KEK_("ì"); }break;
          case 'o':{ KEK_("ò"); }break;
          case 'u':{ KEK_("ù"); }break;
          case 'A':{ KEK_("À"); }break;
          case 'E':{ KEK_("È"); }break;
          case 'I':{ KEK_("È"); }break;
          case 'O':{ KEK_("Ò"); }break;
          case 'U':{ KEK_("Ù"); }break;
          default: { 
            unicodeOutput[j] = Utf8ToUnicode(&utf8Input[i]);
            i += utf8_getByteCountForChar(&utf8Input[i]);
          } break;
        }
      }
      else if(CompareStr(&utf8Input[i], "^"))
      {
        switch(NextChar)
        {
          case 'a':{ KEK_( "â"); }break;
          case 'e':{ KEK_( "ê"); }break;
          case 'i':{ KEK_( "î"); }break;
          case 'o':{ KEK_( "ô"); }break;
          case 'u':{ KEK_( "û"); }break;
          case 'A':{ KEK_( "Â"); }break;
          case 'E':{ KEK_( "Ê"); }break;
          case 'I':{ KEK_( "Î"); }break;
          case 'O':{ KEK_( "Ô"); }break;
          case 'U':{ KEK_( "Û"); }break;
          default: { 
            unicodeOutput[j] = Utf8ToUnicode(&utf8Input[i]);
            i += utf8_getByteCountForChar(&utf8Input[i]);
          } break;
        }
      }
      else if(CompareStr(&utf8Input[i], "¨"))
      {
        switch(NextChar)
        {
          case 'a':{ KEK_("ä"); }break;
          case 'e':{ KEK_("ë"); }break;
          case 'i':{ KEK_("ï"); }break;
          case 'o':{ KEK_("ö"); }break;
          case 'u':{ KEK_("ü"); }break;
          case 'y':{ KEK_("ÿ"); }break;
          case 'A':{ KEK_("Ä"); }break;
          case 'E':{ KEK_("Ë"); }break;
          case 'I':{ KEK_("Ï"); }break;
          case 'O':{ KEK_("Ö"); }break;
          case 'U':{ KEK_("Ü"); }break;
          default: { 
            unicodeOutput[j] = Utf8ToUnicode(&utf8Input[i]);
            i += utf8_getByteCountForChar(&utf8Input[i]);
          } break;
        }
      }else{

        unicodeOutput[j] = Utf8ToUnicode(&utf8Input[i]);
    i += utf8_getByteCountForChar(&utf8Input[i]);
      }
    } else {
      unicodeOutput[j] = Utf8ToUnicode(&utf8Input[i]);
    i += utf8_getByteCountForChar(&utf8Input[i]);
    }
    j++;
  }
  return j;
}

u32 ConvertToUnicode(utf8_byte *utf8Input, u32* unicodeOutput)
{
  return ConvertToUnicodeAccented(utf8Input, unicodeOutput);
}
