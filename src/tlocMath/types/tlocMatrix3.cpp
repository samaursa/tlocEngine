#include "tlocMatrix3.h"
#include "tlocMatrix3.opt.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix_T<tloc::f32, 3>;
  template class Matrix_T<tloc::f64, 3>;

};};};

using namespace tloc;
using namespace math_t;
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 3,  Mat3f32);
TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 3,  Mat3f64);

using namespace tloc;

#include <tlocCore/types/tlocStrongType.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f32 TLOC_COMMA 3>, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(math_t::Vector_T<f64 TLOC_COMMA 3>, 0);

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Mat3f32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Mat3f64);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mat3f32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mat3f64);