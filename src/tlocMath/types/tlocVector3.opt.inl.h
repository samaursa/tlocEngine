#ifndef TLOC_VECTOR_3_OPT_INL
#define TLOC_VECTOR_3_OPT_INL

#ifndef TLOC_VECTOR_3_H
#error "Must include header before including the inline file"
#endif

#include "tlocVector3.h"
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocMath/tlocMath.inl.h>
#include <tlocMath/types/tlocVector.opt.inl.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector3

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_3_TYPES typename T
#define VECTOR_3_PARAMS T, 3

  //------------------------------------------------------------------------
  // Constructors

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T()
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(value_type aValue)
    : base_type(aValue)
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(value_type a_x, value_type a_y, value_type a_z)
    : base_type(core::data_structs::Variadic<value_type, 3>(a_x, a_y, a_z) )
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(vec2_type a_xy, value_type a_z)
    : base_type(core::data_structs::Variadic<value_type, 3>(a_xy[0], a_xy[1], a_z) )
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(value_type aX, vec2_type a_yz)
    : base_type(core::data_structs::Variadic<value_type, 3>(aX, a_yz[0], a_yz[1]) )
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(const this_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(const base_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_3_TYPES>
  Vector_T<VECTOR_3_PARAMS>::
    Vector_T(const core::data_structs::Variadic<value_type,3> &a_vars)
    : base_type(a_vars)
  { }

  //------------------------------------------------------------------------
  // Math operations

  template <VECTOR_3_TYPES>
  typename Vector_T<VECTOR_3_PARAMS>::this_type
    Vector_T<VECTOR_3_PARAMS>::
    Cross(const this_type& aVector) const
  {
    /*
    y * rkVector.z - z * rkVector.y,
    z * rkVector.x - x * rkVector.z,
    x * rkVector.y - y * rkVector.x);
    */

    this_type temp;

    temp.m_values[0] = this->m_values[1] * aVector[2] -
                       this->m_values[2] * aVector[1];
    temp.m_values[1] = this->m_values[2] * aVector[0] -
                       this->m_values[0] * aVector[2];
    temp.m_values[2] = this->m_values[0] * aVector[1] -
                       this->m_values[1] * aVector[0];

    return temp;
  }

  template <VECTOR_3_TYPES>
  void Vector_T<VECTOR_3_PARAMS>::
    Cross(const this_type& aVector1, const this_type& aVector2)
  {
    *this = aVector1.Cross(aVector2);
  }

};};};

#endif