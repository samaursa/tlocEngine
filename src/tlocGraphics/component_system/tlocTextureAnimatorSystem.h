#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXTURE_ANIMATOR_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

namespace tloc { namespace graphics { namespace component_system {

  class TextureAnimatorSystem
    : public core::component_system::EntityProcessingSystem
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
    TextureAnimatorSystem(event_manager_sptr a_eventMgr,
                          entity_manager_sptr a_entityMgr);

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(const entity_manager* a_mgr,
                                        const entity_type* a_ent);
    virtual error_type ShutdownEntity(const entity_manager* a_mgr,
                                      const entity_type* a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void ProcessEntity(const entity_manager* a_mgr,
                               const entity_type* a_ent,
                               f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  private:
    f64   m_totalTime;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef core_sptr::SharedPtr
    <TextureAnimatorSystem>                   texture_animation_system_sptr;

};};};

#endif