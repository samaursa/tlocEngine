#ifndef _TLOC_CORE_INCLUDE_ALL_SMART_PTR_INL_
#define _TLOC_CORE_INCLUDE_ALL_SMART_PTR_INL_

#ifndef _TLOC_CORE_INCLUDE_ALL_SMART_PTR_H_
#error "Must include header before including the inline file"
#endif

#include "tloc_smart_ptr.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#define TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(_type_)\
  TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(_type_);\
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(_type_);\
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(_type_)

#endif