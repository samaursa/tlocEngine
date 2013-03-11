#ifndef _TLOC_MATH_UTILS_PYTHAGORAS_H_
#define _TLOC_MATH_UTILS_PYTHAGORAS_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocMath/types/tlocAngle.h>

namespace tloc { namespace math { namespace utils {

  template <typename T>
  class Pythagoras_T
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef T                                         value_type;
    typedef math::types::Degree_T<value_type>         angle_type;
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

    template <typename T_Side>
    value_type GetSide()
    { return m_sides[T_Side::k_index]; }

  private:

    cont_type m_sides;

  };

  //------------------------------------------------------------------------
  // Common typedefs

  typedef Pythagoras_T<tl_float>    Pythagoras;
  typedef Pythagoras_T<f32>         Pythagorasf32;
  typedef Pythagoras_T<f64>         Pythagorasf64;

};};};

#endif