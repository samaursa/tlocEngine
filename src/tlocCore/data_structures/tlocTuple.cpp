#include "tlocTuple.h"

#ifndef TLOC_FULL_SOURCE
//------------------------------------------------------------------------
// Instantiate table types upto 20x20
#define CLASS_NAME tloc::Tuple
#define TYPE tloc::s32
#include "tlocTemplateTypesN.h"
#undef TYPE

#define TYPE tloc::f32
#include "tlocTemplateTypesN.h"
#undef TYPE

#define TYPE tloc::f64
#include "tlocTemplateTypesN.h"
#undef TYPE

#define TYPE tloc::f128
#include "tlocTemplateTypesN.h"
#undef TYPE

#undef CLASS_NAME
//------------------------------------------------------------------------
// Include the definitions
#include <tlocCore/data_structures/tlocTuple.inl>

#else

TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE();

#endif
