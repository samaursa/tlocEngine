#include "tlocString.h"
#include "tlocString.inl.h"

namespace tloc { namespace core { namespace string {

  // ------------------------------------------------------------------------
  // static variable definitions

  char8 g_controls[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                        0x09,
                        0x0A, 0x0B, 0x0C, 0x0D,
                        0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                        0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                        0x7F,
                        NULL};
  String g_controlsStr(g_controls);

  char8 g_blank[] = {0x09, 0x20, NULL};
  String g_blankStr(g_blank);

  char8 g_space[] = {0x09,
                     0x0A, 0x0B, 0x0C, 0x0D,
                     0x20, NULL};
  String g_spaceStr(g_space);

  char8 g_upper[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
                     0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
                     0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
                     NULL};
  String g_upperStr(g_upper);

  char8 g_lower[] = {0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                     0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
                     0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,
                     NULL};
  String g_lowerStr(g_lower);

  char8 g_alpha[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
                     0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
                     0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
                     0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                     0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
                     0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,
                     NULL};
  String g_alphaStr(g_alpha);

  char8 g_digit[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
                     0x39, NULL};
  String g_digitStr(g_digit);

  char8 g_xdigit[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
                      0x39,
                      0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
                      0x61, 0x62, 0x63, 0x64, 0x65, 0x66, NULL};
  String g_xdigitStr(g_xdigit);

  char8 g_alnum[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
                     0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
                     0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
                     0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                     0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
                     0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,
                     0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
                     0x39, NULL};
  String g_alnumStr(g_alnum);

  char8 g_punct[] = {0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
                     0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
                     0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
                     0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,
                     0x7B, 0x7C, 0x7D, 0x7E, NULL};
  String g_punctStr(g_punct);

  // ------------------------------------------------------------------------
  // specialized function definitions

  template <>
  tl_size
    StrLen( const char8* aCharStr)
  {
    // According to EASTL, this should call intrinsics
    return (tl_size)strlen(aCharStr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <>
  tl_int
    StrCmp( const char8* src, const char8* dst)
  {
    // std implementation is faster
    return strcmp(src, dst);
  }


  template <>
  tl_int
    StrCmp( const char8* aPtr1, const char8* aPtr2,
            const tl_size& aNumChars )
  {
    return memcmp(aPtr1, aPtr2, aNumChars);
  }

  tl_size
    CharAsciiToWide(char32* a_out, const char8* a_in, tl_int a_inSize)
  {
    return ::mbstowcs(a_out, a_in, a_inSize);
  }

  tl_size
    CharWideToAscii(char8* a_out, const char32* a_in, tl_int a_inSize)
  {
    return ::wcstombs(a_out, a_in, a_inSize);
  }

  bool
    IsCntrl(char8 a_char)
  {
    // We cannot test for NULL in g_controlStr because it is also the terminator
    if (a_char == 0)
    { return true; }

    return g_controlsStr.find(a_char) != String::npos;
  }

  bool
    IsBlank(char8 a_char)
  { return g_blankStr.find(a_char) != String::npos; }

  bool
    IsSpace(char8 a_char)
  { return g_spaceStr.find(a_char) != String::npos; }

  bool
    IsUpper(char8 a_char)
  { return g_upperStr.find(a_char) != String::npos; }

  bool
    IsLower(char8 a_char)
  { return g_lowerStr.find(a_char) != String::npos; }

  bool
    IsAlpha(char8 a_char)
  { return g_alphaStr.find(a_char) != String::npos; }

  bool
    IsDigit(char8 a_char)
  { return g_digitStr.find(a_char) != String::npos; }

  bool
    IsNumber(const char8* a_char)
  {
    typedef const char8*    iterator;

    iterator itr    = a_char;
    iterator itrEnd = a_char + StrLen(a_char);

    // Starting with a minus sign? Continue...
    if (*itr == '-')
    {
      ++itr;

      // only a minus sign is not a number
      if (itr == itrEnd)
      { return false; }
    }

    while (itr != itrEnd)
    {
      if (IsDigit(*itr) == false)
      {
        return false;
      }
      ++itr;
    }

    return true;
  }

  bool
    IsRealNumber(const char8* a_char)
  {
    typedef const char8*    iterator;

    iterator itr = a_char;
    iterator itrEnd = a_char + StrLen(a_char);

    // Starting with a minus sign? Continue...
    if (*itr == '-')
    {
      ++itr;

      // only a minus sign is not a number
      if (itr == itrEnd)
      { return false; }
    }

    bool decimalPointFound = false;
    bool exponentFound = false;

    // NOTE about exponent digits: Any exponent digit count is accepted,
    // including 0. The user should check manually if # of digits is required
    while (itr != itrEnd)
    {
      if (*itr == '.')
      {
        if (decimalPointFound)
        { return false; }

        decimalPointFound = true;
      }
      else if (exponentFound == false && (*itr == 'E' || *itr == 'e') )
      {
        exponentFound = true;
        // is the next char a + or -?
        // Note that sign is optional: http://www.cplusplus.com/reference/ios/scientific/
        if ( itr != itrEnd && (*(itr + 1) == '+' || *(itr + 1) == '-') )
        {
          ++itr;
        }
      }
      else
      {
        if (IsDigit(*itr) == false)
        { return false; }
      }

      ++itr;
    }

    return true;
  }

  bool
    IsNegNumber(const char8* a_char)
  {
    typedef const char8*    iterator;

    iterator itr = a_char;

    // Starting with a minus sign? Continue...
    if (*itr == '-')
    {
      return IsNumber(a_char);
    }

    return false;
  }

  bool
    IsNegRealNumber(const char8* a_char)
  {
    typedef const char8*    iterator;

    iterator itr = a_char;

    // Starting with a minus sign? Continue...
    if (*itr == '-')
    {
      return IsRealNumber(a_char);
    }

    return false;
  }

  bool
    IsPosNumber(const char8* a_char)
  {
    if (IsNegNumber(a_char) == false)
    {
      return IsNumber(a_char);
    }

    return false;
  }

  bool
    IsPosRealNumber(const char8* a_char)
  {
    if (IsNegRealNumber(a_char) == false)
    {
      return IsRealNumber(a_char);
    }

    return false;
  }

  bool
    IsXDigit(char8 a_char)
  { return g_xdigitStr.find(a_char) != String::npos; }

  bool
    IsAlNum(char8 a_char)
  { return g_alnumStr.find(a_char) != String::npos; }

  bool
    IsPunct(char8 a_char)
  { return g_punctStr.find(a_char) != String::npos; }

  // ------------------------------------------------------------------------
  // explicit instantiations

  template class StringBase<char8>;
  template class StringBase<char32>;

};};};

//TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE();