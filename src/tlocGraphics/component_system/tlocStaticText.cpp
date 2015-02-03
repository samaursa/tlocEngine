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
    StaticText(BufferArgW a_text, font_ptr a_font, align_type a_alignment, 
               align_type a_horAlignment)
    : base_type("StaticText")
    , Text_I(a_text, a_font, a_alignment, a_horAlignment)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    StaticText::
    SetAlignment(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    Text_I::SetAlignment(a_alignment);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    StaticText::
    SetHorizontalAlignment(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    Text_I::SetHorizontalAlignment(a_alignment);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

using namespace tloc::gfx_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(StaticText);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(StaticText);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(StaticText);