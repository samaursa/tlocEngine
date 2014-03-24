#include "tlocGlyph.h"

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // Glyph

  Glyph::
    Glyph()
    : m_dimensions(core_ds::MakeTuple(0, 0))
    , m_bearing(core_ds::MakeTuple(0, 0))
    , m_advance(0)
  { }

};};};