#include "tlocStaticText.h"

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // StaticText

  StaticText::
    StaticText()
    : base_type("StaticText")
    , Text_I()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticText::
    StaticText(BufferArgW a_text, font_ptr a_font, align_type a_alignment)
    : base_type("StaticText")
    , Text_I(a_text, a_font, a_alignment)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    StaticText::
    SetAlignment(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    Text_I::SetAlignment(a_alignment);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(StaticText);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(StaticText);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(StaticText);