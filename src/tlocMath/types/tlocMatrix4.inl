#ifndef TLOC_MATH_MATRIX_4_INL
#define TLOC_MATH_MATRIX_4_INL

#ifndef TLOC_MATH_MATRIX_4_H
#error "Must include header before including the inline file"
#endif

#include "tlocMatrix4.h"
#include <tlocMath/types/tlocVector4.inl>
#include <tlocMath/types/tlocMatrix.inl>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix4f<T>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_4_TYPES typename T
#define MATRIX_4_PARAMS T

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4()
    : base_type() {}

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4(const this_type& aMatrix)
    : base_type(aMatrix) {}

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4(const base_type& aMatrix)
    : base_type(aMatrix) {}

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>
    ::Matrix4(value_type m00, value_type m01, value_type m02, value_type m03, 
              value_type m10, value_type m11, value_type m12, value_type m13, 
              value_type m20, value_type m21, value_type m22, value_type m23, 
              value_type m30, value_type m31, value_type m32, value_type m33)
  {
    m_values[0] = m00; m_values[4] = m01; m_values[8] = m02; m_values[12] = m03;
    m_values[1] = m10; m_values[5] = m11; m_values[9] = m12; m_values[13] = m13;
    m_values[2] = m20; m_values[6] = m21; m_values[10] = m22; m_values[14] = m23;
    m_values[3] = m30; m_values[7] = m31; m_values[11] = m32; m_values[15] = m33;
  }

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4(value_type m00, 
                                          value_type m11, 
                                          value_type m22,
                                          value_type m33)
  {
    value_type diag[4] = {m00, m11, m22, m33};
    MakeDiagonal(diag);
  }

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4(const_reference aValue)
    : base_type(aValue) 
  { }

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4(const Vector<value_type, 4>& aVec1,
                                          const Vector<value_type, 4>& aVec2,
                                          const Vector<value_type, 4>& aVec3,
                                          const Vector<value_type, 4>& aVec4,
                                          typename base_type::matrix_order aOrder)
  {
    if (aOrder == base_type::k_ColMajor)
    {
      m_values[0] = aVec1[0]; m_values[4] = aVec2[0]; m_values[8] = aVec3[0];
      m_values[1] = aVec1[1]; m_values[5] = aVec2[1]; m_values[9] = aVec3[1];
      m_values[2] = aVec1[2]; m_values[6] = aVec2[2]; m_values[10] = aVec3[2];
      m_values[3] = aVec1[3]; m_values[7] = aVec2[3]; m_values[11] = aVec3[3];

      m_values[12] = aVec4[0];
      m_values[13] = aVec4[1];
      m_values[14] = aVec4[2];
      m_values[15] = aVec4[3];
    }
    else
    {
      m_values[0] = aVec1[0]; m_values[1] = aVec2[0]; m_values[2] = aVec3[0];
      m_values[4] = aVec1[1]; m_values[5] = aVec2[1]; m_values[6] = aVec3[1];
      m_values[8] = aVec1[2]; m_values[9] = aVec2[2]; m_values[10] = aVec3[2];
      m_values[12] = aVec1[3]; m_values[13] = aVec2[3]; m_values[14] = aVec3[3];

      m_values[3] = aVec4[0];
      m_values[7] = aVec4[1];
      m_values[11] = aVec4[2];
      m_values[15] = aVec4[3];
    }
  }

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4(const value_type (&values)[k_MatrixSize], 
                                          typename base_type::matrix_order aOrder)
    : base_type(values, aOrder) 
  { }

  template <MATRIX_4_TYPES>
  TL_FI Matrix4<MATRIX_4_PARAMS>::Matrix4
    (const core::data_structs::Variadic<value_type,k_MatrixSize> &a_vars, 
     matrix_order a_order)
    : base_type(a_vars, a_order)
  { }

};};};

#endif