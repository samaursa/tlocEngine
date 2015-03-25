#include "tlocVector2.h"
#include "tlocVector2.opt.inl.h"

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations

  template class Vector_T<tloc::f32, 2>;
  template class Vector_T<tloc::f64, 2>;

};};};

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec2f64);

using namespace tloc;
using namespace math_t;

TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 2, Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f64, 2, Vec2f64);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Vec2f64);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Vec2f64);