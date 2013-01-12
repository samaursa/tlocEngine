#include "tlocMemory.h"
#include "tlocMemory.inl"

#ifdef TLOC_OS_WIN
  #include <crtdbg.h>
#endif

namespace tloc { namespace core {

  namespace memory
  {
    bool IsValidHeapPointer(const void * a_userData)
    {
      TLOC_UNUSED(a_userData);
#if defined(TLOC_USING_STD_ALLOC) && defined(TLOC_OS_WIN)
      return _CrtIsValidHeapPointer(a_userData) == 0 ? false : true;
#else
      return true;
#endif
    }
  };

};};