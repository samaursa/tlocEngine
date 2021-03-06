#ifndef TLOC_PAIR_H
#define TLOC_PAIR_H

#include <tlocCore/tlocCoreBase.h>

#ifdef TLOC_COMPILER_VISUAL_CPP
# pragma warning(push)
# pragma warning(disable: 4512)
#endif

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
  Pair<T_First, T_Second> MakePair(const T_First& aFirst, const T_Second& aSecond);

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

  namespace algos { namespace pair {

    namespace compare {

    // ///////////////////////////////////////////////////////////////////////
    // Compare the first value

      template <typename T>
      struct First
      {
        First(const T& a_valueToCompare)
          : m_valueToCompare(a_valueToCompare)
        { }

        template <typename U>
        bool operator()(const Pair<T, U>& a_pair)
        { return a_pair.first == m_valueToCompare; }

        const T& m_valueToCompare;
      };

      template <typename T>
      First<T>
        MakeFirst(const T& a_valueToCompare)
      { return First<T>(a_valueToCompare); }

      // ///////////////////////////////////////////////////////////////////////
      // Compare the second value

      template <typename T>
      struct Second
      {
        Second(const T& a_valueToCompare)
          : m_valueToCompare(a_valueToCompare)
        { }

        template <typename U>
        bool operator()(const Pair<T, U>& a_pair)
        { return a_pair.second == m_valueToCompare; }

        const T& m_valueToCompare;
      };

      template <typename T>
      Second<T>
        MakeSecond(const T& a_valueToCompare)
      { return Second<T>(a_valueToCompare); }

    };

  };};

};};

#define TLOC_EXTERN_TEMPLATE_PAIR(_firstType_, _secondType_)\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core::Pair<_firstType_ TLOC_COMMA _secondType_>)

#if TLOC_COMPILER_VISUAL_CPP
#pragma warning(pop)
#endif

#endif