namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Matrix<N, N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_MATRIX for (u32 i = 0; i < MATRIX_SIZE; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <typename T, u32 T_Size>
  TL_FI Matrix<T, T_Size>::Matrix()
    : Table() {}

  template <typename T, u32 T_Size>
  TL_FI Matrix<T, T_Size>::Matrix(const Matrix<T, T_Size>& aMatrix)
    : Table(aMatrix) {}

  template <typename T, u32 T_Size>
  TL_FI Matrix<T, T_Size>::Matrix(const T& aValue)
    : Table(aValue) {}

  template <typename T, u32 T_Size>
  TL_FI Matrix<T, T_Size>::Matrix(const T values[MATRIX_SIZE], MATRIX_ORDER aOrder)
    : Table(values, aOrder) {}

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Zero()
  {
    Set(0);
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Identity()
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

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Add(const Matrix<T, T_Size>& aMatrix)
  {
    ITERATE_MATRIX
    {
      m_values[i] += aMatrix[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Add(const Matrix<T, T_Size>& aMatrix1, 
    const Matrix<T, T_Size>& aMatrix2)
  {
    operator=(aMatrix1);
    Add(aMatrix2);
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Sub(const Matrix<T, T_Size>& aMatrix)
  {
    ITERATE_MATRIX
    {
      m_values[i] -= aMatrix[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Sub(const Matrix<T, T_Size>& aMatrix1, 
    const Matrix<T, T_Size>& aMatrix2)
  {
    operator=(aMatrix1);
    Sub(aMatrix2);
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Mul(const Matrix<T, T_Size>& aMatrix)
  {
    for (u32 i = 0; i < T_Size; ++i)
    {
      Vector<T, T_Size> row;
      GetRow(i, row);
      for (u32 j = 0; j < T_Size; ++j)
      {      
        Vector<T, T_Size> col;
        aMatrix.GetCol(j, col);

        Set(i, j, row.Dot(col));
      }
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Mul(const Matrix<T, T_Size>& aMatrix1, 
                                    const Matrix<T, T_Size>& aMatrix2)
  {
    operator=(aMatrix1);
    Mul(aMatrix2);
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Mul(const T& aReal)
  {
    ITERATE_MATRIX
    {
      m_values[i] *= aReal;
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Mul(const Vector<T, T_Size>& aVectorIn, 
                                    Vector<T, T_Size>& aVectorOut)
  {
    for (u32 i = 0; i < T_Size; ++i)
    {
      Vector<T, T_Size> row;
      GetRow(i, row);
      aVectorOut[i] = aVectorIn.Dot(row);
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Div(const T& aReal)
  {
    ITERATE_MATRIX
    {
      m_values[i] /= aReal;
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Transpose()
  {
    Matrix<T, T_Size> temp = *this;
    Set(temp, ROW_MAJOR);
  }

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::Transpose(const Matrix<T, T_Size>& aMatrix)
  {
    Set(aMatrix, ROW_MAJOR);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <typename T, u32 T_Size>
  TL_FI void Matrix<T, T_Size>::GetDiagonal(Vector<T, T_Size>& aVector)
  {
    for (u32 i = 0; i < T_Size; ++i)
    {
      aVector[i] = m_values[(i * T_Size) + i];
    }
  }
};