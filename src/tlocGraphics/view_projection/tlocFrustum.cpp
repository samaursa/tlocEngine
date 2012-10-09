#include "tlocFrustum.h"
#include <tlocCore/data_structures/tlocTuple.inl>

namespace tloc { namespace graphics { namespace view_projection {

  //------------------------------------------------------------------------
  // Params

  Frustum::Params::Params(const fov_type& a_fov)
    : m_fov(a_fov)
  {
    m_aspectRatio = m_fov.GetAspectRatio();
  }

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
    : m_projMatrix(0),
    m_params(types::FOV(math::Degree(90.0f), ar_type(), types::p_FOV::horizontal() ))
  {
    using namespace types;
    using namespace math::utils;

    real_type top		 = a_rect.GetCoord<rect_type::top>();
    real_type bottom = a_rect.GetCoord<rect_type::bottom>();
    real_type left	 = a_rect.GetCoord<rect_type::left>();
    real_type right	 = a_rect.GetCoord<rect_type::right>();

    DoDefinePlanes
      (plane_args(a_near, a_far, top, bottom, left, right));

    ar_type::width width(Math<real_type>::Abs(right - left));
    ar_type::height height(Math<real_type>::Abs(top - bottom));

    Pythagoras pythHalfAngle(Pythagoras::base(a_near),
                             Pythagoras::opposite(right));
    ar_type    ar(width, height);

    m_params = Params(FOV(pythHalfAngle, ar, p_FOV::horizontal() ));
    m_params.SetNear(a_near).SetFar(a_far);
  }

  Frustum::Frustum(const Params& a_params)
    : m_params(a_params)
  {
    real_type top = m_params.GetNear();
    real_type right = m_params.GetAspectRatio().Get() * top;
    DoDefinePlanes
      (plane_args(m_params.GetNear(), m_params.GetFar(),
                  top, -top, right, -right) );
  }

  Frustum::~Frustum()
  { }

  void Frustum::BuildFrustum()
  {
    DoBuildFrustumFromPlanes();
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

  template class core::Tuple<Frustum::real_type, Frustum::Planes::k_count>;

};};};