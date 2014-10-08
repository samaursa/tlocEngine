#include "tlocMatrix4.h"
#include "tlocMatrix4.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 4>;
  template class Matrix_T<tloc::f64, 4>;
  template class Matrix_T<tloc::f128, 4>;

};};};