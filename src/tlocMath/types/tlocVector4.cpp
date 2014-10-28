#include "tlocVector4.h"
#include "tlocVector4.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector_T<tloc::f32, 4>;
  template class Vector_T<tloc::f64, 4>;
  template class Vector_T<tloc::f128, 4>;

};};};

using namespace tloc;
using namespace math_t;
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f32, 4,  Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 4, Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 4,  Vec4f64);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f64, 4, Vec4f64);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f128, 4, Vec4f128);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f128, 4, Vec4f128);

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f64);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f128);