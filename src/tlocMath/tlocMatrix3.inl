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
  TL_FI Matrix3<T>& Matrix3<T>::Mul(const Matrix3<T>& aMatrix)
  {
    Matrix3<T> temp(*this);
    Mul(temp, aMatrix);

    return *this;
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
  TL_I Matrix3<T>& Matrix3<T>::Adjoint()
  {
    Matrix3<T> temp(*this);
    Adjoint(temp);

    return *this;
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
  TL_FI Matrix3<T>& Matrix3<T>::Orthonormalize()
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

    return *this;
  }

  template <typename T>
  TL_FI void tloc::Matrix3<T>::Orthonormalize( const Matrix3<T>& aMatrix )
  {
    *this = aMatrix;
    Orthonormalize();
  }

  template <typename T>
  TL_FI Matrix3<T>& Matrix3<T>::FastOrthonormalize()
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

    return *this;
  }

  template <typename T>
  TL_FI void tloc::Matrix3<T>::FastOrthonormalize( const Matrix3<T>& aMatrix )
  {
    *this = aMatrix;
    FastOrthonormalize();
  }

  template <typename T>
  void Matrix3<T>::EigenDecomposition(Matrix3<T>& aRot, Matrix3<T>& aDiag) const
  {
    // Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
    // diagonal entries of D are the corresponding eigenvalues.
    T diagonal[3], subdiagonal[2];
    aRot = *this;
    bool reflection = aRot.Tridiagonalize(diagonal, subdiagonal);
    bool converged = aRot.QLAlgorithm(diagonal, subdiagonal);
    TLOC_ASSERT(converged, "QLAlgorithm failed to converge\n");
    TLOC_UNUSED(converged);

    // Sort the eigenvalues in increasing order, d0 <= d1 <= d2.  This is an
    // insertion sort.
    int i;
    T save;

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

  template <typename T>
  TL_I Matrix3<T>& tloc::Matrix3<T>::MakeRotationX( const T& aXAngle )
  {
    T cosine, sine;

    cosine = Math<T>::Cos(aXAngle);
    sine = Math<T>::Sin(aXAngle);

    T values[9] = { (T)1,   (T)0,  (T)0,
                    (T)0, cosine, -sine,
                    (T)0,   sine, cosine };

    Set(values, ROW_MAJOR);
    return *this;
  }

  template <typename T>
  TL_I Matrix3<T>& tloc::Matrix3<T>::MakeRotationY( const T& aYAngle )
  {
    T cosine, sine;

    cosine = Math<T>::Cos(aYAngle);
    sine = Math<T>::Sin(aYAngle);

    T values[9] = {cosine, (T)0,  sine,
                     (T)0, (T)1,  (T)0,
                    -sine, (T)0, cosine};

    Set(values, ROW_MAJOR);
    return *this;
  }

  template <typename T>
  TL_I Matrix3<T>& tloc::Matrix3<T>::MakeRotationZ( const T& aZAngle )
  {
    T cosine, sine;

    cosine = Math<T>::Cos(aZAngle);
    sine = Math<T>::Sin(aZAngle);

    T values[9] = {cosine,  -sine, (T)0,
                     sine, cosine, (T)0,
                     (T)0,   (T)0, (T)1 };

    Set(values, ROW_MAJOR);
    return *this;

  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerXYZ( T aXAngle, T aYAngle, T aZAngle )
  {
    Matrix3<T> matY, matZ;

    MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matY.Mul(matZ));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerXZY( T aXAngle, T aZAngle, T aYAngle )
  {
    Matrix3<T> matY, matZ;

    MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matZ.Mul(matY));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerYXZ( T aYAngle, T aXAngle, T aZAngle )
  {
    Matrix3<T> matX, matZ;

    MakeRotationY(aYAngle);
    matX.MakeRotationX(aXAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matX.Mul(matZ));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerYZX( T aYAngle, T aZAngle, T aXAngle )
  {
    Matrix3<T> matX, matZ;

    MakeRotationY(aYAngle);
    matX.MakeRotationX(aXAngle);
    matZ.MakeRotationZ(aZAngle);

    Mul(matZ.Mul(matX));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerZXY( T aZAngle, T aXAngle, T aYAngle )
  {
    Matrix3<T> matX, matY;

    MakeRotationZ(aZAngle);
    matX.MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);

    Mul(matX.Mul(matY));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerZYX( T aZAngle, T aYAngle, T aXAngle )
  {
    Matrix3<T> matX, matY;

    MakeRotationZ(aZAngle);
    matX.MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle);

    Mul(matY.Mul(matX));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerXYX( T aXAngle0, T aYAngle, T aXAngle1 )
  {
    Matrix3<T> matX, matY;

    MakeRotationX(aXAngle0);
    matX.MakeRotationX(aXAngle1);
    matY.MakeRotationY(aYAngle);

    Mul(matY.Mul(matX));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerXZX( T aXAngle0, T aZAngle, T aXAngle1 )
  {
    Matrix3<T> matX, matZ;

    MakeRotationX(aXAngle0);
    matX.MakeRotationX(aXAngle1);
    matZ.MakeRotationZ(aZAngle);

    Mul(matZ.Mul(matX));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerYXY( T aYAngle0, T aXAngle, T aYAngle1 )
  {
    Matrix3<T> matX, matY;

    MakeRotationY(aYAngle0);
    matX.MakeRotationX(aXAngle);
    matY.MakeRotationY(aYAngle1);

    Mul(matX.Mul(matY));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerYZY( T aYAngle0, T aZAngle, T aYAngle1 )
  {
    Matrix3<T> matY, matZ;

    MakeRotationY(aYAngle0);
    matZ.MakeRotationZ(aZAngle);
    matY.MakeRotationY(aYAngle1);

    Mul(matZ.Mul(matY));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerZXZ( T aZAngle0, T aXAngle, T aZAngle1 )
  {
    Matrix3<T> matZ, matX;

    MakeRotationZ(aZAngle0);
    matX.MakeRotationX(aXAngle);
    matZ.MakeRotationZ(aZAngle1);

    Mul(matX.Mul(matZ));
  }

  template <typename T>
  void tloc::Matrix3<T>::MakeEulerZYZ( T aZAngle0, T aYAngle, T aZAngle1 )
  {
    Matrix3<T> matZ, matY;

    MakeRotationZ(aZAngle0);
    matY.MakeRotationY(aYAngle);
    matZ.MakeRotationZ(aZAngle1);

    Mul(matY.Mul(matZ));
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <typename T>
  bool tloc::Matrix3<T>::Tridiagonalize( T aDiagonal[3], T aSubdiagonal[2] )
  {
    // Householder reduction T = Q^t M Q
    //   Input:
    //     mat, symmetric 3x3 matrix M
    //   Output:
    //     mat, orthogonal matrix Q (a reflection)
    //     diag, diagonal entries of T
    //     subd, subdiagonal entries of T (T is symmetric)

    T m00 = m_values[0];
    T m01 = m_values[1];
    T m02 = m_values[2];
    T m11 = m_values[4];
    T m12 = m_values[5];
    T m22 = m_values[8];

    aDiagonal[0] = m00;
    if (Math<T>::FAbs(m02) >= Math<T>::ZERO_TOLERANCE)
    {
      aSubdiagonal[0] = Math<T>::Sqrt(m01*m01 + m02*m02);
      T invLength = ((T)1)/aSubdiagonal[0];
      m01 *= invLength;
      m02 *= invLength;
      T tmp = ((T)2)*m01*m12 + m02*(m22 - m11);
      aDiagonal[1] = m11 + m02*tmp;
      aDiagonal[2] = m22 - m02*tmp;
      aSubdiagonal[1] = m12 - m01*tmp;

      m_values[0] = (T)1;
      m_values[1] = (T)0;
      m_values[2] = (T)0;
      m_values[3] = (T)0;
      m_values[4] = m01;
      m_values[5] = m02;
      m_values[6] = (T)0;
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

      m_values[0] = (T)1;
      m_values[1] = (T)0;
      m_values[2] = (T)0;
      m_values[3] = (T)0;
      m_values[4] = (T)1;
      m_values[5] = (T)0;
      m_values[6] = (T)0;
      m_values[7] = (T)0;
      m_values[8] = (T)1;
      return false;
    }
  }

  template <typename T>
  bool tloc::Matrix3<T>::QLAlgorithm( T aDiagonal[3], T aSubdiagonal[2] )
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
      T sum, diff, discr, eigVal0, eigVal1, cs, sn, tmp;
      s32 row;

      sum = Math<T>::FAbs(aDiagonal[0]) + Math<T>::FAbs(aDiagonal[1]);
      if (Math<T>::FAbs(aSubdiagonal[0]) + sum == sum)
      {
        // The matrix is effectively
        //       +-        -+
        //   M = | d0  0  0 |
        //       | 0  d1 s1 |
        //       | 0  s1 d2 |
        //       +-        -+

        // Test whether M is diagonal (within numerical round-off).
        sum = Math<T>::FAbs(aDiagonal[1]) +
          Math<T>::FAbs(aDiagonal[2]);
        if (Math<T>::FAbs(aSubdiagonal[1]) + sum == sum)
        {
          return true;
        }

        // Compute the eigenvalues as roots of a quadratic equation.
        sum = aDiagonal[1] + aDiagonal[2];
        diff = aDiagonal[1] - aDiagonal[2];
        discr = Math<T>::Sqrt(diff * diff +
          ((T)4) * aSubdiagonal[1] * aSubdiagonal[1]);
        eigVal0 = ((T)0.5) * (sum - discr);
        eigVal1 = ((T)0.5) * (sum + discr);

        // Compute the Givens rotation.
        if (diff >= (T)0)
        {
          cs = aSubdiagonal[1];
          sn = aDiagonal[1] - eigVal0;
        }
        else
        {
          cs = aDiagonal[2] - eigVal0;
          sn = aSubdiagonal[1];
        }
        tmp = Math<T>::InvSqrt(cs*cs + sn*sn);
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
        aSubdiagonal[0] = (T)0;
        aSubdiagonal[1] = (T)0;
        return true;
      }

      sum = Math<T>::FAbs(aDiagonal[1]) + Math<T>::FAbs(aDiagonal[2]);
      if (Math<T>::FAbs(aSubdiagonal[1]) + sum == sum)
      {
        // The matrix is effectively
        //       +-         -+
        //   M = | d0  s0  0 |
        //       | s0  d1  0 |
        //       | 0   0  d2 |
        //       +-         -+

        // Test whether M is diagonal (within numerical round-off).
        sum = Math<T>::FAbs(aDiagonal[0]) +
          Math<T>::FAbs(aDiagonal[1]);
        if (Math<T>::FAbs(aSubdiagonal[0]) + sum == sum)
        {
          return true;
        }

        // Compute the eigenvalues as roots of a quadratic equation.
        sum = aDiagonal[0] + aDiagonal[1];
        diff = aDiagonal[0] - aDiagonal[1];
        discr = Math<T>::Sqrt(diff*diff +
                ((T)4.0) * aSubdiagonal[0] * aSubdiagonal[0]);
        eigVal0 = ((T)0.5)*(sum - discr);
        eigVal1 = ((T)0.5)*(sum + discr);

        // Compute the Givens rotation.
        if (diff >= (T)0)
        {
          cs = aSubdiagonal[0];
          sn = aDiagonal[0] - eigVal0;
        }
        else
        {
          cs = aDiagonal[1] - eigVal0;
          sn = aSubdiagonal[0];
        }
        tmp = Math<T>::InvSqrt(cs*cs + sn*sn);
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
        aSubdiagonal[0] = (T)0;
        aSubdiagonal[1] = (T)0;
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
      T ratio = (aDiagonal[1] - aDiagonal[0])/(((T)2) * aSubdiagonal[0]);
      T root = Math<T>::Sqrt((T)1 + ratio * ratio);
      T b = aSubdiagonal[1];
      T a = aDiagonal[2] - aDiagonal[0];
      if (ratio >= (T)0)
      {
        a += aSubdiagonal[0]/(ratio + root);
      }
      else
      {
        a += aSubdiagonal[0]/(ratio - root);
      }

      // Compute the Givens rotation for the first pass.
      if (Math<T>::FAbs(b) >= Math<T>::FAbs(a))
      {
        ratio = a/b;
        sn = Math<T>::InvSqrt((T)1 + ratio*ratio);
        cs = ratio*sn;
      }
      else
      {
        ratio = b/a;
        cs = Math<T>::InvSqrt((T)1 + ratio*ratio);
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
      T tmp0 = (aDiagonal[1] - aDiagonal[2])*sn +
        ((T)2) * aSubdiagonal[1] * cs;
      T tmp1 = cs * aSubdiagonal[0];
      b = sn * aSubdiagonal[0];
      a = cs*tmp0 - aSubdiagonal[1];
      tmp0 *= sn;

      // Compute the Givens rotation for the second pass.  The subdiagonal
      // term S[1] in the tridiagonal matrix is updated at this time.
      if (Math<T>::FAbs(b) >= Math<T>::FAbs(a))
      {
        ratio = a/b;
        root = Math<T>::Sqrt((T)1 + ratio*ratio);
        aSubdiagonal[1] = b*root;
        sn = ((T)1)/root;
        cs = ratio*sn;
      }
      else
      {
        ratio = b/a;
        root = Math<T>::Sqrt((T)1 + ratio*ratio);
        aSubdiagonal[1] = a * root;
        cs = ((T)1)/root;
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
      T tmp2 = aDiagonal[1] - tmp0;
      aDiagonal[2] += tmp0;
      tmp0 = (aDiagonal[0] - tmp2) * sn + ((T)2) * tmp1 * cs;
      aSubdiagonal[0] = cs * tmp0 - tmp1;
      tmp0 *= sn;
      aDiagonal[1] = tmp2 + tmp0;
      aDiagonal[0] -= tmp0;
    }
    return false;
  }

};
