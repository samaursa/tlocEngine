#ifndef _TLOC_GRAPHICS_VIEW_PROJECTION_FRUSTUM_H
#define _TLOC_GRAPHICS_VIEW_PROJECTION_FRUSTUM_H

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocMath/data_types/tlocRectangle.h>
#include <tlocMath/angle/tlocAngle.h>
#include <tlocMath/matrix/tlocMatrix4.h>

#include <tlocGraphics/data_types/tlocAspectRatio.h>
#include <tlocGraphics/data_types/tlocFOV.h>

namespace tloc { namespace graphics { namespace view_proj {

  namespace p_frustum
  {
    struct FOVy{};
    struct FOVx{};
  };

  class Frustum
  {
  public:
    struct Planes
    {
      enum
      {
        k_near = 0,
        k_far,
        k_top,
        k_bottom,
        k_left,
        k_right,
        k_count,
      };

    private:
      Planes();
    };

  public:
    typedef tl_float                                    real_type;
    typedef core::Tuple<real_type, Planes::k_count>     cont_type;
    typedef math::types::Rectangle<real_type>           rect_type;
    typedef tl_size                                     size_type;
    typedef math::Radian                                angle_type;
    typedef types::FOV                                  fov_type;
    typedef types::AspectRatio                          ar_type;
    typedef math::Matrix4<real_type>                    matrix_type;

  public:
    struct Params
    {
      Params(const fov_type& a_fov);
      Params(const Params& a_other);

      Params&   SetNear(real_type a_near);
      Params&   SetFar(real_type a_far);

      TLOC_DECL_AND_DEF_GETTER(real_type, GetNear, m_near);
      TLOC_DECL_AND_DEF_GETTER(real_type, GetFar, m_far);
      TLOC_DECL_AND_DEF_GETTER(ar_type, GetAspectRatio, m_aspectRatio);
      TLOC_DECL_AND_DEF_GETTER(fov_type, GetFOV, m_fov);

    private:
      real_type     m_near;
      real_type     m_far;
      ar_type       m_aspectRatio;
      fov_type      m_fov;
    };

  public:
    Frustum(const rect_type& a_rect, real_type a_near, real_type a_far);
    Frustum(const Params& a_params);

    ~Frustum();

    void BuildFrustum();
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Params, GetParams, m_params);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(matrix_type,
                                          GetProjectionMatrix, m_projMatrix);

  private:
    typedef core::Variadic<real_type, Planes::k_count> plane_args;

    void DoDefinePlanes(const plane_args& a_vars);
    void DoBuildFrustumFromPlanes();

    Params                        m_params;
    cont_type                     m_planes;
    matrix_type                   m_projMatrix;
  };

};};};

#endif