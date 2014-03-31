#ifndef _TLOC_GRAPHICS_MEDIA_GLYPH_H_
#define _TLOC_GRAPHICS_MEDIA_GLYPH_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace media {

  // this class will use FreeType terminology
  class Glyph
  {
  public:
    typedef math_t::Rectf             tcoord_type;
    typedef core_ds::Tuple2l          pos_type;
    typedef tl_long                   length_type;

  public:

    Glyph();

    TLOC_DECL_AND_DEF_GETTER(pos_type, GetDimensions, m_dimensions);
    TLOC_DECL_AND_DEF_GETTER(pos_type, GetBearing, m_bearing);
    TLOC_DECL_AND_DEF_GETTER(length_type, GetAdvance, m_advance);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(pos_type, SetDimensions, m_dimensions);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(pos_type, SetBearing, m_bearing);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(length_type, SetAdvance, m_advance);

  private:
    pos_type      m_dimensions;
    pos_type      m_bearing;
    length_type   m_advance;

  };

};};};

#endif