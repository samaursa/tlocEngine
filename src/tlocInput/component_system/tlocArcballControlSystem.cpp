#include "tlocArcBallControlSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocArcBall.h>

#include <tlocInput/component_system/tlocArcballControl.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>
#include <tlocMath/utilities/tlocPythagoras.h>

namespace {

  enum 
  {
    k_alt_pressed = 0,
    k_rotating,
    k_panning,
    k_dolly,
    k_updated,
    k_count
  };

};

namespace tloc { namespace input { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  using namespace core::data_structs;

  // ///////////////////////////////////////////////////////////////////////
  // ArcBallSystem

  ArcBallControlSystem::
    ArcBallControlSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::k_arcball_control))
    , m_flags(k_count)
    , m_xRel(0.0f)
    , m_yRel(0.0f)
    , m_xPos(0.0f)
    , m_yPos(0.0f)
    , m_currentTouch(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::error_type
    ArcBallControlSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::error_type
    ArcBallControlSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    TLOC_LOG_INPUT_WARN_IF(a_ent->HasComponent<gfx_cs::ArcBall>() == false)
      << "Entity (" << a_ent->GetDebugName() << ") doesn't have an ArcBall "
      << "component. CANNOT control using ArcBallControl.";

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::error_type
    ArcBallControlSystem::
    ShutdownEntity(entity_ptr )
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControlSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControlSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControlSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControlSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControlSystem::
    ProcessEntity(entity_ptr a_ent, f64 )
  {
    if (m_flags.IsMarked(k_updated))
    {
      using math_cs::Transform;
      using gfx_cs::ArcBall;
      using input_cs::ArcBallControl;

      math_cs::transform_sptr t = a_ent->GetComponent<Transform>();
      gfx_cs::arcball_sptr arcBall = a_ent->GetComponent<ArcBall>();

      input_cs::arc_ball_control_sptr arcBallControl = 
        a_ent->GetComponent<ArcBallControl>();

      ArcBallControl::vec_type globalMulti = arcBallControl->GetGlobalMultiplier();
      ArcBallControl::vec_type rotMulti    = arcBallControl->GetRotationMultiplier();
      ArcBallControl::vec_type panMulti    = arcBallControl->GetPanMultiplier();
      ArcBallControl::real_type dollyMulti = arcBallControl->GetDollyMultiplier();

      if (m_flags.IsMarked(k_rotating))
      {
        arcBall->MoveVertical(m_yRel * globalMulti[1] * rotMulti[1]);
        arcBall->MoveHorizontal(m_xRel * globalMulti[0] * rotMulti[0]);
      }
      else if (m_flags.IsMarked(k_panning))
      {
        math_t::Vec3f leftVec =
          t->GetOrientation().GetCol(0).ConvertTo<math_t::Vec3f>();
        math_t::Vec3f upVec =
          t->GetOrientation().GetCol(1).ConvertTo<math_t::Vec3f>();
        leftVec *= m_xRel * globalMulti[0] * panMulti[0];
        upVec *= m_yRel * globalMulti[1] * panMulti[1];

        t->SetPosition(t->GetPosition() - leftVec + upVec);
        arcBall->SetFocus(arcBall->GetFocus() - leftVec + upVec);
      }
      else if (m_flags.IsMarked(k_dolly))
      {
        math_t::Vec3f dirVec =
          t->GetOrientation().GetCol(2).ConvertTo<math_t::Vec3f>();
        dirVec *= m_xRel * globalMulti[0] * dollyMulti;

        t->SetPosition(t->GetPosition() - dirVec);
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControlSystem::
    Post_ProcessActiveEntities(f64 )
  {
    m_flags.Unmark(k_updated);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnButtonPress(const tl_size, const input_hid::MouseEvent&, 
                  const input_hid::MouseEvent::button_code_type a_button)
  {
    if (a_button == input_hid::MouseEvent::left)
    {
      if (m_flags.IsMarked(k_alt_pressed))
      { m_flags.Mark(k_rotating); }
      else
      { m_flags.Unmark(k_rotating); }
    }

    if (a_button == input_hid::MouseEvent::middle)
    {
      if (m_flags.IsMarked(k_alt_pressed))
      { m_flags.Mark(k_panning); }
      else
      { m_flags.Unmark(k_panning); }
    }

    if (a_button == input_hid::MouseEvent::right)
    {
      if (m_flags.IsMarked(k_alt_pressed))
      { m_flags.Mark(k_dolly); }
      else
      { m_flags.Unmark(k_dolly); }
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnButtonRelease(const tl_size, const input_hid::MouseEvent&, 
                    const input_hid::MouseEvent::button_code_type a_button)
  {
    if (a_button == input_hid::MouseEvent::left)
    {
      m_flags.Unmark(k_rotating);
    }

    if (a_button == input_hid::MouseEvent::middle)
    {
      m_flags.Unmark(k_panning);
    }

    if (a_button == input_hid::MouseEvent::right)
    {
      m_flags.Unmark(k_dolly);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnMouseMove(const tl_size, const input_hid::MouseEvent& a_event)
  {
    m_xRel = core_utils::CastNumber<f32>(a_event.m_X.m_rel());
    m_yRel = core_utils::CastNumber<f32>(a_event.m_Y.m_rel());

    if (m_flags.IsMarked(k_rotating))
    {
      m_flags.Mark(k_updated);
      return core_dispatch::f_event::Veto();
    }
    else if (m_flags.IsMarked(k_panning))
    {
      m_flags.Mark(k_updated);
      return core_dispatch::f_event::Veto();
    }
    else if (m_flags.IsMarked(k_dolly))
    {
      m_flags.Mark(k_updated);
      return core_dispatch::f_event::Veto();
    }

    m_flags.Unmark(k_updated);
    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnKeyPress(const tl_size, const input_hid::KeyboardEvent& a_event)
  {
    if (a_event.m_keyCode == input_hid::KeyboardEvent::left_alt)
    {
      m_flags.Mark(k_alt_pressed);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnKeyRelease(const tl_size, const input_hid::KeyboardEvent& a_event)
  {
    if (a_event.m_keyCode == input_hid::KeyboardEvent::left_alt)
    {
      m_flags.Unmark(k_alt_pressed);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnTouchPress(const tl_size, const TouchSurfaceEvent& a_event)
  {
    if (m_currentTouch == 0)
    {
      m_currentTouch = a_event.m_touchHandle;
      m_flags.Mark(k_rotating);
      m_xPos = a_event.m_X.m_abs();
      m_yPos = a_event.m_Y.m_abs();
    }

    return core::dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnTouchRelease(const tl_size, const TouchSurfaceEvent& a_event)
  {
    if (a_event.m_touchHandle == m_currentTouch)
    {
      m_flags.Unmark(k_rotating);
      m_currentTouch = 0;
    }

    return core::dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControlSystem::event_type
    ArcBallControlSystem::
    OnTouchMove(const tl_size, const TouchSurfaceEvent& a_event)
  {
    if (a_event.m_touchHandle == m_currentTouch)
    {
      m_xRel = a_event.m_X.m_abs() - m_xPos;
      m_yRel = a_event.m_Y.m_abs() - m_yPos;
      m_xPos = a_event.m_X.m_abs();
      m_yPos = a_event.m_Y.m_abs();
      
      m_flags.Mark(k_updated);
    }
    return core::dispatch::f_event::Continue();
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::input_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ArcBallControlSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(ArcBallControlSystem);