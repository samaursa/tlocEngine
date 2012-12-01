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

namespace tloc { namespace core {

  template class Tuple<tl_float, 2>;
  template class Tuple<f32,			 2>;
  template class Tuple<f64,			 2>;
  template class Tuple<tl_int,	 2>;
  template class Tuple<s32,			 2>;
  template class Tuple<s64,			 2>;
  template class Tuple<tl_uint,	 2>;
  template class Tuple<u32,			 2>;
  template class Tuple<u64,			 2>;

  template class Tuple<tl_float, 3>;
  template class Tuple<f32,			 3>;
  template class Tuple<f64,			 3>;
  template class Tuple<tl_int,	 3>;
  template class Tuple<s32,			 3>;
  template class Tuple<s64,			 3>;
  template class Tuple<tl_uint,	 3>;
  template class Tuple<u32,			 3>;
  template class Tuple<u64,			 3>;

  template class Tuple<tl_float, 4>;
  template class Tuple<f32,			 4>;
  template class Tuple<f64,			 4>;
  template class Tuple<tl_int,	 4>;
  template class Tuple<s32,			 4>;
  template class Tuple<s64,			 4>;
  template class Tuple<tl_uint,	 4>;
  template class Tuple<u32,			 4>;
  template class Tuple<u64,			 4>;

};};

#endif
