#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include "tlocCore/tlocBase.h"
#include <cmath>

namespace tloc
{
  namespace Math
  {
    template <typename T>
    FW_FI T Ceil(const T& aValue) { return ceil(aValue); }

    template <typename T>
    FW_FI T Floor(const T& aValue) { return floor(aValue;) }

    template <typename T> 
    FW_FI T Abs(const T& aValue) { return abs(aValue); }

    template <typename T>
    FW_FI T ATan(const T& aValue) { return atan(aValue); }

    template <typename T>
    FW_FI T ATan2(const T& aValue1, const T& aValue2) { return atan2(aValue1, aValue2); }

    // Taken from OgreMath
    template <typename T>
    FW_FI bool IsNaN(const T& aValue) { return aValue != aValue; }

    // If the difference between the two values is < eps then this
    // returns true
    template <typename T>
    FW_FI bool Approx(const T& aValue1, const T& aValue2,
                      T eps = T(1e-6))
    {
      T toCompare = Abs(aValue1 - aValue2);
      return (toCompare < eps);
    }
  };
};

#endif