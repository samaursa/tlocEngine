namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Matrix3f<T>

  //------------------------------------------------------------------------
  // Constructors

  template <typename T>
  TL_FI Matrix3<T>::Matrix3() 
    : Matrix() {}

  template <typename T>
  TL_FI Matrix3<T>::Matrix3(const Matrix3<T>& aMatrix) 
    : Matrix(aMatrix) {}

  template <typename T>
  TL_FI Matrix3<T>::Matrix3(T m00, T m01, T m02, 
                            T m10, T m11, T m12, 
                            T m20, T m21, T m22)
  {
    m_values[0] = m00; m_values[3] = m01; m_values[6] = m02;
    m_values[1] = m10; m_values[4] = m11; m_values[7] = m12;
    m_values[2] = m20; m_values[5] = m21; m_values[8] = m22;
  }

  template <typename T>
  TL_FI Matrix3<T>::Matrix3(T m00, T m11, T m22)
  {
    T diag[3] = {m00, m11, m22};
    MakeDiagonal(diag);
  }

  template <typename T>
  TL_FI Matrix3<T>::Matrix3(const T& aValue) 
    : Matrix(aValue) {}

  template <typename T>
  TL_FI Matrix3<T>::Matrix3(const Vector<T, 3>& aVec1, 
                            const Vector<T, 3>& aVec2, 
                            const Vector<T, 3>& aVec3, 
                            TABLE_ORDER aOrder)
  {
    if (aOrder == COL_MAJOR)
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

  template <typename T>
  TL_FI Matrix3<T>::Matrix3(const T values[MATRIX_SIZE], TABLE_ORDER aOrder)
    : Matrix(values, aOrder) {}

  //------------------------------------------------------------------------
  // Math Operations

  template <typename T>
  TL_FI void Matrix3<T>::Mul(const Matrix3<T>& aMatrix)
  {
    Matrix3<T> temp(*this);
    Mul(temp, aMatrix);
  }

  template <typename T>
  TL_FI void Matrix3<T>::Mul(const Matrix3<T>& aMatrix1, 
                             const Matrix3<T>& aMatrix2)
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

  template <typename T>
  TL_FI void Matrix3<T>::Mul(const Vector<T, 3>& aVectorIn, 
    Vector<T, 3>& aVectorOut)
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

  template <typename T>
  TL_I T Matrix3<T>::Determinant() const
  {
    T m11_12_21_22 = (m_values[4] * m_values[8] - m_values[7] * m_values[5]) 
                      * m_values[0];
    T m10_12_20_22 = (m_values[1] * m_values[8] - m_values[7] * m_values[2]) 
                      * m_values[3];
    T m10_11_20_21 = (m_values[1] * m_values[5] - m_values[4] * m_values[2]) 
                      * m_values[6];

    return m11_12_21_22 - m10_12_20_22 + m10_11_20_21;
  }

  template <typename T>
  TL_I bool Matrix3<T>::Inverse()
  {
    Matrix3<T> temp(*this);
    return Inverse(temp);
  }

  template <typename T>
  TL_I bool Matrix3<T>::Inverse(const Matrix3<T>& aMatrix)
  {
    T detInv = aMatrix.Determinant();
    if (Math<T>::Approx(detInv, (T)0)) { return false; }

    detInv = ((T)1) / detInv;

    Adjoint(aMatrix);
    Matrix::Mul(detInv);

    return true;
  }

  template <typename T>
  TL_I void Matrix3<T>::Adjoint()
  {
    Matrix3<T> temp(*this);
    Adjoint(temp);
  }

  template <typename T>
  TL_I void Matrix3<T>::Adjoint(const Matrix3<T>& aMatrix)
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
  template <typename T>
  TL_FI void Matrix3<T>::Orthonormalize()
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
    T invLength = Math<T>::InvSqrt(m_values[0] * m_values[0] +
                                   m_values[1] * m_values[1] + 
                                   m_values[2] * m_values[2]);

    m_values[0] *= invLength;
    m_values[1] *= invLength;
    m_values[2] *= invLength;

    // Compute q1.
    T dot0 = m_values[0] * m_values[3] + 
             m_values[1] * m_values[4] +
             m_values[2] * m_values[5];

    m_values[3] -= dot0 * m_values[0];
    m_values[4] -= dot0 * m_values[1];
    m_values[5] -= dot0 * m_values[2];

    invLength = Math<T>::InvSqrt(m_values[3] * m_values[3] +
                                 m_values[4] * m_values[4] + 
                                 m_values[5] * m_values[5]);

    m_values[3] *= invLength;
    m_values[4] *= invLength;
    m_values[5] *= invLength;

    // compute q2
    T dot1 = m_values[3] * m_values[6] + 
             m_values[4] * m_values[7] +
             m_values[5] * m_values[8];

    dot0 = m_values[0] * m_values[6] + 
           m_values[1] * m_values[7] +
           m_values[2] * m_values[8];

    m_values[6] -= dot0 * m_values[0] + dot1 * m_values[3];
    m_values[7] -= dot0 * m_values[1] + dot1 * m_values[4];
    m_values[8] -= dot0 * m_values[2] + dot1 * m_values[5];

    invLength = Math<T>::InvSqrt(m_values[6] * m_values[6] +
                                 m_values[7] * m_values[7] + 
                                 m_values[8] * m_values[8]);

    m_values[6] *= invLength;
    m_values[7] *= invLength;
    m_values[8] *= invLength;
  }

  template <typename T>
  TL_FI void Matrix3<T>::FastOrthonormalize()
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
    T invLength = Math<T>::FastInvSqrt(m_values[0] * m_values[0] +
                                       m_values[1] * m_values[1] + 
                                       m_values[2] * m_values[2]);

    m_values[0] *= invLength;
    m_values[1] *= invLength;
    m_values[2] *= invLength;

    // Compute q1.
    T dot0 = m_values[0] * m_values[3] + 
             m_values[1] * m_values[4] +
             m_values[2] * m_values[5];

    m_values[3] -= dot0 * m_values[0];
    m_values[4] -= dot0 * m_values[1];
    m_values[5] -= dot0 * m_values[2];

    invLength = Math<T>::FastInvSqrt(m_values[3] * m_values[3] +
                                     m_values[4] * m_values[4] + 
                                     m_values[5] * m_values[5]);

    m_values[3] *= invLength;
    m_values[4] *= invLength;
    m_values[5] *= invLength;

    // compute q2
    T dot1 = m_values[3] * m_values[6] + 
             m_values[4] * m_values[7] +
             m_values[5] * m_values[8];

    dot0 = m_values[0] * m_values[6] + 
           m_values[1] * m_values[7] +
           m_values[2] * m_values[8];

    m_values[6] -= dot0 * m_values[0] + dot1 * m_values[3];
    m_values[7] -= dot0 * m_values[1] + dot1 * m_values[4];
    m_values[8] -= dot0 * m_values[2] + dot1 * m_values[5];

    invLength = Math<T>::FastInvSqrt(m_values[6] * m_values[6] +
                                     m_values[7] * m_values[7] + 
                                     m_values[8] * m_values[8]);

    m_values[6] *= invLength;
    m_values[7] *= invLength;
    m_values[8] *= invLength;
  }

  template <typename T>
  TL_FI void Matrix3<T>::EigenDecomposition(Matrix3<T>& aRot, Matrix3<T>& aDiag) const
  {
    TLOC_UNUSED(aRot);
    TLOC_UNUSED(aDiag);
  }
};
