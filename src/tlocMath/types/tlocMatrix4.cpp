#include "tlocMatrix4.h"
#include "tlocMatrix4.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix4<tloc::f32>;
  template class Matrix4<tloc::f64>;
  template class Matrix4<tloc::f128>;

};};};