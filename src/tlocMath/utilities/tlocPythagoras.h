#ifndef _TLOC_MATH_UTILS_PYTHAGORAS_H_
#define _TLOC_MATH_UTILS_PYTHAGORAS_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocMath/angle/tlocAngle.h>

namespace tloc { namespace math { namespace utils {

  template <typename T>
  class Pythagoras_T
  {
  public:
    typedef T                           value_type;
    typedef math::Degree_T<value_type>  angle_type;

    typedef core::types::StrongType_T<value_type, 0> base;
    typedef core::types::StrongType_T<value_type, 1> opposite;
    typedef core::types::StrongType_T<value_type, 2> hypotenuse;

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

    angle_type GetAngle() const;
    angle_type GetAngleOpposite() const;

    TLOC_DECL_AND_DEF_GETTER(value_type, GetBase, m_base);
    TLOC_DECL_AND_DEF_GETTER(value_type, GetOpposite, m_oppos);
    TLOC_DECL_AND_DEF_GETTER(value_type, GetHypotenuse, m_hypo);

  private:

    void DoSet(base, opposite);
    void DoSet(opposite, base);
    void DoSet(base, hypotenuse);
    void DoSet(hypotenuse, base);
    void DoSet(opposite, hypotenuse);
    void DoSet(hypotenuse, opposite);

    void DoSet(angle_type, base);
    void DoSet(angle_type, opposite);
    void DoSet(angle_type, hypotenuse);

    value_type m_base, m_oppos, m_hypo;

  };

  //------------------------------------------------------------------------
  // Common typedefs

  typedef Pythagoras_T<tl_float>    Pythagoras;
  typedef Pythagoras_T<f32>         Pythagorasf32;
  typedef Pythagoras_T<f64>         Pythagorasf64;

};};};

#endif