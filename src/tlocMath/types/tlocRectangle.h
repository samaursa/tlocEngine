#ifndef _TLOC_MATH_TYPES_RECTANGLE_H_
#define _TLOC_MATH_TYPES_RECTANGLE_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocRay.h>

namespace tloc { namespace math { namespace types {

  namespace p_rectangle
  {
    namespace position
    {
      struct Center       {};
      struct BottomLeft   {};
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // RectangleBase_TI<position::BottomLeft>

  template <typename T, typename T_PositionPolicy>
  class RectangleBase_TI;

  // -----------------------------------------------------------------------
  // RectangleBase_TI<BottomLeft>

  template <typename T>
  class RectangleBase_TI<T, p_rectangle::position::BottomLeft>
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef tl_size                                     size_type;
    typedef T                                           value_type;
    typedef p_rectangle::position::BottomLeft           position_policy;
    typedef RectangleBase_TI<value_type,
                             position_policy>           this_type;

    typedef core_ds::Tuple<value_type, 2>               point_type;
    typedef point_type                                  dim_type;

    typedef core::types::StrongType_T<value_type, 0>    width;
    typedef core::types::StrongType_T<value_type, 1>    height;
    typedef core::types::StrongType_T<value_type, 2>    left;
    typedef core::types::StrongType_T<value_type, 3>    right;
    typedef core::types::StrongType_T<value_type, 4>    top;
    typedef core::types::StrongType_T<value_type, 5>    bottom;

    typedef core::types::StrongType_T<point_type, 0>    position;

  protected:
    RectangleBase_TI();
    RectangleBase_TI( width a_w, height a_h,
                      position a_pos = position( point_type( 0 ) ) );
    RectangleBase_TI(left a_l, right a_r, top a_t, bottom a_b);
    RectangleBase_TI(const point_type& a_start, const point_type& a_end);

    point_type  GetCenter() const;

    TLOC_DECL_AND_DEF_GETTER(point_type, GetPosition, m_position);
    TLOC_DECL_AND_DEF_GETTER(dim_type, GetDimensions, m_dimensions);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(point_type, SetPosition, m_position);

  protected:
    value_type   DoGetValue(tl_int a_index) const;

  protected:
    dim_type      m_dimensions;
    point_type    m_position;
  };

  // -----------------------------------------------------------------------
  // RectangleBase_TI<Center>

  template <typename T>
  class RectangleBase_TI<T, p_rectangle::position::Center>
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef tl_size                                     size_type;
    typedef T                                           value_type;
    typedef p_rectangle::position::Center               position_policy;
    typedef RectangleBase_TI<value_type,
                             position_policy>           this_type;

    typedef core_ds::Tuple<value_type, 2>               point_type;
    typedef point_type                                  dim_type;

    typedef core::types::StrongType_T<value_type, 0>    width;
    typedef core::types::StrongType_T<value_type, 1>    height;
    typedef core::types::StrongType_T<value_type, 2>    left;
    typedef core::types::StrongType_T<value_type, 3>    right;
    typedef core::types::StrongType_T<value_type, 4>    top;
    typedef core::types::StrongType_T<value_type, 5>    bottom;

    typedef core::types::StrongType_T<point_type, 0>    position;

  protected:
    RectangleBase_TI();
    RectangleBase_TI( width a_w, height a_h,
                      position a_pos = position( point_type( 0 ) ) );
    RectangleBase_TI(left a_l, right a_r, top a_t, bottom a_b);
    RectangleBase_TI(const point_type& a_start, const point_type& a_end);

    point_type  GetCenter() const;

    TLOC_DECL_AND_DEF_GETTER(point_type, GetPosition, m_position);
    TLOC_DECL_AND_DEF_GETTER(dim_type, GetDimensions, m_dimensions);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(point_type, SetPosition, m_position);

  protected:
    value_type   DoGetValue(tl_int a_index) const;

  protected:
    dim_type      m_dimensions;
    point_type    m_position;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Rectangle_TI<T>

