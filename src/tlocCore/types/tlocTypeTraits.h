#ifndef TLOC_TYPE_TRAITS_H
#define TLOC_TYPE_TRAITS_H

#include <tlocCore/types/tlocBasicTypes.h>
#include "3rdParty/loki/TypeTraits.h"

#include <tlocCore/types/tlocTypeTraitsCommonType.h>
#include <tlocCore/tlocStaticAssert.h>

#include <3rdParty/loki/TypeTraits.h>

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

    // We reach VC++ internal character limit for symbol information which is
    // unfortunate. For now, we will disable the warning
#ifdef _MSC_VER
# pragma warning(disable : 4503)
#endif


    template <class T_ToCheck,
              class T1,
              class T2 = T1, class T3 = T1, class T4 = T1, class T5 = T1,
              class T6 = T1, class T7 = T1, class T8 = T1, class T9 = T1,
              class T10 = T1, class T11 = T1, class T12 = T1, class T13 = T1,
              class T14 = T1, class T15 = T1, class T16 = T1, class T17 = T1,
              class T18 = T1, class T19 = T1, class T20 = T1, class T21 = T1,
              class T22 = T1, class T23 = T1, class T24 = T1, class T25 = T1,
              class T26 = T1, class T27 = T1, class T28 = T1, class T29 = T1,
              class T30 = T1, class T31 = T1, class T32 = T1, class T33 = T1,
              class T34 = T1, class T35 = T1, class T36 = T1, class T37 = T1,
              class T38 = T1, class T39 = T1, class T40 = T1, class T41 = T1,
              class T42 = T1, class T43 = T1, class T44 = T1, class T45 = T1,
              class T46 = T1, class T47 = T1, class T48 = T1, class T49 = T1,
              class T50 = T1, class T51 = T1, class T52 = T1, class T53 = T1,
              class T54 = T1, class T55 = T1, class T56 = T1, class T57 = T1,
              class T58 = T1, class T59 = T1, class T60 = T1, class T61 = T1,
              class T62 = T1, class T63 = T1, class T64 = T1, class T65 = T1,
              class T66 = T1, class T67 = T1, class T68 = T1, class T69 = T1,
              class T70 = T1>
    struct AssertTypeIsSupported
    {
      TLOC_STATIC_ASSERT
        (
          ( (Loki::IsSameType<T_ToCheck, T1>::value) ||
            (Loki::IsSameType<T_ToCheck, T2>::value) ||
            (Loki::IsSameType<T_ToCheck, T3>::value) ||
            (Loki::IsSameType<T_ToCheck, T4>::value) ||
            (Loki::IsSameType<T_ToCheck, T5>::value) ||
            (Loki::IsSameType<T_ToCheck, T6>::value) ||
            (Loki::IsSameType<T_ToCheck, T7>::value) ||
            (Loki::IsSameType<T_ToCheck, T8>::value) ||
            (Loki::IsSameType<T_ToCheck, T9>::value) ||
            (Loki::IsSameType<T_ToCheck, T10>::value) ||
            (Loki::IsSameType<T_ToCheck, T11>::value) ||
            (Loki::IsSameType<T_ToCheck, T12>::value) ||
            (Loki::IsSameType<T_ToCheck, T13>::value) ||
            (Loki::IsSameType<T_ToCheck, T14>::value) ||
            (Loki::IsSameType<T_ToCheck, T15>::value) ||
            (Loki::IsSameType<T_ToCheck, T16>::value) ||
            (Loki::IsSameType<T_ToCheck, T17>::value) ||
            (Loki::IsSameType<T_ToCheck, T18>::value) ||
            (Loki::IsSameType<T_ToCheck, T19>::value) ||
            (Loki::IsSameType<T_ToCheck, T20>::value) ||
            (Loki::IsSameType<T_ToCheck, T21>::value) ||
            (Loki::IsSameType<T_ToCheck, T22>::value) ||
            (Loki::IsSameType<T_ToCheck, T23>::value) ||
            (Loki::IsSameType<T_ToCheck, T24>::value) ||
            (Loki::IsSameType<T_ToCheck, T25>::value) ||
            (Loki::IsSameType<T_ToCheck, T26>::value) ||
            (Loki::IsSameType<T_ToCheck, T27>::value) ||
            (Loki::IsSameType<T_ToCheck, T28>::value) ||
            (Loki::IsSameType<T_ToCheck, T29>::value) ||
            (Loki::IsSameType<T_ToCheck, T30>::value) ||
            (Loki::IsSameType<T_ToCheck, T31>::value) ||
            (Loki::IsSameType<T_ToCheck, T32>::value) ||
            (Loki::IsSameType<T_ToCheck, T33>::value) ||
            (Loki::IsSameType<T_ToCheck, T34>::value) ||
            (Loki::IsSameType<T_ToCheck, T35>::value) ||
            (Loki::IsSameType<T_ToCheck, T36>::value) ||
            (Loki::IsSameType<T_ToCheck, T37>::value) ||
            (Loki::IsSameType<T_ToCheck, T38>::value) ||
            (Loki::IsSameType<T_ToCheck, T39>::value) ||
            (Loki::IsSameType<T_ToCheck, T40>::value) ||
            (Loki::IsSameType<T_ToCheck, T41>::value) ||
            (Loki::IsSameType<T_ToCheck, T42>::value) ||
            (Loki::IsSameType<T_ToCheck, T43>::value) ||
            (Loki::IsSameType<T_ToCheck, T44>::value) ||
            (Loki::IsSameType<T_ToCheck, T45>::value) ||
            (Loki::IsSameType<T_ToCheck, T46>::value) ||
            (Loki::IsSameType<T_ToCheck, T47>::value) ||
            (Loki::IsSameType<T_ToCheck, T48>::value) ||
            (Loki::IsSameType<T_ToCheck, T49>::value) ||
            (Loki::IsSameType<T_ToCheck, T50>::value) ||
            (Loki::IsSameType<T_ToCheck, T51>::value) ||
            (Loki::IsSameType<T_ToCheck, T52>::value) ||
            (Loki::IsSameType<T_ToCheck, T53>::value) ||
            (Loki::IsSameType<T_ToCheck, T54>::value) ||
            (Loki::IsSameType<T_ToCheck, T55>::value) ||
            (Loki::IsSameType<T_ToCheck, T56>::value) ||
            (Loki::IsSameType<T_ToCheck, T57>::value) ||
            (Loki::IsSameType<T_ToCheck, T58>::value) ||
            (Loki::IsSameType<T_ToCheck, T59>::value) ||
            (Loki::IsSameType<T_ToCheck, T60>::value) ||
            (Loki::IsSameType<T_ToCheck, T70>::value) ),
          Type_does_not_match_with_any_supported_type
        );
    };

    template <class T_ToCheck,
              class T1,
              class T2 = T1, class T3 = T1, class T4 = T1, class T5 = T1,
              class T6 = T1, class T7 = T1, class T8 = T1, class T9 = T1,
              class T10 = T1, class T11 = T1, class T12 = T1, class T13 = T1,
              class T14 = T1, class T15 = T1, class T16 = T1, class T17 = T1,
              class T18 = T1, class T19 = T1, class T20 = T1, class T21 = T1,
              class T22 = T1, class T23 = T1, class T24 = T1, class T25 = T1,
              class T26 = T1, class T27 = T1, class T28 = T1, class T29 = T1,
              class T30 = T1, class T31 = T1, class T32 = T1, class T33 = T1,
              class T34 = T1, class T35 = T1, class T36 = T1, class T37 = T1,
              class T38 = T1, class T39 = T1, class T40 = T1, class T41 = T1,
              class T42 = T1, class T43 = T1, class T44 = T1, class T45 = T1,
              class T46 = T1, class T47 = T1, class T48 = T1, class T49 = T1,
              class T50 = T1, class T51 = T1, class T52 = T1, class T53 = T1,
              class T54 = T1, class T55 = T1, class T56 = T1, class T57 = T1,
              class T58 = T1, class T59 = T1, class T60 = T1, class T61 = T1,
              class T62 = T1, class T63 = T1, class T64 = T1, class T65 = T1,
              class T66 = T1, class T67 = T1, class T68 = T1, class T69 = T1,
              class T70 = T1>
    struct AssertTypeIsNotSupported
    {
      TLOC_STATIC_ASSERT
        (
          ( (Loki::IsSameType<T_ToCheck, T1>::value) ||
            (Loki::IsSameType<T_ToCheck, T2>::value) ||
            (Loki::IsSameType<T_ToCheck, T3>::value) ||
            (Loki::IsSameType<T_ToCheck, T4>::value) ||
            (Loki::IsSameType<T_ToCheck, T5>::value) ||
            (Loki::IsSameType<T_ToCheck, T6>::value) ||
            (Loki::IsSameType<T_ToCheck, T7>::value) ||
            (Loki::IsSameType<T_ToCheck, T8>::value) ||
            (Loki::IsSameType<T_ToCheck, T9>::value) ||
            (Loki::IsSameType<T_ToCheck, T10>::value) ||
            (Loki::IsSameType<T_ToCheck, T11>::value) ||
            (Loki::IsSameType<T_ToCheck, T12>::value) ||
            (Loki::IsSameType<T_ToCheck, T13>::value) ||
            (Loki::IsSameType<T_ToCheck, T14>::value) ||
            (Loki::IsSameType<T_ToCheck, T15>::value) ||
            (Loki::IsSameType<T_ToCheck, T16>::value) ||
            (Loki::IsSameType<T_ToCheck, T17>::value) ||
            (Loki::IsSameType<T_ToCheck, T18>::value) ||
            (Loki::IsSameType<T_ToCheck, T19>::value) ||
            (Loki::IsSameType<T_ToCheck, T20>::value) ||
            (Loki::IsSameType<T_ToCheck, T21>::value) ||
            (Loki::IsSameType<T_ToCheck, T22>::value) ||
            (Loki::IsSameType<T_ToCheck, T23>::value) ||
            (Loki::IsSameType<T_ToCheck, T24>::value) ||
            (Loki::IsSameType<T_ToCheck, T25>::value) ||
            (Loki::IsSameType<T_ToCheck, T26>::value) ||
            (Loki::IsSameType<T_ToCheck, T27>::value) ||
            (Loki::IsSameType<T_ToCheck, T28>::value) ||
            (Loki::IsSameType<T_ToCheck, T29>::value) ||
            (Loki::IsSameType<T_ToCheck, T30>::value) ||
            (Loki::IsSameType<T_ToCheck, T31>::value) ||
            (Loki::IsSameType<T_ToCheck, T32>::value) ||
            (Loki::IsSameType<T_ToCheck, T33>::value) ||
            (Loki::IsSameType<T_ToCheck, T34>::value) ||
            (Loki::IsSameType<T_ToCheck, T35>::value) ||
            (Loki::IsSameType<T_ToCheck, T36>::value) ||
            (Loki::IsSameType<T_ToCheck, T37>::value) ||
            (Loki::IsSameType<T_ToCheck, T38>::value) ||
            (Loki::IsSameType<T_ToCheck, T39>::value) ||
            (Loki::IsSameType<T_ToCheck, T40>::value) ||
            (Loki::IsSameType<T_ToCheck, T41>::value) ||
            (Loki::IsSameType<T_ToCheck, T42>::value) ||
            (Loki::IsSameType<T_ToCheck, T43>::value) ||
            (Loki::IsSameType<T_ToCheck, T44>::value) ||
            (Loki::IsSameType<T_ToCheck, T45>::value) ||
            (Loki::IsSameType<T_ToCheck, T46>::value) ||
            (Loki::IsSameType<T_ToCheck, T47>::value) ||
            (Loki::IsSameType<T_ToCheck, T48>::value) ||
            (Loki::IsSameType<T_ToCheck, T49>::value) ||
            (Loki::IsSameType<T_ToCheck, T50>::value) ||
            (Loki::IsSameType<T_ToCheck, T51>::value) ||
            (Loki::IsSameType<T_ToCheck, T52>::value) ||
            (Loki::IsSameType<T_ToCheck, T53>::value) ||
            (Loki::IsSameType<T_ToCheck, T54>::value) ||
            (Loki::IsSameType<T_ToCheck, T55>::value) ||
            (Loki::IsSameType<T_ToCheck, T56>::value) ||
            (Loki::IsSameType<T_ToCheck, T57>::value) ||
            (Loki::IsSameType<T_ToCheck, T58>::value) ||
            (Loki::IsSameType<T_ToCheck, T59>::value) ||
            (Loki::IsSameType<T_ToCheck, T60>::value) ||
            (Loki::IsSameType<T_ToCheck, T70>::value) ) == false,
            Type_passed_is_explicitly_not_a_supported_type
            );
    };

    template <typename T>
    struct CallTraits
    {

      typedef T                                             value_type;
      typedef T&                                            reference;
      typedef const T&                                      const_reference;

      typedef typename
        Loki::Select<Loki::TypeTraits<T>::isFundamental,
                     const T,
                     const T&>::Result                      param_type;
    };

    template <typename T>
    struct CallTraits<T&>
    {
      typedef T                                             value_type;
      typedef T&                                            reference;
      typedef const T&                                      const_reference;

      typedef typename
        Loki::Select<Loki::TypeTraits<T>::isFundamental,
                     const T,
                     const T&>::Result                      param_type;
    };

  };

  // This macro allows compile time selection of the correct iterator type
  // for a container. It is used extensively in tlocAlgorithms
#define TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(_cont_)\
  typename Loki::Select<type_traits::IsConst<_cont_>::result, \
  typename _cont_::const_iterator, typename _cont_::iterator>::Result

  // ///////////////////////////////////////////////////////////////////////
  // Pointee type

  namespace priv {

    template <typename T, bool>
    struct PointeeType;

    template <typename T>
    struct PointeeType<T, false>
    {
      typedef typename T::value_type                      value_type;
    };

    template <typename T>
    struct PointeeType<T, true>
    {
      typedef typename Loki::TypeTraits<T>::PointeeType   value_type;
    };

  };

  template <typename T>
  struct PointeeType
  {
    typedef typename priv::PointeeType
      <T, Loki::TypeTraits<T>::isPointer>::value_type     value_type;
  };

  namespace priv {

    template <typename T, bool>
    struct PointerType;

    template <typename T>
    struct PointerType<T, false>
    {
      typedef typename T::pointer                         value_type;
    };

    template <typename T>
    struct PointerType<T, true>
    {
      typedef T                                           value_type;
    };

  };

  template <typename T>
  struct PointerType
  {
    typedef typename priv::PointerType
      <T, Loki::TypeTraits<T>::isPointer>::value_type     value_type;
  };

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