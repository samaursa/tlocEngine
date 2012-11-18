#include "tlocTime.h"
#include "tlocTime.inl"

namespace tloc { namespace core {

  template class Timer_T<>;
  template class Timer_T<f128>;
  template class Timer_T<f64, u64, false>;
  template class Timer_T<f128, u64, false>;

  template class Timer_T<f32, u32, true>;
  template class Timer_T<f32, u32, false>;

};};