#include "tlocTable.h"
#include "tlocTable.inl"

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

#else

namespace tloc { namespace core { namespace data_structs {

#define INSTANTIATE_TABLE_FOR_ALL_TYPES(_row_,_col_)\
  template class Table<f32,			 _row_, _col_>;\
  template class Table<f64,			 _row_, _col_>;\
  template class Table<s32,			 _row_, _col_>;\
  template class Table<s64,			 _row_, _col_>;\
  template class Table<u32,			 _row_, _col_>;\
  template class Table<u64,			 _row_, _col_>

  INSTANTIATE_TABLE_FOR_ALL_TYPES(1, 1);
  INSTANTIATE_TABLE_FOR_ALL_TYPES(2, 2);
  INSTANTIATE_TABLE_FOR_ALL_TYPES(3, 3);
  INSTANTIATE_TABLE_FOR_ALL_TYPES(4, 4);

};};};

#endif