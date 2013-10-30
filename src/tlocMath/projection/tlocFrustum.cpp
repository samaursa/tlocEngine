#include "tlocFrustum.h"
#include <tlocCore/data_structures/tlocTuple.inl.h>

#include <tlocMath/tloc_math.h>
#include <tlocMath/tloc_math.inl.h>

namespace tloc { namespace math { namespace proj {

  //////////////////////////////////////////////////////////////////////////
  // FrustumBase

#define FRUSTUM_TEMPS   typename T_Real
#define FRUSTUM_PARAMS  T_Real
#define FRUSTUM_TYPE    typename Frustum_TI<FRUSTUM_PARAMS>

  template <FRUSTUM_TEMPS>
  Frustum_TI<FRUSTUM_PARAMS>::Frustum_TI()
    : m_projMatrix(1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1)
  { }

  template <FRUSTUM_TEMPS>
  Frustum_TI<FRUSTUM_PARAMS>::
    Frustum_TI(const this_type& a_other)
    : m_planes(a_other.m_planes)
    , m_projMatrix(a_other.m_projMatrix)
  { }

  template <FRUSTUM_TEMPS>
  Frustum_TI<FRUSTUM_PARAMS>::
    ~Frustum_TI()
  { }

  template <FRUSTUM_TEMPS>
  void Frustum_TI<FRUSTUM_PARAMS>::
    DoDefinePlanes(const plane_args& a_vars)
  {
    m_planes = a_vars;
  }

  template <FRUSTUM_TEMPS>
  FRUSTUM_TYPE::ray_type
    Frustum_TI<FRUSTUM_PARAMS>::
    GetRay(const types::Vector3<real_type>& a_xyzNDC) const
  {

    TLOC_ASSERT(a_xyzNDC[0] >= -1.0f && a_xyzNDC[0] <= 1.0f &&
                a_xyzNDC[1] >= -1.0f && a_xyzNDC[1] <= 1.0f &&
                a_xyzNDC[2] >= -1.0f && a_xyzNDC[2] <= 1.0f,
                "Vector not in Normalized Device Co-ordinates");

    const matrix_type& projMatrix = this->GetProjectionMatrix();

    using math_t::Vector3;

    const real_type z_eye
      = - (projMatrix.Get(2,3) / (a_xyzNDC[2] + projMatrix.Get(2, 2)) );

    // x_eye = -z_eye/P_00(x_NDC + P_20 + P30/z_eye)
    real_type x_eye
    = (-z_eye  / projMatrix.Get(0, 0)) *
       (a_xyzNDC[0] + projMatrix.Get(0, 2) + (projMatrix.Get(0, 3) / z_eye) );

    // y_eye = -z_eye/P_11(x_NDC + P_21 + P31/z_eye)
    real_type y_eye =
      (-z_eye / projMatrix.Get(1, 1)) *
       (a_xyzNDC[1] + projMatrix.Get(1, 2) + (projMatrix.Get(1, 3) / z_eye) );

    Vector3<real_type> rayOrigin(x_eye, y_eye, z_eye);
    Vector3<real_type> rayDir(rayOrigin);
    rayDir.Normalize();

    return ray_type(typename ray_type::origin(rayOrigin),
                    typename ray_type::direction(rayDir));
  }

  //------------------------------------------------------------------------
  // explicit instantiations

  template class Frustum_TI<f32>;
  template class Frustum_TI<f64>;

  //------------------------------------------------------------------------
  // Instantiate tuple for the number of planes we have

  using core::data_structs::Tuple;

  template class Tuple<Frustum_TI<f32>::real_type,
                       p_frustum::PlaneCount::k_planeIndex>;

  template class Tuple<Frustum_TI<f64>::real_type,
                       p_frustum::PlaneCount::k_planeIndex>;

  //////////////////////////////////////////////////////////////////////////
  // Frustum<Perspective>

#define FRUSTUM_PERSP_TEMPS  typename T_Real
#define FRUSTUM_PERSP_PARAMS T_Real, p_frustum::Perspective
#define FRUSTUM_PERSP_TYPE   typename Frustum_T<FRUSTUM_PERSP_PARAMS>

