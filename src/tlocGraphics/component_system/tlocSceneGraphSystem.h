#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_SCENE_GRAPH_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_SCENE_GRAPH_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>

namespace tloc { namespace graphics { namespace component_system {

  class SceneGraphSystem
    : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem    base_type;

  public:
    SceneGraphSystem(event_manager_ptr   a_eventMgr,
                     entity_manager_ptr  a_entityMgr);

    virtual void SortEntities();

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();

    virtual error_type Post_ReInitialize();

    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(SceneGraphSystem, scene_graph_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(SceneGraphSystem, scene_graph_system);

  // -----------------------------------------------------------------------
  // meta functions

  namespace f_scene_graph
  {
    typedef SceneGraphSystem::entity_manager_ptr        entity_manager_ptr;
    typedef SceneGraphSystem::const_entity_ptr          const_entity_ptr;

    void 
      DeactivateHierarchy(entity_manager_ptr a_mgr, const_entity_ptr a_parent);

    void 
      ActivateHierarchy(entity_manager_ptr a_mgr, const_entity_ptr a_parent);

    void 
      DeactivateHierarchy(const_entity_ptr a_parent);

    void 
      ActivateHierarchy(const_entity_ptr a_parent);
  };

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::SceneGraphSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::SceneGraphSystem);

#endif