#pragma once
#ifndef _TLOC_INPUT_COMPONENT_SYSTEM_ARCBALL_CONTROL_SYSTEM_H_
#define _TLOC_INPUT_COMPONENT_SYSTEM_ARCBALL_CONTROL_SYSTEM_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocInput/hid/tlocKeyboard.h>
#include <tlocInput/hid/tlocMouse.h>

namespace tloc { namespace input { namespace component_system {

  class ArcBallControlSystem
    : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem      base_type;
    typedef core_dispatch::Event                                event_type;
    typedef tl_float                                            real_type;

  public:
    ArcBallControlSystem(event_manager_ptr a_eventMgr,
                         entity_manager_ptr a_entityMgr);

    virtual error_type Pre_Initialize();

    virtual error_type InitializeEntity(entity_ptr);
    virtual error_type ShutdownEntity(entity_ptr);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&);
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&);

    virtual void ProcessEntity(entity_ptr a_ent, f64 );
    virtual void Post_ProcessActiveEntities(f64 );

    // -----------------------------------------------------------------------
    // callbacks

    event_type    OnButtonPress(const tl_size, const input_hid::MouseEvent&,
                                const input_hid::MouseEvent::button_code_type a_button);
    event_type    OnButtonRelease(const tl_size, const input_hid::MouseEvent&,
                                  const input_hid::MouseEvent::button_code_type a_button);
    event_type    OnMouseMove(const tl_size, const input_hid::MouseEvent& a_event);

    event_type    OnKeyPress(const tl_size, const input_hid::KeyboardEvent& a_event);
    event_type    OnKeyRelease(const tl_size, const input_hid::KeyboardEvent& a_event);

  private:
    core_utils::Checkpoints       m_flags;
    real_type                     m_xRel, m_yRel;

  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(ArcBallControlSystem, arc_ball_control_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(ArcBallControlSystem, arc_ball_control_system);

};};};

TLOC_DEF_TYPE(tloc::input_cs::ArcBallControlSystem);

#endif

