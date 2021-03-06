#pragma once
#ifndef TLOC_VARIADIC_H
#define TLOC_VARIADIC_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/data_structures/tlocTuple.h>

namespace tloc { namespace core { namespace data_structs {

  ///-------------------------------------------------------------------------
  /// @brief
  /// A simple class to (ver loosely) give us the variadic templates
  /// functionality.
  ///-------------------------------------------------------------------------
  template <typename T, tl_size T_Size>
  class Variadic;

  template <typename T>
  class Variadic<T, 1> : public Tuple<T, 1>
  {
  public:
    enum { k_size = 1 };
  public:
    typedef Tuple<T, 1> base_type;
    using base_type::operator[];

  public:
    Variadic(T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 2> : public Tuple<T, 2>
  {
  public:
    enum { k_size = 2 };
  public:
    typedef Tuple<T, 2> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 3> : public Tuple<T, 3>
  {
  public:
    enum { k_size = 3 };
  public:
    typedef Tuple<T, 3> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 4> : public Tuple<T, 4>
  {
  public:
    enum { k_size = 4 };
  public:
    typedef Tuple<T, 4> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 5> : public Tuple<T, 5>
  {
  public:
    enum { k_size = 5 };
  public:
    typedef Tuple<T, 5> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 6> : public Tuple<T, 6>
  {
  public:
    enum { k_size = 6 };
  public:
    typedef Tuple<T, 6> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 7> : public Tuple<T, 7>
  {
  public:
    enum { k_size = 7 };
  public:
    typedef Tuple<T, 7> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 8> : public Tuple<T, 8>
  {
  public:
    enum { k_size = 8 };
  public:
    typedef Tuple<T, 8> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 9> : public Tuple<T, 9>
  {
  public:
    enum { k_size = 9 };
  public:
    typedef Tuple<T, 9> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 10> : public Tuple<T, 10>
  {
  public:
    enum { k_size = 10 };
  public:
    typedef Tuple<T, 10> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 11> : public Tuple<T, 11>
  {
  public:
    enum { k_size = 11 };
  public:
    typedef Tuple<T, 11> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 12> : public Tuple<T, 12>
  {
  public:
    enum { k_size = 12 };
  public:
    typedef Tuple<T, 12> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 13> : public Tuple<T, 13>
  {
  public:
    enum { k_size = 13 };
  public:
    typedef Tuple<T, 13> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 14> : public Tuple<T, 14>
  {
  public:
    enum { k_size = 14 };
  public:
    typedef Tuple<T, 14> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 15> : public Tuple<T, 15>
  {
  public:
    enum { k_size = 15 };
  public:
    typedef Tuple<T, 15> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  template <typename T>
  class Variadic<T, 16> : public Tuple<T, 16>
  {
  public:
    enum { k_size = 16 };
  public:
    typedef Tuple<T, 16> base_type;
    using base_type::operator[];

  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[k_size]);
  };

  //------------------------------------------------------------------------
  // Common typedefs for Variadics

#include "tlocVariadicTypedefMacros.h"

TLOC_DECLARE_VARIADIC_TYPES(tl_int, s);
TLOC_DECLARE_VARIADIC_TYPES(s32, s32);
TLOC_DECLARE_VARIADIC_TYPES(s64, s64);
TLOC_DECLARE_VARIADIC_TYPES(tl_uint, u);
TLOC_DECLARE_VARIADIC_TYPES(u32, u32);
TLOC_DECLARE_VARIADIC_TYPES(u64, u64);
TLOC_DECLARE_VARIADIC_TYPES(tl_float, f);
TLOC_DECLARE_VARIADIC_TYPES(f32, f32);
TLOC_DECLARE_VARIADIC_TYPES(f64, f64);
TLOC_DECLARE_VARIADIC_TYPES(char8, c);
TLOC_DECLARE_VARIADIC_TYPES(char32, w);
TLOC_DECLARE_VARIADIC_TYPES(tl_size, k_size);

#undef TLOC_DECLARE_VARIADIC_TYPES

};};};

#endif