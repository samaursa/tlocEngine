#ifndef TLOC_MEMORY_INL
#define TLOC_MEMORY_INL

#ifndef TLOC_MEMORY_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl.h>

namespace tloc { namespace core {


  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    uninitialized_copy(T_InputIterator aRangeBegin,
                       T_InputIterator aRangeEnd,
                       T_OutputIterator aDestRangeBegin)
  {
    typedef typename Loki::TypeTraits<T_OutputIterator> unknown_type;
    typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

    return detail::DoUninitializedCopyWithItrType(aRangeBegin, aRangeEnd,
                                                  aDestRangeBegin, pointer_type());
  }

  template <typename T_InputIterator, typename T_Count, typename T_ValueType>
  void
    uninitialized_fill_n(T_InputIterator a_first,
                         T_Count a_count,
                         const T_ValueType& a_value)
  {
    typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
    typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

    detail::DoUninitializedFillNWithItrType(a_first, a_count,
                                            a_value, pointer_type());
  }

  namespace detail {

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsRawItr)
    {
      typedef typename Loki::TypeTraits<T_OutputIterator>::PointeeType value_type;
      return DoUninitializedCopyWithValueType<value_type>
        (a_rangeBegin, a_rangeEnd, a_destRangeBegin);
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsComplexItr)
    {
      typedef typename T_OutputIterator::value_type value_type;
      return DoUninitializedCopyWithValueType<value_type>
        (a_rangeBegin, a_rangeEnd, a_destRangeBegin);
    }

    template <typename T_ValueType, typename T_InputIterator, 
              typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithValueType(T_InputIterator a_rangeBegin,
                                       T_InputIterator a_rangeEnd,
                                       T_OutputIterator a_destRangeBegin)
    {
      //TODO: Add proper checks for POD types.
      typedef typename Loki::TypeTraits<T_ValueType> value_type_traits;
      typedef typename Loki::Int2Type<value_type_traits::isArith &&
                             !(value_type_traits::isConst) &&
                             !(value_type_traits::isVolatile)>
                             assign_type;

      return DoUninitializedCopy<T_ValueType>
        (a_rangeBegin, a_rangeEnd, a_destRangeBegin, assign_type());
    }

    template <typename T_ValueType, typename T_InputIterator, 
              typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopy (T_InputIterator aRangeBegin,
                           T_InputIterator aRangeEnd,
                           T_OutputIterator aDestRangeBegin,
                           HasTrivalAssign)
    {
      return tloc::core::copy(aRangeBegin, aRangeEnd, aDestRangeBegin);
    }

    template <typename T_ValueType, typename T_InputIterator, 
              typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopy (T_InputIterator aRangeBegin,
                           T_InputIterator aRangeEnd,
                           T_OutputIterator aDestRangeBegin,
                           HasComplexAssign)
    {
      T_OutputIterator currentDestination(aDestRangeBegin);

      for (/* */; aRangeBegin != aRangeEnd; ++aRangeBegin, ++currentDestination)
      {
        new(&*currentDestination) T_ValueType(*aRangeBegin);
      }

      return currentDestination;
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    void
      DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                      T_Count a_count,
                                      const T_ValueType& a_value,
                                      IsRawItr)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoUninitializedFillNWithValueType(a_first, a_count, a_value, value_type());
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    void
      DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                      T_Count a_count,
                                      const T_ValueType& a_value,
                                      IsComplexItr)
    {
      typedef typename T_InputIterator::value_type value_type;
      DoUninitializedFillNWithValueType(a_first, a_count, a_value, value_type());
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillNWithValueType(T_InputIterator a_first,
                                        T_Count a_count,
                                        const T_ValueType&
                                        a_value,
                                        T_ValueTypeInputIterator)
    {
      //TODO: Add proper checks for POD types.
      typedef typename Loki::TypeTraits<T_ValueTypeInputIterator> value_type_traits;
      typedef typename Loki::Int2Type<value_type_traits::isArith &&
                             !(value_type_traits::isConst) &&
                             !(value_type_traits::isVolatile)>
                             assign_type;

      detail::DoUninitializedFillN(a_first, a_count, a_value,
                                   T_ValueType(), assign_type());
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillN(T_InputIterator a_first,
                           T_Count a_count,
                           const T_ValueType& a_value,
                           T_ValueTypeInputIterator,
                           HasTrivalAssign)
    {
      tloc::core::fill_n(a_first, a_count, a_value);
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillN(T_InputIterator a_first,
                           T_Count a_count,
                           const T_ValueType& a_value,
                           T_ValueTypeInputIterator,
                           HasComplexAssign)
    {
      T_InputIterator currentDestination(a_first);

      for (/* */; a_count > 0; --a_count, ++currentDestination)
      {
        new(&*currentDestination) T_ValueTypeInputIterator(a_value);
      }
    }
  }

};};


#endif
