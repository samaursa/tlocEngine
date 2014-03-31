#include "tlocVector3.h"
#include "tlocVector3.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector3<tloc::f32>;
  template class Vector3<tloc::f64>;

};};};

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f64);