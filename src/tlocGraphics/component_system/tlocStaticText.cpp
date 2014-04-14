#include "tlocStaticText.h"

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // StaticText

  StaticText::
    StaticText()
    : base_type(k_component_type)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticText::
    StaticText(BufferArgW a_text, font_size_type a_size)
    : base_type(k_component_type)
    , m_text(a_text)
    , m_fontSize(a_size)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(StaticText);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(StaticText);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(StaticText);