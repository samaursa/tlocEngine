#include "tlocMatrix3.h"
#include "tlocMatrix3.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 3>;
  template class Matrix_T<tloc::f64, 3>;
  template class Matrix_T<tloc::f128, 3>;

};};};

using namespace tloc;
using namespace math_t;
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 3,  Mat3f32);
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 3,  Mat3f64);
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f128, 3, Mat3f128);

using namespace tloc;

#include <tlocCore/types/tlocStrongType.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f32 TLOC_COMMA 3>, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f64 TLOC_COMMA 3>, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f128 TLOC_COMMA 3>, 0);