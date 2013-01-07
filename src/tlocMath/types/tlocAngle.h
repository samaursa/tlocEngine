#ifndef _TLOC_MATH_ANGLE_H_
#define _TLOC_MATH_ANGLE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace math { namespace types {

  template <typename T, class T_Derived>
  class Angle_T
  {
  public:
    typedef T           value_type;

    typedef T_Derived   derived_type;
    typedef Angle_T     this_type;

    Angle_T(value_type a_angle = 0);

    template <typename T_AngleType>
    Angle_T(T_AngleType a_angle)
    {
      typedef Loki::TypeTraits<T_AngleType>                 unknown_type;
      typedef Loki::Int2Type<unknown_type::isFundamental>   resolved_angle_type;

      DoSetAngleCtor(a_angle, resolved_angle_type() );
    }

    this_type&    operator=(value_type a_angle);
    this_type&    operator=(const this_type& a_other);

    template <typename T_AngleType>
    this_type&    operator=(const T_AngleType& a_angle);

    template <typename T_AngleType>
    value_type    GetAs() const;
    TLOC_DECL_AND_DEF_GETTER(value_type, Get, m_angle);

    this_type   operator+  (this_type a_other) const;
    this_type&  operator+= (this_type a_other) ;

    this_type   operator-  (this_type a_other) const;
    this_type&  operator-= (this_type a_other) ;

    this_type   operator*  (this_type a_other) const;
    this_type&  operator*= (this_type a_other) ;

    this_type   operator/  (this_type a_other) const;
    this_type&  operator/= (this_type a_other) ;

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
    Radian_T(T_AngleType a_angle) : base_type(a_angle)
    { }

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
    Degree_T(T_AngleType a_angle) : base_type(a_angle)
    { }

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
  // Typedefs

  typedef Radian_T<tl_float>      Radian;
  typedef Radian_T<f32>           Radian32;
  typedef Radian_T<f64>           Radian64;

  typedef Degree_T<tl_float>      Degree;
  typedef Degree_T<f32>           Degree32;
  typedef Degree_T<f64>           Degree64;

};};};

#endif