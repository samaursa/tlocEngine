#include "tlocMesh.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

#define MESH_TEMPS  typename T_VertexStoragePolicy
#define MESH_PARAMS T_VertexStoragePolicy
#define MESH_TYPE   typename Mesh_T<MESH_PARAMS>

  template <MESH_TEMPS>
  Mesh_T<MESH_PARAMS>::
    Mesh_T()
    : base_type(vertex_storage_policy::k_component_id, "Mesh")
    , m_texCoordsEnabled(true)
    , m_normalsEnabled(true)
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiation

  template class Mesh_T<p_primitive::ArrayOfStructures>;
  template class Mesh_T<p_primitive::StructureOfArrays>;


};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mesh);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Mesh_Interleaved);

TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Mesh);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Mesh_Interleaved);