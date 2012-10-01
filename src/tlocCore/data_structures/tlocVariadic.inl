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
  template <typename T_ArrayType>
  Variadic<T, 1>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0) = a_array[0];
  }

  template <typename T>
  Variadic<T, 2>::Variadic(T a_1, T a_2)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
  }

  template <typename T>
  template <typename T_ArrayType>
  Variadic<T, 2>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0) = a_array[0];
    operator[](1) = a_array[1];
  }

  //------------------------------------------------------------------------

  template <typename T>
  Variadic<T, 3>::Variadic(T a_1, T a_2, T a_3)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
  }

  template <typename T>
  template <typename T_ArrayType>
  Variadic<T, 3>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
  }

  //------------------------------------------------------------------------

  template <typename T>
  Variadic<T, 4>::Variadic(T a_1, T a_2, T a_3, T a_4)
  {
    operator[](0) = a_1;
    operator[](1) = a_2;
    operator[](2) = a_3;
    operator[](3) = a_4;
  }

  template <typename T>
  template <typename T_ArrayType>
  Variadic<T, 4>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
  }
  
  //------------------------------------------------------------------------

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
  template <typename T_ArrayType>
  Variadic<T, 5>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
    operator[](4)   = a_array[4];
  }

  //------------------------------------------------------------------------

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
  template <typename T_ArrayType>
  Variadic<T, 6>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
    operator[](4)   = a_array[4];
    operator[](5)   = a_array[5];
  }

  //------------------------------------------------------------------------

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
  template <typename T_ArrayType>
  Variadic<T, 7>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
    operator[](4)   = a_array[4];
    operator[](5)   = a_array[5];
    operator[](6)   = a_array[6];
  }

  //------------------------------------------------------------------------

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
  template <typename T_ArrayType>
  Variadic<T, 8>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
    operator[](4)   = a_array[4];
    operator[](5)   = a_array[5];
    operator[](6)   = a_array[6];
    operator[](7)   = a_array[7];
  }

  //------------------------------------------------------------------------

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
  template <typename T_ArrayType>
  Variadic<T, 9>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
    operator[](4)   = a_array[4];
    operator[](5)   = a_array[5];
    operator[](6)   = a_array[6];
    operator[](7)   = a_array[7];
    operator[](8)   = a_array[8];
  }

  //------------------------------------------------------------------------

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

  template <typename T>
  template <typename T_ArrayType>
  Variadic<T, 10>::Variadic(const T_ArrayType (&a_array)[size])
  {
    operator[](0)   = a_array[0];
    operator[](1)   = a_array[1];
    operator[](2)   = a_array[2];
    operator[](3)   = a_array[3];
    operator[](4)   = a_array[4];
    operator[](5)   = a_array[5];
    operator[](6)   = a_array[6];
    operator[](7)   = a_array[7];
    operator[](8)   = a_array[8];
    operator[](9)   = a_array[9];
  }

};};

#endif