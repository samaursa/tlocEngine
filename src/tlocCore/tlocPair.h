#ifndef TLOC_PAIR_H
#define TLOC_PAIR_H

#include "tlocBase.h"

namespace tloc { namespace core {

  template <typename T_First, typename T_Second>
  class Pair
  {
  public:
    typedef T_First   first_type;
    typedef T_Second  second_type;

    T_First   first;
    T_Second  second;

    Pair();
    template <typename T1, typename T2>
    Pair(const Pair<T1, T2>& aOtherPair);
    Pair(const T_First& aFirst);
    Pair(const T_First& aFirst, const T_Second& aSecond);
  };

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second> MakePair(const Pair<T_First, T_Second>& aOtherPair);

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second> MakePair(const T_First& aFirst, const T_First& aSecond);

  //////////////////////////////////////////////////////////////////////////
  // Global operators

  template <typename T1, typename T2>
  TL_FI bool operator== (const Pair<T1, T2>& a, const Pair<T1, T2>& b);

  template <typename T1, typename T2>
  TL_FI bool operator!= (const Pair<T1, T2>& a, const Pair<T1, T2>& b);

  template <typename T1, typename T2>
  TL_FI bool operator<(const Pair<T1, T2>& a, const Pair<T1, T2>& b);

  template <typename T1, typename T2>
  TL_FI bool operator>(const Pair<T1, T2>& a, const Pair<T1, T2>& b);

  template <typename T1, typename T2>
  TL_FI bool operator>=(const Pair<T1, T2>& a, const Pair<T1, T2>& b);

  template <typename T1, typename T2>
  TL_FI bool operator<=(const Pair<T1, T2>& a, const Pair<T1, T2>& b);

};};

#endif