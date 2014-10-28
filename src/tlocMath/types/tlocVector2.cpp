#include "tlocVector2.h"
#include "tlocVector2.opt.inl.h"

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations

  template class Vector_T<tloc::f32, 2>;
  template class Vector_T<tloc::f64, 2>;
  template class Vector_T<tloc::f128, 2>;

};};};

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec2f64);

using namespace tloc;
using namespace math_t;
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f32, 2,  Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 2, Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 2,  Vec2f64);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f64, 2, Vec2f64);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f128, 2, Vec2f128);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f128, 2, Vec2f128);
