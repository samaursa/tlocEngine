#ifndef TLOC_MATH_H
#define TLOC_MATH_H

#include "tlocCore/tlocBase.h"
#include <cmath>

namespace tloc
{
  namespace Math
  {
    template <typename T> 
    FW_FI T Abs(const T& aValue) { return abs(aValue); }

    template <typename T>
    FW_FI T ATan(const T& aValue) { return atan(aValue); }

    template <typename T>
    FW_FI T ATan2(const T& aValue1, const T& aValue2) { return atan2(aValue1, aValue2); }

    template <typename T>
    FW_FI T Ceil(const T& aValue) { return ceil(aValue); }

    // Taken from OgreMath
    template <typename T>
    FW_FI bool IsNaN(const T& aValue) { return aValue != aValue; }
  };
};

#endif