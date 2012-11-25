#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_RENDER_SYSTEM_H_

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocMath/vector/tlocVector3.h>

namespace tloc { namespace graphics { namespace component_system {

  class QuadRenderSystem : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem  base_type;
    using base_type::component_type;
    using base_type::error_type;

    using base_type::event_manager;
    using base_type::entity_manager;
    using base_type::entity_type;
    using base_type::event_type;
    using base_type::event_value_type;

    typedef core::tl_array<math::Vec3f32>::type     vec3_cont_type;

  public:
    QuadRenderSystem(event_manager* a_eventMgr, entity_manager* a_entityMgr);

    virtual error_type Initialize();
    virtual error_type Shutdown();
    virtual void Pre_ProcessActiveEntities() {}
    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent);
    virtual void Post_ProcessActiveEntities() {}

    virtual void Pre_OnEvent(const event_type& a_event);
    virtual void Post_OnEvent(const event_type& a_event);

  private:
    vec3_cont_type  m_quadList;
  };

};};};

#endif