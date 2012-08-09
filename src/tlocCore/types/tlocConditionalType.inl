#ifndef TLOC_CONDITIONAL_TYPE_INL
#define TLOC_CONDITIONAL_TYPE_INL

#ifndef TLOC_CONDITIONAL_TYPE_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {

//------------------------------------------------------------------------
  // ConditionalType<T, false>

#define COND_TYPE_FALSE_TEMPS typename T
#define COND_TYPE_FALSE_PARAMS T, false 

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>::ConditionalType() {}

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>::ConditionalType(const T& aValue)
  {
    TLOC_UNUSED(aValue);
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator= (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator+ (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator+ (const T& aOther) const
  {
    return aOther;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator- (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator- (const T& aOther) const
  {
    return aOther;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator* (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator* (const T& aOther) const
  {
    return aOther;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator/ (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator/ (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return 0;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator+= (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator+= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator-= (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator-= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator*= (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator*= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::
    operator/= (const ConditionalType<COND_TYPE_FALSE_PARAMS>& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator/= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator++()
  {
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator++(int)
  {
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator--()
  {
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI ConditionalType<COND_TYPE_FALSE_PARAMS>
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator--(int)
  {
    return *this;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator==(const this_type& aOther) 
    const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator==(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator!=(const this_type& aOther) 
    const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator!=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator< (const this_type& aOther) 
    const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator< (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator<=(const this_type& aOther) 
    const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator<=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator>=(const this_type& aOther) 
    const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator>=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool
    ConditionalType<COND_TYPE_FALSE_PARAMS>::operator> (const this_type& aOther) 
    const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool ConditionalType<COND_TYPE_FALSE_PARAMS>:: operator> 
    (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI const T&
    ConditionalType<COND_TYPE_FALSE_PARAMS>::Get() const
  {
    return g_conditional_type_invalid_value;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI T ConditionalType<COND_TYPE_FALSE_PARAMS>::Value() const
  {
    return g_conditional_type_invalid_value;
  }

  template <COND_TYPE_FALSE_TEMPS>
  TL_FI bool ConditionalType<COND_TYPE_FALSE_PARAMS>::IsValid() const
  {
    return false;
  }

  //------------------------------------------------------------------------
  // ConditionalType<T, true>

#define COND_TYPE_TRUE_TEMPS typename T
#define COND_TYPE_TRUE_PARAMS T, true

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>::ConditionalType() {}

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>::ConditionalType(const T& aValue)
    : m_value(aValue) {}

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator= (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther)
  {
    m_value = aOther.Value();
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator= (const T& aOther)
  {
    m_value = aOther;
    return *this;
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator+ (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther) const
  {
    return Value() + aOther.Value();
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::operator+ (const T& aOther) 
    const
  {
    return Value() + aOther;
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator- (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther) const
  {
    return Value() - aOther.Value();
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::operator- (const T& aOther) 
    const
  {
    return Value() - aOther;
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator* (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther) const
  {
    return Value() * aOther.Value();
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::operator* (const T& aOther) 
    const
  {
    return Value() * aOther;
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator/ (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther) const
  {
    return Value() / aOther.Value();
  }

  template <typename T>
  TL_FI T ConditionalType<COND_TYPE_TRUE_PARAMS>::operator/ (const T& aOther) 
    const
  {
    return Value() / aOther;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator+= 
    (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther)
  {
    m_value += aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator+= (const T& aOther)
  {
    m_value += aOther;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator-= (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther)
  {
    m_value -= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator-= (const T& aOther)
  {
    m_value -= aOther;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator*= (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther)
  {
    m_value *= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator*= (const T& aOther)
  {
    m_value *= aOther;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::
    operator/= (const ConditionalType<COND_TYPE_TRUE_PARAMS>& aOther)
  {
    m_value /= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator/= (const T& aOther)
  {
    m_value /= aOther;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator++()
  {
    ++m_value;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator++(int)
  {
    ConditionalType<COND_TYPE_TRUE_PARAMS> temp(m_value);
    ++m_value;
    return temp;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator--()
  {
    --m_value;
    return *this;
  }

  template <typename T>
  TL_FI ConditionalType<COND_TYPE_TRUE_PARAMS>
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator--(int)
  {
    ConditionalType<COND_TYPE_TRUE_PARAMS> temp(m_value);
    --m_value;
    return temp;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator==(const this_type& aOther) 
    const
  {
    return m_value == aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator==(const T& aOther) const
  {
    return m_value == aOther;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator!=(const this_type& aOther) 
    const
  {
    return m_value != aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator!=(const T& aOther) const
  {
    return m_value != aOther;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator< (const this_type& aOther) 
    const
  {
    return m_value < aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator< (const T& aOther) const
  {
    return m_value < aOther;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator<=(const this_type& aOther) 
    const
  {
    return m_value <= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator<=(const T& aOther) const
  {
    return m_value <= aOther;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator>=(const this_type& aOther) 
    const
  {
    return m_value >= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator>=(const T& aOther) const
  {
    return m_value >= aOther;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator> (const this_type& aOther) 
    const
  {
    return m_value > aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    ConditionalType<COND_TYPE_TRUE_PARAMS>::operator> (const T& aOther) const
  {
    return m_value > aOther;
  }

  template <typename T>
  TL_FI const T&
    ConditionalType<COND_TYPE_TRUE_PARAMS>::Get() const
  {
    return m_value;
  }

  template <typename T>
  TL_FI T
    ConditionalType<COND_TYPE_TRUE_PARAMS>::Value() const
  {
    return m_value;
  }

  template <typename T>
  TL_FI bool ConditionalType<COND_TYPE_TRUE_PARAMS>::IsValid() const
  {
    return true;
  }

#define COND_TYPE_PKG_TYPES   typename T_User, typename T, bool T_DeclareValue
#define COND_TYPE_PKG_PARAMS  T_User, T, T_DeclareValue 

  template <COND_TYPE_PKG_TYPES>
  ConditionalTypePackage<COND_TYPE_PKG_PARAMS>::ConditionalTypePackage()
    : cond_type() {}

  template <COND_TYPE_PKG_TYPES>
  ConditionalTypePackage<COND_TYPE_PKG_PARAMS>::
    ConditionalTypePackage(const T_User& aUserValue, const T& aValue) 
    : cond_type(aValue), m_var(aUserValue) {}

};};

#endif