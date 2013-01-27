#include "tlocVector3.h"
#include "tlocVector3.inl"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector3<tloc::f32>;
  template class Vector3<tloc::f64>;
  template class Vector3<tloc::f128>;

};};};