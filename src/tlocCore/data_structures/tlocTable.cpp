#include "tlocTable.h"
#include "tlocTable.inl.h"

namespace tloc { namespace core { namespace data_structs {

#define INSTANTIATE_TABLE_FOR_ALL_TYPES(_row_,_col_)\
  TLOC_EXPLICITLY_INSTANTIATE_TABLE(f32, _row_, _col_);\
  TLOC_EXPLICITLY_INSTANTIATE_TABLE(f64, _row_, _col_);\
  TLOC_EXPLICITLY_INSTANTIATE_TABLE(u32, _row_, _col_);\
  TLOC_EXPLICITLY_INSTANTIATE_TABLE(u64, _row_, _col_);\
  TLOC_EXPLICITLY_INSTANTIATE_TABLE(s32, _row_, _col_);\
  TLOC_EXPLICITLY_INSTANTIATE_TABLE(s64, _row_, _col_)

  INSTANTIATE_TABLE_FOR_ALL_TYPES(1, 1);
  INSTANTIATE_TABLE_FOR_ALL_TYPES(2, 2);
  INSTANTIATE_TABLE_FOR_ALL_TYPES(3, 3);
  INSTANTIATE_TABLE_FOR_ALL_TYPES(4, 4);

};};};