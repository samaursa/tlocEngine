#ifndef TLOC_MATRIX_INL
#define TLOC_MATRIX_INL

#ifndef TLOC_MATRIX_H
#error "Must include header before including the inline file"
#endif

#include "tlocMatrix.h"
#include <tlocCore/data_structures/tlocTable.inl>
#include <tlocCore/data_structures/tlocVariadic.inl>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix<N, N>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_TYPES typename T, tl_size T_Size
#define MATRIX_PARAMS T, T_Size

  //////////////////////////////////////////////////////////////////////////
  // Misc Macros

#define ITERATE_MATRIX      for (tl_size i = 0; i < k_MatrixSize; ++i)
#define ITERATE_MATRIX_HALF for (tl_size i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <MATRIX_TYPES>
  Matrix<MATRIX_PARAMS>::
    Matrix()
    : base_type() 
  { }

  template <MATRIX_TYPES>
  Matrix<MATRIX_PARAMS>::
    Matrix(const this_type& aMatrix)
    : base_type(aMatrix)
  { }

  template <MATRIX_TYPES>
  Matrix<MATRIX_PARAMS>::
    Matrix(const base_type& aMatrix)
    : base_type(aMatrix)
  { }

  template <MATRIX_TYPES>
  Matrix<MATRIX_PARAMS>::
    Matrix(const_reference aValue)
    : base_type(aValue) 
  { }

  template <MATRIX_TYPES>
  Matrix<MATRIX_PARAMS>::
    Matrix(const value_type (&values)[k_MatrixSize],
                                      matrix_order aOrder) 
                                      : base_type(values, aOrder)
  { }

  template <MATRIX_TYPES>
  Matrix<MATRIX_PARAMS>::
    Matrix (const tloc::core::data_structs::Variadic<T, k_MatrixSize> &a_vars, 
            matrix_order a_order) 
     : base_type(a_vars, a_order)
  { }

  //------------------------------------------------------------------------
  // Modifiers

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Zero()
  {
    memset(m_values, 0, sizeof(T) * k_MatrixSize);
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Identity()
  {
    Zero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, 1);
    }
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    MakeDiagonal(const value_type values[T_Size])
  {
    Zero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, values[i]);
    }
  }

  //------------------------------------------------------------------------
  // Math operations

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type& 
    Matrix<MATRIX_PARAMS>::
    Add(const this_type& aMatrix)
  {
    ITERATE_MATRIX
    {
      m_values[i] += aMatrix[i];
    }

    return *this;
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Add(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    base_type::operator=(aMatrix1);
    Add(aMatrix2);
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type& 
    Matrix<MATRIX_PARAMS>::
    Sub(const this_type& aMatrix)
  {
    ITERATE_MATRIX
    {
      m_values[i] -= aMatrix[i];
    }

    return *this;
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Sub(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    base_type::operator=(aMatrix1);
    Sub(aMatrix2);
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type& 
    Matrix<MATRIX_PARAMS>::
    Mul(const this_type& aMatrix)
  {
    for (tl_size i = 0; i < T_Size; ++i)
    {
      Vector<value_type, T_Size> row;
      GetRow(i, row);
      for (tl_size j = 0; j < T_Size; ++j)
      {
        Vector<value_type, T_Size> col;
        aMatrix.GetCol(j, col);

        Set(i, j, row.Dot(col));
      }
    }

    return *this;
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Mul(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    base_type::operator=(aMatrix1);
    Mul(aMatrix2);
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type& 
    Matrix<MATRIX_PARAMS>::
    Mul(const_reference aReal)
  {
    ITERATE_MATRIX
    {
      m_values[i] *= aReal;
    }

    return *this;
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Mul(const Vector<value_type, T_Size>& aVectorIn, 
        Vector<value_type, T_Size>& aVectorOut) const
  {
    ITERATE_MATRIX_HALF
    {
      Vector<value_type, T_Size> row;
      GetRow(i, row);
      aVectorOut[(tl_int)i] = aVectorIn.Dot(row);
    }
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type& 
    Matrix<MATRIX_PARAMS>::
    Div(const_reference aReal)
  {
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::Approx(aReal, 0.0f) == false,
      "The matrix is being divided by zero!");

    ITERATE_MATRIX
    {
      m_values[i] /= aReal;
    }

    return *this;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type& 
    Matrix<MATRIX_PARAMS>::
    Transpose()
  {
    this_type temp(*this);
    Set(temp.m_values, base_type::k_RowMajor);

    return *this;
  }

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    Transpose(const this_type& aMatrix)
  {
    Set(aMatrix.m_values, base_type::k_RowMajor);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <MATRIX_TYPES>
  void Matrix<MATRIX_PARAMS>::
    GetDiagonal(Vector<value_type, T_Size>& aVector)
  {
    ITERATE_MATRIX_HALF
    {
      aVector[(tl_int)i] = m_values[((tl_int)i * T_Size) + (tl_int)i];
    }
  }

  //------------------------------------------------------------------------
  // Operators

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator+ (const this_type& a_matrix) const
  {
    this_type returnMat(*this);

    returnMat.Add(a_matrix);

    return returnMat;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator- (const this_type& a_matrix) const
  {
    this_type returnMat(*this);

    returnMat.Sub(a_matrix);

    return returnMat;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator* (const this_type& a_matrix) const
  {
    this_type returnMat(*this);

    returnMat.Mul(a_matrix);

    return returnMat;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator* (const_reference a_value) const
  {
    this_type returnMat(*this);

    returnMat.Mul(a_value);

    return returnMat;
  }

  template <MATRIX_TYPES>
  Vector<typename Matrix<MATRIX_PARAMS>::value_type, T_Size> 
    Matrix<MATRIX_PARAMS>::
    operator* (const Vector<value_type, T_Size>& a_vector) const
  {
    Vector<value_type, T_Size> returnVec;
    Mul(a_vector, returnVec);

    return returnVec;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator/ (const_reference a_matrix) const
  {
    this_type returnMat(*this);

    returnMat.Div(a_matrix);

    return returnMat;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator+= (const this_type& a_matrix)
  {
    Add(a_matrix);
    return *this;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator-= (const this_type& a_matrix)
  {
    Sub(a_matrix);
    return *this;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator*= (const this_type& a_matrix)
  {
    Mul(a_matrix);
    return *this;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator*= (const_reference a_value)
  {
    Mul(a_value);
    return *this;
  }

  template <MATRIX_TYPES>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator/= (const_reference a_value)
  {
    Div(a_value);
    return *this;
  }

  //template <MATRIX_TYPES>
  //Matrix<MATRIX_PARAMS>& Matrix<MATRIX_PARAMS>::
  //  operator=(const this_type& aMatrix )
  //{
  //  base_type::operator =(aMatrix);
  //  return *this;
  //}

  template <MATRIX_TYPES>
  bool Matrix<MATRIX_PARAMS>::
    operator==( const this_type& aMatrix )
  {
    ITERATE_MATRIX
    {
      if (!Math<T>::Approx(m_values[i], aMatrix[i])) { return false; }
    }

    return true;
  }

  template <MATRIX_TYPES>
  bool Matrix<MATRIX_PARAMS>::
    operator!=( const this_type& aMatrix )
  {
    return !operator==(aMatrix);
  }

};};};

#endif