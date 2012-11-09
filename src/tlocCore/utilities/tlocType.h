#ifndef _TLOC_CORE_UTILS_TYPE_H_
#define _TLOC_CORE_UTILS_TYPE_H_

#include <tlocCore/tlocBase.h>

namespace tloc { namespace core { namespace utils {

  //------------------------------------------------------------------------
  // Safe 32-bit to 64-bit type conversions with sanity checks

  ///-------------------------------------------------------------------------
  /// @brief Converts an a_value to a 32 bit number.
  ///
  /// @param  a_value The value.
  ///
  ///                 @note A linking error means the type conversion you are
  ///                 looking for is not supported.
  ///-------------------------------------------------------------------------
  template <typename T_ReturnType, typename T_ToCast>
  T_ReturnType CastTo32(T_ToCast a_value);

  ///-------------------------------------------------------------------------
  /// @brief
  /// Cast numbers from signed to unsigned and vice versa. This function
  /// will fire an assertion if the cast results in a loss of data.
  ///
  /// @param  a_value The casted value
  ///-------------------------------------------------------------------------
  template <typename T_ReturnType, typename T_ToCast>
  T_ReturnType CastNumber(T_ToCast a_value);

};};};


#endif