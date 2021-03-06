#include "tlocTime.h"
#include "tlocTime.opt.inl.h"

namespace tloc { namespace core { namespace time {

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Timer_T<>;
  template class Timer_T<f64, u64, p_timer_t::NoAdjust>;

  template class Timer_T<f32, u32, p_timer_t::Adjust>;
  template class Timer_T<f32, u32, p_timer_t::NoAdjust>;

  // -----------------------------------------------------------------------
  // global functions

  Timer g_programTime;

  const Timer&
    GetProgramTime()
  { return g_programTime; }

};};};