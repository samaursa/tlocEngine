#include "tlocVector.h"
#define TLOC_VECTOR_ALLOW_EASY_OPERATIONS
#include "tlocVector.inl"

#ifndef TLOC_FULL_SOURCE
//------------------------------------------------------------------------
// Instantiate table types upto 20x20
#define CLASS_NAME tloc::Vector
#define TYPE tloc::f32
#include <tlocCore/types/tlocTemplateTypesN.h>
#undef TYPE

#define TYPE tloc::f64
#include <tlocCore/types/tlocTemplateTypesN.h>
#undef TYPE

#define TYPE tloc::f128
#include <tlocCore/types/tlocTemplateTypesN.h>
#undef TYPE

#undef CLASS_NAME
//------------------------------------------------------------------------
// Include the definitions
#include "tlocVector.inl"

#else

namespace tloc { namespace math {

#include "tlocVectorExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f32, 1);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 1);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 2);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 3);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f32, 4);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 4);

  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s32, 1);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s64, 1);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s64, 2);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s64, 3);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s32, 4);
  TLOC_EXPLICITLY_INSTANTIATE_VECTOR(s64, 4);

};};

#endif // TLOC_NO_SOURCE