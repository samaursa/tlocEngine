#pragma once
#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/data_structures/tlocTable.h>
#include <tlocMath/vector/tlocVector.h>

//////////////////////////////////////////////////////////////////////////
/* NOTES
 *
 * Matrices are arranged in column-major order in memory as well as matrix
 * layout. This means that each column of the matrix is a vector and
 * consequently the matrix/vector multiplication is performed by:
 *
 * M * v
 *
 * where `v` is a column vector. The matrix is arranged in memory in a
 * column-major layout, i.e. a 3x3 matrix will be layed out in memory such
 * that mat3x3[0], [1] and [2] indices correspond to the first column
 * vector. Similarly, [3], [4] and [5] indices correspond to the second
 * column vector and so on.
 */

namespace tloc { namespace math {

  template <typename T, tl_size T_Size>
  class Matrix : public core::Table<T, T_Size, T_Size>
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix<T, T_Size>                     this_type;
    typedef core::Table<T, T_Size, T_Size>        base_type;

    typedef typename base_type::table_order       table_order;
    typedef table_order                           matrix_order;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::value_type&       reference;
    typedef typename base_type::value_type const& const_reference;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::GetRow;
    using base_type::Set;
    using base_type::k_TableSize;
    using base_type::m_values;

  protected:

    enum { k_MatrixSize = k_TableSize };

  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix();

    // Copy constructor
    TL_FI Matrix(const this_type& aMatrix);

    // Copy constructor
    TL_FI Matrix(const base_type& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    TL_FI explicit Matrix(const_reference aValue);

    // Fill the matrix with values in a certain matrix order
    TL_FI Matrix(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    TL_FI Matrix(const core::Variadic<T, k_MatrixSize>& a_vars, matrix_order a_order);

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this matrix by setting all values to 0
    TL_FI void Zero();

    // Modifes this matrix by making it an identity matrix
    TL_FI void Identity();

    // Modifies this matrix to be a diagonal matrix
    TL_FI void MakeDiagonal(const value_type values[T_Size]);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by adding the incoming matrix
    TL_FI this_type& Add(const this_type& aMatrix);

    // Modifies this matrix by adding the incoming matrices and storing the
    // result in this matrix
    TL_FI void Add(const this_type& aMatrix1,
                   const this_type& aMatrix2);

    // Modifies this matrix by subtracting the incoming matrix
    TL_FI this_type& Sub(const this_type& aMatrix);

    // Modifies this matrix by subtracting the incoming matrices and storing
    // the result in this matrix
    TL_FI void Sub(const this_type& aMatrix1,
                   const this_type& aMatrix2);

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI this_type& Mul(const this_type& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const this_type& aMatrix1,
                   const this_type& aMatrix2);

    // Modifies this matrix by multiplying the incoming real number
    TL_FI this_type& Mul(const_reference aReal);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<value_type, T_Size>& aVectorIn,
                   Vector<value_type, T_Size>& aVectorOut) const;

    // Modifies this matrix by dividing the incoming real number
    TL_FI this_type& Div(const_reference aReal);

    // Modifies this matrix by transposing the matrix
    TL_FI this_type& Transpose();

    // Modifies this matrix by transposing the incoming matrix and storing
    // the result in this matrix
    TL_FI void Transpose(const this_type& aMatrix);

    //------------------------------------------------------------------------
    // Accessors

    // Stores the diagonal of this Matrix in aVector
    TL_FI void GetDiagonal(Vector<value_type, T_Size>& aVector);

    //------------------------------------------------------------------------
    // Operators

    TL_FI this_type   operator+ (const this_type& a_matrix) const;
    TL_FI this_type   operator- (const this_type& a_matrix) const;
    TL_FI this_type   operator* (const this_type& a_matrix) const;
    TL_FI this_type   operator* (const_reference a_value) const;
    TL_FI this_type   operator/ (const_reference a_value) const;

    TL_FI Vector<value_type, T_Size>
      operator* (const Vector<value_type, T_Size>& a_vector) const;

    TL_FI this_type&   operator+= (const this_type& a_matrix);
    TL_FI this_type&   operator-= (const this_type& a_matrix);
    TL_FI this_type&   operator*= (const this_type& a_matrix);
    TL_FI this_type&   operator*= (const_reference a_value);
    TL_FI this_type&   operator/= (const_reference a_value);

    //TL_FI this_type& operator=(const this_type& a_other);
    TL_FI bool operator== (const this_type& aMatrix);
    TL_FI bool operator!= (const this_type& aMatrix);

    //------------------------------------------------------------------------
    // Special Matrices

    static const this_type ZERO;
    static const this_type IDENTITY;

  private:

    static this_type DoGetIdentity();
  };

  //------------------------------------------------------------------------
  // Static const definitions
  template <typename T, tl_size T_Size>
  const typename Matrix<T, T_Size>::this_type Matrix<T, T_Size>::ZERO =
    typename Matrix<T, T_Size>::this_type(0);

  template <typename T, tl_size T_Size>
  const typename Matrix<T, T_Size>::this_type Matrix<T, T_Size>::IDENTITY =
    Matrix<T, T_Size>::this_type::DoGetIdentity();

  template <typename T, tl_size T_Size>
  typename Matrix<T, T_Size>::this_type
    Matrix<T, T_Size>::DoGetIdentity()
  {
    this_type temp;
    temp.Identity();
    return temp;
  }

};};

#endif