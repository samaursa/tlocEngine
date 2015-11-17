#ifndef _TLOC_CORE_BASE_CLASSES_NON_NEWABLE_H_
#define _TLOC_CORE_BASE_CLASSES_NON_NEWABLE_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core { namespace base_classes {

  class non_newable_i
  {
  public:
    void* operator new(tl_size) = delete;
    void* operator new(tl_size, void*) = delete;
    void* operator new[](tl_size) = delete;
    void* operator new[](tl_size, void*) = delete;
  };

};};};

#endif