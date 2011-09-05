#pragma once
#ifndef TLOC_TYPES_H
#define TLOC_TYPES_H

#include <wctype.h>
#include <limits>
#include <limits.h>

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Basic types

  typedef char              char8;
  typedef wchar_t           char32;

  typedef __int8            s8;
  typedef __int16           s16;
  typedef __int32           s32;
  typedef __int64           s64;
  typedef float             f32;
  typedef double            f64;
  typedef long double       f128;

  typedef unsigned char     uchar8;
  typedef unsigned __int8   u8;
  typedef unsigned __int16  u16;
  typedef unsigned __int32  u32;
  typedef unsigned __int64  u64;

  typedef size_t            tl_size;

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
#define TL_UINT_MAX               0

#define TL_LONG_MIN               LONG_MIN
#define TL_LONG_MAX               LONG_MAX
#define TL_ULONG_MIN              0
#define TL_ULONG_MAX              ULONG_MAX

#define TL_LLONG_MIN              LLONG_MIN
#define TL_LLONG_MAX              LLONG_MAX
#define TL_ULLONG_MIN             0
#define TL_ULLONG_MAX             ULLONG_MAX

  //////////////////////////////////////////////////////////////////////////
  // Containers

  /*template <typename T>
  class FwVecArray : public std::vector<T> {};

  template <typename T, typename _Ty,
    typename _Pr = less<_Kty>,
    typename _Alloc = allocator<pair<const _Kty, _Ty> >>
  class FwMap : public std::map<T, _Ty, _Pr, _Alloc> {};

  template <typename _Ty, typename _Ax = allocator<_Ty> >
  class FwList : public std::list<_Ty, _Ax> {};*/

  /*typedef FwVecArray<tl_uchar>     FwVecUChar;
  typedef FwVecArray<tl_uint32>    FwVecUInt;
  typedef FwVecArray<tl_ulong>     FwVecULong;
  typedef FwVecArray<tl_int32>     FwVecInt;
  typedef FwVecArray<tl_real32>    FwVecFloat;
  typedef FwVecArray<tl_real64>    FwVecDouble;*/
  /*typedef FwVecArray<std::string>  FwVecString;*/
};

#endif