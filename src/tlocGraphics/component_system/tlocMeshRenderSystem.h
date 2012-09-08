#pragma once
#ifndef TLOC_MESH_RENDER_SYSTEM_H
#define TLOC_MESH_RENDER_SYSTEM_H

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>


namespace tloc { namespace graphics { namespace component_system {

  class MeshRenderSystem : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem  base_type;
    using base_type::component_type;

    typedef core::component_system::EventManager        event_manager;
    typedef core::component_system::EntityManager       entity_manager;
    typedef core::component_system::Entity              entity_type;

    MeshRenderSystem(event_manager* a_eventMgr, entity_manager* a_entityMgr);
    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent);
  };

};};};

#endif