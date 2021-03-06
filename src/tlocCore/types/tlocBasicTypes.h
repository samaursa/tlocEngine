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
#define TLOC_U_INT_PTR_TYPE size_t
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

  typedef unsigned char     uchar8;
  typedef TLOC_U_INT8_TYPE   u8;
  typedef TLOC_U_INT16_TYPE  u16;
  typedef TLOC_U_INT32_TYPE  u32;
  typedef TLOC_U_INT64_TYPE  u64;

  typedef long                 tloc_long;
  typedef unsigned long        tloc_ulong;
  typedef TLOC_SIZE_TYPE       tloc_size;
  typedef TLOC_U_INT_PTR_TYPE  tloc_uintptr; // Guaranteed to hold a native pointer
  typedef TLOC_PTR_DIFF_TYPE   tloc_ptrdiff;

  //------------------------------------------------------------------------
  // The following types are useful when you want the best type size depending
  // on the platform itself

#if defined(_WIN64) || defined(__LP64__)
  typedef int               tloc_int;
  typedef unsigned int      tloc_uint;
  typedef float             tloc_float;
  typedef double            tloc_double;
#elif defined(WIN32) || defined(_WIN32) || ( defined(__APPLE__) && !defined(__LP64__) )
  typedef int               tloc_int;
  typedef unsigned int      tloc_uint;
  typedef float             tloc_float;
  typedef double            tloc_double;
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

  // ///////////////////////////////////////////////////////////////////////
  // NumericLimits_T

  template <typename T>
  class NumericLimits_T
  {
  public:
    typedef T                             value_type;

  public:
    static  value_type        min();
    static  value_type        max();
    static  value_type        epsilon();
  };

};

typedef tloc::char8         tl_char8;
typedef tloc::char32        tl_char32;

typedef unsigned short      tl_ushort;

typedef tloc::s8            tl_s8;
typedef tloc::s16           tl_s16;
typedef tloc::s32           tl_s32;
typedef tloc::s64           tl_s64;
typedef tloc::f32           tl_f32;
typedef tloc::f64           tl_f64;

typedef tloc::uchar8        tl_uchar8;
typedef tloc::u8            tl_u8;
typedef tloc::u16           tl_u16;
typedef tloc::u32           tl_u32;
typedef tloc::u64           tl_u64;

typedef tloc::tloc_long     tl_long;
typedef tloc::tloc_ulong    tl_ulong;
typedef tloc::tloc_size     tl_size;
typedef tloc::tloc_uintptr  tl_uintptr;
typedef tloc::tloc_ptrdiff  tl_ptrdiff;

typedef tloc::tloc_int      tl_int;
typedef tloc::tloc_uint     tl_uint;
typedef tloc::tloc_float    tl_float;
typedef tloc::tloc_double   tl_double;

#endif