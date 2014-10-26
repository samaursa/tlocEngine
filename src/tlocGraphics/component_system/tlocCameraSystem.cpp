#include "tlocCameraSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocGraphics/component_system/tlocCamera.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  using namespace core::data_structs;

  // ///////////////////////////////////////////////////////////////////////
  // CameraSystem

  CameraSystem::
    CameraSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::camera))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    CameraSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    typedef Camera::matrix_type           matrix_type;
    typedef math_cs::transform_f32_sptr   trans_type;

    camera_sptr cam = a_ent->GetComponent<Camera>();
    trans_type camTrans = a_ent->GetComponent<trans_type::value_type>();

    matrix_type viewMat;
    matrix_type m_vpMatrix;
    viewMat.MakeIdentity();
    m_vpMatrix.MakeIdentity();

    // LookAt target
    if (cam->DoIsTargetUpdated())
    {
      const Camera::point_type camPos = camTrans->GetPosition();

      const Camera::point_type newTarget = 
        (cam->DoGetTarget() - camPos).Inverse() + camPos;

      camTrans->LookAt(newTarget);
    }

    // vMVP, but since we are doing column major, it becomes PVMv

    m_vpMatrix = cam->GetFrustumRef().GetProjectionMatrix();

    if (a_ent->HasComponent(transform))
    {
      math_cs::Transform vMatInv = camTrans->Invert();
      viewMat = vMatInv.GetTransformation().Cast<matrix_type>();
    }

    m_vpMatrix = m_vpMatrix * viewMat;

    cam->SetViewProj(m_vpMatrix);
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(CameraSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(CameraSystem);