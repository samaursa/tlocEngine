#include "tlocStrongType.h"
#include "tlocStrongType.inl"

namespace tloc { namespace core { namespace types {

#define TLOC_INSTANTIATE_STRONG_TYPE(_type_)\
  template struct StrongType_T<_type_, 0>;\
  template struct StrongType_T<_type_, 1>;\
  template struct StrongType_T<_type_, 2>;\
  template struct StrongType_T<_type_, 3>;\
  template struct StrongType_T<_type_, 4>;\
  template struct StrongType_T<_type_, 5>;\
  template struct StrongType_T<_type_, 6>;\
  template struct StrongType_T<_type_, 7>;\
  template struct StrongType_T<_type_, 8>;\
  template struct StrongType_T<_type_, 9>

  TLOC_INSTANTIATE_STRONG_TYPE(s8);
  TLOC_INSTANTIATE_STRONG_TYPE(u8);

  TLOC_INSTANTIATE_STRONG_TYPE(s32);
  TLOC_INSTANTIATE_STRONG_TYPE(s64);

  TLOC_INSTANTIATE_STRONG_TYPE(u32);
  TLOC_INSTANTIATE_STRONG_TYPE(u64);

  TLOC_INSTANTIATE_STRONG_TYPE(f32);
  TLOC_INSTANTIATE_STRONG_TYPE(f64);
  TLOC_INSTANTIATE_STRONG_TYPE(f128);


};};};