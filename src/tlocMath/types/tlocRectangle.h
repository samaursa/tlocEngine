#ifndef _TLOC_MATH_TYPES_RECTANGLE_H_
#define _TLOC_MATH_TYPES_RECTANGLE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Rectangle
  {
  public:
    typedef tl_size                                 size_type;
    typedef T                                       real_type;
    typedef Rectangle<real_type>                    this_type;
    typedef Vector2<real_type>                      point_type;

    typedef core::types::StrongType_T<real_type, 0>   width;
    typedef core::types::StrongType_T<real_type, 1>   height;
    typedef core::types::StrongType_T<real_type, 2>   left;
    typedef core::types::StrongType_T<real_type, 3>   right;
    typedef core::types::StrongType_T<real_type, 4>   top;
    typedef core::types::StrongType_T<real_type, 5>   bottom;

    typedef core::types::StrongType_T<point_type, 0>  position;

  public:
    Rectangle();
    Rectangle(width a_w, height a_h,
              position a_pos = position(point_type(0)) );
    Rectangle(left a_l, right a_r, top a_t, bottom a_b);
    Rectangle(const this_type& a_other);

    bool operator == (const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    real_type   GetWidth() const;
    real_type   GetHeight() const;
    void        SetWidth(real_type a_value);
    void        SetHeight(real_type a_value);

    template <typename T_Side>
    real_type   GetValue() const;
    template <typename T_Side1, typename T_Side2>
    point_type  GetCoord() const;

    point_type  GetCoord_TopLeft() const;
    point_type  GetCoord_TopRight() const;
    point_type  GetCoord_BottomLeft() const;
    point_type  GetCoord_BottomRight() const;

    void        SetPosition(const point_type& a_centerPosition);
    void        ResetPosition();
    void        Offset(const point_type& a_offsetBy);
    point_type  GetPosition() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// If rectangle's left &gt;= right || top &lt;= bottom, rectangle is
    /// invalid.
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool        IsValid() const;

    bool        Contains(const point_type& a_xyPoint);
    bool        Intersects(const this_type& a_other) const;
    bool        Intersects(const this_type& a_other,
                           this_type& a_overlapOut) const;

  private:
    real_type   DoGetValue(tl_int a_index) const;
    template <typename T_Side1, typename T_Side2>
    point_type  DoGetCoord() const;

  private:
    point_type    m_extents;
    point_type    m_position;
  };

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T>
  template <typename T_Side>
  typename Rectangle<T>::real_type
    Rectangle<T>::GetValue() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side, left, right, top, bottom>();
    return DoGetValue(T_Side::k_index);
  }

  template <typename T>
  template <typename T_Side1, typename T_Side2>
  typename Rectangle<T>::point_type
    Rectangle<T>::GetCoord() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side1, top, bottom>();
    tloc::type_traits::AssertTypeIsSupported<T_Side2, left, right>();
    return DoGetCoord<T_Side1, T_Side2>();
  }

  //------------------------------------------------------------------------
  // Typedefs

  typedef Rectangle<tl_float>   Rectf;
  typedef Rectangle<f32>        Rectf32;
  typedef Rectangle<f64>        Rectf64;

};};};

#endif