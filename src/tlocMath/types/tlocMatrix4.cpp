#include "tlocMatrix4.h"
#include "tlocMatrix4.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 4>;
  template class Matrix_T<tloc::f64, 4>;

};};};

using namespace tloc;
using namespace math_t;
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 4,  Mat4f32);
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 4,  Mat4f64);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Mat4f32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Mat4f64);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mat4f32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mat4f64);