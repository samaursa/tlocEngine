#ifndef _TLOC_MATH_TYPES_NORMALIZER_H_
#define _TLOC_MATH_TYPES_NORMALIZER_H_

#include <tlocCore/types/tlocStrongType.h>

#include <tlocMath/tlocRange.h>
#include <tlocMath/tlocMathBase.h>

namespace tloc { namespace math { namespace utils {

  template <typename T_ValueFrom, typename T_ValueTo,
            typename T_CommonType = f64>
  class Scale_T
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T_ValueFrom);
    TLOC_STATIC_ASSERT_IS_ARITH(T_ValueTo);
    TLOC_STATIC_ASSERT_IS_FLOAT(T_CommonType);

  public:
    typedef T_ValueFrom                                small_value_type;
    typedef T_ValueTo                                  large_value_type;
    typedef Scale_T<small_value_type, large_value_type>  this_type;

    typedef math::Range_T<small_value_type>            range_small;
    typedef math::Range_T<large_value_type>            range_large;

    typedef T_CommonType                               common_type;

  public:
    Scale_T(range_small a_smallRange, range_large a_largeRange);

    large_value_type ScaleUp(small_value_type a_valueToScale) const;
    small_value_type ScaleDown(large_value_type a_valueToScale) const;

  private:
    range_small  m_smallRange;
    range_large  m_largeRange;

  };

  //------------------------------------------------------------------------
  // typedefs
  //
  // Notes: typedefs take the following form: scale_typeFrom_typeTo
  //        e.g. scale_s8_s16

#define TLOC_DECLARE_SCALE_TYPES(_type_)\
  typedef Scale_T<_type_, s8>       scale_ ##_type_ ##_s8;\
  typedef Scale_T<_type_, s16>      scale_ ##_type_ ##_s16;\
  typedef Scale_T<_type_, s32>      scale_ ##_type_ ##_s32;\
  typedef Scale_T<_type_, s64>      scale_ ##_type_ ##_s64;\
  typedef Scale_T<_type_, u8>       scale_ ##_type_ ##_u8;\
  typedef Scale_T<_type_, u16>      scale_ ##_type_ ##_u16;\
  typedef Scale_T<_type_, u32>      scale_ ##_type_ ##_u32;\
  typedef Scale_T<_type_, u64>      scale_ ##_type_ ##_u64;\
  typedef Scale_T<_type_, f32>      scale_ ##_type_ ##_f32;\
  typedef Scale_T<_type_, f64>      scale_ ##_type_ ##_f64;\
  typedef Scale_T<_type_, tl_uint>  scale_ ##_type_ ##_tl_uint;\
  typedef Scale_T<_type_, tl_int>   scale_ ##_type_ ##_tl_int;\
  typedef Scale_T<_type_, tl_float> scale_ ##_type_ ##_tl_float;\
  typedef Scale_T<_type_, tl_size> scale_ ##_type_ ##_tl_size

  TLOC_DECLARE_SCALE_TYPES(s8);
  TLOC_DECLARE_SCALE_TYPES(s16);
  TLOC_DECLARE_SCALE_TYPES(s32);
  TLOC_DECLARE_SCALE_TYPES(s64);
  TLOC_DECLARE_SCALE_TYPES(u8);
  TLOC_DECLARE_SCALE_TYPES(u16);
  TLOC_DECLARE_SCALE_TYPES(u32);
  TLOC_DECLARE_SCALE_TYPES(u64);
  TLOC_DECLARE_SCALE_TYPES(f32);
  TLOC_DECLARE_SCALE_TYPES(f64);
  TLOC_DECLARE_SCALE_TYPES(tl_uint);
  TLOC_DECLARE_SCALE_TYPES(tl_int);
  TLOC_DECLARE_SCALE_TYPES(tl_float);

  typedef scale_tl_uint_tl_uint     scale_tl_uint;
  typedef scale_tl_int_tl_int       scale_tl_int;
  typedef scale_tl_float_tl_float   scale_tl_float;

};};};

#endif