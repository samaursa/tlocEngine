#include "tlocMesh.h"

namespace tloc { namespace graphics { namespace component_system {

#define MESH_TEMPS  typename T_VertexStoragePolicy
#define MESH_PARAMS T_VertexStoragePolicy
#define MESH_TYPE   typename Mesh_T<MESH_PARAMS>

  template <MESH_TEMPS>
  Mesh_T<MESH_PARAMS>::
    Mesh_T()
    : base_type(vertex_storage_policy::k_component_id)
  { }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class Mesh_T<p_primitive::ArrayOfStructures>;
  template class Mesh_T<p_primitive::StructureOfArrays>;

};};};