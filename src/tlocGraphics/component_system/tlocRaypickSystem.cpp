#include "tlocRaypickSystem.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocGraphics/component_system/tlocRaypick.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/component_system/tlocBoundingBox.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>
#include <tlocMath/tlocRange.h>
#include <tlocMath/utilities/tlocScale.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  using     namespace math_t;
  using     math_utils::scale_f32_f32;
  typedef   math_utils::scale_f32_f32::range_small          range_small;
  typedef   math_utils::scale_f32_f32::range_large          range_large;

  namespace {

    TLOC_DECL_ALGO_WITH_CTOR_UNARY(RaypickEventByEntity_T, core_cs::entity_vptr, );
    TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(RaypickEventByEntity_T, )
    { return extract()(a).m_ent == m_value; }

    typedef RaypickEventByEntity_T<core::use_reference>   RaypickEventByEntity;
    typedef RaypickEventByEntity_T<core::use_pointee>     RaypickEventPointerByEntity;

  };
  
  // ///////////////////////////////////////////////////////////////////////
  // RaypickEvent

  RaypickEvent::
    RaypickEvent()
    : m_distanceChecked(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RaypickEvent::
    operator==(const this_type& a_other) const
  { 
    return m_ent == a_other.m_ent && 
           m_cameraEnt == a_other.m_cameraEnt && 
           m_camToEntVec == a_other.m_camToEntVec &&
           m_distanceChecked == a_other.m_distanceChecked;
  }

  // ///////////////////////////////////////////////////////////////////////
  // RaypickSystem

  RaypickSystem::
    RaypickSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entMgr)
    : base_type(a_eventMgr, a_entMgr, 
                register_type().Add<Raypick>(),
                "RaypickSystem")
    , m_windowDim(core_ds::MakeTuple(1000.0f, 1000.0f))
    , m_pickingMode(p_raypick_system::k_on_click)
    , m_pickingButton(input_hid::MouseEvent::k_left)
    , m_currentTouch(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    InitializeEntity(entity_ptr a_ent) -> error_type
  { 
    auto bb2d = a_ent->GetComponentIfExists<BoundingBox2D>();
    auto bb3d = a_ent->GetComponentIfExists<BoundingBox3D>();

    auto r = a_ent->GetComponentIfExists<Raypick>();

    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(bb2d == nullptr && bb3d == nullptr)
      << "Entity " << *a_ent << " does not have a BoundingBox component. "
      << "Raypicking will not work.";

    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(bb2d && bb3d)
      << "Entity " << *a_ent << " has both BoundingBox2D and BoundingBox3D. "
      << "Raypicking may not work as expected.";

    return ErrorSuccess;

  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RaypickSystem::
    Pre_ProcessActiveEntities(f64)
  { 
    m_camViewMat = matrix_type::IDENTITY;
    m_camViewMatInv = matrix_type::IDENTITY;
    m_camTransMat = matrix_type::IDENTITY;

    if (m_sharedCamera)
    { 
      m_camViewMat = 
        m_sharedCamera->GetComponent<gfx_cs::Camera>()->GetViewMatrix();
      m_camViewMatInv = m_camViewMat.Invert();

      m_camTransMat = 
        m_sharedCamera->GetComponent<math_cs::Transform>()->GetTransformation();
    }

    for (auto itr = m_mouseMovements.begin(), itrEnd = m_mouseMovements.end(); 
         itr != itrEnd; ++itr)
    {
      range_small   smallR = math::RangeNeg1to1<f32, math::p_range::Inclusive>();
      range_large   largeRX(0.0f, (f32)m_windowDim[0]);
      range_large   largeRY(0.0f, (f32)m_windowDim[1]);
      scale_f32_f32 scx(smallR, largeRX);
      scale_f32_f32 scy(smallR, largeRY);

      Vec3f32 xyz(scx.ScaleDown((*itr)[0]), 
                  scy.ScaleDown((f32)m_windowDim[1] - (*itr)[1] - 1.0f), -1.0f );

      ray_type ray  = math_t::Ray3f32(Ray3f32::origin(xyz), 
                                      Ray3f32::direction(Vec3f32(0.0f, 0.0f, -1.0f)));

      if (m_sharedCamera)
      {
        ray = m_sharedCamera->GetComponent<gfx_cs::Camera>()
          ->GetFrustumRef().GetRay(xyz);
      }

      // the ray is now in world space
      ray = ray * m_camViewMatInv;

      m_rays.push_back(ray);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    RaypickSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    if (m_mouseMovements.size() == 0) { return; }

    auto t = a_ent->GetComponentIfExists<math_cs::Transform>();
    auto r = a_ent->GetComponentIfExists<gfx_cs::Raypick>();

    auto objTransMat = matrix_type::IDENTITY;
    auto objTransMatInv = matrix_type::IDENTITY;

    if (t)
    { 
      objTransMat = t->GetTransformation();
      objTransMatInv = t->Invert().GetTransformation(); 
    }

    const auto camToEntVec = objTransMat.GetCol(3).ConvertTo<Vec3f32>() - 
                             m_camTransMat.GetCol(3).ConvertTo<Vec3f32>();

    RaypickEvent evt;

    // if this entity has already been picked before, then we may be unpicking it
    auto itrEvent = core::find_if_all(m_alreadyRaypicked, RaypickEventByEntity(a_ent));
    if (itrEvent == m_alreadyRaypicked.end())
    {
      evt.m_ent = a_ent;
      evt.m_cameraEnt = m_sharedCamera;
      evt.m_camToEntVec = camToEntVec;
      evt.m_distanceChecked = r->GetIsDistanceChecked();
    }
    else
    { evt = *itrEvent; }

    // We check whether the last selection is still closer to the camera. This
    // does not take into account frustum culling
    if (m_closestToCamera.m_cameraEnt)
    {
      if (r->GetIsDistanceChecked() && camToEntVec.LengthSquared() > 
          m_closestToCamera.m_camToEntVec.LengthSquared())
      { return; }
    }

    auto bb2d = a_ent->GetComponentIfExists<gfx_cs::BoundingBox2D>();
    auto bb3d = a_ent->GetComponentIfExists<gfx_cs::BoundingBox3D>();

    if (bb2d == nullptr && bb3d == nullptr)
    { return; }

    for (auto itr = m_rays.begin(), itrEnd = m_rays.end(); 
         itr != itrEnd; ++itr)
    {
      evt.m_rayInWorldSpace = *itr;
      const auto ray = evt.m_rayInWorldSpace * objTransMatInv;

      if (bb2d)
      {
        if (bb2d->GetIsCircular())
        {
          const auto& bounds = bb2d->GetCircularBounds();
          if (bounds.Intersects(ray))
          { 
            if (r->GetIsDistanceChecked())
            { m_closestToCamera = evt; }
            else
            { 
              if (itrEvent == m_alreadyRaypicked.end())
              { 
                m_raypickEvents.push_back(evt);
                itrEvent = m_raypickEvents.end() - 1;
              }
            }
          }
          else
          {
            if (itrEvent != m_alreadyRaypicked.end())
            { 
              if (core::find_if_all(m_unraypickEvents, RaypickEventByEntity(a_ent))
                  == m_unraypickEvents.end())
              { m_unraypickEvents.push_back(evt); }
            }
          }
        }
        else
        {
          const auto& bounds = bb2d->GetBounds();
          if (bounds.Intersects(ray).first)
          { 
            if (r->GetIsDistanceChecked())
            { m_closestToCamera = evt; }
            else
            { 
              if (itrEvent == m_alreadyRaypicked.end())
              { 
                m_raypickEvents.push_back(evt); 
                itrEvent = m_raypickEvents.end() - 1;
              }
            }
          }
          else
          {
            if (itrEvent != m_alreadyRaypicked.end())
            { 
              if (core::find_if_all(m_unraypickEvents, RaypickEventByEntity(a_ent))
                  == m_unraypickEvents.end())
              { m_unraypickEvents.push_back(evt); }
            }
          }
        }
      }
      else
      {
        const auto& bounds = bb3d->GetBounds();
        if (bounds.Intersects(ray))
        { 
          if (r->GetIsDistanceChecked())
          { m_closestToCamera = evt; }
          else
          { 
            if (itrEvent == m_alreadyRaypicked.end())
            { 
              m_raypickEvents.push_back(evt);
              itrEvent = m_raypickEvents.end() - 1;
            }
          }
        }
        else
        {
          if (itrEvent != m_alreadyRaypicked.end())
          { 
            if (core::find_if_all(m_unraypickEvents, RaypickEventByEntity(a_ent)) 
                == m_unraypickEvents.end() )
            { m_unraypickEvents.push_back(evt); }
          }
        }
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RaypickSystem::
    Post_ProcessActiveEntities(f64)
  {
    m_mouseMovements.clear();
    m_rays.clear();

    if (m_closestToCamera.m_ent)
    { 
      auto itrEvent = core::find_if_all
        (m_alreadyRaypicked, RaypickEventByEntity(m_closestToCamera.m_ent));

      if (itrEvent == m_alreadyRaypicked.end())
      { m_raypickEvents.push_back(m_closestToCamera); }
    }
    m_closestToCamera = RaypickEvent();

    // send all pick events
    for (u32 i = 0; i < m_allObservers.size(); ++i)
    {
      for (auto itr = m_raypickEvents.begin(), itrEnd = m_raypickEvents.end();
           itr != itrEnd; ++itr)
      { m_allObservers[i]->OnRaypickEvent(*itr); }
    }

    // transfer all the recent events to m_alreadyRaypicked
    for (auto itr = m_raypickEvents.begin(), itrEnd = m_raypickEvents.end();
         itr != itrEnd; ++itr)
    { m_alreadyRaypicked.push_back(*itr); }
    m_raypickEvents.clear();

    // send all unpick events
    for (u32 i = 0; i < m_allObservers.size(); ++i)
    {
      for (auto itr = m_unraypickEvents.begin(), itrEnd = m_unraypickEvents.end();
           itr != itrEnd; ++itr)
      { m_allObservers[i]->OnRayUnpickEvent(*itr); }
    }

    for (auto itr = m_unraypickEvents.begin(), itrEnd = m_unraypickEvents.end();
         itr != itrEnd; ++itr)
    {
      auto itrEvent = core::find_if_all
        (m_alreadyRaypicked, RaypickEventByEntity(itr->m_ent));

      if (itrEvent != m_alreadyRaypicked.end())
      { m_alreadyRaypicked.erase(itrEvent); }
    }

    m_unraypickEvents.clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    SetCamera(entity_ptr a_camera) -> this_type&
  {
    if (a_camera->HasComponent<gfx_cs::Camera>())
    { m_sharedCamera = a_camera; }
    else
    { 
      TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Entity " << *a_camera 
        << " does not have a Camera component";
      m_sharedCamera = nullptr;
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    SetPickingMode(picking_mode a_mode, button_code a_button) -> this_type&
  {
    m_pickingMode = a_mode;
    m_pickingButton = a_button;

    TLOC_LOG_GFX_DEBUG_FILENAME_ONLY_IF(a_button == input_hid::MouseEvent::none)
      << "Raypicking disabled (button_code = none).";

    if (m_pickingButton < input_hid::MouseEvent::none ||
        m_pickingButton >= input_hid::MouseEvent::k_count)
    {
      TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Invalid button for raypicking.";
      m_pickingButton = input_hid::MouseEvent::none;
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnMouseButtonPress(const tl_size, 
                       const input_hid::MouseEvent& a_event, 
                       const input_hid::MouseEvent::button_code_type a_button) 
                       -> event_type
  {
    if (a_button == m_pickingButton)
    {
      auto autopos =  vec2_type((f32)a_event.m_X.m_abs, (f32)a_event.m_Y.m_abs);
      m_mouseMovements.push_back(autopos);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnMouseButtonRelease(const tl_size, 
                         const input_hid::MouseEvent& a_event, 
                         const input_hid::MouseEvent::button_code_type a_button) 
                        -> event_type
  {
    if (m_pickingMode != p_raypick_system::k_on_click && 
        a_button == m_pickingButton)
    {
      auto autopos =  vec2_type((f32)a_event.m_X.m_abs, (f32)a_event.m_Y.m_abs);
      m_mouseMovements.push_back(autopos);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnMouseMove(const tl_size, const input_hid::MouseEvent& a_event) -> event_type
  {
    if (m_pickingMode == p_raypick_system::k_on_click)
    { return core_dispatch::f_event::Continue(); }

    if (m_pickingMode == p_raypick_system::k_continuous_on_click)
    {
      if ( (a_event.m_buttonCode & m_pickingButton) == false)
      { return core_dispatch::f_event::Continue(); }
    }

    auto autopos = vec2_type((f32) a_event.m_X.m_abs, (f32) a_event.m_Y.m_abs);
    m_mouseMovements.push_back(autopos);
    
    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnTouchPress(const tl_size,
                 const input::TouchSurfaceEvent& a_event)
                 -> event_type
  {
    if (m_currentTouch == 0)
    {
      m_currentTouch = a_event.m_touchHandle;
      auto autopos =  vec2_type((f32)a_event.m_X.m_abs, (f32)a_event.m_Y.m_abs);
      m_mouseMovements.push_back(autopos);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnTouchRelease(const tl_size,
                   const input::TouchSurfaceEvent& a_event)
                   -> event_type
  {
    if (a_event.m_touchHandle != m_currentTouch)
    { return core_dispatch::f_event::Continue(); }

    m_currentTouch = 0;

    if (m_pickingMode != p_raypick_system::k_on_click)
    {
      auto autopos =  vec2_type((f32)a_event.m_X.m_abs, (f32)a_event.m_Y.m_abs);
      m_mouseMovements.push_back(autopos);
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnTouchMove(const tl_size, const input::TouchSurfaceEvent& a_event) -> event_type
  {
    if (a_event.m_touchHandle == m_currentTouch &&
        m_pickingMode != p_raypick_system::k_on_click)
    {
      auto autopos = vec2_type((f32) a_event.m_X.m_abs, (f32) a_event.m_Y.m_abs);
      m_mouseMovements.push_back(autopos);
    }
    
    return core_dispatch::f_event::Continue();
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(RaypickSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(RaypickSystem);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(RaypickEvent);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(RaypickSystem::ray_type);