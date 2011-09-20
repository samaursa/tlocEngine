namespace tloc
{
  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair()
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const Pair<T_First, T_Second>& aOtherPair )
    : m_first(aOtherPair.m_first)
    , m_second(aOtherPair.m_second)
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const Pair<T_Second, T_First>& aOtherPair )
    : m_first(aOtherPair.m_first)
    , m_second(aOtherPair.m_second)
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const T_First& aFirst )
    : m_first(aFirst)
  {
  }

  template <typename T_First, typename T_Second>
  Pair<T_First, T_Second>::Pair( const T_First& aFirst, const T_Second& aSecond )
    : m_first(aFirst)
    , m_second(aSecond)
  {
  }
};