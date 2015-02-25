#include "tlocMatrix2.h"
#include "tlocMatrix2.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 2>;
  template class Matrix_T<tloc::f64, 2>;

};};};

using namespace tloc;
using namespace math_t;
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 2,  Mat2f32);
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 2,  Mat2f64);