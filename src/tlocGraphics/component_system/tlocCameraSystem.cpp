#include "tlocCameraSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

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
    CameraSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::camera))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    CameraSystem::
    ProcessEntity(const entity_manager* ,
                  const entity_type* a_ent, f64 )
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    typedef Camera::matrix_type         matrix_type;

    Camera* cam = a_ent->GetComponent<Camera>();

    matrix_type viewMat;
    matrix_type m_vpMatrix;
    viewMat.MakeIdentity();
    m_vpMatrix.MakeIdentity();

    // vMVP, but since we are doing column major, it becomes PVMv

    m_vpMatrix = a_ent->GetComponent
      <gfx_cs::Camera>()->GetFrustumRef().GetProjectionMatrix();

    if (a_ent->HasComponent(transform))
    {
      math_cs::Transform* vMat = a_ent->GetComponent<math_cs::Transform>();
      math_cs::Transform vMatInv = vMat->Invert();
      viewMat = vMatInv.GetTransformation().Cast<matrix_type>();
    }

    m_vpMatrix = m_vpMatrix * viewMat;

    cam->SetViewProj(m_vpMatrix);
  }

};};};