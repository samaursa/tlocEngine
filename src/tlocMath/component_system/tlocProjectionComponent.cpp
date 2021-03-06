#include "tlocProjectionComponent.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace math { namespace component_system {

  namespace
  {
    typedef math_proj::frustum_persp_f32      frustum_type;
    typedef frustum_type::param_type          frustum_param_type;

    frustum_type GetDefaultFrustum()
    {
      using math_t::degree_f32;

      typedef frustum_type::fov_type  fov_type;
      typedef fov_type::ar_type       ar_type;

      ar_type   ar(ar_type::width(800), ar_type::height(600));
      fov_type  fov(degree_f32(70.0f), ar, types::p_FOV::vertical());

      frustum_param_type params(fov);
      params.SetNear(1.0f);
      params.SetFar(100.0f);

      frustum_type fr(params);
      fr.BuildFrustum();

      return fr;
    }
  };

  Projection::Projection()
    : base_type("Projection")
    , m_frustum(GetDefaultFrustum())
  { }

  Projection::Projection(const frustum_type& a_frustum)
    : base_type("Projection")
    , m_frustum(a_frustum)
  { }

};};};

//------------------------------------------------------------------------
// Explicit Instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::math_cs::Projection);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(tloc::math_cs::Projection);