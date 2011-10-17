namespace tloc
{
#define COND_TYPE_TEMP ConditionalType<T, true>

  template <typename T>
  TL_FI COND_TYPE_TEMP::ConditionalType() {}

  template <typename T>
  TL_FI COND_TYPE_TEMP::ConditionalType(const T& aValue)
    : m_value(aValue) {}

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator= (const COND_TYPE_TEMP& aOther)
  {
    m_value = aOther.value();
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator= (const T& aOther)
  {
    m_value = aOther;
    return *this;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator+ (const COND_TYPE_TEMP& aOther)
  {
    return value() + aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator+ (const T& aOther)
  {
    return value() + aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator- (const COND_TYPE_TEMP& aOther)
  {
    return value() - aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator- (const T& aOther)
  {
    return value() - aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator* (const COND_TYPE_TEMP& aOther)
  {
    return value() * aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator* (const T& aOther)
  {
    return value() * aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator/ (const COND_TYPE_TEMP& aOther)
  {
    return value() / aOther.value();
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::operator/ (const T& aOther)
  {
    return value() / aOther;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator+= (const COND_TYPE_TEMP& aOther)
  {
    m_value += aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator+= (const T& aOther)
  {
    m_value += aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator-= (const COND_TYPE_TEMP& aOther)
  {
    m_value -= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator-= (const T& aOther)
  {
    m_value -= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator*= (const COND_TYPE_TEMP& aOther)
  {
    m_value *= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator*= (const T& aOther)
  {
    m_value *= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator/= (const COND_TYPE_TEMP& aOther)
  {
    m_value /= aOther.m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator/= (const T& aOther)
  {
    m_value /= aOther;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator++()
  {
    ++m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP
    COND_TYPE_TEMP::operator++(int)
  {
    COND_TYPE_TEMP temp(m_value);
    ++m_value;
    return temp;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP&
    COND_TYPE_TEMP::operator--()
  {
    --m_value;
    return *this;
  }

  template <typename T>
  TL_FI COND_TYPE_TEMP
    COND_TYPE_TEMP::operator--(int)
  {
    COND_TYPE_TEMP temp(m_value);
    --m_value;
    return temp;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator==(const this_type& aOther)
  {
    return m_value == aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator==(const T& aOther)
  {
    return m_value == aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator!=(const this_type& aOther)
  {
    return m_value != aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator!=(const T& aOther)
  {
    return m_value != aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator< (const this_type& aOther)
  {
    return m_value < aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator< (const T& aOther)
  {
    return m_value < aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator<=(const this_type& aOther)
  {
    return m_value <= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator<=(const T& aOther)
  {
    return m_value <= aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator>=(const this_type& aOther)
  {
    return m_value >= aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator>=(const T& aOther)
  {
    return m_value >= aOther;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator> (const this_type& aOther)
  {
    return m_value > aOther.m_value;
  }

  template <typename T>
  TL_FI bool
    COND_TYPE_TEMP::operator> (const T& aOther)
  {
    return m_value > aOther;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::get()
  {
    return m_value;
  }

  template <typename T>
  TL_FI T
    COND_TYPE_TEMP::value()
  {
    return m_value;
  }
};