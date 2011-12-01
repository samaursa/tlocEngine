#pragma once
#ifndef TLOC_MATRIX_2_H
#define TLOC_MATRIX_2_H

#include "tlocCore/tlocBase.h"
#include "tlocMath/tlocVector2.h"
#include "tlocMath/tlocMatrix.h"

namespace tloc { namespace math {

  template <typename T>
  class Matrix2 : public Matrix<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix2();

    // Generate a matrix by inputs in row-major order
    TL_FI Matrix2(T m00, T m01,
                  T m10, T m11);

    // Generate a diagonal matrix
    TL_FI Matrix2(T m00, T m11);

    // Copy constructor
    TL_FI Matrix2(const Matrix2<T>& aMatrix);

    // Fill the matrix with a certain value
    TL_FI explicit Matrix2(const T& aValue);

    // Fill the matrix with vectors depending on the selected order
    TL_FI Matrix2(const Vector2<T>& aVec1, const Vector2<T>& aVec2,
                  TABLE_ORDER aOrder);

    // Fill the matrix with values in a certain matrix order
    TL_FI Matrix2(const T values[MATRIX_SIZE], TABLE_ORDER aOrder);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI Matrix2<T>& Mul(const Matrix2<T>& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix2<T>& aMatrix1,
                   const Matrix2<T>& aMatrix2);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector2<T>& aVectorIn,
                         Vector2<T>& aVectorOut);

    // Returns the determinant of this Matrix
    TL_I T Determinant() const;

    // Modifies this matrix by storing its inverse
    // If determinant is 0, then false is returned, otherwise, true.
    TL_I bool Inverse();

    // Modifies this matrix by storing the inverse of the incoming matrix.
    // If determinant is 0, the false is returned, otherwise, true.
    TL_I bool Inverse(const Matrix2<T>& aMatrix);

    // Modifies this matrix by storing its adjoint
    TL_I Matrix2<T>& Adjoint();

    // Modifies this matrix by storing the adjoint of the incoming matrix
    TL_I void Adjoint(const Matrix2<T>& aMatrix);

    // Normalizes the column vectors of the matrix
    TL_FI Matrix2<T>& Orthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix
    TL_FI void Orthonormalize(const Matrix2<T>& aMatrix);

    // Normalizes the column vectors of the matrix. This uses FastInvSqrt()
    // used in the Quake engine and may result in lost precision
    TL_FI Matrix2<T>& FastOrthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix. This uses FastInvSqrt() used in the Quake engine
    // and may result in lost precision
    TL_FI void FastOrthonormalize(const Matrix2<T>& aMatrix);

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    TL_I void EigenDecomposition(Matrix2<T>& aRot, Matrix2<T>& aDiag) const;
  };

  typedef Matrix2<f32>  Mat2f;
  typedef Matrix2<f64>  Mat2d;
  typedef Matrix2<f128> Mat2l;

};};

#endif