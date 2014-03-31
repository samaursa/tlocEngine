#pragma once
#ifndef TLOC_MATRIX_3_H
#define TLOC_MATRIX_3_H

#include <tlocMath/tlocMathBase.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix.h>

#include <tlocMath/types/tlocAngle.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Matrix3 : public Matrix<T, 3>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix3<T>                            this_type;
    typedef Matrix<T, 3>                          base_type;

    typedef typename base_type::matrix_order      matrix_order;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;
    typedef typename base_type::vec_type          vec_type;

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
    Matrix3();

    // Generate a matrix by inputs in row-major order
    Matrix3(value_type m00, value_type m01, value_type m02,
            value_type m10, value_type m11, value_type m12,
            value_type m20, value_type m21, value_type m22);

    // Generate a diagonal matrix
    Matrix3(value_type m00, value_type m11, value_type m22);

    // Copy constructor
    Matrix3(const this_type& aMatrix);

    // Copy constructor
    Matrix3(const base_type& aMatrix);

    // Modifies this matrix by filling it with the incoming value
    explicit Matrix3(const_reference aValue);

    // Fill the matrix with vectors depending on the selected order
    Matrix3(const Vector<value_type, 3>& aVec1,
            const Vector<value_type, 3>& aVec2,
            const Vector<value_type, 3>& aVec3,
            typename base_type::matrix_order aOrder);

    // Fill the matrix with values in a certain matrix order
    Matrix3(const value_type (&values)[k_MatrixSize], matrix_order aOrder);

    Matrix3(const core::data_structs::
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

    void        MakeRotationX(const_reference aXAngle);
    void        MakeRotationY(const_reference aYAngle);
    void        MakeRotationZ(const_reference aZAngle);

    void        MakeRotation(const vec_type& a_axis,
                             Radian_T<value_type> a_angle);

    // Modifies this vector by creating a rotation matrix from the incoming
    // angles by the order specified by the function. E.g. MakeEulerXYZ will
    // create a matrix that is:
    //
    // MatX * (MatY * MatZ)
    //
    // and if multiplied by a vector later, the breakdown will be:
    //
    // MatX * (MayY * (MatZ * V))
    void MakeEulerXYZ (value_type aXAngle, value_type aYAngle,
                       value_type aZAngle);
    void MakeEulerXZY (value_type aXAngle, value_type aZAngle,
                       value_type aYAngle);
    void MakeEulerYXZ (value_type aYAngle, value_type aXAngle,
                       value_type aZAngle);
    void MakeEulerYZX (value_type aYAngle, value_type aZAngle,
                       value_type aXAngle);
    void MakeEulerZXY (value_type aZAngle, value_type aXAngle,
                       value_type aYAngle);
    void MakeEulerZYX (value_type aZAngle, value_type aYAngle,
                       value_type aXAngle);
    void MakeEulerXYX (value_type aXAngle0, value_type aYAngle,
                       value_type aXAngle1);
    void MakeEulerXZX (value_type aXAngle0, value_type aZAngle,
                       value_type aXAngle1);
    void MakeEulerYXY (value_type aYAngle0, value_type aXAngle,
                       value_type aYAngle1);
    void MakeEulerYZY (value_type aYAngle0, value_type aZAngle,
                       value_type aYAngle1);
    void MakeEulerZXZ (value_type aZAngle0, value_type aXAngle,
                       value_type aZAngle1);
    void MakeEulerZYZ (value_type aZAngle0, value_type aYAngle,
                       value_type aZAngle1);

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

  typedef Matrix3<f32>  Mat3f32;
  typedef Matrix3<f64>  Mat3f64;
  typedef Matrix3<f128> Mat3f128;

  typedef Matrix3<tl_float> Mat3f;

};};};

#endif