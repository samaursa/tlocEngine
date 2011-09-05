#include "tlocMatrix.h"

#ifndef TLOC_FULL_SOURCE
//------------------------------------------------------------------------
// Instantiate table types upto 20x20
#define CLASS_NAME tloc::Matrix
#define TYPE tloc::f32
#include "tlocCore/tlocTemplateTypesN.h"
#undef TYPE

#define TYPE tloc::f64
#include "tlocCore/tlocTemplateTypesN.h"
#undef TYPE

#define TYPE tloc::f128
#include "tlocCore/tlocTemplateTypesN.h"
#undef TYPE

#undef CLASS_NAME

//------------------------------------------------------------------------
// Include the definitions
#include "tlocMatrix.inl"

#else

IntentionallyEmptySourceFile();

#endif // TLOC_NO_SOURCE