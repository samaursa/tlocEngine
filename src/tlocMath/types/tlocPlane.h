#ifndef _TLOC_MATH_TYPES_PLANE_H_
#define _TLOC_MATH_TYPES_PLANE_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocMath/types/tlocRay.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Plane_T
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);
  public:
    typedef T                                        value_type;
    typedef value_type                               real_type;
    typedef Plane_T<value_type>                      this_type;
    typedef Vector_T<value_type, 3>                  vec_type;
    typedef Vector_T<value_type, 3>                  dir_vec_type;
    typedef Matrix_T<value_type, 3>                  orientation_type;
    typedef Matrix_T<value_type, 4>                  transform_type;
    typedef Ray_T<real_type, 3>                      ray_type;

    typedef core::types::StrongType_T<vec_type, 0>   origin;
    typedef core::types::StrongType_T<vec_type, 1>   direction;

  public:
    Plane_T(origin a_origin = origin(vec_type::ZERO), 
            direction a_dir = direction(vec_type::UNIT_Z) );

    vec_type              GetIntersect(const ray_type& a_ray) const;
    bool                  GetIsParallel(const ray_type& a_ray) const;

    this_type             operator+(const this_type& a_other) const;
    this_type&            operator+=(const this_type& a_other);

    this_type             operator-(const this_type& a_other) const;
    this_type&            operator-=(const this_type& a_other);

    this_type             operator*(const transform_type& a_transform) const;
    this_type             operator*(const orientation_type& a_transform) const;
    this_type&            operator*=(const transform_type& a_transform);
    this_type&            operator*=(const orientation_type& a_transform);

    bool                  operator==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(vec_type, GetOrigin, m_origin);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(dir_vec_type, GetDirection, m_direction);

  private:
    vec_type      m_origin;
    dir_vec_type  m_direction;

  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Plane_T<tl_float> Plane;
  typedef Plane_T<f32>      Planef32;
  typedef Plane_T<f64>      Planef64;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Plane_T<tl_float>);
  TLOC_EXTERN_TEMPLATE_CLASS(Plane_T<f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Plane_T<f64>);

};};};

#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace core {

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig, typename T>
    const Log_T<T_Logger, T_BuildConfig>&
      operator << (const Log_T<T_Logger, T_BuildConfig>& a_log,
                   const math_t::Plane_T<T>& a_plane)
    {
      a_log << "orig: [" << a_plane.GetOrigin() << "] dir: [" 
        << a_plane.GetDirection() << "]"; 

      return a_log;
    }

  };

};};

#endif