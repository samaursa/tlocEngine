#include "tlocVector4.h"
#include "tlocVector4.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector4<tloc::f32>;
  template class Vector4<tloc::f64>;
  template class Vector4<tloc::f128>;

};};};