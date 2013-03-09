#pragma once
#ifndef TLOC_BASIC_TYPES_H
#define TLOC_BASIC_TYPES_H

#include <tlocCore/tlocCoreBase.h>
#include <wctype.h>
#include <limits.h>
#include <stddef.h> // Needed for OSX built-in types

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // C++11 NULL define (this will be removed when compiling as C++11)

  // Copied from http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/nullptr#Solution_and_Sample_Code
  const // It is a const object...
  class nullptr_t
  {
  public:
    template<class T>
    inline operator T*() const // convertible to any type of null non-member pointer...
    { return 0; }

    template<class C, class T>
    inline operator T C::*() const   // or any type of null member pointer...
    { return 0; }

  private:
    void operator&() const;  // Can't take address of nullptr

  } nullptr = {};

  //////////////////////////////////////////////////////////////////////////
  // Windows Types

#if defined(WIN32) || defined(_WIN32) || defined (_WIN64)
#define TLOC_INT8_TYPE  __int8
#define TLOC_INT16_TYPE __int16
#define TLOC_INT32_TYPE __int32
#define TLOC_INT64_TYPE __int64

#define TLOC_U_INT8_TYPE unsigned TLOC_INT8_TYPE
#define TLOC_U_INT16_TYPE unsigned TLOC_INT16_TYPE
#define TLOC_U_INT32_TYPE unsigned TLOC_INT32_TYPE
#define TLOC_U_INT64_TYPE unsigned TLOC_INT64_TYPE

#define TLOC_SIZE_TYPE      size_t
#define TLOC_U_INT_PTR_TYPE uintptr_t
#define TLOC_PTR_DIFF_TYPE  ptrdiff_t
#endif

  //////////////////////////////////////////////////////////////////////////
  // OSX Types

#if defined(TARGET_OS_MAC) || defined (__APPLE__) || defined (MACOSX) || defined (macintosh) || defined (Macintosh)

#define TLOC_INT8_TYPE  __int8_t
#define TLOC_INT16_TYPE __int16_t
#define TLOC_INT32_TYPE __int32_t
#define TLOC_INT64_TYPE __int64_t

#define TLOC_U_INT8_TYPE  __uint8_t
#define TLOC_U_INT16_TYPE __uint16_t
#define TLOC_U_INT32_TYPE __uint32_t
#define TLOC_U_INT64_TYPE __uint64_t

#define TLOC_SIZE_TYPE      size_t
#define TLOC_U_INT_PTR_TYPE uintptr_t
#define TLOC_PTR_DIFF_TYPE  ptrdiff_t
#endif

  //////////////////////////////////////////////////////////////////////////
  // Basic types

  typedef char              char8;
  typedef wchar_t           char32;

  // typedef short          short; // cannot typedef this for obvious reasons
  typedef unsigned short    ushort;

  typedef TLOC_INT8_TYPE    s8;
  typedef TLOC_INT16_TYPE   s16;
  typedef TLOC_INT32_TYPE   s32;
  typedef TLOC_INT64_TYPE   s64;
  typedef float             f32;
  typedef double            f64;
  typedef long double       f128;

  typedef unsigned char     uchar8;
  typedef TLOC_U_INT8_TYPE   u8;
  typedef TLOC_U_INT16_TYPE  u16;
  typedef TLOC_U_INT32_TYPE  u32;
  typedef TLOC_U_INT64_TYPE  u64;

  typedef long                 tl_long;
  typedef unsigned long        tl_ulong;
  typedef TLOC_SIZE_TYPE       tl_size;
  typedef TLOC_U_INT_PTR_TYPE  tl_uintptr; // Guaranteed to hold a native pointer
  typedef TLOC_PTR_DIFF_TYPE   tl_ptrdiff;

  //------------------------------------------------------------------------
  // The following types are useful when you want the best type size depending
  // on the platform itself

#if defined(_WIN64) || defined(__LP64__)
  typedef s64               tl_int;
  typedef u64               tl_uint;
  typedef f64               tl_float;
#elif defined(WIN32) || defined(_WIN32) || ( defined(__APPLE__) && !defined(__LP64__) )
  typedef s32               tl_int;
  typedef u32               tl_uint;
  typedef f32               tl_float;
#else
# error WIP
#endif

  //////////////////////////////////////////////////////////////////////////
  // Numerical limits

#define TL_NUM_CHAR_BITS          CHAR_BIT
#define TL_SCHAR_MIN              SCHAR_MIN
#define TL_SCHAR_MAX              SCHAR_MAX
#define TL_UCHAR_MIN              0
#define TL_UCHAR_MAX              UCHAR_MAX

#define TL_CHAR_MIN               CHAR_MIN
#define TL_CHAR_MAX               CHAR_MAX

#define TL_WCHAR_MAX_NUM_BYTES    MB_LEN_MAX
#define TL_SHORT_MIN              SHRT_MIN
#define TL_SHORT_MAX              SHRT_MAX
#define TL_USHORT_MIN             0
#define TL_USHORT_MAX             USHRT_MAX

#define TL_INT_MIN                INT_MIN
#define TL_INT_MAX                INT_MAX
#define TL_UINT_MIN               0
#define TL_UINT_MAX               UINT_MAX

#define TL_LONG_MIN               LONG_MIN
#define TL_LONG_MAX               LONG_MAX
#define TL_ULONG_MIN              0
#define TL_ULONG_MAX              ULONG_MAX

#define TL_LLONG_MIN              LLONG_MIN
#define TL_LLONG_MAX              LLONG_MAX
#define TL_ULLONG_MIN             0
#define TL_ULLONG_MAX             ULLONG_MAX

};

#endif
