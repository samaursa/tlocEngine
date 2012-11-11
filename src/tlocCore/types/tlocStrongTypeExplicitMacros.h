#define TLOC_INSTANTIATE_STRONG_TYPE(_type_)\
namespace tloc { namespace core { namespace types {\
  template class StrongType_T<_type_, 0>;\
  template class StrongType_T<_type_, 1>;\
  template class StrongType_T<_type_, 2>;\
  template class StrongType_T<_type_, 3>;\
  template class StrongType_T<_type_, 4>;\
  template class StrongType_T<_type_, 5>;\
  template class StrongType_T<_type_, 6>;\
  template class StrongType_T<_type_, 7>;\
  template class StrongType_T<_type_, 8>;\
  template class StrongType_T<_type_, 9>;\
};};};