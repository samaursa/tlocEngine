#include "tlocRay.h"

#include <tlocCore/types/tlocStrongType.inl.h>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>

namespace tloc { namespace math { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Ray_T<T, T_Size>

#define RAY_TEMPS   typename T
#define RAY_PARAMS  T, 3
#define RAY_TYPE    typename Ray_T<RAY_PARAMS>

  template <RAY_TEMPS>
  Ray_T<RAY_PARAMS>::
    Ray_T()
    : m_origin(0)
    , m_direction(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  Ray_T<RAY_PARAMS>::
    Ray_T(origin a_origin, direction a_direction)
    : m_origin(a_origin)
    , m_direction(a_direction)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator+(const this_type& a_other) const
  {
    this_type temp(*this);
    temp += a_other;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator-(const this_type& a_other) const
  {
    this_type temp(*this);
    temp -= a_other;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator*(const transform_type& a_trans) const
  {
    this_type temp(*this);
    temp *= a_trans;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator*(const orientation_type& a_rotMat) const
  {
    this_type temp(*this);
    temp *= a_rotMat;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type&
  Ray_T<RAY_PARAMS>::
    operator+=(const this_type& a_other)
  {
    m_origin = GetOrigin() + a_other.GetOrigin();
    m_direction = GetDirection() + a_other.GetDirection();
    m_direction.Normalize();

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type&
  Ray_T<RAY_PARAMS>::
    operator-=(const this_type& a_other)
  {
    m_origin = GetOrigin() - a_other.GetOrigin();
    m_direction = GetDirection() - a_other.GetDirection();
    m_direction.Normalize();

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type&
  Ray_T<RAY_PARAMS>::
    operator*=(const transform_type& a_trans)
  {
    typedef Vector_T<T, 4>    vec4_type;

    auto newOrigin = a_trans * m_origin.template ConvertTo<vec4_type>();

    Matrix_T<T, 3> mRot(a_trans[0], a_trans[4], a_trans[8],
                        a_trans[1], a_trans[5], a_trans[9],
                        a_trans[2], a_trans[6], a_trans[10]);

    m_origin = newOrigin.template ConvertTo<vec_type>();
    m_direction = mRot * m_direction;

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type&
  Ray_T<RAY_PARAMS>::
    operator*=(const orientation_type& a_rotMat)
  {
    m_origin = a_rotMat * m_origin;
    m_direction = a_rotMat * m_direction;

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  bool
  Ray_T<RAY_PARAMS>::
    operator==(const this_type& a_other) const
  {
    return m_origin == a_other.m_origin && m_direction == a_other.m_direction;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Ray_T<T, 2>

#define RAY2_TEMPS   typename T
#define RAY2_PARAMS  T, 2
#define RAY2_TYPE    typename Ray_T<RAY2_PARAMS>

  template <RAY2_TEMPS>
  Ray_T<RAY2_PARAMS>::
    Ray_T()
    : m_origin(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  Ray_T<RAY2_PARAMS>::
    Ray_T(origin a_origin, direction )
    : m_origin(a_origin)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  RAY2_TYPE::this_type
  Ray_T<RAY2_PARAMS>::
    operator+(const this_type& a_other) const
  {
    this_type temp(*this);
    temp += a_other;
    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  RAY2_TYPE::this_type
  Ray_T<RAY2_PARAMS>::
    operator-(const this_type& a_other) const
  {
    this_type temp(*this);
    temp -= a_other;
    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  RAY2_TYPE::this_type&
  Ray_T<RAY2_PARAMS>::
    operator+=(const this_type& a_other)
  {
    m_origin = GetOrigin() + a_other.GetOrigin();
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  RAY2_TYPE::this_type&
  Ray_T<RAY2_PARAMS>::
    operator-=(const this_type& a_other)
  {
    m_origin = GetOrigin() - a_other.GetOrigin();
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  bool
  Ray_T<RAY2_PARAMS>::
    operator==(const this_type& a_other) const
  {
    return m_origin == a_other.m_origin;
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Ray_T<f32, 2>;
  template class Ray_T<f32, 3>;

  template class Ray_T<f64, 2>;
  template class Ray_T<f64, 3>;

};};};

TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec2f32);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec2f64);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec3f32);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec3f64);