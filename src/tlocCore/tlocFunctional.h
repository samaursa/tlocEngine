#ifndef TLOC_FUNCTIONAL_H
#define TLOC_FUNCTIONAL_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Constness - these functions can be used to write the non-const version
  // of a function by calling the const version of the function to avoid
  // code duplication

  template <typename T>
  const T* add_const(T* a_type)
  { return a_type; }

  template <typename T>
  T* remove_const(const T* a_type)
  { return const_cast<T*>(a_type); }

  //////////////////////////////////////////////////////////////////////////
  // Base classes

  template <typename T_Arg, typename T_Result>
  struct unary_function
  {
    typedef T_Arg     argument_type;
    typedef T_Result  result_type;
  };

  template <typename T_Arg1, typename T_Arg2, typename T_Result>
  class binary_function
  {
    typedef T_Arg1    first_argument_type;
    typedef T_Arg2    second_argument_type;
    typedef T_Result  result_type;
  };

  struct unary_function_type  {};
  struct binary_function_type {};

  // These macros are preferred over inheriting from unary/binary base classes
#define DECL_UNARY_FUNC(T_Arg , T_Result)\
  typedef unary_function_type function_type;\
  typedef T_Arg               argument_type;\
  typedef T_Result            result_type

#define DECL_BINARY_FUNC(T_Arg1, T_Arg2, T_Result)\
  typedef unary_function_type function_type;\
  typedef T_Arg1              first_argument_type;\
  typedef T_Arg2              second_argument_type;\
  typedef T_Result            result_type

  //////////////////////////////////////////////////////////////////////////
  // Arithmetic operations

  template <typename T>
  struct plus : binary_function<T, T, T>
  {
    T operator()(const T& a_x, const T& a_y) const { return a_x + a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct minus : binary_function<T, T, T>
  {
    T operator()(const T& a_x, const T& a_y) const { return a_x - a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct multiplies : binary_function<T, T, T>
  {
    T operator()(const T& a_x, const T& a_y) const { return a_x * a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct divides : binary_function<T, T, T>
  {
    T operator()(const T& a_x, const T& a_y) const { return a_x / a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct modulus : binary_function<T, T, T>
  {
    T operator()(const T& a_x, const T& a_y) const { return a_x % a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct negate : unary_function<T, T>
  {
    T operator()(const T& a_x) const { return -a_x; }
  };

  //////////////////////////////////////////////////////////////////////////
  // Comparisor operations

  template <typename T>
  struct equal_to_stored : unary_function<T, bool>
  {
  public:
    typedef equal_to_stored<T>                this_type;

  public:
    equal_to_stored(const T& a_toCompareWith) 
      : m_toCompareWith(a_toCompareWith) 
    { }

    this_type& operator= (const equal_to_stored& a_other)
    { 
      m_toCompareWith = a_other.m_toCompareWith;
      return *this;
    }

    bool operator()(const T& a_x) const { return m_toCompareWith == a_x; }

    const T m_toCompareWith;
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct not_equal_to_stored : unary_function<T, bool>
  {
    not_equal_to_stored(const T& a_toCompareWith) : m_toCompareWith(a_toCompareWith) {}
    bool operator()(const T& a_x) const { return m_toCompareWith != a_x; }

    const T m_toCompareWith;
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct equal_to : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x == a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct not_equal_to : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x != a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct greater : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x > a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct less : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x < a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct greater_equal : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x >= a_y; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  struct less_equal : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x <= a_y; }
  };

  //////////////////////////////////////////////////////////////////////////
  // Logical operations

  template <typename T>
  struct logical_and : binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x && a_y; }
  };

  template <typename T>
  struct logical_or: binary_function<T, T, bool>
  {
    bool operator()(const T& a_x, const T& a_y) const { return a_x || a_y; }
  };

  template <typename T>
  struct logical_not: unary_function<T, bool>
  {
    bool operator()(const T& a_x) const { return !a_x; }
  };

  //////////////////////////////////////////////////////////////////////////
  // hash related function objects

  template <typename T>
  struct hash
  {
    tl_size operator()(T p) const
    {
      TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value),
                         Unable_to_generate_a_hash_for_this_type);
    }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <typename T>
  struct hash<T*>
  {
    tl_size operator()(T* p) const { return (tl_size)(tl_uintptr)(p); }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<bool>
  { tl_size operator()(bool a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<char8>
  { tl_size operator()(char8 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<char32>
  { tl_size operator()(char32 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<uchar8>
  { tl_size operator()(uchar8 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<s16>
  { tl_size operator()(s16 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<s32>
  { tl_size operator()(s32 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<s64>
  { tl_size operator()(s64 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<u16>
  { tl_size operator()(u16 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<u32>
  { tl_size operator()(u32 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<u64>
  { tl_size operator()(u64 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<f32>
  { tl_size operator()(f32 a_value) const; };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  template <>
  struct hash<f64>
  { tl_size operator()(f64 a_value) const; };

  //////////////////////////////////////////////////////////////////////////
  // Use self/first/second

  template <typename T>
  struct use_self
  {
    DECL_UNARY_FUNC(T, T);

    const T& operator()(const T& a) const { return a; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Pair>
  struct use_first
  {
    DECL_UNARY_FUNC(T_Pair, const typename T_Pair::first_type);

    result_type& operator()(const T_Pair& a) const
    { return a.first; }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Pair>
  struct use_second
  {
    DECL_UNARY_FUNC(T_Pair, const typename T_Pair::second_type);

    result_type& operator()(const T_Pair& a) const
    { return a.second; }
  };

  // ///////////////////////////////////////////////////////////////////////
  // extractor from pointers or use reference

  struct use_reference
  {
    template <typename T>
    T& operator()(T& a) { return a; }
  };

  struct use_pointee
  {
    template <typename T>
    typename PointeeType<T>::value_type& 
      operator()(T& a) const 
    { 
      typedef  typename PointeeType<T>::value_type             pointee_type;
      return *a; 
    }
  };

};};

#endif
