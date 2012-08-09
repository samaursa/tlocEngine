#ifndef TLOC_CONDITIONAL_TYPE_H
#define TLOC_CONDITIONAL_TYPE_H

#include <tlocCore/tlocBase.h>

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Conditional type
  //
  // This type is capable of being compiled out if T_DeclareValue = false. All
  // operators are overloaded. With T_DeclareValue = false, operators do not do
  // anything. In case of the comparison operators, the result is always false.
  // If you get the value of the <false> type the value returned is
  // g_conditional_type_invalid_value.
  //
  // @note You should NOT test against g_conditional_type_invalid_value to see
  // if your type is valid or not. Your first attempt should be to use compile
  // time type checking. At runtime, you can use the IsValid() function which
  // will return true for a <true> type.
  template <typename T, bool T_DeclareValue>
  struct ConditionalType {};

  ///-------------------------------------------------------------------------
  /// @brief This type can be conditionally removed based on the boolean value.
  ///-------------------------------------------------------------------------
  template <typename T>
  struct ConditionalType<T, false>
  {
    typedef T                                   value_type;
    typedef ConditionalType<value_type, false>  this_type;

    TL_FI ConditionalType();
    TL_FI ConditionalType(const T& aValue);

    TL_FI this_type& operator= (const this_type& aOther);
    TL_FI this_type& operator= (const T& aOther);

    TL_FI T          operator+ (const this_type& aOther) const;
    TL_FI T          operator+ (const T& aOther) const;
    TL_FI T          operator- (const this_type& aOther) const;
    TL_FI T          operator- (const T& aOther) const;
    TL_FI T          operator* (const this_type& aOther) const;
    TL_FI T          operator* (const T& aOther) const;
    TL_FI T          operator/ (const this_type& aOther) const;
    TL_FI T          operator/ (const T& aOther) const;

    TL_FI this_type& operator+=(const this_type& aOther);
    TL_FI this_type& operator+=(const T& aOther);
    TL_FI this_type& operator-=(const this_type& aOther);
    TL_FI this_type& operator-=(const T& aOther);
    TL_FI this_type& operator*=(const this_type& aOther);
    TL_FI this_type& operator*=(const T& aOther);
    TL_FI this_type& operator/=(const this_type& aOther);
    TL_FI this_type& operator/=(const T& aOther);

    TL_FI this_type& operator++();
    TL_FI this_type  operator++(int);
    TL_FI this_type& operator--();
    TL_FI this_type  operator--(int);

    TL_FI bool       operator==(const this_type& aOther) const;
    TL_FI bool       operator==(const T& aOther) const;
    TL_FI bool       operator!=(const this_type& aOTher) const;
    TL_FI bool       operator!=(const T& aOTher) const;
    TL_FI bool       operator< (const this_type& aOther) const;
    TL_FI bool       operator< (const T& aOther) const;
    TL_FI bool       operator<=(const this_type& aOther) const;
    TL_FI bool       operator<=(const T& aOther) const;
    TL_FI bool       operator>=(const this_type& aOther) const;
    TL_FI bool       operator>=(const T& aOther) const;
    TL_FI bool       operator> (const this_type& aOther) const;
    TL_FI bool       operator> (const T& aOther) const;

    TL_FI const T&   Get() const;
    TL_FI T          Value() const;

    TL_FI bool       IsValid() const;

    static T g_conditional_type_invalid_value;
  };

  // Default value for the returned invalid_type
  template <typename T>
  T ConditionalType<T, false>::g_conditional_type_invalid_value;

  /// ConditionalType<true> which behaves as if you are working with the original
  /// type itself
  template <typename T>
  struct ConditionalType<T, true>
  {
    typedef T                                   value_type;
    typedef ConditionalType<value_type, true>   this_type;

    TL_FI ConditionalType();
    TL_FI ConditionalType(const T& aValue);

    TL_FI this_type& operator= (const this_type& aOther);
    TL_FI this_type& operator= (const T& aOther);

    TL_FI T          operator+ (const this_type& aOther) const;
    TL_FI T          operator+ (const T& aOther) const;
    TL_FI T          operator- (const this_type& aOther) const;
    TL_FI T          operator- (const T& aOther) const;
    TL_FI T          operator* (const this_type& aOther) const;
    TL_FI T          operator* (const T& aOther) const;
    TL_FI T          operator/ (const this_type& aOther) const;
    TL_FI T          operator/ (const T& aOther) const;

    TL_FI this_type& operator+=(const this_type& aOther);
    TL_FI this_type& operator+=(const T& aOther);
    TL_FI this_type& operator-=(const this_type& aOther);
    TL_FI this_type& operator-=(const T& aOther);
    TL_FI this_type& operator*=(const this_type& aOther);
    TL_FI this_type& operator*=(const T& aOther);
    TL_FI this_type& operator/=(const this_type& aOther);
    TL_FI this_type& operator/=(const T& aOther);

    TL_FI this_type& operator++();
    TL_FI this_type  operator++(int);
    TL_FI this_type& operator--();
    TL_FI this_type  operator--(int);

    TL_FI bool       operator==(const this_type& aOther) const;
    TL_FI bool       operator==(const T& aOther) const;
    TL_FI bool       operator!=(const this_type& aOTher) const;
    TL_FI bool       operator!=(const T& aOTher) const;
    TL_FI bool       operator< (const this_type& aOther) const;
    TL_FI bool       operator< (const T& aOther) const;
    TL_FI bool       operator<=(const this_type& aOther) const;
    TL_FI bool       operator<=(const T& aOther) const;
    TL_FI bool       operator>=(const this_type& aOther) const;
    TL_FI bool       operator>=(const T& aOther) const;
    TL_FI bool       operator> (const this_type& aOther) const;
    TL_FI bool       operator> (const T& aOther) const;

    TL_FI const T&   Get() const;
    TL_FI T          Value() const;

    TL_FI bool       IsValid() const;

  private:

    T                m_value;
  };

  ///-------------------------------------------------------------------------
  /// Condition type package. Including ConditionalType as a member with
  /// T_DeclareValue = false will not eliminate the size of the type (C++ does
  /// not allow 0 size classes). To get around that, use the following class
  /// for one of your other members in the class where T_User is the other
  /// member and T is your conditional type.
  ///
  /// @note All operators are inherited from ConditionalType<> which means that
  /// comparison between this package and another package is essentially a
  /// comparison between ConditionType<>s and does NOT take the user variable
  /// into account.
  ///-------------------------------------------------------------------------
  template <typename T_User, typename T, bool T_DeclareValue>
  struct ConditionalTypePackage : public ConditionalType<T, T_DeclareValue>
  {
    typedef ConditionalType<T, T_DeclareValue>    cond_type;

    ConditionalTypePackage();
    ConditionalTypePackage(const T_User& aUserValue, const T& aValue);

    using cond_type::operator=;

    using cond_type::operator+;
    using cond_type::operator-;
    using cond_type::operator*;
    using cond_type::operator/;

    using cond_type::operator+=;
    using cond_type::operator-=;
    using cond_type::operator*=;
    using cond_type::operator/=;

    using cond_type::operator++;
    using cond_type::operator--;

    using cond_type::operator==;
    using cond_type::operator!=;
    using cond_type::operator<;
    using cond_type::operator>;
    using cond_type::operator<=;
    using cond_type::operator>=;

    T_User m_var;
  };

  // Global operators

  template <typename T, typename T2, bool T_DeclareValue>
  T operator+( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator+(aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  ConditionalType<T2, T_DeclareValue>
    operator+=( const T& a_otherValue,
    const ConditionalType<T2, T_DeclareValue>& a_other)
  {
    return a_other.operator+(a_otherValue);
  }

  template <typename T, typename T2>
  T operator-( const T& aOtherValue,
    const ConditionalType<T2, false>& aOther)
  {
    TLOC_UNUSED(aOther);
    return aOtherValue;
  }

  template <typename T, typename T2>
  T operator-( const T& aOtherValue,
    const ConditionalType<T2, true>& aOther)
  {
    return aOtherValue - aOther.Get();
  }

  template <typename T, typename T2>
  ConditionalType<T2, false>
    operator-=( const T& aOtherValue,
    const ConditionalType<T2, false>& aOther)
  {
    TLOC_UNUSED(aOther);
    return aOtherValue;
  }

  template <typename T, typename T2>
  ConditionalType<T2, true>
    operator-=( const T& aOtherValue,
    const ConditionalType<T2, true>& aOther)
  {
    return aOtherValue - aOther.Get();
  }

  template <typename T, typename T2, bool T_DeclareValue>
  T operator*( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator*(aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  ConditionalType<T2, T_DeclareValue>
    operator*=( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator*(aOtherValue);
  }

  template <typename T, typename T2>
  T operator/( const T& aOtherValue,
    const ConditionalType<T2, false>& aOther)
  {
    TLOC_UNUSED(aOther);
    return aOtherValue;
  }

  template <typename T, typename T2>
  T operator/( const T& aOtherValue,
    const ConditionalType<T2, true>& aOther)
  {
    return aOtherValue / aOther.Get();
  }

  template <typename T, typename T2>
  ConditionalType<T2, false>
    operator/=( const T& aOtherValue,
    const ConditionalType<T2, false>& aOther)
  {
    TLOC_UNUSED(aOther);
    return aOtherValue;
  }

  template <typename T, typename T2>
  ConditionalType<T2, true>
    operator/=( const T& aOtherValue,
    const ConditionalType<T2, true>& aOther)
  {
    return aOtherValue / aOther.Get();
  }

  template <typename T, typename T2, bool T_DeclareValue>
  bool operator==( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator==(aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  bool operator!=( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator!=(aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  bool operator<=( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator >= (aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  bool operator>=( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator <= (aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  bool operator<( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator > (aOtherValue);
  }

  template <typename T, typename T2, bool T_DeclareValue>
  bool operator>( const T& aOtherValue,
    const ConditionalType<T2, T_DeclareValue>& aOther)
  {
    return aOther.operator < (aOtherValue);
  }

};};

#endif