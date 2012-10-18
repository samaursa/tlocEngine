#ifndef TLOC_TYPE_TRAITS_H
#define TLOC_TYPE_TRAITS_H

#include <tlocCore/types/tlocBasicTypes.h>
#include "3rdParty/loki/TypeTraits.h"

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
              class T19, class T20>
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
            (Loki::IsSameType<T_TypeToCheck, T20>::value) ) ,
          Type_does_not_match_with_any_supported_type
        );
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
                            T12, T13, T14, T15, T16, T17, T18, T19, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17, class T18>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16, class T17>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15, class T16>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14, class T15>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13, class T14>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12,
              class T13>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11, class T12>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10, class T11>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9, class T10>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8, class T9>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T9, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7, class T8>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T8, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6,
              class T7>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T7, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5, class T6>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T6, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4, class T5>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T5, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3, class T4>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T4, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2, class T3>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T3, T>();
    }

    template <class T_TypeToCheck,
              class T1, class T2>
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T2, T>();
    }

    template <class T_TypeToCheck,
              class T1 >
    void AssertTypeIsSupported()
    {
      typedef T_TypeToCheck T;
      AssertTypeIsSupported<T, T1, T>();
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