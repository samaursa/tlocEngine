#ifndef TLOC_TUPLE_H
#define TLOC_TUPLE_H

#include "tlocCore\tlocBase.h"
#include "tlocCore\tlocStandardFuncs.h"

namespace tloc
{
  template <typename T, u32 aSize>
  class Tuple
  {
  public:

    // Empty default constructor
    Tuple();
    Tuple(const Tuple<T, aSize>& aTuple);
    
    explicit Tuple(const T& aValue);    

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
    
    // Direct array access. Generally not recommended
    TL_FI operator T* ();
    TL_FI operator const T* () const;

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this vector so that all values of this vector equal aValue
    TL_FI void Set(T aValue);

    // Swaps the vector with the incoming vector
    TL_FI void Swap(Tuple<T, aSize>& aVector);

    //------------------------------------------------------------------------
    // Operators

    TL_FI Tuple<T, aSize>& operator= (const Tuple<T, aSize>& aTuple);

  protected:

    T values[aSize];
  };

#include "tlocTuple.inl"

#undef ITERATE_TUPLE

};

#endif