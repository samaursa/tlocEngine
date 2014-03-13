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

  public:
    ArcBallSystem(event_manager_ptr a_eventMgr,
                  entity_manager_ptr a_entityMgr);

    virtual error_type Pre_Initialize() { return ErrorSuccess; }

    virtual error_type InitializeEntity(entity_ptr)
    { return ErrorSuccess; }

    virtual error_type ShutdownEntity(entity_ptr)
    { return ErrorSuccess; }

    virtual void Pre_ProcessActiveEntities(f64) {}
    virtual void Post_ProcessActiveEntities(f64) {}
    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

    virtual void ProcessEntity(entity_ptr a_ent,
                               f64 a_deltaT);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(ArcBallSystem, arc_ball_system);

};};};

#endif

