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
    //TODO: Add proper checks for POD types.
    typedef Loki::TypeTraits<T_OutputIterator>::PointeeType value_type;
    typedef Loki::TypeTraits<value_type> value_type_traits;
    typedef Loki::Int2Type<value_type_traits::isArith &&
                           !(value_type_traits::isConst) &&
                           !(value_type_traits::isVolatile)> 
                           assign_type;

    return detail::DoUninitializedCopy(aRangeBegin, 
                               aRangeEnd, 
                               aDestRangeBegin,
                               value_type(),
                               assign_type());
  }

  namespace detail {

    template <typename T_InputIterator, typename T_OutputIterator, typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy (T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin,
                                               T_ValueType,
                                               hasTrivalAssign)
    {
      return tloc::core::copy(aRangeBegin, aRangeEnd, aDestRangeBegin);
    }

    template <typename T_InputIterator, typename T_OutputIterator, typename T_ValueType>
    TL_I T_OutputIterator DoUninitializedCopy (T_InputIterator aRangeBegin,
                                               T_InputIterator aRangeEnd,
                                               T_OutputIterator aDestRangeBegin,
                                               T_ValueType,
                                               hasComplexAssign)
    {
      T_OutputIterator currentDestination(aDestRangeBegin);

      for (/* */; aRangeBegin != aRangeEnd; ++aRangeBegin, ++currentDestination)
      {
        new(&*currentDestination) T_ValueType(*aRangeBegin);
      }

      return currentDestination;
    }


  }

};};


#endif