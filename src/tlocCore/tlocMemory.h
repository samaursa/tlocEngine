#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include "tlocBase.h"
#include <memory.h>
#include <new>

#ifndef TLOC_BASE_H
# error "Must include tlocBase.h before including tlocMemory.h"
#endif

//////////////////////////////////////////////////////////////////////////
// C allocation

#ifdef TLOC_USING_NED_MALLOC
// Check to make sure we are not using CRT memory
#   include <3rdParty/nedmalloc/nedmalloc.h>
#   define TL_MALLOC(tl_size)                 nedalloc::nedmalloc(tl_size)
#   define TL_CALLOC(tl_numElements, tl_size) nedalloc::nedcalloc(tl_numElements, tl_size)
#   define TL_REALLOC(tl_ptr, tl_size)        nedalloc::nedrealloc(tl_ptr, tl_size)
#   define TL_FREE(tl_ptr)                    nedalloc::nedfree(tl_ptr)

#else   // TLOC_USING_NED_MALLOC
#   include <memory.h>
#   define TL_MALLOC(tl_size)                 malloc(tl_size)
#   define TL_CALLOC(tl_numElements, tl_size) calloc(tl_numElements, tl_size)
#   define TL_REALLOC(tl_ptr, tl_size)        realloc(tl_ptr, tl_size)
#   define TL_FREE(tl_ptr)                    free(tl_ptr)
#endif  // TLOC_USING_NED_MALLOC

//////////////////////////////////////////////////////////////////////////
// C++ allocation
//
// All custom new/delete do not throw exceptions, regardless of parameters

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

#endif // TLOC_USE_CUSTOM_NEW_DELETE

#endif  // TLOC_MEMORY_H