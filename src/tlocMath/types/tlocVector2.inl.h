#ifndef TLOC_VECTOR_2_INL
#define TLOC_VECTOR_2_INL

#ifndef TLOC_VECTOR_2_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocMath/tlocMath.inl.h>
#include <tlocMath/types/tlocVector.inl.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  //Vector_T 

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_2_TYPES typename T
#define VECTOR_2_PARAMS T, 2

  template <VECTOR_2_TYPES>
  Vector_T<VECTOR_2_PARAMS>::
    Vector_T()
    : base_type()
  { }

  template <VECTOR_2_TYPES>
  Vector_T<VECTOR_2_PARAMS>::
    Vector_T(const_reference aValue)
    : base_type(aValue)
  { }

  template <VECTOR_2_TYPES>
  Vector_T<VECTOR_2_PARAMS>::
    Vector_T(const_reference aX, const_reference aY)
    : base_type(core::data_structs::Variadic<value_type, 2>(aX, aY))
  { }

  template <VECTOR_2_TYPES>
  Vector_T<VECTOR_2_PARAMS>::
    Vector_T(const this_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_2_TYPES>
  Vector_T<VECTOR_2_PARAMS>::
    Vector_T(const base_type& aVector)
    : base_type(aVector)
  { }

  template <VECTOR_2_TYPES>
  Vector_T<VECTOR_2_PARAMS>::
    Vector_T(const core::data_structs::Variadic<value_type, 2>& a_vars)
    : base_type(a_vars)
  { }

};};};

#endif