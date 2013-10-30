#ifndef _TLOC_MATH_TYPES_H_
#define _TLOC_MATH_TYPES_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace math { namespace types {

  template <typename T, tl_size T_Size>
  class Ray_T
  {
    TLOC_STATIC_ASSERT(T_Size == 2 || T_Size == 3,
      Ray_only_supports_size_value_of_2_or_3);
  };

  template <typename T>
  class Ray_T<T, 3>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    typedef Ray_T<T, 3>                              this_type;
    typedef Vector3<T>                               vec_type;
    typedef Vector3<T>                               dir_vec_type;
    typedef Matrix3<T>                               orientation_type;
    typedef Matrix4<T>                               transform_type;

    typedef core::types::StrongType_T<vec_type, 0>   origin;
    typedef core::types::StrongType_T<vec_type, 1>   direction;

  public:
    Ray_T();
    Ray_T(origin a_origin, direction a_direction = direction(vec_type(0)) );

    this_type             operator+(const this_type& a_other) const;
    this_type             operator-(const this_type& a_other) const;
    this_type             operator*(const transform_type& a_transform) const;
    this_type             operator*(const orientation_type& a_transform) const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(vec_type, GetOrigin, m_origin);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(dir_vec_type, GetDirection, m_direction);

  private:
    vec_type      m_origin;
    dir_vec_type  m_direction;

  };

  template <typename T>
  class Ray_T<T, 2>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    typedef Ray_T<T, 2>                              this_type;
    typedef Vector2<T>                               vec_type;
    typedef Vector3<T>                               dir_vec_type;

    typedef core::types::StrongType_T<vec_type, 0>   origin;
    typedef core::types::StrongType_T<vec_type, 1>   direction;

  public:
    Ray_T();
    Ray_T(origin a_origin, direction a_direction = direction(vec_type(0)) );

    this_type             operator+(const this_type& a_other) const;
    this_type             operator-(const this_type& a_other) const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(vec_type, GetOrigin, m_origin);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(dir_vec_type, GetDirection, s_direction);

  private:
    vec_type                  m_origin;
    static const dir_vec_type s_direction;
  };

  template <typename T>
  typename Ray_T<T, 2>::dir_vec_type
    const Ray_T<T, 2>::s_direction =
    typename Ray_T<T, 2>::dir_vec_type(core_ds::Variadic<T, 3>(0, 0, 1));

  //------------------------------------------------------------------------
  // Typedefs

  typedef Ray_T<tl_float, 2> Ray2f;
  typedef Ray_T<tl_float, 3> Ray3f;

  typedef Ray_T<f32, 2>     Ray2f32;
  typedef Ray_T<f32, 3>     Ray3f32;

  typedef Ray_T<f64, 2>     Ray2f64;
  typedef Ray_T<f64, 3>     Ray3f64;


};};};

#endif