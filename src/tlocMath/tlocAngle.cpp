#include "tlocAngle.h"
#include "tlocAngle.inl"

namespace tloc { namespace math {

  template class Radian_T<f32>;
  template class Radian_T<f64>;

  template class Degree_T<f32>;
  template class Degree_T<f64>;

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

#include "tlocAngleExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f32, Radian_T, Degree_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f64, Radian_T, Degree_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f32, Degree_T, Radian_T);
  TLOC_EXPLICITLY_INSTANTIATE_ANGLE(f64, Degree_T, Radian_T);

  ////------------------------------------------------------------------------
  //// Angle

  //template class Angle_T<f32, Radian_T<f32> >;
  //template class Angle_T<f64, Radian_T<f64> >;

  //template f32 Angle_T<f32, Radian_T<f32> >::GetAs<Radian_T<f32> >() const;
  //template f32 Angle_T<f32, Radian_T<f32> >::GetAs<Degree_T<f32> >() const;
  //template f64 Angle_T<f64, Radian_T<f64> >::GetAs<Radian_T<f64> >() const;
  //template f64 Angle_T<f64, Radian_T<f64> >::GetAs<Degree_T<f64> >() const;

  //template f32 Angle_T<f32, Degree_T<f32> >::GetAs<Radian_T<f32> >() const;
  //template f32 Angle_T<f32, Degree_T<f32> >::GetAs<Degree_T<f32> >() const;
  //template f64 Angle_T<f64, Degree_T<f64> >::GetAs<Radian_T<f64> >() const;
  //template f64 Angle_T<f64, Degree_T<f64> >::GetAs<Degree_T<f64> >() const;

  ////------------------------------------------------------------------------
  //// Radian

  //template Radian_T<f32>::Radian_T(Radian_T<f32>);
  //template Radian_T<f32>::Radian_T(Degree_T<f32>);
  //template Radian_T<f64>::Radian_T(Radian_T<f64>);
  //template Radian_T<f64>::Radian_T(Degree_T<f64>);

  //template void Radian_T<f32>::DoSetAngle(Degree_T<f32>);
  //template void Radian_T<f64>::DoSetAngle(Degree_T<f32>);

  //template Radian_T<f32>::value_type Radian_T<f32>::DoGetAs(Degree_T<f32>) const;
  //template Radian_T<f64>::value_type Radian_T<f64>::DoGetAs(Degree_T<f64>) const;

  ////------------------------------------------------------------------------
  //// Degree

  //template Degree_T<f32>::Degree_T(Radian_T<f32>);
  //template Degree_T<f32>::Degree_T(Degree_T<f32>);
  //template Degree_T<f64>::Degree_T(Radian_T<f64>);
  //template Degree_T<f64>::Degree_T(Degree_T<f64>);

  //template void Degree_T<f64>::DoSetAngle(Degree_T<f32>);
  //template void Degree_T<f64>::DoSetAngle(Degree_T<f32>);

  //template Degree_T<f32>::value_type Degree_T<f32>::DoGetAs(Degree_T<f32>) const;
  //template Degree_T<f64>::value_type Degree_T<f64>::DoGetAs(Degree_T<f64>) const;

};};