  template <typename T, typename T_PositionPolicy>
  class Rectangle_TI
    : public RectangleBase_TI<T, T_PositionPolicy>
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef tl_size                                 size_type;
    typedef T                                       value_type;
    typedef T_PositionPolicy                        position_policy;
    typedef Rectangle_TI<value_type,
                         position_policy>           this_type;
    typedef RectangleBase_TI<value_type,
                             position_policy>       base_type;

    typedef core_ds::Tuple<value_type, 2>           point_type;

    typedef core::types::StrongType_T<value_type, 0>    width;
    typedef core::types::StrongType_T<value_type, 1>    height;
    typedef core::types::StrongType_T<value_type, 2>    left;
    typedef core::types::StrongType_T<value_type, 3>    right;
    typedef core::types::StrongType_T<value_type, 4>    top;
    typedef core::types::StrongType_T<value_type, 5>    bottom;

    typedef core::types::StrongType_T<point_type, 0>    position;

  public:
    Rectangle_TI();
    Rectangle_TI( width a_w, height a_h,
                  position a_pos = position( point_type( 0 ) ) );
    Rectangle_TI(left a_l, right a_r, top a_t, bottom a_b);
    Rectangle_TI(const point_type& a_start, const point_type& a_end);

    template <typename U, typename U_PositionPolicy>
    Rectangle_TI(const Rectangle_TI<U, U_PositionPolicy>& a_other);

    bool operator == (const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    value_type  GetWidth() const;
    value_type  GetHeight() const;
    value_type  GetArea() const;
    void        SetWidth(value_type a_value);
    void        SetHeight(value_type a_value);

    template <typename T_Side>
    value_type  GetValue() const;
    template <typename T_Side1, typename T_Side2>
    point_type  GetCoord() const;

    point_type  GetCoord_TopLeft() const;
    point_type  GetCoord_TopRight() const;
    point_type  GetCoord_BottomLeft() const;
    point_type  GetCoord_BottomRight() const;

    void        ResetPosition();

    void        MakeOffset(const point_type& a_offsetBy);
    void        MakeFlip();

    this_type   Offset(const point_type& a_offsetBy);
    this_type   Flip();

    using base_type::GetCenter;
    using base_type::GetPosition;
    using base_type::SetPosition;
    using base_type::GetDimensions;

    ///-------------------------------------------------------------------------
    /// @brief
    /// If rectangle's left &gt;= right || top &lt;= bottom, rectangle is
    /// invalid.
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool        IsValid() const;

    bool        Contains(const point_type& a_xyPoint);
    bool        Contains(const this_type& a_other) const;
    bool        Fits(const this_type& a_other) const;

    bool        Intersects(const this_type& a_other) const;
    bool        Intersects(const this_type& a_other,
                           this_type& a_overlapOut) const;

  private:
    using base_type::DoGetValue;

    template <typename T_Side1, typename T_Side2>
    point_type  DoGetCoord() const;
  };

  //------------------------------------------------------------------------
  // Template definitions Rectangle_TI<>

  template <typename T, typename T_PositionPolicy>
  template <typename U, typename U_PositionPolicy>
  Rectangle_TI<T, T_PositionPolicy>::
    Rectangle_TI(const Rectangle_TI<U, U_PositionPolicy>& a_other)
    : base_type( left( a_other.GetValue<typename Rectangle_TI<U, U_PositionPolicy>::left>() ), 
                 right( a_other.GetValue<typename Rectangle_TI<U, U_PositionPolicy>::right>() ),
                 top( a_other.GetValue<typename Rectangle_TI<U, U_PositionPolicy>::top>() ), 
                 bottom( a_other.GetValue<typename Rectangle_TI<U, U_PositionPolicy>::bottom>() ) )
  { }

  template <typename T, typename T_PositionPolicy>
  template <typename T_Side>
  typename Rectangle_TI<T, T_PositionPolicy>::value_type
    Rectangle_TI<T, T_PositionPolicy>::GetValue() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side, left, right, top, bottom>();
    return DoGetValue(T_Side::k_index);
  }

