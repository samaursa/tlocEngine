#include "tlocRectangle.h"

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/data_structures/tlocTuple.inl>

#define TLOC_CHECK_RECTANGLE_EXTENTS(_left_, _right_, _top_, _bottom_)\
  TLOC_ASSERT_LOW_LEVEL( (_left <= _right) && (_bottom_ <= _top_),\
  "Rectangle extents are incorrect!");

namespace tloc { namespace graphics { namespace types {

#define TLOC_RECTANGLE_TEMP typename T
#define TLOC_RECTANGLE_PARAMS T
#define TLOC_RECTANGLE_TYPE typename Rectangle<TLOC_RECTANGLE_PARAMS>

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>
    ::Rectangle(value_type a_left = 0, value_type a_right = 0,
                value_type a_top = 0, value_type a_bottom = 0)
  {
    m_extents[left]   = a_left;
    m_extents[right]  = a_right;
    m_extents[top]    = a_top;
    m_extents[bottom] = a_bottom;
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return m_extents == a_other.m_extents;
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::value_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::GetCoord(side_type a_side) const
  {
    return m_extents[a_side];
  }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>
    ::SetCoord(side_type a_side, value_type a_newCoord)
  {
    m_extents[a_side] = a_newCoord;
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::value_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::GetWidth() const
  {
    return m_extents[right] - m_extents[left];
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::value_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::GetHeight() const
  {
    return m_extents[top] - m_extents[bottom];
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::IsValid() const
  {
    return (m_extents[left] < m_extents[right] &&
            m_extents[top] > m_extents[bottom]);
  }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::Offset(const point_type& a_offsetBy)
  {
    m_extents[left]   += a_offsetBy[0];
    m_extents[right]  += a_offsetBy[0];
    m_extents[top]    += a_offsetBy[1];
    m_extents[bottom] += a_offsetBy[1];
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    Contains(const point_type &a_xyPoint)
  {
    return (a_xyPoint[0] >= m_extents[left]) &&
           (a_xyPoint[0] <= m_extents[right]) &&
           (a_xyPoint[1] <= m_extents[top]) &&
           (a_xyPoint[1] >= m_extents[bottom]);
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
    a_overlapOut =
      Rectangle( tlMax(m_extents[left],   a_other.GetCoord(left)),
                 tlMin(m_extents[right],  a_other.GetCoord(right)),
                 tlMin(m_extents[top],    a_other.GetCoord(top)),
                 tlMax(m_extents[bottom], a_other.GetCoord(bottom)) );

    if (a_overlapOut.IsValid())
    { return true; }
    else
    { return false; }
  }

  //------------------------------------------------------------------------
  // Explicit initialization

  template class Rectangle<s32>;
  template class Rectangle<s64>;

  template class Rectangle<f32>;
  template class Rectangle<f64>;
  template class Rectangle<f128>;

};};};