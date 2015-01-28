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
  
  // ///////////////////////////////////////////////////////////////////////
  // RaypickEvent

  RaypickEvent::
    RaypickEvent()
    : m_noDistanceCheck(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RaypickEvent::
    operator==(const this_type& a_other) const
  { 
    return m_pickedEnt == a_other.m_pickedEnt && 
           m_cameraEnt == a_other.m_cameraEnt && 
           m_camToEntVec == a_other.m_camToEntVec &&
           m_mouseCoords == a_other.m_mouseCoords && 
           m_noDistanceCheck == a_other.m_noDistanceCheck;
  }

  // ///////////////////////////////////////////////////////////////////////
  // RaypickSystem

  RaypickSystem::
    RaypickSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entMgr)
    : base_type(a_eventMgr, a_entMgr, 
                register_type().Add<Raypick>(),
                "RaypickSystem")
    , m_windowDim(core_ds::MakeTuple(1000.0f, 1000.0f))
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
    m_currentPick = nullptr;
    m_rays.clear();

    m_camTransMat = matrix_type::IDENTITY;

    auto const camTransMatInv = m_camTransMat.Invert();

    if (m_sharedCamera)
    { 
      m_camTransMat = 
        m_sharedCamera->GetComponent<math_cs::Transform>()->GetTransformation();
    }

    for (auto itr = m_mouseMovements.begin(), itrEnd = m_mouseMovements.end(); 
         itr != itrEnd; ++itr)
    {
      range_small   smallR(-1.0f, 1.1f);
      range_large   largeRX(0.0f, (f32)m_windowDim[0]);
      range_large   largeRY(0.0f, (f32)m_windowDim[1]);
      scale_f32_f32 scx(smallR, largeRX);
      scale_f32_f32 scy(smallR, largeRY);

      Vec3f32 xyz(scx.ScaleDown((*itr)[0]), 
                  scy.ScaleDown((f32)m_windowDim[1] - (*itr)[1] - 1.0f), 0.0f );

      ray_type ray  = math_t::Ray3f32(Ray3f32::origin(xyz), 
                                      Ray3f32::direction(Vec3f32(0.0f, 0.0f, -1.0f)));

      if (m_sharedCamera)
      {
        ray = m_sharedCamera->GetComponent<gfx_cs::Camera>()
          ->GetFrustumRef().GetRay(xyz);
      }

      // the ray is now in world space
      ray = ray * camTransMatInv;

      m_rays.push_back(ray);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    RaypickSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    auto r = a_ent->GetComponentIfExists<gfx_cs::Raypick>();

    auto t = a_ent->GetComponentIfExists<math_cs::Transform>();
    auto bb2d = a_ent->GetComponentIfExists<gfx_cs::BoundingBox2D>();
    auto bb3d = a_ent->GetComponentIfExists<gfx_cs::BoundingBox3D>();

    if (bb2d == nullptr && bb3d == nullptr)
    { return; }

    auto objTransMat = matrix_type::IDENTITY;

    if (t)
    { objTransMat = t->GetTransformation(); }

    const auto objTransMatInv = objTransMat.Invert();

    RaypickEvent event;
    event.m_pickedEnt = a_ent;
    event.m_cameraEnt = m_sharedCamera;
    event.m_camToEntVec = m_camTransMat.GetCol(3).ConvertTo<Vec3f32>() - 
                          objTransMat.GetCol(3).ConvertTo<Vec3f32>();

    for (auto itr = m_rays.begin(), itrEnd = m_rays.end(); 
         itr != itrEnd; ++itr)
    {
      const auto ray = (*itr) * objTransMatInv;

      if (bb2d)
      {
        auto rayPos2f = ray.GetOrigin().ConvertTo<Vec2f32>();
        auto rayDir2f = ray.GetDirection().ConvertTo<Vec2f32>();

        auto ray2 = Ray2f32(Ray2f32::origin(rayPos2f), 
                            Ray2f32::direction(rayDir2f));

        if (bb2d->GetIsCircular())
        {
          const auto& bounds = bb2d->GetCircularBounds();
          if (bounds.Intersects(ray2))
          { m_raypickEvents.push_back(event); }
        }
        else
        {
          const auto& bounds = bb2d->GetBounds();
          if (bounds.Intersects(ray2))
          { m_raypickEvents.push_back(event); }
        }
      }
      else
      {
        const auto& bounds = bb3d->GetBounds();
        if (bounds.Intersects(ray))
        { m_raypickEvents.push_back(event); }
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RaypickSystem::
    Post_ProcessActiveEntities(f64)
  {
    m_mouseMovements.clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    RaypickSystem::
    SetCamera(entity_ptr a_camera)
  {
    if (a_camera->HasComponent<gfx_cs::Camera>())
    { m_sharedCamera = a_camera; }
    else
    { 
      TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Entity " << *a_camera 
        << " does not have a Camera component";
      m_sharedCamera = nullptr;
    }

  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    RaypickSystem::
    OnMouseMove(const tl_size, const input_hid::MouseEvent& a_event) -> event_type
  {
    auto autopos =  vec2_type((f32)a_event.m_X.m_abs, 
                              (f32)a_event.m_Y.m_abs);
    m_mouseMovements.push_back(autopos);
    
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