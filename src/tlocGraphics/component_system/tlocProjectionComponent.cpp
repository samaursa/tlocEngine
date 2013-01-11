#include "tlocProjectionComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocGraphics/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace
  {
    typedef Projection::frustum_type          frustum_type;
    typedef Projection::frustum_param_type    frustum_param_type;

    frustum_param_type GetDefaultFrustumParams()
    {
      using math::types::Degree;

      typedef frustum_type::fov_type  fov_type;
      typedef fov_type::ar_type       ar_type;

      ar_type   ar(ar_type::width(800), ar_type::height(600));
      fov_type  fov(Degree(70.0f), ar, types::p_FOV::vertical());

      frustum_param_type params(fov);
      params.SetNear(1.0f);
      params.SetFar(100.0f);

      return params;
    }
  };

  Projection::Projection()
    : base_type(components::projection)
    , m_frustum(GetDefaultFrustumParams())
  {
    m_frustum.BuildFrustum();
  }

  Projection::Projection(const frustum_type& a_frustum)
    : base_type(components::projection)
    , m_frustum(a_frustum)
  { }

  void Projection::SetFrustum(const frustum_param_type& a_params)
  {
    m_frustum = frustum_type(a_params);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  // SmartPtr
  template core::smart_ptr::SharedPtr<Projection>;

  // Pool
  template core::component_system::ComponentPool_TI<ProjectionPtr>;

};};};