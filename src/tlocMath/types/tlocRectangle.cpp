#include "tlocRectangle.h"

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/data_structures/tlocTuple.inl>

#define TLOC_CHECK_RECTANGLE_EXTENTS(_left_, _right_, _top_, _bottom_)\
  TLOC_ASSERT_LOW_LEVEL( (_left <= _right) && (_bottom_ <= _top_),\
  "Rectangle extents are incorrect!");

namespace tloc { namespace math { namespace types {

  namespace priv {

    template <typename T_Real>
    typename Rectangle<T_Real>::point_type
      DoGetCoord(const Rectangle<T_Real>& a_rect,
                 typename Rectangle<T_Real>::top,
                 typename Rectangle<T_Real>::left)
    {
      typedef Rectangle<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::left>(),
                        a_rect.template GetValue<typename rect_type::top>());
    }

    template <typename T_Real>
    typename Rectangle<T_Real>::point_type
      DoGetCoord(const Rectangle<T_Real>& a_rect,
                 typename Rectangle<T_Real>::top,
                 typename Rectangle<T_Real>::right)
    {
      typedef Rectangle<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::right>(),
                        a_rect.template GetValue<typename rect_type::top>());
    }

    template <typename T_Real>
    typename Rectangle<T_Real>::point_type
      DoGetCoord(const Rectangle<T_Real>& a_rect,
                 typename Rectangle<T_Real>::bottom,
                 typename Rectangle<T_Real>::left)
    {
      typedef Rectangle<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::left>(),
                        a_rect.template GetValue<typename rect_type::bottom>());
    }

    template <typename T_Real>
    typename Rectangle<T_Real>::point_type
      DoGetCoord(const Rectangle<T_Real>& a_rect,
                 typename Rectangle<T_Real>::bottom,
                 typename Rectangle<T_Real>::right)
    {
      typedef Rectangle<T_Real>               rect_type;
      typedef typename rect_type::point_type  point_type;

      return point_type(a_rect.template GetValue<typename rect_type::right>(),
                        a_rect.template GetValue<typename rect_type::bottom>());
    }
  };

#define TLOC_RECTANGLE_TEMP typename T
#define TLOC_RECTANGLE_PARAMS T
#define TLOC_RECTANGLE_TYPE typename Rectangle<TLOC_RECTANGLE_PARAMS>

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>::
    Rectangle()
    : m_extents(0.0f, 0.0f)
    , m_position(0, 0)
  { }

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>::
    Rectangle(width a_w, height a_h, position a_pos)
    : m_extents(a_w, a_h)
    , m_position(a_pos)
  { }

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>::
    Rectangle(left a_l, right a_r, top a_t, bottom a_b)
    : m_extents( (a_r - a_l), (a_t - a_b) )
    , m_position( (a_l + a_r) * 0.5f, (a_t + a_b) * 0.5f )
  { }

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>::
    Rectangle(const this_type& a_other)
    : m_extents(a_other.m_extents)
    , m_position(a_other.m_position)
  { }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::this_type&
    Rectangle<TLOC_RECTANGLE_PARAMS>::operator= (const this_type& a_other)
  {
    m_extents = a_other.m_extents;
    m_position = a_other.m_position;
    return *this;
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return m_extents == a_other.m_extents && m_position == a_other.m_position;
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::real_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetWidth() const
  { return m_extents[width::k_index]; }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::real_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetHeight() const
  { return m_extents[height::k_index]; }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::
    SetWidth(real_type a_value)
  { m_extents[width::k_index] = a_value; }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::
    SetHeight(real_type a_value)
  { m_extents[height::k_index] = a_value; }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetCoord_TopLeft() const
  { return DoGetCoord<top, left>(); }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetCoord_TopRight() const
  { return DoGetCoord<top, right>(); }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetCoord_BottomLeft() const
  { return DoGetCoord<bottom, left>(); }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetCoord_BottomRight() const
  { return DoGetCoord<bottom, right>(); }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::
    SetPosition(const point_type& a_centerPosition)
  { m_position = a_centerPosition; }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::
    ResetPosition()
  { m_position.Set(0); }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::
    Offset(const point_type& a_offsetBy)
  { m_position += a_offsetBy; }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    Contains(const point_type &a_xyPoint)
  {
    return (a_xyPoint[0] >= GetValue<left>()    ) &&
           (a_xyPoint[0] <= GetValue<right>()   ) &&
           (a_xyPoint[1] <= GetValue<top>()     ) &&
           (a_xyPoint[1] >= GetValue<bottom>()  );
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetPosition() const
  { return m_position; }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    IsValid() const
  {
    return m_extents[width::k_index] > 0 &&
           m_extents[height::k_index] > 0;
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    Intersects(const this_type& a_other) const
  {
    Rectangle temp;
    return Intersects(a_other, temp);
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    Intersects(const this_type& a_other, this_type& a_overlapOut) const
  {
    using namespace core;

    left    overL(tlMax(GetValue<left>()  , a_other.GetValue<left>()));
    right   overR(tlMin(GetValue<right>() , a_other.GetValue<right>()));
    top     overT(tlMin(GetValue<top>()   , a_other.GetValue<top>()));
    bottom  overB(tlMax(GetValue<bottom>(), a_other.GetValue<bottom>()));

    a_overlapOut = Rectangle(overL, overR, overT, overB);

    if (a_overlapOut.IsValid())
    { return true; }
    else
    { return false; }
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::real_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    DoGetValue(tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL
      (a_index >= left::k_index && a_index <= bottom::k_index, "Out of bounds!");

    const real_type half = 0.5f;
    switch (a_index)
    {
    case left::k_index:
      return -(m_extents[width::k_index] * half) + m_position[0];
    case right::k_index:
      return (m_extents[width::k_index] * half) + m_position[0];
    case top::k_index:
      return (m_extents[height::k_index] * half) + m_position[1];
    case bottom::k_index:
      return -(m_extents[height::k_index] * half) + m_position[1];
    default:
      return 0;
    }
  }

  template <TLOC_RECTANGLE_TEMP>
  template <typename T_Side1, typename T_Side2>
  TLOC_RECTANGLE_TYPE::point_type Rectangle<TLOC_RECTANGLE_PARAMS>::
    DoGetCoord() const
  {
    return priv::DoGetCoord<real_type>(*this, T_Side1(0), T_Side2(0));
  }

  //------------------------------------------------------------------------
  // Explicit initialization

#define TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(_type_)\
  template class Rectangle<_type_>;\
  template Rectangle<_type_>::point_type \
  Rectangle<_type_>::DoGetCoord<Rectangle<_type_>::top, Rectangle<_type_>::left>() const;\
  template Rectangle<_type_>::point_type \
  Rectangle<_type_>::DoGetCoord<Rectangle<_type_>::top, Rectangle<_type_>::right>() const;\
  template Rectangle<_type_>::point_type \
  Rectangle<_type_>::DoGetCoord<Rectangle<_type_>::bottom, Rectangle<_type_>::left>() const;\
  template Rectangle<_type_>::point_type \
  Rectangle<_type_>::DoGetCoord<Rectangle<_type_>::bottom, Rectangle<_type_>::right>() const

  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f32);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f64);
  TLOC_EXPLICITLY_INSTANTIATE_RECTANGLE(f128);

};};};