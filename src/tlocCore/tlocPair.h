#ifndef TLOC_PAIR_H
#define TLOC_PAIR_H

#include "tlocBase.h"

namespace tloc
{
  template <typename T_First, typename T_Second>
  class Pair
  {
  public:
    T_First   m_first;
    T_Second  m_second;

    Pair();
    Pair(const Pair<T_First, T_Second>& aOtherPair);
    Pair(const Pair<T_Second, T_First>& aOtherPair);
    Pair(const T_First& aFirst);
    Pair(const T_First& aFirst, const T_Second& aSecond);
  };
};

#include "tlocPair.inl"

#endif