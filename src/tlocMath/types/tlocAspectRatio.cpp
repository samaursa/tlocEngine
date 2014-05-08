#include "tlocAspectRatio.h"

#include <tlocCore/tlocAssert.h>
#include <tlocMath/tlocMath.h>

namespace tloc { namespace math { namespace types {

#define ASPECT_RATIO_TEMPS  typename T_Real
#define ASPECT_RATIO_PARAMS T_Real
#define ASPECT_RATIO_TYPE   typename AspectRatio_T<ASPECT_RATIO_PARAMS>

  template <ASPECT_RATIO_TEMPS>
  AspectRatio_T<ASPECT_RATIO_PARAMS>::
    AspectRatio_T(width a_width, height a_height)
    : m_ratio( a_width.m_value / a_height.m_value)
  {
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::IsEqual(a_height, 0.0f) == false,
                          "Divide by zero!");
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::IsEqual(m_ratio, 0.0f) == false,
                          "Aspect ratio cannot be zero!");
  }

  template <ASPECT_RATIO_TEMPS>
  AspectRatio_T<ASPECT_RATIO_PARAMS>::
    AspectRatio_T(const this_type& a_other)
    : m_ratio(a_other.m_ratio)
  {
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::IsEqual(m_ratio, 0.0f) == false,
                          "Aspect ratio cannot be zero!");
  }

  template <ASPECT_RATIO_TEMPS>
  void AspectRatio_T<ASPECT_RATIO_PARAMS>::
    operator= (const this_type& a_other)
  {
    m_ratio = a_other.m_ratio;
  }

  template <ASPECT_RATIO_TEMPS>
  ASPECT_RATIO_TYPE::value_type
    AspectRatio_T<ASPECT_RATIO_PARAMS>::
    GetInv() const
  {
    return 1 / Get();
  }

  //------------------------------------------------------------------------
  // explicit instantiations

  template class AspectRatio_T<f32>;
  template class AspectRatio_T<f64>;

};};};