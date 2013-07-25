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
  class Matrix4 : public Matrix<T, 4>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix4<T>                            this_type;
    typedef Matrix<T, 4>                          base_type;

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

    using base_type::operator*;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    Matrix4();

    // Generate a matrix by inputs in row-major order
    Matrix4(value_type m00, value_type m01, value_type m02, value_type m03,
            value_type m10, value_type m11, value_type m12, value_type m13,
            value_type m20, value_type m21, value_type m22, value_type m23,
            value_type m30, value_type m31, value_type m32, value_type m33);

    // Generate a diagonal matrix
    Matrix4(value_type m00, value_type m11, value_type m22, value_type m33);

    // Copy constructor
    Matrix4(const this_type& aMatrix);

    // Copy constructor
    Matrix4(const base_type& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    explicit Matrix4(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    Matrix4(const Vector<value_type, 4>& aVec1,
            const Vector<value_type, 4>& aVec2,
            const Vector<value_type, 4>& aVec3,
            const Vector<value_type, 4>& aVec4,
            typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    Matrix4(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix4(const core::data_structs::
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

  typedef Matrix4<f32>  Mat4f32;
  typedef Matrix4<f64>  Mat4f64;
  typedef Matrix4<f128> Mat4f128;

  typedef Matrix4<tl_float> Mat4f;

};};};

#endif