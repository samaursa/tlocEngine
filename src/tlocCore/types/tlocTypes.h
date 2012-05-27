#pragma once
#ifndef TLOC_TYPES_H
#define TLOC_TYPES_H

#include <tlocCore/tlocBase.h>
#include <wctype.h>
#include <limits.h>

//------------------------------------------------------------------------
// Global functions, no namespace
//
// These are the rare few functions that are globally defined without under
// the tloc namespace. This is so that types in other namespaces can
// successfully call TLOC_DEF_TYPE.

//////////////////////////////////////////////////////////////////////////
// Compile time type to string functions.
// USAGE: A type that you want (or is required) to have its own specialized
//        type_to_string<> function should simply call TLOC_DEF_TYPE(type)
//        after the type declaration in the header

// We do not allow unregistered types to be queried. If the compiler sent you
// here, trace back to the type that originated the error and register it.
template <typename>
struct tloc_type_to_string
{
  static const char* value()
  {
    TLOC_STATIC_ASSERT(false, Using_an_unregistered_type_Call_TLOC_DEF_TYPE_to_register_the_type);
  }
};

#ifdef TLOC_DEF_TYPE
#error "TLOC_DEF_TYPE is already defined somewhere else!"
#else
#define TLOC_DEF_TYPE(_type_)\
  template <>\
  struct tloc_type_to_string<_type_>\
  {\
    static const char* value()\
    {\
      return #_type_;\
    }\
  }
#endif

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Basic types

  typedef char              char8;
  typedef wchar_t           char32;

  typedef __int8            s8;
  typedef __int16           s16;
  typedef __int32           s32;
  typedef __int64           s64;
  typedef float             f32;
  typedef double            f64;
  typedef long double       f128;

  typedef unsigned char     uchar8;
  typedef unsigned __int8   u8;
  typedef unsigned __int16  u16;
  typedef unsigned __int32  u32;
  typedef unsigned __int64  u64;

  typedef size_t            tl_size;
  typedef uintptr_t         tl_uintptr; // Guaranteed to hold a native pointer
  typedef ptrdiff_t         tl_ptrdiff;

  //------------------------------------------------------------------------
  // The following types are useful when you want the best type size depending
  // on the platform itself

#if defined(WIN32) || defined(_WIN32)
  typedef s32               tl_int;
  typedef u32               tl_uint;
  typedef f32               tl_float;
#elif defined(_WIN64)
  typedef s64               tl_int;
  typedef u64               tl_uint;
  typedef f64               tl_float;
#else
# error WIP
#endif

  //////////////////////////////////////////////////////////////////////////
  // Numerical limits

#define TL_NUM_CHAR_BITS          CHAR_BIT
#define TL_SCHAR_MIN              SCHAR_MIN
#define TL_SCHAR_MAX              SCHAR_MAX
#define TL_UCHAR_MIN              0
#define TL_UCHAR_MAX              UCHAR_MAX

#define TL_CHAR_MIN               CHAR_MIN
#define TL_CHAR_MAX               CHAR_MAX

#define TL_WCHAR_MAX_NUM_BYTES    MB_LEN_MAX
#define TL_SHORT_MIN              SHRT_MIN
#define TL_SHORT_MAX              SHRT_MAX
#define TL_USHORT_MIN             0
#define TL_USHORT_MAX             USHRT_MAX

#define TL_INT_MIN                INT_MIN
#define TL_INT_MAX                INT_MAX
#define TL_UINT_MIN               0
#define TL_UINT_MAX               UINT_MAX

#define TL_LONG_MIN               LONG_MIN
#define TL_LONG_MAX               LONG_MAX
#define TL_ULONG_MIN              0
#define TL_ULONG_MAX              ULONG_MAX

#define TL_LLONG_MIN              LLONG_MIN
#define TL_LLONG_MAX              LLONG_MAX
#define TL_ULLONG_MIN             0
#define TL_ULLONG_MAX             ULLONG_MAX

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
};

#endif