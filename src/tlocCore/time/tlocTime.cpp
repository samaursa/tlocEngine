#include "tlocTime.h"
#include "tlocTime.inl"

namespace tloc { namespace core {

  template class Timer<>;
  template class Timer<f128>;
  template class Timer<f64, u64, false>;
  template class Timer<f128, u64, false>;

  template class Timer<f32, u32, true>;
  template class Timer<f32, u32, false>;

};};