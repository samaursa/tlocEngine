#ifndef TLOC_MEMORY_INL
#define TLOC_MEMORY_INL

#ifndef TLOC_MEMORY_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.inl"

namespace tloc { namespace core {

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

  TL_FI void* operator new (std::size_t size)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr)
  {
    TL_FREE(ptr);
  }

  TL_FI void* operator new (std::size_t size, const std::nothrow_t&)
  {
    void *ptr = TL_MALLOC(size);
    return ptr; // Not throwing on purpose
  }

  TL_FI void operator delete (void* ptr, const std::nothrow_t&)
  {
    TL_FREE(ptr);
  }

#endif

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator uninitialized_copy(T_InputIterator aRangeBegin, 
                                           T_InputIterator aRangeEnd, 
                                           T_OutputIterator aDestRangeBegin)
  {
    typedef Loki::TypeTraits<T_OutputIterator> unknown_type;
    typedef Loki::Int2Type<unknown_type::isPointer> pointer_type;

    return detail::DoUninitializedCopyWithItrType(aRangeBegin, aRangeEnd, 
                                                  aDestRangeBegin, pointer_type());
  }

  template <typename T_InputIterator, typename T_Count, typename T_ValueType>
  TL_I void uninitialized_fill_n(T_InputIterator a_first, 
                                 T_Count a_count, 
                                 const T_ValueType& a_value)
  {
    typedef Loki::TypeTraits<T_InputIterator> unknown_type;
    typedef Loki::Int2Type<unknown_type::isPointer> pointer_type;

    detail::DoUninitializedFillNWithItrType(a_first, a_count, 
                                            a_value, pointer_type());
  }

  namespace detail {

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator 
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin, 
                                     T_InputIterator a_rangeEnd, 
                                     T_OutputIterator a_destRangeBegin, 
                                     IsRawItr)
    {
      typedef Loki::TypeTraits<T_OutputIterator>::PointeeType value_type;
      return DoUninitializedCopyWithValueType(a_rangeBegin, 
                                              a_rangeEnd, 
                                              a_destRangeBegin, 
                                              value_type());
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator 
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin, 
                                     T_InputIterator a_rangeEnd, 
                                     T_OutputIterator a_destRangeBegin, 
                                     IsComplexItr)
    {
      typedef T_OutputIterator::value_type value_type;
      return DoUninitializedCopyWithValueType(a_rangeBegin,
                                              a_rangeEnd,
                                              a_destRangeBegin,
                                              value_type());
    }

    template <typename T_InputIterator, typename T_OutputIterator, 
              typename T_ValueType>
    TL_I T_OutputIterator 
      DoUninitializedCopyWithValueType(T_InputIterator a_rangeBegin, 
                                       T_InputIterator a_rangeEnd, 
                                       T_OutputIterator a_destRangeBegin, 
                                       T_ValueType)
    {
      //TODO: Add proper checks for POD types.
      typedef Loki::TypeTraits<T_ValueType> value_type_traits;
      typedef Loki::Int2Type<value_type_traits::isArith &&
                             !(value_type_traits::isConst) &&
                             !(value_type_traits::isVolatile)> 
                             assign_type;

      return DoUninitializedCopy(a_rangeBegin, 
                                 a_rangeEnd, 
                                 a_destRangeBegin,
                                 T_ValueType(),
                                 assign_type());
    }

    template <typename T_InputIterator, typename T_OutputIterator, 
              typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy (T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin,
                                               T_ValueType,
                                               HasTrivalAssign)
    {
      return tloc::core::copy(aRangeBegin, aRangeEnd, aDestRangeBegin);
    }

    template <typename T_InputIterator, typename T_OutputIterator, 
              typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy (T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin,
                                               T_ValueType,
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
    TL_I void DoUninitializedFillNWithItrType(T_InputIterator a_first, 
                                              T_Count a_count, 
                                              const T_ValueType& a_value, 
                                              IsRawItr)
    {
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoUninitializedFillNWithValueType(a_first, a_count, a_value, value_type());
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoUninitializedFillNWithItrType(T_InputIterator a_first, 
                                              T_Count a_count, 
                                              const T_ValueType& a_value, 
                                              IsComplexItr)
    {
      typedef T_InputIterator::value_type value_type;
      DoUninitializedFillNWithValueType(a_first, a_count, a_value, value_type());
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    TL_I void DoUninitializedFillNWithValueType(T_InputIterator a_first, 
                                                T_Count a_count, 
                                                const T_ValueType& 
                                                a_value, 
                                                T_ValueTypeInputIterator)
    {
      //TODO: Add proper checks for POD types.
      typedef Loki::TypeTraits<T_ValueTypeInputIterator> value_type_traits;
      typedef Loki::Int2Type<value_type_traits::isArith &&
                             !(value_type_traits::isConst) &&
                             !(value_type_traits::isVolatile)>
                             assign_type;

      detail::DoUninitializedFillN(a_first, a_count, a_value, 
                                   T_ValueType(), assign_type());
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    TL_I void DoUninitializedFillN(T_InputIterator a_first, 
                                   T_Count a_count, 
                                   const T_ValueType& a_value,
                                   T_ValueTypeInputIterator,
                                   HasTrivalAssign)
    {
      tloc::core::fill_n(a_first, a_count, a_value);
    }

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    TL_I void DoUninitializedFillN(T_InputIterator a_first, 
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