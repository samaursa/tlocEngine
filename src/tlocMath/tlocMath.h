#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include <cmath>
#include <float.h>

#include "tlocCore/tlocBase.h"

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
    TL_STATIC_FI T Log(const T& aLog);
    TL_STATIC_FI T Sin(const T& aValInRad);
    TL_STATIC_FI T Cos(const T& aValInRad);

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

    // Simple linear interpolation between two values.
    // The equation is: 
    //        returnedValue = aBias * aValue1 + (1 - aBias) * aValue2;
    TL_STATIC_FI T Lerp(const T& aValue1, const T& aValue2, 
                        const T aBias = (T)0.5);

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
    
    static Math<T>  m_math;
    static const T  m_cosTable[64];
    static const T  m_sinTable[64];
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Math<f32> Mathf;
  typedef Math<f64> Mathd;
  typedef Math<f128> Mathl;  
};

#ifdef TLOC_FULL_SOURCE
#include "tlocMath.inl"
#endif

#endif