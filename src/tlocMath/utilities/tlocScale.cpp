#include "tlocScale.h"

#include <tlocCore/utilities/tlocType.h>
#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl.h>

namespace tloc { namespace math { namespace utils {

#define SCALE_TEMPS   typename T_ValueFrom, typename T_ValueTo, typename T_CommonType
#define SCALE_PARAMS  T_ValueFrom, T_ValueTo, T_CommonType
#define SCALE_TYPE    typename Scale_T<SCALE_PARAMS>

  template <SCALE_TEMPS>
  Scale_T<SCALE_PARAMS>::
    Scale_T(range_small a_smallRange, range_large a_largeRange)
    : m_smallRange(a_smallRange)
    , m_largeRange(a_largeRange)
  {
    TLOC_ASSERT(m_smallRange.size() <= m_largeRange.size(),
      "a_rangeFrom size must be smaller than a_rangeTo size");
  }

  template <SCALE_TEMPS>
  SCALE_TYPE::large_value_type
    Scale_T<SCALE_PARAMS>::
    ScaleUp(small_value_type a_valueToScale) const
  {
    TLOC_ASSERT( m_smallRange.IsInRange(a_valueToScale), "Value out of range!");

    small_value_type r1Size;
    large_value_type r2Size;

    r1Size = m_smallRange.back() - m_smallRange.front();
    r2Size = m_largeRange.back() - m_largeRange.front();

    TLOC_ASSERT(Approx<small_value_type>(r1Size, 0) != true,
      "Divide by zero!");

    a_valueToScale -= m_smallRange.front();

    common_type valPerc = (common_type)a_valueToScale / (common_type)r1Size;
    common_type valConverted = (common_type)r2Size * valPerc;
    large_value_type finalVal =
      core_utils::CastNumber<large_value_type, common_type>(valConverted);

    finalVal += m_largeRange.front();

    return finalVal;
  }

  template <SCALE_TEMPS>
  SCALE_TYPE::small_value_type
    Scale_T<SCALE_PARAMS>::
    ScaleDown(large_value_type a_valueToScale) const
  {
    TLOC_ASSERT( m_largeRange.IsInRange(a_valueToScale), "Value out of range!");

    small_value_type r1Size;
    large_value_type r2Size;

    r1Size = m_smallRange.back() - m_smallRange.front();
    r2Size = m_largeRange.back() - m_largeRange.front();

    TLOC_ASSERT(Approx<large_value_type>(r2Size, 0) != true,
      "Divide by zero!");

    a_valueToScale -= m_largeRange.front();

    common_type valPerc = (common_type)a_valueToScale / (common_type)r2Size;
    common_type valConverted = (common_type)r1Size * valPerc;
    small_value_type finalVal =
      core_utils::CastNumber<small_value_type, common_type>(valConverted);

    finalVal += m_smallRange.front();

    return finalVal;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation

#define TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type1_, _type2_)\
  template class Scale_T<_type1_, _type2_, f64>;\
  template class Scale_T<_type1_, _type2_, f32>

#define TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(_type_)\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s8);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s16);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s32);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s64);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u8);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u16);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u32);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u64);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, f32);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, f64)

  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(s8);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(s16);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(s32);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(s64);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(u8);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(u16);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(u32);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(u64);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(f32);
  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(f64);

};};};