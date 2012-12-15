#include "tlocVector3.h"
#include "tlocVector3.inl"

//------------------------------------------------------------------------
// Explicit template instantiations
template class tloc::math::Vector3<tloc::s32>;
template class tloc::math::Vector3<tloc::s64>;
template class tloc::math::Vector3<tloc::u32>;
template class tloc::math::Vector3<tloc::u64>;
template class tloc::math::Vector3<tloc::f32>;
template class tloc::math::Vector3<tloc::f64>;
template class tloc::math::Vector3<tloc::f128>;

#ifndef TLOC_FULL_SOURCE
#include "tlocVector3.inl"
#endif