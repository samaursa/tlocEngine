#include "tlocAngle.h"
#include "tlocAngle.inl"

namespace tloc { namespace math { namespace types {

  template class Radian_T<f32>;
  template class Radian_T<f64>;

  template class Degree_T<f32>;
  template class Degree_T<f64>;

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

#include "tlocAngleExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f32, Radian_T, Degree_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f64, Radian_T, Degree_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f32, Degree_T, Radian_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f64, Degree_T, Radian_T);

};};};