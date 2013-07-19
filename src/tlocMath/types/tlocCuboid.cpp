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
                 typename Cuboid_T<T_Real>::near)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::near>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::near)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::near>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::near)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::near>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::near)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::near>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::far)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::far>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::top,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::far)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::top>(),
                        a_cube.template GetValue<typename cuboid_type::far>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::left,
                 typename Cuboid_T<T_Real>::far)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::left>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::far>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Cuboid_T<T_Real>::point_type
      DoGetCoord(const Cuboid_T<T_Real>& a_cube,
                 typename Cuboid_T<T_Real>::bottom,
                 typename Cuboid_T<T_Real>::right,
                 typename Cuboid_T<T_Real>::far)
    {
      typedef Cuboid_T<T_Real>                  cuboid_type;
      typedef typename cuboid_type::point_type  point_type;

      return point_type(a_cube.template GetValue<typename cuboid_type::right>(),
                        a_cube.template GetValue<typename cuboid_type::bottom>(),
                        a_cube.template GetValue<typename cuboid_type::far>());
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
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  Cuboid_T<CUBOID_PARAMS>::
    Cuboid_T(width a_w, height a_h, depth a_d)
    : m_dimensions(a_w, a_h, a_d)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  Cuboid_T<CUBOID_PARAMS>::
    Cuboid_T(left a_l, right a_r, top a_t, bottom a_b, near a_n, far a_f)
    : m_dimensions( (a_r - a_l), (a_t - a_b), (a_near - a_far) )
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
    GetCoord_TopLeftNear() const
  { return DoGetCoord<top, left, near>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopRightNear() const
  { return DoGetCoord<top, right, near>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomLeftNear() const
  { return DoGetCoord<bottom, left, near>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomRightNear() const
  { return DoGetCoord<bottom, right, near>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopLeftFar() const
  { return DoGetCoord<top, left, far>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_TopRightFar() const
  { return DoGetCoord<top, right, far>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomLeftFar() const
  { return DoGetCoord<bottom, left, far>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMP>
  CUBOID_TYPE::point_type
    Cuboid_T<CUBOID_PARAMS>::
    GetCoord_BottomRightFar() const
  { return DoGetCoord<bottom, right, far>(); }

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
           (a_xyzPoint[2] >= GetValue<near>()    ) &&
           (a_xyzPoint[2] <= GetValue<far>()     );
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
    right   overR( tlMax(GetValue<right>()  , a_other.GetValue<right>()) );
    top     overT( tlMax(GetValue<top>()    , a_other.GetValue<top>()) );
    bottom  overB( tlMax(GetValue<bottom>() , a_other.GetValue<bottom>()) );
    near    overN( tlMax(GetValue<near>()   , a_other.GetValue<near>()) );
    far     overF( tlMax(GetValue<far>()    , a_other.GetValue<far>()) );

    a_overlapOut = this_type(overL, overR, overT, overB, overN, overF);

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
    const vec3_type  rayDirInv(1.0f / rayDir[0],
                               1.0f / rayDir[1],
                               1.0f / rayDir[2]);

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
      tymin = (halfDimMin[1] - rayOrig[0]) * rayDirInv[0];
      tymax = (halfDimMax[1] - rayOrig[0]) * rayDirInv[0];
    }
    else
    {
      tymin = (halfDimMax[1] - rayOrig[0]) * rayDirInv[0];
      tymax = (halfDimMin[1] - rayOrig[0]) * rayDirInv[0];
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

};};};