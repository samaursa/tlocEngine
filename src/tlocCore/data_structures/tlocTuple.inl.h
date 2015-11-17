#ifndef TLOC_TUPLE_INL
#define TLOC_TUPLE_INL

#ifndef TLOC_TUPLE_H
#error "Must include header before including the inline file"
#endif

#include "tlocTuple.h"
#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocType.h>
#include <algorithm>

#include <type_traits>

namespace tloc { namespace core { namespace data_structs {

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
  TL_FI Tuple<TUPLE_PARAMS>::
    Tuple()
  { /* Intentionally empty */ }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::
    Tuple(const this_type& aTuple)
  { Set(aTuple); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_TupleType>
  TL_FI Tuple<TUPLE_PARAMS>::
    Tuple(const Tuple<T_TupleType, k_size>& aTuple)
  { Set(aTuple); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  TL_FI Tuple<TUPLE_PARAMS>::
    Tuple(const T_ArrayType (&aArray)[k_size])
  { Set(aArray); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI Tuple<TUPLE_PARAMS>::
    Tuple(const T& aValue)
  { Set(aValue); }

  //------------------------------------------------------------------------
  // Accessors

  template <TUPLE_TEMP>
  TL_FI T& Tuple<TUPLE_PARAMS>::
    operator [](size_type aIndex)
  {
    TLOC_ASSERT(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI const T& Tuple<TUPLE_PARAMS>::
    operator [](size_type aIndex) const
  {
    TLOC_ASSERT(aIndex < T_Size, "Index is out of bounds!");
    return m_values[aIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI T& Tuple<TUPLE_PARAMS>::
    Get(tl_size aIndex)
  {
    TLOC_ASSERT(aIndex < T_Size, "Index is out of bounds!");
    return m_values[aIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI const T& Tuple<TUPLE_PARAMS>::
    Get(tl_size aIndex) const
  {
    TLOC_ASSERT(aIndex < T_Size, "Index is out of bounds!");
    return m_values[aIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI TUPLE_TYPE::value_type* Tuple<TUPLE_PARAMS>::
    data()
  { return m_values; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI TUPLE_TYPE::value_type const * Tuple<TUPLE_PARAMS>::
    data() const
  { return m_values; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  TL_FI tl_size Tuple<TUPLE_PARAMS>::
    size() const
  { return k_size; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_OtherTuple>
  TL_FI T_OtherTuple Tuple<TUPLE_PARAMS>::
    ConvertTo() const
  {
    T_OtherTuple toRet;
    toRet.ConvertFrom(*this);
    return toRet;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_OtherTuple, typename T_Policy>
  TL_FI T_OtherTuple Tuple<TUPLE_PARAMS>::
    ConvertTo() const
  {
    TLOC_STATIC_ASSERT_SUPPORTED(T_Policy, 
                                 p_tuple::overflow_one, p_tuple::overflow_zero);

    T_OtherTuple toRet;
    toRet.ConvertFrom(*this, T_Policy());
    return toRet;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  namespace {
    typedef std::true_type       typesAreSame;
    typedef std::false_type      typesAreDifferent;

    template <typename T_OtherType, typename T_ValueType,
              tl_size T_Size>
    const Tuple<T_OtherType, T_Size>&
      DoCast(const Tuple<T_ValueType, T_Size>& a_tuple, typesAreSame)
    {
      return a_tuple;
    }

    template <typename T_OtherType, typename T_ValueType,
              tl_size T_Size>
    Tuple<T_OtherType, T_Size>
      DoCast(const Tuple<T_ValueType, T_Size>& a_tuple, typesAreDifferent)
    {
      Tuple<T_OtherType, T_Size> temp;
      for(tl_int i = 0; i < T_Size; ++i)
      {
        temp[i] = core_utils::
          cast_number<T_OtherType, T_ValueType>(a_tuple[i]);
      }

      return temp;
    }
  }


  template <TUPLE_TEMP>
  template <typename T_TupleType>
  T_TupleType
    Tuple<TUPLE_PARAMS>::
    Cast() const
  {
    typedef typename T_TupleType::value_type                  other_value_type;
    typedef std::is_same<value_type, other_value_type>        type_result;
    typedef std::integral_constant<bool, type_result::value>  types_same_or_not;

    TLOC_STATIC_ASSERT((T_TupleType::k_size == k_size),
                        "Tuple sizes must be the same");

    return DoCast<other_value_type, value_type, T_Size>
      (*this, types_same_or_not());
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::
    Set(T aValue)
  {
    ITERATE_TUPLE
    { m_values[i] = aValue; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_TupleType>
  void Tuple<TUPLE_PARAMS>::
    Set(const Tuple<T_TupleType, T_Size>& aTuple)
  {
    DoSet(aTuple, std::is_same<T, T_TupleType>::type());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  void Tuple<TUPLE_PARAMS>::
    Set(const T_ArrayType (&aArray)[T_Size])
  {
    DoSet(aArray, std::is_same<T, T_ArrayType>::type());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::
    Swap(this_type& aVector)
  {
    ITERATE_TUPLE
    { core::swap(m_values[(tl_int)i], aVector[(tl_int)i]); }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_OtherTuple, typename T_Policy>
  void Tuple<TUPLE_PARAMS>::
    DoConvertFrom(const T_OtherTuple& a_other,
                  incoming_bigger)
  {
    for (tl_int i = 0; i < k_size; ++i)
    { m_values[i] = core_utils::cast_number<value_type>(a_other[i]); }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_OtherTuple, typename T_Policy>
  void Tuple<TUPLE_PARAMS>::
    DoConvertFrom(const T_OtherTuple& a_other,
                  incoming_smaller)
  {
    for (tl_int i = 0; i < T_OtherTuple::k_size; ++i)
    { m_values[i] = core_utils::cast_number<value_type>(a_other[i]); }

    DoFillRemaining<T_OtherTuple::k_size>(T_Policy());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <tl_size T_TupleSize>
  void Tuple<TUPLE_PARAMS>::
    DoFillRemaining(p_tuple::overflow_same)
  { /* Intentionally empty */ }

  template <TUPLE_TEMP>
  template <tl_size T_TupleSize>
  void Tuple<TUPLE_PARAMS>::
    DoFillRemaining(p_tuple::overflow_one)
  {
    for (tl_int i = T_TupleSize; i < k_size; ++i)
    { m_values[i] = 1; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <tl_size T_TupleSize>
  void Tuple<TUPLE_PARAMS>::
    DoFillRemaining(p_tuple::overflow_zero)
  {
    for (tl_int i = T_TupleSize; i < k_size; ++i)
    { m_values[i] = 0; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_OtherValueType, tl_size T_TupleSize>
  void Tuple<TUPLE_PARAMS>::
    ConvertFrom(const Tuple<T_OtherValueType, T_TupleSize>& a_other)
  {
    DoConvertFrom<Tuple<T_OtherValueType, T_TupleSize>, p_tuple::overflow_one>
      (a_other, type_traits::bool_constant<k_size < T_TupleSize>());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_OtherValueType, tl_size T_TupleSize, typename T_Policy>
  void Tuple<TUPLE_PARAMS>::
    ConvertFrom(const Tuple<T_OtherValueType, T_TupleSize>& a_other,
                T_Policy)
  {
    TLOC_STATIC_ASSERT_SUPPORTED (T_Policy, 
      p_tuple::overflow_one, p_tuple::overflow_same, p_tuple::overflow_zero);

    DoConvertFrom<Tuple<T_OtherValueType, T_TupleSize>, T_Policy>
      (a_other, type_traits::bool_constant<k_size < T_TupleSize>());
  }

  //------------------------------------------------------------------------
  // Operators

  template <TUPLE_TEMP>
  bool Tuple<TUPLE_PARAMS>::
    operator==( const this_type& aTuple ) const
  {
    ITERATE_TUPLE
    { if (m_values[(tl_int)i] != aTuple[(tl_int)i]) { return false; } }

    return true;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  bool Tuple<TUPLE_PARAMS>::
    operator!=( const this_type& aTuple ) const
  { return !operator==(aTuple); }

  //------------------------------------------------------------------------
  // Details

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::
    DoSet(const T (&aArray)[T_Size], std::true_type)
  { core_mem::MemCopy(m_values, aArray, T_Size); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_ArrayType>
  void Tuple<TUPLE_PARAMS>::
    DoSet(const T_ArrayType (&aArray)[T_Size], std::false_type)
  {
    TLOC_STATIC_ASSERT(sizeof(T) == sizeof(T_ArrayType),
      Array_type_must_be_the_same_size_as_the_tuple_type);

    ITERATE_TUPLE
    { m_values[i] = aArray[i]; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  void Tuple<TUPLE_PARAMS>::
    DoSet(const this_type& aTuple, std::true_type)
  { core_mem::MemCopy(m_values, aTuple.data(), T_Size); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TUPLE_TEMP>
  template <typename T_TupleType>
  void Tuple<TUPLE_PARAMS>::
    DoSet(const Tuple<T_TupleType, T_Size>& aTuple, std::false_type)
  {
    ITERATE_TUPLE
    { m_values[i] = core_utils::cast_number<value_type>(aTuple[i]); }
  }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_TUPLE(_type_, _size_)\
  template class tloc::core_ds::Tuple<_type_, _size_>

#endif
