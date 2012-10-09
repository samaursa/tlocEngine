#ifndef TLOC_GRAPHICS_TYPES_RECTANGLE_H
#define TLOC_GRAPHICS_TYPES_RECTANGLE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace types {

  template <typename T>
  class Rectangle
  {
  public:
    typedef tl_size                     size_type;
    typedef T                           value_type;
    typedef Rectangle<value_type>       this_type;
    typedef core::Tuple<value_type, 2>  point_type;

  public:
    enum { left = 0, right, top, bottom }; typedef size_type  side_type;

  public:
    Rectangle(value_type a_halfWidth, value_type a_halfHeight);
    Rectangle(value_type a_left = 0, value_type a_right = 0,
              value_type a_top = 0, value_type a_bottom = 0);

    bool operator == (const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    value_type  GetCoord(side_type a_side) const;
    void        SetCoord(side_type a_side, value_type a_newCoord);

    ///-------------------------------------------------------------------------
    /// @brief May return a negative width if rectangle is invalid
    ///-------------------------------------------------------------------------
    value_type  GetWidth() const;

    ///-------------------------------------------------------------------------
    /// @brief May return a negative height if rectangle is invalid
    ///-------------------------------------------------------------------------
    value_type  GetHeight() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// If rectangle's left &gt;= right || top &lt;= bottom, rectangle is
    /// invalid.
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool        IsValid() const;

    void        Offset(const point_type& a_offsetBy);
    bool        Contains(const point_type& a_xyPoint);
    bool        Intersects(const this_type& a_other) const;
    bool        Intersects(const this_type& a_other,
                           this_type& a_overlapOut) const;

  private:
    typedef core::Tuple<value_type, 4>  extents_type;

  private:
    extents_type  m_extents;
  };

  typedef Rectangle<tl_int>     RectangleInt;
  typedef Rectangle<tl_float>   RectangleFloat;

};};};

#endif