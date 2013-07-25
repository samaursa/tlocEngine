#include "tlocRectangle.h"

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#define TLOC_CHECK_RECTANGLE_EXTENTS(_left_, _right_, _top_, _bottom_)\
  TLOC_ASSERT_LOW_LEVEL( (_left <= _right) && (_bottom_ <= _top_),\
  "Rectangle extents are incorrect!");

namespace tloc { namespace math { namespace types {

  namespace priv {

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Rectangle_T<T_Real>::point_type
      DoGetCoord(const Rectangle_T<T_Real>& a_rect,
                 typename Rectangle_T<T_Real>::top,
                 typename Rectangle_T<T_Real>::left)
    {
      typedef Rectangle_T<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::left>(),
                        a_rect.template GetValue<typename rect_type::top>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Rectangle_T<T_Real>::point_type
      DoGetCoord(const Rectangle_T<T_Real>& a_rect,
                 typename Rectangle_T<T_Real>::top,
                 typename Rectangle_T<T_Real>::right)
    {
      typedef Rectangle_T<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::right>(),
                        a_rect.template GetValue<typename rect_type::top>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Rectangle_T<T_Real>::point_type
      DoGetCoord(const Rectangle_T<T_Real>& a_rect,
                 typename Rectangle_T<T_Real>::bottom,
                 typename Rectangle_T<T_Real>::left)
    {
      typedef Rectangle_T<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::left>(),
                        a_rect.template GetValue<typename rect_type::bottom>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real>
    typename Rectangle_T<T_Real>::point_type
      DoGetCoord(const Rectangle_T<T_Real>& a_rect,
                 typename Rectangle_T<T_Real>::bottom,
                 typename Rectangle_T<T_Real>::right)
    {
      typedef Rectangle_T<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::right>(),
                        a_rect.template GetValue<typename rect_type::bottom>());
    }
  };

#define TLOC_RECTANGLE_TEMP typename T
#define TLOC_RECTANGLE_PARAMS T
#define TLOC_RECTANGLE_TYPE typename Rectangle_T<TLOC_RECTANGLE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T()
    : m_dimensions(0.0f, 0.0f)
    , m_position(0, 0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T(width a_w, height a_h, position a_pos)
    : m_dimensions(a_w, a_h)
    , m_position(a_pos)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T(left a_l, right a_r, top a_t, bottom a_b)
    : m_dimensions( (a_r - a_l), (a_t - a_b) )
    , m_position( (a_l + a_r) * 0.5f, (a_t + a_b) * 0.5f )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::this_type&
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    operator= (const this_type& a_other)
  {
    this_type temp(a_other);
    swap(temp);

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  void
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    swap(this_type& a_rect)
  {
    using core::swap;

    swap(m_dimensions, a_rect.m_dimensions);
    swap(m_position, a_rect.m_position);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return m_dimensions == a_other.m_dimensions && m_position == a_other.m_position;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::real_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetWidth() const
  { return m_dimensions[width::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::real_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetHeight() const
  { return m_dimensions[height::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  void
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    SetWidth(real_type a_value)
  { m_dimensions[width::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  void
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    SetHeight(real_type a_value)
  { m_dimensions[height::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetCoord_TopLeft() const
  { return DoGetCoord<top, left>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetCoord_TopRight() const
  { return DoGetCoord<top, right>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetCoord_BottomLeft() const
  { return DoGetCoord<bottom, left>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetCoord_BottomRight() const
  { return DoGetCoord<bottom, right>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  void
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    SetPosition(const point_type& a_centerPosition)
  { m_position = a_centerPosition; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  void
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    ResetPosition()
  { m_position.Set(0); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  void
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Offset(const point_type& a_offsetBy)
  { m_position += a_offsetBy; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Contains(const point_type &a_xyPoint)
  {
    return (a_xyPoint[0] >= GetValue<left>()    ) &&
           (a_xyPoint[0] <= GetValue<right>()   ) &&
           (a_xyPoint[1] <= GetValue<top>()     ) &&
           (a_xyPoint[1] >= GetValue<bottom>()  );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    GetPosition() const
  { return m_position; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    IsValid() const
  {
    return m_dimensions[width::k_index] > 0 &&
           m_dimensions[height::k_index] > 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Intersects(const this_type& a_other) const
  {
    this_type temp;
    return Intersects(a_other, temp);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Intersects(const this_type& a_other, this_type& a_overlapOut) const
  {
    TLOC_ASSERT(IsValid(), "Intersects() may not work with invalid dimensions!");

    using namespace core;

    left    overL(tlMax(GetValue<left>()  , a_other.GetValue<left>()));
    right   overR(tlMin(GetValue<right>() , a_other.GetValue<right>()));
    top     overT(tlMin(GetValue<top>()   , a_other.GetValue<top>()));
    bottom  overB(tlMax(GetValue<bottom>(), a_other.GetValue<bottom>()));

    a_overlapOut = Rectangle_T(overL, overR, overT, overB);

    if (a_overlapOut.IsValid())
    { return true; }
    else
    { return false; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Intersects(const ray_2d_type& a_ray) const
  {
    TLOC_ASSERT(IsValid(), "Intersects() may not work with invalid dimensions!");

    const point_type& rayOrigin = a_ray.GetOrigin();

    // Since we are a 2D box, we assume our direction is +Z
    if (rayOrigin[0] < GetValue<left>() ||
        rayOrigin[0] > GetValue<right>()  ||
        rayOrigin[1] < GetValue<bottom>() ||
        rayOrigin[1] > GetValue<top>() )
    {
      return false;
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::intersect_ret_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Intersects(const ray_3d_type& a_ray, from_origin a_fo,
               double_sided a_ds) const
  {
    TLOC_ASSERT(IsValid(), "Intersects() may not work with invalid dimensions!");

    // following http://geomalgorithms.com/a05-_intersect-1.html

    typedef typename ray_3d_type::vec_type           vec_type;

    const vec_type& orig = a_ray.GetOrigin();
    const vec_type& dir = a_ray.GetDirection();

    const real_type dirDotNormal = dir.Dot(s_normal);

    // Is the ray above the plane with same direction as plane normal or
    // below the plane with the opposite direction as plane normal? Both
    // conditions mean ray is not intersecting if from_origin
    if (a_fo && ( (orig[2] < 0.0f && dirDotNormal < 0.0f) ||
                  (orig[2] > 0.0f && dirDotNormal > 0.0f)) )
    { return false; }

    if (!a_ds && dirDotNormal >= 0.0f)
    { return false; }

    real_type sNumer = -(orig.Dot(s_normal));
    real_type sDenom = dir.Dot(s_normal);

    real_type s = sNumer / sDenom;

    vec_type p = orig + (dir * s);

    bool intersects = Intersects(ray_2d_type(typename ray_2d_type::origin
      (p.template ConvertTo<typename ray_2d_type::vec_type>() )) );

    return core::MakePair(intersects, p);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::real_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    DoGetValue(tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL
      (a_index >= left::k_index && a_index <= bottom::k_index, "Out of bounds!");

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
    default:
      return 0;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  template <typename T_Side1, typename T_Side2>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    DoGetCoord() const
  {
    return priv::DoGetCoord<real_type>(*this, T_Side1(0), T_Side2(0));
  }

  //------------------------------------------------------------------------
  // Explicit initialization

#define TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(_type_)\
  template class Rectangle_T<_type_>;\
  template Rectangle_T<_type_>::point_type \
  Rectangle_T<_type_>::DoGetCoord<Rectangle_T<_type_>::top, Rectangle_T<_type_>::left>() const;\
  template Rectangle_T<_type_>::point_type \
  Rectangle_T<_type_>::DoGetCoord<Rectangle_T<_type_>::top, Rectangle_T<_type_>::right>() const;\
  template Rectangle_T<_type_>::point_type \
  Rectangle_T<_type_>::DoGetCoord<Rectangle_T<_type_>::bottom, Rectangle_T<_type_>::left>() const;\
  template Rectangle_T<_type_>::point_type \
  Rectangle_T<_type_>::DoGetCoord<Rectangle_T<_type_>::bottom, Rectangle_T<_type_>::right>() const

  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f32);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f64);

};};};