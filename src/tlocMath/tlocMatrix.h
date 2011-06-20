#pragma once
#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTable.h"
#include "tlocMath/tlocVector.h"

namespace tloc
{
  template <typename T, u32 T_Size>
  class Matrix : public Table<T, T_Size, T_Size>
  {
  protected:
    enum { MATRIX_SIZE = TABLE_SIZE };

  public:
    //------------------------------------------------------------------------
    // Constructors

    typedef TABLE_ORDER MATRIX_ORDER;

    // Empty default constructor
    TL_FI Matrix();
    TL_FI Matrix(const Matrix<T, T_Size>& aMatrix);

    TL_FI explicit Matrix(const T& aValue);
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
    TL_FI void Add(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by adding the incoming matrices and storing the
    // result in this matrix
    TL_FI void Add(const Matrix<T, T_Size>& aMatrix1,
                   const Matrix<T, T_Size>& aMatrix2);

    // Modifies this matrix by subtracting the incoming matrix
    TL_FI void Sub(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by subtracting the incoming matrices and storing
    // the result in this matrix
    TL_FI void Sub(const Matrix<T, T_Size>& aMatrix1,
                   const Matrix<T, T_Size>& aMatrix2);

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix<T, T_Size>& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix<T, T_Size>& aMatrix1,
                   const Matrix<T, T_Size>& aMatrix2);

    // Modifies this matrix by multiplying the incoming real number
    TL_FI void Mul(const T& aReal);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the 
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<T, T_Size>& aVectorIn,
                   Vector<T, T_Size>& aVectorOut);

    // Modifies this matrix by dividing the incoming real number
    TL_FI void Div(const T& aReal);

    // Modifies this matrix by transposing the matrix
    TL_FI void Transpose();

    // Modifies this matrix by transposing the incoming matrix and storing
    // the result in this matrix
    TL_FI void Transpose(const Matrix<T, T_Size>& aMatrix);

    //------------------------------------------------------------------------
    // Accessors

    // Stores the diagonal of this Matrix in aVector
    TL_FI void GetDiagonal(Vector<T, T_Size>& aVector);

    //------------------------------------------------------------------------
    // Special Matrices

    static const Matrix<T, T_Size> ZERO;
    static const Matrix<T, T_Size> IDENTITY;
  };
};

#ifdef TLOC_FULL_SOURCE
  #include "tlocMatrix.inl"
#endif

#endif