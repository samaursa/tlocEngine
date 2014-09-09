#include "tlocText_I.h"

namespace tloc { namespace graphics { namespace component_system {

#define TLOC_TEXT_TEMPS   typename T_Derived
#define TLOC_TEXT_PARAMS  T_Derived

  // ///////////////////////////////////////////////////////////////////////
  // Text_TI

  Text_I::
    Text_I()
    : m_verticalKerning(0)
    , m_alignment(alignment::k_align_left)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Text_I::
    Text_I(BufferArgW a_text, font_ptr a_font, align_type a_alignment)
    : m_text(a_text)
    , m_verticalKerning(0)
    , m_alignment(a_alignment)
    , m_font(a_font)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Text_I::
    ~Text_I()
  { }

};};};

#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::gfx_cs::Text_I);