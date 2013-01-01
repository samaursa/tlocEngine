#include "tlocRectangle.h"

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/data_structures/tlocTuple.inl>

#define TLOC_CHECK_RECTANGLE_EXTENTS(_left_, _right_, _top_, _bottom_)\
  TLOC_ASSERT_LOW_LEVEL( (_left <= _right) && (_bottom_ <= _top_),\
  "Rectangle extents are incorrect!");

namespace tloc { namespace math { namespace types {

#define TLOC_RECTANGLE_TEMP typename T
#define TLOC_RECTANGLE_PARAMS T
#define TLOC_RECTANGLE_TYPE typename Rectangle<TLOC_RECTANGLE_PARAMS>

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>
    ::Rectangle(half_width a_w, half_height a_h)
  {
    m_extents[left::k_index]   = -a_w;
    m_extents[right::k_index]  = a_w;

    m_extents[top::k_index]    = a_h;
    m_extents[bottom::k_index] = -a_h;
  }

  template <TLOC_RECTANGLE_TEMP>
  Rectangle<TLOC_RECTANGLE_PARAMS>
    ::Rectangle(left a_l, right a_r, top a_t, bottom a_b)
  {
    m_extents[left::k_index]   = a_l;
    m_extents[right::k_index]  = a_r;
    m_extents[top::k_index]    = a_t;
    m_extents[bottom::k_index] = a_b;
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return m_extents == a_other.m_extents;
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::value_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::GetWidth() const
  {
    return m_extents[right::k_index] - m_extents[left::k_index];
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::value_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::GetHeight() const
  {
    return m_extents[top::k_index] - m_extents[bottom::k_index];
  }

  template <TLOC_RECTANGLE_TEMP>
  TLOC_RECTANGLE_TYPE::point_type
    Rectangle<TLOC_RECTANGLE_PARAMS>::
    GetCenter() const
  {
    point_type center;
    center[0] = (m_extents[left::k_index] + m_extents[right::k_index]) / 2;
    center[1] = (m_extents[top::k_index] + m_extents[bottom::k_index]) / 2;

    return center;
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::IsValid() const
  {
    return (m_extents[left::k_index] < m_extents[right::k_index] &&
            m_extents[top::k_index] > m_extents[bottom::k_index]);
  }

  template <TLOC_RECTANGLE_TEMP>
  void Rectangle<TLOC_RECTANGLE_PARAMS>::Offset(const point_type& a_offsetBy)
  {
    m_extents[left::k_index]   += a_offsetBy[0];
    m_extents[right::k_index]  += a_offsetBy[0];
    m_extents[top::k_index]    += a_offsetBy[1];
    m_extents[bottom::k_index] += a_offsetBy[1];
  }

  template <TLOC_RECTANGLE_TEMP>
  bool Rectangle<TLOC_RECTANGLE_PARAMS>::
    Contains(const point_type &a_xyPoint)
  {
    return (a_xyPoint[0] >= m_extents[left::k_index]) &&
           (a_xyPoint[0] <= m_extents[right::k_index]) &&
           (a_xyPoint[1] <= m_extents[top::k_index]) &&
           (a_xyPoint[1] >= m_extents[bottom::k_index]);
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

    left    overL(tlMax(m_extents[left::k_index],  a_other.GetCoord<left>()));
    right   overR(tlMin(m_extents[right::k_index], a_other.GetCoord<right>()));
    top     overT(tlMin(m_extents[top::k_index],   a_other.GetCoord<top>()));
    bottom  overB(tlMax(m_extents[bottom::k_index],a_other.GetCoord<bottom>()));

    a_overlapOut = Rectangle(overL, overR, overT, overB);

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