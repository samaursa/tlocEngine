#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocAlgorithms.h"
#include <memory.h>
#include <new>

#ifndef TLOC_BASE_H
# error "Must include tlocBase.h before including tlocMemory.h"
#endif

//////////////////////////////////////////////////////////////////////////
// C allocation

#ifdef TLOC_USING_NED_MALLOC
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

  void* operator new (std::size_t size);
  void  operator delete (void* ptr);
  void* operator new (std::size_t size, const std::nothrow_t&);
  void  operator delete (void* ptr, const std::nothrow_t&);

#endif // TLOC_USE_CUSTOM_NEW_DELETE

namespace tloc { namespace core {

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator uninitialized_copy(T_InputIterator aRangeBegin,
                                           T_InputIterator aRangeEnd,
                                           T_OutputIterator aDestRangeBegin);

  namespace detail {

    typedef type_true hasTrivalAssign;
    typedef type_false hasComplexAssign;

    template <typename T_InputIterator, typename T_OutputIterator, typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy (T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin,
                                               T_ValueType,
                                               hasTrivalAssign);

    template <typename T_InputIterator, typename T_OutputIterator, typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy (T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin,
                                               T_ValueType,
                                               hasComplexAssign);




  };

};};


#endif  // TLOC_MEMORY_H