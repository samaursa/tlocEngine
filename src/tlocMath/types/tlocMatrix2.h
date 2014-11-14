#pragma once
#ifndef TLOC_MATRIX_2_H
#define TLOC_MATRIX_2_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocMatrix.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Matrix_T<T, 2>
    : public Matrix_TI<T, 2, Matrix_T<T, 2> >
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix_T<T, 2>                        this_type;
    typedef Matrix_TI<T, 2, this_type>            base_type;

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
    Matrix_T();

    // Copy constructor
    Matrix_T(const this_type& aMatrix);

    // Copy constructor
    Matrix_T(const base_type& aMatrix);

    // Generate a matrix by inputs in row-major order
    Matrix_T(value_type m00, value_type m01,
             value_type m10, value_type m11);

    // Generate a diagonal matrix
    Matrix_T(value_type m00, value_type m11);

    // Fill the matrix with a certain value
    explicit Matrix_T(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    Matrix_T(const Vector_T<value_type, 2>& aVec1,
             const Vector_T<value_type, 2>& aVec2,
             typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    Matrix_T(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix_T(const core::data_structs::Variadic<value_type, 4>& a_vars,
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

  // -----------------------------------------------------------------------
  // typedefs

  typedef Matrix_T<f32, 2>      Mat2f32;
  typedef Matrix_T<f64, 2>      Mat2f64;
  typedef Matrix_T<f128, 2>     Mat2f128;
  typedef Matrix_T<tl_float, 2> Mat2f;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_T<f32 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_T<f64 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_T<f128 TLOC_COMMA 2>);

  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f32 TLOC_COMMA 2 TLOC_COMMA  Mat2f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f64 TLOC_COMMA 2 TLOC_COMMA  Mat2f64>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f128 TLOC_COMMA 2 TLOC_COMMA  Mat2f128>);

};};};

#endif