#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocCore/memory/tlocAllocators.h>

#ifndef TLOC_BASE_H
# error "Must include tlocBase.h before including tlocMemory.h"
#endif

namespace tloc { namespace core {

  namespace memory
  {
    extern bool IsValidHeapPointer(const void * a_userData);
  };

  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    uninitialized_copy(T_InputIterator aRangeBegin,
                       T_InputIterator aRangeEnd,
                       T_OutputIterator aDestRangeBegin);

  template <typename T_InputIterator, typename T_Count, typename T_ValueType>
  void
    uninitialized_fill_n(T_InputIterator a_first,
                         T_Count a_count,
                         const T_ValueType& a_value);

  namespace detail {

    typedef type_true       IsRawItr;
    typedef type_false      IsComplexItr;
    typedef type_true       HasTrivalAssign;
    typedef type_false      HasComplexAssign;

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsRawItr);

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsComplexItr);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    T_OutputIterator
      DoUninitializedCopyWithValueType(T_InputIterator a_rangeBegin,
                                       T_InputIterator a_rangeEnd,
                                       T_OutputIterator a_destRangeBegin,
                                       T_ValueType);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    T_OutputIterator
      DoUninitializedCopy(T_InputIterator aRangeBegin,
                          T_InputIterator aRangeEnd,
                          T_OutputIterator aDestRangeBegin,
                          T_ValueType,
                          HasTrivalAssign);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    T_OutputIterator
      DoUninitializedCopy(T_InputIterator aRangeBegin,
                          T_InputIterator aRangeEnd,
                          T_OutputIterator aDestRangeBegin,
                          T_ValueType,
                          HasComplexAssign);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    void
      DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                      T_Count a_count,
                                      const T_ValueType& a_value,
                                      IsRawItr);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    void
      DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                      T_Count a_count,
                                      const T_ValueType& a_value,
                                      IsComplexItr);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillNWithValueType(T_InputIterator a_first,
                                        T_Count a_count,
                                        const T_ValueType& a_value,
                                        T_ValueTypeInputIterator);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillN(T_InputIterator a_first,
                           T_Count a_count,
                           const T_ValueType& a_value,
                           T_ValueTypeInputIterator,
                           HasTrivalAssign);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillN(T_InputIterator a_first,
                           T_Count a_count,
                           const T_ValueType& a_value,
                           T_ValueTypeInputIterator,
                           HasComplexAssign);
  };

};};


#endif  // TLOC_MEMORY_H
