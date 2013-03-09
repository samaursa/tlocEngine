#ifndef _TLOC_MATH_MATRIX_EXPLICIT_MACROS_H_
#define _TLOC_MATH_MATRIX_EXPLICIT_MACROS_H_

#define TLOC_EXPLICITLY_INSTANTIATE_MATRIX(_type_, _size_)\
  template class Matrix<_type_, _size_>
#endif