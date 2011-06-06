#ifndef TLOC_TUPLE_H
#define TLOC_TUPLE_H

#include "tlocCore\tlocBase.h"
#include "tlocCore\tlocStandardFuncs.h"

namespace tloc
{
#define ITERATE_TUPLE for (tl_uint32 i = 0; i < aSize; ++i)

  template <typename T, tl_uint32 aSize>
  class Tuple
  {
  public:

    // Empty default constructor
    Tuple();
    Tuple(const Tuple<T, aSize>& aTuple);
    
    explicit Tuple(const T& aValue);    

    //------------------------------------------------------------------------
    // Accessors

    TL_FI T& operator[] (tl_uint32 aIndex);
    TL_FI const T& operator[] (tl_uint32 aIndex) const;
    
    // Direct array access. Generally not recommended
    TL_FI operator T* ();
    TL_FI operator const T* () const;

    TL_FI Tuple<T, aSize>& operator= (const Tuple<T, aSize>& aTuple);

  protected:

    T values[aSize];
  };

#include "tlocTuple.inl"

#undef ITERATE_TUPLE

};

#endif