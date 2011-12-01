#pragma once
#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTable.h"
#include "tlocMath/tlocVector.h"

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

  template <typename T, u32 T_Size>
  class Matrix : public core::Table<T, T_Size, T_Size>
  {
  protected:
    enum { MATRIX_SIZE = TABLE_SIZE };

  public:
    //------------------------------------------------------------------------
    // Constructors

    typedef TABLE_ORDER MATRIX_ORDER;

    // Empty default constructor
    TL_FI Matrix();

    // Copy constructor
    TL_FI Matrix(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    TL_FI explicit Matrix(const T& aValue);

    // Fill the matrix with values in a certain matrix order
    TL_FI Matrix(const T values[MATRIX_SIZE], MATRIX_ORDER aOrder);

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this matrix by setting all values to 0
    TL_FI void Zero();

    // Modifes this matrix by making it an identity matrix
    TL_FI void Identity();

    // Modifies this matrix to be a diagonal matrix
    TL_FI void MakeDiagonal(const T values[T_Size]);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by adding the incoming matrix
    TL_FI Matrix<T, T_Size>& Add(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by adding the incoming matrices and storing the
    // result in this matrix
    TL_FI void Add(const Matrix<T, T_Size>& aMatrix1,
                   const Matrix<T, T_Size>& aMatrix2);

    // Modifies this matrix by subtracting the incoming matrix
    TL_FI Matrix<T, T_Size>& Sub(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by subtracting the incoming matrices and storing
    // the result in this matrix
    TL_FI void Sub(const Matrix<T, T_Size>& aMatrix1,
                   const Matrix<T, T_Size>& aMatrix2);

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI Matrix<T, T_Size>& Mul(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix<T, T_Size>& aMatrix1,
                   const Matrix<T, T_Size>& aMatrix2);

    // Modifies this matrix by multiplying the incoming real number
    TL_FI Matrix<T, T_Size>& Mul(const T& aReal);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<T, T_Size>& aVectorIn,
                   Vector<T, T_Size>& aVectorOut);

    // Modifies this matrix by dividing the incoming real number
    TL_FI Matrix<T, T_Size>& Div(const T& aReal);

    // Modifies this matrix by transposing the matrix
    TL_FI Matrix<T, T_Size>& Transpose();

    // Modifies this matrix by transposing the incoming matrix and storing
    // the result in this matrix
    TL_FI void Transpose(const Matrix<T, T_Size>& aMatrix);

    //------------------------------------------------------------------------
    // Accessors

    // Stores the diagonal of this Matrix in aVector
    TL_FI void GetDiagonal(Vector<T, T_Size>& aVector);

    //------------------------------------------------------------------------
    // Operators

    TL_FI bool operator == (const Matrix<T, T_Size>& aMatrix);
    TL_FI bool operator != (const Matrix<T, T_Size>& aMatrix);

    //------------------------------------------------------------------------
    // Special Matrices

    static const Matrix<T, T_Size> ZERO;
    static const Matrix<T, T_Size> IDENTITY;

  private:

    static Matrix<T, T_Size> pInternal_GetIdentity();
  };

  //------------------------------------------------------------------------
  // Static const definitions
  template <typename T, u32 T_Size>
  const Matrix<T, T_Size> Matrix<T, T_Size>::ZERO = Matrix<T, T_Size>(0);
  template <typename T, u32 T_Size>
  const Matrix<T, T_Size> Matrix<T, T_Size>::IDENTITY = Matrix<T, T_Size>::pInternal_GetIdentity();

  template <typename T, u32 T_Size>
  Matrix<T, T_Size> Matrix<T, T_Size>::pInternal_GetIdentity()
  {
    Matrix<T, T_Size> temp;
    temp.Identity();
    return temp;
  }

};};

#endif