#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/types/tlocTypes.h>

namespace tloc {

  template <typename T>
  class Math
  {
  public:
    //------------------------------------------------------------------------
    // Basic functions

    static T Ceil(T aValue);
    static T Floor(T aValue);
    static T Abs(T aValue);
    static T FAbs(T aValue);
    static T Tan(T aValue);
    static T ATan(T aValue);
    static T ATan2(T aValue1, T aValue2);
    static T Log(T aLog);
    static T Sin(T aValInRad);
    static T ASin(T aValInRad);
    static T Cos(T aValInRad);
    static T ACos(T aValInRad);
    static T Degree(T aValueInRadian);
    static T Radian(T aValueInDegrees);
    static T Sqrt(T aValue);
    static T InvSqrt(T aValue);

    //------------------------------------------------------------------------
    // Misc functions

    static bool IsEqual(T a_first, T a_second);

    // Taken from OgreMath
    static bool IsNaN(T aValue);

    // If the difference between the two values is < eps then this
    // returns true
    static bool Approx(T aValue1, T aValue2, T eps = T(Math<T>::EPSILON));

    // Taken from http://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2/600306#600306
    static bool IsPowerOfTwo(const tl_uint& aValue);

    //------------------------------------------------------------------------
    // Fast Specialized functions

    static T FastInvSqrt(T aValue);
    static u32 FastPowOfTwo(const u32& aPower);

    // returns 1 for positive floats, -1 for negative floats, 0 for 0.0f
    // taken from http://www.musicdsp.org/showone.php?id=249
    static s32 FastSignInt(const f32& aRealIn);

    //------------------------------------------------------------------------
    // Simple Interpolations

    // Simple linear interpolation between two values.
    // The equation is:
    //        returnedValue = aBias * aValue1 + (1 - aBias) * aValue2;
    static T Lerp(T aValue1, T aValue2, T aBias = (T)0.5);

    static const T EPSILON;
    static const T ZERO_TOLERANCE;
    static const T MAX_REAL;
    static const T PI;
    static const T TWO_PI;
    static const T HALF_PI;
    static const T INV_PI;
    static const T INV_TWO_PI;
    static const T DEG_TO_RAD;
    static const T RAD_TO_DEG;
    static const T LOGN_2;
    static const T LOGN_10;
    static const T INV_LOGN_2;
    static const T INV_LOGN_10;

  private:
    Math();
    ~Math();

    // Math class initialization happens as soon as the program starts
    static void Initialize();

    static Math<T>      m_math;
    static const T      m_cosTable[64];
    static const T      m_sinTable[64];
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Math<s32>   Mathi;
  typedef Math<u32>   Mathu;

  typedef Math<f32>   Mathf32;
  typedef Math<f64>   Mathf64;

  typedef Math<tl_float>   Mathf;

};

#endif