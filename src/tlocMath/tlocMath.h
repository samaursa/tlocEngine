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
  namespace Math
  {
    template <typename T>
    TL_FI T Ceil(const T& aValue) { return ceil(aValue); }

    template <typename T>
    TL_FI T Floor(const T& aValue) { return floor(aValue); }

    template <typename T> 
    TL_FI T Abs(const T& aValue) { return abs(aValue); }

    template <typename T>
    TL_FI T ATan(const T& aValue) { return atan(aValue); }

    template <typename T>
    TL_FI T ATan2(const T& aValue1, const T& aValue2) { return atan2(aValue1, aValue2); }

    // Taken from OgreMath
    template <typename T>
    TL_FI bool IsNaN(const T& aValue) { return aValue != aValue; }

    // If the difference between the two values is < eps then this
    // returns true
    template <typename T>
    TL_FI bool Approx(const T& aValue1, const T& aValue2,
                      T eps = T(1e-6))
    {
      T toCompare = Abs(aValue1 - aValue2);
      return (toCompare < eps);
    }

    template <typename T>
    TL_FI T Degree(const T& aValueInRadian)
    {
      return aValueInRadian  * (T)TL_RAD_TO_DEGREE_CONSTANT;
    }

    template <typename T>
    TL_FI T Radian(const T& aValueInDegrees)
    {
      return aValueInDegrees * (T)TL_DEGREE_TO_RAD_CONSTANT;
    }
  };
};

#endif