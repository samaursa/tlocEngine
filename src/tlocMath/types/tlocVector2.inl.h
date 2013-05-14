#ifndef TLOC_VECTOR_2_INL
#define TLOC_VECTOR_2_INL

#ifndef TLOC_VECTOR_2_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocMath/tlocMath.inl>
#include <tlocMath/types/tlocVector.inl>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector2

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_2_TYPES typename T
#define VECTOR_2_PARAMS T

  template <VECTOR_2_TYPES>
  Vector2<VECTOR_2_PARAMS>::
    Vector2()
    : base_type()
  { }

  template <VECTOR_2_TYPES>
  Vector2<VECTOR_2_PARAMS>::
    Vector2(const_reference aValue)
    : base_type(aValue)
  { }

  template <VECTOR_2_TYPES>
  Vector2<VECTOR_2_PARAMS>::
    Vector2(const_reference aX, const_reference aY)
    : base_type(core::data_structs::Variadic<value_type, 2>(aX, aY))
  { }

  template <VECTOR_2_TYPES>
  Vector2<VECTOR_2_PARAMS>::
    Vector2(const this_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_2_TYPES>
  Vector2<VECTOR_2_PARAMS>::
    Vector2(const base_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_2_TYPES>
  Vector2<VECTOR_2_PARAMS>::
    Vector2(const core::data_structs::Variadic<value_type, 2>& a_vars)
    : base_type(a_vars)
  { }

};};};

#endif