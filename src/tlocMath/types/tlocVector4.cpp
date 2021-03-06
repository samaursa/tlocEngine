#include "tlocVector4.h"
#include "tlocVector4.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Vector_T<tloc::f32, 4>;
  template class Vector_T<tloc::f64, 4>;

};};};

using namespace tloc;
using namespace math_t;

TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 4, Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f64, 4, Vec4f64);

using namespace tloc::math::types;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Vec4f64);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Vec4f64);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Vec4f64);