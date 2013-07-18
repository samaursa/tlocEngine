#ifndef _TLOC_MATH_TYPES_CUBOID_H_
#define _TLOC_MATH_TYPES_CUBOID_H_

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
    typedef core::types::StrongType_T<real_type, 7>   near;
    typedef core::types::StrongType_T<real_type, 8>   far;

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
    Cuboid_T(left a_l, right a_r, top a_t, bottom a_b, near a_n, far a_f);

    template <typename T_Real>
    Cuboid_T(const Rectangle_T<T_Real>& a_rect,
             real_type a_near, real_type a_far);

    this_type& operator= (const this_type& a_other);

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

    point_type GetCoord_TopLeftNear() const;
    point_type GetCoord_TopRightNear() const;
    point_type GetCoord_BottomLeftNear() const;
    point_type GetCoord_BottomRightNear() const;

    point_type GetCoord_TopLeftFar() const;
    point_type GetCoord_TopRightFar() const;
    point_type GetCoord_BottomLeftFar() const;
    point_type GetCoord_BottomRightFar() const;

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
    bool        Intersects(const ray_3d_type& a_ray) const;
    intersect_ret_type
                Intersects(const ray_3d_type& a_ray,
                           from_origin a_fo = from_origin(true),
                           double_sided a_ds = double_sided(false) ) const;
    void        Intersects(const ray_3d_type& a_ray,
                           intersect_ret_type_cont& a_out,
                           from_origin a_fo = from_origin(true)) const;
  private:
    point_type    m_dimensions;
  };

};};};

#endif