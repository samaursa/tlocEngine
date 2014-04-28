#ifndef _TLOC_GRAPHICS_MEDIA_FONT_SIZE_H_
#define _TLOC_GRAPHICS_MEDIA_FONT_SIZE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocStrongType.h>

namespace tloc { namespace graphics { namespace media {

  class FontSize
  {
  public:
    // freetype uses unsigned short for font size
    typedef ushort                                    size_type;
    typedef tl_float                                  real_type;
    typedef core_ds::Tuple2size                       dim_type;

    typedef core_t::StrongType_T<dim_type, 0>         dpi;
    typedef core_t::StrongType_T<dim_type, 1>         resolution;

    typedef core_t::StrongType_T<size_type, 0>        em;
    typedef core_t::StrongType_T<size_type, 1>        pixels;
    typedef core_t::StrongType_T<size_type, 2>        fraction;

  public:
    FontSize(em a_size, dpi a_dpi);
    FontSize(fraction a_0to100, resolution a_resolution);
    FontSize(pixels a_heightInPixels);

    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeightInPixels, m_heightInPixels);

  private:
    size_type       m_heightInPixels;

  };

};};};

#endif