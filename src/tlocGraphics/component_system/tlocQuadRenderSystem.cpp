#include "tlocQuadRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace component_system {

  QuadRenderSystem::QuadRenderSystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::quad))
  { }

  QuadRenderSystem::error_type QuadRenderSystem::Initialize()
  { return ErrorSuccess(); }

  QuadRenderSystem::error_type QuadRenderSystem::Shutdown()
  { return ErrorSuccess(); }

  void QuadRenderSystem::ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    using namespace core::component_system;
    typedef graphics::component_system::Quad    quad_type;

    const entity_type* ent = a_ent;
    ComponentMapper<quad_type> mesh = ent->GetComponents(components::mesh);

    if (a_ent->HasComponent(components::material))
    {
      // Prepare the material
    }

    // Render
    TLOC_UNUSED(a_mgr);
  }

  void QuadRenderSystem::Pre_OnEvent(const event_type& a_event)
  { TLOC_UNUSED(a_event); }

  void QuadRenderSystem::Post_OnEvent(const event_type& a_event)
  { TLOC_UNUSED(a_event); }

};};};