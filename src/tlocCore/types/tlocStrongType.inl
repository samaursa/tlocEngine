#ifndef _TLOC_CORE_TYPES_STRONG_TYPE_INL_
#define _TLOC_CORE_TYPES_STRONG_TYPE_INL_

#ifndef _TLOC_CORE_TYPES_STRONG_TYPE_H_
#error "Must include header before including the inline file"
#endif

#include "tlocStrongType.h"
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

namespace tloc { namespace core { namespace types {

#define STRONG_TYPE_TEMP    typename T, tl_size T_UniqueCounter, typename T_Ptr, typename T_Ref
#define STRONG_TYPE_PARAMS  T, T_UniqueCounter, T_Ptr, T_Ref
#define STRONG_TYPE_TYPE    typename StrongType_T<STRONG_TYPE_PARAMS>

  namespace 
  {
    typedef type_true   simple_type;
    typedef type_false  complex_type;

    template <typename T_ReturnType, typename T_TypeIn>
    T_ReturnType DoGetValue(T_TypeIn a_type, simple_type)
    {
      return a_type;
    }

    template <typename T_ReturnType, typename T_TypeIn>
    T_ReturnType DoGetValue(T_TypeIn a_type, complex_type)
    {
      return *a_type;
    }

    template <typename T_TypeIn, typename T_ValueType>
    void DoSetValue(T_TypeIn a_type, T_ValueType& a_value, simple_type)
    {
      a_value = a_type;
    }

    template <typename T_TypeIn, typename T_ValueType>
    void DoSetValue(T_TypeIn a_type, T_ValueType& a_value, complex_type)
    {
      a_value = &(a_type);
    }
  };

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::
    StrongType_T(const_sel_val_type_ref a_value)
  { 
    typedef Loki::Int2Type<Loki::TypeTraits<T>::isFundamental> v_type;

    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T&, T const *>::Result                    out_type;

    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T, const_pointer>::Result                    argument_type;

    DoSetValue<const_sel_val_type_ref, 
               const_sel_val_type_ptr>(a_value, m_value, v_type());
  }

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::StrongType_T(this_type const & a_other)
    : m_value(a_other.m_value)
  { }

  template <STRONG_TYPE_TEMP>
  STRONG_TYPE_TYPE::this_type& 
    StrongType_T<STRONG_TYPE_PARAMS>::operator= (this_type const & a_other)
  { 
    m_value = a_other.m_value; 
    return *this; 
  }

  template <STRONG_TYPE_TEMP>
  STRONG_TYPE_TYPE::this_type& 
    StrongType_T<STRONG_TYPE_PARAMS>::operator= 
    (const_sel_val_type_ptr a_other)
  { 
    //TemplateDiagnose<const_selected_value_type> a;
    m_value = a_other; 
    return *this; 
  }

  template <STRONG_TYPE_TEMP>
  StrongType_T<STRONG_TYPE_PARAMS>::operator 
    STRONG_TYPE_TYPE::const_sel_return_type () const
  {
    typedef Loki::Int2Type<Loki::TypeTraits<T>::isFundamental> v_type;

    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T, const_reference>::Result                    return_type;

    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T, const_pointer>::Result                    argument_type;

    return DoGetValue<return_type, argument_type>(m_value, v_type());
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