#ifndef TLOC_TUPLE_INL
#define TLOC_TUPLE_INL

#ifndef TLOC_TUPLE_H
#error "Must include header before including the inline file"
#endif

#include "tlocTemplateUtils.h"

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Tuple<N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_TUPLE for (tl_size i = 0; i < T_Size; ++i)

#define TUPLE_TEMP   typename T, tl_size T_Size
#define TUPLE_PARAMS T, T_Size
#define TUPLE_TYPE   typename Tuple<TUPLE_PARAMS>

  //------------------------------------------------------------------------
  // Constructors

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::Tuple()
  {
  }

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::Tuple(const this_type& aTuple)
  {
    Set(aTuple);
  }

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  TL_FI Tuple<TUPLE_PARAMS>::Tuple(const T_ArrayType (&aArray)[T_Size])
  {
    Set(aArray);
  }

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::Tuple(const T& aValue)
  {
    Set(aValue);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <TUPLE_TEMP>
  TL_FI T& Tuple<TUPLE_PARAMS>::operator [](tl_int aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <TUPLE_TEMP>
  TL_FI const T& Tuple<TUPLE_PARAMS>::operator [](tl_int aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <TUPLE_TEMP>
  TL_FI T& Tuple<TUPLE_PARAMS>::Get(tl_size aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <TUPLE_TEMP>
  TL_FI const T& Tuple<TUPLE_PARAMS>::Get(tl_size aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::operator T*()
  {
    return m_values;
  }

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::operator const T*() const
  {
    return m_values;
  }

  template <TUPLE_TEMP>
  TL_FI tl_size Tuple<TUPLE_PARAMS>::GetSize() const
  {
    return k_TupleSize;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::Set(T aValue)
  {
    ITERATE_TUPLE
    {
      m_values[i] = aValue;
    }
  }

  template <TUPLE_TEMP>
  template <typename T_TupleType>
  void Tuple<TUPLE_PARAMS>::Set(const Tuple<T_TupleType, T_Size>& aTuple)
  {
    // We go through the trouble of identifying the type for the sole reason of
    // letting the compiler generate type mismatch warnings

    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_TupleType), 
      Array_type_must_be_the_same_size_as_the_tuple_type);
    typedef Loki::Int2Type< Loki::IsSameType<T, T_TupleType>::value > is_same_type;

    DoSet(aTuple, is_same_type());
  }

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  void Tuple<TUPLE_PARAMS>::Set(const T_ArrayType (&aArray)[T_Size])
  {
    // We go through the trouble of identifying the type for the sole reason of
    // letting the compiler generate type mismatch warnings

    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_ArrayType), 
      Array_type_must_be_the_same_size_as_the_tuple_type);
    typedef Loki::Int2Type< Loki::IsSameType<T, T_ArrayType>::value > is_same_type;

    DoSet(aArray, is_same_type());
  }

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::Swap(this_type& aVector)
  {
    ITERATE_TUPLE
    {
      tlSwap(m_values[(tl_int)i], aVector[(tl_int)i]);
    }
  }

  //------------------------------------------------------------------------
  // Operators

  template <TUPLE_TEMP>
  template <typename T_TupleType>
  TL_FI Tuple<TUPLE_PARAMS>& 
    Tuple<TUPLE_PARAMS>::operator=(const Tuple<T_TupleType, T_Size>& aTuple)
  {
    Set(aTuple);
    return *this;
  }

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  TL_FI Tuple<TUPLE_PARAMS>& 
    Tuple<TUPLE_PARAMS>::operator=( const T_ArrayType (&aArray)[T_Size])
  {
    Set(aArray);
    return *this;
  }

  template <TUPLE_TEMP>
  TL_FI bool Tuple<TUPLE_PARAMS>::operator==( const this_type& aTuple )
  {
    ITERATE_TUPLE
    {
      if (m_values[(tl_int)i] != aTuple[(tl_int)i]) { return false; }
    }

    return true;
  }

  template <TUPLE_TEMP>
  TL_FI bool Tuple<TUPLE_PARAMS>::operator!=( const this_type& aTuple )
  {
    return !operator==(aTuple);
  }

  //------------------------------------------------------------------------
  // Details

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::DoSet(const T (&aArray)[T_Size], type_true)
  {
    memcpy(m_values, aArray, sizeof(T) * T_Size);
  }

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  void Tuple<TUPLE_PARAMS>::DoSet(const T_ArrayType (&aArray)[T_Size], type_false)
  {
    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_ArrayType), 
      Array_type_must_be_the_same_size_as_the_tuple_type);

    ITERATE_TUPLE
    {
      m_values[i] = aArray[i];
    }
  }

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::DoSet(const this_type& aTuple, type_true)
  {
    memcpy(m_values, aTuple, sizeof(T) * T_Size);
  }

  template <TUPLE_TEMP>
  template <typename T_TupleType>
  void Tuple<TUPLE_PARAMS>::DoSet(const Tuple<T_TupleType, T_Size>& aTuple, type_false)
  {
    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_TupleType), 
      Tuple_type_must_be_the_same_size_as_this_tuple_type);

    ITERATE_TUPLE
    {
      m_values[i] = aTuple[i];
    }
  }


};};

#endif