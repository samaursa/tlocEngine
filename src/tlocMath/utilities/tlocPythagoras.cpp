#include "tlocPythagoras.h"

#include <tlocCore/data_structures/tlocTuple.inl>
#include <tlocMath/tlocMath.h>
#include <cmath>

namespace tloc { namespace math { namespace utils {

#define PYTHAGORAS_TEMP   typename T
#define PYTHAGORAS_PARAMS T
#define PYTHAGORAS_TYPE   typename Pythagoras_T<PYTHAGORAS_PARAMS>

  namespace
  {
    template <typename T>
    T GetHypo(T a_base, T a_oppos)
    {
      return Math<T>::Sqrt( (a_base * a_base) + (a_oppos * a_oppos) );
    }

    template <typename T>
    T GetOther(T a_hypo, T a_other)
    {
      TLOC_ASSERT_LOW_LEVEL(a_hypo > a_other, "Triangle is not right-angled");
      return Math<T>::Sqrt( (a_hypo * a_hypo) - (a_other * a_other) );
    }
  };

  template <PYTHAGORAS_TEMP>
  template <typename T_TriSide1, typename T_TriSide2>
  Pythagoras_T<PYTHAGORAS_PARAMS>::
    Pythagoras_T(T_TriSide1 a_side1, T_TriSide2 a_side2)
  {
    DoSet(a_side1, a_side2);
  }

  template <PYTHAGORAS_TEMP>
  template <typename T_TriSide>
  Pythagoras_T<PYTHAGORAS_PARAMS>::
    Pythagoras_T(angle_type a_angle, T_TriSide a_side)
  {
    DoSet(a_angle, a_side);
  }

  template <PYTHAGORAS_TEMP>
  Pythagoras_T<PYTHAGORAS_PARAMS>::
    Pythagoras_T(const this_type& a_other)
    : m_sides(a_other.m_sides)
  { }

  template <PYTHAGORAS_TEMP>
  PYTHAGORAS_TYPE::angle_type
    Pythagoras_T<PYTHAGORAS_PARAMS>::GetAngle() const
  {
    return Math<value_type>::ACos(m_sides[base::k_index] /
                                  m_sides[hypotenuse::k_index]);
  }

  template <PYTHAGORAS_TEMP>
  PYTHAGORAS_TYPE::angle_type
    Pythagoras_T<PYTHAGORAS_PARAMS>::GetAngleOpposite() const
  {
    return 90 - GetAngle().GetAs<angle_type>();
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(base a_base, opposite a_oppos)
  {
    m_sides[base::k_index]        = a_base;
    m_sides[opposite::k_index]    = a_oppos;
    m_sides[hypotenuse::k_index]  = GetHypo<value_type>(a_base, a_oppos);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(opposite a_oppos, base a_base)
  {
    DoSet(a_base, a_oppos);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(base a_base, hypotenuse a_hypo)
  {
    m_sides[base::k_index]        = a_base;
    m_sides[hypotenuse::k_index]  = a_hypo;
    m_sides[opposite::k_index]    = GetOther<value_type>(a_hypo, a_base);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(hypotenuse a_hypo, base a_base)
  {
    DoSet(a_base, a_hypo);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(opposite a_oppos, hypotenuse a_hypo)
  {
    m_sides[opposite::k_index]    = a_oppos;
    m_sides[hypotenuse::k_index]  = a_hypo;
    m_sides[base::k_index] = GetOther<value_type>(a_hypo, a_oppos);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(hypotenuse a_hypo, opposite a_oppos)
  {
    DoSet(a_oppos, a_hypo);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(angle_type a_angle, base a_base)
  {
    hypotenuse hypo = hypotenuse
      (a_base / Math<value_type>::Cos(a_angle.GetAs<angle_type>()) );
    DoSet(a_base, hypo);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(angle_type a_angle, opposite a_oppos)
  {
    hypotenuse hypo = hypotenuse
      (a_oppos / Math<value_type>::Sin(a_angle.GetAs<angle_type>()) );
    DoSet(a_oppos, hypo);
  }

  template <PYTHAGORAS_TEMP>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::DoSet(angle_type a_angle, hypotenuse a_hypo)
  {
    opposite oppos = opposite
      (a_hypo * Math<value_type>::Sin(a_angle.GetAs<angle_type>()) );
    DoSet(oppos, a_hypo);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiation

#define TLOC_INSTANTIATE_PYTHAGORAS(_type_)\
  template class Pythagoras_T<_type_>;\
  \
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::base, Pythagoras_T<_type_>::opposite);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::opposite , Pythagoras_T<_type_>::base);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::base, Pythagoras_T<_type_>::hypotenuse);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::hypotenuse, Pythagoras_T<_type_>::base);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::opposite, Pythagoras_T<_type_>::hypotenuse);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::hypotenuse, Pythagoras_T<_type_>::opposite);\
  \
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::angle_type, Pythagoras_T<_type_>::base);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::angle_type, Pythagoras_T<_type_>::opposite);\
  template Pythagoras_T<_type_>::Pythagoras_T(Pythagoras_T<_type_>::angle_type, Pythagoras_T<_type_>::hypotenuse)

  TLOC_INSTANTIATE_PYTHAGORAS(f32);
  TLOC_INSTANTIATE_PYTHAGORAS(f64);

};};};
