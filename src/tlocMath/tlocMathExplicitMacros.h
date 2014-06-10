#ifndef _TLOC_MATH_EXPLICIT_MACROS_H_
#define _TLOC_MATH_EXPLICIT_MACROS_H_

#define TLOC_EXPLICITLY_INSTANTIATE_MATH(_type_)\
  template <>\
  const _type_ Math<_type_>::PI               = (_type_)(4.0f*atan(1.0f));\
  template <>\
  const _type_ Math<_type_>::EPSILON          = std::numeric_limits<_type_>::epsilon();\
  template <>\
  const _type_ Math<_type_>::ZERO_TOLERANCE   = std::numeric_limits<_type_>::epsilon();\
  template <>\
  const _type_ Math<_type_>::MAX_REAL         = std::numeric_limits<_type_>::max();\
  template <>\
  const _type_ Math<_type_>::TWO_PI           = Math<_type_>::PI * 2.0f;\
  template <>\
  const _type_ Math<_type_>::HALF_PI          = Math<_type_>::PI * 0.5f;\
  template <>\
  const _type_ Math<_type_>::INV_PI           = (_type_)(1.0f / Math<_type_>::PI);\
  template <>\
  const _type_ Math<_type_>::INV_TWO_PI       = (_type_)(1.0f / Math<_type_>::TWO_PI);\
  template <>\
  const _type_ Math<_type_>::DEG_TO_RAD       = (_type_)(Math<_type_>::PI/180.0f);\
  template <>\
  const _type_ Math<_type_>::RAD_TO_DEG       = (_type_)(180.0f/Math<_type_>::PI);\
  template <>\
  const _type_ Math<_type_>::LOGN_2           = math::Log(2.0f);\
  template <>\
  const _type_ Math<_type_>::LOGN_10          = math::Log(10.0f);\
  template <>\
  const _type_ Math<_type_>::INV_LOGN_2       = 1.0f / Math<_type_>::LOGN_2;\
  template <>\
  const _type_ Math<_type_>::INV_LOGN_10      = 1.0f / Math<_type_>::LOGN_10;\
  \
  template class Math<_type_>


#endif