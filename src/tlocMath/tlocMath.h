#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include "tlocCore/tlocBase.h"
#include <cmath>

#define TL_PI 4.0 * atan(1.0)

// Multiply these numbers with the respective source value to get the 
// correct output
#define TL_DEGREE_TO_RAD_CONSTANT (TL_PI / 180.0)
#define TL_RAD_TO_DEGREE_CONSTANT (180 / TL_PI)

namespace tloc
{
  template <typename T>
  class Math
  {
  public:

    TL_STATIC_FI T Ceil(const T& aValue);
    TL_STATIC_FI T Floor(const T& aValue);
    TL_STATIC_FI T Abs(const T& aValue);
    TL_STATIC_FI T FAbs(const T& aValue);
    TL_STATIC_FI T ATan(const T& aValue);
    TL_STATIC_FI T ATan2(const T& aValue1, const T& aValue2);

    // Taken from OgreMath
    TL_STATIC_FI bool IsNaN(const T& aValue);

    // If the difference between the two values is < eps then this
    // returns true
    TL_STATIC_FI bool Approx(const T& aValue1, const T& aValue2,
                      T eps = T(1e-6));   

    TL_STATIC_FI T Degree(const T& aValueInRadian);
    TL_STATIC_FI T Radian(const T& aValueInDegrees);    
    TL_STATIC_FI T Sqrt(const T& aValue);  
    TL_STATIC_FI T InvSqrt(const T& aValue);
    TL_STATIC_FI T FastInvSqrt(const T& aValue);
  };

  typedef Math<f32> Mathf;
  typedef Math<f64> Mathd;
  typedef Math<f128> Mathl;
};

#ifdef TLOC_FULL_SOURCE
#include "tlocMath.inl"
#endif

#endif