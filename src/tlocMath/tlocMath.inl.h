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

  namespace {
    template <typename T>
    T GetAbs(T a_value)
    {
      return std::abs(a_value);
    }

    TL_I s64 GetAbs(s64 a_value)
    {
      return (s64)std::abs((s32)a_value);
    }

    template <typename T>
    T GetSqrt(T a_value)
    {
      return std::sqrt(a_value);
    }

    TL_I s32 GetSqrt(s32 a_value)
    {
      return (s32)std::sqrt((tl_float)a_value);
    }

    TL_I s64 GetSqrt(s64 a_value)
    {
      return (s64)std::sqrt((tl_float)a_value);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Math<T>

  template <typename T>
  T Math<T>::
    Ceil(T aValue)
  {
    return std::ceil(aValue);
  }

  template <typename T>
  T Math<T>::
    Floor(T aValue)
  {
    return std::floor(aValue);
  }

  template <typename T>
  T Math<T>::
    Abs(T aValue)
  {
    return GetAbs(aValue);
  }

  template <typename T>
  T Math<T>::
    FAbs(T aValue)
  {
    return std::fabs(aValue);
  }

  template <typename T>
  T Math<T>::
    Tan(T aValue)
  {
    return std::tan(aValue);
  }

  template <typename T>
  T Math<T>::
    ATan(T aValue)
  {
    return std::atan(aValue);
  }

  template <typename T>
  T Math<T>::
    ATan2(T aValue1, T aValue2)
  {
    return std::atan2(aValue1, aValue2);
  }

  template <typename T>
  T Math<T>::
    Log( T aLog )
  {
    return std::log(aLog);
  }

  template <typename T>
  T Math<T>::
    Sin( T aValInRad )
  {
    return std::sin(aValInRad);
  }

  template <typename T>
  T Math<T>::
    ASin( T aValInRad )
  {
    return std::asin(aValInRad);
  }

  template <typename T>
  T Math<T>::
    Cos( T aValInRad )
  {
    return std::cos(aValInRad);
  }

  template <typename T>
  T Math<T>::
    ACos( T aValInRad )
  {
    return std::acos(aValInRad);
  }

  template <typename T>
  T Math<T>::
    Degree(T aValueInRadian)
  {
    return aValueInRadian  * Math<T>::RAD_TO_DEG;
  }

  template <typename T>
  T Math<T>::
    Radian(T aValueInDegrees)
  {
    return aValueInDegrees * Math<T>::DEG_TO_RAD;
  }

  template <typename T>
  T Math<T>::
    Sqrt(T aValue)
  {
    return GetSqrt(aValue);
  }

  template <typename T>
  T Math<T>::
    InvSqrt(T aValue)
  {
    return ((T)1) / Sqrt(aValue);
  }

  //------------------------------------------------------------------------
  // Misc Functions

  template <typename T>
  bool Math<T>::
    IsEqual(T a_first, T a_second)
  {
    return Approx(a_first, a_second, EPSILON);
  }

  template <typename T>
  bool Math<T>::
    IsNaN(T aValue)
  {
    return aValue != aValue; //-V501
  }

  template <typename T>
  bool Math<T>::
    Approx(T aValue1, T aValue2, T eps /* = T(1e-6) */)
  {
    T toCompare = Abs(aValue1 - aValue2);
    return (toCompare <= eps);
  }

  template <typename T>
  bool Math<T>::
    IsPowerOfTwo( const tl_uint& aValue )
  {
    return (aValue != 0) && ((aValue & (aValue - 1)) == 0);
  }

  //------------------------------------------------------------------------
  // Fast specialized functions

  template <typename T>
  T Math<T>::
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

  template <typename T>
  u32 Math<T>::
    FastPowOfTwo( const u32& aPower )
  {
    return 0x00000001 << aPower;
  }

  template <typename T>
  s32 Math<T>::
    FastSignInt( const f32& aRealIn )
  {
    if (((s32&)aRealIn & 0x7FFFFFF)==0) return 0;
    return (signed ((s32&)aRealIn & 0x80000000) >> 31) | 1;
  }

  //------------------------------------------------------------------------
  // Simple Interpolations

  template <typename T>
  T Math<T>::
    Lerp(T aValue1, T aValue2, T aBias)
  {
    return (aBias * aValue1) + ((1 - aBias) * aValue2);
  }

  namespace math {

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
        while (num2Res < a_num1 ||
               Approx(num2Res, a_num1))
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
    };

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
    bool Approx(T a_num1, T a_num2)
    {
      TLOC_STATIC_ASSERT_IS_ARITH(T);
      typedef Loki::Int2Type< Loki::TypeTraits<T>::isFloat> float_or_not;

      return priv::DoApprox(a_num1, a_num2, Epsilon<T>(), float_or_not());
    }

  };

};

#endif