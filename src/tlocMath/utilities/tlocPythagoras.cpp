#include "tlocPythagoras.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/data_structures/tlocTuple.inl.h>
#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl.h>

namespace tloc { namespace math { namespace utils {

  //------------------------------------------------------------------------
  // using
  using math::types::Degree_T;
  using math::types::Radian_T;

  namespace
  {
    template <typename T>
    T GetHypo(T a_base, T a_oppos)
    {
      return math::Sqrt( (a_base * a_base) + (a_oppos * a_oppos) );
    }

    template <typename T>
    T GetOther(T a_hypo, T a_other)
    {
      TLOC_ASSERT_LOW_LEVEL(a_hypo > a_other, "Triangle is not right-angled");
      return math::Sqrt( (a_hypo * a_hypo) - (a_other * a_other) );
    }

    //------------------------------------------------------------------------
    // Helper functions

#define TYPEDEF_TYPES()\
  typedef typename T::value_type    value_type;\
  typedef typename T::base          base;\
  typedef typename T::opposite      opposite;\
  typedef typename T::hypotenuse    hypotenuse

#define T_TYPE typename T

    template <class T>
    void DoSet(T_TYPE::base a_base,
               T_TYPE::opposite a_oppos,
               T_TYPE::cont_type& m_sides)
    {
      TYPEDEF_TYPES();
      m_sides[base::k_index]        = a_base;
      m_sides[opposite::k_index]    = a_oppos;
      m_sides[hypotenuse::k_index]  = GetHypo<value_type>(a_base, a_oppos);
    }

    template <class T>
    void DoSet(T_TYPE::opposite a_oppos,
               T_TYPE::base a_base,
               T_TYPE::cont_type& m_sides)
    {
      DoSet<T>(a_base, a_oppos, m_sides);
    }

    template <class T>
    void DoSet(T_TYPE::base a_base,
               T_TYPE::hypotenuse a_hypo,
               T_TYPE::cont_type& m_sides)
    {
      TYPEDEF_TYPES();
      m_sides[base::k_index]        = a_base;
      m_sides[hypotenuse::k_index]  = a_hypo;
      m_sides[opposite::k_index]    = GetOther<value_type>(a_hypo, a_base);
    }

    template <class T>
    void DoSet(T_TYPE::hypotenuse a_hypo,
               T_TYPE::base a_base,
               T_TYPE::cont_type& m_sides)
    {
      DoSet<T>(a_base, a_hypo, m_sides);
    }

    template <class T>
    void DoSet(T_TYPE::opposite a_oppos,
               T_TYPE::hypotenuse a_hypo,
               T_TYPE::cont_type& m_sides)
    {
      TYPEDEF_TYPES();
      m_sides[opposite::k_index]    = a_oppos;
      m_sides[hypotenuse::k_index]  = a_hypo;
      m_sides[base::k_index] = GetOther<value_type>(a_hypo, a_oppos);
    }

    template <class T>
    void DoSet(T_TYPE::hypotenuse a_hypo,
               T_TYPE::opposite a_oppos,
               T_TYPE::cont_type& m_sides)
    {
      DoSet<T>(a_oppos, a_hypo, m_sides);
    }

    template <class T>
    void DoSet(T_TYPE::angle_type a_angle,
               T_TYPE::base a_base,
               T_TYPE::cont_type& m_sides)
    {
      TYPEDEF_TYPES();
      hypotenuse hypo = hypotenuse(a_base / math::Cos(math_t::MakeRadian(a_angle)) );
      DoSet<T>(a_base, hypo, m_sides);
    }

    template <class T>
    void DoSet(T_TYPE::angle_type a_angle,
               T_TYPE::opposite a_oppos,
               T_TYPE::cont_type& m_sides)
    {
      TYPEDEF_TYPES();
      hypotenuse hypo = hypotenuse(a_oppos / math::Sin(math_t::MakeRadian(a_angle)) );
      DoSet<T>(a_oppos, hypo, m_sides);
    }

