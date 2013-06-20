#include "tlocMesh.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

#define MESH_TEMPS  typename T_VertexStoragePolicy
#define MESH_PARAMS T_VertexStoragePolicy
#define MESH_TYPE   typename Mesh_T<MESH_PARAMS>

  template <MESH_TEMPS>
  Mesh_T<MESH_PARAMS>::
    Mesh_T()
    : base_type(vertex_storage_policy::k_component_id)
    , m_posAttr(new gl::Attribute())
    , m_normAttr(new gl::Attribute())
    , m_tcoordAttr(new gl::Attribute())
  {
    m_posAttr->SetName("a_vPos");
    m_normAttr->SetName("a_vNorm");
    m_tcoordAttr->SetName("a_tCoord");
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiation

  template class Mesh_T<p_primitive::ArrayOfStructures>;
  template class Mesh_T<p_primitive::StructureOfArrays>;

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Mesh);
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Mesh_Interleaved);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(mesh_sptr);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(mesh_interleaved_sptr);

};};};