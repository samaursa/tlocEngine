#include "tlocMesh.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  Mesh::
    Mesh()
    : base_type("Mesh")
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mesh);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Mesh);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Mesh);