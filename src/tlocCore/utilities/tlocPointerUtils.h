#ifndef TLOC_POINTER_UTILS_H
#define TLOC_POINTER_UTILS_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace utils {

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // To pointer

  template <typename T>
  tl_uintptr
    GetMemoryAddress(const T& a)
  {
    return (tl_uintptr)(a);
  }

  // ///////////////////////////////////////////////////////////////////////
  // MemoryAddress class

  class MemoryAddress
  {
  public:
    typedef MemoryAddress               this_type;

  public:

    template <typename T>
    explicit MemoryAddress(const T& a_value)
    { m_memAddress = GetMemoryAddress(a_value); }

    bool operator==(const this_type& a_other) const
    { return m_memAddress == a_other.m_memAddress; }
    bool operator< (const this_type& a_other) const
    { return m_memAddress < a_other.m_memAddress; }
    TLOC_DECLARE_OPERATORS(this_type);

    tl_uintptr  m_memAddress;
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // Pointer comparison utility

  template <typename T, typename U>
  bool IsSamePointer(T a_ptr1, U a_ptr2)
  {
    // Perform some checks
    typedef type_true   valid_type;
    typedef type_false  invalid_type;

    typedef typename Loki::Select< (Loki::TypeTraits<T>::isUnsignedInt||
      Loki::TypeTraits<T>::isPointer), valid_type, invalid_type>::Result  T_type;

    typedef typename Loki::Select< (Loki::TypeTraits<U>::isUnsignedInt||
      Loki::TypeTraits<U>::isPointer ), valid_type, invalid_type>::Result  U_type;

    TLOC_STATIC_ASSERT( (Loki::IsSameType<T_type, valid_type>::value),
      T_type_passed_is_not_an_unsigned_int_nor_a_pointer);
    TLOC_STATIC_ASSERT( (Loki::IsSameType<U_type, valid_type>::value),
      U_type_passed_is_not_an_unsigned_int_nor_a_pointer);

    // Checks passed, return result
    return (tl_size)a_ptr1 == (tl_size)a_ptr2;
  }

};};};


#endif