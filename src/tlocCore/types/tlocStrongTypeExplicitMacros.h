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