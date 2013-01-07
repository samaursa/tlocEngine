#ifndef TLOC_MATRIX_2_INL
#define TLOC_MATRIX_2_INL

#ifndef TLOC_MATRIX_2_H
#error "Must include header before including the inline file"
#endif

#include <tlocMath/types/tlocVector2.inl>
#include <tlocMath/types/tlocMatrix.inl>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix2f<T>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_2_TYPES typename T
#define MATRIX_2_PARAMS T

  //------------------------------------------------------------------------
  // Constructors

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2()
    : base_type() 
  { }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2(const this_type& aMatrix)
    : base_type(aMatrix) 
  { }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2(const base_type& aMatrix)
    : base_type(aMatrix) 
  { }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2(value_type m00, value_type m01,
                                          value_type m10, value_type m11)
  {
    m_values[0] = m00;
    m_values[1] = m10;
    m_values[2] = m01;
    m_values[3] = m11;
  }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2(value_type m00, value_type m11)
  {
    T diag[2] = {m00, m11};
    MakeDiagonal(diag);
  }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2(const_reference aValue)
    : base_type(aValue) {}

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>::Matrix2(const Vector2<value_type>& aVec1, 
                                          const Vector2<value_type>& aVec2,
                                          typename base_type::matrix_order aOrder)
  {
    if (aOrder == base_type::k_ColMajor)
    {
      m_values[0] = aVec1[0];
      m_values[1] = aVec1[1];
      m_values[2] = aVec2[0];
      m_values[3] = aVec2[1];
    }
    else
    {
      m_values[0] = aVec1[0];
      m_values[2] = aVec1[1];
      m_values[1] = aVec2[0];
      m_values[3] = aVec2[1];
    }
  }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>
    ::Matrix2(const value_type (&values)[k_MatrixSize], matrix_order aOrder)
    : base_type(values, aOrder) 
  { }

  template <MATRIX_2_TYPES>
  TL_FI Matrix2<MATRIX_2_PARAMS>
    ::Matrix2(const tloc::core::Variadic<value_type, 4>& a_vars, 
              matrix_order a_order) 
              : base_type(a_vars, a_order)
  { }

  //------------------------------------------------------------------------
  // Math Operations

  template <MATRIX_2_TYPES>
  TL_FI typename Matrix2<MATRIX_2_PARAMS>::this_type& 
    Matrix2<MATRIX_2_PARAMS>::Mul(const this_type& aMatrix)
  {
    this_type temp(*this);
    Mul(temp, aMatrix);

    return *this;
  }

  template <MATRIX_2_TYPES>
  TL_FI void Matrix2<MATRIX_2_PARAMS>::Mul(const this_type& aMatrix1,
                                           const this_type& aMatrix2)
  {
    m_values[0] = (aMatrix1[0] * aMatrix2[0]) + (aMatrix1[2] * aMatrix2[1]);
    m_values[2] = (aMatrix1[1] * aMatrix2[0]) + (aMatrix1[3] * aMatrix2[1]);
    m_values[1] = (aMatrix1[0] * aMatrix2[2]) + (aMatrix1[2] * aMatrix2[3]);
    m_values[3] = (aMatrix1[1] * aMatrix2[2]) + (aMatrix1[3] * aMatrix2[3]);
  }

  template <MATRIX_2_TYPES>
  TL_FI void Matrix2<MATRIX_2_PARAMS>::Mul(const Vector2<value_type>& aVectorIn,
                                           Vector2<value_type>& aVectorOut) const
  {
    aVectorOut[0] = (m_values[0] * aVectorIn[0]) + (m_values[2] * aVectorIn[1]);
    aVectorOut[1] = (m_values[1] * aVectorIn[0]) + (m_values[3] * aVectorIn[1]);
  }

  template <MATRIX_2_TYPES>
  TL_FI typename Matrix2<MATRIX_2_PARAMS>::value_type 
    Matrix2<MATRIX_2_PARAMS>::Determinant() const
  {
    return (m_values[0] * m_values[3]) - (m_values[2] * m_values[1]);
  }

  template <MATRIX_2_TYPES>
  TL_FI bool Matrix2<MATRIX_2_PARAMS>::Inverse()
  {
    this_type temp(*this);
    return Inverse(temp);
  }

  template <MATRIX_2_TYPES>
  TL_FI bool Matrix2<MATRIX_2_PARAMS>::Inverse(const this_type& aMatrix)
  {
    T detInv = ((T)1) / aMatrix.Determinant();

    if (Math<T>::Approx(detInv, (T)0)) { return false; }

    m_values[0] = aMatrix[3] * detInv;
    m_values[1] = -aMatrix[1] * detInv;
    m_values[2] = -aMatrix[2] * detInv;
    m_values[3] = aMatrix[0] * detInv;

    return true;
  }

  template <MATRIX_2_TYPES>
  TL_FI typename Matrix2<MATRIX_2_PARAMS>::this_type& 
    Matrix2<MATRIX_2_PARAMS>::Adjoint()
  {
    this_type temp(*this);
    Adjoint(temp);

    return *this;
  }

  template <MATRIX_2_TYPES>
  TL_FI void Matrix2<MATRIX_2_PARAMS>::Adjoint(const this_type& aMatrix)
  {
    m_values[0] = aMatrix[3];
    m_values[1] = -aMatrix[1];
    m_values[2] = -aMatrix[2];
    m_values[3] = aMatrix[0];
  }

  // Taken directly from WildMagic5 (modified to suit out needs)
  template <MATRIX_2_TYPES>
  TL_FI typename Matrix2<MATRIX_2_PARAMS>::this_type& 
    Matrix2<MATRIX_2_PARAMS>::Orthonormalize()
  {
    value_type invLength = Math<value_type>::InvSqrt(m_values[0] * m_values[0] +
      m_values[1] * m_values[1]);
    m_values[0] *= invLength;
    m_values[1] *= invLength;

    // Compute q1
    value_type dot0 = (m_values[0] * m_values[2]) + (m_values[1] * m_values[3]);
    m_values[2] -= dot0 * m_values[0];
    m_values[3] -= dot0 * m_values[2];

    invLength = Math<value_type>::InvSqrt(m_values[2] * m_values[2] +
      m_values[3] * m_values[3]);

    m_values[2] *= invLength;
    m_values[3] *= invLength;

    return *this;
  }

  template <MATRIX_2_TYPES>
  TL_FI void Matrix2<MATRIX_2_PARAMS>::Orthonormalize( const this_type& aMatrix )
  {
    base_type::operator= (aMatrix);
    Orthonormalize();
  }

  template <MATRIX_2_TYPES>
  TL_FI typename Matrix2<MATRIX_2_PARAMS>::this_type& 
    Matrix2<MATRIX_2_PARAMS>::FastOrthonormalize()
  {
    value_type invLength = Math<value_type>::FastInvSqrt(m_values[0] * 
      m_values[0] + m_values[2] * m_values[2]);
    m_values[0] *= invLength;
    m_values[2] *= invLength;

    // Compute q1
    value_type dot0 = m_values[0] * m_values[1] + m_values[2] * m_values[3];
    m_values[1] -= dot0 * m_values[0];
    m_values[3] -= dot0 * m_values[2];

    invLength = Math<value_type>::FastInvSqrt(m_values[1] * m_values[1] +
                                              m_values[3] * m_values[3]);

    m_values[1] *= invLength;
    m_values[3] *= invLength;

    return *this;
  }

  template <MATRIX_2_TYPES>
  TL_FI void 
    Matrix2<MATRIX_2_PARAMS>::FastOrthonormalize( const this_type& aMatrix )
  {
    base_type::operator= (aMatrix);
    FastOrthonormalize();
  }

  template <MATRIX_2_TYPES>
  TL_FI void Matrix2<MATRIX_2_PARAMS>
    ::EigenDecomposition(this_type& aRot, this_type& aDiag) const
  {
    value_type sum = Math<value_type>::FAbs(m_values[0]) + 
      Math<value_type>::FAbs(m_values[3]);
    if (Math<value_type>::FAbs(m_values[2]) + sum == sum)
    {
      // The matrix is diagonal
      aRot[0] = (value_type)1; aRot[2] = (value_type)0;
      aRot[1] = (value_type)0; aRot[3] = (value_type)1;

      aDiag[0] = m_values[0]; aDiag[2] = (value_type)0;
      aDiag[1] = (value_type)0;        aDiag[3] = m_values[3];

      return;
    }

    value_type eigVal0and1[2];

    value_type trace = m_values[0] + m_values[3];
    value_type diff = m_values[0] - m_values[3];
    value_type discr = Math<value_type>::Sqrt(diff * diff + ((value_type)4) * 
      m_values[2] * m_values[2]);
    eigVal0and1[0] = ((value_type)0.5) * (trace - discr);
    eigVal0and1[1] = ((value_type)0.5) * (trace + discr);
    aDiag.MakeDiagonal( eigVal0and1 );

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

    aRot.m_values[0] = cs;
    aRot.m_values[1] = sn;
    aRot.m_values[2] = -sn;
    aRot.m_values[3] = cs;
  }

};};};

#endif