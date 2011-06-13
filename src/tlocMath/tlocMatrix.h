#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTable.h"
#include "tlocMath/tlocVector.h"

namespace tloc
{
  template <typename T, typename T_SIZE>
  class Matrix : public Table<T, T_SIZE, T_SIZE>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix();
    TL_FI Matrix(const Matrix<T, T_SIZE>& aMatrix);

    TL_FI explicit Matrix(const T& aValue);
    TL_FI Matrix(const T values[TABLE_SIZE], TABLE_ORDER aOrder);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by adding the incoming matrix
    TL_FI void Add(const Matrix<T, T_SIZE>& aMatrix);

    // Modifies this matrix by adding the incoming matrices and storing the
    // result in this matrix
    TL_FI void Add(const Matrix<T, T_SIZE>& aMatrix1,
                   const Matrix<T, T_SIZE>& aMatrix2);

    // Modifies this matrix by subtracting the incoming matrix
    TL_FI void Sub(const Matrix<T, T_SIZE>& aMatrix);

    // Modifies this matrix by subtracting the incoming matrices and storing
    // the result in this matrix
    TL_FI void Sub(const Matrix<T, T_SIZE>& aMatrix1,
                   const Matrix<T, T_SIZE>& aMatrix2);

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix<T, T_SIZE>& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix<T, T_SIZE>& aMatrix1,
                   const Matrix<T, T_SIZE>& aMatrix2);

    // Modifies this matrix by multiplying the incoming real number
    TL_FI void Mul(const T& aReal);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the 
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<T, T_SIZE>& aVectorIn,
                   const Vector<T, T_SIZE>& aVectorOut);


    
  };
};

#endif