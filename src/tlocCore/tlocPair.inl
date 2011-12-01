#ifndef TLOC_PAIR_INL
#define TLOC_PAIR_INL

#ifndef TLOC_PAIR_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair()
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const Pair<T_First, T_Second>& aOtherPair )
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

};};

#endif