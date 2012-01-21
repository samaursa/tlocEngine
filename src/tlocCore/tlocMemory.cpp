#include "tlocMemory.h"
#include "tlocMemory.inl"

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

  void* operator new (std::size_t size)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  void operator delete (void* ptr)
  {
    TL_FREE(ptr);
  }

  void* operator new (std::size_t size, const std::nothrow_t&)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  void operator delete (void* ptr, const std::nothrow_t&)
  {
    TL_FREE(ptr);
  }

#endif