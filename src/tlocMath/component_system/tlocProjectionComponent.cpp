#include "tlocProjectionComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace math { namespace component_system {

  namespace
  {
    typedef math_proj::frustum_persp          frustum_type;
    typedef frustum_type::param_type          frustum_param_type;

    frustum_type GetDefaultFrustum()
    {
      using math::types::Degree;

      typedef frustum_type::fov_type  fov_type;
      typedef fov_type::ar_type       ar_type;

      ar_type   ar(ar_type::width(800), ar_type::height(600));
      fov_type  fov(Degree(70.0f), ar, types::p_FOV::vertical());

      frustum_param_type params(fov);
      params.SetNear(1.0f);
      params.SetFar(100.0f);

      frustum_type fr(params);
      fr.BuildFrustum();

      return fr;
    }
  };

  Projection::Projection()
    : base_type(k_component_type)
    , m_frustum(GetDefaultFrustum())
  { }

  Projection::Projection(const frustum_type& a_frustum)
    : base_type(components::projection)
    , m_frustum(a_frustum)
  { }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  // SmartPtr
  template class core::smart_ptr::SharedPtr<Projection>;

  // Pool
  template class core::component_system::ComponentPool_TI<ProjectionPtr>;

};};};