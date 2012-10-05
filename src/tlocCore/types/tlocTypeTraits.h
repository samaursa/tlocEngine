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