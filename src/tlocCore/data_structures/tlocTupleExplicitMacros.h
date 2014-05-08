#ifndef _TLOC_CORE_TUPLE_EXPLICIT_MACROS_H_
#define _TLOC_CORE_TUPLE_EXPLICIT_MACROS_H_

// _vt_ = value_type
// _dt_ = derived_type (can be Tuple itself)
#define TLOC_EXPLICITLY_INSTANTIATE_TUPLE(_vt_, _size_)\
  template class tloc::core_ds::Tuple<_vt_, _size_>

#endif