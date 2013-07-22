#include "tlocCuboid.h"

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

namespace tloc { namespace math { namespace types {

  namespace priv {

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::back)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::back>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::back)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::back>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::back)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::back>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::back)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::back>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::front)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::front>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::front)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::front>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::front)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::front>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::front)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::front>());
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // Cuboid_T<T>

#define CUBOID_TEMP     typename T
#define CUBOID_PARAMS   T
#define CUBOID_TYPE     typename Cuboid_T<CUBOID_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  Cuboid_T<CUBOID_PARAMS>::
    Cuboid_T()
    : m_dimensions(0.0f, 0.0f, 0.0f)
    , m_position(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  Cuboid_T<CUBOID_PARAMS>::
    Cuboid_T(width a_w, height a_h, depth a_d,
             position a_pos = position(point_type(0)) )
    : m_dimensions(a_w, a_h, a_d)
    , m_position(a_pos)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  Cuboid_T<CUBOID_PARAMS>::
    Cuboid_T(left a_l, right a_r, top a_t, bottom a_b, front a_fr, back a_ba)
    : m_dimensions( (a_r - a_l), (a_t - a_b), (a_fr - a_ba) )
    , m_position( (a_l + a_r) * 0.5f, (a_t + a_b) * 0.5f, (a_fr + a_ba) * 0.5f)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::this_type&
    Cuboid_T<CUBOID_PARAMS>::
    operator=(const this_type& a_other)
  {
    this_type temp(a_other);
    temp.swap(*this);

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    swap(this_type& a_cuboid)
  {
    using core::swap;

    swap(m_dimensions, a_cuboid.m_dimensions);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  bool
    Cuboid_T<CUBOID_PARAMS>::
    operator==(const this_type& a_other) const
  {
    return m_dimensions == a_other.m_dimensions;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::real_type
    Cuboid_T<CUBOID_PARAMS>::
    GetWidth() const
  { return m_dimensions[width::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::real_type
    Cuboid_T<CUBOID_PARAMS>::
    GetHeight() const
  { return m_dimensions[height::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::real_type
    Cuboid_T<CUBOID_PARAMS>::
    GetDepth() const
  { return m_dimensions[depth::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    SetWidth(real_type a_value)
  { m_dimensions[width::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    SetHeight(real_type a_value)
  { m_dimensions[height::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    SetDepth(real_type a_value)
  { m_dimensions[depth::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopLeftBack() const
  { return DoGetCoord<top, left, back>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopRightBack() const
  { return DoGetCoord<top, right, back>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomLeftBack() const
  { return DoGetCoord<bottom, left, back>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomRightBack() const
  { return DoGetCoord<bottom, right, back>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopLeftFront() const
  { return DoGetCoord<top, left, front>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopRightFront() const
  { return DoGetCoord<top, right, front>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomLeftFront() const
  { return DoGetCoord<bottom, left, front>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomRightFront() const
  { return DoGetCoord<bottom, right, front>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    SetPosition(const point_type& a_centerPosition)
  { m_position = a_centerPosition; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    ResetPosition()
  { m_position.Set(0); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  void
    Cuboid_T<CUBOID_PARAMS>::
    Offset(const point_type& a_offsetBy)
  { m_position += a_offsetBy; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetPosition() const
  { return m_position; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  bool
    Cuboid_T<CUBOID_PARAMS>::
    Contains(const point_type &a_xyzPoint)
  {
    return (a_xyzPoint[0] >= GetValue<left>()    ) &&
           (a_xyzPoint[0] <= GetValue<right>()   ) &&
           (a_xyzPoint[1] <= GetValue<top>()     ) &&
           (a_xyzPoint[1] >= GetValue<bottom>()  ) &&
           (a_xyzPoint[2] >= GetValue<back>()    ) &&
           (a_xyzPoint[2] <= GetValue<front>()     );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  bool
    Cuboid_T<CUBOID_PARAMS>::
    IsValid() const
  {
    return m_dimensions[width::k_index] > 0 &&
           m_dimensions[height::k_index] > 0 &&
           m_dimensions[depth::k_index] > 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  bool
    Cuboid_T<CUBOID_PARAMS>::
    Intersects(const this_type& a_other) const
  {
    this_type temp;
    return Intersects(a_other, temp);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  bool
    Cuboid_T<CUBOID_PARAMS>::
    Intersects(const this_type& a_other, this_type& a_overlapOut) const
  {
    using namespace core;

    left    overL( tlMax(GetValue<left>()   , a_other.GetValue<left>()) );
    right   overR( tlMin(GetValue<right>()  , a_other.GetValue<right>()) );
    top     overT( tlMin(GetValue<top>()    , a_other.GetValue<top>()) );
    bottom  overB( tlMax(GetValue<bottom>() , a_other.GetValue<bottom>()) );
    front   overFr( tlMin(GetValue<front>() , a_other.GetValue<front>()) );
    back    overBa( tlMax(GetValue<back>()  , a_other.GetValue<back>()) );

    a_overlapOut = this_type(overL, overR, overT, overB, overFr, overBa);

    if (a_overlapOut.IsValid())
    { return true; }
    else
    { return false; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  bool
    Cuboid_T<CUBOID_PARAMS>::
    Intersects(const ray_3d_type& a_ray,
               from_origin a_fo = from_origin(true)) const
  {
    // using the method: http://people.csail.mit.edu/amy/papers/box-jgt.pdf

    typedef ray_3d_type::vec_type             vec3_type;

    real_type tmin, tmax, tymin, tymax, tzmin, tzmax;

    const vec3_type& rayOrig = a_ray.GetOrigin();
    const vec3_type& rayDir  = a_ray.GetDirection();
    const vec3_type  rayDirInv( core_ds::Variadic<real_type, 3>
      (1.0f / rayDir[0], 1.0f / rayDir[1], 1.0f / rayDir[2]) );

    const point_type halfDimMin = m_dimensions * -0.5f;
    const point_type halfDimMax = m_dimensions * 0.5f;

    if (rayDir[0] >= 0)
    {
      tmin = (halfDimMin[0] - rayOrig[0]) * rayDirInv[0];
      tmax = (halfDimMax[0] - rayOrig[0]) * rayDirInv[0];
    }
    else
    {
      tmin = (halfDimMax[0] - rayOrig[0]) * rayDirInv[0];
      tmax = (halfDimMin[0] - rayOrig[0]) * rayDirInv[0];
    }

    if (rayDir[1] >= 0)
    {
      tymin = (halfDimMin[1] - rayOrig[1]) * rayDirInv[1];
      tymax = (halfDimMax[1] - rayOrig[1]) * rayDirInv[1];
    }
    else
    {
      tymin = (halfDimMax[1] - rayOrig[1]) * rayDirInv[1];
      tymax = (halfDimMin[1] - rayOrig[1]) * rayDirInv[1];
    }

    if ( (tmin > tymax) || (tymin > tmax) )
    { return false; }

    if (tymin > tmin)
    { tmin = tymin; }
    if (tymax < tmax)
    { tmax = tymax; }

    if (rayDir[2] >= 0)
    {
      tzmin = (halfDimMin[2] - rayOrig[2]) * rayDirInv[2];
      tzmax = (halfDimMax[2] - rayOrig[2]) * rayDirInv[2];
    }
    else
    {
      tzmin = (halfDimMax[2] - rayOrig[2]) * rayDirInv[2];
      tzmax = (halfDimMin[2] - rayOrig[2]) * rayDirInv[2];
    }

    if ( (tmin > tzmax) || (tzmin > tmax) )
    { return false; }
    if (tzmin > tmin)
    { tmin = tzmin; }
    if (tzmax < tmax)
    { tmax = tzmax; }

    if (a_fo && tmin < 0)
    { return false; }
    else
    { return true; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::real_type
    Cuboid_T<CUBOID_PARAMS>::
    DoGetValue(tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL
      (a_index >= left::k_index && a_index <= front::k_index, "Out of bounds!");

    const real_type half = 0.5f;
    switch (a_index)
    {
    case left::k_index:
      return -(m_dimensions[width::k_index] * half) + m_position[0];
    case right::k_index:
      return (m_dimensions[width::k_index] * half) + m_position[0];
    case top::k_index:
      return (m_dimensions[height::k_index] * half) + m_position[1];
    case bottom::k_index:
      return -(m_dimensions[height::k_index] * half) + m_position[1];
    case back::k_index:
      return -(m_dimensions[depth::k_index] * half) + m_position[2];
    case front::k_index:
      return  (m_dimensions[depth::k_index] * half) + m_position[2];
    default:
      return 0;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  template <typename T_Side1, typename T_Side2, typename T_Side3>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    DoGetCoord() const
  {
    return priv::DoGetCoord<real_type>(*this, T_Side1(0), T_Side2(0), T_Side3(0));
  }

  //------------------------------------------------------------------------
  // Explicit initialization

#define TLOC_EXPLICITLY_INSTANTIATE_CUBOID(_type_)\
  template class Cuboid_T<_type_>;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::top, \
                               Cuboid_T<_type_>::left, \
                               Cuboid_T<_type_>::back>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::top, \
                               Cuboid_T<_type_>::right, \
                               Cuboid_T<_type_>::back>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::bottom, \
                               Cuboid_T<_type_>::left, \
                               Cuboid_T<_type_>::back>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::bottom, \
                               Cuboid_T<_type_>::right, \
                               Cuboid_T<_type_>::back>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::top, \
                               Cuboid_T<_type_>::left, \
                               Cuboid_T<_type_>::front>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::top, \
                               Cuboid_T<_type_>::right, \
                               Cuboid_T<_type_>::front>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::bottom, \
                               Cuboid_T<_type_>::left, \
                               Cuboid_T<_type_>::front>() const;\
  \
  template Cuboid_T<_type_>::point_type \
  Cuboid_T<_type_>::DoGetCoord<Cuboid_T<_type_>::bottom, \
                               Cuboid_T<_type_>::right, \
                               Cuboid_T<_type_>::front>() const

  TLOC_EXPLICITLY_INSTANTIATE_CUBOID(f32);
  TLOC_EXPLICITLY_INSTANTIATE_CUBOID(f64);

};};};