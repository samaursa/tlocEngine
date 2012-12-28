#ifndef TLOC_ALLOCATOR_INL
#define TLOC_ALLOCATOR_INL

#ifndef TLOC_ALLOCATOR_H
#error "Must include header before including the inline file"
#endif

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

# if defined (_MSC_VER)
#   define ALLOCATOR_DECL_THROW(type)
#   define ALLOCATOR_DECL_NO_THROW()
# else
#   define ALLOCATOR_DECL_THROW(type) throw(type)
#   define ALLOCATOR_DECL_NO_THROW()  throw()
# endif

  TL_FI void* operator new (std::size_t size) 
    ALLOCATOR_DECL_THROW(std::bad_alloc)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr) 
    ALLOCATOR_DECL_NO_THROW()
  {
    if (ptr) 
      TL_FREE(ptr);
  }

  TL_FI void* operator new (std::size_t size, const std::nothrow_t&) 
    ALLOCATOR_DECL_NO_THROW()
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr, const std::nothrow_t&) 
    ALLOCATOR_DECL_NO_THROW()
  {
    if (ptr) 
      TL_FREE(ptr);
  }

#endif

#endif