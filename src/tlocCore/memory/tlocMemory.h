#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>

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
  TL_I T_OutputIterator     uninitialized_copy(T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin);

  template <typename T_InputIterator, typename T_Count, typename T_ValueType>
  TL_I void                 uninitialized_fill_n(T_InputIterator a_first,
                                                 T_Count a_count,
                                                 const T_ValueType& a_value);

  namespace detail {

    typedef type_true       IsRawItr;
    typedef type_false      IsComplexItr;
    typedef type_true       HasTrivalAssign;
    typedef type_false      HasComplexAssign;

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsRawItr);

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsComplexItr);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    TL_I T_OutputIterator
      DoUninitializedCopyWithValueType(T_InputIterator a_rangeBegin,
                                       T_InputIterator a_rangeEnd,
                                       T_OutputIterator a_destRangeBegin,
                                       T_ValueType);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy(T_InputIterator aRangeBegin,
                                              T_InputIterator aRangeEnd,
                                              T_OutputIterator aDestRangeBegin,
                                              T_ValueType,
                                              HasTrivalAssign);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    TL_I T_OutputIterator   DoUninitializedCopy(T_InputIterator aRangeBegin,
                                                T_InputIterator aRangeEnd,
                                                T_OutputIterator aDestRangeBegin,
                                                T_ValueType,
                                                HasComplexAssign);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                              T_Count a_count,
                                              const T_ValueType& a_value,
                                              IsRawItr);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                              T_Count a_count,
                                              const T_ValueType& a_value,
                                              IsComplexItr);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    TL_I void DoUninitializedFillNWithValueType(T_InputIterator a_first,
                                                T_Count a_count,
                                                const T_ValueType& a_value,
                                                T_ValueTypeInputIterator);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    TL_I void               DoUninitializedFillN(T_InputIterator a_first,
                                                 T_Count a_count,
                                                 const T_ValueType& a_value,
                                                 T_ValueTypeInputIterator,
                                                 HasTrivalAssign);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    TL_I void               DoUninitializedFillN(T_InputIterator a_first,
                                                 T_Count a_count,
                                                 const T_ValueType& a_value,
                                                 T_ValueTypeInputIterator,
                                                 HasComplexAssign);
  };

};};


#endif  // TLOC_MEMORY_H