#ifndef TLOC_MATH_VECTOR_4_OPT_INL
#define TLOC_MATH_VECTOR_4_OPT_INL

#ifndef TLOC_MATH_VECTOR_4_H
#error "Must include header before including the inline file"
#endif

#include "tlocVector4.h"
#include <tlocMath/types/tlocVector.opt.inl.h>

namespace tloc { namespace math { namespace types {

#define VECTOR_4_TEMP     typename T
#define VECTOR_4_PARAMS   T, 4
#define VECTOR_4_TYPE     typename Vector_T<VECTOR_4_PARAMS>

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T()
    : base_type()
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(const base_type& a_other)
    : base_type(a_other)
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(const this_type& a_other)
    : base_type(a_other)
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(value_type a_x, value_type a_y, value_type a_z, value_type a_w)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_x, a_y, a_z, a_w))
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(value_type a_x, vec3_type a_yzw)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_x, a_yzw[0], a_yzw[1], a_yzw[2]))
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(vec3_type a_xyz, value_type a_w)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_xyz[0], a_xyz[1], a_xyz[2], a_w))
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(vec2_type a_xy, vec2_type a_zw)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_xy[0], a_xy[1], a_zw[0], a_zw[1]))
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(vec2_type a_xy, value_type a_z, value_type a_w)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_xy[0], a_xy[1], a_z, a_w) )
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(value_type a_x, value_type a_y, vec2_type a_zw)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_x, a_y, a_zw[0], a_zw[1]) )
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(value_type a_x, vec2_type a_yz, value_type a_z)
    : base_type(core::data_structs::Variadic<value_type, 4>(a_x, a_yz[0], a_yz[1], a_z) )
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::
    Vector_T(const core::data_structs::Variadic<T, 4>& a_vars)
    : base_type(a_vars)
  { }

  template <VECTOR_4_TEMP>
  Vector_T<VECTOR_4_PARAMS>::Vector_T(const_reference a_value)
    : base_type(a_value)
  { }

};};};

#endif