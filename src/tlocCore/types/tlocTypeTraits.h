#ifndef TLOC_TYPE_TRAITS_H
#define TLOC_TYPE_TRAITS_H

#include <tlocCore/types/tlocBasicTypes.h>
#include "3rdParty/loki/TypeTraits.h"

#include <tlocCore/types/tlocTypeTraitsCommonType.h>

namespace tloc
{
  typedef Loki::Int2Type<1>  type_true;
  typedef Loki::Int2Type<0>  type_false;

  namespace type_traits
  {
    template<class T> struct IsConst
    {
      enum { result = false };
    };

    template<class T> struct IsConst<const T>
    {
      enum { result = true };
    };

  //////////////////////////////////////////////////////////////////////////
  // These functions can be used at compile time to ensure only certain types
  // are used with template arguments. The functions are empty so they are
  // (should be) optimized out

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25, class T26, class T27, class T28, class T29, class T30>
    void AssertTypeIsSupported()
    {
      TLOC_STATIC_ASSERT
        (
          ( (Loki::IsSameType<T_TypeToCheck, T1>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T2>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T3>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T4>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T5>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T6>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T7>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T8>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T9>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T10>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T11>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T12>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T13>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T14>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T15>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T16>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T17>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T18>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T19>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T20>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T21>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T22>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T23>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T24>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T25>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T26>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T27>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T28>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T29>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T30>::value) ) ,
          Type_does_not_match_with_any_supported_type
        );
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25, class T26, class T27, class T28, class T29>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T25, T26, T27, T28, T29, T29>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25, class T26, class T27, class T28>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T25, T26, T27, T28, T28>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25, class T26, class T27>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T25, T26, T27, T27>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25, class T26>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T25, T26, T26>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T25, T25>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T24>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T23>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T22>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T19, T20,
                            T21, T21>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T20>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T19>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T18>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T17>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T16>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T15>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T14>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T13>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T12>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T11>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T10>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T9>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T8>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T7>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T6>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T5>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T4>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T3>();
    }

    template <class T_TypeToCheck,
              class T1, class T2>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T2>();
    }

    template <class T_TypeToCheck,
              class T1 >
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T1>();
    }

    //////////////////////////////////////////////////////////////////////////
    // These functions can be used at compile time to ensure only certain types
    // are used with template arguments. The functions are empty so they are
    // (should be) optimized out

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24,
              class T25>
    void AssertTypeIsNotSupported()
    {
      TLOC_STATIC_ASSERT
        (
          ( (Loki::IsSameType<T_TypeToCheck, T1>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T2>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T3>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T4>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T5>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T6>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T7>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T8>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T9>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T10>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T11>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T12>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T13>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T14>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T15>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T16>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T17>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T18>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T19>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T20>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T21>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T22>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T23>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T24>::value) ||
            (Loki::IsSameType<T_TypeToCheck, T25>::value) ) == false ,
          Type_passed_is_explicitly_not_a_supported_type
        );
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23, class T24>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T24>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22, class T23>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T23>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21, class T22>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T22>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20, class T21>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T19, T20,
                            T21, T21>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19, class T20>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T20>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18,
              class T19>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T19>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T18>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T17>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T16>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T15>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T14>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T13>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T12>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T11>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T10>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T9>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T8>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T7, T7>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T6, T6>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T5, T5>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T4, T4>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T3, T3>();
    }

    template <class T_TypeToCheck,
              class T1, class T2>
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T2, T2>();
    }

    template <class T_TypeToCheck,
              class T1 >
    void AssertTypeIsNotSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsNotSupported<T, T1, T1>();
    }
  }

  // This macro allows compile time selection of the correct iterator type
  // for a container. It is used extensively in tlocAlgorithms
#define TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(_cont_)\
  typename Loki::Select<type_traits::IsConst<_cont_>::result, \
  typename _cont_::const_iterator, typename _cont_::iterator>::Result
};

//------------------------------------------------------------------------
// Loki helpers
// Some Loki typetraits require specializations. They will go here

namespace Loki
{
  //------------------------------------------------------------------------
  // Signed ints

  template <>
  struct IsCustomSignedInt<tloc::s8>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomSignedInt<tloc::s16>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomSignedInt<tloc::s32>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomSignedInt<tloc::s64>
  {
    enum { value = 1 };
  };

  //------------------------------------------------------------------------
  // Unsigned ints

  template <>
  struct IsCustomUnsignedInt<tloc::u8>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomUnsignedInt<tloc::u16>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomUnsignedInt<tloc::u32>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomUnsignedInt<tloc::u64>
  {
    enum { value = 1 };
  };

  //------------------------------------------------------------------------
  // Floats

  template <>
  struct IsCustomFloat<tloc::f32>
  {
    enum { value = 1 };
  };

  template <>
  struct IsCustomFloat<tloc::f64>
  {
    enum { value = 1 };
  };

};

#endif