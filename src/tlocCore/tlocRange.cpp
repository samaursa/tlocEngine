#include "tlocRange.h"
#include "tlocRange.inl"

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // explicit instantiations

  template class Range_T<s8>;
  template class Range_T<u8>;
  template class Range_T<s16>;
  template class Range_T<u16>;
  template class Range_T<s32>;
  template class Range_T<s32>;
  template class Range_T<s64>;
  template class Range_T<u32>;
  template class Range_T<u64>;
  template class Range_T<f32>;
  template class Range_T<f64>;

};};