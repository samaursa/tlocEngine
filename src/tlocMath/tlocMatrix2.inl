namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Matrix2f<T>

  //------------------------------------------------------------------------
  // Constructors

  template <typename T>
  TL_FI Matrix2<T>::Matrix2() 
    : Matrix() {}

  template <typename T>
  TL_FI Matrix2<T>::Matrix2(const Matrix2<T>& aMatrix) 
    : Matrix(aMatrix) {}

  template <typename T>
TL_FI Matrix2<T>::Matrix2(T m00, T m01, 
                          T m10, T m11)
  {
    m_values[0] = m00;
    m_values[1] = m10;
    m_values[2] = m01;
    m_values[3] = m11;
  }

  template <typename T>
  TL_FI Matrix2<T>::Matrix2(T m00, T m11)
  {
    T diag[2] = {m00, m11};
    MakeDiagonal(diag);
  }

  template <typename T>
  TL_FI Matrix2<T>::Matrix2(const T& aValue) 
    : Matrix(aValue) {}

  template <typename T>
  TL_FI Matrix2<T>::Matrix2(const Vector<T, 2>& aVec1, const Vector<T, 2>& aVec2, 
    TABLE_ORDER aOrder)
  {
    if (aOrder == COL_MAJOR)
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

  template <typename T>
  TL_FI Matrix2<T>::Matrix2(const T values[MATRIX_SIZE], TABLE_ORDER aOrder)
    : Matrix(values, aOrder) {}

  //------------------------------------------------------------------------
  // Math Operations

  template <typename T>
  TL_FI void Matrix2<T>::Mul(const Matrix2<T>& aMatrix)
  {
    Matrix2<T> temp(*this);
    Mul(temp, aMatrix);
  }

  template <typename T>
  TL_FI void Matrix2<T>::Mul(const Matrix2<T>& aMatrix1, 
    const Matrix2<T>& aMatrix2)
  {
    m_values[0] = (aMatrix1[0] * aMatrix2[0]) + (aMatrix1[2] * aMatrix2[1]);
    m_values[2] = (aMatrix1[1] * aMatrix2[0]) + (aMatrix1[3] * aMatrix2[1]);
    m_values[1] = (aMatrix1[0] * aMatrix2[2]) + (aMatrix1[2] * aMatrix2[3]);
    m_values[3] = (aMatrix1[1] * aMatrix2[2]) + (aMatrix1[3] * aMatrix2[3]);
  }

  template <typename T>
  TL_FI void Matrix2<T>::Mul(const Vector<T, 2>& aVectorIn, 
    Vector<T, 2>& aVectorOut)
  {
    aVectorOut[0] = (m_values[0] * aVectorIn[0]) + (m_values[2] * aVectorIn[1]);
    aVectorOut[1] = (m_values[1] * aVectorIn[0]) + (m_values[3] * aVectorIn[1]);
  }

  template <typename T>
  TL_FI T Matrix2<T>::Determinant() const
  {
    return (m_values[0] * m_values[3]) - (m_values[2] * m_values[1]);
  }

  template <typename T>
  TL_FI bool Matrix2<T>::Inverse()
  {
    Matrix2<T> temp = *this;
    return Inverse(temp);
  }

  template <typename T>
  TL_FI bool Matrix2<T>::Inverse(const Matrix2<T>& aMatrix)
  {
    T detInv = ((T)1) / aMatrix.Determinant();

    if (Math<T>::Approx(detInv, (T)0)) { return false; }

    m_values[0] = aMatrix[3] * detInv;    
    m_values[1] = -aMatrix[1] * detInv;
    m_values[2] = -aMatrix[2] * detInv;
    m_values[3] = aMatrix[0] * detInv;

    return true;
  }

  template <typename T>
  TL_FI void Matrix2<T>::Adjoint()
  {
    Matrix2<T> temp = *this;
    Adjoint(temp);
  }

  template <typename T>
  TL_FI void Matrix2<T>::Adjoint(const Matrix2<T>& aMatrix)
  {
    m_values[0] = aMatrix[3];
    m_values[1] = -aMatrix[1];
    m_values[2] = -aMatrix[2];
    m_values[3] = aMatrix[0];
  }

  // Taken directly from WildMagic5 (modified to suit out needs)
  template <typename T>
  TL_FI void Matrix2<T>::Orthonormalize()
  {
    T invLength = Math<T>::InvSqrt(m_values[0] * m_values[0] +
      m_values[1] * m_values[1]);
    m_values[0] *= invLength;
    m_values[1] *= invLength;

    // Compute q1
    T dot0 = (m_values[0] * m_values[2]) + (m_values[1] * m_values[3]);
    m_values[2] -= dot0 * m_values[0];
    m_values[3] -= dot0 * m_values[2];

    invLength = Math<T>::InvSqrt(m_values[2] * m_values[2] + 
      m_values[3] * m_values[3]);

    m_values[2] *= invLength;
    m_values[3] *= invLength;
  }

  template <typename T>
  TL_FI void Matrix2<T>::FastOrthonormalize()
  {
    T invLength = Math<T>::FastInvSqrt(m_values[0] * m_values[0] +
      m_values[2] * m_values[2]);
    m_values[0] *= invLength;
    m_values[2] *= invLength;

    // Compute q1
    T dot0 = m_values[0] * m_values[1] + m_values[2] * m_values[3];
    m_values[1] -= dot0 * m_values[0];
    m_values[3] -= dot0 * m_values[2];

    invLength = Math<T>::FastInvSqrt(m_values[1] * m_values[1] + 
      m_values[3] * m_values[3]);

    m_values[1] *= invLength;
    m_values[3] *= invLength;
  }

  template <typename T>
  TL_FI void Matrix2<T>::EigenDecomposition(Matrix2<T>& aRot, Matrix2<T>& aDiag) const
  {
    T sum = Math<T>::FAbs(m_values[0]) + Math<T>::FAbs(m_values[3]);
    if (Math<T>::FAbs(m_values[2]) + sum == sum)
    {
      // The matrix is diagonal
      aRot[0] = (T)1; aRot[2] = (T)0; 
      aRot[1] = (T)0; aRot[3] = (T)1;

      aDiag[0] = m_values[0]; aDiag[2] = (T)0;
      aDiag[1] = (T)0;        aDiag[3] = m_values[3];

      return;
    }

    T eigVal0and1[2];

    T trace = m_values[0] + m_values[3];
    T diff = m_values[0] - m_values[3];
    T discr = Math<T>::Sqrt(diff * diff + ((T)4) * m_values[2] * m_values[2]);
    eigVal0and1[0] = ((T)0.5) * (trace - discr);
    eigVal0and1[1] = ((T)0.5) * (trace + discr);
    aDiag.MakeDiagonal( eigVal0and1 );

    T cs, sn;
    if (diff >= (T)0)
    {
      cs = m_values[2];
      sn = eigVal0and1[0] - m_values[0];
    }
    else
    {
      cs = eigVal0and1[0] - m_values[3];
      sn = m_values[2];
    }

    T invLength = Math<T>::InvSqrt(cs * cs + sn * sn);
    cs *= invLength;
    sn *= invLength;

    aRot.m_values[0] = cs;
    aRot.m_values[1] = sn;
    aRot.m_values[2] = -sn;
    aRot.m_values[3] = cs;
  }
};
