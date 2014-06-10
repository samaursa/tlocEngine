#ifndef _TLOC_MATH_ANGLE_H_
#define _TLOC_MATH_ANGLE_H_

#include <tlocCore/base_classes/tlocPolicyBase.h>
#include <tlocMath/tlocMathBase.h>

#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace math { namespace types {

  template <typename T, class T_Derived>
  class Angle_T
    : core_bclass::PolicyBase_TI<T_Derived>
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef T                                         value_type;
    typedef T_Derived                                 derived_type;
    typedef Angle_T<value_type, derived_type>         this_type;
    typedef core_bclass::PolicyBase_TI<derived_type>  base_type;

  public:
    Angle_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Angle_T(T_AngleType a_angle);

    derived_type&    operator=(value_type a_angle);
    derived_type&    operator=(const this_type& a_other);

    template <typename T_AngleType>
    derived_type&    operator=(const T_AngleType& a_angle);

    template <typename T_AngleType>
    value_type    GetAs() const;
    TLOC_DECL_AND_DEF_GETTER(value_type, Get, m_angle);

    derived_type   operator+  (this_type a_other) const;
    derived_type&  operator+= (this_type a_other) ;

    derived_type   operator-  (this_type a_other) const;
    derived_type&  operator-= (this_type a_other) ;

    derived_type   operator*  (this_type a_other) const;
    derived_type&  operator*= (this_type a_other) ;

    derived_type   operator/  (this_type a_other) const;
    derived_type&  operator/= (this_type a_other) ;

    bool operator <  (this_type a_other) const;
    bool operator == (this_type a_other) const;
    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    typedef type_true     fundamental_type;
    typedef type_false    angle_type;

    void DoSetAngleCtor(value_type, fundamental_type);
    template <typename T_AngleType>
    void DoSetAngleCtor(T_AngleType, angle_type);

    value_type    m_angle;

  private:
    using base_type::This;
  };

  //////////////////////////////////////////////////////////////////////////
  // Radian

  template <typename T>
  class Radian_T : protected Angle_T<T, Radian_T<T> >
  {
  public:
    template <typename U, class V> friend class Angle_T;

    typedef Radian_T<T>              this_type;
    typedef Angle_T<T, this_type>    base_type;

    typedef typename base_type::value_type  value_type;

    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator-;
    using base_type::operator-=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator<;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>;
    using base_type::operator<=;
    using base_type::operator>=;

    using base_type::GetAs;
    using base_type::Get;
    using base_type::m_angle;

  public:
    Radian_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Radian_T(T_AngleType a_angle);

    template <typename T_AngleType>
    this_type&    operator=(const T_AngleType& a_angle);

    value_type GetAsDegree() const;

  private:
    template <typename T_AngleType>
    void DoSetAngle(T_AngleType a_angle);
    void DoSetAngle(this_type a_angle);

    template <typename T_AngleType>
    value_type DoGetAs(T_AngleType) const;
    value_type DoGetAs(this_type) const;
  };

  //////////////////////////////////////////////////////////////////////////
  // Degree

  template <typename T>
  class Degree_T : protected Angle_T<T, Degree_T<T> >
  {
  public:
    template <typename U, class V> friend class Angle_T;

    typedef Degree_T<T>              this_type;
    typedef Angle_T<T, this_type>    base_type;

    typedef typename base_type::value_type  value_type;

    using base_type::operator+;
    using base_type::operator+=;
    using base_type::operator-;
    using base_type::operator-=;
    using base_type::operator*;
    using base_type::operator*=;
    using base_type::operator/;
    using base_type::operator/=;

    using base_type::operator<;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>;
    using base_type::operator<=;
    using base_type::operator>=;

    using base_type::GetAs;
    using base_type::Get;
    using base_type::m_angle;

  public:
    Degree_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Degree_T(T_AngleType a_angle);

    template <typename T_AngleType>
    this_type&    operator=(const T_AngleType& a_angle);

    value_type GetAsRadian() const;

  private:
    template <typename T_AngleType>
    void DoSetAngle(T_AngleType a_angle);
    void DoSetAngle(this_type a_angle);

    template <typename T_AngleType>
    value_type DoGetAs(T_AngleType) const;
    value_type DoGetAs(this_type) const;
  };

  //////////////////////////////////////////////////////////////////////////
  // Template definitions

  template <typename T, class T_Derived>
  template <typename T_AngleType>
  Angle_T<T, T_Derived>::
    Angle_T(T_AngleType a_angle)
  {
    typedef Loki::TypeTraits<T_AngleType>                 unknown_type;
    typedef Loki::Int2Type<unknown_type::isFundamental>   resolved_angle_type;

    TLOC_STATIC_ASSERT(
      ( Loki::Conversion<T_AngleType, this_type>::exists2Way ||
        Loki::TypeTraits<T_AngleType>::isArith),
        T_AngleType_must_be_derived_from_Angle_T_or_must_be_value_type);

    // Select the type to cast to, this is necessary for f32 and f64 (does
    // nothing for Radian or Degree) to allow casting from f32 to f64. An
    // unfortunate side-effect is that f64 to f32 casts will be implicit but
    // hopefully no angle will be big enough
    typedef typename Loki::Select<Loki::TypeTraits<T_AngleType>::isFloat,
      value_type, T_AngleType>::Result  cast_to;

    DoSetAngleCtor(static_cast<cast_to>(a_angle), resolved_angle_type() );
  }

  template <typename T, class T_Derived>
  template <typename T_AngleType>
  void Angle_T<T, T_Derived>::
    DoSetAngleCtor(T_AngleType a_angle, angle_type)
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<value_type, typename T_AngleType::value_type>::value),
      value_types_are_not_the_same);

    static_cast<derived_type*>(this)->DoSetAngle(a_angle);
  }

  //------------------------------------------------------------------------
  // Radian

  template <typename T>
  template <typename T_AngleType>
  Radian_T<T>::
    Radian_T(T_AngleType a_angle)
    : base_type(a_angle)
  {
    TLOC_STATIC_ASSERT(
      ( Loki::Conversion<T_AngleType, base_type>::exists2Way ||
        Loki::TypeTraits<T_AngleType>::isFloat),
        T_AngleType_must_be_a_real_number_or_derived_from_Angle_T);
  }

  // -----------------------------------------------------------------------

  template <typename T>
  Radian_T<T>
    MakeRadian(T a_angle)
  {
    return Radian_T<T>(a_angle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  Radian_T<T>
    MakeRadian(Degree_T<T> a_angle)
  {
    return Radian_T<T>(a_angle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  Radian_T<T>
    MakeRadian(Radian_T<T> a_angle)
  {
    return a_angle
  }

  //------------------------------------------------------------------------
  // Degree

  template <typename T>
  template <typename T_AngleType>
  Degree_T<T>::
    Degree_T(T_AngleType a_angle)
    : base_type(a_angle)
  {
    TLOC_STATIC_ASSERT(
      ( Loki::Conversion<T_AngleType, base_type>::exists2Way ||
        Loki::TypeTraits<T_AngleType>::isArith),
        T_AngleType_must_be_derived_from_Angle_T);
  }

  // -----------------------------------------------------------------------

  template <typename T>
  Degree_T<T>
    MakeDegree(T a_angle)
  {
    return Degree_T<T>(a_angle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  Degree_T<T>
    MakeDegree(Radian_T<T> a_angle)
  {
    return Degree_T<T>(a_angle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  Degree_T<T>
    MakeDegree(Degree_T<T> a_angle)
  {
    return a_angle;
  }

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef Radian_T<tl_float>      Radian;
  typedef Radian_T<f32>           radian_f32;
  typedef Radian_T<f64>           radian_f64;

  typedef Degree_T<tl_float>      Degree;
  typedef Degree_T<f32>           degree_f32;
  typedef Degree_T<f64>           degree_f64;

};};};

#endif