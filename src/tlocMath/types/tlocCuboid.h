#ifndef _TLOC_MATH_TYPES_CUBOID_H_
#define _TLOC_MATH_TYPES_CUBOID_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocRay.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Cuboid_T
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef tl_size                                   size_type;
    typedef T                                         real_type;
    typedef Cuboid_T<real_type>                       this_type;
    typedef Vector3<real_type>                        point_type;
    typedef Ray_T<real_type, 3>                       ray_3d_type;

    typedef core::types::StrongType_T<real_type, 0>   width;
    typedef core::types::StrongType_T<real_type, 1>   height;
    typedef core::types::StrongType_T<real_type, 2>   depth;
    typedef core::types::StrongType_T<real_type, 3>   left;
    typedef core::types::StrongType_T<real_type, 4>   right;
    typedef core::types::StrongType_T<real_type, 5>   top;
    typedef core::types::StrongType_T<real_type, 6>   bottom;
    typedef core::types::StrongType_T<real_type, 7>   back;
    typedef core::types::StrongType_T<real_type, 8>   front;

    typedef core::types::StrongType_T<point_type, 0>  position;

    typedef core::types::StrongType_T<bool, 0>        from_origin;
    typedef core::types::StrongType_T<bool, 1>        double_sided;

    typedef core::Pair<bool,
      typename ray_3d_type::vec_type>                 intersect_ret_type;

    typedef core_conts::Array<intersect_ret_type>     intersect_ret_type_cont;

  public:
    Cuboid_T();
    Cuboid_T(width a_w, height a_h, depth a_d,
             position a_pos = position(point_type(0)) );
    Cuboid_T(left a_l, right a_r, top a_t, bottom a_b, front a_fr, back a_ba);

    template <typename T_Real>
    Cuboid_T(const Cuboid_T<T_Real>& a_cuboid);

    this_type&  operator= (const this_type& a_other);
    void        swap(this_type& a_cuboid);

    bool operator==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    real_type   GetWidth() const;
    real_type   GetHeight() const;
    real_type   GetDepth() const;

    void        SetWidth(real_type a_value);
    void        SetHeight(real_type a_value);
    void        SetDepth(real_type a_value);

    template <typename T_Side>
    real_type GetValue() const;
    template <typename T_Side1, typename T_Side2, typename T_Side3>
    point_type GetCoord() const;

    point_type  GetCoord_TopLeftBack() const;
    point_type  GetCoord_TopRightBack() const;
    point_type  GetCoord_BottomLeftBack() const;
    point_type  GetCoord_BottomRightBack() const;

    point_type  GetCoord_TopLeftFront() const;
    point_type  GetCoord_TopRightFront() const;
    point_type  GetCoord_BottomLeftFront() const;
    point_type  GetCoord_BottomRightFront() const;

    void        SetPosition(const point_type& a_centerPosition);
    void        ResetPosition();
    void        Offset(const point_type& a_offsetBy);
    point_type  GetPosition() const;

    TLOC_DECL_AND_DEF_GETTER(point_type, GetDimensions, m_dimensions);

    bool        IsValid() const;

    bool        Contains(const point_type& a_xyzPoint);
    bool        Intersects(const this_type& a_other) const;
    bool        Intersects(const this_type& a_other,
                           this_type& a_overlapOut) const;
    bool        Intersects(const ray_3d_type& a_ray,
                           from_origin a_fo = from_origin(true)) const;
  private:
    real_type   DoGetValue(tl_int a_index) const;
    template <typename T_Side1, typename T_Side2, typename T_Side3>
    point_type  DoGetCoord() const;

  private:
    point_type    m_dimensions;
    point_type    m_position;

  };

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T>
  template <typename T_Real>
  Cuboid_T<T>::
    Cuboid_T(const Cuboid_T<T_Real>& a_other)
    : m_dimensions(a_other.GetDimensions())
  { }

  template <typename T>
  template <typename T_Side>
  typename Cuboid_T<T>::real_type
    Cuboid_T<T>::GetValue() const
  {
    tloc::type_traits::
      AssertTypeIsSupported<T_Side, left, right, top, bottom, back, front>();
    return DoGetValue(T_Side::k_index);
  }

  template <typename T>
  template <typename T_Side1, typename T_Side2, typename T_Side3>
  typename Cuboid_T<T>::point_type
    Cuboid_T<T>::GetCoord() const
  {
    tloc::type_traits::AssertTypeIsSupported<T_Side1, top, bottom>();
    tloc::type_traits::AssertTypeIsSupported<T_Side2, left, right>();
    tloc::type_traits::AssertTypeIsSupported<T_Side3, back, front>();
    return DoGetCoord<T_Side1, T_Side2, T_Side3>();
  }

  //------------------------------------------------------------------------
  // swap

  template <typename T>
  void swap(Cuboid_T<T>& a, Cuboid_T<T>& b)
  { a.swap(b); }

  //------------------------------------------------------------------------
  // Typedefs

  typedef Cuboid_T<tl_float>   Cuboidf;
  typedef Cuboid_T<f32>        Cuboidf32;
  typedef Cuboid_T<f64>        Cuboidf64;

};};};

#endif