#ifndef TLOC_MATH_MATRIX_4_INL
#define TLOC_MATH_MATRIX_4_INL

#ifndef TLOC_MATH_MATRIX_4_H
#error "Must include header before including the inline file"
#endif

#include "tlocMatrix4.h"

#include <tlocCore/tlocAssert.h>

#include <tlocMath/types/tlocVector4.inl.h>
#include <tlocMath/types/tlocMatrix.inl.h>
#include <tlocMath/types/tlocMatrix3.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix_T<T>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_4_TEMPS typename T
#define MATRIX_4_PARAMS T, 4
#define MATRIX_4_TYPE typename Matrix_T<MATRIX_4_PARAMS>

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T()
    : base_type() {}

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(const this_type& aMatrix)
    : base_type(aMatrix) {}

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(const base_type& aMatrix)
    : base_type(aMatrix) {}

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(value_type m00, value_type m01, value_type m02, value_type m03,
             value_type m10, value_type m11, value_type m12, value_type m13,
             value_type m20, value_type m21, value_type m22, value_type m23,
             value_type m30, value_type m31, value_type m32, value_type m33)
  {
    m_values[0] = m00; m_values[4] = m01; m_values[8] = m02; m_values[12] = m03;
    m_values[1] = m10; m_values[5] = m11; m_values[9] = m12; m_values[13] = m13;
    m_values[2] = m20; m_values[6] = m21; m_values[10] = m22; m_values[14] = m23;
    m_values[3] = m30; m_values[7] = m31; m_values[11] = m32; m_values[15] = m33;
  }

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(value_type m00, value_type m11, value_type m22, value_type m33)
  {
    value_type diag[4] = {m00, m11, m22, m33};
    MakeDiagonal(diag);
  }

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(const_reference aValue)
    : base_type(aValue)
  { }

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(const Vector_T<value_type, 4>& aVec1,
             const Vector_T<value_type, 4>& aVec2,
             const Vector_T<value_type, 4>& aVec3,
             const Vector_T<value_type, 4>& aVec4,
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

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(const value_type (&values)[k_MatrixSize],
            typename base_type::matrix_order aOrder)
    : base_type(values, aOrder)
  { }

  template <MATRIX_4_TEMPS>
  Matrix_T<MATRIX_4_PARAMS>::
    Matrix_T(const core::data_structs::Variadic<value_type,k_MatrixSize> &a_vars,
              matrix_order a_order)
    : base_type(a_vars, a_order)
  { }

  template <MATRIX_4_TEMPS>
  MATRIX_4_TYPE::this_type
  Matrix_T<MATRIX_4_PARAMS>::
    Adjoint() const
  {
    this_type   adj;

    adj[0] = m_values[5]  * m_values[10] * m_values[15] -
             m_values[5]  * m_values[11] * m_values[14] -
             m_values[9]  * m_values[6]  * m_values[15] +
             m_values[9]  * m_values[7]  * m_values[14] +
             m_values[13] * m_values[6]  * m_values[11] -
             m_values[13] * m_values[7]  * m_values[10];

    adj[4] = -m_values[4]  * m_values[10] * m_values[15] +
              m_values[4]  * m_values[11] * m_values[14] +
              m_values[8]  * m_values[6]  * m_values[15] -
              m_values[8]  * m_values[7]  * m_values[14] -
              m_values[12] * m_values[6]  * m_values[11] +
              m_values[12] * m_values[7]  * m_values[10];

    adj[8] = m_values[4]  * m_values[9] * m_values[15] -
             m_values[4]  * m_values[11] * m_values[13] -
             m_values[8]  * m_values[5] * m_values[15] +
             m_values[8]  * m_values[7] * m_values[13] +
             m_values[12] * m_values[5] * m_values[11] -
             m_values[12] * m_values[7] * m_values[9];

    adj[12] = -m_values[4]  * m_values[9] * m_values[14] +
               m_values[4]  * m_values[10] * m_values[13] +
               m_values[8]  * m_values[5] * m_values[14] -
               m_values[8]  * m_values[6] * m_values[13] -
               m_values[12] * m_values[5] * m_values[10] +
               m_values[12] * m_values[6] * m_values[9];

    adj[1] = -m_values[1]  * m_values[10] * m_values[15] +
              m_values[1]  * m_values[11] * m_values[14] +
              m_values[9]  * m_values[2] * m_values[15] -
              m_values[9]  * m_values[3] * m_values[14] -
              m_values[13] * m_values[2] * m_values[11] +
              m_values[13] * m_values[3] * m_values[10];

    adj[5] = m_values[0]  * m_values[10] * m_values[15] -
             m_values[0]  * m_values[11] * m_values[14] -
             m_values[8]  * m_values[2] * m_values[15] +
             m_values[8]  * m_values[3] * m_values[14] +
             m_values[12] * m_values[2] * m_values[11] -
             m_values[12] * m_values[3] * m_values[10];

    adj[9] = -m_values[0]  * m_values[9] * m_values[15] +
              m_values[0]  * m_values[11] * m_values[13] +
              m_values[8]  * m_values[1] * m_values[15] -
              m_values[8]  * m_values[3] * m_values[13] -
              m_values[12] * m_values[1] * m_values[11] +
              m_values[12] * m_values[3] * m_values[9];

    adj[13] = m_values[0]  * m_values[9] * m_values[14] -
              m_values[0]  * m_values[10] * m_values[13] -
              m_values[8]  * m_values[1] * m_values[14] +
              m_values[8]  * m_values[2] * m_values[13] +
              m_values[12] * m_values[1] * m_values[10] -
              m_values[12] * m_values[2] * m_values[9];

    adj[2] = m_values[1]  * m_values[6] * m_values[15] -
             m_values[1]  * m_values[7] * m_values[14] -
             m_values[5]  * m_values[2] * m_values[15] +
             m_values[5]  * m_values[3] * m_values[14] +
             m_values[13] * m_values[2] * m_values[7] -
             m_values[13] * m_values[3] * m_values[6];

    adj[6] = -m_values[0]  * m_values[6] * m_values[15] +
              m_values[0]  * m_values[7] * m_values[14] +
              m_values[4]  * m_values[2] * m_values[15] -
              m_values[4]  * m_values[3] * m_values[14] -
              m_values[12] * m_values[2] * m_values[7] +
              m_values[12] * m_values[3] * m_values[6];

    adj[10] = m_values[0]  * m_values[5] * m_values[15] -
              m_values[0]  * m_values[7] * m_values[13] -
              m_values[4]  * m_values[1] * m_values[15] +
              m_values[4]  * m_values[3] * m_values[13] +
              m_values[12] * m_values[1] * m_values[7] -
              m_values[12] * m_values[3] * m_values[5];

    adj[14] = -m_values[0]  * m_values[5] * m_values[14] +
               m_values[0]  * m_values[6] * m_values[13] +
               m_values[4]  * m_values[1] * m_values[14] -
               m_values[4]  * m_values[2] * m_values[13] -
               m_values[12] * m_values[1] * m_values[6] +
               m_values[12] * m_values[2] * m_values[5];

    adj[3] = -m_values[1] * m_values[6] * m_values[11] +
              m_values[1] * m_values[7] * m_values[10] +
              m_values[5] * m_values[2] * m_values[11] -
              m_values[5] * m_values[3] * m_values[10] -
              m_values[9] * m_values[2] * m_values[7] +
              m_values[9] * m_values[3] * m_values[6];

    adj[7] = m_values[0] * m_values[6] * m_values[11] -
             m_values[0] * m_values[7] * m_values[10] -
             m_values[4] * m_values[2] * m_values[11] +
             m_values[4] * m_values[3] * m_values[10] +
             m_values[8] * m_values[2] * m_values[7] -
             m_values[8] * m_values[3] * m_values[6];

    adj[11] = -m_values[0] * m_values[5] * m_values[11] +
               m_values[0] * m_values[7] * m_values[9] +
               m_values[4] * m_values[1] * m_values[11] -
               m_values[4] * m_values[3] * m_values[9] -
               m_values[8] * m_values[1] * m_values[7] +
               m_values[8] * m_values[3] * m_values[5];

    adj[15] = m_values[0] * m_values[5] * m_values[10] -
              m_values[0] * m_values[6] * m_values[9] -
              m_values[4] * m_values[1] * m_values[10] +
              m_values[4] * m_values[2] * m_values[9] +
              m_values[8] * m_values[1] * m_values[6] -
              m_values[8] * m_values[2] * m_values[5];

    return adj;
  }

  template <MATRIX_4_TEMPS>
  MATRIX_4_TYPE::this_type
    Matrix_T<MATRIX_4_PARAMS>::
    Invert() const
  {
    this_type   inv;
    value_type  det;

    inv = Adjoint();

    // quicker than calling our Determinant() method
    det = m_values[0] * inv[0] + m_values[1] * inv[4] +
          m_values[2] * inv[8] + m_values[3] * inv[12];

    TLOC_ASSERT_LOW_LEVEL(tloc::math::IsEqual<value_type>(det, 0) == false,
      "Determinant is zero (will result in divide by zero)!");

    det = 1.0f / det;

    for (tl_int i = 0; i < 16; ++i)
    { inv[i] *= det; }

    return inv;
  }

  template <MATRIX_4_TEMPS>
  MATRIX_4_TYPE::value_type
    Matrix_T<MATRIX_4_PARAMS>::
    Determinant() const
  {
    // the numbers denote the index of matrix (see Inverse() for further
    // details)
    value_type inv0, inv4, inv8, inv12;

    inv0 = m_values[5]  * m_values[10] * m_values[15] -
           m_values[5]  * m_values[11] * m_values[14] -
           m_values[9]  * m_values[6]  * m_values[15] +
           m_values[9]  * m_values[7]  * m_values[14] +
           m_values[13] * m_values[6]  * m_values[11] -
           m_values[13] * m_values[7]  * m_values[10];

    inv4 = -m_values[4]  * m_values[10] * m_values[15] +
            m_values[4]  * m_values[11] * m_values[14] +
            m_values[8]  * m_values[6]  * m_values[15] -
            m_values[8]  * m_values[7]  * m_values[14] -
            m_values[12] * m_values[6]  * m_values[11] +
            m_values[12] * m_values[7]  * m_values[10];

    inv8 = m_values[4]  * m_values[9] * m_values[15] -
           m_values[4]  * m_values[11] * m_values[13] -
           m_values[8]  * m_values[5] * m_values[15] +
           m_values[8]  * m_values[7] * m_values[13] +
           m_values[12] * m_values[5] * m_values[11] -
           m_values[12] * m_values[7] * m_values[9];

    inv12 = -m_values[4]  * m_values[9] * m_values[14] +
             m_values[4]  * m_values[10] * m_values[13] +
             m_values[8]  * m_values[5] * m_values[14] -
             m_values[8]  * m_values[6] * m_values[13] -
             m_values[12] * m_values[5] * m_values[10] +
             m_values[12] * m_values[6] * m_values[9];

    return m_values[0] * inv0 + m_values[1] * inv4 +
           m_values[2] * inv8 + m_values[3] * inv12;
  }

  template <MATRIX_4_TEMPS>
  MATRIX_4_TYPE::this_type
    Matrix_T<MATRIX_4_PARAMS>::
    DoInvert(p_matrix4::NonAffine) const
  {
    return Invert();
  }

  template <MATRIX_4_TEMPS>
  MATRIX_4_TYPE::this_type
    Matrix_T<MATRIX_4_PARAMS>::
    DoInvert(p_matrix4::Affine) const
  {
    // from: http://stackoverflow.com/a/2625420/368599
    //adj(A) = [ inv(M)   -inv(M) * b ]
    //         [   0            1     ]

    this_type toRet(*this);

    Matrix_T<value_type, 3> orientationPart (toRet[0], toRet[4], toRet[8], 
                                             toRet[1], toRet[5], toRet[9], 
                                             toRet[2], toRet[6], toRet[10]);

    Vector_T<value_type, 3>  vectorPart(toRet[12], toRet[13], toRet[14]);

    orientationPart = orientationPart.Inverse();
    vectorPart      = orientationPart * vectorPart.Inverse();

    toRet[0] = orientationPart[0];
    toRet[1] = orientationPart[1];
    toRet[2] = orientationPart[2];
    toRet[4] = orientationPart[3];
    toRet[5] = orientationPart[4];
    toRet[6] = orientationPart[5];
    toRet[8] = orientationPart[6];
    toRet[9] = orientationPart[7];
    toRet[10] = orientationPart[8];

    toRet[12] = vectorPart[0];
    toRet[13] = vectorPart[1];
    toRet[14] = vectorPart[2];

    return toRet;
  }

};};};

#endif