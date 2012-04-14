#ifndef TLOC_UTILS_H
#define TLOC_UTILS_H

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocTemplateUtils.h"

namespace tloc { namespace core {

///-----------------------------------------------------------------------------
/// Used to prevent a struct or class from being initialized by declaring a
/// constructor with a static assert.
///
/// @param  helper_name Name of the helper.
///-----------------------------------------------------------------------------
#define DECL_TYPEDEF_HELPER(helper_name) helper_name() { \
  TLOC_STATIC_ASSERT(false, \
  Cannot_instantiate_typedef_helper_USE_typedef_type_declared_in_helper); }

///-------------------------------------------------------------------------
/// Used to avoid code duplication for operators. Requires definition of
/// operators == and <
///
/// @param object The type itself
///-------------------------------------------------------------------------
#define TLOC_DECLARE_OPERATORS(object) \
  bool operator !=(const object& a_other) const { return !(operator==(a_other)); }\
  bool operator > (const object& a_other) const { return a_other.operator<(*this); }\
  bool operator <=(const object& a_other) const { return !(operator>(a_other)); }\
  bool operator >=(const object& a_other) const { return !(operator<(a_other)); }

  //------------------------------------------------------------------------
  // Pointer comparison utility

  template <typename T, typename U>
  bool IsSamePointer(T a_ptr1, U a_ptr2)
  {
    // Perform some checks
    typedef type_true   valid_type;
    typedef type_false  invalid_type;

    typedef Loki::Select< (Loki::TypeTraits<T>::isIntegral ||
      Loki::TypeTraits<T>::isPointer), valid_type, invalid_type>::Result  T_type;

    typedef Loki::Select< (Loki::TypeTraits<U>::isIntegral ||
      Loki::TypeTraits<U>::isPointer ), valid_type, invalid_type>::Result  U_type;

    TLOC_STATIC_ASSERT( (Loki::IsSameType<T_type, valid_type>::value),
      T_type_passed_is_not_an_unsigned_int_nor_a_pointer);
    TLOC_STATIC_ASSERT( (Loki::IsSameType<U_type, valid_type>::value),
      U_type_passed_is_not_an_unsigned_int_nor_a_pointer);

    // Checks passed, return result
    return (tl_size)a_ptr1 == (tl_size)a_ptr2;
  }


};};


#endif