  //------------------------------------------------------------------------
  // Params

  template <FRUSTUM_PERSP_TEMPS>
  Frustum_T<FRUSTUM_PERSP_PARAMS>::Params::
    Params(const fov_type& a_fov)
    : m_fov(a_fov)
  {
    m_aspectRatio = m_fov.GetAspectRatio();
  }

  template <FRUSTUM_PERSP_TEMPS>
  Frustum_T<FRUSTUM_PERSP_PARAMS>::Params::
    Params(const Params& a_other)
    : m_near(a_other.m_near)
    , m_far (a_other.m_far)
    , m_aspectRatio(a_other.m_aspectRatio)
    , m_fov(a_other.m_fov)
  { }

  template <FRUSTUM_PERSP_TEMPS>
  FRUSTUM_PERSP_TYPE::Params&
    Frustum_T<FRUSTUM_PERSP_PARAMS>::Params::
    SetNear(real_type a_near)
  {
    m_near = a_near;
    return *this;
  }

  template <FRUSTUM_PERSP_TEMPS>
  FRUSTUM_PERSP_TYPE::Params&
    Frustum_T<FRUSTUM_PERSP_PARAMS>::Params::
    SetFar(real_type a_far)
  {
    m_far = a_far;
    return *this;
  }

  //------------------------------------------------------------------------
  // Frustum

  template <FRUSTUM_PERSP_TEMPS>
  Frustum_T<FRUSTUM_PERSP_PARAMS>::
    Frustum_T()
    : m_params(fov_type(degree_type(90.0f),
               ar_type(),
               types::p_FOV::horizontal()) )
  { }

  template <FRUSTUM_PERSP_TEMPS>
  Frustum_T<FRUSTUM_PERSP_PARAMS>::
    Frustum_T(const rect_type& a_rect, real_type a_near, real_type a_far)
    : m_params(fov_type(degree_type(90.0f),
                        ar_type(),
                        types::p_FOV::horizontal()) )
  {
    using namespace types;

    real_type top		 = a_rect.template GetValue<typename rect_type::top>();
    real_type bottom = a_rect.template GetValue<typename rect_type::bottom>();
    real_type left	 = a_rect.template GetValue<typename rect_type::left>();
    real_type right	 = a_rect.template GetValue<typename rect_type::right>();

    this->DoDefinePlanes
      (plane_args(a_near, a_far, top, bottom, left, right));

    typename ar_type::width width(Math<real_type>::Abs(right - left));
    typename ar_type::height height(Math<real_type>::Abs(top - bottom));

    pyth_type pythHalfAngle =
      pyth_type( typename pyth_type::base(a_near),
                 typename pyth_type::opposite(right) );
    ar_type    ar(width, height);

    m_params = Params(fov_type(pythHalfAngle, ar, p_FOV::horizontal() ));
    m_params.SetNear(a_near).SetFar(a_far);
  }

  template <FRUSTUM_PERSP_TEMPS>
  Frustum_T<FRUSTUM_PERSP_PARAMS>::
    Frustum_T(const Params& a_params)
    : m_params(a_params)
  {
    using namespace math::utils;

    degree_type halfFOV
      (m_params.GetFOV().template Get
      <types::p_FOV::vertical>().template GetAs<degree_type>() / 2.0f);

    typedef Pythagoras_T<real_type>   pyth_type;

    pyth_type pyth =
      pyth_type(halfFOV, typename pyth_type::base(m_params.GetNear()));

    real_type top = pyth.template GetSide<typename pyth_type::opposite>();
    real_type right = m_params.GetAspectRatio().Get() * top;
    this->DoDefinePlanes
      (plane_args(m_params.GetNear(), m_params.GetFar(),
                  top, -top, -right, right) );
  }

  template <FRUSTUM_PERSP_TEMPS>
  Frustum_T<FRUSTUM_PERSP_PARAMS>::
    ~Frustum_T()
  { }

