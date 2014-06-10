#ifndef TLOC_MATRIX_2_INL
#define TLOC_MATRIX_2_INL

#ifndef TLOC_MATRIX_2_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAssert.h>
#include <tlocMath/types/tlocVector2.inl.h>
#include <tlocMath/types/tlocMatrix.inl.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix_T<T>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_2_TEMPS typename T
#define MATRIX_2_PARAMS T, 2
#define MATRIX_2_TYPE  typename Matrix_T<MATRIX_2_PARAMS>

  //------------------------------------------------------------------------
  // Constructors

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T()
    : base_type()
  { }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(const this_type& a_matrix)
    : base_type(a_matrix)
  { }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(const base_type& a_matrix)
    : base_type(a_matrix)
  { }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(value_type m00, value_type m01,
            value_type m10, value_type m11)
  {
    m_values[0] = m00;
    m_values[1] = m10;
    m_values[2] = m01;
    m_values[3] = m11;
  }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(value_type m00, value_type m11)
  {
    T diag[2] = {m00, m11};
    MakeDiagonal(diag);
  }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(const_reference aValue)
    : base_type(aValue) {}

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(const Vector_T<value_type, 2>& a_vec1,
            const Vector_T<value_type, 2>& a_vec2,
            typename base_type::matrix_order aOrder)
  {
    if (aOrder == base_type::k_ColMajor)
    {
      m_values[0] = a_vec1[0];
      m_values[1] = a_vec1[1];
      m_values[2] = a_vec2[0];
      m_values[3] = a_vec2[1];
    }
    else
    {
      m_values[0] = a_vec1[0];
      m_values[2] = a_vec1[1];
      m_values[1] = a_vec2[0];
      m_values[3] = a_vec2[1];
    }
  }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(const value_type (&values)[k_MatrixSize], matrix_order aOrder)
    : base_type(values, aOrder)
  { }

  template <MATRIX_2_TEMPS>
  Matrix_T<MATRIX_2_PARAMS>::
    Matrix_T(const tloc::core::data_structs::Variadic<value_type, 4>& a_vars,
            matrix_order a_order)
    : base_type(a_vars, a_order)
  { }

  //------------------------------------------------------------------------
  // Math Operations

  template <MATRIX_2_TEMPS>
  MATRIX_2_TYPE::value_type
    Matrix_T<MATRIX_2_PARAMS>::
    Determinant() const
  {
    return (m_values[0] * m_values[3]) - (m_values[2] * m_values[1]);
  }

  template <MATRIX_2_TEMPS>
  MATRIX_2_TYPE::this_type
    Matrix_T<MATRIX_2_PARAMS>::
    Inverse() const
  {
    this_type temp;
    temp.Inverse(*this);
    return temp;
  }

  template <MATRIX_2_TEMPS>
  void
    Matrix_T<MATRIX_2_PARAMS>::
    Inverse(const this_type& a_matrix)
  {
    value_type detInv = a_matrix.Determinant();

    TLOC_ASSERT_LOW_LEVEL
      (Math<value_type>::IsEqual(detInv, 0.0f) == false, "Divide by zero!");
    detInv = ((value_type)1) / detInv;

    m_values[0] =  a_matrix[3] * detInv;
    m_values[1] = -a_matrix[1] * detInv;
    m_values[2] = -a_matrix[2] * detInv;
    m_values[3] =  a_matrix[0] * detInv;
  }

  template <MATRIX_2_TEMPS>
  typename Matrix_T<MATRIX_2_PARAMS>::this_type
    Matrix_T<MATRIX_2_PARAMS>::
    Adjoint() const
  {
    this_type temp;
    temp.Adjoint(*this);

    return temp;
  }

  template <MATRIX_2_TEMPS>
  void Matrix_T<MATRIX_2_PARAMS>::
    Adjoint(const this_type& a_matrix)
  {
    m_values[0] = a_matrix[3];
    m_values[1] = -a_matrix[1];
    m_values[2] = -a_matrix[2];
    m_values[3] = a_matrix[0];
  }

  // Taken directly from WildMagic5 (modified to suit out needs)
  template <MATRIX_2_TEMPS>
  typename Matrix_T<MATRIX_2_PARAMS>::this_type
    Matrix_T<MATRIX_2_PARAMS>::
    Orthonormalize() const
  {
    this_type temp(*this);

    value_type invLength =
      Math<value_type>::InvSqrt(temp.m_values[0] * temp.m_values[0] +
                                temp.m_values[1] * temp.m_values[1]);
    temp.m_values[0] *= invLength;
    temp.m_values[1] *= invLength;

    // Compute q1
    value_type dot0 = (temp.m_values[0] * temp.m_values[2]) +
                      (temp.m_values[1] * temp.m_values[3]);
    temp.m_values[2] -= dot0 * temp.m_values[0];
    temp.m_values[3] -= dot0 * temp.m_values[2];

    invLength =
      Math<value_type>::InvSqrt(temp.m_values[2] * temp.m_values[2] +
                                temp.m_values[3] * temp.m_values[3]);

    temp.m_values[2] *= invLength;
    temp.m_values[3] *= invLength;

    return temp;
  }

  template <MATRIX_2_TEMPS>
  void Matrix_T<MATRIX_2_PARAMS>::
    Orthonormalize( const this_type& a_matrix )
  {
    *this = a_matrix.Orthonormalize();
  }

  template <MATRIX_2_TEMPS>
  typename Matrix_T<MATRIX_2_PARAMS>::this_type
    Matrix_T<MATRIX_2_PARAMS>::
    FastOrthonormalize() const
  {
    this_type temp(*this);

    value_type invLength =
      Math<value_type>::FastInvSqrt( (temp.m_values[0] * temp.m_values[0]) +
                                     (temp.m_values[2] * temp.m_values[2]) );
    temp.m_values[0] *= invLength;
    temp.m_values[2] *= invLength;

    // Compute q1
    value_type dot0 = (temp.m_values[0] * temp.m_values[1]) +
                      (temp.m_values[2] * temp.m_values[3]);
    temp.m_values[1] -= dot0 * temp.m_values[0];
    temp.m_values[3] -= dot0 * temp.m_values[2];

    invLength =
      Math<value_type>::FastInvSqrt(temp.m_values[1] * temp.m_values[1] +
                                    temp.m_values[3] * temp.m_values[3]);

    temp.m_values[1] *= invLength;
    temp.m_values[3] *= invLength;

    return *this;
  }

  template <MATRIX_2_TEMPS>
  void
    Matrix_T<MATRIX_2_PARAMS>::
    FastOrthonormalize( const this_type& a_matrix )
  {
    *this = a_matrix.FastOrthonormalize();
  }

  template <MATRIX_2_TEMPS>
  void Matrix_T<MATRIX_2_PARAMS>::
    EigenDecomposition(this_type& a_rot, this_type& a_diag) const
  {
    value_type sum = Math<value_type>::FAbs(m_values[0]) +
      Math<value_type>::FAbs(m_values[3]);
    if (Math<value_type>::FAbs(m_values[2]) + sum == sum)
    {
      // The matrix is diagonal
      a_rot[0] = (value_type)1; a_rot[2] = (value_type)0;
      a_rot[1] = (value_type)0; a_rot[3] = (value_type)1;

      a_diag[0] = m_values[0]; a_diag[2] = (value_type)0;
      a_diag[1] = (value_type)0;        a_diag[3] = m_values[3];

      return;
    }

    value_type eigVal0and1[2];

    value_type trace = m_values[0] + m_values[3];
    value_type diff = m_values[0] - m_values[3];
    value_type discr = Math<value_type>::Sqrt(diff * diff + ((value_type)4) *
      m_values[2] * m_values[2]);
    eigVal0and1[0] = ((value_type)0.5) * (trace - discr);
    eigVal0and1[1] = ((value_type)0.5) * (trace + discr);
    a_diag.MakeDiagonal( eigVal0and1 );

    value_type cs, sn;
    if (diff >= (value_type)0)
    {
      cs = m_values[2];
      sn = eigVal0and1[0] - m_values[0];
    }
    else
    {
      cs = eigVal0and1[0] - m_values[3];
      sn = m_values[2];
    }

    value_type invLength = Math<value_type>::InvSqrt(cs * cs + sn * sn);
    cs *= invLength;
    sn *= invLength;

    a_rot.m_values[0] = cs;
    a_rot.m_values[1] = sn;
    a_rot.m_values[2] = -sn;
    a_rot.m_values[3] = cs;
  }

};};};

#endif