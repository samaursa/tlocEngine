#include "tlocVector3.h"
#include "tlocVector3.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector_T<tloc::f32, 3>;
  template class Vector_T<tloc::f64, 3>;

};};};

using namespace tloc;
using namespace math_t;

TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 3, Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f64, 3, Vec3f64);

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec3f64);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Vec3f64);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Vec3f64);