#pragma once
#ifndef TLOC_VARIADIC_H
#define TLOC_VARIADIC_H

#include <tlocCore/data_structures/tlocTuple.h>

namespace tloc { namespace core {

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
    enum { size = 1 };
  public:
    Variadic(T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 2> : public Tuple<T, 2>
  {
  public:
    enum { size = 2 };
  public:
    Variadic(T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 3> : public Tuple<T, 3>
  {
  public:
    enum { size = 3 };
  public:
    Variadic(T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 4> : public Tuple<T, 4>
  {
  public:
    enum { size = 4 };
  public:
    Variadic(T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 5> : public Tuple<T, 5>
  {
  public:
    enum { size = 5 };
  public:
    Variadic(T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 6> : public Tuple<T, 6>
  {
  public:
    enum { size = 6 };
  public:
    Variadic(T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 7> : public Tuple<T, 7>
  {
  public:
    enum { size = 7 };
  public:
    Variadic(T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 8> : public Tuple<T, 8>
  {
  public:
    enum { size = 8 };
  public:
    Variadic(T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 9> : public Tuple<T, 9>
  {
  public:
    enum { size = 9 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 10> : public Tuple<T, 10>
  {
  public:
    enum { size = 10 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 11> : public Tuple<T, 11>
  {
  public:
    enum { size = 11 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 12> : public Tuple<T, 12>
  {
  public:
    enum { size = 12 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 13> : public Tuple<T, 13>
  {
  public:
    enum { size = 13 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 14> : public Tuple<T, 14>
  {
  public:
    enum { size = 14 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 15> : public Tuple<T, 15>
  {
  public:
    enum { size = 15 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  template <typename T>
  class Variadic<T, 16> : public Tuple<T, 16>
  {
  public:
    enum { size = 16 };
  public:
    Variadic(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T);

    template <typename T_ArrayType>
    Variadic(const T_ArrayType (&a_array)[size]);
  };

  //------------------------------------------------------------------------
  // Common typedefs for Variadics

#include "tlocVariadicTypedefMacros.h"

TLOC_DECLARE_VARIADIC_TYPES(tl_int, i);
TLOC_DECLARE_VARIADIC_TYPES(tl_uint, u);
TLOC_DECLARE_VARIADIC_TYPES(tl_float, f);
TLOC_DECLARE_VARIADIC_TYPES(char8, c);
TLOC_DECLARE_VARIADIC_TYPES(char32, w);

#undef TLOC_DECLARE_VARIADIC_TYPES

};};

#endif