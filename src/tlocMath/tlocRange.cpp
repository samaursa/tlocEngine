#include "tlocRange.h"
#include "tlocRange.inl.h"

namespace tloc { namespace math {

#define TLOC_EXPLICITLY_INSTANTIATE_RANGE(_type_)\
  template class Range_T<_type_>

  //------------------------------------------------------------------------
  // explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_RANGE(s8);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(u8);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(s16);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(u16);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(s32);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(u32);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(s64);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(u64);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(f32);
  TLOC_EXPLICITLY_INSTANTIATE_RANGE(f64);

};};