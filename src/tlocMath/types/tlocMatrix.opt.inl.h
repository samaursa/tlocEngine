#ifndef TLOC_MATRIX_OPT_INL
#define TLOC_MATRIX_OPT_INL

#ifndef TLOC_MATRIX_H
#error "Must include header before including the inline file"
#endif

#include "tlocMatrix.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/data_structures/tlocTable.inl.h>
#include <tlocCore/data_structures/tlocVariadic.inl.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Matrix_TI<N, N>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define MATRIX_TEMPS  typename T, tl_size T_Size
#define MATRIX_PARAMS T, T_Size
#define MATRIX_TYPE   typename Matrix_TI<MATRIX_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Misc Macros

#define ITERATE_MATRIX      for (tl_int i = 0; i < k_MatrixSize; ++i)
#define ITERATE_MATRIX_HALF for (tl_int i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <MATRIX_TEMPS>
  Matrix_TI<MATRIX_PARAMS>::
    Matrix_TI()
    : base_type()
  { }

  template <MATRIX_TEMPS>
  Matrix_TI<MATRIX_PARAMS>::
    Matrix_TI(value_type aValue)
    : base_type(aValue)
  { }

  template <MATRIX_TEMPS>
  Matrix_TI<MATRIX_PARAMS>::
    Matrix_TI(const value_type (&values)[k_MatrixSize], matrix_order aOrder)
    : base_type(values, aOrder)
  { }

  template <MATRIX_TEMPS>
  Matrix_TI<MATRIX_PARAMS>::
    Matrix_TI(const tloc::core::data_structs::Variadic<T, k_MatrixSize> &a_vars,
              matrix_order a_order)
     : base_type(a_vars, a_order)
  { }

  //------------------------------------------------------------------------
  // Modifiers

  template <MATRIX_TEMPS>
  void
    Matrix_TI<MATRIX_PARAMS>::
    MakeZero()
  {
    memset(m_values, 0, sizeof(T) * k_MatrixSize);
  }

  template <MATRIX_TEMPS>
  void
    Matrix_TI<MATRIX_PARAMS>::
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
    Matrix_TI<MATRIX_PARAMS>::
    MakeDiagonal(const value_type values[T_Size])
  {
    MakeZero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, values[i]);
    }
  }

  template <MATRIX_TEMPS>
  void
    Matrix_TI<MATRIX_PARAMS>::
    MakeDiagonal(const Vector_T<value_type, T_Size>& a_diagonal)
  {
    MakeZero();
    ITERATE_MATRIX_HALF
    {
      Set(i, i, a_diagonal[i]);
    }
  }

  //------------------------------------------------------------------------
  // Math operations

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix_TI<MATRIX_PARAMS>::
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
  void Matrix_TI<MATRIX_PARAMS>::
    Add(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    base_type::operator=(aMatrix1);
    Add(aMatrix2);
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix_TI<MATRIX_PARAMS>::
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
  void Matrix_TI<MATRIX_PARAMS>::
    Sub(const this_type& aMatrix1, const this_type& aMatrix2)
  {
    *this = aMatrix1.Sub(aMatrix2);
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix_TI<MATRIX_PARAMS>::
    Mul(const this_type& a_matrix) const
  {
    this_type temp(*this);

    for (tl_size i = 0; i < T_Size; ++i)
    {
      Vector_T<value_type, T_Size> row;
      temp.GetRow(i, row);
      for (tl_size j = 0; j < T_Size; ++j)
      {
        Vector_T<value_type, T_Size> col;
        a_matrix.GetCol(j, col);

        temp.Set(i, j, row.Dot(col));
      }
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  void Matrix_TI<MATRIX_PARAMS>::
    Mul(const this_type& a_matrix1, const this_type& a_matrix2)
  {
    *this = a_matrix1.Mul(a_matrix2);
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix_TI<MATRIX_PARAMS>::
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
    Matrix_TI<MATRIX_PARAMS>::
    Mul(const vec_type& a_vecIn, vec_type& a_vecOut) const
  {
    ITERATE_MATRIX_HALF
    {
      Vector_T<value_type, T_Size> row;
      GetRow(i, row);
      a_vecOut[(tl_int)i] = a_vecIn.Dot(row);
    }
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::vec_type
    Matrix_TI<MATRIX_PARAMS>::
    Mul(const vec_type& a_vecIn) const
  {
    vec_type temp;
    Mul(a_vecIn, temp);
    return temp;
  }

  template <MATRIX_TEMPS>
  MATRIX_TYPE::this_type
    Matrix_TI<MATRIX_PARAMS>::
    Div(const_reference aReal) const
  {
    TLOC_ASSERT_LOW_LEVEL(math::IsEqual<value_type>(aReal, 0.0f) == false,
      "The matrix is being divided by zero!");

    this_type temp(*this);

    ITERATE_MATRIX
    {
      temp.m_values[i] /= aReal;
    }

    return temp;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type
    Matrix_TI<MATRIX_PARAMS>::
    Transpose() const
  {
    this_type temp(m_values, base_type::k_RowMajor);
    return temp;
  }

  template <MATRIX_TEMPS>
  void Matrix_TI<MATRIX_PARAMS>::
    Transpose(const this_type& a_matrix)
  {
    Set(a_matrix.m_values, base_type::k_RowMajor);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <MATRIX_TEMPS>
  void Matrix_TI<MATRIX_PARAMS>::
    GetDiagonal(Vector_T<value_type, T_Size>& aVector)
  {
    ITERATE_MATRIX_HALF
    {
      aVector[(tl_int)i] = m_values[((tl_int)i * T_Size) + (tl_int)i];
    }
  }

  //------------------------------------------------------------------------
  // Operators

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type
    Matrix_TI<MATRIX_PARAMS>::
    operator+ (const this_type& a_matrix) const
  {
    this_type returnMat = Add(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type
    Matrix_TI<MATRIX_PARAMS>::
    operator- (const this_type& a_matrix) const
  {
    this_type returnMat = Sub(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type
    Matrix_TI<MATRIX_PARAMS>::
    operator* (const this_type& a_matrix) const
  {
    this_type returnMat = Mul(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type
    Matrix_TI<MATRIX_PARAMS>::
    operator* (const_reference a_value) const
  {
    this_type returnMat = Mul(a_value);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  Vector_T<typename Matrix_TI<MATRIX_PARAMS>::value_type, T_Size>
    Matrix_TI<MATRIX_PARAMS>::
    operator* (const Vector_T<value_type, T_Size>& a_vector) const
  {
    vec_type returnVec = Mul(a_vector);
    return returnVec;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type
    Matrix_TI<MATRIX_PARAMS>::
    operator/ (const_reference a_matrix) const
  {
    this_type returnMat = Div(a_matrix);
    return returnMat;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type&
    Matrix_TI<MATRIX_PARAMS>::
    operator+= (const this_type& a_matrix)
  {
    *this = Add(a_matrix);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type&
    Matrix_TI<MATRIX_PARAMS>::
    operator-= (const this_type& a_matrix)
  {
    *this = Sub(a_matrix);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type&
    Matrix_TI<MATRIX_PARAMS>::
    operator*= (const this_type& a_matrix)
  {
    *this = Mul(a_matrix);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type&
    Matrix_TI<MATRIX_PARAMS>::
    operator*= (const_reference a_value)
  {
    *this = Mul(a_value);
    return *this;
  }

  template <MATRIX_TEMPS>
  typename Matrix_TI<MATRIX_PARAMS>::this_type&
    Matrix_TI<MATRIX_PARAMS>::
    operator/= (const_reference a_value)
  {
    *this = Div(a_value);
    return *this;
  }

  template <MATRIX_TEMPS>
  bool Matrix_TI<MATRIX_PARAMS>::
    operator==( const this_type& a_matrix )
  {
    ITERATE_MATRIX
    {
      if (!math::IsEqual(m_values[i], a_matrix[i])) { return false; }
    }

    return true;
  }

  template <MATRIX_TEMPS>
  bool Matrix_TI<MATRIX_PARAMS>::
    operator!=( const this_type& a_matrix )
  {
    return !operator==(a_matrix);
  }

};};};

#endif