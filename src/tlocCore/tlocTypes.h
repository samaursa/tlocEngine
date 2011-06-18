#pragma once
#ifndef TLOC_TYPES_H
#define TLOC_TYPES_H

//#include <vector>
//#include <map>
//#include <list>
//#include <string>

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Basic types

  typedef short           s16;
  typedef int             s32;
  typedef long            s64;
  typedef float           f32;
  typedef double          f64;
  typedef long double     f128;

  typedef unsigned char   uchar;
  typedef unsigned short  u16;
  typedef unsigned int    u32;
  typedef unsigned long   u64;

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