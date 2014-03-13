#include "tlocAllocators.h"

#include <tlocCore/smart_ptr/tlocSmartPtrTracker.h>

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
  using namespace tloc;

  if (ptr)
  {
    TLOC_ASSERT(core_sptr::priv::DoIsPointerTracked(ptr) == false,
                "Pointer currently being tracked/used by a SmartPtr");
    TLOC_ASSERT(core_sptr::priv::DoIsPointerTrackedVirtually(ptr) == false,
                "Pointer currently being tracked/used by VirtualPtr");
    TL_FREE(ptr);
  }
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
  using namespace tloc;

  if (ptr)
  {
    TLOC_ASSERT(core_sptr::priv::DoIsPointerTracked(ptr) == 0,
                "Pointer currently being tracked/used");
    TLOC_ASSERT(core_sptr::priv::DoIsPointerTrackedVirtually(ptr) == false,
                "Pointer currently being tracked/used by VirtualPtr");
    TL_FREE(ptr);
  }
}

#endif