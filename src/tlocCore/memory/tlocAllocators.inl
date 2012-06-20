#ifndef TLOC_ALLOCATOR_INL
#define TLOC_ALLOCATOR_INL

#ifndef TLOC_ALLOCATOR_H
#error "Must include header before including the inline file"
#endif

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

  TL_FI void* operator new (std::size_t size)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr)
  {
    TL_FREE(ptr);
  }

  TL_FI void* operator new (std::size_t size, const std::nothrow_t&)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr, const std::nothrow_t&)
  {
    TL_FREE(ptr);
  }

#endif

#endif