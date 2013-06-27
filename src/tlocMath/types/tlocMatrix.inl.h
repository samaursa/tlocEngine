#ifndef TLOC_MATRIX_INL
#define TLOC_MATRIX_INL

#ifndef TLOC_MATRIX_H
#error "Must include header before including the inline file"
#endif

#include "tlocMatrix.h"
#include <tlocCore/data_structures/tlocTable.inl.h>
#include <tlocCore/data_structures/tlocVariadic.inl.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix<N, N>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_TEMPS  typename T, tl_size T_Size
#define MATRIX_PARAMS T, T_Size
#define MATRIX_TYPE   typename Matrix<MATRIX_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Misc Macros

#define ITERATE_MATRIX      for (tl_size i = 0; i < k_MatrixSize; ++i)
#define ITERATE_MATRIX_HALF for (tl_size i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <MATRIX_TEMPS>
  Matrix<MATRIX_PARAMS>::
    Matrix()
    : base_type()
  { }

  template <MATRIX_TEMPS>
  Matrix<MATRIX_PARAMS>::
    Matrix(value_type aValue)
    : base_type(aValue)
  { }

  template <MATRIX_TEMPS>
  Matrix<MATRIX_PARAMS>::
    Matrix(const value_type (&values)[k_MatrixSize],
                                      matrix_order aOrder)
                                      : base_type(values, aOrder)
  { }

  template <MATRIX_TEMPS>
  Matrix<MATRIX_PARAMS>::
    Matrix (const tloc::core::data_structs::Variadic<T, k_MatrixSize> &a_vars,
            matrix_order a_order)
     : base_type(a_vars, a_order)
  { }

  //------------------------------------------------------------------------
  // Modifiers

  template <MATRIX_TEMPS>
  void
    Matrix<MATRIX_PARAMS>::
    MakeZero()
  {
    memset(m_values, 0, sizeof(T) * k_MatrixSize);
  }

  template <MATRIX_TEMPS>
  void
    Matrix<MATRIX_PARAMS>::
    MakeIdentity()
  {
    MakeZero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, 1);
    }
  }

  template <MATRIX_TEMPS>
  void
    Matrix<MATRIX_PARAMS>::
    MakeDiagonal(const value_type values[T_Size])
  {
    MakeZero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, values[i]);
    }
  }

  //------------------------------------------------------------------------
  // Math operations

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix<MATRIX_PARAMS>::
    Add(const this_type& a_matrix) const
  {
    this_type temp(*this);

    ITERATE_MATRIX
    {
      temp.m_values[i] += a_matrix[i];
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  void Matrix<MATRIX_PARAMS>::
    Add(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    base_type::operator=(aMatrix1);
    Add(aMatrix2);
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix<MATRIX_PARAMS>::
    Sub(const this_type& a_matrix) const
  {
    this_type temp(*this);

    ITERATE_MATRIX
    {
      temp.m_values[i] -= a_matrix[i];
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  void Matrix<MATRIX_PARAMS>::
    Sub(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    *this = aMatrix1.Sub(aMatrix2);
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix<MATRIX_PARAMS>::
    Mul(const this_type& a_matrix) const
  {
    this_type temp(*this);

    for (tl_size i = 0; i < T_Size; ++i)
    {
      Vector<value_type, T_Size> row;
      temp.GetRow(i, row);
      for (tl_size j = 0; j < T_Size; ++j)
      {
        Vector<value_type, T_Size> col;
        a_matrix.GetCol(j, col);

        temp.Set(i, j, row.Dot(col));
      }
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  void Matrix<MATRIX_PARAMS>::
    Mul(const this_type& a_matrix1, const this_type& a_matrix2)
  {
    *this = a_matrix1.Mul(a_matrix2);
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix<MATRIX_PARAMS>::
    Mul(const_reference aReal) const
  {
    this_type temp(*this);

    ITERATE_MATRIX
    {
      temp.m_values[i] *= aReal;
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  void
    Matrix<MATRIX_PARAMS>::
    Mul(const vec_type& a_vecIn, vec_type& a_vecOut) const
  {
    ITERATE_MATRIX_HALF
    {
      Vector<value_type, T_Size> row;
      GetRow(i, row);
      a_vecOut[(tl_int)i] = a_vecIn.Dot(row);
    }
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::vec_type
    Matrix<MATRIX_PARAMS>::
    Mul(const vec_type& a_vecIn) const
  {
    vec_type temp;
    Mul(a_vecIn, temp);
    return temp;
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix<MATRIX_PARAMS>::
    Div(const_reference aReal) const
  {
    TLOC_ASSERT_LOW_LEVEL(Math<value_type>::Approx(aReal, 0.0f) == false,
      "The matrix is being divided by zero!");

    this_type temp(*this);

    ITERATE_MATRIX
    {
      temp.m_values[i] /= aReal;
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    Transpose() const
  {
    this_type temp(m_values, base_type::k_RowMajor);
    return temp;
  }

  template <MATRIX_TEMPS>
  void Matrix<MATRIX_PARAMS>::
    Transpose(const this_type& a_matrix)
  {
    Set(a_matrix.m_values, base_type::k_RowMajor);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <MATRIX_TEMPS>
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

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator+ (const this_type& a_matrix) const
  {
    this_type returnMat(*this);

    returnMat.Add(a_matrix);

    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator- (const this_type& a_matrix) const
  {
    this_type returnMat = Sub(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator* (const this_type& a_matrix) const
  {
    this_type returnMat = Mul(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator* (const_reference a_value) const
  {
    this_type returnMat = Mul(a_value);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  Vector<typename Matrix<MATRIX_PARAMS>::value_type, T_Size>
    Matrix<MATRIX_PARAMS>::
    operator* (const Vector<value_type, T_Size>& a_vector) const
  {
    vec_type returnVec = Mul(a_vector);
    return returnVec;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type
    Matrix<MATRIX_PARAMS>::
    operator/ (const_reference a_matrix) const
  {
    this_type returnMat = Div(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator+= (const this_type& a_matrix)
  {
    *this = Add(a_matrix);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator-= (const this_type& a_matrix)
  {
    *this = Sub(a_matrix);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator*= (const this_type& a_matrix)
  {
    *this = Mul(a_matrix);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator*= (const_reference a_value)
  {
    *this = Mul(a_value);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix<MATRIX_PARAMS>::this_type&
    Matrix<MATRIX_PARAMS>::
    operator/= (const_reference a_value)
  {
    *this = Div(a_value);
    return *this;
  }

  //template <MATRIX_TEMPS>
  //Matrix<MATRIX_PARAMS>& Matrix<MATRIX_PARAMS>::
  //  operator=(const this_type& a_matrix )
  //{
  //  base_type::operator =(a_matrix);
  //  return *this;
  //}

  template <MATRIX_TEMPS>
  bool Matrix<MATRIX_PARAMS>::
    operator==( const this_type& a_matrix )
  {
    ITERATE_MATRIX
    {
      if (!Math<T>::Approx(m_values[i], a_matrix[i])) { return false; }
    }

    return true;
  }

  template <MATRIX_TEMPS>
  bool Matrix<MATRIX_PARAMS>::
    operator!=( const this_type& a_matrix )
  {
    return !operator==(a_matrix);
  }

};};};

#endif