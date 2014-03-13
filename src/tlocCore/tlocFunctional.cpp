#include "tlocFunctional.h"

namespace tloc { namespace core {

  // ///////////////////////////////////////////////////////////////////////
  // hash

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<bool>::operator()(bool a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<char8>::operator()(char8 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<char32>::operator()(char32 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<uchar8>::operator()(uchar8 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<s16>::operator()(s16 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<s32>::operator()(s32 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<s64>::operator()(s64 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<u16>::operator()(u16 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<u32>::operator()(u32 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<u64>::operator()(u64 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<f32>::operator()(f32 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<f64>::operator()(f64 a_value) const
  { return static_cast<tl_size>(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tl_size
    hash<f128>::operator()(f128 a_value) const
  { return static_cast<tl_size>(a_value); }

};};