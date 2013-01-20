#ifndef TLOC_MATH_INL
#define TLOC_MATH_INL

#ifndef TLOC_MATH_H
#error "Must include header before including the inline file"
#endif

#include "tlocMath.h"
#include <cmath>
#include <tlocCore/types/tlocTypes.inl>

namespace tloc {

  namespace {
    template <typename T>
    T GetAbs(T a_value)
    {
      return abs(a_value);
    }

    s64 GetAbs(s64 a_value)
    {
      return (s64)abs((s32)a_value);
    }

    template <typename T>
    T GetSqrt(T a_value)
    {
      return sqrt(a_value);
    }

    s32 GetSqrt(s32 a_value)
    {
      return (s32)sqrt((tl_float)a_value);
    }

    s64 GetSqrt(s64 a_value)
    {
      return (s64)sqrt((tl_float)a_value);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Math<T>

  template <typename T>
  TL_FI T Math<T>::Ceil(T aValue)
  {
    return ceil(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::Floor(T aValue)
  {
    return floor(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::Abs(T aValue)
  {
    return GetAbs(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::FAbs(T aValue)
  {
    return fabs(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::Tan(T aValue)
  {
    return tan(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::ATan(T aValue)
  {
    return atan(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::ATan2(T aValue1, T aValue2)
  {
    return atan2(aValue1, aValue2);
  }

  template <typename T>
  TL_FI T Math<T>::Log( T aLog )
  {
    return log(aLog);
  }

  template <typename T>
  TL_FI T Math<T>::Sin( T aValInRad )
  {
    return sin(aValInRad);
  }

  template <typename T>
  TL_FI T Math<T>::ASin( T aValInRad )
  {
    return asin(aValInRad);
  }

  template <typename T>
  TL_FI T Math<T>::Cos( T aValInRad )
  {
    return cos(aValInRad);
  }

  template <typename T>
  TL_FI T Math<T>::ACos( T aValInRad )
  {
    return acos(aValInRad);
  }

  template <typename T>
  TL_FI T Math<T>::Degree(T aValueInRadian)
  {
    return aValueInRadian  * Math<T>::RAD_TO_DEG;
  }

  template <typename T>
  TL_FI T Math<T>::Radian(T aValueInDegrees)
  {
    return aValueInDegrees * Math<T>::DEG_TO_RAD;
  }

  template <typename T>
  TL_FI T Math<T>::Sqrt(T aValue)
  {
    return GetSqrt(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::InvSqrt(T aValue)
  {
    return ((T)1) / Sqrt(aValue);
  }

  //------------------------------------------------------------------------
  // Misc Functions

  template <typename T>
  TL_FI bool Math<T>::IsEqual(T a_first, T a_second)
  {
    return Approx(a_first, a_second, EPSILON);
  }

  template <typename T>
  TL_FI bool Math<T>::IsNaN(T aValue)
  {
    return aValue != aValue; //-V501
  }

  template <typename T>
  TL_FI bool Math<T>::Approx(T aValue1, T aValue2, T eps /* = T(1e-6) */)
  {
    T toCompare = Abs(aValue1 - aValue2);
    return (toCompare < eps);
  }

  template <typename T>
  TL_FI bool Math<T>::IsPowerOfTwo( const tl_uint& aValue )
  {
    return (aValue != 0) && ((aValue & (aValue - 1)) == 0);
  }

  //------------------------------------------------------------------------
  // Fast specialized functions

  template <typename T>
  TL_FI T Math<T>::FastInvSqrt(T aValue)
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
  TL_FI u32 Math<T>::FastPowOfTwo( const u32& aPower )
  {
    return 0x00000001 << aPower;
  }

  template <typename T>
  TL_FI s32 Math<T>::FastSignInt( const f32& aRealIn )
  {
    if (((s32&)aRealIn & 0x7FFFFFF)==0) return 0;
    return (signed ((s32&)aRealIn & 0x80000000) >> 31) | 1;
  }

  //------------------------------------------------------------------------
  // Simple Interpolations

  template <typename T>
  TL_FI T Math<T>::Lerp(T aValue1, T aValue2, T aBias)
  {
    return (aBias * aValue1) + ((1 - aBias) * aValue2);
  }



};

#endif