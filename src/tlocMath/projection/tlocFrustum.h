#ifndef _TLOC_MATH_VIEW_PROJECTION_FRUSTUM_H
#define _TLOC_MATH_VIEW_PROJECTION_FRUSTUM_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/types/tlocAngle.h>
#include <tlocMath/types/tlocMatrix4.h>

#include <tlocMath/types/tlocAspectRatio.h>
#include <tlocMath/types/tlocFOV.h>
#include <tlocMath/types/tlocRay.h>

namespace tloc { namespace math { namespace proj {

  namespace p_frustum
  {
    struct Perspective{};
    struct Orthographic{};

    struct FOVy{};
    struct FOVx{};

    struct Near       { enum { k_planeIndex = 0 }; };
    struct Far        { enum { k_planeIndex = 1 }; };
    struct Top        { enum { k_planeIndex = 2 }; };
    struct Bottom     { enum { k_planeIndex = 3 }; };
    struct Left       { enum { k_planeIndex = 4 }; };
    struct Right      { enum { k_planeIndex = 5 }; };
    struct PlaneCount { enum { k_planeIndex = 6 }; };
  };

  //------------------------------------------------------------------------
  // Frustum

  template <typename T_Real>
  class Frustum_TI
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T_Real);

  public:
    typedef T_Real                                      real_type;
    typedef Frustum_TI<real_type>                       this_type;
    typedef math::types::Matrix4<real_type>             matrix_type;
    typedef core::data_structs::Tuple
      <real_type, p_frustum::PlaneCount::k_planeIndex>  cont_type;
    typedef types::Ray_T<real_type, 3>                  ray_type;

  public:
    Frustum_TI(const this_type& a_other);
    ~Frustum_TI();

    template <typename T_Plane>
    real_type GetPlane() const;

    ray_type  GetRay(const types::Vector3<real_type>& a_xyzNDC) const;

    TLOC_DECL_AND_DEF_SETTER(matrix_type,
                             SetProjectionMatrix, m_projMatrix);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(matrix_type,
                                          GetProjectionMatrix, m_projMatrix);

  protected:
    typedef typename core::data_structs::Variadic<real_type,
      p_frustum::PlaneCount::k_planeIndex> plane_args;

  protected:
    Frustum_TI();

    void DoDefinePlanes(const plane_args& a_vars);

    TLOC_DECL_AND_DEF_GETTER_DIRECT(matrix_type,
                                    DoGetProjectionMatrix, m_projMatrix);
  private:
    cont_type                     m_planes;
    matrix_type                   m_projMatrix;
  };

  //````````````````````````````````````````````````````````````````````````
  // template definitions

  template <typename T_Real>
  template <typename T_Planes>
  typename Frustum_TI<T_Real>::real_type
    Frustum_TI<T_Real>::
    GetPlane() const
  { return m_planes[T_Planes::k_planeIndex]; }

  //------------------------------------------------------------------------
  //

