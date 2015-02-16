#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include <tlocMath/tlocMathBase.h>
#include <tlocMath/types/tlocAngle.h>

#include <tlocCore/types/tlocTypes.h>
#include <limits>
#include <cmath>

namespace tloc {

  template <typename T>
  class Math
  {
  public:
    static const T      EPSILON;
    static const T      ZERO_TOLERANCE;
    static const T      MAX_REAL;
    static const T      PI;
    static const T      TWO_PI;
    static const T      HALF_PI;
    static const T      INV_PI;
    static const T      INV_TWO_PI;
    static const T      DEG_TO_RAD;
    static const T      RAD_TO_DEG;
    static const T      LOGN_2;
    static const T      LOGN_10;
    static const T      INV_LOGN_2;
    static const T      INV_LOGN_10;
  };



  //------------------------------------------------------------------------
  // Typedefs
  typedef Math<s32>   Mathi;
  typedef Math<u32>   Mathu;

  typedef Math<f32>   Mathf32;
  typedef Math<f64>   Mathf64;

  typedef Math<tl_float>   Mathf;

  namespace math {

    template <typename T>
    T Abs(T a_value);

    template <typename T>
    T Remainder(T a_numerator, T a_denominator);

    template <typename T>
    T Epsilon();

    template <typename T>
    bool Approx(T a_num1, T a_num2, tl_int a_maxUnitsInLastPlace);

    template <typename T>
    bool ApproxRelative(T a_num1, T a_num2, T a_epsilon);

    template <typename T>
    bool ApproxAbsolute(T a_num1, T a_num2, T a_epsilon);

    template <typename T>
    bool IsEqual(T a_num1, T a_num2);
    template <typename T>
    bool IsEqualRelative(T a_num1, T a_num2);
    template <typename T>
    bool IsEqualAbsolute(T a_num1, T a_num2);

    template <typename T>
    bool IsEqualToZero(T a_num1);
    template <typename T>
    bool IsEqualToZeroRelative(T a_num1);
    template <typename T>
    bool IsEqualToZeroAbsolute(T a_num1);

    template <typename T>
    bool IsNotEqualToZero(T a_num1);
    template <typename T>
    bool IsNotEqualToZeroRelative(T a_num1);
    template <typename T>
    bool IsNotEqualToZeroAbsolute(T a_num1);

    template <typename T>
    bool IsEqualToOne(T a_num1);
    template <typename T>
    bool IsEqualToOneRelative(T a_num1);
    template <typename T>
    bool IsEqualToOneAbsolute(T a_num1);

    template <typename T>
    bool IsNotEqualToOne(T a_num1);
    template <typename T>
    bool IsNotEqualToOneRelative(T a_num1);
    template <typename T>
    bool IsNotEqualToOneAbsolute(T a_num1);

    template <typename T>
    bool IsNotEqual(T a_num1, T a_num2);
    template <typename T>
    bool IsNotEqualRelative(T a_num1, T a_num2);
    template <typename T>
    bool IsNotEqualAbsolute(T a_num1, T a_num2);

    template <typename T>
    T Ceil(T a_value);

    template <typename T>
    T Floor(T a_value);

    template <typename T>
    T Abs(T a_value);

    template <typename T>
    T FAbs(T a_value);

    template <typename T>
    T Tan(math_t::Radian_T<T> a_value);

    template <typename T>
    math_t::Radian_T<T> 
      ATan(T a_value);

    template <typename T>
    math_t::Radian_T<T> 
      ATan2(T a_value1, T a_value2);

    template <typename T>
    T Log(T aLog);

    template <typename T>
    T Sin(math_t::Radian_T<T> a_value);

    template <typename T>
    math_t::Radian_T<T> 
      ASin(T a_value);

    template <typename T>
    T Cos(math_t::Radian_T<T> a_value);

    template <typename T>
    math_t::Radian_T<T> 
      ACos(T a_value);

    template <typename T>
    T Sqrt(T a_value);

    template <typename T>
    T InvSqrt(T a_value);

    //------------------------------------------------------------------------
    // Misc functions

    // Taken from OgreMath
    template <typename T>
    bool IsNaN(T aValue);

    // Taken from http://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2/600306#600306
    bool IsPowerOfTwo(const tl_uint& aValue);

    //------------------------------------------------------------------------
    // Fast Specialized functions

    template <typename T>
    T    FastInvSqrt(T aValue);

    u32  FastPowOfTwo(const u32& aPower);

    // returns 1 for positive floats, -1 for negative floats, 0 for 0.0f
    // taken from http://www.musicdsp.org/showone.php?id=249
    s32  FastSignInt(const f32& aRealIn);

    //------------------------------------------------------------------------
    // Simple Interpolations

    // Simple linear interpolation between two values.
    // The equation is:
    //        returnedValue = aBias * aValue1 + (1 - aBias) * aValue2;
    template <typename T>
    T    Lerp(T aValue1, T aValue2, T aBias = (T)0.5);
  };

};

#include "tlocMath.inl.h"

#endif