  template <FRUSTUM_PERSP_TEMPS>
  void Frustum_T<FRUSTUM_PERSP_PARAMS>::
    BuildFrustum()
  {
    using namespace p_frustum;

    real_type pTop    = this->template GetPlane<Top>();
    real_type pBott   = this->template GetPlane<Bottom>();
    real_type pLeft   = this->template GetPlane<Left>();
    real_type pRight  = this->template GetPlane<Right>();
    real_type pNear   = this->template GetPlane<Near>();
    real_type pFar    = this->template GetPlane<Far>();

    real_type RminLReci = 1 / (pRight - pLeft);
    real_type TminBReci = 1 / (pTop - pBott);
    real_type FminNReci = 1 / (pFar - pNear);

    matrix_type& projMatrix = this->DoGetProjectionMatrix();

    projMatrix(0, 0) = 2 * pNear * RminLReci;
    projMatrix(1, 1) = 2 * pNear * TminBReci;
    projMatrix(0, 2) =  (pRight + pLeft)  * RminLReci;
    projMatrix(1, 2) =  (pTop   + pBott)  * TminBReci;
    projMatrix(2, 2) = -(pFar   + pNear ) * FminNReci;
    projMatrix(3, 2) = -1;
    projMatrix(2, 3) = -2 * pFar * pNear  * FminNReci;
    projMatrix(3, 3) = 0;
  }

