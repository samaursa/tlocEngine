#include "tlocConditionalType.h"
#include "tlocConditionalType.inl.h"

#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core {

  // Some default instantiations
#define INSTANTIATE(_type_) template struct ConditionalType<_type_, true>; \
  template struct ConditionalType<_type_, false>

  INSTANTIATE(char8);
  INSTANTIATE(char32);

  INSTANTIATE(s8);
  INSTANTIATE(s16);
  INSTANTIATE(s32);
  INSTANTIATE(s64);

  INSTANTIATE(f32);
  INSTANTIATE(f64);

  INSTANTIATE(u8);
  INSTANTIATE(u16);
  INSTANTIATE(u32);
  INSTANTIATE(u64);

  INSTANTIATE(tl_size);

};};