    template <class T>
    void DoSet(T_TYPE::angle_type a_angle,
               T_TYPE::hypotenuse a_hypo,
               T_TYPE::cont_type& m_sides)
    {
      TYPEDEF_TYPES();
      opposite oppos = opposite(a_hypo * math::Sin(math_t::MakeRadian(a_angle)) );
      DoSet<T>(oppos, a_hypo, m_sides);
    }

  };

  //////////////////////////////////////////////////////////////////////////
  // Pythagoras_T

#define PYTHAGORAS_TEMP   typename T
#define PYTHAGORAS_PARAMS T
#define PYTHAGORAS_TYPE   typename Pythagoras_T<PYTHAGORAS_PARAMS>

  template <PYTHAGORAS_TEMP>
  template <typename T_TriSide1, typename T_TriSide2>
  void
    Pythagoras_T<PYTHAGORAS_PARAMS>::
    DoConstruct(T_TriSide1 a_side1, T_TriSide2 a_side2)
  {
    DoSet<this_type>(a_side1, a_side2, m_sides);
  }

  template <PYTHAGORAS_TEMP>
  template <typename T_TriSide>
  void Pythagoras_T<PYTHAGORAS_PARAMS>::
    DoConstruct(angle_type a_angle, T_TriSide a_side)
  {
    DoSet<this_type>(a_angle, a_side, m_sides);
  }

  template <PYTHAGORAS_TEMP>
  Pythagoras_T<PYTHAGORAS_PARAMS>::
    Pythagoras_T(const this_type& a_other)
    : m_sides(a_other.m_sides)
  { }

  template <PYTHAGORAS_TEMP>
  PYTHAGORAS_TYPE::angle_type
    Pythagoras_T<PYTHAGORAS_PARAMS>::
    GetAngle() const
  {
    return Radian_T<value_type>
      ( math::ACos(m_sides[base::k_index] / m_sides[hypotenuse::k_index]) );
  }

  template <PYTHAGORAS_TEMP>
  PYTHAGORAS_TYPE::angle_type
    Pythagoras_T<PYTHAGORAS_PARAMS>::
    GetAngleOpposite() const
  {
    return 90 - GetAngle().template GetAs<angle_type>();
  }

  //------------------------------------------------------------------------
  // Explicit Instantiation

#define TLOC_INSTANTIATE_PYTHAGORAS(_type_)\
  template class Pythagoras_T<_type_>;\
  \
  template void Pythagoras_T<_type_>::DoConstruct(Pythagoras_T<_type_>::base, Pythagoras_T<_type_>::opposite);\
  template void Pythagoras_T<_type_>::DoConstruct(Pythagoras_T<_type_>::opposite , Pythagoras_T<_type_>::base);\
  template void Pythagoras_T<_type_>::DoConstruct(Pythagoras_T<_type_>::base, Pythagoras_T<_type_>::hypotenuse);\
  template void Pythagoras_T<_type_>::DoConstruct(Pythagoras_T<_type_>::hypotenuse, Pythagoras_T<_type_>::base);\
  template void Pythagoras_T<_type_>::DoConstruct(Pythagoras_T<_type_>::opposite, Pythagoras_T<_type_>::hypotenuse);\
  template void Pythagoras_T<_type_>::DoConstruct(Pythagoras_T<_type_>::hypotenuse, Pythagoras_T<_type_>::opposite);\
  \
  template void Pythagoras_T<_type_>::DoConstruct(Degree_T<_type_>, Pythagoras_T<_type_>::base);\
  template void Pythagoras_T<_type_>::DoConstruct(Degree_T<_type_>, Pythagoras_T<_type_>::opposite);\
  template void Pythagoras_T<_type_>::DoConstruct(Degree_T<_type_>, Pythagoras_T<_type_>::hypotenuse);\
  \
  template void Pythagoras_T<_type_>::DoConstruct(Radian_T<_type_>, Pythagoras_T<_type_>::base);\
  template void Pythagoras_T<_type_>::DoConstruct(Radian_T<_type_>, Pythagoras_T<_type_>::opposite);\
  template void Pythagoras_T<_type_>::DoConstruct(Radian_T<_type_>, Pythagoras_T<_type_>::hypotenuse)

  TLOC_INSTANTIATE_PYTHAGORAS(f32);
  TLOC_INSTANTIATE_PYTHAGORAS(f64);

};};};
