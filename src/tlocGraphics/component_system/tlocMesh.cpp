#include "tlocMesh.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // 2D Mesh

  Mesh_T<p_mesh::Mesh2D, p_mesh::Dynamic>::
    Mesh_T()
    : base_type("Mesh2D")
  { }

  // ///////////////////////////////////////////////////////////////////////
  // 2D Mesh - STATIC

  Mesh_T<p_mesh::Mesh2D, p_mesh::Static>::
    Mesh_T()
    : base_type("Mesh2DStatic")
  { }

  // ///////////////////////////////////////////////////////////////////////
  // 3D Mesh

  Mesh_T<p_mesh::Mesh3D, p_mesh::Dynamic>::
    Mesh_T()
    : base_type("Mesh")
  { }

  // ///////////////////////////////////////////////////////////////////////
  // 3D Mesh - STATIC

  Mesh_T<p_mesh::Mesh3D, p_mesh::Static>::
    Mesh_T()
    : base_type("MeshStatic")
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