  template <FRUSTUM_PERSP_TEMPS>
  FRUSTUM_PERSP_TYPE::ray_type
    Frustum_T<FRUSTUM_PERSP_PARAMS>::
    GetRay(const types::Vector3<real_type>& a_xyzNDC) const
  {
    TLOC_ASSERT(a_xyzNDC[0] >= -1.0f && a_xyzNDC[0] <= 1.0f &&
                a_xyzNDC[1] >= -1.0f && a_xyzNDC[1] <= 1.0f &&
                a_xyzNDC[2] >= -1.0f && a_xyzNDC[2] <= 1.0f,
                "Vector not in Normalized Device Co-ordinates");

    real_type pFar  = m_params.GetFar();
    real_type pNear = m_params.GetNear();

    const matrix_type& projMatrix = this->GetProjectionMatrix();

    using math_t::Vector3;
    /* For details, see Saad's Master's thesis Appendix H */

    // We need to go from NDC -> Clip -> Eye
    // Note that w_clip (perspective divide) is -z_eye. How? When we multiply
    // the xyz_eye vector with M_proj, we get xyzw_clip, where w = -z_eye due
    // to the M_proj lower low being 0, 0, -1 (the z_eye), 0

    // We need z_eye
    const real_type z_eye
      = (2 * pFar * pNear) /
          ( (a_xyzNDC[2] * (pFar - pNear) - (pFar + pNear)) );

    // x_eye = -z_eye/P_00(x_NDC + P_20)
    real_type x_eye = (-z_eye / projMatrix.Get(0, 0)) *
                      (a_xyzNDC[0] + projMatrix.Get(0, 2));

    // y_eye = -z_eye/P_11(x_NDC + P_21)
    real_type y_eye = (-z_eye / projMatrix.Get(1, 1)) *
                      (a_xyzNDC[1] + projMatrix.Get(1, 2));

    Vector3<real_type> rayOrigin(x_eye, y_eye, z_eye);
    Vector3<real_type> rayDir(rayOrigin);
    rayDir.Normalize();

    return ray_type(typename ray_type::origin(rayOrigin),
                    typename ray_type::direction(rayDir));
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Frustum_T<f32, p_frustum::Perspective>;
  template class Frustum_T<f64, p_frustum::Perspective>;

  //////////////////////////////////////////////////////////////////////////
  // Frustum<Orthographic>

#define FRUSTUM_ORTHO_TEMPS  typename T_Real
#define FRUSTUM_ORTHO_PARAMS T_Real, p_frustum::Orthographic
#define FRUSTUM_ORTHO_TYPE   typename Frustum_T<FRUSTUM_ORTHO_PARAMS>

  //------------------------------------------------------------------------
  // Frustum

  template <FRUSTUM_ORTHO_TEMPS>
  Frustum_T<FRUSTUM_ORTHO_PARAMS>::
    Frustum_T()
  { }

  template <FRUSTUM_ORTHO_TEMPS>
  Frustum_T<FRUSTUM_ORTHO_PARAMS>::
    Frustum_T(const rect_type& a_rect, real_type a_near, real_type a_far)
  {
    using namespace types;
    using namespace math::utils;

    real_type top		 = a_rect.template GetValue<typename rect_type::top>();
    real_type bottom = a_rect.template GetValue<typename rect_type::bottom>();
    real_type left	 = a_rect.template GetValue<typename rect_type::left>();
    real_type right	 = a_rect.template GetValue<typename rect_type::right>();

    this->DoDefinePlanes
      (plane_args(a_near, a_far, top, bottom, left, right));
  }

  template <FRUSTUM_ORTHO_TEMPS>
  Frustum_T<FRUSTUM_ORTHO_PARAMS>::
    ~Frustum_T()
  { }

  template <FRUSTUM_ORTHO_TEMPS>
  void Frustum_T<FRUSTUM_ORTHO_PARAMS>::
    BuildFrustum()
  {
    using namespace p_frustum;

    real_type pTop    = this->template GetPlane<Top>();
    real_type pBott   = this->template GetPlane<Bottom>();
    real_type pLeft   = this->template GetPlane<Left>();
    real_type pRight  = this->template GetPlane<Right>();
    real_type pNear   = this->template GetPlane<Near>();
    real_type pFar    = this->template GetPlane<Far>();

    real_type RminLReci = 1 / (pRight - pLeft);
    real_type TminBReci = 1 / (pTop - pBott);
    real_type FminNReci = 1 / (pFar - pNear);

    matrix_type& projMatrix = this->DoGetProjectionMatrix();

    projMatrix(0, 0) =  2 * RminLReci;
    projMatrix(1, 1) =  2 * TminBReci;
    projMatrix(2, 2) = -2 * FminNReci;

    projMatrix(0, 3) = -( (pRight + pLeft) * RminLReci);
    projMatrix(1, 3) = -( (pTop   + pBott) * TminBReci);
    projMatrix(2, 3) = -( (pFar   + pNear) * FminNReci);

    projMatrix(3, 3) = 1;
  }

  template <FRUSTUM_ORTHO_TEMPS>
  FRUSTUM_ORTHO_TYPE::ray_type
    Frustum_T<FRUSTUM_ORTHO_PARAMS>::
    GetRay(const types::Vector3<real_type>& a_xyzNDC) const
  {
    TLOC_ASSERT(a_xyzNDC[0] >= -1.0f && a_xyzNDC[0] <= 1.0f &&
                a_xyzNDC[1] >= -1.0f && a_xyzNDC[1] <= 1.0f &&
                a_xyzNDC[2] >= -1.0f && a_xyzNDC[2] <= 1.0f,
                "Vector not in Normalized Device Co-ordinates");

    real_type pFar  = this->template GetPlane<p_frustum::Far>();
    real_type pNear = this->template GetPlane<p_frustum::Near>();

    const matrix_type& projMatrix = this->GetProjectionMatrix();

    using math_t::Vector3;
    /* For details, see Saad's Master's thesis Appendix H */

    // We need to go from NDC -> Clip -> Eye
    // Note that w_clip (perspective divide) is -z_eye. How? When we multiply
    // the xyz_eye vector with M_proj, we get xyzw_clip, where w = -z_eye due
    // to the M_proj lower low being 0, 0, -1 (the z_eye), 0

    // We need z_eye
    const real_type z_eye
      = - ((pFar - pNear) * a_xyzNDC[2] + (pFar + pNear)) / 2;

    // x_eye = -z_eye/P_00(x_NDC + P_20)
    real_type x_eye = (a_xyzNDC[0] - projMatrix.Get(0, 3)) /
                       projMatrix.Get(0, 0);

    real_type y_eye = (a_xyzNDC[1] - projMatrix.Get(1, 3)) /
                       projMatrix.Get(1, 1);

    Vector3<real_type> rayOrigin(x_eye, y_eye, z_eye);
    Vector3<real_type> rayDir(0, 0, -1);

    return ray_type(typename ray_type::origin(rayOrigin),
                    typename ray_type::direction(rayDir));
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Frustum_T<f32, p_frustum::Orthographic>;
  template class Frustum_T<f64, p_frustum::Orthographic>;


};};};