  template <typename T, typename T_PositionPolicy>
  template <typename T_Side1, typename T_Side2>
  typename Rectangle_TI<T, T_PositionPolicy>::point_type
    Rectangle_TI<T, T_PositionPolicy>::GetCoord() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side1, top, bottom>();
    tloc::type_traits::AssertTypeIsSupported<T_Side2, left, right>();
    return DoGetCoord<T_Side1, T_Side2>();
  }

  // ///////////////////////////////////////////////////////////////////////
  // Rectangle_T<T>

  template <typename T, typename T_PositionPolicy>
  class Rectangle_T
    : public Rectangle_TI<T, T_PositionPolicy>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    typedef T                                         value_type;
    typedef value_type                                real_type;
    typedef T_PositionPolicy                          position_policy;
    typedef Rectangle_T<real_type, position_policy>   this_type;
    typedef Rectangle_TI<real_type, position_policy>  base_type;

    typedef typename base_type::size_type           size_type;

    typedef typename base_type::width               width;
    typedef typename base_type::height              height;
    typedef typename base_type::left                left;
    typedef typename base_type::right               right;
    typedef typename base_type::top                 top;
    typedef typename base_type::bottom              bottom;
    typedef typename base_type::position            position;
    typedef typename base_type::point_type          point_type;

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
    Rectangle_T( width a_w, height a_h,
                 position a_pos = position( point_type(0) ) );
    Rectangle_T( left a_l, right a_r, top a_t, bottom a_b );
    Rectangle_T( const point_type& a_start, const point_type& a_end );

    template <typename U, typename U_PositionPolicy>
    Rectangle_T(const Rectangle_T<U, U_PositionPolicy>& a_other);

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

    using base_type::GetCenter;
    using base_type::SetPosition;
    using base_type::ResetPosition;
    using base_type::Offset;
    using base_type::GetPosition;

    using base_type::GetDimensions;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(dir_vec_type, GetNormal, s_normal);

    using base_type::IsValid;
    using base_type::Contains;
    using base_type::Intersects;

    bool        Intersects(const ray_2d_type& a_ray) const;
    intersect_ret_type
                Intersects(const ray_3d_type& a_ray,
                           from_origin a_fo = from_origin(true),
                           double_sided a_ds = double_sided(false) ) const;

  private:
    static const dir_vec_type s_normal;
  };

  template <typename T, typename T_PositionPolicy>
  typename Rectangle_T<T, T_PositionPolicy>::dir_vec_type
    const Rectangle_T<T, T_PositionPolicy>::s_normal =
    typename Rectangle_T<T, T_PositionPolicy>::
    dir_vec_type(core_ds::Variadic<T, 3>(0, 0, 1));

  //------------------------------------------------------------------------
  // Template definitions Rectangle_T<>

  template <typename T, typename T_PositionPolicy>
  template <typename U, typename U_PositionPolicy>
  Rectangle_T<T, T_PositionPolicy>::
    Rectangle_T(const Rectangle_T<U, U_PositionPolicy>& a_other)
    : base_type(a_other)
  { }

  //------------------------------------------------------------------------
  // Typedefs

  typedef Rectangle_TI<tl_int, p_rectangle::position::BottomLeft>   Rects_bl;
  typedef Rectangle_TI<s32, p_rectangle::position::BottomLeft>      Rects32_bl;
  typedef Rectangle_TI<s64, p_rectangle::position::BottomLeft>      Rects64_bl;

  typedef Rectangle_TI<tl_int, p_rectangle::position::Center>       Rects_c;
  typedef Rectangle_TI<s32, p_rectangle::position::Center>          Rects32_c;
  typedef Rectangle_TI<s64, p_rectangle::position::Center>          Rects64_c;

  typedef Rectangle_T<tl_float, p_rectangle::position::BottomLeft>  Rectf_bl;
  typedef Rectangle_T<f32, p_rectangle::position::BottomLeft>       Rectf32_bl;
  typedef Rectangle_T<f64, p_rectangle::position::BottomLeft>       Rectf64_bl;

