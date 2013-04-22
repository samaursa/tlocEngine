#include "tlocMeshRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  MeshRenderSystem::MeshRenderSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr
    , Variadic<component_type, 1>(components::mesh))
  {
  }

  MeshRenderSystem::error_type MeshRenderSystem::Initialize()
  { return ErrorSuccess; }

  MeshRenderSystem::error_type MeshRenderSystem::Shutdown()
  { return ErrorSuccess; }

  void MeshRenderSystem::ProcessEntity(const entity_manager* ,
                                       const entity_type* )
  {
  }

  void MeshRenderSystem::Pre_OnEvent(const event_type& a_event)
  { TLOC_UNUSED(a_event); }

  void MeshRenderSystem::Post_OnEvent(const event_type& a_event)
  { TLOC_UNUSED(a_event); }

};};};