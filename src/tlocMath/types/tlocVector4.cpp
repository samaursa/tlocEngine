#include "tlocVector4.h"
#include "tlocVector4.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector_T<tloc::f32, 4>;
  template class Vector_T<tloc::f64, 4>;

};};};

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f64);