#ifndef _TLOC_MATH_UTILS_PYTHAGORAS_H_
#define _TLOC_MATH_UTILS_PYTHAGORAS_H_

#include <tlocMath/tlocMathBase.h>
#include <tlocMath/types/tlocAngle.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace math { namespace utils {

  template <typename T>
  class Pythagoras_T
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef T                                         value_type;
    typedef math_t::Degree_T<value_type>              angle_type;
    typedef math_t::Radian_T<value_type>              radian_type;
    typedef Pythagoras_T<value_type>                  this_type;
    typedef core::data_structs::Tuple<value_type, 3>  cont_type;

    typedef core::types::StrongType_T<value_type, 0>  base;
    typedef core::types::StrongType_T<value_type, 1>  opposite;
    typedef core::types::StrongType_T<value_type, 2>  hypotenuse;

  public:

    ///-------------------------------------------------------------------------
    /// @brief Pythagoras generic constructor
    ///
    /// @param  a_side1 base, oppoiste or hypotenuse
    /// @param  a_side2 base, oppoiste or hypotenuse
    ///-------------------------------------------------------------------------
    template <typename T_TriSide1, typename T_TriSide2>
    Pythagoras_T(T_TriSide1 a_side1, T_TriSide2 a_side2);

    template <typename T_TriSide>
    Pythagoras_T(angle_type a_angle, T_TriSide a_side);

    Pythagoras_T(const this_type& a_other);

    angle_type GetAngle() const;
    angle_type GetAngleOpposite() const;

    template <typename T_TriSide>
    value_type GetSide();

  private:
    template <typename T_TriSide1, typename T_TriSide2>
    void DoConstruct(T_TriSide1 a_side1, T_TriSide2 a_side2);

    template <typename T_TriSide>
    void DoConstruct(angle_type a_angle, T_TriSide a_side);

  private:
    cont_type m_sides;
  };

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T>
  template <typename T_TriSide1, typename T_TriSide2>
  Pythagoras_T<T>::
    Pythagoras_T(T_TriSide1 a_side1, T_TriSide2 a_side2)
  {
    typedef math_t::Degree_T<T> deg;
    typedef math_t::Radian_T<T> rad;

    // We need deg and rad in there for the first argument because this ctor
    // is compiled anyway and it will error out before selecting the other ctor
    type_traits::AssertTypeIsSupported
      <T_TriSide1, base, opposite, hypotenuse, deg, rad>();
    type_traits::AssertTypeIsSupported
      <T_TriSide2, base, opposite, hypotenuse>();
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<T_TriSide1, T_TriSide2>::value == false),
        Two_sides_cannot_be_the_same);

    DoConstruct(a_side1, a_side2);
  }

  template <typename T>
  template <typename T_TriSide>
  Pythagoras_T<T>::
    Pythagoras_T(angle_type a_angle, T_TriSide a_side)
  {
    type_traits::AssertTypeIsSupported
      <T_TriSide, base, opposite, hypotenuse>();

    DoConstruct(a_angle, a_side);
  }

  template <typename T>
  template <typename T_TriSide>
  typename Pythagoras_T<T>::value_type
    Pythagoras_T<T>::
    GetSide()
  {
    type_traits::AssertTypeIsSupported
      <T_TriSide, base, opposite, hypotenuse>();

    return m_sides[T_TriSide::k_index];
  }


  //------------------------------------------------------------------------
  // Common typedefs

  typedef Pythagoras_T<tl_float>    Pythagoras;
  typedef Pythagoras_T<f32>         Pythagorasf32;
  typedef Pythagoras_T<f64>         Pythagorasf64;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Pythagoras_T<tl_float>);
  TLOC_EXTERN_TEMPLATE_CLASS(Pythagoras_T<f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Pythagoras_T<f64>);

};};};

#endif