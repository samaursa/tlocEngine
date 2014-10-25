#ifndef TLOC_PAIR_INL
#define TLOC_PAIR_INL

#ifndef TLOC_PAIR_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocPair.h>

namespace tloc { namespace core {

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair()
    : first(), second()
  {
  }

  template <typename T_First, typename T_Second>
  template <typename T1, typename T2>
  Pair<T_First, T_Second>::Pair( const Pair<T1, T2>& aOtherPair )
    : first(aOtherPair.first)
    , second(aOtherPair.second)
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const T_First& aFirst )
    : first(aFirst)
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const T_First& aFirst, const T_Second& aSecond )
    : first(aFirst)
    , second(aSecond)
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second> MakePair( const Pair<T_First, T_Second>& aOtherPair )
  {
    return Pair<T_First, T_Second>(aOtherPair);
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second> MakePair( const T_First& aFirst, const T_Second& aSecond )
  {
    return Pair<T_First, T_Second>(aFirst, aSecond);
  }

  //////////////////////////////////////////////////////////////////////////
  // Global operators

  template <typename T1, typename T2>
  bool 
    operator== (const Pair<T1, T2>& a, const Pair<T1, T2>& b)
  { return ( (a.first == a.second) && (a.second == b.second) ); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  bool 
    operator!= (const Pair<T1, T2>& a, const Pair<T1, T2>& b)
  { return !(a == b); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  bool 
    operator<(const Pair<T1, T2>& a, const Pair<T1, T2>& b)
  {
    // Confusing comparison. According to the standard: In inequality
    // comparisons (<, >), the first elements are compared first, and only if
    // the inequality comparison is not true for them, the second elements are
    // compared. 
    return (a.first<b.first) || (!(b.first<a.first)&&(a.second < b.second));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  bool 
    operator>(const Pair<T1, T2>& a, const Pair<T1, T2>& b)
  { return b < a; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  bool 
    operator>=(const Pair<T1, T2>& a, const Pair<T1, T2>& b)
  { return !(a < b); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  bool 
    operator<=(const Pair<T1, T2>& a, const Pair<T1, T2>& b)
  { return !(b < a); }

};};

#define TLOC_EXPLICITLY_INSTANTIATE_PAIR(_firstType_, _secondType_)\
  template class tloc::core::Pair<_firstType_, _secondType_>

#endif