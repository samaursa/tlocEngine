#ifndef _TLOC_MATH_VECTOR_EXPLICIT_MACROS_H_
#define _TLOC_MATH_VECTOR_EXPLICIT_MACROS_H_

#define TLOC_EXPLICITLY_INSTANTIATE_VECTOR(_type_, _size_)\
  template class Vector<_type_, _size_>;\
  \
  template Vector<_type_, _size_>::value_type Vector<_type_, _size_>::DoLength<p_vector::accurate>(const this_type&) const;\
  template Vector<_type_, _size_>::value_type Vector<_type_, _size_>::DoNorm<p_vector::accurate>(const this_type&);\
  template Vector<_type_, _size_>::value_type Vector<_type_, _size_>::DoDistance<p_vector::accurate>(const this_type&) const;\

#endif