#include "tlocVector3.h"
#include "tlocVector3.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector_T<tloc::f32, 3>;
  template class Vector_T<tloc::f64, 3>;
  template class Vector_T<tloc::f128, 3>;

};};};

using namespace tloc;
using namespace math_t;

TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 3, Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f64, 3, Vec3f64);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f128, 3, Vec3f128);

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f64);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f128);