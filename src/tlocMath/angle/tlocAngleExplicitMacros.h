#ifndef TLOC_MATH_ANGLE_EXPLICIT_MACROS_H
#define TLOC_MATH_ANGLE_EXPLICIT_MACROS_H

// _vt_ = value_type
// _dt_ = derived_type
// _ot_ = other_type
#define TLOC_EXPLICITLY_INSTANTIATE_ANGLE(_vt_, _dt_, _ot_)\
  template class Angle_T<_vt_, _dt_<_vt_> >;\
  \
  template Angle_T<_vt_, _dt_<_vt_> >& Angle_T<_vt_, _dt_<_vt_> >::operator= (const _dt_<_vt_>&);\
  template Angle_T<_vt_, _dt_<_vt_> >& Angle_T<_vt_, _dt_<_vt_> >::operator= (const _ot_<_vt_>&);\
  \
  template void Angle_T<_vt_, _dt_<_vt_> >::DoSetAngleCtor(_dt_<_vt_>, _dt_<_vt_>::angle_type);\
  template void Angle_T<_vt_, _dt_<_vt_> >::DoSetAngleCtor(_ot_<_vt_>, _dt_<_vt_>::angle_type);\
  \
  template _vt_ Angle_T<_vt_, _dt_<_vt_> >::GetAngleAs<_dt_<_vt_> >() const;\
  template _vt_ Angle_T<_vt_, _dt_<_vt_> >::GetAngleAs<_ot_<_vt_> >() const;\
  \
  template _dt_<_vt_>::_dt_(_dt_<_vt_>);\
  template _dt_<_vt_>::_dt_(_ot_<_vt_>);\
  \
  template _dt_<_vt_>& _dt_<_vt_>::operator= (const _dt_<_vt_>&);\
  template _dt_<_vt_>& _dt_<_vt_>::operator= (const _ot_<_vt_>&);\
  \
  template void _dt_<_vt_>::DoSetAngle(_ot_<_vt_>);\
  \
  template _dt_<_vt_>::value_type _dt_<_vt_>::DoGetAs(_ot_<_vt_>) const;

#endif