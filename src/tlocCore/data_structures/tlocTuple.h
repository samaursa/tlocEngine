#ifndef TLOC_TUPLE_H
#define TLOC_TUPLE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <memory.h>

namespace tloc { namespace core {

  // Tuple policies
  namespace p_tuple
  {
    // The following policies determine what to do with the overflow when
    // converting between different tuple types
    struct overflow_same {};
    struct overflow_zero {};
    struct overflow_one {};
  };

  template <typename T, tl_size T_Size>
  class Tuple
  {
  public:

    typedef T                                           value_type;
    typedef tl_size                                     size_type;
    typedef Tuple<value_type, T_Size>                   this_type;

    // Empty default constructor
    TL_FI Tuple();
    TL_FI Tuple(const Tuple<T, T_Size>& aTuple);

    template <typename T_ArrayType>
    TL_FI Tuple(const T_ArrayType (&aArray)[T_Size]);

    template <template <class, class> class T_Variadic>
    TL_FI Tuple(const T_Variadic<T, tl_size>& a_vars);

    TL_FI explicit Tuple(const T& aValue);

    //------------------------------------------------------------------------
    // Accessors

    // Access range is that of an integer, approx. 2.1 billion elements.
    // If size is more than that, use the get function instead
    TL_FI value_type& operator[] (tl_int aIndex);

    // Access range is that of an integer, approx. 2.1 billion elements.
    // If size is more than that, use the get function instead
    TL_FI const value_type& operator[] (tl_int aIndex) const;

    TL_FI value_type& Get(size_type aIndex);
    TL_FI const value_type& Get(size_type aIndex) const;

    // Direct array access. Generally not recommended but useful for memcpy
    TL_FI T*        data();
    TL_FI T const*  data() const;

    // Access the size of the tuple
    TL_FI size_type GetSize() const;

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this tuple so that all values of this tuple equal aValue
    TL_FI void Set(T aValue);

    // Copies the values of the other tuple into this tuple
    template <typename T_TupleType>
    TL_FI void Set(const Tuple<T_TupleType, T_Size>& aTuple);

    // Copies the values in the array into this tuple
    template <typename T_ArrayType>
    TL_FI void Set(const T_ArrayType (&aArray)[T_Size]);

    // Swaps the tuple with the incoming vector
    TL_FI void Swap(this_type& aVector);

    // Converts between different sized tuples. The default overflow policy
    // applied here is p_tuple::overflow_one
    template <typename T_OtherValueType, tl_size T_TupleSize>
    TL_FI void ConvertFrom(const Tuple<T_OtherValueType, T_TupleSize>& a_other);

    // Converts between different sized tuples.
    template <typename T_OtherValueType, tl_size T_TupleSize, typename T_Policy>
    TL_FI void ConvertFrom(const Tuple<T_OtherValueType, T_TupleSize>& a_other,
                           T_Policy a_conversionPolicy);

    template <typename T_OtherValueType, tl_size T_TupleSize>
    TL_FI Tuple<T_OtherValueType, T_TupleSize> ConvertTo();

    // Converts between different sized tuples.
    template <typename T_OtherValueType, tl_size T_TupleSize, typename T_Policy>
    TL_FI Tuple<T_OtherValueType, T_TupleSize> ConvertTo();

    //------------------------------------------------------------------------
    // Operators

    template <typename T_TupleType>
    TL_FI Tuple<T, T_Size>& operator= (const Tuple<T_TupleType, T_Size>& aTuple);
    template <typename T_ArrayType>
    TL_FI Tuple<T, T_Size>& operator= (const T_ArrayType (&aArray)[T_Size]);

    TL_FI bool operator == (const this_type& aTuple) const;
    TL_FI bool operator != (const this_type& aTuple) const;

  protected:

    enum { k_TupleSize = T_Size};
    T m_values[k_TupleSize];

  private:

    template <typename T_ArrayType>
    TL_FI void DoSet(const T_ArrayType (&aArray)[T_Size], type_false);
    TL_FI void DoSet(const T (&aArray)[T_Size], type_true);

    template <typename T_TupleType>
    TL_FI void DoSet(const Tuple<T_TupleType, T_Size>& aTuple, type_false);
    TL_FI void DoSet(const this_type& aTuple, type_true);

    typedef type_true     incoming_bigger;
    typedef type_false    incoming_smaller;

    template <typename T_OtherValueType, tl_size T_TupleSize, typename T_Policy>
    TL_FI void DoConvertFrom(const Tuple<T_OtherValueType, T_TupleSize>& a_other,
                             incoming_bigger);

    template <typename T_OtherValueType, tl_size T_TupleSize, typename T_Policy>
    TL_FI void DoConvertFrom(const Tuple<T_OtherValueType, T_TupleSize>& a_other,
                             incoming_smaller);

    template <tl_size T_TupleSize>
    TL_FI void DoFillRemaining(p_tuple::overflow_same);
    template <tl_size T_TupleSize>
    TL_FI void DoFillRemaining(p_tuple::overflow_one);
    template <tl_size T_TupleSize>
    TL_FI void DoFillRemaining(p_tuple::overflow_zero);
  };

  typedef Tuple<tl_float,	2>    Tuple2f;
  typedef Tuple<f32,			2>    Tuple2f32;
  typedef Tuple<f64,			2>    Tuple2f64;
  typedef Tuple<tl_int,		2>    Tuple2s;
  typedef Tuple<s32,			2>    Tuple2s32;
  typedef Tuple<s64,			2>    Tuple2s64;
  typedef Tuple<tl_uint,	2>    Tuple2u;
  typedef Tuple<u32,			2>    Tuple2u32;
  typedef Tuple<u64,			2>    Tuple2u64;

  typedef Tuple<tl_float,	3>    Tuple3f;
  typedef Tuple<f32,			3>    Tuple3f32;
  typedef Tuple<f64,			3>    Tuple3f64;
  typedef Tuple<tl_int,		3>    Tuple3s;
  typedef Tuple<s32,			3>    Tuple3s32;
  typedef Tuple<s64,			3>    Tuple3s64;
  typedef Tuple<tl_uint,	3>    Tuple3u;
  typedef Tuple<u32,			3>    Tuple3u32;
  typedef Tuple<u64,			3>    Tuple3u64;

  typedef Tuple<tl_float,	4>    Tuple4f;
  typedef Tuple<f32,			4>    Tuple4f32;
  typedef Tuple<f64,			4>    Tuple4f64;
  typedef Tuple<tl_int,		4>    Tuple4s;
  typedef Tuple<s32,			4>    Tuple4s32;
  typedef Tuple<s64,			4>    Tuple4s64;
  typedef Tuple<tl_uint,	4>    Tuple4u;
  typedef Tuple<u32,			4>    Tuple4u32;
  typedef Tuple<u64,			4>    Tuple4u64;

  typedef Tuple<bool,     2>    Tuple2b;
  typedef Tuple<bool,     3>    Tuple3b;
  typedef Tuple<bool,     4>    Tuple4b;

};};

#endif