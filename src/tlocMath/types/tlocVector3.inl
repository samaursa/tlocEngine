#ifndef TLOC_VECTOR_3_INL
#define TLOC_VECTOR_3_INL

#ifndef TLOC_VECTOR_3_H
#error "Must include header before including the inline file"
#endif

#include "tlocVector3.h"
#include <tlocCore/tlocAlgorithms.inl>
#include <tlocMath/tlocMath.inl>
#include <tlocMath/types/tlocVector.inl>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector3

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_3_TYPES typename T
#define VECTOR_3_PARAMS T

  //------------------------------------------------------------------------
  // Constructors

  template <VECTOR_3_TYPES>
  Vector3<VECTOR_3_PARAMS>::
    Vector3()
  { }

  template <VECTOR_3_TYPES>
  Vector3<VECTOR_3_PARAMS>::
    Vector3(const_reference aValue)
    : base_type(aValue)
  { }

  template <VECTOR_3_TYPES>
  Vector3<VECTOR_3_PARAMS>::
    Vector3(const_reference aX, const_reference aY, const_reference aZ) 
    : base_type(core::data_structs::Variadic<value_type, 3>(aX, aY, aZ) )
  { }

  template <VECTOR_3_TYPES>
  Vector3<VECTOR_3_PARAMS>::
    Vector3(const this_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_3_TYPES>
  Vector3<VECTOR_3_PARAMS>::
    Vector3(const base_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_3_TYPES>
  Vector3<VECTOR_3_PARAMS>::
    Vector3(const core::data_structs::Variadic<value_type,3> &a_vars)
    : base_type(a_vars)
  { }

  //------------------------------------------------------------------------
  // Math operations

  template <VECTOR_3_TYPES>
  typename Vector3<VECTOR_3_PARAMS>::this_type& 
    Vector3<VECTOR_3_PARAMS>::
    Cross(const this_type& aVector)
  {
    /*
    y * rkVector.z - z * rkVector.y,
    z * rkVector.x - x * rkVector.z,
    x * rkVector.y - y * rkVector.x);
    */

    this_type temp(*this);

    m_values[0] = temp[1] * aVector[2] - temp[2] * aVector[1];
    m_values[1] = temp[2] * aVector[0] - temp[0] * aVector[2];
    m_values[2] = temp[0] * aVector[1] - temp[1] * aVector[0];

    return *this;
  }

  template <VECTOR_3_TYPES>
  void Vector3<VECTOR_3_PARAMS>::
    Cross(const this_type& aVector1, const this_type& aVector2)
  {
    *this = aVector1;
    Cross(aVector2);
  }

};};};

#endif