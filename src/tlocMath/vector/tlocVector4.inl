#ifndef TLOC_MATH_VECTOR_4_INL
#define TLOC_MATH_VECTOR_4_INL

#ifndef TLOC_MATH_VECTOR_4_H
#error "Must include header before including the inline file"
#endif

#include "tlocVector4.h"

namespace tloc { namespace math {

#define VECTOR_4_TEMP     typename T
#define VECTOR_4_PARAMS   T
#define VECTOR_4_TYPE     typename Vector4<VECTOR_4_PARAMS>

  template <VECTOR_4_TEMP>
  Vector4<VECTOR_4_PARAMS>::Vector4()
    : base_type()
  { } 

  template <VECTOR_4_TEMP>
  Vector4<VECTOR_4_PARAMS>::Vector4(const this_type& a_other)
    : base_type(a_other)
  { } 

  template <VECTOR_4_TEMP>
  Vector4<VECTOR_4_PARAMS>::Vector4(value_type a_x, value_type a_y, 
                                    value_type a_z, value_type a_w)
                                    : base_type
  {
  }

};};