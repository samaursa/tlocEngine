#ifndef _TLOC_GRAPHICS_TYPES_ASPECT_RATIO_H_
#define _TLOC_GRAPHICS_TYPES_ASPECT_RATIO_H_

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocStrongType.h>

namespace tloc { namespace graphics { namespace types {

  class AspectRatio
  {
  public:
    typedef tl_float                                      value_type;
    typedef core::types::StrongType_T<tl_float, 0>        width;
    typedef core::types::StrongType_T<tl_float, 1>        height;

  public:
    AspectRatio    (width a_width = width(640.0f),
                    height a_height = height(480.0f));
    AspectRatio    (height a_height, width a_width);
    AspectRatio    (const AspectRatio& a_other);
    void operator= (const AspectRatio& a_other);

    value_type GetInv() const;
    TLOC_DECL_AND_DEF_GETTER(value_type, Get, m_ratio);

  private:

    value_type  m_ratio;

  };

};};};

#endif