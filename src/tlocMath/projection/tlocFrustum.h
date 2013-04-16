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

    struct Near
    { enum { k_planeIndex = 0 }; };
    struct Far
    { enum { k_planeIndex = 1 }; };
    struct Top
    { enum { k_planeIndex = 2 }; };
    struct Bottom
    { enum { k_planeIndex = 3 }; };
    struct Left
    { enum { k_planeIndex = 4 }; };
    struct Right
    { enum { k_planeIndex = 5 }; };
    struct PlaneCount
    { enum { k_planeIndex = 6 }; };
  };

  //------------------------------------------------------------------------
  // FrustumBase

  class FrustumBase
  {
  public:
    typedef tl_float                                    real_type;
    typedef math::types::Matrix4<real_type>             matrix_type;
    typedef core::data_structs::Tuple
      <real_type, p_frustum::PlaneCount::k_planeIndex>  cont_type;

  public:

    template <typename T_Plane>
    real_type GetPlane() const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(matrix_type,
                                          GetProjectionMatrix, m_projMatrix);

  protected:
    typedef core::data_structs::Variadic<real_type,
      p_frustum::PlaneCount::k_planeIndex> plane_args;

  protected:
    FrustumBase();
    ~FrustumBase();

    void DoDefinePlanes(const plane_args& a_vars);

    TLOC_DECL_AND_DEF_GETTER_DIRECT(matrix_type,
                                    DoGetProjectionMatrix, m_projMatrix);
  private:
    cont_type                     m_planes;
    matrix_type                   m_projMatrix;
  };

  //````````````````````````````````````````````````````````````````````````
  // template definitions

  template <typename T_Planes>
  FrustumBase::real_type
    FrustumBase::
    GetPlane() const
  { return m_planes[T_Planes::k_planeIndex]; }

  //------------------------------------------------------------------------
  //

  template <typename T_FrustumType>
  class Frustum_T
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_FrustumType, p_frustum::Perspective>::value ||
       Loki::IsSameType<T_FrustumType, p_frustum::Orthographic>::value),
       Invalid_frustum_type);
  };

  //------------------------------------------------------------------------
  // Frustum_T<Perspective>

  template <>
  class Frustum_T<p_frustum::Perspective> : public FrustumBase
  {
  public:
    typedef p_frustum::Perspective                      projection_type;
    typedef Frustum_T<projection_type>                  this_type;

    typedef tl_float                                    real_type;
    typedef core::data_structs::Tuple
      <real_type, p_frustum::PlaneCount::k_planeIndex>  cont_type;
    typedef math::types::Rectangle_T<real_type>         rect_type;
    typedef tl_size                                     size_type;
    typedef types::Ray_T<real_type, 3>                  ray_type;
    typedef math::types::Matrix4<real_type>             matrix_type;

    typedef types::FOV                                  fov_type;
    typedef types::AspectRatio                          ar_type;

  public:
    struct Params
    {
      Params(const fov_type& a_fov);
      Params(const Params& a_other);

      Params&   SetNear(real_type a_near);
      Params&   SetFar(real_type a_far);


      TLOC_DECL_AND_DEF_GETTER(real_type, GetNear, m_near);
      TLOC_DECL_AND_DEF_GETTER(real_type, GetFar, m_far);
      TLOC_DECL_AND_DEF_GETTER(ar_type,   GetAspectRatio, m_aspectRatio);
      TLOC_DECL_AND_DEF_GETTER(fov_type,  GetFOV, m_fov);

    private:
      real_type     m_near;
      real_type     m_far;
      ar_type       m_aspectRatio;
      fov_type      m_fov;
    };

  public:
    Frustum_T(const rect_type& a_rect, real_type a_near, real_type a_far);
    Frustum_T(const Params& a_params);

    ~Frustum_T();

    void      BuildFrustum();
    ray_type  GetRay(const types::Vector3<real_type>& a_xyzNDC) const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Params, GetParams, m_params);
  private:

    Params                        m_params;
  };

  //------------------------------------------------------------------------
  // Frustum_T<Orthographic>

  template <>
  class Frustum_T<p_frustum::Orthographic> : public FrustumBase
  {
  public:
    typedef p_frustum::Perspective                      projection_type;
    typedef Frustum_T<projection_type>                  this_type;

    typedef tl_float                                    real_type;
    typedef core::data_structs::Tuple
      <real_type, p_frustum::PlaneCount::k_planeIndex>  cont_type;
    typedef math::types::Rectangle_T<real_type>         rect_type;
    typedef tl_size                                     size_type;
    typedef types::Ray_T<real_type, 3>                  ray_type;
    typedef math::types::Matrix4<real_type>             matrix_type;

  public:
    Frustum_T(const rect_type& a_rect, real_type a_near, real_type a_far);
    ~Frustum_T();

    void      BuildFrustum();
    ray_type  GetRay(const types::Vector3<real_type>& a_xyzNDC) const;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef Frustum_T<p_frustum::Perspective>   frustum_persp;
  typedef Frustum_T<p_frustum::Orthographic>  frustum_ortho;

};};};

#endif