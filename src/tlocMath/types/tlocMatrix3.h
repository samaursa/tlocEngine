#pragma once
#ifndef TLOC_MATRIX_3_H
#define TLOC_MATRIX_3_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix.h>

#include <tlocMath/types/tlocAngle.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Matrix_T<T, 3>
    : public Matrix_TI<T, 3, Matrix_T<T, 3> >
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix_T<T, 3>                            this_type;
    typedef Matrix_TI<T, 3, this_type>                base_type;

    typedef typename base_type::matrix_order          matrix_order;

    typedef typename base_type::value_type            value_type;
    typedef typename base_type::reference             reference;
    typedef typename base_type::const_reference       const_reference;
    typedef typename base_type::vec_type              vec_type;
    typedef Radian_T<value_type>                      angle_type;

    typedef core_t::StrongType_T<vec_type, 0>         up;
    typedef core_t::StrongType_T<vec_type, 1>         dir;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::Set;
    using base_type::MakeDiagonal;
    using base_type::Mul;
    using base_type::m_values;
    using base_type::k_MatrixSize;

    using base_type::operator*;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    Matrix_T();

    // Generate a matrix by inputs in row-major order
    Matrix_T(value_type m00, value_type m01, value_type m02,
            value_type m10, value_type m11, value_type m12,
            value_type m20, value_type m21, value_type m22);

    // Generate a diagonal matrix
    Matrix_T(value_type m00, value_type m11, value_type m22);

    // Copy constructor
    Matrix_T(const this_type& aMatrix);

    // Copy constructor
    Matrix_T(const base_type& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    explicit Matrix_T(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    Matrix_T(const Vector_T<value_type, 3>& aVec1,
             const Vector_T<value_type, 3>& aVec2,
             const Vector_T<value_type, 3>& aVec3,
             typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    Matrix_T(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix_T(const core::data_structs::
             Variadic <value_type, k_MatrixSize>& a_vars,
             matrix_order a_order);

    //------------------------------------------------------------------------
    // Math operations

    // Returns the determinant of this Matrix
    value_type  Determinant() const;

    this_type   Inverse() const;
    void        Inverse(const this_type& aMatrix);

    this_type   Adjoint() const;
    void        Adjoint(const this_type& aMatrix);

    this_type   Orthonormalize() const;
    void        Orthonormalize(const this_type& aMatrix);

    // Normalizes the column vectors of the matrix. This uses FastInvSqrt()
    // used in the Quake engine and may result in lost precision
    this_type   FastOrthonormalize() const;
    void        FastOrthonormalize(const this_type& aMatrix);

    // Taken from WildMagic5
    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0
    // and d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    void        EigenDecomposition(this_type& aRot, this_type& aDiag) const;

    void        MakeRotationX(angle_type a_angle);
    void        MakeRotationY(angle_type a_angle);
    void        MakeRotationZ(angle_type a_angle);

    void        MakeRotation(const vec_type& a_axis, angle_type a_angle);

    // Modifies this vector by creating a rotation matrix from the incoming
    // angles by the order specified by the function. E.g. MakeEulerXYZ will
    // create a matrix that is:
    //
    // MatX * (MatY * MatZ)
    //
    // and if multiplied by a vector later, the breakdown will be:
    //
    // MatX * (MayY * (MatZ * V))
    void MakeEulerXYZ (angle_type aXAngle, angle_type aYAngle,
                       angle_type aZAngle);
    void MakeEulerXZY (angle_type aXAngle, angle_type aZAngle,
                       angle_type aYAngle);
    void MakeEulerYXZ (angle_type aYAngle, angle_type aXAngle,
                       angle_type aZAngle);
    void MakeEulerYZX (angle_type aYAngle, angle_type aZAngle,
                       angle_type aXAngle);
    void MakeEulerZXY (angle_type aZAngle, angle_type aXAngle,
                       angle_type aYAngle);
    void MakeEulerZYX (angle_type aZAngle, angle_type aYAngle,
                       angle_type aXAngle);
    void MakeEulerXYX (angle_type aXAngle0, angle_type aYAngle,
                       angle_type aXAngle1);
    void MakeEulerXZX (angle_type aXAngle0, angle_type aZAngle,
                       angle_type aXAngle1);
    void MakeEulerYXY (angle_type aYAngle0, angle_type aXAngle,
                       angle_type aYAngle1);
    void MakeEulerYZY (angle_type aYAngle0, angle_type aZAngle,
                       angle_type aYAngle1);
    void MakeEulerZXZ (angle_type aZAngle0, angle_type aXAngle,
                       angle_type aZAngle1);
    void MakeEulerZYZ (angle_type aZAngle0, angle_type aYAngle,
                       angle_type aZAngle1);

    void Orient(dir a_direction);
    void Orient(dir a_direction, up a_up);

  private:

    // Taken from WildMagic5
    // Support for eigendecomposition.  The Tridiagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tridiagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    bool DoTridiagonalize (value_type aDiagonal[3], value_type aSubdiagonal[2]);
    bool DoQLAlgorithm (value_type aDiagonal[3], value_type aSubdiagonal[2]);
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Matrix_T<f32, 3>  Mat3f32;
  typedef Matrix_T<f64, 3>  Mat3f64;

  typedef Matrix_T<tl_float, 3> Mat3f;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_T<f32 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_T<f64 TLOC_COMMA 3>);

  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f32 TLOC_COMMA 3 TLOC_COMMA  Mat3f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f64 TLOC_COMMA 3 TLOC_COMMA  Mat3f64>);

};};};

#endif