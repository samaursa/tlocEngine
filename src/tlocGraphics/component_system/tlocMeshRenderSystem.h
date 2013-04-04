#pragma once
#ifndef TLOC_MESH_RENDER_SYSTEM_H
#define TLOC_MESH_RENDER_SYSTEM_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>


namespace tloc { namespace graphics { namespace component_system {

  class MeshRenderSystem : public core::component_system::EntityProcessingSystem
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

  public:
    MeshRenderSystem(event_manager_sptr a_eventMgr,
                     entity_manager_sptr a_entityMgr);

    virtual error_type Initialize();
    virtual error_type Shutdown();
    virtual void ProcessEntity(const entity_manager* a_mgr,
                               const entity_type* a_ent);

    virtual void Pre_OnEvent(const event_type& a_event);
    virtual void Post_OnEvent(const event_type& a_event);
  };

};};};

#endif