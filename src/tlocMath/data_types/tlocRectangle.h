#ifndef _TLOC_MATH_TYPES_RECTANGLE_H_
#define _TLOC_MATH_TYPES_RECTANGLE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Rectangle
  {
  public:
    typedef tl_size                                  size_type;
    typedef T                                        value_type;
    typedef Rectangle<value_type>                    this_type;
    typedef core::Tuple<value_type, 2>               point_type;

    typedef core::types::StrongType_T<value_type, 0> left;
    typedef core::types::StrongType_T<value_type, 1> right;
    typedef core::types::StrongType_T<value_type, 2> top;
    typedef core::types::StrongType_T<value_type, 3> bottom;
    typedef core::types::StrongType_T<value_type, 4> half_width;
    typedef core::types::StrongType_T<value_type, 5> half_height;

  public:
    Rectangle(half_width a_w = half_width(0), half_height a_h = half_height(0));
    Rectangle(left a_l, right a_r, top a_t, bottom a_b);

    bool operator == (const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    template <typename T_Side>
    value_type  GetCoord() const;
    template <typename T_Side>
    void        SetCoord(value_type a_newCoord);

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

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T>
  template <typename T_Side>
  typename Rectangle<T>::value_type
    Rectangle<T>::GetCoord() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side, left, right, top, bottom>();
    return m_extents[T_Side::k_index];
  }

  template <typename T>
  template <typename T_Side>
  void Rectangle<T>::SetCoord(value_type a_newCoord)
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side, left, right, top, bottom>();
    m_extents[T_Side::k_index] = a_newCoord;
  }

  //------------------------------------------------------------------------
  // Typedefs

  typedef Rectangle<tl_int>     Recti;
  typedef Rectangle<s32>        Recti32;
  typedef Rectangle<s64>        Recti64;

  typedef Rectangle<tl_float>   Rectf;
  typedef Rectangle<f32>        Rectf32;
  typedef Rectangle<f64>        Rectf64;

};};};

#endif