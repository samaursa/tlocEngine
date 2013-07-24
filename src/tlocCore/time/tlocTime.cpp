#include "tlocTime.h"
#include "tlocTime.inl.h"

namespace tloc { namespace core { namespace time {

  template class Timer_T<>;
  template class Timer_T<f128>;
  template class Timer_T<f64, u64, p_timer_t::NoAdjust>;
  template class Timer_T<f128, u64, p_timer_t::NoAdjust>;

  template class Timer_T<f32, u32, p_timer_t::Adjust>;
  template class Timer_T<f32, u32, p_timer_t::NoAdjust>;

};};};