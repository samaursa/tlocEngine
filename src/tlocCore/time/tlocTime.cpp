#include "tlocTime.h"
#include "tlocTime.inl"

namespace tloc { namespace core {

  template Timer<>;
  template Timer<f128>;
  template Timer<f64, u64, false>;
  template Timer<f128, u64, false>;

  template Timer<f32, u32, true>;
  template Timer<f32, u32, false>;

};};