#pragma once
#ifndef TLOC_MATH_MATRIX_4_H
#define TLOC_MATH_MATRIX_4_H

#include <tlocMath/tlocMathBase.h>

#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix.h>

namespace tloc { namespace math { namespace types {

  namespace p_matrix4
  {
    struct NonAffine{};
    // i.e. the matrix is an actual transformation matrix
    struct Affine{};
  };

  // Matrix indices (columns are vertical)
  //
  // 0   4   8    12
  // 1   5   9    13
  // 2   6   10   14
  // 3   7   11   15

  template <typename T>
  class Matrix_T<T, 4>
    : public Matrix_TI<T, 4>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix_T<T, 4>                          this_type;
    typedef Matrix_TI<T, 4>                         base_type;

    typedef typename base_type::matrix_order        matrix_order;

    typedef typename base_type::value_type          value_type;
    typedef typename base_type::reference           reference;
    typedef typename base_type::const_reference     const_reference;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::Set;
    using base_type::MakeDiagonal;
    using base_type::m_values;
    using base_type::k_MatrixSize;

    using base_type::operator*;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    Matrix_T();

    // Generate a matrix by inputs in row-major order
    Matrix_T(value_type m00, value_type m01, value_type m02, value_type m03,
             value_type m10, value_type m11, value_type m12, value_type m13,
             value_type m20, value_type m21, value_type m22, value_type m23,
             value_type m30, value_type m31, value_type m32, value_type m33);

    // Generate a diagonal matrix
    Matrix_T(value_type m00, value_type m11, value_type m22, value_type m33);

    // Copy constructor
    Matrix_T(const this_type& aMatrix);

    // Copy constructor
    Matrix_T(const base_type& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    explicit Matrix_T(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    Matrix_T(const Vector_T<value_type, 4>& aVec1,
             const Vector_T<value_type, 4>& aVec2,
             const Vector_T<value_type, 4>& aVec3,
             const Vector_T<value_type, 4>& aVec4,
             typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    Matrix_T(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix_T(const core::data_structs::
             Variadic<value_type, k_MatrixSize>& a_vars,
             matrix_order a_order);

    this_type Adjoint() const;

    // Non-affine inverse assumed. Slower than affine inverse.
    this_type Invert() const;

    // Affine: faster, but incorrect results for non-affine matrices
    template <typename T_InverseType>
    this_type Invert() const;

    value_type Determinant() const;

  private:
    this_type DoInvert(p_matrix4::NonAffine) const;
    this_type DoInvert(p_matrix4::Affine) const;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T>
  template <typename T_InverseType>
  typename Matrix_T<T, 4>::this_type
    Matrix_T<T, 4>::Invert() const
  {
    type_traits::AssertTypeIsSupported
      <T_InverseType, p_matrix4::Affine, p_matrix4::NonAffine>();

    return DoInvert(T_InverseType());
  }

  // -----------------------------------------------------------------------
  // typedefs

  typedef Matrix_T<f32, 4>  Mat4f32;
  typedef Matrix_T<f64, 4>  Mat4f64;
  typedef Matrix_T<f128, 4> Mat4f128;

  typedef Matrix_T<tl_float, 4> Mat4f;

};};};

#endif