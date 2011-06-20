#pragma once
#ifndef TLOC_MATRIX_2_H
#define TLOC_MATRIX_2_H

#include "tlocCore/tlocBase.h"
#include "tlocMath/tlocVector.h"
#include "tlocMath/tlocMatrix.h"

namespace tloc
{
  template <typename T>
  class Matrix2 : public Matrix<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix2();
    TL_FI Matrix2(T m00, T m01, T m10, T m11);
    TL_FI Matrix2(const Matrix2<T>& aMatrix);

    TL_FI explicit Matrix2(const T& aValue);
    TL_FI Matrix2(const T values[MATRIX_SIZE], TABLE_ORDER aOrder);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix2<T>& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix2<T>& aMatrix1,
                   const Matrix2<T>& aMatrix2);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the 
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<T, 2>& aVectorIn,
                         Vector<T, 2>& aVectorOut);

    // Returns the determinant of this Matrix
    TL_I T Determinant() const;

    // Modifies this matrix by storing its inverse
    // If determinant is 0, then false is returned, otherwise, true.
    TL_I bool Inverse();

    // Modifies this matrix by storing the inverse of the incoming matrix.
    // If determinant is 0, the false is returned, otherwise, true.
    TL_I bool Inverse(const Matrix2<T>& aMatrix);

    // Modifies this matrix by storing its adjoint
    TL_I void Adjoint();

    // Modifies this matrix by storing the adjoint of the incoming matrix
    TL_I void Adjoint(const Matrix2<T>& aMatrix);

    // Normalizes the column vectors of the matrix
    TL_FI void Orthonormalize();

    // Normalizes the column vectors of the matrix. This uses FastInvSqrt() 
    // used in the Quake engine and may result in lost precision
    TL_FI void FastOrthonormalize();

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    TL_I void EigenDecomposition(Matrix2<T>& aRot, Matrix2<T>& aDiag) const;
  };

  typedef Matrix2<f32> Mat2f;
  typedef Matrix2<f64> Mat2d;

#include "tlocMatrix2.inl"
};

#endif