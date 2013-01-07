#pragma once
#ifndef TLOC_MATRIX_3_H
#define TLOC_MATRIX_3_H

#include <tlocCore/tlocBase.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Matrix3 : public Matrix<T, 3>
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix3<T>                            this_type;
    typedef Matrix<T, 3>                          base_type;

    typedef typename base_type::matrix_order      matrix_order;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::Set;
    using base_type::MakeDiagonal;
    using base_type::m_values;
    using base_type::k_MatrixSize;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix3();

    // Generate a matrix by inputs in row-major order
    TL_FI Matrix3(value_type m00, value_type m01, value_type m02,
                  value_type m10, value_type m11, value_type m12,
                  value_type m20, value_type m21, value_type m22);

    // Generate a diagonal matrix
    TL_FI Matrix3(value_type m00, value_type m11, value_type m22);

    // Copy constructor
    TL_FI Matrix3(const this_type& aMatrix);

    // Copy constructor
    TL_FI Matrix3(const base_type& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    TL_FI explicit Matrix3(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    TL_FI Matrix3(const Vector<value_type, 3>& aVec1,
                  const Vector<value_type, 3>& aVec2,
                  const Vector<value_type, 3>& aVec3,
                  typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    TL_FI Matrix3(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    TL_FI Matrix3(const core::Variadic<value_type, k_MatrixSize>& a_vars,
                  matrix_order a_order);


    //------------------------------------------------------------------------
    // Math operations

    // Modifies this matrix by multiplying the incoming matrix and storing
    // the result in this matrix
    TL_FI this_type& Mul(const this_type& aMatrix);

    // Modifies this matrix by multiplying the incoming matrices and storing
    // the result in this matrix
    TL_FI void Mul(const this_type& aMatrix1,
                   const this_type& aMatrix2);

    // Multiplies the incoming inVector with this matrix and stores it in
    // the outVector. Since we are assuming column major matrices, the
    // result is: vOut = M * vIn
    TL_FI void Mul(const Vector<value_type, 3>& aVectorIn,
                   Vector<value_type, 3>& aVectorOut) const;

    // Returns the determinant of this Matrix
    TL_I value_type Determinant() const;

    // Modifies this matrix by storing its inverse
    // If determinant is 0, then false is returned, otherwise, true.
    TL_I bool Inverse();

    // Modifies this matrix by storing the inverse of the incoming matrix.
    // If determinant is 0, the false is returned, otherwise, true.
    TL_I bool Inverse(const this_type& aMatrix);

    // Modifies this matrix by storing its adjoint
    TL_I this_type& Adjoint();

    // Modifies this matrix by storing the adjoint of the incoming matrix
    TL_I void Adjoint(const this_type& aMatrix);

    // Normalizes the column vectors of the matrix
    TL_I this_type& Orthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix
    TL_I void Orthonormalize(const this_type& aMatrix);

    // Normalizes the column vectors of the matrix. This uses FastInvSqrt()
    // used in the Quake engine and may result in lost precision
    TL_FI this_type& FastOrthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix. Uses FastInvSqrt() used in the Quake engine and
    // may result in lost precision
    TL_FI void FastOrthonormalize(const this_type& aMatrix);

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    void EigenDecomposition(this_type& aRot, this_type& aDiag) const;

    // Modifies this matrix to be a rotation matrix about the x-axis
    TL_I this_type& MakeRotationX(const_reference aXAngle);

    // Modifies this matrix to be a rotation matrix about the y-axis
    TL_I this_type& MakeRotationY(const_reference aYAngle);

    // Modifies this matrix to be a rotation matrix about the z-axis
    TL_I this_type& MakeRotationZ(const_reference aZAngle);

    // Modifies this vector by creating a rotation matrix from the incoming
    // angles by the order specified by the function. E.g. MakeEulerXYZ will
    // create a matrix that is:
    //
    // MatX * (MatY * MatZ)
    //
    // and if multiplied by a vector later, the breakdown will be:
    //
    // MatX * (MayY * (MatZ * V))
    TL_I void MakeEulerXYZ (value_type aXAngle, value_type aYAngle,
                            value_type aZAngle);
    TL_I void MakeEulerXZY (value_type aXAngle, value_type aZAngle,
                            value_type aYAngle);
    TL_I void MakeEulerYXZ (value_type aYAngle, value_type aXAngle,
                            value_type aZAngle);
    TL_I void MakeEulerYZX (value_type aYAngle, value_type aZAngle,
                            value_type aXAngle);
    TL_I void MakeEulerZXY (value_type aZAngle, value_type aXAngle,
                            value_type aYAngle);
    TL_I void MakeEulerZYX (value_type aZAngle, value_type aYAngle,
                            value_type aXAngle);
    TL_I void MakeEulerXYX (value_type aXAngle0, value_type aYAngle,
                            value_type aXAngle1);
    TL_I void MakeEulerXZX (value_type aXAngle0, value_type aZAngle,
                            value_type aXAngle1);
    TL_I void MakeEulerYXY (value_type aYAngle0, value_type aXAngle,
                            value_type aYAngle1);
    TL_I void MakeEulerYZY (value_type aYAngle0, value_type aZAngle,
                            value_type aYAngle1);
    TL_I void MakeEulerZXZ (value_type aZAngle0, value_type aXAngle,
                            value_type aZAngle1);
    TL_I void MakeEulerZYZ (value_type aZAngle0, value_type aYAngle,
                            value_type aZAngle1);

  private:

    // Taken from WildMagic5
    // Support for eigendecomposition.  The Tridiagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tridiagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    bool Tridiagonalize (value_type aDiagonal[3], value_type aSubdiagonal[2]);
    bool QLAlgorithm (value_type aDiagonal[3], value_type aSubdiagonal[2]);
  };

  typedef Matrix3<f32>  Mat3f32;
  typedef Matrix3<f64>  Mat3f64;
  typedef Matrix3<f128> Mat3f128;

  typedef Matrix3<tl_float> Mat3f;

};};};

#endif