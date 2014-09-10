#include "tlocRectangle.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocMath/tlocMath.inl.h>

#define TLOC_CHECK_RECTANGLE_EXTENTS(_left_, _right_, _top_, _bottom_)\
  TLOC_ASSERT_LOW_LEVEL( (_left <= _right) && (_bottom_ <= _top_),\
  "Rectangle extents are incorrect!");

namespace tloc { namespace math { namespace types {

  using core_ds::MakeTuple;

  typedef type_true                   IsFloat;
  typedef type_false                  IsNotFloat;

  namespace priv {

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real, typename T_PositionPolicy>
    typename Rectangle_TI<T_Real, T_PositionPolicy>::point_type
      DoGetCoord(const Rectangle_TI<T_Real, T_PositionPolicy>& a_rect,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::top,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::left)
    {
      typedef Rectangle_TI<T_Real, T_PositionPolicy>             rect_type;

      return MakeTuple(a_rect.template GetValue<typename rect_type::left>(),
                       a_rect.template GetValue<typename rect_type::top>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real, typename T_PositionPolicy>
    typename Rectangle_TI<T_Real, T_PositionPolicy>::point_type
      DoGetCoord(const Rectangle_TI<T_Real, T_PositionPolicy>& a_rect,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::top,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::right)
    {
      typedef Rectangle_TI<T_Real, T_PositionPolicy>             rect_type;

      return MakeTuple(a_rect.template GetValue<typename rect_type::right>(),
                       a_rect.template GetValue<typename rect_type::top>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real, typename T_PositionPolicy>
    typename Rectangle_TI<T_Real, T_PositionPolicy>::point_type
      DoGetCoord(const Rectangle_TI<T_Real, T_PositionPolicy>& a_rect,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::bottom,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::left)
    {
      typedef Rectangle_TI<T_Real, T_PositionPolicy>             rect_type;

      return MakeTuple(a_rect.template GetValue<typename rect_type::left>(),
                       a_rect.template GetValue<typename rect_type::bottom>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Real, typename T_PositionPolicy>
    typename Rectangle_TI<T_Real, T_PositionPolicy>::point_type
      DoGetCoord(const Rectangle_TI<T_Real, T_PositionPolicy>& a_rect,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::bottom,
                 typename Rectangle_TI<T_Real, T_PositionPolicy>::right)
    {
      typedef Rectangle_TI<T_Real, T_PositionPolicy>             rect_type;

      return MakeTuple(a_rect.template GetValue<typename rect_type::right>(),
                       a_rect.template GetValue<typename rect_type::bottom>());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    void
      AssertCenterPositionIsNotRounded(core_ds::Tuple<T, 2> a_dim, IsNotFloat)
    {
      TLOC_UNUSED(a_dim);
      TLOC_ASSERT_LOW_LEVEL(a_dim[0] % 2 == 0, "Center position will be rounded");
      TLOC_ASSERT_LOW_LEVEL(a_dim[1] % 2 == 0, "Center position will be rounded");
    }

    template <typename T>
    void
      AssertCenterPositionIsNotRounded(core_ds::Tuple<T, 2>, IsFloat)
    { /* Intentionally empty */ }

  };

  // ///////////////////////////////////////////////////////////////////////
  // RectangleBase_TI<BottomLeft>

#define TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP    typename T
#define TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS  T, p_rectangle::position::BottomLeft
#define TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TYPE    typename RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>::
    RectangleBase_TI()
    : m_dimensions(0)
    , m_position(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>::
    RectangleBase_TI(width a_w, height a_h, position a_pos)
    : m_dimensions( MakeTuple( a_w.m_value, a_h.m_value ) )
    , m_position(a_pos)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>::
    RectangleBase_TI(left a_l, right a_r, top a_t, bottom a_b)
    : m_dimensions( MakeTuple( a_r - a_l,
                               a_t - a_b ) )
    , m_position( MakeTuple( a_l.m_value, a_b.m_value) )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>::
    RectangleBase_TI(const point_type& a_start, const point_type& a_end)
    : m_dimensions( MakeTuple( a_end[0] - a_start[0],
                               a_end[1] - a_start[1] ) )
    , m_position( a_start )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP>
  TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TYPE::point_type
    RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>::
    GetCenter() const
  {
    point_type dim = GetDimensions();
    point_type pos = GetPosition();
    return MakeTuple(dim[0] / 2 + pos[0], dim[1] / 2 + pos[1]);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TEMP>
  TLOC_RECTANGLE_BASE_BOTTOM_LEFT_TYPE::value_type
    RectangleBase_TI<TLOC_RECTANGLE_BASE_BOTTOM_LEFT_PARAMS>::
    DoGetValue(tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL
      (a_index >= left::k_index && a_index <= bottom::k_index, "Out of bounds!");

    switch (a_index)
    {
    case left::k_index:
      return m_position[0];
    case right::k_index:
      return (m_dimensions[width::k_index] ) + m_position[0];
    case top::k_index:
      return (m_dimensions[height::k_index] ) + m_position[1];
    case bottom::k_index:
      return m_position[1];
    default:
      return 0;
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // RectangleBase_TI<Center>

#define TLOC_RECTANGLE_BASE_CENTER_TEMP    typename T
#define TLOC_RECTANGLE_BASE_CENTER_PARAMS  T, p_rectangle::position::Center
#define TLOC_RECTANGLE_BASE_CENTER_TYPE    typename RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_CENTER_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>::
    RectangleBase_TI()
    : m_dimensions(0)
    , m_position(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_CENTER_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>::
    RectangleBase_TI(width a_w, height a_h, position a_pos)
    : m_dimensions( MakeTuple( a_w.m_value, a_h.m_value ) )
    , m_position(a_pos)
  { 
    typedef Loki::Int2Type< Loki::TypeTraits<T>::isFloat> float_or_not;
    priv::AssertCenterPositionIsNotRounded(m_dimensions, float_or_not());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_CENTER_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>::
    RectangleBase_TI(left a_l, right a_r, top a_t, bottom a_b)
    : m_dimensions( MakeTuple( a_r - a_l,
                               a_t - a_b ) )
    , m_position( MakeTuple( (a_l + a_r) / 2,
                             (a_t + a_b) / 2 ) )
  { 
    typedef Loki::Int2Type< Loki::TypeTraits<T>::isFloat> float_or_not;
    priv::AssertCenterPositionIsNotRounded(m_dimensions, float_or_not());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_CENTER_TEMP>
  RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>::
    RectangleBase_TI(const point_type& a_start, const point_type& a_end)
    : m_dimensions( MakeTuple( a_end[0] - a_start[0],
                               a_end[1] - a_start[1] ) )
    , m_position( MakeTuple( (a_end[0] + a_start[0]) / 2,
                             (a_end[1] + a_start[1]) / 2 ) )
  { 
    typedef Loki::Int2Type< Loki::TypeTraits<T>::isFloat> float_or_not;
    priv::AssertCenterPositionIsNotRounded(m_dimensions, float_or_not());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_CENTER_TEMP>
  TLOC_RECTANGLE_BASE_CENTER_TYPE::point_type
    RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>::
    GetCenter() const
  {
    return GetPosition();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_BASE_CENTER_TEMP>
  TLOC_RECTANGLE_BASE_CENTER_TYPE::value_type
    RectangleBase_TI<TLOC_RECTANGLE_BASE_CENTER_PARAMS>::
    DoGetValue(tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL
      (a_index >= left::k_index && a_index <= bottom::k_index, "Out of bounds!");

    switch (a_index)
    {
    case left::k_index:
      return -(m_dimensions[width::k_index] / 2) + m_position[0];
    case right::k_index:
      return (m_dimensions[width::k_index] / 2) + m_position[0];
    case top::k_index:
      return (m_dimensions[height::k_index] / 2) + m_position[1];
    case bottom::k_index:
      return -(m_dimensions[height::k_index] / 2) + m_position[1];
    default:
      return 0;
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // Rectangle_TI<>

#define TLOC_RECTANGLE_TI_TEMP    typename T, typename T_PositionPolicy
#define TLOC_RECTANGLE_TI_PARAMS  T, T_PositionPolicy
#define TLOC_RECTANGLE_TI_TYPE    typename Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Rectangle_TI()
    : base_type()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Rectangle_TI(width a_w, height a_h, position a_pos)
    : base_type(a_w, a_h, a_pos)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Rectangle_TI(left a_l, right a_r, top a_t, bottom a_b)
    : base_type(a_l, a_r, a_t, a_b)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Rectangle_TI(const point_type& a_start, const point_type& a_end)
    : base_type(a_start, a_end)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    operator ==( const this_type& a_other ) const
  {
    return math::IsEqual(m_dimensions[0], a_other.m_dimensions[0]) && 
           math::IsEqual(m_dimensions[1], a_other.m_dimensions[1]) && 
           math::IsEqual(m_position[0], a_other.m_position[0]) && 
           math::IsEqual(m_position[1], a_other.m_position[1]);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::value_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetWidth() const
  { return m_dimensions[width::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::value_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetHeight() const
  { return m_dimensions[height::k_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::value_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetArea() const
  { return GetWidth() * GetHeight(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  void
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    SetWidth(value_type a_value)
  { m_dimensions[width::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  void
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    SetHeight(value_type a_value)
  { m_dimensions[height::k_index] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::point_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetCoord_TopLeft() const
  { return DoGetCoord<top, left>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::point_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetCoord_TopRight() const
  { return DoGetCoord<top, right>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::point_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetCoord_BottomLeft() const
  { return DoGetCoord<bottom, left>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::point_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    GetCoord_BottomRight() const
  { return DoGetCoord<bottom, right>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  void
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    ResetPosition()
  { m_position.Set(0); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  void
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    MakeOffset(const point_type& a_offsetBy)
  {
    m_position[0] += a_offsetBy[0];
    m_position[1] += a_offsetBy[1];
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  void
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    MakeFlip()
  {
    dim_type newDim = GetDimensions();
    core::swap(newDim[0], newDim[1]);

    this_type temp = 
      this_type(width(newDim[0]), height(newDim[1]), position(GetPosition()) );

    core::swap(*this, temp);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::this_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Offset(const point_type& a_offsetBy)
  {
    this_type temp(*this);
    temp.MakeOffset(a_offsetBy);
    return temp;
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  TLOC_RECTANGLE_TI_TYPE::this_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Flip()
  {
    this_type temp(*this);
    temp.MakeFlip();
    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    IsValid() const
  {
    return m_dimensions[width::k_index] > 0 &&
           m_dimensions[height::k_index] > 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Contains(const point_type &a_xyPoint)
  {
    return (a_xyPoint[0] >= GetValue<left>()    ) &&
           (a_xyPoint[0] <= GetValue<right>()   ) &&
           (a_xyPoint[1] <= GetValue<top>()     ) &&
           (a_xyPoint[1] >= GetValue<bottom>()  );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Contains(const this_type& a_other) const
  {
    if (Fits(a_other))
    {
      this_type overlap;
      Intersects(a_other, overlap);

      point_type otherDim   = a_other.GetDimensions();
      point_type overlapDim = overlap.GetDimensions();

      if ( math::IsEqual(otherDim[0], overlapDim[0]) &&
           math::IsEqual(otherDim[1], overlapDim[1]) )
      { return true; }
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Fits(const this_type& a_other) const
  {
    point_type dim      = GetDimensions();
    point_type otherDim = a_other.GetDimensions();

    return dim[0] >= otherDim[0] && dim[1] >= otherDim[1];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Intersects(const this_type& a_other) const
  {
    this_type temp;
    return Intersects(a_other, temp);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  bool
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    Intersects(const this_type& a_other, this_type& a_overlapOut) const
  {
    TLOC_ASSERT(IsValid(), "Intersects() may not work with invalid dimensions!");

    using namespace core;

    left    overL(tlMax(GetValue<left>()  , a_other.GetValue<left>()));
    right   overR(tlMin(GetValue<right>() , a_other.GetValue<right>()));
    top     overT(tlMin(GetValue<top>()   , a_other.GetValue<top>()));
    bottom  overB(tlMax(GetValue<bottom>(), a_other.GetValue<bottom>()));

    a_overlapOut = this_type(overL, overR, overT, overB);

    if (a_overlapOut.IsValid())
    { return true; }
    else
    { return false; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TI_TEMP>
  template <typename T_Side1, typename T_Side2>
  TLOC_RECTANGLE_TI_TYPE::point_type
    Rectangle_TI<TLOC_RECTANGLE_TI_PARAMS>::
    DoGetCoord() const
  {
    return priv::DoGetCoord<value_type>(*this, T_Side1(0), T_Side2(0));
  }

  // ///////////////////////////////////////////////////////////////////////
  // Rectangle_T<>

#define TLOC_RECTANGLE_TEMP   typename T, typename T_PositionPolicy
#define TLOC_RECTANGLE_PARAMS T, T_PositionPolicy
#define TLOC_RECTANGLE_TYPE   typename Rectangle_T<TLOC_RECTANGLE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T()
    : base_type()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T(width a_w, height a_h, position a_pos)
    : base_type(a_w, a_h, a_pos)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T(left a_l, right a_r, top a_t, bottom a_b)
    : base_type(a_l, a_r, a_t, a_b)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Rectangle_T(const point_type& a_start, const point_type& a_end)
    : base_type(a_start, a_end)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RECTANGLE_TEMP>
  bool
    Rectangle_T<TLOC_RECTANGLE_PARAMS>::
    Intersects(const ray_2d_type& a_ray) const
  {
    TLOC_ASSERT(IsValid(), "Intersects() may not work with invalid dimensions!");

    const point_type& rayOrigin = a_ray.GetOrigin();

    // Since we are a 2D box, we assume our direction is +Z
    if (rayOrigin[0] < base_type::template GetValue<left>() ||
        rayOrigin[0] > base_type::template GetValue<right>()  ||
        rayOrigin[1] < base_type::template GetValue<bottom>() ||
        rayOrigin[1] > base_type::template GetValue<top>() )
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

  //------------------------------------------------------------------------
  // Explicit initialization

#define TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE_TI(_type_, _positionPolicy_)\
  template class RectangleBase_TI<_type_, _positionPolicy_>;\
  template class Rectangle_TI<_type_, _positionPolicy_>;\
  template Rectangle_TI<_type_, _positionPolicy_>::point_type \
  Rectangle_TI<_type_, _positionPolicy_>::\
  DoGetCoord<Rectangle_TI<_type_, _positionPolicy_>::top,\
             Rectangle_TI<_type_, _positionPolicy_>::left>() const;\
  \
  template Rectangle_TI<_type_, _positionPolicy_>::point_type \
  Rectangle_TI<_type_, _positionPolicy_>::\
  DoGetCoord<Rectangle_TI<_type_, _positionPolicy_>::top,\
             Rectangle_TI<_type_, _positionPolicy_>::right>() const;\
  \
  template Rectangle_TI<_type_, _positionPolicy_>::point_type \
  Rectangle_TI<_type_, _positionPolicy_>::\
  DoGetCoord<Rectangle_TI<_type_, _positionPolicy_>::bottom,\
             Rectangle_TI<_type_, _positionPolicy_>::left>() const;\
  \
  template Rectangle_TI<_type_, _positionPolicy_>::point_type \
  Rectangle_TI<_type_, _positionPolicy_>::\
  DoGetCoord<Rectangle_TI<_type_, _positionPolicy_>::bottom,\
             Rectangle_TI<_type_, _positionPolicy_>::right>() const;

  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE_TI(s32, p_rectangle::position::BottomLeft);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE_TI(s64, p_rectangle::position::BottomLeft);

  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE_TI(s32, p_rectangle::position::Center);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE_TI(s64, p_rectangle::position::Center);

#define TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(_type_, _positionPolicy_)\
  template class Rectangle_T<_type_, _positionPolicy_>;\
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE_TI(_type_, _positionPolicy_)

  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f32, p_rectangle::position::BottomLeft);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f64, p_rectangle::position::BottomLeft);

  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f32, p_rectangle::position::Center);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f64, p_rectangle::position::Center);

};};};

#include <tlocCore/types/tlocStrongType.inl.h>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>

using namespace tloc::math_t;

// NOTE: Instatiating only for Bottom Left since Center has the same point_type
TLOC_INSTANTIATE_STRONG_TYPE(Rects32_bl::point_type);
TLOC_INSTANTIATE_STRONG_TYPE(Rects64_bl::point_type);

TLOC_INSTANTIATE_STRONG_TYPE(Rectf32_bl::point_type);
TLOC_INSTANTIATE_STRONG_TYPE(Rectf64_bl::point_type);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rects32_bl);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rects64_bl);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rects32_c);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rects64_c);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rectf32_bl);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rectf64_bl);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rectf32_c);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rectf64_c);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rects32_bl);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rects64_bl);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rects32_c);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rects64_c);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rectf32_bl);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rectf64_bl);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rectf32_c);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Rectf64_c);