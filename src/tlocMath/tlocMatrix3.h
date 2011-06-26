#pragma once
#ifndef TLOC_MATRIX_3_H
#define TLOC_MATRIX_3_H

#include "tlocCore/tlocBase.h"
#include "tlocMath/tlocVector.h"
#include "tlocMath/tlocMatrix.h"

namespace tloc
{
  template <typename T>
  class Matrix3 : public Matrix<T, 3>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix3();

    // Generate a matrix by inputs in row-major order
    TL_FI Matrix3(T m00, T m01, T m02, 
                  T m10, T m11, T m12, 
                  T m20, T m21, T m22);

    // Generate a diagonal matrix
    TL_FI Matrix3(T m00, T m11, T m22);

    // Copy constructor
    TL_FI Matrix3(const Matrix3<T>& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    TL_FI explicit Matrix3(const T& aValue);

    // Fill the matrix with vectors depending on the selected order
    TL_FI Matrix3(const Vector<T, 3>& aVec1, const Vector<T, 3>& aVec2,
                  const Vector<T, 3>& aVec3, TABLE_ORDER aOrder);

    // Fill the matrix with values in a certain matrix order
    TL_FI Matrix3(const T values[MATRIX_SIZE], TABLE_ORDER aOrder);

    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI Matrix3& Mul(const Matrix3<T>& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const Matrix3<T>& aMatrix1,
                   const Matrix3<T>& aMatrix2);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the 
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<T, 3>& aVectorIn,
                   Vector<T, 3>& aVectorOut);

    // Returns the determinant of this Matrix
    TL_I T Determinant() const;

    // Modifies this matrix by storing its inverse
    // If determinant is 0, then false is returned, otherwise, true.
    TL_I bool Inverse();

    // Modifies this matrix by storing the inverse of the incoming matrix.
    // If determinant is 0, the false is returned, otherwise, true.
    TL_I bool Inverse(const Matrix3<T>& aMatrix);

    // Modifies this matrix by storing its adjoint
    TL_I Matrix3& Adjoint();

    // Modifies this matrix by storing the adjoint of the incoming matrix
    TL_I void Adjoint(const Matrix3<T>& aMatrix);

    // Normalizes the column vectors of the matrix
    TL_FI Matrix3& Orthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix
    TL_FI void Orthonormalize(const Matrix3<T>& aMatrix);

    // Normalizes the column vectors of the matrix. This uses FastInvSqrt() 
    // used in the Quake engine and may result in lost precision
    TL_FI Matrix3& FastOrthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix. Uses FastInvSqrt() used in the Quake engine and 
    // may result in lost precision
    TL_FI void FastOrthonormalize(const Matrix3<T>& aMatrix);

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    void EigenDecomposition(Matrix3<T>& aRot, Matrix3<T>& aDiag) const;

  private:

    // Taken from WildMagic5
    // Support for eigendecomposition.  The Tridiagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tridiagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    bool Tridiagonalize (T aDiagonal[3], T aSubdiagonal[2]);
    bool QLAlgorithm (T aDiagonal[3], T aSubdiagonal[2]);

    // Euler angles helper. This function should not be used directly
    // as the order of rotation is ambiguous
    TL_FI void MakeEuler(T aAngle1, T aAngle2, T aAngle3);
  };

  typedef Matrix3<f32>  Mat3f;
  typedef Matrix3<f64>  Mat3d;
  typedef Matrix3<f128> Mat3l;
};

#ifdef TLOC_FULL_SOURCE
#include "tlocMatrix3.inl"
#endif

#endif