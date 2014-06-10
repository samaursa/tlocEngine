#include "tlocMatrix3.h"
#include "tlocMatrix3.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 3>;
  template class Matrix_T<tloc::f64, 3>;
  template class Matrix_T<tloc::f128, 3>;

};};};