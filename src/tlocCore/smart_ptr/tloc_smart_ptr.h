#ifndef _TLOC_CORE_INCLUDE_ALL_SMART_PTR_H_
#define _TLOC_CORE_INCLUDE_ALL_SMART_PTR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

#define TLOC_TYPEDEF_ALL_SMART_PTRS(_type_)\
  TLOC_TYPEDEF_UNIQUE_PTR(_type_);\
  TLOC_TYPEDEF_VIRTUAL_PTR(_type_);\
  TLOC_TYPEDEF_SHARED_PTR(_type_)

#endif