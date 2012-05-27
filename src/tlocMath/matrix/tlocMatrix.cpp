#include "tlocMatrix.h"
#include "tlocMatrix.inl"

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
#include "tlocMatrix.inl"

#else

TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE();

#endif // TLOC_NO_SOURCE