#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include <cmath>
#include <float.h>

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"

namespace tloc {

  template <typename T>
  class Math
  {
  public:
    //------------------------------------------------------------------------
    // Basic functions

    TL_STATIC_FI T Ceil(const T& aValue);
    TL_STATIC_FI T Floor(const T& aValue);
    TL_STATIC_FI T Abs(const T& aValue);
    TL_STATIC_FI T FAbs(const T& aValue);
    TL_STATIC_FI T ATan(const T& aValue);
    TL_STATIC_FI T ATan2(const T& aValue1, const T& aValue2);
    TL_STATIC_FI T Log(const T& aLog);
    TL_STATIC_FI T Sin(const T& aValInRad);
    TL_STATIC_FI T Cos(const T& aValInRad);
    TL_STATIC_FI T Degree(const T& aValueInRadian);
    TL_STATIC_FI T Radian(const T& aValueInDegrees);
    TL_STATIC_FI T Sqrt(const T& aValue);
    TL_STATIC_FI T InvSqrt(const T& aValue);

    //------------------------------------------------------------------------
    // Misc functions

    // Taken from OgreMath
    TL_STATIC_FI bool IsNaN(const T& aValue);

    // If the difference between the two values is < eps then this
    // returns true
    TL_STATIC_FI bool Approx(const T& aValue1, const T& aValue2,
      T eps = T(1e-6));

    // Taken from http://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2/600306#600306
    TL_STATIC_FI bool IsPowerOfTwo(const u32& aValue);

    //------------------------------------------------------------------------
    // Fast Specialized functions

    TL_STATIC_FI T FastInvSqrt(const T& aValue);
    TL_STATIC_FI u32 FastPowOfTwo(const u32& aPower);

    // returns 1 for positive floats, -1 for negative floats, 0 for 0.0f
    // taken from http://www.musicdsp.org/showone.php?id=249
    TL_STATIC_FI s32 FastSignInt(const T& aRealIn);

    //------------------------------------------------------------------------
    // Simple Interpolations

    // Simple linear interpolation between two values.
    // The equation is:
    //        returnedValue = aBias * aValue1 + (1 - aBias) * aValue2;
    TL_STATIC_FI T Lerp(const T& aValue1, const T& aValue2,
                        const T& aBias = (T)0.5);

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
  typedef Math<f32>   Mathf;
  typedef Math<f64>   Mathd;
  typedef Math<f128>  Mathl;

};

#endif