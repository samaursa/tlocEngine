#ifndef TLOC_PAIR_H
#define TLOC_PAIR_H

#include "tlocBase.h"

namespace tloc { namespace core {

  template <typename T_First, typename T_Second>
  class Pair
  {
  public:
    T_First   first;
    T_Second  second;

    Pair();
    Pair(const Pair<T_First, T_Second>& aOtherPair);
    Pair(const T_First& aFirst);
    Pair(const T_First& aFirst, const T_Second& aSecond);
  };

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second> MakePair(const Pair<T_First, T_Second>& aOtherPair);

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second> MakePair(const T_First& aFirst, const T_First& aSecond);

};};

#endif