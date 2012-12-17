#include "tlocVector2.h"
#include "tlocVector2.inl"

//------------------------------------------------------------------------
// Explicit template instantiations
template class tloc::math::Vector2<tloc::f32>;
template class tloc::math::Vector2<tloc::f64>;
template class tloc::math::Vector2<tloc::f128>;

//------------------------------------------------------------------------
#ifndef TLOC_FULL_SOURCE
#include "tlocVector2.inl"
#endif // TLOC_NO_SOURCE