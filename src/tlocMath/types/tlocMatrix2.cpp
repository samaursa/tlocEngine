#include "tlocMatrix2.h"
#include "tlocMatrix2.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 2>;
  template class Matrix_T<tloc::f64, 2>;
  template class Matrix_T<tloc::f128, 2>;

};};};