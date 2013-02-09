#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_PROJECTION_COMPONENT_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_PROJECTION_COMPONENT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/view_projection/tlocFrustum.h>

namespace tloc { namespace graphics { namespace component_system {

  class Projection : public core::component_system::Component_T<Projection>
  {
  public:
    typedef core::component_system::Component_T<Projection>     base_type;

    typedef view_proj::Frustum            frustum_type;
    typedef view_proj::Frustum::Params    frustum_param_type;

  public:
    Projection();
    explicit Projection(const frustum_type& a_frustum);

    void SetFrustum(const frustum_param_type& a_params);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(frustum_type, GetFrustumRef, m_frustum);
    TLOC_DECL_AND_DEF_SETTER(frustum_type, SetFrustum, m_frustum);

  private:
    frustum_type  m_frustum;
  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef core::smart_ptr::SharedPtr<Projection>    ProjectionPtr;
  typedef core::component_system::
          ComponentPool_TI<ProjectionPtr>           ProjectionPool;

};};};

#endif