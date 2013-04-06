#pragma once
#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/data_structures/tlocTable.h>
#include <tlocMath/types/tlocVector.h>

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

namespace tloc { namespace math { namespace types {

  template <typename T, tl_size T_Size>
  class Matrix : public core::data_structs::Table<T, T_Size, T_Size>
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix<T, T_Size>                             this_type;
    typedef core::data_structs::Table<T, T_Size, T_Size>  base_type;

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
    Matrix();

    // Copy constructor
    template <typename T_Real>
    Matrix(const core_ds::Table<T_Real, T_Size, T_Size>& aMatrix)
      : base_type(aMatrix)
    { }

    // Modifies this matrix by filling it with the incoming value
    explicit Matrix(value_type aValue);

    // Fill the matrix with values in a certain matrix order
    Matrix(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix(const core::data_structs::Variadic<T, k_MatrixSize>& a_vars,
           matrix_order a_order);

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this matrix by setting all values to 0
    void Zero();

    // Modifes this matrix by making it an identity matrix
    void Identity();

    // Modifies this matrix to be a diagonal matrix
    void MakeDiagonal(const value_type values[T_Size]);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by adding the incoming matrix
    this_type& Add(const this_type& aMatrix);

    // Modifies this matrix by adding the incoming matrices and storing the
    // result in this matrix
    void Add(const this_type& aMatrix1, const this_type& aMatrix2);

    // Modifies this matrix by subtracting the incoming matrix
    this_type& Sub(const this_type& aMatrix);

    // Modifies this matrix by subtracting the incoming matrices and storing
    // the result in this matrix
    void Sub(const this_type& aMatrix1, const this_type& aMatrix2);

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    this_type& Mul(const this_type& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    void Mul(const this_type& aMatrix1, const this_type& aMatrix2);

    // Modifies this matrix by multiplying the incoming real number
    this_type& Mul(const_reference aReal);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the
    // result is: vOut = M * vIn
    void Mul(const Vector<value_type, T_Size>& aVectorIn,
             Vector<value_type, T_Size>& aVectorOut) const;

    // Modifies this matrix by dividing the incoming real number
    this_type& Div(const_reference aReal);

    // Modifies this matrix by transposing the matrix
    this_type& Transpose();

    // Modifies this matrix by transposing the incoming matrix and storing
    // the result in this matrix
    void Transpose(const this_type& aMatrix);

    //------------------------------------------------------------------------
    // Accessors

    // Stores the diagonal of this Matrix in aVector
    void GetDiagonal(Vector<value_type, T_Size>& aVector);

    //------------------------------------------------------------------------
    // Operators

    this_type   operator+ (const this_type& a_matrix) const;
    this_type   operator- (const this_type& a_matrix) const;
    this_type   operator* (const this_type& a_matrix) const;
    this_type   operator* (const_reference a_value) const;
    this_type   operator/ (const_reference a_value) const;

    Vector<value_type, T_Size>
      operator* (const Vector<value_type, T_Size>& a_vector) const;

    this_type&   operator+= (const this_type& a_matrix);
    this_type&   operator-= (const this_type& a_matrix);
    this_type&   operator*= (const this_type& a_matrix);
    this_type&   operator*= (const_reference a_value);
    this_type&   operator/= (const_reference a_value);

    //this_type& operator=(const this_type& a_other);
    bool operator== (const this_type& aMatrix);
    bool operator!= (const this_type& aMatrix);

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

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T, tl_size T_Size>
  typename Matrix<T, T_Size>::this_type
    Matrix<T, T_Size>::
    DoGetIdentity()
  {
    this_type temp;
    temp.Identity();
    return temp;
  }

};};};

#endif