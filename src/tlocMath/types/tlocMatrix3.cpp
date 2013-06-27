#include "tlocMatrix3.h"
#include "tlocMatrix3.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix3<tloc::f32>;
  template class Matrix3<tloc::f64>;
  template class Matrix3<tloc::f128>;

};};};