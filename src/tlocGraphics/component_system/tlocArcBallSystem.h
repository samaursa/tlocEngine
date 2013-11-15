#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_ARCBALL_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_ARCBALL_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

//#include <tlocMath/types/tlocVector3.h>
//#include <tlocMath/types/tlocMatrix4.h>
//#include <tlocMath/projection/tlocFrustum.h>
//#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  class ArcBallSystem
    : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem      base_type;
    using base_type::component_type;
    using base_type::error_type;

    using base_type::event_manager;
    using base_type::entity_manager;
    using base_type::entity_type;
    using base_type::event_type;
    using base_type::event_value_type;

  public:
    ArcBallSystem(event_manager_sptr a_eventMgr,
                  entity_manager_sptr a_entityMgr);

    virtual error_type Pre_Initialize() { return ErrorSuccess; }

    virtual error_type InitializeEntity(const entity_manager* ,
                                        const entity_type* )
    { return ErrorSuccess; }

    virtual error_type ShutdownEntity(const entity_manager* ,
                                      const entity_type* )
    { return ErrorSuccess; }

    virtual void Pre_ProcessActiveEntities(f64 ) {}
    virtual void Post_ProcessActiveEntities(f64 ) {}
    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

    virtual void ProcessEntity(const entity_manager* a_mgr,
                               const entity_type* a_ent,
                               f64 a_deltaT);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(ArcBallSystem, arc_ball_system);

};};};

#endif

