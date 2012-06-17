#ifndef TLOC_MATRIX_3_INL
#define TLOC_MATRIX_3_INL

#ifndef TLOC_MATRIX_3_H
#error "Must include header before including the inline file"
#endif

#include <tlocMath/vector/tlocVector3.inl>
#include <tlocMath/matrix/tlocMatrix.inl>

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Matrix3f<T>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_3_TYPES typename T
#define MATRIX_3_PARAMS T

  //------------------------------------------------------------------------
  // Constructors

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>::Matrix3()
    : base_type() {}

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>::Matrix3(const this_type& aMatrix)
    : base_type(aMatrix) {}

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>
    ::Matrix3(value_type m00, value_type m01, value_type m02,
              value_type m10, value_type m11, value_type m12,
              value_type m20, value_type m21, value_type m22)
  {
    m_values[0] = m00; m_values[3] = m01; m_values[6] = m02;
    m_values[1] = m10; m_values[4] = m11; m_values[7] = m12;
    m_values[2] = m20; m_values[5] = m21; m_values[8] = m22;
  }

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>::Matrix3(value_type m00, 
                                          value_type m11, 
                                          value_type m22)
  {
    value_type diag[3] = {m00, m11, m22};
    MakeDiagonal(diag);
  }

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>::Matrix3(const_reference aValue)
    : base_type(aValue) {}

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>::Matrix3(const Vector<value_type, 3>& aVec1,
                                          const Vector<value_type, 3>& aVec2,
                                          const Vector<value_type, 3>& aVec3,
                                          typename base_type::matrix_order aOrder)
  {
    if (aOrder == base_type::k_ColMajor)
    {
      m_values[0] = aVec1[0]; m_values[3] = aVec2[0]; m_values[6] = aVec3[0];
      m_values[1] = aVec1[1]; m_values[4] = aVec2[1]; m_values[7] = aVec3[1];
      m_values[2] = aVec1[2]; m_values[5] = aVec2[2]; m_values[8] = aVec3[2];
    }
    else
    {
      m_values[0] = aVec1[0]; m_values[1] = aVec2[0]; m_values[2] = aVec3[0];
      m_values[3] = aVec1[1]; m_values[4] = aVec2[1]; m_values[5] = aVec3[1];
      m_values[6] = aVec1[2]; m_values[7] = aVec2[2]; m_values[8] = aVec3[2];
    }
  }

  template <MATRIX_3_TYPES>
  TL_FI Matrix3<MATRIX_3_PARAMS>::Matrix3(const value_type (&values)[k_MatrixSize], 
                                          typename base_type::matrix_order aOrder)
    : base_type(values, aOrder) {}

  //------------------------------------------------------------------------
  // Math Operations

  template <MATRIX_3_TYPES>
  TL_FI typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::Mul(const this_type& aMatrix)
  {
    this_type temp(*this);
    Mul(temp, aMatrix);

    return *this;
  }

  template <MATRIX_3_TYPES>
  TL_FI void Matrix3<MATRIX_3_PARAMS>::Mul(const this_type& aMatrix1,
                                           const this_type& aMatrix2)
  {
    m_values[0] = aMatrix1[0] * aMatrix2[0] +
                  aMatrix1[3] * aMatrix2[1] +
                  aMatrix1[6] * aMatrix2[2];
    m_values[1] = aMatrix1[1] * aMatrix2[0] +
                  aMatrix1[4] * aMatrix2[1] +
                  aMatrix1[7] * aMatrix2[2];
    m_values[2] = aMatrix1[2] * aMatrix2[0] +
                  aMatrix1[5] * aMatrix2[1] +
                  aMatrix1[8] * aMatrix2[2];
    m_values[3] = aMatrix1[0] * aMatrix2[3] +
                  aMatrix1[3] * aMatrix2[4] +
                  aMatrix1[6] * aMatrix2[5];
    m_values[4] = aMatrix1[1] * aMatrix2[3] +
                  aMatrix1[4] * aMatrix2[4] +
                  aMatrix1[7] * aMatrix2[5];
    m_values[5] = aMatrix1[2] * aMatrix2[3] +
                  aMatrix1[5] * aMatrix2[4] +
                  aMatrix1[8] * aMatrix2[5];
    m_values[6] = aMatrix1[0] * aMatrix2[6] +
                  aMatrix1[3] * aMatrix2[7] +
                  aMatrix1[6] * aMatrix2[8];
    m_values[7] = aMatrix1[1] * aMatrix2[6] +
                  aMatrix1[4] * aMatrix2[7] +
                  aMatrix1[7] * aMatrix2[8];
    m_values[8] = aMatrix1[2] * aMatrix2[6] +
                  aMatrix1[5] * aMatrix2[7] +
                  aMatrix1[8] * aMatrix2[8];
  }

  template <MATRIX_3_TYPES>
  TL_FI void Matrix3<MATRIX_3_PARAMS>::Mul(const Vector<value_type, 3>& aVectorIn,
                                           Vector<value_type, 3>& aVectorOut)
  {
    aVectorOut[0] = m_values[0] * aVectorIn[0] +
                    m_values[3] * aVectorIn[1] +
                    m_values[6] * aVectorIn[2];
    aVectorOut[1] = m_values[1] * aVectorIn[0] +
                    m_values[4] * aVectorIn[1] +
                    m_values[7] * aVectorIn[2];
    aVectorOut[2] = m_values[2] * aVectorIn[0] +
                    m_values[5] * aVectorIn[1] +
                    m_values[8] * aVectorIn[2];
  }

  template <MATRIX_3_TYPES>
  TL_I typename Matrix3<MATRIX_3_PARAMS>::value_type 
    Matrix3<MATRIX_3_PARAMS>::Determinant() const
  {
    value_type m11_12_21_22 = 
      (m_values[4] * m_values[8] - m_values[7] * m_values[5]) * m_values[0];
    value_type m10_12_20_22 = 
      (m_values[1] * m_values[8] - m_values[7] * m_values[2]) * m_values[3];
    value_type m10_11_20_21 = 
      (m_values[1] * m_values[5] - m_values[4] * m_values[2]) * m_values[6];

    return m11_12_21_22 - m10_12_20_22 + m10_11_20_21;
  }

  template <MATRIX_3_TYPES>
  TL_I bool Matrix3<MATRIX_3_PARAMS>::Inverse()
  {
    this_type temp(*this);
    return Inverse(temp);
  }

  template <MATRIX_3_TYPES>
  TL_I bool Matrix3<MATRIX_3_PARAMS>::Inverse(const this_type& aMatrix)
  {
    value_type detInv = aMatrix.Determinant();
    if (Math<value_type>::Approx(detInv, (value_type)0)) { return false; }

    detInv = ((value_type)1) / detInv;

    Adjoint(aMatrix);
    base_type::Mul(detInv);

    return true;
  }

  template <MATRIX_3_TYPES>
  TL_I typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::Adjoint()
  {
    this_type temp(*this);
    Adjoint(temp);

    return *this;
  }

  template <MATRIX_3_TYPES>
  TL_I void Matrix3<MATRIX_3_PARAMS>::Adjoint(const this_type& aMatrix)
  {
    // Matrix adjoint which is the matrix of minors turned into matrix of
    // co-factors which is then transposed
    m_values[0] = aMatrix[4] * aMatrix[8] - aMatrix[7] * aMatrix[5]; // +
    m_values[3] = aMatrix[6] * aMatrix[5] - aMatrix[3] * aMatrix[8]; // -
    m_values[6] = aMatrix[3] * aMatrix[7] - aMatrix[6] * aMatrix[4]; // +
    m_values[1] = aMatrix[7] * aMatrix[2] - aMatrix[1] * aMatrix[8]; // -
    m_values[4] = aMatrix[0] * aMatrix[8] - aMatrix[6] * aMatrix[2]; // +
    m_values[7] = aMatrix[1] * aMatrix[6] - aMatrix[0] * aMatrix[7]; // -
    m_values[2] = aMatrix[1] * aMatrix[5] - aMatrix[4] * aMatrix[2]; // +
    m_values[5] = aMatrix[3] * aMatrix[2] - aMatrix[0] * aMatrix[5]; // -
    m_values[8] = aMatrix[0] * aMatrix[4] - aMatrix[3] * aMatrix[1]; // +
  }

  // Taken directly from WildMagic5 (modified to suit out needs)
  template <MATRIX_3_TYPES>
  TL_FI typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::Orthonormalize()
  {
    // Copied from WildMagic5

    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // Compute q0.
    value_type invLength = 
      Math<value_type>::InvSqrt(m_values[0] * m_values[0] +
                                m_values[1] * m_values[1] +
                                m_values[2] * m_values[2]);

    m_values[0] *= invLength;
    m_values[1] *= invLength;
    m_values[2] *= invLength;

    // Compute q1.
    value_type dot0 = m_values[0] * m_values[3] +
                      m_values[1] * m_values[4] +
                      m_values[2] * m_values[5];

    m_values[3] -= dot0 * m_values[0];
    m_values[4] -= dot0 * m_values[1];
    m_values[5] -= dot0 * m_values[2];

    invLength = Math<value_type>::InvSqrt(m_values[3] * m_values[3] +
                                          m_values[4] * m_values[4] +
                                          m_values[5] * m_values[5]);

    m_values[3] *= invLength;
    m_values[4] *= invLength;
    m_values[5] *= invLength;

    // compute q2
    value_type dot1 = m_values[3] * m_values[6] +
                      m_values[4] * m_values[7] +
                      m_values[5] * m_values[8];

    dot0 = m_values[0] * m_values[6] +
           m_values[1] * m_values[7] +
           m_values[2] * m_values[8];

    m_values[6] -= dot0 * m_values[0] + dot1 * m_values[3];
    m_values[7] -= dot0 * m_values[1] + dot1 * m_values[4];
    m_values[8] -= dot0 * m_values[2] + dot1 * m_values[5];

    invLength = Math<value_type>::InvSqrt(m_values[6] * m_values[6] +
                                          m_values[7] * m_values[7] +
                                          m_values[8] * m_values[8]);

    m_values[6] *= invLength;
    m_values[7] *= invLength;
    m_values[8] *= invLength;

    return *this;
  }

  template <MATRIX_3_TYPES>
  TL_FI void Matrix3<MATRIX_3_PARAMS>::Orthonormalize( const this_type& aMatrix )
  {
    *this = aMatrix;
    Orthonormalize();
  }

  template <MATRIX_3_TYPES>
  TL_FI typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::FastOrthonormalize()
  {
    // Copied from WildMagic5

    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // Compute q0.
    value_type invLength = 
      Math<value_type>::FastInvSqrt(m_values[0] * m_values[0] +
                                    m_values[1] * m_values[1] +
                                    m_values[2] * m_values[2]);

    m_values[0] *= invLength;
    m_values[1] *= invLength;
    m_values[2] *= invLength;

    // Compute q1.
    value_type dot0 = m_values[0] * m_values[3] +
                      m_values[1] * m_values[4] +
                      m_values[2] * m_values[5];

    m_values[3] -= dot0 * m_values[0];
    m_values[4] -= dot0 * m_values[1];
    m_values[5] -= dot0 * m_values[2];

    invLength = Math<value_type>::FastInvSqrt(m_values[3] * m_values[3] +
                                              m_values[4] * m_values[4] +
                                              m_values[5] * m_values[5]);

    m_values[3] *= invLength;
    m_values[4] *= invLength;
    m_values[5] *= invLength;

    // compute q2
    value_type dot1 = m_values[3] * m_values[6] +
                      m_values[4] * m_values[7] +
                      m_values[5] * m_values[8];

    dot0 = m_values[0] * m_values[6] +
           m_values[1] * m_values[7] +
           m_values[2] * m_values[8];

    m_values[6] -= dot0 * m_values[0] + dot1 * m_values[3];
    m_values[7] -= dot0 * m_values[1] + dot1 * m_values[4];
    m_values[8] -= dot0 * m_values[2] + dot1 * m_values[5];

    invLength = Math<value_type>::FastInvSqrt(m_values[6] * m_values[6] +
                                              m_values[7] * m_values[7] +
                                              m_values[8] * m_values[8]);

    m_values[6] *= invLength;
    m_values[7] *= invLength;
    m_values[8] *= invLength;

    return *this;
  }

  template <MATRIX_3_TYPES>
  TL_FI void 
    Matrix3<MATRIX_3_PARAMS>::FastOrthonormalize( const this_type& aMatrix )
  {
    *this = aMatrix;
    FastOrthonormalize();
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::
    EigenDecomposition(this_type& aRot, this_type& aDiag) const
  {
    // Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
    // diagonal entries of D are the corresponding eigenvalues.
    value_type diagonal[3], subdiagonal[2];
    aRot = *this;
    bool reflection = aRot.Tridiagonalize(diagonal, subdiagonal);
    bool converged = aRot.QLAlgorithm(diagonal, subdiagonal);
    TLOC_ASSERT(converged, "QLAlgorithm failed to converge\n");
    TLOC_UNUSED(converged);

    // Sort the eigenvalues in increasing order, d0 <= d1 <= d2.  This is an
    // insertion sort.
    int i;
    value_type save;

    if (diagonal[1] < diagonal[0])
    {
      // Swap d0 and d1.
      save = diagonal[0];
      diagonal[0] = diagonal[1];
      diagonal[1] = save;

      // Swap V0 and V1.
      for (i = 0; i < 3; ++i)
      {
        save = aRot(i,0);
        aRot(i,0) = aRot(i,1);
        aRot(i,1) = save;
      }
      reflection = !reflection;
    }

    if (diagonal[2] < diagonal[1])
    {
      // Swap d1 and d2.
      save = diagonal[1];
      diagonal[1] = diagonal[2];
      diagonal[2] = save;

      // Swap V1 and V2.
      for (i = 0; i < 3; ++i)
      {
        save = aRot(i,1);
        aRot(i,1) = aRot(i,2);
        aRot(i,2) = save;
      }
      reflection = !reflection;
    }

    if (diagonal[1] < diagonal[0])
    {
      // Swap d0 and d1.
      save = diagonal[0];
      diagonal[0] = diagonal[1];
      diagonal[1] = save;

      // Swap V0 and V1.
      for (i = 0; i < 3; ++i)
      {
        save = aRot(i,0);
        aRot(i,0) = aRot(i,1);
        aRot(i,1) = save;
      }
      reflection = !reflection;
    }

    aDiag.MakeDiagonal(diagonal);

    if (reflection)
    {
      // The orthogonal transformation that diagonalizes M is a reflection.
      // Make the eigenvectors a right-handed system by changing sign on
      // the last column.
      aRot(0,2) = -aRot(0,2);
      aRot(1,2) = -aRot(1,2);
      aRot(2,2) = -aRot(2,2);
    }
  }

  template <MATRIX_3_TYPES>
  TL_I typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::MakeRotationX( const_reference aXAngle )
  {
    value_type cosine, sine;

    cosine = Math<value_type>::Cos(aXAngle);
    sine = Math<value_type>::Sin(aXAngle);

    value_type values[9] = { (value_type)1,  (value_type)0,  (value_type)0,
                             (value_type)0,         cosine,          -sine,
                             (value_type)0,           sine,         cosine };

    Set(values, base_type::k_RowMajor);
    return *this;
  }

  template <MATRIX_3_TYPES>
  TL_I typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::MakeRotationY( const_reference aYAngle )
  {
    value_type cosine, sine;

    cosine = Math<value_type>::Cos(aYAngle);
    sine = Math<value_type>::Sin(aYAngle);

    value_type values[9] = {        cosine,  (value_type)0,           sine,
                             (value_type)0,  (value_type)1,  (value_type)0,
                                     -sine,  (value_type)0,         cosine};

    Set(values, base_type::k_RowMajor);
    return *this;
  }

  template <MATRIX_3_TYPES>
  TL_I typename Matrix3<MATRIX_3_PARAMS>::this_type& 
    Matrix3<MATRIX_3_PARAMS>::MakeRotationZ( const_reference aZAngle )
  {
    value_type cosine, sine;

    cosine = Math<value_type>::Cos(aZAngle);
    sine = Math<value_type>::Sin(aZAngle);

    value_type values[9] = {        cosine,          -sine,  (value_type)0,
                                      sine,         cosine,  (value_type)0,
                             (value_type)0,  (value_type)0,  (value_type)1 };

    Set(values, base_type::k_RowMajor);
    return *this;

  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerXYZ( value_type aXAngle, 
                                               value_type aYAngle, 
                                               value_type aZAngle )
  {
    this_type matY, matZ;

    MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matY.Mul(matZ));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerXZY( value_type aXAngle, 
                                               value_type aZAngle, 
                                               value_type aYAngle )
  {
    this_type matY, matZ;

    MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matZ.Mul(matY));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerYXZ( value_type aYAngle, 
                                               value_type aXAngle, 
                                               value_type aZAngle )
  {
    this_type matX, matZ;

    MakeRotationY(aYAngle);
    matX.MakeRotationX(aXAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matX.Mul(matZ));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerYZX( value_type aYAngle, 
                                               value_type aZAngle, 
                                               value_type aXAngle )
  {
    this_type matX, matZ;

    MakeRotationY(aYAngle);
    matX.MakeRotationX(aXAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matZ.Mul(matX));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerZXY( value_type aZAngle, 
                                               value_type aXAngle, 
                                               value_type aYAngle )
  {
    this_type matX, matY;

    MakeRotationZ(aZAngle);
    matX.MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);

    Mul(matX.Mul(matY));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerZYX( value_type aZAngle, 
                                               value_type aYAngle, 
                                               value_type aXAngle )
  {
    this_type matX, matY;

    MakeRotationZ(aZAngle);
    matX.MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);

    Mul(matY.Mul(matX));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerXYX( value_type aXAngle0, 
                                               value_type aYAngle, 
                                               value_type aXAngle1 )
  {
    this_type matX, matY;

    MakeRotationX(aXAngle0);
    matX.MakeRotationX(aXAngle1);
    matY.MakeRotationY(aYAngle);

    Mul(matY.Mul(matX));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerXZX( value_type aXAngle0, 
                                               value_type aZAngle, 
                                               value_type aXAngle1 )
  {
    this_type matX, matZ;

    MakeRotationX(aXAngle0);
    matX.MakeRotationX(aXAngle1);
    matZ.MakeRotationZ(aZAngle);

    Mul(matZ.Mul(matX));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerYXY( value_type aYAngle0, 
                                               value_type aXAngle, 
                                               value_type aYAngle1 )
  {
    this_type matX, matY;

    MakeRotationY(aYAngle0);
    matX.MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle1);

    Mul(matX.Mul(matY));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerYZY( value_type aYAngle0, 
                                               value_type aZAngle, 
                                               value_type aYAngle1 )
  {
    this_type matY, matZ;

    MakeRotationY(aYAngle0);
    matZ.MakeRotationZ(aZAngle);
    matY.MakeRotationY(aYAngle1);

    Mul(matZ.Mul(matY));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerZXZ( value_type aZAngle0, 
                                               value_type aXAngle, 
                                               value_type aZAngle1 )
  {
    this_type matZ, matX;

    MakeRotationZ(aZAngle0);
    matX.MakeRotationX(aXAngle);
    matZ.MakeRotationZ(aZAngle1);

    Mul(matX.Mul(matZ));
  }

  template <MATRIX_3_TYPES>
  void Matrix3<MATRIX_3_PARAMS>::MakeEulerZYZ( value_type aZAngle0, 
                                               value_type aYAngle, 
                                               value_type aZAngle1 )
  {
    this_type matZ, matY;

    MakeRotationZ(aZAngle0);
    matY.MakeRotationY(aYAngle);
    matZ.MakeRotationZ(aZAngle1);

    Mul(matY.Mul(matZ));
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <MATRIX_3_TYPES>
  bool Matrix3<MATRIX_3_PARAMS>
    ::Tridiagonalize( value_type aDiagonal[3], value_type aSubdiagonal[2] )
  {
    // Householder reduction T = Q^t M Q
    //   Input:
    //     mat, symmetric 3x3 matrix M
    //   Output:
    //     mat, orthogonal matrix Q (a reflection)
    //     diag, diagonal entries of T
    //     subd, subdiagonal entries of T (T is symmetric)

    value_type m00 = m_values[0];
    value_type m01 = m_values[1];
    value_type m02 = m_values[2];
    value_type m11 = m_values[4];
    value_type m12 = m_values[5];
    value_type m22 = m_values[8];

    aDiagonal[0] = m00;
    if (Math<value_type>::FAbs(m02) >= Math<value_type>::ZERO_TOLERANCE)
    {
      aSubdiagonal[0] = Math<value_type>::Sqrt(m01*m01 + m02*m02);
      value_type invLength = ((value_type)1)/aSubdiagonal[0];
      m01 *= invLength;
      m02 *= invLength;
      value_type tmp = ((value_type)2)*m01*m12 + m02*(m22 - m11);
      aDiagonal[1] = m11 + m02*tmp;
      aDiagonal[2] = m22 - m02*tmp;
      aSubdiagonal[1] = m12 - m01*tmp;

      m_values[0] = (value_type)1;
      m_values[1] = (value_type)0;
      m_values[2] = (value_type)0;
      m_values[3] = (value_type)0;
      m_values[4] = m01;
      m_values[5] = m02;
      m_values[6] = (value_type)0;
      m_values[7] = m02;
      m_values[8] = -m01;
      return true;
    }
    else
    {
      aDiagonal[1] = m11;
      aDiagonal[2] = m22;
      aSubdiagonal[0] = m01;
      aSubdiagonal[1] = m12;

      m_values[0] = (value_type)1;
      m_values[1] = (value_type)0;
      m_values[2] = (value_type)0;
      m_values[3] = (value_type)0;
      m_values[4] = (value_type)1;
      m_values[5] = (value_type)0;
      m_values[6] = (value_type)0;
      m_values[7] = (value_type)0;
      m_values[8] = (value_type)1;
      return false;
    }
  }

  template <MATRIX_3_TYPES>
  bool Matrix3<MATRIX_3_PARAMS>
    ::QLAlgorithm( value_type aDiagonal[3], value_type aSubdiagonal[2] )
  {
    // This is an implementation of the symmetric QR algorithm from the book
    // "Matrix Computations" by Gene H. Golub and Charles F. Van Loan,
    // second edition.  The algorithm is 8.2.3.  The implementation has a
    // slight variation to actually make it a QL algorithm, and it traps the
    // case when either of the subdiagonal terms s0 or s1 is zero and reduces
    // the 2-by-2 subblock directly.

    const s32 imax = 32;
    for (s32 i = 0; i < imax; ++i)
    {
      value_type sum, diff, discr, eigVal0, eigVal1, cs, sn, tmp;
      s32 row;

      sum = Math<value_type>::FAbs(aDiagonal[0]) + 
            Math<value_type>::FAbs(aDiagonal[1]);
      if (Math<value_type>::FAbs(aSubdiagonal[0]) + sum == sum)
      {
        // The matrix is effectively
        //       +-        -+
        //   M = | d0  0  0 |
        //       | 0  d1 s1 |
        //       | 0  s1 d2 |
        //       +-        -+

        // Test whether M is diagonal (within numerical round-off).
        sum = Math<value_type>::FAbs(aDiagonal[1]) +
              Math<value_type>::FAbs(aDiagonal[2]);
        if (Math<value_type>::FAbs(aSubdiagonal[1]) + sum == sum)
        {
          return true;
        }

        // Compute the eigenvalues as roots of a quadratic equation.
        sum = aDiagonal[1] + aDiagonal[2];
        diff = aDiagonal[1] - aDiagonal[2];
        discr = Math<value_type>::Sqrt(diff * diff +
                ((value_type)4) * aSubdiagonal[1] * aSubdiagonal[1]);
        eigVal0 = ((value_type)0.5) * (sum - discr);
        eigVal1 = ((value_type)0.5) * (sum + discr);

        // Compute the Givens rotation.
        if (diff >= (value_type)0)
        {
          cs = aSubdiagonal[1];
          sn = aDiagonal[1] - eigVal0;
        }
        else
        {
          cs = aDiagonal[2] - eigVal0;
          sn = aSubdiagonal[1];
        }
        tmp = Math<value_type>::InvSqrt(cs*cs + sn*sn);
        cs *= tmp;
        sn *= tmp;

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (row = 0; row < 3; ++row)
        {
          tmp = m_values[2+3*row];
          m_values[2 + 3 * row] = sn * m_values[1 + 3 * row] + cs * tmp;
          m_values[ 1 + 3 * row] = cs * m_values[1 + 3 * row] - sn * tmp;
        }

        // Update the tridiagonal matrix.
        aDiagonal[1] = eigVal0;
        aDiagonal[2] = eigVal1;
        aSubdiagonal[0] = (value_type)0;
        aSubdiagonal[1] = (value_type)0;
        return true;
      }

      sum = Math<value_type>::FAbs(aDiagonal[1]) + 
            Math<value_type>::FAbs(aDiagonal[2]);
      if (Math<value_type>::FAbs(aSubdiagonal[1]) + sum == sum)
      {
        // The matrix is effectively
        //       +-         -+
        //   M = | d0  s0  0 |
        //       | s0  d1  0 |
        //       | 0   0  d2 |
        //       +-         -+

        // Test whether M is diagonal (within numerical round-off).
        sum = Math<value_type>::FAbs(aDiagonal[0]) +
              Math<value_type>::FAbs(aDiagonal[1]);
        if (Math<value_type>::FAbs(aSubdiagonal[0]) + sum == sum)
        {
          return true;
        }

        // Compute the eigenvalues as roots of a quadratic equation.
        sum = aDiagonal[0] + aDiagonal[1];
        diff = aDiagonal[0] - aDiagonal[1];
        discr = Math<value_type>::Sqrt(diff*diff +
                ((value_type)4.0) * aSubdiagonal[0] * aSubdiagonal[0]);
        eigVal0 = ((value_type)0.5)*(sum - discr);
        eigVal1 = ((value_type)0.5)*(sum + discr);

        // Compute the Givens rotation.
        if (diff >= (value_type)0)
        {
          cs = aSubdiagonal[0];
          sn = aDiagonal[0] - eigVal0;
        }
        else
        {
          cs = aDiagonal[1] - eigVal0;
          sn = aSubdiagonal[0];
        }
        tmp = Math<value_type>::InvSqrt(cs*cs + sn*sn);
        cs *= tmp;
        sn *= tmp;

        // Post-multiply the current orthogonal matrix with the Givens
        // rotation.
        for (row = 0; row < 3; ++row)
        {
          tmp = m_values[1+3*row];
          m_values[1 + 3 * row] = sn * m_values[0 + 3 * row] + cs * tmp;
          m_values[0 + 3 * row] = cs * m_values[0 + 3 * row] - sn * tmp;
        }

        // Update the tridiagonal matrix.
        aDiagonal[0] = eigVal0;
        aDiagonal[1] = eigVal1;
        aSubdiagonal[0] = (value_type)0;
        aSubdiagonal[1] = (value_type)0;
        return true;
      }

      // The matrix is
      //       +-        -+
      //   M = | d0 s0  0 |
      //       | s0 d1 s1 |
      //       | 0  s1 d2 |
      //       +-        -+

      // Set up the parameters for the first pass of the QL step.  The
      // value for A is the difference between diagonal term D[2] and the
      // implicit shift suggested by Wilkinson.
      value_type ratio = (aDiagonal[1] - aDiagonal[0])/
                          (((value_type)2) * aSubdiagonal[0]);
      value_type root = Math<value_type>::Sqrt((value_type)1 + ratio * ratio);
      value_type b = aSubdiagonal[1];
      value_type a = aDiagonal[2] - aDiagonal[0];
      if (ratio >= (value_type)0)
      {
        a += aSubdiagonal[0]/(ratio + root);
      }
      else
      {
        a += aSubdiagonal[0]/(ratio - root);
      }

      // Compute the Givens rotation for the first pass.
      if (Math<value_type>::FAbs(b) >= Math<value_type>::FAbs(a))
      {
        ratio = a/b;
        sn = Math<value_type>::InvSqrt((value_type)1 + ratio*ratio);
        cs = ratio*sn;
      }
      else
      {
        ratio = b/a;
        cs = Math<value_type>::InvSqrt((value_type)1 + ratio*ratio);
        sn = ratio*cs;
      }

      // Post-multiply the current orthogonal matrix with the Givens
      // rotation.
      for (row = 0; row < 3; ++row)
      {
        tmp = m_values[2+3*row];
        m_values[2 + 3 * row] = sn * m_values[1 + 3 * row] + cs * tmp;
        m_values[1 + 3 * row] = cs * m_values[1 + 3 * row] - sn * tmp;
      }

      // Set up the parameters for the second pass of the QL step.  The
      // values tmp0 and tmp1 are required to fully update the tridiagonal
      // matrix at the end of the second pass.
      value_type tmp0 = (aDiagonal[1] - aDiagonal[2])*sn +
                        ((value_type)2) * aSubdiagonal[1] * cs;
      value_type tmp1 = cs * aSubdiagonal[0];
      b = sn * aSubdiagonal[0];
      a = cs*tmp0 - aSubdiagonal[1];
      tmp0 *= sn;

      // Compute the Givens rotation for the second pass.  The subdiagonal
      // term S[1] in the tridiagonal matrix is updated at this time.
      if (Math<value_type>::FAbs(b) >= Math<value_type>::FAbs(a))
      {
        ratio = a/b;
        root = Math<value_type>::Sqrt((value_type)1 + ratio*ratio);
        aSubdiagonal[1] = b*root;
        sn = ((value_type)1)/root;
        cs = ratio*sn;
      }
      else
      {
        ratio = b/a;
        root = Math<value_type>::Sqrt((value_type)1 + ratio*ratio);
        aSubdiagonal[1] = a * root;
        cs = ((value_type)1)/root;
        sn = ratio * cs;
      }

      // Postmultiply the current orthogonal matrix with the Givens
      // rotation.
      for (row = 0; row < 3; ++row)
      {
        tmp = m_values[1 + 3 * row];
        m_values[1 + 3 * row] = sn * m_values[0 + 3 * row] + cs * tmp;
        m_values[0 + 3 * row] = cs * m_values[0 + 3 * row] - sn * tmp;
      }

      // Complete the update of the tridiagonal matrix.
      value_type tmp2 = aDiagonal[1] - tmp0;
      aDiagonal[2] += tmp0;
      tmp0 = (aDiagonal[0] - tmp2) * sn + ((value_type)2) * tmp1 * cs;
      aSubdiagonal[0] = cs * tmp0 - tmp1;
      tmp0 *= sn;
      aDiagonal[1] = tmp2 + tmp0;
      aDiagonal[0] -= tmp0;
    }
    return false;
  }

};};

#endif