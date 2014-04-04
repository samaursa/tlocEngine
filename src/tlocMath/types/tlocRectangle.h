#ifndef _TLOC_MATH_TYPES_RECTANGLE_H_
#define _TLOC_MATH_TYPES_RECTANGLE_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocRay.h>

namespace tloc { namespace math { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Rectangle_TI<T>

  template <typename T>
  class Rectangle_TI
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef tl_size                                 size_type;
    typedef T                                       real_type;
    typedef Rectangle_TI<real_type>                 this_type;
    typedef core_ds::Tuple<real_type, 2>            point_type;

    typedef core::types::StrongType_T<real_type, 0>   width;
    typedef core::types::StrongType_T<real_type, 1>   height;
    typedef core::types::StrongType_T<real_type, 2>   left;
    typedef core::types::StrongType_T<real_type, 3>   right;
    typedef core::types::StrongType_T<real_type, 4>   top;
    typedef core::types::StrongType_T<real_type, 5>   bottom;

    typedef core::types::StrongType_T<point_type, 0>  position;

  public:
    Rectangle_TI();
    Rectangle_TI( width a_w, height a_h,
                  position a_pos = position( point_type( 0 ) ) );
    Rectangle_TI(left a_l, right a_r, top a_t, bottom a_b);
    Rectangle_TI(const point_type& a_start, const point_type& a_end);

    template <typename T_Real>
    Rectangle_TI(const Rectangle_TI<T_Real>& a_other);

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

    void        SetPosition(const point_type& a_bottomLeftCoord);
    void        ResetPosition();
    void        Offset(const point_type& a_offsetBy);
    point_type  GetPosition() const;

    TLOC_DECL_AND_DEF_GETTER(point_type, GetDimensions, m_dimensions);

    ///-------------------------------------------------------------------------
    /// @brief
    /// If rectangle's left &gt;= right || top &lt;= bottom, rectangle is
    /// invalid.
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool        IsValid() const;

    bool        Contains(const point_type& a_xyPoint);

  private:
    real_type   DoGetValue(tl_int a_index) const;
    template <typename T_Side1, typename T_Side2>
    point_type  DoGetCoord() const;

  private:
    point_type    m_dimensions;
    point_type    m_position;
  };


  //------------------------------------------------------------------------
  // Template definitions Rectangle_TI<>

  template <typename T>
  template <typename T_Real>
  Rectangle_TI<T>::
    Rectangle_TI(const Rectangle_TI<T_Real>& a_other)
    : m_dimensions(a_other.GetDimensions())
    , m_position(a_other.GetPosition())
  { }

  template <typename T>
  template <typename T_Side>
  typename Rectangle_TI<T>::real_type
    Rectangle_TI<T>::GetValue() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side, left, right, top, bottom>();
    return DoGetValue(T_Side::k_index);
  }

  template <typename T>
  template <typename T_Side1, typename T_Side2>
  typename Rectangle_TI<T>::point_type
    Rectangle_TI<T>::GetCoord() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side1, top, bottom>();
    tloc::type_traits::AssertTypeIsSupported<T_Side2, left, right>();
    return DoGetCoord<T_Side1, T_Side2>();
  }

  // ///////////////////////////////////////////////////////////////////////
  // Rectangle_T<T>

  template <typename T>
  class Rectangle_T
    : public Rectangle_TI<T>
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef T                                       value_type;
    typedef value_type                              real_type;
    typedef Rectangle_T<real_type>                  this_type;
    typedef Rectangle_TI<value_type>                base_type;

    typedef typename base_type::size_type           size_type;

    typedef typename base_type::width               width;
    typedef typename base_type::height              height;
    typedef typename base_type::left                left;
    typedef typename base_type::right               right;
    typedef typename base_type::top                 top;
    typedef typename base_type::bottom              bottom;
    typedef typename base_type::position            position;

    typedef Vector2<real_type>                      point_type;
    typedef Ray_T<real_type, 2>                     ray_2d_type;
    typedef Ray_T<real_type, 3>                     ray_3d_type;

    typedef core::Pair<bool,
      typename ray_3d_type::vec_type>               intersect_ret_type;

    typedef math_t::Vector3<real_type>              dir_vec_type;

    typedef core_t::StrongType_T<bool, 0>      from_origin;
    typedef core_t::StrongType_T<bool, 1>      double_sided;
    typedef core_t::StrongType_T<bool, 2>      make_center_origin;

  public:
    Rectangle_T();
    Rectangle_T(width a_w, height a_h,
                position a_pos = position(point_type(0)),
                make_center_origin = make_center_origin(false));
    Rectangle_T(left a_l, right a_r, top a_t, bottom a_b,
                make_center_origin = make_center_origin(false));
    Rectangle_T(const point_type& a_start, const point_type& a_end,
                make_center_origin = make_center_origin(false));

    template <typename T_Real>
    Rectangle_T(const Rectangle_T<T_Real>& a_other);

    using base_type::operator==;
    using base_type::operator!=;

    using base_type::GetWidth;
    using base_type::GetHeight;
    using base_type::SetWidth;
    using base_type::SetHeight;

    using base_type::GetValue;
    using base_type::GetCoord;

    using base_type::GetCoord_TopLeft;
    using base_type::GetCoord_TopRight;
    using base_type::GetCoord_BottomLeft;
    using base_type::GetCoord_BottomRight;

    using base_type::SetPosition;
    using base_type::ResetPosition;
    using base_type::Offset;
    using base_type::GetPosition;

    void        MakeOriginCenter();
    point_type  GetCenter() const;

    using base_type::GetDimensions;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(dir_vec_type, GetNormal, s_normal);

    using base_type::IsValid;
    using base_type::Contains;

    bool        Intersects(const this_type& a_other) const;
    bool        Intersects(const this_type& a_other,
                           this_type& a_overlapOut) const;
    bool        Intersects(const ray_2d_type& a_ray) const;
    intersect_ret_type
                Intersects(const ray_3d_type& a_ray,
                           from_origin a_fo = from_origin(true),
                           double_sided a_ds = double_sided(false) ) const;

  private:
    static const dir_vec_type s_normal;
  };

  template <typename T>
  typename Rectangle_T<T>::dir_vec_type
    const Rectangle_T<T>::s_normal = typename Rectangle_T<T>::
    dir_vec_type(core_ds::Variadic<T, 3>(0, 0, 1));

  //------------------------------------------------------------------------
  // Template definitions Rectangle_T<>

  template <typename T>
  template <typename T_Real>
  Rectangle_T<T>::
    Rectangle_T(const Rectangle_T<T_Real>& a_other)
    : base_type(a_other)
  { }

  //------------------------------------------------------------------------
  // Typedefs

  typedef Rectangle_TI<tl_int>    Rects;
  typedef Rectangle_TI<s32>       Rects32;
  typedef Rectangle_TI<s64>       Rects64;

  typedef Rectangle_T<tl_float>   Rectf;
  typedef Rectangle_T<f32>        Rectf32;
  typedef Rectangle_T<f64>        Rectf64;

};};};

#endif