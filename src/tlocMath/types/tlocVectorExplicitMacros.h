#ifndef _TLOC_MATH_VECTOR_EXPLICIT_MACROS_H_
#define _TLOC_MATH_VECTOR_EXPLICIT_MACROS_H_

#define TLOC_EXPLICITLY_INSTANTIATE_VECTOR(_type_, _size_)\
  template class Vector_TI<_type_, _size_>;\
  \
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoLength<p_vector::accurate>(const this_type&) const;\
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoNorm<p_vector::accurate>(const this_type&);\
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoDistance<p_vector::accurate>(const this_type&) const;\

#define TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(_type_, _size_)\
  template class Vector_TI<_type_, _size_>;\
  \
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoLength<p_vector::accurate>(const this_type&) const;\
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoNorm<p_vector::accurate>(const this_type&);\
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoDistance<p_vector::accurate>(const this_type&) const;\
  \
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoLength<p_vector::fast>(const this_type&) const;\
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoNorm<p_vector::fast>(const this_type&);\
  template Vector_TI<_type_, _size_>::value_type Vector_TI<_type_, _size_>::DoDistance<p_vector::fast>(const this_type&) const;\

#endif