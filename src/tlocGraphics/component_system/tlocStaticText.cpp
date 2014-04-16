#include "tlocStaticText.h"

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // StaticText

  StaticText::
    StaticText()
    : base_type(k_component_type)
    , m_alignment(k_align_left)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticText::
    StaticText(BufferArgW a_text, align_type a_alignment)
    : base_type(k_component_type)
    , m_text(a_text)
    , m_alignment(a_alignment)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    StaticText::
    Align(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    m_alignment = a_alignment;
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