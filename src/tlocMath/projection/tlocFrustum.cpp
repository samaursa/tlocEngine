#include "tlocFrustum.h"
#include <tlocCore/data_structures/tlocTuple.inl>

#include <tlocMath/tloc_math.h>
#include <tlocMath/tloc_math.inl>

namespace tloc { namespace math { namespace proj {

  //------------------------------------------------------------------------
  // Params

  Frustum::Params::Params(const fov_type& a_fov)
    : m_fov(a_fov)
  {
    m_aspectRatio = m_fov.GetAspectRatio();
  }

  Frustum::Params::Params(const Params& a_other)
    : m_near(a_other.m_near)
    , m_far (a_other.m_far)
    , m_aspectRatio(a_other.m_aspectRatio)
    , m_fov(a_other.m_fov)
  { }

  Frustum::Params& Frustum::Params::SetNear(real_type a_near)
  {
    m_near = a_near;
    return *this;
  }

  Frustum::Params& Frustum::Params::SetFar(real_type a_far)
  {
    m_far = a_far;
    return *this;
  }

  //------------------------------------------------------------------------
  // Frustum

  Frustum::Frustum(const rect_type& a_rect, real_type a_near, real_type a_far)
    : m_params(types::FOV(math::types::Degree(90.0f),
                          ar_type(),
                          types::p_FOV::horizontal()) )
    , m_projMatrix(0)
  {
    using namespace types;
    using namespace math::utils;

    real_type top		 = a_rect.GetValue<rect_type::top>();
    real_type bottom = a_rect.GetValue<rect_type::bottom>();
    real_type left	 = a_rect.GetValue<rect_type::left>();
    real_type right	 = a_rect.GetValue<rect_type::right>();

    DoDefinePlanes
      (plane_args(a_near, a_far, top, bottom, left, right));

    ar_type::width width(Math<real_type>::Abs(right - left));
    ar_type::height height(Math<real_type>::Abs(top - bottom));

    Pythagoras pythHalfAngle =
      Pythagoras( Pythagoras::base(a_near), Pythagoras::opposite(right) );
    ar_type    ar(width, height);

    m_params = Params(FOV(pythHalfAngle, ar, p_FOV::horizontal() ));
    m_params.SetNear(a_near).SetFar(a_far);
  }

  Frustum::Frustum(const Params& a_params)
    : m_params(a_params)
    , m_projMatrix(0)

  {
    using namespace math::utils;
    using math::types::Degree;

    Degree halfFOV
      (m_params.GetFOV().Get<types::p_FOV::vertical>().GetAs<Degree>() / 2);

    Pythagoras pyth =
      Pythagoras(halfFOV, Pythagoras::base(m_params.GetNear()));

    real_type top = pyth.GetSide<Pythagoras::opposite>();
    real_type right = m_params.GetAspectRatio().Get() * top;
    DoDefinePlanes
      (plane_args(m_params.GetNear(), m_params.GetFar(),
                  top, -top, -right, right) );
  }

  Frustum::~Frustum()
  { }

  void Frustum::BuildFrustum()
  {
    DoBuildFrustumFromPlanes();
  }

  Frustum::ray_type
    Frustum::
    GetRay(const types::Vector3<real_type>& a_xyzNDC) const
  {
    TLOC_ASSERT(a_xyzNDC[0] >= -1.0f && a_xyzNDC[0] <= 1.0f &&
                a_xyzNDC[1] >= -1.0f && a_xyzNDC[1] <= 1.0f &&
                a_xyzNDC[2] >= -1.0f && a_xyzNDC[2] <= 1.0f,
                "Vector not in Normalized Device Co-ordinates");

    real_type pFar  = m_params.GetFar();
    real_type pNear = m_params.GetNear();

    using math_t::Vector3;
    /* For details, see Saad's Master's thesis Appendix H */

    // We need to go from NDC -> Clip -> Eye
    // Note that w_clip (perspective divide) is -z_eye. How? When we multiply
    // the xyz_eye vector with M_proj, we get xyzw_clip, where w = -z_eye due
    // to the M_proj lower low being 0, 0, -1 (the z_eye), 0

    // We need z_eye
    const real_type z_eye
      = - (2 * pFar * pNear) /
          ( (a_xyzNDC[2] * (pNear * pFar) + (pFar + pNear)) );

    // x_eye = -z_eye/P_00(x_NDC + P_20)
    real_type x_eye = (-z_eye / m_projMatrix.Get(0, 0)) *
                      (a_xyzNDC[0] + m_projMatrix.Get(2, 0));

    // y_eye = -z_eye/P_11(x_NDC + P_21)
    real_type y_eye = (-z_eye / m_projMatrix.Get(1, 1)) *
                      (a_xyzNDC[1] + m_projMatrix.Get(2, 1));

    Vector3<real_type> rayOrigin(x_eye, y_eye, z_eye);
    Vector3<real_type> rayDir(0, 0, -1);

    return ray_type(ray_type::origin(rayOrigin),
                    ray_type::direction(rayDir));
  }

  //------------------------------------------------------------------------
  // Helper functions

  void Frustum::DoDefinePlanes(const plane_args& a_vars)
  {
    m_planes = a_vars;
  }

  void Frustum::DoBuildFrustumFromPlanes()
  {
    typedef Planes  p;

    real_type RminLReci = 1 / (m_planes[p::k_right] -
                               m_planes[p::k_left]);
    real_type TminBReci = 1 / (m_planes[p::k_top] -
                               m_planes[p::k_bottom]);
    real_type FminNReci = 1 / (m_planes[p::k_far] -
                               m_planes[p::k_near]);

    m_projMatrix(0, 0) = 2 * m_planes[p::k_near] * RminLReci;
    m_projMatrix(1, 1) = 2 * m_planes[p::k_near] * TminBReci;
    m_projMatrix(0, 2) = (m_planes[p::k_right] +
                          m_planes[p::k_left]) * RminLReci;
    m_projMatrix(1, 2) = (m_planes[p::k_top] +
                          m_planes[p::k_bottom]) * TminBReci;
    m_projMatrix(2, 2) = (-(m_planes[Planes::k_far] +
                            m_planes[p::k_near])) * FminNReci;
    m_projMatrix(3, 2) = -1;
    m_projMatrix(2, 3) = -2 * m_planes[Planes::k_far] *
                              m_planes[Planes::k_near] * FminNReci;
  }

  //------------------------------------------------------------------------
  // Instantiate tuple for the number of planes we have

  using core::data_structs::Tuple;

  template class Tuple<Frustum::real_type, Frustum::Planes::k_count>;

};};};