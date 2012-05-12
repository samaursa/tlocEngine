#ifndef TLOC_TUPLE_INL
#define TLOC_TUPLE_INL

#ifndef TLOC_TUPLE_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Tuple<N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_TUPLE for (tl_size i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <typename T, tl_size T_Size>
  TL_FI Tuple<T, T_Size>::Tuple()
  {
  }

  template <typename T, tl_size T_Size>
  TL_FI Tuple<T, T_Size>::Tuple(const Tuple<T, T_Size>& aTuple)
  {
    Set(aTuple);
  }

  template <typename T, tl_size T_Size>
  template <typename T_ArrayType>
  TL_FI Tuple<T, T_Size>::Tuple(const T_ArrayType (&aArray)[T_Size])
  {
    Set(aArray);
  }

  template <typename T, tl_size T_Size>
  TL_FI Tuple<T, T_Size>::Tuple(const T& aValue)
  {
    Set(aValue);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <typename T, tl_size T_Size>
  TL_FI T& Tuple<T, T_Size>::operator [](tl_int aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, tl_size T_Size>
  TL_FI const T& Tuple<T, T_Size>::operator [](tl_int aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, tl_size T_Size>
  TL_FI T& Tuple<T, T_Size>::Get(tl_size aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, tl_size T_Size>
  TL_FI const T& Tuple<T, T_Size>::Get(tl_size aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, tl_size T_Size>
  TL_FI Tuple<T, T_Size>::operator T*()
  {
    return m_values;
  }

  template <typename T, tl_size T_Size>
  TL_FI Tuple<T, T_Size>::operator const T*() const
  {
    return m_values;
  }

  template <typename T, tl_size T_Size>
  TL_FI tl_size Tuple<T, T_Size>::GetSize() const
  {
    return k_TupleSize;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T, tl_size T_Size>
  void Tuple<T, T_Size>::Set(T aValue)
  {
    ITERATE_TUPLE
    {
      m_values[i] = aValue;
    }
  }

  template <typename T, tl_size T_Size>
  template <typename T_TupleType>
  void Tuple<T, T_Size>::Set(const Tuple<T_TupleType, T_Size>& aTuple)
  {
    // We go through the trouble of identifying the type for the sole reason of
    // letting the compiler generate type mismatch warnings

    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_TupleType), 
      Array_type_must_be_the_same_size_as_the_tuple_type);
    typedef Loki::Int2Type< Loki::IsSameType<T, T_TupleType>::value > is_same_type;

    DoSet(aTuple, is_same_type());
  }

  template <typename T, tl_size T_Size>
  template <typename T_ArrayType>
  void Tuple<T, T_Size>::Set(const T_ArrayType (&aArray)[T_Size])
  {
    // We go through the trouble of identifying the type for the sole reason of
    // letting the compiler generate type mismatch warnings

    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_ArrayType), 
      Array_type_must_be_the_same_size_as_the_tuple_type);
    typedef Loki::Int2Type< Loki::IsSameType<T, T_ArrayType>::value > is_same_type;

    DoSet(aArray, is_same_type());
  }

  template <typename T, tl_size T_Size>
  void Tuple<T, T_Size>::Swap(Tuple<T, T_Size>& aVector)
  {
    ITERATE_TUPLE
    {
      tlSwap(m_values[i], aVector[i]);
    }
  }

  //------------------------------------------------------------------------
  // Operators

  template <typename T, tl_size T_Size>
  template <typename T_TupleType>
  TL_FI Tuple<T, T_Size>& 
    Tuple<T, T_Size>::operator=(const Tuple<T_TupleType, T_Size>& aTuple)
  {
    Set(aTuple);
    return *this;
  }

  template <typename T, tl_size T_Size>
  template <typename T_ArrayType>
  TL_FI Tuple<T, T_Size>& 
    Tuple<T, T_Size>::operator=( const T_ArrayType (&aArray)[T_Size])
  {
    Set(aArray);
    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI bool Tuple<T, T_Size>::operator==( const Tuple<T, T_Size>& aTuple )
  {
    ITERATE_TUPLE
    {
      if (m_values[i] != aTuple[i]) { return false; }
    }

    return true;
  }

  template <typename T, tl_size T_Size>
  TL_FI bool Tuple<T, T_Size>::operator!=( const Tuple<T, T_Size>& aTuple )
  {
    return !operator==(aTuple);
  }

  //------------------------------------------------------------------------
  // Details

  template <typename T, tl_size T_Size>
  void Tuple<T, T_Size>::DoSet(const T (&aArray)[T_Size], type_true)
  {
    memcpy(m_values, aArray, sizeof(T) * T_Size);
  }

  template <typename T, tl_size T_Size>
  template <typename T_ArrayType>
  void Tuple<T, T_Size>::DoSet(const T_ArrayType (&aArray)[T_Size], type_false)
  {
    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_ArrayType), 
      Array_type_must_be_the_same_size_as_the_tuple_type);

    ITERATE_TUPLE
    {
      m_values[i] = aArray[i];
    }
  }

  template <typename T, tl_size T_Size>
  void Tuple<T, T_Size>::DoSet(const Tuple<T, T_Size>& aTuple, type_true)
  {
    memcpy(m_values, aTuple, sizeof(T) * T_Size);
  }

  template <typename T, tl_size T_Size>
  template <typename T_TupleType>
  void Tuple<T, T_Size>::DoSet(const Tuple<T_TupleType, T_Size>& aTuple, type_false)
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