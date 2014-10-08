#include "tlocVector3.h"
#include "tlocVector3.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector_T<tloc::f32, 3>;
  template class Vector_T<tloc::f64, 3>;
  template class Vector_T<tloc::f128, 3>;

};};};

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f64);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f128);