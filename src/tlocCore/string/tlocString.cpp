#include "tlocString.h"
#include "tlocString.inl.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <stdio.h>
#include <stdarg.h>

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
  const char8*
    StrChr(const char8* a_string, char a_charToLocate)
  {
    const char8* currChar = a_string;

    while(*currChar != 0)
    {
      if (*currChar == a_charToLocate)
      { return currChar; }

      ++currChar;
    }

    if (*currChar == a_charToLocate)
    { return currChar; }

    return nullptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <>
  char8*
    StrChr(char8* a_string, char a_charToLocate)
  {
    return const_cast<char8*>(StrChr(const_cast<const char8*>(a_string), a_charToLocate) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <>
  const char8*
    StrRChr(const char8* a_string, char a_charToLocate)
  {
    const char8* currChar = a_string;
    const char8* charToRet = nullptr;

    while(*currChar != 0)
    {
      if (*currChar == a_charToLocate)
      { charToRet = currChar; }

      ++currChar;
    }

    if (*currChar == a_charToLocate)
    { charToRet = currChar; }

    return charToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <>
  char8*
    StrRChr(char8* a_string, char a_charToLocate)
  {
    return const_cast<char8*>
      (StrRChr(const_cast<const char8*>(a_string), a_charToLocate) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <>
  tl_int
    StrCmp( const char8* aPtr1, const char8* aPtr2,
            const tl_size& aNumChars )
  {
    return memcmp(aPtr1, aPtr2, aNumChars);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  char32
    CharAsciiToWide(const char8 a_in)
  {
    char32 out[2] = {0, 0};
    char8 in[] = {a_in, '\0'};

    if (CharAsciiToWide(out, in, 1) > 0)
    { 
      TLOC_ASSERT_LOW_LEVEL(out[1] == 0, "More than 1 character written to buffer");
      return out[0];
    }

    return 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  char8
    CharWideToAscii(const char32 a_in)
  {
    char8 out[2] = {0, 0};
    char32 in[] = {a_in, L'\0'};

    if (CharWideToAscii(out, in, 1) > 0)
    { 
      TLOC_ASSERT_LOW_LEVEL(out[1] == 0, "More than 1 character written to buffer");
      return out[0];
    }

    return 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_size
    CharAsciiToWide(char32* a_out, const char8* a_in, tl_size a_inSize)
  {
    return ::mbstowcs(a_out, a_in, a_inSize);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_size
    CharWideToAscii(char8* a_out, const char32* a_in, tl_size a_inSize)
  {
    return ::wcstombs(a_out, a_in, a_inSize);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StringW
    CharAsciiToWide(const String a_in)
  {
    const StringW::size_type length = a_in.length();
    char32* buffer = new char32[length + 1];
    buffer[length] = 0;
    CharAsciiToWide(buffer, a_in.c_str(), a_in.length());
    return StringW(buffer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  String
    CharWideToAscii(const StringW a_in)
  {
    const String::size_type length = a_in.length();
    char8* buffer = new char[length + 1];
    buffer[length] = 0;
    CharWideToAscii(buffer, a_in.c_str(), a_in.length());
    return String(buffer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsCntrl(char8 a_char)
  {
    // We cannot test for NULL in g_controlStr because it is also the terminator
    if (a_char == 0)
    { return true; }

    return g_controlsStr.find(a_char) != String::npos;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsBlank(char8 a_char)
  { return g_blankStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsSpace(char8 a_char)
  { return g_spaceStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsUpper(char8 a_char)
  { return g_upperStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsLower(char8 a_char)
  { return g_lowerStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsAlpha(char8 a_char)
  { return g_alphaStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsDigit(char8 a_char)
  { return g_digitStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsPosNumber(const char8* a_char)
  {
    if (IsNegNumber(a_char) == false)
    {
      return IsNumber(a_char);
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsPosRealNumber(const char8* a_char)
  {
    if (IsNegRealNumber(a_char) == false)
    {
      return IsRealNumber(a_char);
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsXDigit(char8 a_char)
  { return g_xdigitStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsAlNum(char8 a_char)
  { return g_alnumStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    IsPunct(char8 a_char)
  { return g_punctStr.find(a_char) != String::npos; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // Note that this solution for a safer sprintf has been taken from:
  // http://stackoverflow.com/a/69911/368599

  String
    Vformat (const char *fmt, va_list ap)
  {
    // Allocate a buffer on the stack that's big enough for us almost
    // all the time.  Be prepared to allocate dynamically if it doesn't fit.
    const size_t buffSize = 2048;
    size_t size = buffSize;

    char stackbuf[buffSize];
    core_conts::Array<char8> dynamicbuf;
    char *buf = &stackbuf[0];

    for (;;) {
        // Try to vsnprintf into our buffer.
        int needed = vsnprintf (buf, size, fmt, ap);
        // NB. C99 (which modern Linux and OS X follow) says vsnprintf
        // failure returns the length it would have needed.  But older
        // glibc and current Windows return -1 for failure, i.e., not
        // telling us how much was needed.

        if (needed <= (int)size && needed >= 0) {
            // It fit fine so we're done.
            return core_str::String (buf, (size_t) needed);
        }

        // vsnprintf reported that it wanted to write more characters
        // than we allotted.  So try again using a dynamic buffer.  This
        // doesn't happen very often if we chose our initial size well.
        size = (needed > 0) ? (needed+1) : (size*2);
        dynamicbuf.resize (size);
        buf = &dynamicbuf[0];
    }
  }

  String
    Format(const char8* a_string, ...)
  {
    va_list ap;
    va_start (ap, a_string);
    String buf = Vformat (a_string, ap);
    va_end (ap);
    return buf;
  }

  // ------------------------------------------------------------------------
  // explicit instantiations

  template class StringBase<char8>;
  template class StringBase<char32>;

  template bool operator==(const StringBase<char8>&, const StringBase<char8>&);
  template bool operator==(const StringBase<char32>&, const StringBase<char32>&);

  template bool operator==(const char8*, const StringBase<char8>&);
  template bool operator==(const char32*, const StringBase<char32>&);

  template bool operator==(const StringBase<char8>&, const char8*);
  template bool operator==(const StringBase<char32>&, const char32*);

  template bool operator!=(const StringBase<char8>&, const StringBase<char8>&);
  template bool operator!=(const StringBase<char32>&, const StringBase<char32>&);

  template bool operator!=(const char8*, const StringBase<char8>&);
  template bool operator!=(const char32*, const StringBase<char32>&);

  template bool operator!=(const StringBase<char8>&, const char8*);
  template bool operator!=(const StringBase<char32>&, const char32*);

};};};

namespace tloc { namespace core {

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // Hash

  // -----------------------------------------------------------------------
  // https://sites.google.com/site/murmurhash/

//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

// Note - The x86 and x64 versions do _not_ produce the same results, as the
// algorithms are optimized for their respective platforms. You can still
// compile and run any of them on any platform, but your performance with the
// non-native version will be less than optimal.

  //-----------------------------------------------------------------------------
  // Platform-specific functions and macros

  // Microsoft Visual Studio

#if defined(_MSC_VER)

#include <stdlib.h>

#define ROTL32(x,y)	_rotl(x,y)
#define ROTL64(x,y)	_rotl64(x,y)

#define BIG_CONSTANT(x) (x)

  // Other compilers

#else	// defined(_MSC_VER)

  inline u32 rotl32 ( u32 x, s8 r )
  {
    return (x << r) | (x >> (32 - r));
  }

  inline u64 rotl64 ( u64 x, s8 r )
  {
    return (x << r) | (x >> (64 - r));
  }

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

#endif // !defined(_MSC_VER)

  //-----------------------------------------------------------------------------
  // Block read - if your platform needs to do endian-swapping or can only
  // handle aligned reads, do the conversion here

  u32 getblock32 ( const u32 * p, int i )
  {
    return p[i];
  }

  u64 getblock64 ( const u64 * p, int i )
  {
    return p[i];
  }

  //-----------------------------------------------------------------------------
  // Finalization mix - force all bits of a hash block to avalanche

  u32 fmix32 ( u32 h )
  {
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
  }

  //----------

  u64 fmix64 ( u64 k )
  {
    k ^= k >> 33;
    k *= BIG_CONSTANT(0xff51afd7ed558ccd);
    k ^= k >> 33;
    k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
    k ^= k >> 33;

    return k;
  }

  //-----------------------------------------------------------------------------

  void MurmurHash3_x86_32 ( const void * key, tl_int len,
                            u32 seed, void * out )
  {
    const s8 * data = (const s8*)key;
    const int nblocks = len / 4;

    u32 h1 = seed;

    const u32 c1 = 0xcc9e2d51;
    const u32 c2 = 0x1b873593;

    //----------
    // body

    const u32 * blocks = (const u32 *)(data + nblocks*4);

    for(int i = -nblocks; i; i++)
    {
      u32 k1 = getblock32(blocks,i);

      k1 *= c1;
      k1 = ROTL32(k1,15);
      k1 *= c2;

      h1 ^= k1;
      h1 = ROTL32(h1,13);
      h1 = h1*5+0xe6546b64;
    }

    //----------
    // tail

    const s8 * tail = (const s8*)(data + nblocks*4);

    u32 k1 = 0;

    switch(len & 3)
    {
    case 3: k1 ^= tail[2] << 16;
    case 2: k1 ^= tail[1] << 8;
    case 1: k1 ^= tail[0];
      k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len;

    h1 = fmix32(h1);

    *(u32*)out = h1;
  }

  //-----------------------------------------------------------------------------

  void MurmurHash3_x86_128 ( const void * key, const int len,
    u32 seed, void * out )
  {
    const s8 * data = (const s8*)key;
    const int nblocks = len / 16;

    u32 h1 = seed;
    u32 h2 = seed;
    u32 h3 = seed;
    u32 h4 = seed;

    const u32 c1 = 0x239b961b;
    const u32 c2 = 0xab0e9789;
    const u32 c3 = 0x38b34ae5;
    const u32 c4 = 0xa1e38b93;

    //----------
    // body

    const u32 * blocks = (const u32 *)(data + nblocks*16);

    for(int i = -nblocks; i; i++)
    {
      u32 k1 = getblock32(blocks,i*4+0);
      u32 k2 = getblock32(blocks,i*4+1);
      u32 k3 = getblock32(blocks,i*4+2);
      u32 k4 = getblock32(blocks,i*4+3);

      k1 *= c1; k1  = ROTL32(k1,15); k1 *= c2; h1 ^= k1;

      h1 = ROTL32(h1,19); h1 += h2; h1 = h1*5+0x561ccd1b;

      k2 *= c2; k2  = ROTL32(k2,16); k2 *= c3; h2 ^= k2;

      h2 = ROTL32(h2,17); h2 += h3; h2 = h2*5+0x0bcaa747;

      k3 *= c3; k3  = ROTL32(k3,17); k3 *= c4; h3 ^= k3;

      h3 = ROTL32(h3,15); h3 += h4; h3 = h3*5+0x96cd1c35;

      k4 *= c4; k4  = ROTL32(k4,18); k4 *= c1; h4 ^= k4;

      h4 = ROTL32(h4,13); h4 += h1; h4 = h4*5+0x32ac3b17;
    }

    //----------
    // tail

    const s8 * tail = (const s8*)(data + nblocks*16);

    u32 k1 = 0;
    u32 k2 = 0;
    u32 k3 = 0;
    u32 k4 = 0;

    switch(len & 15)
    {
    case 15: k4 ^= tail[14] << 16;
    case 14: k4 ^= tail[13] << 8;
    case 13: k4 ^= tail[12] << 0;
      k4 *= c4; k4  = ROTL32(k4,18); k4 *= c1; h4 ^= k4;

    case 12: k3 ^= tail[11] << 24;
    case 11: k3 ^= tail[10] << 16;
    case 10: k3 ^= tail[ 9] << 8;
    case  9: k3 ^= tail[ 8] << 0;
      k3 *= c3; k3  = ROTL32(k3,17); k3 *= c4; h3 ^= k3;

    case  8: k2 ^= tail[ 7] << 24;
    case  7: k2 ^= tail[ 6] << 16;
    case  6: k2 ^= tail[ 5] << 8;
    case  5: k2 ^= tail[ 4] << 0;
      k2 *= c2; k2  = ROTL32(k2,16); k2 *= c3; h2 ^= k2;

    case  4: k1 ^= tail[ 3] << 24;
    case  3: k1 ^= tail[ 2] << 16;
    case  2: k1 ^= tail[ 1] << 8;
    case  1: k1 ^= tail[ 0] << 0;
      k1 *= c1; k1  = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len; h2 ^= len; h3 ^= len; h4 ^= len;

    h1 += h2; h1 += h3; h1 += h4;
    h2 += h1; h3 += h1; h4 += h1;

    h1 = fmix32(h1);
    h2 = fmix32(h2);
    h3 = fmix32(h3);
    h4 = fmix32(h4);

    h1 += h2; h1 += h3; h1 += h4;
    h2 += h1; h3 += h1; h4 += h1;

    ((u32*)out)[0] = h1;
    ((u32*)out)[1] = h2;
    ((u32*)out)[2] = h3;
    ((u32*)out)[3] = h4;
  }

//-----------------------------------------------------------------------------

  void MurmurHash3_x64_128 ( const void * key, const int len,
                             const u32 seed, void * out )
  {
    const s8 * data = (const s8*)key;
    const int nblocks = len / 16;

    u64 h1 = seed;
    u64 h2 = seed;

    const u64 c1 = BIG_CONSTANT(0x87c37b91114253d5);
    const u64 c2 = BIG_CONSTANT(0x4cf5ad432745937f);

    //----------
    // body

    const u64 * blocks = (const u64 *)(data);

    for(int i = 0; i < nblocks; i++)
    {
      u64 k1 = getblock64(blocks,i*2+0);
      u64 k2 = getblock64(blocks,i*2+1);

      k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;

      h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

      k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

      h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
    }

    //----------
    // tail

    const u8 * tail = (const u8*)(data + nblocks*16);

    u64 k1 = 0;
    u64 k2 = 0;

    switch(len & 15)
    {
    case 15: k2 ^= ((u64)tail[14]) << 48;
    case 14: k2 ^= ((u64)tail[13]) << 40;
    case 13: k2 ^= ((u64)tail[12]) << 32;
    case 12: k2 ^= ((u64)tail[11]) << 24;
    case 11: k2 ^= ((u64)tail[10]) << 16;
    case 10: k2 ^= ((u64)tail[ 9]) << 8;
    case  9: k2 ^= ((u64)tail[ 8]) << 0;
      k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

    case  8: k1 ^= ((u64)tail[ 7]) << 56;
    case  7: k1 ^= ((u64)tail[ 6]) << 48;
    case  6: k1 ^= ((u64)tail[ 5]) << 40;
    case  5: k1 ^= ((u64)tail[ 4]) << 32;
    case  4: k1 ^= ((u64)tail[ 3]) << 24;
    case  3: k1 ^= ((u64)tail[ 2]) << 16;
    case  2: k1 ^= ((u64)tail[ 1]) << 8;
    case  1: k1 ^= ((u64)tail[ 0]) << 0;
      k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len; h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    ((u64*)out)[0] = h1;
    ((u64*)out)[1] = h2;
  }

  //-----------------------------------------------------------------------------

  tl_size
    hash<core_str::String>::
    operator()(const core_str::String& a_value) const
  {
    tl_uint valueLength =
      core_utils::CastNumber<tl_uint>(a_value.size());

    // using 32-bit hash for now
    u32 hash;
    MurmurHash3_x86_32(a_value.c_str(), valueLength, 35, &hash);

    return core_utils::CastNumber<tl_size>(hash);
  }

};};