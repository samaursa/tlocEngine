#include "tlocBasicTypes.h"

#include <limits>

namespace tloc {

  // ///////////////////////////////////////////////////////////////////////
  // NumericLimits_T<tl_size>

#define NUMERIC_LIMITS_TEMPS  typename T
#define NUMERIC_LIMITS_PARAMS T
#define NUMERIC_LIMITS_TYPE   typename NumericLimits_T<T>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <NUMERIC_LIMITS_TEMPS>
  NUMERIC_LIMITS_TYPE::value_type
    NumericLimits_T<NUMERIC_LIMITS_PARAMS>::
    min()
  {
    return std::numeric_limits<value_type>::min();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <NUMERIC_LIMITS_TEMPS>
  NUMERIC_LIMITS_TYPE::value_type
    NumericLimits_T<NUMERIC_LIMITS_PARAMS>::
    max()
  {
    return std::numeric_limits<value_type>::max();
  }

  // ///////////////////////////////////////////////////////////////////////
  // explicit specializations

  template class NumericLimits_T<tl_int>;
  template class NumericLimits_T<tl_uint>;
  template class NumericLimits_T<tl_size>;

};