#ifndef _TLOC_MATH_STATISTICS_FUNCTION_INL_
#define _TLOC_MATH_STATISTICS_FUNCTION_INL_

#ifndef _TLOC_MATH_STATISTICS_FUNCTION_H_
#error "Must include header before including the inline file"
#endif

#include "tlocStatFunction.h"

namespace tloc { namespace math { namespace statistics {

  // ///////////////////////////////////////////////////////////////////////
  // Function_T<>

#define TLOC_MATH_STAT_FUNCTION_TEMPS   typename T_ArrayPtr, typename T_Method
#define TLOC_MATH_STAT_FUNCTION_PARAMS  T_ArrayPtr, T_Method
#define TLOC_MATH_STAT_FUNCTION_TYPE    typename Function_T<TLOC_MATH_STAT_FUNCTION_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_MATH_STAT_FUNCTION_TEMPS>
  Function_T<TLOC_MATH_STAT_FUNCTION_PARAMS>::
    Function_T(array_ptr a_data)
    : m_data(a_data)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_MATH_STAT_FUNCTION_TEMPS>
  Function_T<TLOC_MATH_STAT_FUNCTION_PARAMS>::
    Function_T(array_ptr a_data, func_type a_func)
    : m_data(a_data)
    , m_func(a_func)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_MATH_STAT_FUNCTION_TEMPS>
  TLOC_MATH_STAT_FUNCTION_TYPE::value_type
    Function_T<TLOC_MATH_STAT_FUNCTION_PARAMS>::
    Calculate()
  {
    m_result = m_func.DoCalculate(*m_data);
    return m_result;
  }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_STATISTICS_FUNCTION(_array_, _method_)\
  template class tloc::math::statistics::Function_T< _array_*, _method_ >;\
  template class tloc::math::statistics::Function_T< tloc::core::smart_ptr::SharedPtr<_array_>, _method_ >

#endif