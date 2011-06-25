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
                           const Matrix3<T>& aMatrix3)
{

}

template <typename T>
TL_FI void Matrix3<T>::Mul(const Vector<T, 3>& aVectorIn, 
                           Vector<T, 3>& aVectorOut)
{
}

template <typename T>
TL_FI T Matrix3<T>::Determinant() const
{
  return 0;
}

template <typename T>
TL_FI bool Matrix3<T>::Inverse()
{
  return false;
}

template <typename T>
TL_FI bool Matrix3<T>::Inverse(const Matrix3<T>& aMatrix)
{
  return false;
}

template <typename T>
TL_FI void Matrix3<T>::Adjoint()
{
}

template <typename T>
TL_FI void Matrix3<T>::Adjoint(const Matrix3<T>& aMatrix)
{
}

// Taken directly from WildMagic5 (modified to suit out needs)
template <typename T>
TL_FI void Matrix3<T>::Orthonormalize()
{
}

template <typename T>
TL_FI void Matrix3<T>::FastOrthonormalize()
{
}

template <typename T>
TL_FI void Matrix3<T>::EigenDecomposition(Matrix3<T>& aRot, Matrix3<T>& aDiag) const
{
}
