#ifndef TLOC_VECTOR_2_INL
#define TLOC_VECTOR_2_INL

#ifndef TLOC_VECTOR_2_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl>
#include <tlocMath/tlocMath.inl>
#include <tlocMath/vector/tlocVector.inl>

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Vector2

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_2_TYPES typename T
#define VECTOR_2_PARAMS T

  template <VECTOR_2_TYPES>
  TL_FI Vector2<VECTOR_2_PARAMS>::Vector2()
  {
  }

  template <VECTOR_2_TYPES>
  TL_FI Vector2<VECTOR_2_PARAMS>::Vector2(const_reference aValue)
  {
    m_values[0] = aValue;
    m_values[1] = aValue;
  }

  template <VECTOR_2_TYPES>
  TL_FI Vector2<VECTOR_2_PARAMS>::Vector2(const_reference aX, const_reference aY)
  {
    m_values[0] = aX;
    m_values[1] = aY;
  }

  template <VECTOR_2_TYPES>
  TL_FI Vector2<VECTOR_2_PARAMS>::Vector2(const this_type& aVector)
  {
    m_values[0] = aVector[0];
    m_values[1] = aVector[1];
  }

  template <VECTOR_2_TYPES>
  TL_FI Vector2<VECTOR_2_PARAMS>::Vector2(const base_type& aVector)
  {
    m_values[0] = aVector[0];
    m_values[1] = aVector[1];
  }

};};

#endif