#include "tlocTuple.h"
#include "tlocTuple.inl"

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

namespace tloc { namespace core { namespace data_structs {

#include "tlocTupleExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f64, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(s32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(s64, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(u32, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(u64, 2);

  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f64, 3);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(s32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(s64, 3);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(u32, 3);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(u64, 3);

  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f32, 4);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(f64, 4);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(s32, 4);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(s64, 4);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(u32, 4);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(u64, 4);

  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(bool, 2);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(bool, 3);
  TLOC_EXPLICITLY_INSTANTIATE_TUPLE(bool, 4);

};};};

#endif
