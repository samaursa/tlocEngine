#include "tlocSkyBox.h"

#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace graphics { namespace component_system {

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SkyBox::
    SkyBox(tex_obj_type a_cubeMap)
    : base_type("SkyBox")
    , m_cubeMap(a_cubeMap)
  { 
  }

};};};

// -----------------------------------------------------------------------
// Explicit Instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SkyBox);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(SkyBox);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(SkyBox);