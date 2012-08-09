#include "tlocMatrix3.h"
#include "tlocMatrix3.inl"

//------------------------------------------------------------------------
// Explicit template instantiations
template class tloc::math::Matrix3<tloc::f32>;
template class tloc::math::Matrix3<tloc::f64>;
template class tloc::math::Matrix3<tloc::f128>;

#ifndef TLOC_FULL_SOURCE
#include "tlocMatrix3.inl"
#endif