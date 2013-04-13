#include "tlocAspectRatio.h"

#include <tlocMath/tlocMath.h>

namespace tloc { namespace math { namespace types {

  AspectRatio::AspectRatio(width a_width, height a_height)
    : m_ratio( a_width.m_value / a_height.m_value)
  {
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::IsEqual(a_height, 0.0f) == false,
                          "Divide by zero!");
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::IsEqual(m_ratio, 0.0f) == false,
                          "Aspect ratio cannot be zero!");
  }

  AspectRatio::AspectRatio(const AspectRatio& a_other)
    : m_ratio(a_other.m_ratio)
  {
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::IsEqual(m_ratio, 0.0f) == false,
                          "Aspect ratio cannot be zero!");
  }

  void AspectRatio::operator= (const AspectRatio& a_other)
  {
    m_ratio = a_other.m_ratio;
  }

  AspectRatio::value_type AspectRatio::GetInv() const
  {
    return 1 / Get();
  }

};};};