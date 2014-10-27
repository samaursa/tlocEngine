#include "tlocQuad.h"

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Quad

  Quad::
    Quad()
    : base_type("Quad")
    , m_rect(rect_type::width(1.0f), rect_type::height(1.0f))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Quad::
    Quad(const rect_type& a_rect)
    : base_type("Quad")
    , m_rect(a_rect)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Quad);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Quad);