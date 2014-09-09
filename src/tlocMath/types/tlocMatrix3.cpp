#include "tlocMatrix3.h"
#include "tlocMatrix3.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 3>;
  template class Matrix_T<tloc::f64, 3>;
  template class Matrix_T<tloc::f128, 3>;

};};};

using namespace tloc;

#include <tlocCore/types/tlocStrongType.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f32 TLOC_COMMA 3>, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f64 TLOC_COMMA 3>, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f128 TLOC_COMMA 3>, 0);