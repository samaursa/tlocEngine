#include "tlocVector2.h"
#include "tlocVector2.inl.h"

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations

  template class Vector2<tloc::f32>;
  template class Vector2<tloc::f64>;
  template class Vector2<tloc::f128>;

};};};

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec2f64);