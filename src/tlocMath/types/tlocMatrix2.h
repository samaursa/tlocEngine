#pragma once
#ifndef TLOC_MATRIX_2_H
#define TLOC_MATRIX_2_H

#include <tlocCore/tlocBase.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocMatrix.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Matrix2 : public Matrix<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix2<T>                            this_type;
    typedef Matrix<T, 2>                          base_type;

    typedef typename base_type::matrix_order      matrix_order;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::MakeDiagonal;
    using base_type::m_values;
    using base_type::k_MatrixSize;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix2();

    // Copy constructor
    TL_FI Matrix2(const this_type& aMatrix);

    // Copy constructor
    TL_FI Matrix2(const base_type& aMatrix);

    // Generate a matrix by inputs in row-major order
    TL_FI Matrix2(value_type m00, value_type m01,
                  value_type m10, value_type m11);

    // Generate a diagonal matrix
    TL_FI Matrix2(value_type m00, value_type m11);

    // Fill the matrix with a certain value
    TL_FI explicit Matrix2(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    TL_FI Matrix2(const Vector2<value_type>& aVec1,
                  const Vector2<value_type>& aVec2,
                  typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    TL_FI Matrix2(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    TL_FI Matrix2(const core::Variadic<value_type, 4>& a_vars,
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
    TL_FI void Mul(const Vector2<value_type>& aVectorIn,
                         Vector2<value_type>& aVectorOut) const;

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
    TL_FI this_type& Orthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix
    TL_FI void Orthonormalize(const this_type& aMatrix);

    // Normalizes the column vectors of the matrix. This uses FastInvSqrt()
    // used in the Quake engine and may result in lost precision
    TL_FI this_type& FastOrthonormalize();

    // Modifies this matrix by storing the orthonormalized version of the
    // incoming matrix. This uses FastInvSqrt() used in the Quake engine
    // and may result in lost precision
    TL_FI void FastOrthonormalize(const this_type& aMatrix);

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    TL_I void EigenDecomposition(this_type& aRot, this_type& aDiag) const;
  };

  typedef Matrix2<f32>  Mat2f32;
  typedef Matrix2<f64>  Mat2f64;
  typedef Matrix2<f128> Mat2f128;

  typedef Matrix2<tl_float> Mat2f;

};};};

#endif