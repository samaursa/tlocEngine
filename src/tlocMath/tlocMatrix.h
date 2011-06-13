#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTable.h"
#include "tlocMath/tlocVector.h"

namespace tloc
{
  template <typename T, u32 T_SIZE>
  class Matrix : public Table<T, T_SIZE, T_SIZE>
  {
  protected:
    enum { MATRIX_SIZE = TABLE_SIZE };

  public:
    //------------------------------------------------------------------------
    // Constructors

    typedef TABLE_ORDER MATRIX_ORDER;

    // Empty default constructor
    TL_FI Matrix();
    TL_FI Matrix(const Matrix<T, T_SIZE>& aMatrix);

    TL_FI explicit Matrix(const T& aValue);
    TL_FI Matrix(const T values[MATRIX_SIZE], MATRIX_ORDER aOrder);

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

    // Modifies this matrix by dividing the incoming real number
    TL_FI void Div(const T& aReal);

    // Modifies this matrix by transposing the matrix
    TL_FI void Transpose();

    // Modifies this matrix by transposing the incoming matrix and storing
    // the result in this matrix
    TL_FI void Transpose(const Matrix<T, T_SIZE>& aMatrix);

    //------------------------------------------------------------------------
    // Accessors

    // Stores the diagonal of this Matrix in aVector
    TL_FI void GetDiagonal(Vector<T, T_SIZE>& aVector);
  };

  typedef Matrix<float, 2> Mat2f;
  typedef Matrix<float, 3> Mat3f;
  typedef Matrix<float, 4> Mat4f;

  typedef Matrix<double, 2> Mat2d;
  typedef Matrix<double, 3> Mat3d;
  typedef Matrix<double, 4> Mat4d;

  template <typename T>
  class Matrix2 : public Matrix<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix2();
    TL_FI Matrix2(const Matrix2<T>& aMatrix);

    TL_FI explicit Matrix2(const T& aValue);
    TL_FI Matrix2(const T values[MATRIX_SIZE], TABLE_ORDER aOrder);

  };

#include "tlocMatrix.inl"
};

#endif