#include "tlocTable.h"

#ifndef TLOC_FULL_SOURCE
//------------------------------------------------------------------------
// Instantiate table types upto 20x20
#define CLASS_NAME tloc::Table
#define TYPE tloc::s32
#include "tlocTemplateTypesNxM.h"
#undef TYPE

#define TYPE tloc::f32
#include "tlocTemplateTypesNxM.h"
#undef TYPE

#define TYPE tloc::f64
#include "tlocTemplateTypesNxM.h"
#undef TYPE

#define TYPE tloc::f128
#include "tlocTemplateTypesNxM.h"
#undef TYPE

#undef CLASS_NAME

//------------------------------------------------------------------------
// Include the definitions
#include "tlocTable.inl"
#endif