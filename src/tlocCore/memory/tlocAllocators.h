#ifndef TLOC_ALLOCATOR_H
#define TLOC_ALLOCATOR_H

#include <tlocCore/tlocCoreBase.h>

#include <memory.h>
#include <new>

//////////////////////////////////////////////////////////////////////////
// C allocation

#include <memory.h>
  #define TL_MALLOC(tl_size)                 malloc(tl_size)
  #define TL_CALLOC(tl_numElements, tl_size) calloc(tl_numElements, tl_size)
  #define TL_REALLOC(tl_ptr, tl_size)        realloc(tl_ptr, tl_size)
  #define TL_FREE(tl_ptr)                    free(tl_ptr)

//////////////////////////////////////////////////////////////////////////
// C++ allocation
//
// All custom new/delete do not throw exceptions, regardless of parameters

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

# if defined (_MSC_VER)
void* operator new (std::size_t size);
void  operator delete (void* ptr);
void* operator new (std::size_t size, const std::nothrow_t&);
void  operator delete (void* ptr, const std::nothrow_t&);
# else
void* operator new (std::size_t size) throw(std::bad_alloc);
void  operator delete (void* ptr) throw();
void* operator new (std::size_t size, const std::nothrow_t&) throw();
void  operator delete (void* ptr, const std::nothrow_t&) throw();
# endif

namespace tloc { namespace core { namespace memory {
  namespace tracking { 

    void DoEnableLogging();
    void DoDisableLogging();

    void DoDisableTracking();

    namespace priv {

      void DoTrackMemoryAddress(void* a_memAddress);
      void DoUntrackMemoryAddress(void* a_memAddress);

      void DoTrackConnectedMemoryAddress(void* a_memAddress,
                                         void* a_connectedAddress);

      void DoTrackPointerToMemoryAddress(void* a_memAddress, void* a_ptr);
      void DoUntrackPointerToMemoryAddress(void* a_memAddress, void* a_ptr);

      bool DoIsPointerToValidMemoryAddress(void* a_ptr);
      bool DoIsMemoryAddressTracked(void* a_memAddress);

      void DoAssertPointerToValidMemoryAddress(void* a_memAddress, void* a_ptr);

      size_t DoGetNumberOfPointersToMemoryAddress(void* a_memAddress);

    };
  };
};};};

#endif // TLOC_USE_CUSTOM_NEW_DELETE

#endif
