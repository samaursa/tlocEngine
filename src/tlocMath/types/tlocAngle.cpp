#include "tlocAngle.h"
#include "tlocAngle.opt.inl.h"

namespace tloc { namespace math { namespace types {

  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f32, Radian_T, Degree_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f64, Radian_T, Degree_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f32, Degree_T, Radian_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f64, Degree_T, Radian_T);

};};};