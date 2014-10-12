#include "tlocFan.h"

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Fan::
    Fan()
    : base_type(k_component_type, "Fan")
    , m_ellipse(ellipse_type::diameter(1.0f))
    , m_sides(sides(8))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Fan::
    Fan(const ellipse_type& a_ellipse, sides a_sides)
    : base_type(k_component_type, "Fan")
    , m_ellipse(a_ellipse)
    , m_sides(a_sides)
  { }

};};};

// -----------------------------------------------------------------------
// Explicit Instantiations

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Fan);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Fan);