#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_CAMERA_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_CAMERA_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/tlocPair.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  class CameraSystem;

  class Camera
    : public core_cs::Component_T<Camera, 
                                  core_cs::component_group::k_graphics,
                                  components::k_camera>
  {
  public:
    friend class CameraSystem;

    typedef Camera                                      this_type;
    typedef Component_T
      <this_type, k_component_group, k_component_type>  base_type;
    typedef math_proj::frustum_f32                      frustum_type;
    typedef frustum_type::matrix_type                   matrix_type;
    typedef math_t::Vec3f32                             point_type;
    typedef core::Pair<bool, point_type>                target_type;

  public:
    Camera();
    explicit Camera(const frustum_type& a_frustum);

    void LookAt(point_type a_target);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(frustum_type, GetFrustumRef, m_frustum);
    TLOC_DECL_AND_DEF_SETTER(frustum_type, SetFrustum, m_frustum);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (matrix_type, GetViewProjRef, m_vpMat);
    TLOC_DECL_AND_DEF_SETTER(matrix_type, SetViewProj, m_vpMat);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (matrix_type, GetViewMatrix, m_viewMat);
    TLOC_DECL_AND_DEF_SETTER(matrix_type, SetViewMatrix, m_viewMat);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (matrix_type, GetProjectionMatrix, m_projMat);
    TLOC_DECL_AND_DEF_SETTER(matrix_type, SetProjectionMatrix, m_projMat);

  private:
    TLOC_DECL_GETTER_NON_CONST(bool, DoIsTargetUpdated);
    TLOC_DECL_AND_DEF_GETTER(point_type, DoGetTarget, m_target.second);

  private:
    frustum_type      m_frustum;
    matrix_type       m_vpMat;
    matrix_type       m_viewMat;
    matrix_type       m_projMat;
    target_type       m_target;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Camera, camera);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Camera, camera);
  TLOC_TYPEDEF_COMPONENT_POOL(Camera, camera);

};};};


#endif