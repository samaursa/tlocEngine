#include "tlocMatrix2.h"
#include "tlocMatrix2.inl.h"

namespace tloc { namespace math { namespace types {

  //------------------------------------------------------------------------
  // Explicit template instantiations
  template class Matrix2<tloc::f32>;
  template class Matrix2<tloc::f64>;
  template class Matrix2<tloc::f128>;

};};};