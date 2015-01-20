#ifndef TLOC_MATH_INL
#define TLOC_MATH_INL

#ifndef TLOC_MATH_H
#error "Must include header before including the inline file"
#endif

#include "tlocMath.h"
#include <cmath>
#include <cstdlib>
#include <tlocCore/types/tlocTypes.inl.h>

namespace tloc {

  namespace priv {
  }

  //------------------------------------------------------------------------
  // Misc Functions

  //------------------------------------------------------------------------
  // Fast specialized functions


  namespace math {

    // -----------------------------------------------------------------------
    // private global functions

    namespace priv {

      typedef type_true   IsFloat;
      typedef type_false  IsNotFloat;

      template <typename T>
      T DoRemainder(T a_num1, T a_num2, IsFloat)
      {
        // At least on MSVC fmod returns the wrong answer (e.g. 1.0 % 0.1 is
        // equal to 0.0f, where as fmod returns 0.0999999)
        //return fmod(a_num1, a_num2);

        if (a_num2 > a_num1)
        { return a_num1; }

        tl_size multi = 1;
        T num2Res = a_num2;
        while (num2Res < a_num1 || IsEqual(num2Res, a_num1))
        {
          ++multi;
          num2Res = a_num2 * multi;
        }

        num2Res = a_num2 * (multi - 1);
        return a_num1 - num2Res;
      }

      template <typename T>
      T DoRemainder(T a_num1, T a_num2, IsNotFloat)
      { return a_num1 % a_num2; }

      template <typename T>
      bool DoApprox(T a_num1, T a_num2, T a_epsilon, IsFloat)
      {
        T toCompare = fabs(a_num1 - a_num2);
        return (toCompare <= a_epsilon);
      }

      template <typename T>
      bool DoApprox(T a_num1, T a_num2, T a_epsilon, IsNotFloat)
      {
        T toCompare = Abs<T>(a_num1 - a_num2);
        return (toCompare <= a_epsilon);
      }

      typedef type_true   IsUnsigned;
      typedef type_false  IsSigned;

      template <typename T>
      T DoAbs(T a_value, IsSigned)
      {
        if (a_value < 0)
        { return -a_value; }

        return a_value;
      }

      template <typename T>
      T DoAbs(T a_value, IsUnsigned)
      { return a_value; }

      template <typename T>
      T DoGetAbs(T a_value)
      {
        return std::abs(a_value);
      }

      TL_I s64 DoGetAbs(s64 a_value)
      {
        return (s64)std::abs((s32)a_value);
      }

      template <typename T>
      T DoGetSqrt(T a_value)
      {
        return std::sqrt(a_value);
      }

      TL_I s32 DoGetSqrt(s32 a_value)
      {
        return (s32)std::sqrt((tl_float)a_value);
      }

      TL_I s64 DoGetSqrt(s64 a_value)
      {
        return (s64)std::sqrt((tl_float)a_value);
      }
    };

    // -----------------------------------------------------------------------
    // global functions

    template <typename T>
    T Abs(T a_value)
    {
      TLOC_STATIC_ASSERT_IS_ARITH(T);
      typedef Loki::Int2Type< Loki::TypeTraits<T>::isUnsignedInt> s_or_u;

      return priv::DoAbs(a_value, s_or_u());
    }

    template <typename T>
    T Remainder(T a_numerator, T a_denominator)
    {
      TLOC_STATIC_ASSERT_IS_ARITH(T);
      typedef Loki::Int2Type< Loki::TypeTraits<T>::isFloat> float_or_not;

      return priv::DoRemainder(a_numerator, a_denominator, float_or_not());
    }

    template <typename T>
    T Epsilon()
    {
      TLOC_STATIC_ASSERT_IS_ARITH(T);
      return std::numeric_limits<T>::epsilon();
    }

    template <typename T>
    bool Approx(T a_num1, T a_num2, T eps)
    {
      TLOC_STATIC_ASSERT_IS_ARITH(T);
      typedef Loki::Int2Type< Loki::TypeTraits<T>::isFloat> float_or_not;

      return priv::DoApprox(a_num1, a_num2, eps, float_or_not());
    }

    template <typename T>
    bool IsEqual(T a_num1, T a_num2)
    { return Approx(a_num1, a_num2, Epsilon<T>()); }

    template <typename T>
    bool IsEqualToZero(T a_num1)
    { return IsEqual(a_num1, (T)0); }

    template <typename T>
    bool IsNotEqualToZero(T a_num1)
    { return IsNotEqualToZero(a_num1) == false; }

    template <typename T>
    bool IsEqualToOne(T a_num1)
    { return IsEqual(a_num1, (T)1); }

    template <typename T>
    bool IsNotEqualToOne(T a_num1)
    { return IsEqualToOne(a_num1) == false; }

    template <typename T>
    bool IsNotEqual(T a_num1, T a_num2)
    { return IsEqual(a_num1, a_num2) == false; }

    template <typename T>
    T 
      Ceil(T aValue)
    {
      return std::ceil(aValue);
    }

    template <typename T>
    T Floor(T aValue)
    {
      return std::floor(aValue);
    }

    template <typename T>
    T 
      FAbs(T aValue)
    {
      return std::fabs(aValue);
    }

    template <typename T>
    T 
      Tan(math_t::Radian_T<T> a_value)
    {
      return std::tan(a_value.Get());
    }

    template <typename T>
    math_t::Radian_T<T> 
      ATan(T a_value)
    {
      return math_t::MakeRadian(std::atan(a_value));
    }

    template <typename T>
    math_t::Radian_T<T> 
      ATan2(T a_value1, T a_value2)
    {
      return math_t::MakeRadian(std::atan2(a_value1, a_value2));
    }

    template <typename T>
    T 
      Log( T aLog )
    {
      return std::log(aLog);
    }

    template <typename T>
    T 
      Sin(math_t::Radian_T<T> a_value)
    {
      return std::sin(a_value.Get());
    }

    template <typename T>
    math_t::Radian_T<T> 
      ASin(T a_value)
    {
      return math_t::MakeRadian(std::asin(a_value));
    }

    template <typename T>
    T 
      Cos(math_t::Radian_T<T> a_value)
    {
      return std::cos(a_value.Get());
    }

    template <typename T>
    math_t::Radian_T<T> 
      ACos(T a_value)
    {
      return math_t::MakeRadian(std::acos(a_value));
    }

    template <typename T>
    T 
      Sqrt(T aValue)
    {
      return priv::DoGetSqrt(aValue);
    }

    template <typename T>
    T 
      InvSqrt(T aValue)
    {
      return ((T)1) / Sqrt(aValue);
    }

    template <typename T>
    bool 
      IsNaN(T aValue)
    {
      return aValue != aValue; //-V501
    }

    template <typename T>
    T 
      FastInvSqrt(T aValue)
    {
      f32 lLength = (f32)aValue;

      // Calculate length inverse
      f32 xhalf = 0.5f*lLength;
      s32 i = *(s32*)&lLength; // get bits for floating value
      i = 0x5f375a86- (i>>1); // gives initial guess y0
      lLength = *(f32*)&i; // convert bits back to float
      lLength = lLength*(1.5f-xhalf*lLength*lLength); // Newton step, repeating increases accuracy

      return (T)lLength;
    }

    //------------------------------------------------------------------------
    // Simple Interpolations

    template <typename T>
    T 
      Lerp(T aValue1, T aValue2, T aBias)
    {
      return (aBias * aValue1) + ((1 - aBias) * aValue2);
    }

  };
};

#endif