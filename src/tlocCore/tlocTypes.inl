#ifndef TLOC_TYPES_INL
#define TLOC_TYPES_INL

#ifndef TLOC_TYPES_H
#error "Must include header before including the inline file"
#endif

namespace tloc
{
#define COND_TYPE_TEMP_FALSE ConditionalType<T, T_DeclareValue>

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE::ConditionalType() {}

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE::ConditionalType(const T& aValue)
  {
    TLOC_UNUSED(aValue);
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator+ (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator+ (const T& aOther) const
  {
    return aOther;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator- (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator- (const T& aOther) const
  {
    return aOther;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator* (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator* (const T& aOther) const
  {
    return aOther;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator/ (const COND_TYPE_TEMP_FALSE& aOther) const
  {
    TLOC_UNUSED(aOther);
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::operator/ (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return 0;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator+= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator+= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator-= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator-= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator*= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator*= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator/= (const COND_TYPE_TEMP_FALSE& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator/= (const T& aOther)
  {
    TLOC_UNUSED(aOther);
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator++()
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE
    COND_TYPE_TEMP_FALSE::operator++(int)
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE&
    COND_TYPE_TEMP_FALSE::operator--()
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI COND_TYPE_TEMP_FALSE
    COND_TYPE_TEMP_FALSE::operator--(int)
  {
    return *this;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator==(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator==(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator!=(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator!=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator< (const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator< (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator<=(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator<=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator>=(const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator>=(const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return true;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator> (const this_type& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI bool
    COND_TYPE_TEMP_FALSE::operator> (const T& aOther) const
  {
    TLOC_UNUSED(aOther);
    return false;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI const T&
    COND_TYPE_TEMP_FALSE::Get() const
  {
    return g_conditional_type_invalid_value;
  }

  template <typename T, bool T_DeclareValue>
  TL_FI T
    COND_TYPE_TEMP_FALSE::Value() const
  {
    return g_conditional_type_invalid_value;
  }

#define COND_TYPE_TEMP_TRUE ConditionalType<T, true>

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE::ConditionalType() {}

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE::ConditionalType(const T& aValue)
    : m_value(aValue) {}

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value = aOther.Value();
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator= (const T& aOther)
  {
    m_value = aOther;
    return *this;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator+ (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return Value() + aOther.Value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator+ (const T& aOther) const
  {
    return Value() + aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator- (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return Value() - aOther.Value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator- (const T& aOther) const
  {
    return Value() - aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator* (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return Value() * aOther.Value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator* (const T& aOther) const
  {
    return Value() * aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator/ (const COND_TYPE_TEMP_TRUE& aOther) const
  {
    return Value() / aOther.Value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::operator/ (const T& aOther) const
  {
    return Value() / aOther;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator+= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value += aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator+= (const T& aOther)
  {
    m_value += aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator-= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value -= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator-= (const T& aOther)
  {
    m_value -= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator*= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value *= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator*= (const T& aOther)
  {
    m_value *= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator/= (const COND_TYPE_TEMP_TRUE& aOther)
  {
    m_value /= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator/= (const T& aOther)
  {
    m_value /= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator++()
  {
    ++m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE
    COND_TYPE_TEMP_TRUE::operator++(int)
  {
    COND_TYPE_TEMP_TRUE temp(m_value);
    ++m_value;
    return temp;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE&
    COND_TYPE_TEMP_TRUE::operator--()
  {
    --m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP_TRUE
    COND_TYPE_TEMP_TRUE::operator--(int)
  {
    COND_TYPE_TEMP_TRUE temp(m_value);
    --m_value;
    return temp;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator==(const this_type& aOther) const
  {
    return m_value == aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator==(const T& aOther) const
  {
    return m_value == aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator!=(const this_type& aOther) const
  {
    return m_value != aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator!=(const T& aOther) const
  {
    return m_value != aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator< (const this_type& aOther) const
  {
    return m_value < aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator< (const T& aOther) const
  {
    return m_value < aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator<=(const this_type& aOther) const
  {
    return m_value <= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator<=(const T& aOther) const
  {
    return m_value <= aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator>=(const this_type& aOther) const
  {
    return m_value >= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator>=(const T& aOther) const
  {
    return m_value >= aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator> (const this_type& aOther) const
  {
    return m_value > aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP_TRUE::operator> (const T& aOther) const
  {
    return m_value > aOther;
  }

  template <typename T>
  TL_FI const T&
    COND_TYPE_TEMP_TRUE::Get() const
  {
    return m_value;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP_TRUE::Value() const
  {
    return m_value;
  }

#define COND_TYPE_PKG_TYPES   typename T_User, typename T, bool T_DeclareValue
#define COND_TYPE_PKG_PARAMS  T_User, T, T_DeclareValue 

  template <COND_TYPE_PKG_TYPES>
  ConditionalTypePackage<COND_TYPE_PKG_PARAMS>::ConditionalTypePackage()
    : cond_type() {}

  template <COND_TYPE_PKG_TYPES>
  ConditionalTypePackage<COND_TYPE_PKG_PARAMS>::ConditionalTypePackage(const T_User& aUserValue, 
    const T& aValue) : cond_type(aValue), m_var(aUserValue) {}

};

#endif