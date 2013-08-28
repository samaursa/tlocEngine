#include "tlocMatrix.h"

#define TLOC_MATRIX_ALLOW_EASY_OPERATIONS
#include "tlocMatrix.inl.h"

#ifndef TLOC_FULL_SOURCE
//------------------------------------------------------------------------
// Instantiate table types upto 20x20
#define CLASS_NAME tloc::Matrix
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
#include "tlocMatrix.inl.h"

#else

namespace tloc { namespace math { namespace types {

#include "tlocMatrixExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f32, 4);

  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 2);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 3);
  TLOC_EXPLICITLY_INSTANTIATE_MATRIX(f64, 4);

};};};

#endif // TLOC_NO_SOURCE