  typedef Rectangle_T<tl_float, p_rectangle::position::Center>      Rectf_c;
  typedef Rectangle_T<f32, p_rectangle::position::Center>           Rectf32_c;
  typedef Rectangle_T<f64, p_rectangle::position::Center>           Rectf64_c;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Rects_bl, rects_bl);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rects32_bl, rects32_bl);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rects64_bl, rects64_bl);

  TLOC_TYPEDEF_ALL_SMART_PTRS(Rects_c, rects_c);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rects32_c, rects32_c);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rects64_c, rects64_c);

  TLOC_TYPEDEF_ALL_SMART_PTRS(Rectf_bl, rectf_bl);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rectf32_bl, rectf32_bl);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rectf64_bl, rectf64_bl);

  TLOC_TYPEDEF_ALL_SMART_PTRS(Rectf_c, rectf_c);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rectf32_c, rectf32_c);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rectf64_c, rectf64_c);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rects_bl, rects_bl);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rects32_bl, rects32_bl);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rects64_bl, rects64_bl);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rects_c, rects_c);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rects32_c, rects32_c);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rects64_c, rects64_c);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rectf_bl, rectf_bl);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rectf32_bl, rectf32_bl);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rectf64_bl, rectf64_bl);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rectf_c, rectf_c);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rectf32_c, rectf32_c);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Rectf64_c, rectf64_c);

  // -----------------------------------------------------------------------
  // algorithms

  namespace algos { namespace rectangle { 

    namespace compare {

      struct Equal        {};
      struct Less         {};
      struct LessEqual    {};
      struct Greater      {};
      struct GreaterEqual {};

      // ///////////////////////////////////////////////////////////////////////
      // Width

      template <typename T_Comparison>
      struct WidthBinary
      {
        typedef T_Comparison                                  comparison;

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Equal)
        { return math::IsEqual(a.GetWidth(), b.GetWidth()); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Less)
        { return a.GetWidth() < b.GetWidth(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Greater)
        { return a.GetWidth() < b.GetWidth(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, LessEqual)
        { return a.GetWidth() <= b.GetWidth(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, GreaterEqual)
        { return a.GetWidth() >= b.GetWidth(); }

        template <typename T, typename U>
        bool operator()(const T& a, const U& b)
        { return Is(a, b, comparison()); }
      };

      template <typename T, typename T_PositionPolicy, typename T_Comparison>
      struct Width
      {
        typedef math_t::Rectangle_TI<T, T_PositionPolicy>     value_type;
        typedef T_Comparison                                  comparison;

        Width(const value_type& a_rect)
          : m_rect(&a_rect)
        { }

        bool Is(const value_type& a_other, Equal)
        { return math::IsEqual(m_rect->GetWidth(), a_other.GetWidth()); }

        bool Is(const value_type& a_other, Less)
        { return m_rect->GetWidth() < a_other.GetWidth(); }

        bool Is(const value_type& a_other, Greater)
        { return m_rect->GetWidth() > a_other.GetWidth(); }

        bool Is(const value_type& a_other, LessEqual)
        { return m_rect->GetWidth() <= a_other.GetWidth(); }

        bool Is(const value_type& a_other, GreaterEqual)
        { return m_rect->GetWidth() >= a_other.GetWidth(); }

        bool operator()(const value_type& a_other)
        { return Is(a_other, comparison()); }

        const value_type* m_rect;
      };

      template <typename T, typename T_PositionPolicy, typename T_Comparison>
      Width<T, T_PositionPolicy, T_Comparison>
        MakeWidth(const math_t::Rectangle_TI<T, T_PositionPolicy>& a_rect, 
                  T_Comparison)
      { 
        type_traits::AssertTypeIsSupported<T_Comparison, 
          Equal, Less, Greater, LessEqual, GreaterEqual>();
        return Width<T, T_PositionPolicy, T_Comparison>(a_rect);
      }

      // ///////////////////////////////////////////////////////////////////////
      // Height

      template <typename T_Comparison>
      struct HeightBinary
      {
        typedef T_Comparison                                  comparison;

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Equal)
        { return math::IsEqual(a.GetHeight(), b.GetHeight()); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Less)
        { return a.GetHeight() < b.GetHeight(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Greater)
        { return a.GetHeight() < b.GetHeight(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, LessEqual)
        { return a.GetHeight() <= b.GetHeight(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, GreaterEqual)
        { return a.GetHeight() >= b.GetHeight(); }

        template <typename T, typename U>
        bool operator()(const T& a, const U& b)
        { return Is(a, b, comparison()); }
      };

      template <typename T, typename T_PositionPolicy, typename T_Comparison>
      struct Height
      {
        typedef math_t::Rectangle_TI<T, T_PositionPolicy>     value_type;
        typedef T_Comparison                                  comparison;

        Height(const value_type& a_rect)
          : m_rect(&a_rect)
        { }

        bool Is(const value_type& a_other, Equal)
        { return math::IsEqual(m_rect->GetHeight(), a_other.GetHeight()); }

        bool Is(const value_type& a_other, Less)
        { return m_rect->GetHeight() < a_other.GetHeight(); }

        bool Is(const value_type& a_other, Greater)
        { return m_rect->GetHeight() > a_other.GetHeight(); }

        bool Is(const value_type& a_other, LessEqual)
        { return m_rect->GetHeight() <= a_other.GetHeight(); }

        bool Is(const value_type& a_other, GreaterEqual)
        { return m_rect->GetHeight() >= a_other.GetHeight(); }

        bool operator()(const value_type& a_other)
        { return Is(a_other, comparison()); }

        const value_type* m_rect;
      };

      template <typename T, typename T_PositionPolicy, typename T_Comparison>
      Height<T, T_PositionPolicy, T_Comparison>
        MakeHeight(const math_t::Rectangle_TI<T, T_PositionPolicy>& a_rect, 
                   T_Comparison)
      { 
        type_traits::AssertTypeIsSupported<T_Comparison, 
          Equal, Less, Greater, LessEqual, GreaterEqual>();
        return Height<T, T_PositionPolicy, T_Comparison>(a_rect);
      }

      // ///////////////////////////////////////////////////////////////////////
      // Area

      template <typename T_Comparison>
      struct AreaBinary
      {
        typedef T_Comparison                                  comparison;

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Equal)
        { return math::IsEqual(a.GetArea(), b.GetArea()); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Less)
        { return a.GetArea() < b.GetArea(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, Greater)
        { return a.GetArea() < b.GetArea(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, LessEqual)
        { return a.GetArea() <= b.GetArea(); }

        template <typename T, typename U>
        bool Is(const T& a, const U& b, GreaterEqual)
        { return a.GetArea() >= b.GetArea(); }

        template <typename T, typename U>
        bool operator()(const T& a, const U& b)
        { return Is(a, b, comparison()); }
      };

      template <typename T, typename T_PositionPolicy, typename T_Comparison>
      struct Area
      {
        typedef math_t::Rectangle_TI<T, T_PositionPolicy>     value_type;
        typedef T_Comparison                                  comparison;

        Area(const value_type& a_rect)
          : m_rect(&a_rect)
        { }

        bool Is(const value_type& a_other, Equal)
        { return math::IsEqual(m_rect->GetArea(), a_other.GetArea()); }

        bool Is(const value_type& a_other, Less)
        { return m_rect->GetArea() < a_other.GetArea(); }

        bool Is(const value_type& a_other, Greater)
        { return m_rect->GetArea() > a_other.GetArea(); }

        bool Is(const value_type& a_other, LessEqual)
        { return m_rect->GetArea() <= a_other.GetArea(); }

        bool Is(const value_type& a_other, GreaterEqual)
        { return m_rect->GetArea() >= a_other.GetArea(); }

        bool operator()(const value_type& a_other)
        { return Is(a_other, comparison()); }

        const value_type* m_rect;
      };

      template <typename T, typename T_PositionPolicy, typename T_Comparison>
      Area<T, T_PositionPolicy, T_Comparison>
        MakeArea(const math_t::Rectangle_TI<T, T_PositionPolicy>& a_rect, 
                 T_Comparison)
      { 
        type_traits::AssertTypeIsSupported<T_Comparison, 
          Equal, Less, Greater, LessEqual, GreaterEqual>();
        return Area<T, T_PositionPolicy, T_Comparison>(a_rect);
      }

    };

  };};

};};};

#endif