#ifndef TLOC_MATRIX_INL
#define TLOC_MATRIX_INL

#ifndef TLOC_MATRIX_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Matrix<N, N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_MATRIX      for (tl_size i = 0; i < k_MatrixSize; ++i)
#define ITERATE_MATRIX_HALF for (tl_size i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>::Matrix()
    : Table() {}

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>::Matrix(const Matrix<T, T_Size>& aMatrix)
    : Table(aMatrix) {}

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>::Matrix(const T& aValue)
    : Table(aValue) {}

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>::Matrix(const T (&values)[k_MatrixSize],
                                  MATRIX_ORDER aOrder)
                                  : Table(values, aOrder)
  {}

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Zero()
  {
    memset(m_values, 0, sizeof(T) * k_MatrixSize);
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Identity()
  {
    Zero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, 1);
    }
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::MakeDiagonal(const T values[T_Size])
  {
    Zero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, values[i]);
    }
  }

  //------------------------------------------------------------------------
  // Math operations

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>& Matrix<T, T_Size>
    ::Add(const Matrix<T, T_Size>& aMatrix)
  {
    ITERATE_MATRIX
    {
      m_values[i] += aMatrix[i];
    }

    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Add(const Matrix<T, T_Size>& aMatrix1,
    const Matrix<T, T_Size>& aMatrix2)
  {
    operator=(aMatrix1);
    Add(aMatrix2);
  }

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>& Matrix<T, T_Size>
    ::Sub(const Matrix<T, T_Size>& aMatrix)
  {
    ITERATE_MATRIX
    {
      m_values[i] -= aMatrix[i];
    }

    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Sub(const Matrix<T, T_Size>& aMatrix1,
    const Matrix<T, T_Size>& aMatrix2)
  {
    operator=(aMatrix1);
    Sub(aMatrix2);
  }

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>& Matrix<T, T_Size>
    ::Mul(const Matrix<T, T_Size>& aMatrix)
  {
    for (tl_size i = 0; i < T_Size; ++i)
    {
      Vector<T, T_Size> row;
      GetRow(i, row);
      for (tl_size j = 0; j < T_Size; ++j)
      {
        Vector<T, T_Size> col;
        aMatrix.GetCol(j, col);

        Set(i, j, row.Dot(col));
      }
    }

    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Mul(const Matrix<T, T_Size>& aMatrix1,
                                    const Matrix<T, T_Size>& aMatrix2)
  {
    operator=(aMatrix1);
    Mul(aMatrix2);
  }

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>& Matrix<T, T_Size>::Mul(const T& aReal)
  {
    ITERATE_MATRIX
    {
      m_values[i] *= aReal;
    }

    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Mul(const Vector<T, T_Size>& aVectorIn,
                                    Vector<T, T_Size>& aVectorOut)
  {
    ITERATE_MATRIX_HALF
    {
      Vector<T, T_Size> row;
      GetRow(i, row);
      aVectorOut[i] = aVectorIn.Dot(row);
    }
  }

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>& Matrix<T, T_Size>::Div(const T& aReal)
  {
    TLOC_ASSERT_LOW_LEVEL(Math<T>::Approx(aReal, 0.0f) == false,
      "The matrix is being divided by zero!");

    ITERATE_MATRIX
    {
      m_values[i] /= aReal;
    }

    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI Matrix<T, T_Size>& Matrix<T, T_Size>::Transpose()
  {
    Matrix<T, T_Size> temp = *this;
    Set(temp.m_values, k_RowMajor);

    return *this;
  }

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::Transpose(const Matrix<T, T_Size>& aMatrix)
  {
    Set(aMatrix.m_values, k_RowMajor);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <typename T, tl_size T_Size>
  TL_FI void Matrix<T, T_Size>::GetDiagonal(Vector<T, T_Size>& aVector)
  {
    ITERATE_MATRIX_HALF
    {
      aVector[i] = m_values[(i * T_Size) + i];
    }
  }

  //------------------------------------------------------------------------
  // Operators

  template <typename T, tl_size T_Size>
  TL_FI bool Matrix<T, T_Size>::operator==( const Matrix<T, T_Size>& aMatrix )
  {
    ITERATE_MATRIX
    {
      if (!Math<T>::Approx(m_values[i], aMatrix[i])) { return false; }
    }

    return true;
  }

  template <typename T, tl_size T_Size>
  TL_FI bool Matrix<T, T_Size>::operator!=( const Matrix<T, T_Size>& aMatrix )
  {
    return !operator==(aMatrix);
  }

};};

#endif