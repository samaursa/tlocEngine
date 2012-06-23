#ifndef TLOC_ALLOCATOR_INL
#define TLOC_ALLOCATOR_INL

#ifndef TLOC_ALLOCATOR_H
#error "Must include header before including the inline file"
#endif

// Visual C++ does not implement checked exceptions, which is needed when
// overloading new and delete operators with the GCC compiler. 
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4290) 
#endif

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

  TL_FI void* operator new (std::size_t size) throw(std::bad_alloc)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr) throw()
  {
    TL_FREE(ptr);
  }

  TL_FI void* operator new (std::size_t size, const std::nothrow_t&) throw()
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr, const std::nothrow_t&) throw()
  {
    TL_FREE(ptr);
  }

#endif

#if _MSC_VER
#pragma warning(pop)
#endif

#endif