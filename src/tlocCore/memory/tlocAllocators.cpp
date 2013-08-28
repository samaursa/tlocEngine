#include "tlocAllocators.h"

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

# if defined (_MSC_VER)
#   define ALLOCATOR_DECL_THROW(type)
#   define ALLOCATOR_DECL_NO_THROW()
# else
#   define ALLOCATOR_DECL_THROW(type) throw(type)
#   define ALLOCATOR_DECL_NO_THROW()  throw()
# endif

void* operator new (std::size_t size)
ALLOCATOR_DECL_THROW(std::bad_alloc)
{
  void *ptr = TL_MALLOC(size);
  return ptr; // Not throwing on purpose
}

void operator delete (void* ptr)
ALLOCATOR_DECL_NO_THROW()
{
  if (ptr)
    TL_FREE(ptr);
}

void* operator new (std::size_t size, const std::nothrow_t&)
ALLOCATOR_DECL_NO_THROW()
{
  void *ptr = TL_MALLOC(size);
  return ptr; // Not throwing on purpose
}

void operator delete (void* ptr, const std::nothrow_t&)
ALLOCATOR_DECL_NO_THROW()
{
  if (ptr)
    TL_FREE(ptr);
}

#endif