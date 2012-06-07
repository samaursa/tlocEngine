#ifndef TLOC_TUPLE_H
#define TLOC_TUPLE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <memory.h>

namespace tloc { namespace core {

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
    TL_FI operator T* ();
    TL_FI operator const T* () const;

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

    //------------------------------------------------------------------------
    // Operators

    template <typename T_TupleType>
    TL_FI Tuple<T, T_Size>& operator= (const Tuple<T_TupleType, T_Size>& aTuple);
    template <typename T_ArrayType>
    TL_FI Tuple<T, T_Size>& operator= (const T_ArrayType (&aArray)[T_Size]);

    TL_FI bool operator == (const this_type& aTuple);
    TL_FI bool operator != (const this_type& aTuple);

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
  };

};};

#ifdef TLOC_FULL_SOURCE
#include <tlocCore/data_structures/tlocTuple.inl>
#endif


#endif