#ifndef TLOC_ITERATOR_H
#define TLOC_ITERATOR_H

#include "tlocBase.h"

namespace tloc
{
  template <typename T_InputItr>
  tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd);

  namespace detail
  {
    typedef type_true   IsPtrItr;
    typedef type_false  IsComplexItr;

    template <typename T_InputItr>
    tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd, IsPtrItr);

    template <typename T_InputItr>
    tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd, IsComplexItr);
  };
};

#include "tlocIterator.inl"

#endif