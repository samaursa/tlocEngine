#ifndef TLOC_TUPLE_H
#define TLOC_TUPLE_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocAlgorithms.h"
#include <memory.h>

namespace tloc { namespace core {

  template <typename T, u32 T_Size>
  class Tuple
  {
  public:

    // Empty default constructor
    TL_FI Tuple();
    TL_FI Tuple(const Tuple<T, T_Size>& aTuple);

    TL_FI explicit Tuple(const T& aValue);

    //------------------------------------------------------------------------
    // Accessors

    // Access range is that of an integer, approx. 2.1 billion elements.
    // If size is more than that, use the get function instead
    TL_FI T& operator[] (s32 aIndex);

    // Access range is that of an integer, approx. 2.1 billion elements.
    // If size is more than that, use the get function instead
    TL_FI const T& operator[] (s32 aIndex) const;

    TL_FI T& Get(u32 aIndex);
    TL_FI const T& Get(u32 aIndex) const;

    // Direct array access. Generally not recommended but useful for memcpy
    TL_FI operator T* ();
    TL_FI operator const T* () const;

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this tuple so that all values of this tuple equal aValue
    TL_FI void Set(T aValue);

    // Swaps the tuple with the incoming vector
    TL_FI void Swap(Tuple<T, T_Size>& aVector);

    //------------------------------------------------------------------------
    // Operators

    TL_FI Tuple<T, T_Size>& operator= (const Tuple<T, T_Size>& aTuple);
    TL_FI bool operator == (const Tuple<T, T_Size>& aTuple);
    TL_FI bool operator != (const Tuple<T, T_Size>& aTuple);

  protected:

    T m_values[T_Size];
  };

};};

#ifdef TLOC_FULL_SOURCE
#include "tlocTuple.inl"
#endif


#endif