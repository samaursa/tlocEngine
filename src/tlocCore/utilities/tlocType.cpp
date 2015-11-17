#include "tlocType.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/tlocAssert.h>

#include <limits>

namespace tloc { namespace core { namespace utils {

  namespace p_do_cast_to_32
  {
#define CHECK_AND_CAST_TO_32(_type_)\
  TLOC_ASSERT(a_value < std::numeric_limits<_type_>::max(), \
    "Casting will result in loss of information!");\
      return (_type_)a_value

    template <typename T_ReturnType, typename T_ToCast>
    T_ReturnType 
      do_cast_to_32(T_ToCast a_value)
    { return a_value; }

    template <>
    s32 
      do_cast_to_32<s32, s64>(s64 a_value)
    { CHECK_AND_CAST_TO_32(s32); }

    template <>
    u32 
      do_cast_to_32<u32, u64>(u64 a_value)
    { CHECK_AND_CAST_TO_32(u32); }

    template <>
    f32 
      do_cast_to_32<f32, f64>(f64 a_value)
    { CHECK_AND_CAST_TO_32(f32); }

#undef CHECK_AND_CAST_TO_32
  };

  template <typename T_ReturnType, typename T_ToCast>
  T_ReturnType 
    cast_to_32(T_ToCast a_value)
  {
    return p_do_cast_to_32::do_cast_to_32<T_ReturnType, T_ToCast>(a_value);
  }

  namespace p_cast_number
  {
#define CHECK_AND_CAST_TO_SIGNED(_type_, _toCast_)\
  TLOC_ASSERT(a_value <= (_toCast_)std::numeric_limits<_type_>::max(), \
    "Casting will result in loss of information!");\
      return (_type_)a_value

#define CHECK_AND_CAST_SMALL_TO_SIGNED(_type_, _toCast_)\
  TLOC_ASSERT( (_type_)a_value <= std::numeric_limits<_type_>::max(), \
    "Casting will result in loss of information!");\
      return (_type_)a_value

#define CHECK_AND_CAST_TO_UNSIGNED(_type_, _toCast_)\
  TLOC_ASSERT(a_value >= 0 && (_type_)a_value <= \
              std::numeric_limits<_type_>::max(), \
                "Casting will result in loss of information!");\
    return (_type_)a_value

#define CHECK_AND_CAST_TO_UNSIGNED_SMALL(_type_, _toCast_)\
  TLOC_ASSERT(a_value >= 0 && a_value <= \
              (_toCast_)std::numeric_limits<_type_>::max(), \
                "Casting will result in loss of information!");\
    return (_type_)a_value

    template <typename T_ReturnType, typename T_ToCast>
    T_ReturnType do_cast_number(T_ToCast a_value)
    { return (T_ReturnType)a_value; }

    template <>
    s8 do_cast_number<s8, s32>(s32 a_value)
    { CHECK_AND_CAST_TO_SIGNED(s8, s32); }

    template <>
    s8 do_cast_number<s8, s64>(s64 a_value)
    { CHECK_AND_CAST_TO_SIGNED(s8, s64); }

    template <>
    s8 do_cast_number<s8, u32>(u32 a_value)
    { CHECK_AND_CAST_TO_SIGNED(s8, u32); }

    template <>
    s8 do_cast_number<s8, u64>(u64 a_value)
    { CHECK_AND_CAST_TO_SIGNED(s8, u64); }

    template <>
    u8 do_cast_number<u8, s32>(s32 a_value)
    { CHECK_AND_CAST_TO_UNSIGNED_SMALL(u8, s32); }

    template <>
    u8 do_cast_number<u8, s64>(s64 a_value)
    { CHECK_AND_CAST_TO_UNSIGNED_SMALL(u8, s64); }

    template <>
    u8 do_cast_number<u8, u32>(u32 a_value)
    { CHECK_AND_CAST_TO_UNSIGNED_SMALL(u8, u32); }

    template <>
    u8 do_cast_number<u8, u64>(u64 a_value)
    { CHECK_AND_CAST_TO_UNSIGNED_SMALL(u8, u64); }

    template <>
    s32 do_cast_number<s32, u32>(u32 a_value)
    { CHECK_AND_CAST_TO_SIGNED(s32, u32); }

    template <>
    u32 do_cast_number<u32, s32>(s32 a_value)
    { CHECK_AND_CAST_TO_UNSIGNED(u32, s32); }

#undef CHECK_AND_CAST_TO_SIGNED

  };

  template <typename T_ReturnType, typename T_ToCast>
  T_ReturnType cast_number(T_ToCast a_value)
  {
    return p_cast_number::do_cast_number<T_ReturnType, T_ToCast>(a_value);
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template s32 cast_to_32(s32);
  template s32 cast_to_32(s64);

  template u32 cast_to_32(u32);
  template u32 cast_to_32(u64);

  template f32 cast_to_32(f32);
  template f32 cast_to_32(f64);

#define INSTANTIATE_CAST_NUMBER(_type_)\
  template _type_  cast_number(s8);\
  template _type_  cast_number(u8);\
  template _type_  cast_number(s16);\
  template _type_  cast_number(u16);\
  template _type_  cast_number(s32);\
  template _type_  cast_number(u32);\
  template _type_  cast_number(s64);\
  template _type_  cast_number(u64);\
  template _type_  cast_number(f32);\
  template _type_  cast_number(f64);\
  template _type_  cast_number(tl_long);\
  template _type_  cast_number(tl_ulong)

  INSTANTIATE_CAST_NUMBER(char32);
  INSTANTIATE_CAST_NUMBER(s8);
  INSTANTIATE_CAST_NUMBER(u8);
  INSTANTIATE_CAST_NUMBER(s16);
  INSTANTIATE_CAST_NUMBER(u16);
  INSTANTIATE_CAST_NUMBER(s32);
  INSTANTIATE_CAST_NUMBER(s64);
  INSTANTIATE_CAST_NUMBER(u32);
  INSTANTIATE_CAST_NUMBER(u64);
  INSTANTIATE_CAST_NUMBER(f32);
  INSTANTIATE_CAST_NUMBER(f64);
  INSTANTIATE_CAST_NUMBER(tl_long);
  INSTANTIATE_CAST_NUMBER(tl_ulong);

};};};