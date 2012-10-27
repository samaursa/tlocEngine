#ifndef _TLOC_CORE_TYPES_STRONG_TYPE_INL_H_
#define _TLOC_CORE_TYPES_STRONG_TYPE_INL_H_

#ifndef _TLOC_CORE_TYPES_STRONG_TYPE_H_
#error "Must include header before including the inline file"
#endif

#include "tlocStrongType.h"
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace types {

#define STRONG_TYPE_TEMP    typename T, tl_size T_UniqueCounter
#define STRONG_TYPE_PARAMS  T, T_UniqueCounter
#define STRONG_TYPE_TYPE    typename StrongType_T<STRONG_TYPE_PARAMS>

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::StrongType_T(const T a_value)
    : m_value(a_value)
  { }

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::StrongType_T(const this_type& a_other)
    : m_value(a_other.m_value)
  { }

  template <STRONG_TYPE_TEMP>
  STRONG_TYPE_TYPE::this_type& 
    StrongType_T<STRONG_TYPE_PARAMS>::operator= (const this_type& a_other)
  { 
    m_value = a_other.m_value; 
    return *this; 
  }

  template <STRONG_TYPE_TEMP>
  STRONG_TYPE_TYPE::this_type& 
    StrongType_T<STRONG_TYPE_PARAMS>::operator= (value_type a_other)
  { 
    m_value = a_other; 
    return *this; 
  }

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::operator value_type& ()
  {
    return m_value;
  }

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::operator value_type const& () const
  {
    return m_value;
  }

  template <STRONG_TYPE_TEMP>
  bool StrongType_T<STRONG_TYPE_PARAMS>::
    operator== (const this_type& a_other) const
  { 
    return m_value == a_other.m_value; 
  }

  template <STRONG_TYPE_TEMP>
  bool StrongType_T<STRONG_TYPE_PARAMS>::
    operator< (const this_type& a_other) const
  { 
    return m_value == a_other.m_value; 
  }

};};};

#endif