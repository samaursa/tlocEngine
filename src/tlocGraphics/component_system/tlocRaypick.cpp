#include "tlocRaypick.h"

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Rapick3D

  Raypick::
    Raypick()
    : base_type("Raypick")
    , m_distanceChecked(true)
  { }

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Raypick);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Raypick);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Raypick);