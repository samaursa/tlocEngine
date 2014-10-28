#ifndef _TLOC_MATH_TYPES_ASPECT_RATIO_H_
#define _TLOC_MATH_TYPES_ASPECT_RATIO_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocStrongType.h>

namespace tloc { namespace math { namespace types {

  template <typename T_Real>
  class AspectRatio_T
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T_Real);

  public:
    typedef T_Real                                        value_type;
    typedef AspectRatio_T<value_type>                     this_type;
    typedef core::types::StrongType_T<value_type, 0>      width;
    typedef core::types::StrongType_T<value_type, 1>      height;

  public:
    AspectRatio_T    (width a_width = width(640.0f),
                      height a_height = height(480.0f));
    AspectRatio_T   (const this_type& a_other);
    void operator=  (const this_type& a_other);

    value_type GetInv() const;
    TLOC_DECL_AND_DEF_GETTER(value_type, Get, m_ratio);

  private:

    value_type  m_ratio;

  };

  //------------------------------------------------------------------------
  // typedefs

  typedef AspectRatio_T<tl_float>   AspectRatio;
  typedef AspectRatio_T<f32>        aspect_ratio_f32;
  typedef AspectRatio_T<f64>        aspect_ratio_f64;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(AspectRatio_T<tl_float>);
  TLOC_EXTERN_TEMPLATE_CLASS(AspectRatio_T<f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(AspectRatio_T<f64>);

};};};

#endif