#ifndef _TLOC_CORE_BASE_CLASSES_NON_NEWABLE_H_
#define _TLOC_CORE_BASE_CLASSES_NON_NEWABLE_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core { namespace base_classes {

  class NonNewable_I
  {
  private:
    void* operator new(tl_size);
    void* operator new(tl_size, void*);
    void* operator new[](tl_size);
    void* operator new[](tl_size, void*);
  };

};};};

#endif