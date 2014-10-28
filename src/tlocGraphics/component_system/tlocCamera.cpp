#include "tlocCamera.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

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
      fov_type  fov(degree_f32(70.0f), ar, math_t::p_FOV::vertical());

      frustum_param_type params(fov);
      params.SetNear(1.0f);
      params.SetFar(100.0f);

      frustum_type fr(params);
      fr.BuildFrustum();

      return fr;
    }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Camera::
    Camera()
    : base_type("Camera")
    , m_frustum(GetDefaultFrustum())
    , m_vpMat(matrix_type::IDENTITY)
    , m_viewMat(matrix_type::IDENTITY)
    , m_projMat(matrix_type::IDENTITY)
  { 
    m_target.first = false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Camera::
    Camera(const frustum_type& a_frustum)
    : base_type("Camera")
    , m_frustum(a_frustum)
    , m_vpMat(matrix_type::IDENTITY)
    , m_viewMat(matrix_type::IDENTITY)
    , m_projMat(matrix_type::IDENTITY)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Camera::
    LookAt(point_type a_target)
  {
    m_target.first = true;
    m_target.second = a_target;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Camera::
    DoIsTargetUpdated()
  {
    bool flag = m_target.first;
    m_target.first = false;
    return flag;
  }

};};};

// -----------------------------------------------------------------------
// Explicit Instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Camera);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Camera);