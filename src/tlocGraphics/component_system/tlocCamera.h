#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_CAMERA_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_CAMERA_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  class Camera
    : public core_cs::Component_T<Camera, components::camera>
  {
  public:
    typedef Camera                                      this_type;
    typedef Component_T<this_type, components::camera>  base_type;
    typedef math_proj::frustum_f32                           frustum_type;
    typedef frustum_type::matrix_type                           view_proj_mat_type;

  public:
    Camera();
    explicit Camera(const frustum_type& a_frustum);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(frustum_type, GetFrustumRef, m_frustum);
    TLOC_DECL_AND_DEF_SETTER(frustum_type, SetFrustum, m_frustum);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (view_proj_mat_type, GetViewProjRef, m_vpMat);
    TLOC_DECL_AND_DEF_SETTER(view_proj_mat_type, SetViewProj, m_vpMat);

  private:
    frustum_type        m_frustum;
    view_proj_mat_type  m_vpMat;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(Camera, camera);
  TLOC_TYPEDEF_COMPONENT_POOL(camera_sptr, camera_sptr);

};};};


#endif