//////////////////////////////////////////////////////////////////////////
// Matrix<N, N>

//------------------------------------------------------------------------
// Macros

#define ITERATE_MATRIX for (u32 i = 0; i < MATRIX_SIZE; ++i)

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix()
: Table() {}

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix(const Matrix<T, T_SIZE>& aMatrix)
: Table(aMatrix) {}

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix(const T& aValue)
: Table(aValue) {}

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix(const T values[MATRIX_SIZE], MATRIX_ORDER aOrder)
: Table(values, aOrder) {}

//------------------------------------------------------------------------
// Modifiers

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Zero()
{
  Set(0);
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Identity()
{
  /*for (u32 i = 0; i < T_SIZE; ++i)
  {
    Vector<T, T_SIZE> vec;
    vec.Zero();
    vec[i] = 1;
    SetCol(
  }*/
}

//------------------------------------------------------------------------
// Math operations

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Add(const Matrix<T, T_SIZE>& aMatrix)
{
  ITERATE_MATRIX
  {
    m_values[i] += aMatrix[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Add(const Matrix<T, T_SIZE>& aMatrix1, 
                                  const Matrix<T, T_SIZE>& aMatrix2)
{
  operator=(aMatrix1);
  Add(aMatrix2);
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Sub(const Matrix<T, T_SIZE>& aMatrix)
{
  ITERATE_MATRIX
  {
    m_values[i] -= aMatrix[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Sub(const Matrix<T, T_SIZE>& aMatrix1, 
                                  const Matrix<T, T_SIZE>& aMatrix2)
{
  operator=(aMatrix1);
  Sub(aMatrix2);
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Mul(const Matrix<T, T_SIZE>& aMatrix)
{
  for (u32 i = 0; i < T_SIZE; ++i)
  {
    Vector<T, T_SIZE> row;
    GetRow(i, row);
    for (u32 j = 0; j < T_SIZE; ++j)
    {      
      Vector<T, T_SIZE> col;
      aMatrix.GetCol(j, col);
      
      Set(i, j, row.Dot(col));
    }
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Mul(const Matrix<T, T_SIZE>& aMatrix1, 
                                  const Matrix<T, T_SIZE>& aMatrix2)
{
  operator=(aMatrix1);
  Mul(Matrix2);
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Mul(const T& aReal)
{
  ITERATE_MATRIX
  {
    m_values[i] *= aReal;
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Div(const T& aReal)
{
  ITERATE_MATRIX
  {
    m_values[i] /= aReal;
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Transpose()
{
  Matrix<T, T_SIZE> temp = *this;
  Set(temp, ROW_MAJOR);
}

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::Transpose(const Matrix<T, T_SIZE>& aMatrix)
{
  Set(aMatrix, ROW_MAJOR);
}

//------------------------------------------------------------------------
// Accessors

template <typename T, u32 T_SIZE>
TL_FI void Matrix<T, T_SIZE>::GetDiagonal(Vector<T, T_SIZE>& aVector)
{
  for (u32 i = 0; i < T_SIZE; ++i)
  {
    aVector[i] = m_values[(i * T_SIZE) + i];
  }
}