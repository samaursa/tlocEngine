#pragma once
#ifndef TLOC_MATRIX_2_H
#define TLOC_MATRIX_2_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocMatrix.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Matrix2 : public Matrix<T, 2>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

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

    using base_type::operator*;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    Matrix2();

    // Copy constructor
    Matrix2(const this_type& aMatrix);

    // Copy constructor
    Matrix2(const base_type& aMatrix);

    // Generate a matrix by inputs in row-major order
    Matrix2(value_type m00, value_type m01,
            value_type m10, value_type m11);

    // Generate a diagonal matrix
    Matrix2(value_type m00, value_type m11);

    // Fill the matrix with a certain value
    explicit Matrix2(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    Matrix2(const Vector_T<value_type, 2>& aVec1,
            const Vector_T<value_type, 2>& aVec2,
            typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    Matrix2(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix2(const core::data_structs::Variadic<value_type, 4>& a_vars,
            matrix_order a_order);

    //------------------------------------------------------------------------
    // Math operations

    value_type  Determinant() const;

    this_type   Inverse() const;
    void        Inverse(const this_type& a_matrix);

    this_type   Adjoint() const;
    void        Adjoint(const this_type& a_matrix);

    this_type   Orthonormalize() const;
    void        Orthonormalize(const this_type& a_matrix);
    this_type   FastOrthonormalize() const;
    void        FastOrthonormalize(const this_type& a_matrix);

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    void EigenDecomposition(this_type& aRot, this_type& aDiag) const;
  };

  typedef Matrix2<f32>  Mat2f32;
  typedef Matrix2<f64>  Mat2f64;
  typedef Matrix2<f128> Mat2f128;

  typedef Matrix2<tl_float> Mat2f;

};};};

#endif