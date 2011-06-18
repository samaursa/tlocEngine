#include "tlocMath/tlocMath.h"

namespace tloc
{
  template Math<f32>;
  template Math<f64>;
  template Math<f128>;
};

#ifndef TLOC_FULL_SOURCE
#include "tlocMath.inl"
#endif