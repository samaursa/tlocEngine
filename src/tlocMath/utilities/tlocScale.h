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

  typedef Scale_T<s8, s8>     scale_s8_s8;
  typedef Scale_T<s8, s16>    scale_s8_s16;
  typedef Scale_T<s8, s32>    scale_s8_s32;
  typedef Scale_T<s8, s64>    scale_s8_s64;
  typedef Scale_T<s8, u8>     scale_s8_u8;
  typedef Scale_T<s8, u16>    scale_s8_u16;
  typedef Scale_T<s8, u32>    scale_s8_u32;
  typedef Scale_T<s8, u64>    scale_s8_u64;
  typedef Scale_T<s8, f32>    scale_s8_f32;
  typedef Scale_T<s8, f64>    scale_s8_f64;

  typedef Scale_T<s16, s8>    scale_s16_s8;
  typedef Scale_T<s16, s16>   scale_s16_s16;
  typedef Scale_T<s16, s32>   scale_s16_s32;
  typedef Scale_T<s16, s64>   scale_s16_s64;
  typedef Scale_T<s16, u8>    scale_s16_u8;
  typedef Scale_T<s16, u16>   scale_s16_u16;
  typedef Scale_T<s16, u32>   scale_s16_u32;
  typedef Scale_T<s16, u64>   scale_s16_u64;
  typedef Scale_T<s16, f32>   scale_s16_f32;
  typedef Scale_T<s16, f64>   scale_s16_f64;

  typedef Scale_T<s32, s8>    scale_s32_s8;
  typedef Scale_T<s32, s16>   scale_s32_s16;
  typedef Scale_T<s32, s32>   scale_s32_s32;
  typedef Scale_T<s32, s64>   scale_s32_s64;
  typedef Scale_T<s32, u8>    scale_s32_u8;
  typedef Scale_T<s32, u16>   scale_s32_u16;
  typedef Scale_T<s32, u32>   scale_s32_u32;
  typedef Scale_T<s32, u64>   scale_s32_u64;
  typedef Scale_T<s32, f32>   scale_s32_f32;
  typedef Scale_T<s32, f64>   scale_s32_f64;

  typedef Scale_T<s64, s8>    scale_s64_s8;
  typedef Scale_T<s64, s16>   scale_s64_s16;
  typedef Scale_T<s64, s32>   scale_s64_s32;
  typedef Scale_T<s64, s64>   scale_s64_s64;
  typedef Scale_T<s64, u8>    scale_s64_u8;
  typedef Scale_T<s64, u16>   scale_s64_u16;
  typedef Scale_T<s64, u32>   scale_s64_u32;
  typedef Scale_T<s64, u64>   scale_s64_u64;
  typedef Scale_T<s64, f32>   scale_s64_f32;
  typedef Scale_T<s64, f64>   scale_s64_f64;

  typedef Scale_T<u8, s8>     scale_u8_s8;
  typedef Scale_T<u8, s16>    scale_u8_s16;
  typedef Scale_T<u8, s32>    scale_u8_s32;
  typedef Scale_T<u8, s64>    scale_u8_s64;
  typedef Scale_T<u8, u8>     scale_u8_u8;
  typedef Scale_T<u8, u16>    scale_u8_u16;
  typedef Scale_T<u8, u32>    scale_u8_u32;
  typedef Scale_T<u8, u64>    scale_u8_u64;
  typedef Scale_T<u8, f32>    scale_u8_f32;
  typedef Scale_T<u8, f64>    scale_u8_f64;

  typedef Scale_T<u16, s8>    scale_u16_s8;
  typedef Scale_T<u16, s16>   scale_u16_s16;
  typedef Scale_T<u16, s32>   scale_u16_s32;
  typedef Scale_T<u16, s64>   scale_u16_s64;
  typedef Scale_T<u16, u8>    scale_u16_u8;
  typedef Scale_T<u16, u16>   scale_u16_u16;
  typedef Scale_T<u16, u32>   scale_u16_u32;
  typedef Scale_T<u16, u64>   scale_u16_u64;
  typedef Scale_T<u16, f32>   scale_u16_f32;
  typedef Scale_T<u16, f64>   scale_u16_f64;

  typedef Scale_T<u32, s8>    scale_u32_s8;
  typedef Scale_T<u32, s16>   scale_u32_s16;
  typedef Scale_T<u32, s32>   scale_u32_s32;
  typedef Scale_T<u32, s64>   scale_u32_s64;
  typedef Scale_T<u32, u8>    scale_u32_u8;
  typedef Scale_T<u32, u16>   scale_u32_u16;
  typedef Scale_T<u32, u32>   scale_u32_u32;
  typedef Scale_T<u32, u64>   scale_u32_u64;
  typedef Scale_T<u32, f32>   scale_u32_f32;
  typedef Scale_T<u32, f64>   scale_u32_f64;

  typedef Scale_T<u64, s8>    scale_u64_s8;
  typedef Scale_T<u64, s16>   scale_u64_s16;
  typedef Scale_T<u64, s32>   scale_u64_s32;
  typedef Scale_T<u64, s64>   scale_u64_s64;
  typedef Scale_T<u64, u8>    scale_u64_u8;
  typedef Scale_T<u64, u16>   scale_u64_u16;
  typedef Scale_T<u64, u32>   scale_u64_u32;
  typedef Scale_T<u64, u64>   scale_u64_u64;
  typedef Scale_T<u64, f32>   scale_u64_f32;
  typedef Scale_T<u64, f64>   scale_u64_f64;

  typedef Scale_T<f32, s8>    scale_f32_s8;
  typedef Scale_T<f32, s16>   scale_f32_s16;
  typedef Scale_T<f32, s32>   scale_f32_s32;
  typedef Scale_T<f32, s64>   scale_f32_s64;
  typedef Scale_T<f32, u8>    scale_f32_u8;
  typedef Scale_T<f32, u16>   scale_f32_u16;
  typedef Scale_T<f32, u32>   scale_f32_u32;
  typedef Scale_T<f32, u64>   scale_f32_u64;
  typedef Scale_T<f32, f32>   scale_f32_f32;
  typedef Scale_T<f32, f64>   scale_f32_f64;

  typedef Scale_T<f64, s8>    scale_f64_s8;
  typedef Scale_T<f64, s16>   scale_f64_s16;
  typedef Scale_T<f64, s32>   scale_f64_s32;
  typedef Scale_T<f64, s64>   scale_f64_s64;
  typedef Scale_T<f64, u8>    scale_f64_u8;
  typedef Scale_T<f64, u16>   scale_f64_u16;
  typedef Scale_T<f64, u32>   scale_f64_u32;
  typedef Scale_T<f64, u64>   scale_f64_u64;
  typedef Scale_T<f64, f32>   scale_f64_f32;
  typedef Scale_T<f64, f64>   scale_f64_f64;
};};};

#endif