  template <typename T_Real, typename T_FrustumType>
  class Frustum_T
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_FrustumType, p_frustum::Perspective>::value ||
       Loki::IsSameType<T_FrustumType, p_frustum::Orthographic>::value),
       Invalid_frustum_type);
  };

  //------------------------------------------------------------------------
  // Frustum_T<Perspective>

  template <typename T_Real>
  class Frustum_T<T_Real, p_frustum::Perspective>
    : public Frustum_TI<T_Real>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T_Real);

  public:
    typedef Frustum_TI<T_Real>                          base_type;
    typedef typename base_type::real_type               real_type;
    typedef typename base_type::plane_args              plane_args;

    typedef p_frustum::Perspective                      projection_type;
    typedef Frustum_T<T_Real, projection_type>          this_type;

    typedef core::data_structs::Tuple
      <real_type, p_frustum::PlaneCount::k_planeIndex>  cont_type;

    typedef math_t::Rectangle_T
      <real_type, 
       math_t::p_rectangle::position::Center>           rect_type;

    typedef types::Ray_T<real_type, 3>                  ray_type;
    typedef math_t::Matrix4<real_type>                  matrix_type;

    typedef types::FOV_T<real_type>                     fov_type;
    typedef types::AspectRatio_T<real_type>             ar_type;
    typedef types::Degree_T<real_type>                  degree_type;
    typedef utils::Pythagoras_T<real_type>              pyth_type;

  public:
    struct Params
    {
    public:
      typedef Params            this_type;

    public:
      Params(const fov_type& a_fov);
      Params(const Params& a_other);

      TLOC_DECL_AND_DEF_GETTER(real_type, GetNear, m_near);
      TLOC_DECL_AND_DEF_GETTER(real_type, GetFar, m_far);
      TLOC_DECL_AND_DEF_GETTER(real_type, GetConvergence, m_convergence);
      TLOC_DECL_AND_DEF_GETTER(real_type, GetInteraxial, m_interaxial);

      TLOC_DECL_AND_DEF_GETTER(ar_type,   GetAspectRatio, m_aspectRatio);
      TLOC_DECL_AND_DEF_GETTER(fov_type,  GetFOV, m_fov);

      TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(real_type, SetNear, m_near);
      TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(real_type, SetFar, m_far);
      TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(real_type, SetConvergence,
                                              m_convergence);
      TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(real_type, SetInteraxial,
                                              m_interaxial);

    private:
      real_type     m_near;
      real_type     m_far;
      real_type     m_convergence;
      real_type     m_interaxial;

      ar_type       m_aspectRatio;
      fov_type      m_fov;
    };

  public:
    typedef Params                                    param_type;

  public:
    Frustum_T();
    Frustum_T(const rect_type& a_rect, real_type a_near, real_type a_far);
    Frustum_T(const Params& a_params);

    ~Frustum_T();

    void      BuildFrustum();

    // TODO: Should be a macro
    // Calls base function. Only needed for clarity
    template <typename T_Plane>
    real_type GetPlane() const;

    ray_type  GetRay(const types::Vector3<real_type>& a_xyzNDC) const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Params, GetParams, m_params);

  private:
    Params                        m_params;
  };

  //````````````````````````````````````````````````````````````````````````
  // template definitions

  template <typename T_Real>
  template <typename T_Planes>
  typename Frustum_T<T_Real, p_frustum::Perspective>::real_type
    Frustum_T<T_Real, p_frustum::Perspective>::
    GetPlane() const
  { return base_type::template GetPlane<T_Planes>(); }

  //------------------------------------------------------------------------
  // Frustum_T<Orthographic>

  template <typename T_Real>
  class Frustum_T<T_Real, p_frustum::Orthographic>
    : public Frustum_TI<T_Real>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T_Real);

  public:
    typedef Frustum_TI<T_Real>                          base_type;
    typedef typename base_type::real_type               real_type;
    typedef typename base_type::plane_args              plane_args;

    typedef p_frustum::Orthographic                     projection_type;
    typedef Frustum_T<T_Real, projection_type>          this_type;

    typedef core::data_structs::Tuple
      <real_type, p_frustum::PlaneCount::k_planeIndex>  cont_type;

    typedef math_t::Rectangle_T
      <real_type, 
       math_t::p_rectangle::position::Center>           rect_type;

    typedef tl_size                                     size_type;
    typedef types::Ray_T<real_type, 3>                  ray_type;
    typedef math::types::Matrix4<real_type>             matrix_type;

    typedef types::FOV_T<real_type>                     fov_type;
    typedef types::AspectRatio_T<real_type>             ar_type;
    typedef types::Degree_T<real_type>                  degree_type;

  public:
    Frustum_T();
    Frustum_T(const rect_type& a_rect, real_type a_near, real_type a_far);
    ~Frustum_T();

    void      BuildFrustum();

    // TODO: Should be a macro
    // Calls base function. Only needed for clarity
    template <typename T_Plane>
    real_type GetPlane() const;

    ray_type  GetRay(const types::Vector3<real_type>& a_xyzNDC) const;
  };

  //````````````````````````````````````````````````````````````````````````
  // template definitions

  template <typename T_Real>
  template <typename T_Planes>
  typename Frustum_T<T_Real, p_frustum::Orthographic>::real_type
    Frustum_T<T_Real, p_frustum::Orthographic>::
    GetPlane() const
  { return base_type::template GetPlane<T_Planes>(); }

  //------------------------------------------------------------------------
  // typedefs

  typedef Frustum_TI<tl_float>  Frustum;
  typedef Frustum_TI<f32>       frustum_f32;
  typedef Frustum_TI<f64>       frustum_f64;

  typedef Frustum_T<tl_float, p_frustum::Perspective>   FrustumPersp;
  typedef Frustum_T<tl_float, p_frustum::Orthographic>  FrustumOrtho;

  typedef Frustum_T<f32, p_frustum::Perspective>   frustum_persp_f32;
  typedef Frustum_T<f32, p_frustum::Orthographic>  frustum_ortho_f32;

  typedef Frustum_T<f64, p_frustum::Perspective>   frustum_persp_f64;
  typedef Frustum_T<f64, p_frustum::Orthographic>  frustum_ortho_f64;

};};};

#endif