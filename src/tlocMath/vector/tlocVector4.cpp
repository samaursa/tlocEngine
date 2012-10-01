#include "tlocVector4.h"
#include "tlocVector4.inl"

//------------------------------------------------------------------------
// Explicit template instantiations
template class tloc::math::Vector4<tloc::f32>;
template class tloc::math::Vector4<tloc::f64>;
template class tloc::math::Vector4<tloc::f128>;
template class tloc::math::Vector4<tloc::tl_float>;

#ifndef TLOC_FULL_SOURCE
#include "tlocVector3.inl"
#endif