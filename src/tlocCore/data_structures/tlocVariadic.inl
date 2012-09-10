#ifndef TLOC_VARIADIC_INL
#define TLOC_VARIADIC_INL

#ifndef TLOC_VARIADIC_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/data_structures/tlocTuple.inl>

namespace tloc { namespace core {

  template <typename T>
  Variadic<T, 1>::Variadic(T a_1)
  {
    operator[](0) = a_1;
  }

  template <typename T>
  Variadic<T, 2>::Variadic(T a_1, T a_2)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
  }

  template <typename T>
  Variadic<T, 3>::Variadic(T a_1, T a_2, T a_3)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
  }

  template <typename T>
  Variadic<T, 4>::Variadic(T a_1, T a_2, T a_3, T a_4)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
  }

  template <typename T>
  Variadic<T, 5>::Variadic(T a_1, T a_2, T a_3, T a_4, T a_5)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
    operator[](4) = a_5;
  }

  template <typename T>
  Variadic<T, 6>::Variadic(T a_1, T a_2, T a_3, T a_4, T a_5, T a_6)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
    operator[](4) = a_5;
    operator[](5) = a_6;
  }

  template <typename T>
  Variadic<T, 7>::Variadic(T a_1, T a_2, T a_3, T a_4, T a_5, T a_6, T a_7)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
    operator[](4) = a_5;
    operator[](5) = a_6;
    operator[](6) = a_7;
  }

  template <typename T>
  Variadic<T, 8>::Variadic(T a_1, T a_2, T a_3, T a_4, T a_5, T a_6, T a_7,
                           T a_8)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
    operator[](4) = a_5;
    operator[](5) = a_6;
    operator[](6) = a_7;
    operator[](7) = a_8;
  }

  template <typename T>
  Variadic<T, 9>::Variadic(T a_1, T a_2, T a_3, T a_4, T a_5, T a_6, T a_7,
                           T a_8, T a_9)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
    operator[](4) = a_5;
    operator[](5) = a_6;
    operator[](6) = a_7;
    operator[](7) = a_8;
    operator[](8) = a_9;
  }

  template <typename T>
  Variadic<T, 10>::Variadic(T a_1, T a_2, T a_3, T a_4, T a_5, T a_6, T a_7,
                            T a_8, T a_9, T a_10)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
    operator[](4) = a_5;
    operator[](5) = a_6;
    operator[](6) = a_7;
    operator[](7) = a_8;
    operator[](8) = a_9;
    operator[](9) = a_10;
  }


};};

#endif