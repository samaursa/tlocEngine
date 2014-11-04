#pragma once
#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocStaticAssert.h>
#include <tlocCore/data_structures/tlocTable.h>
#include <tlocMath/types/tlocVector.h>

//////////////////////////////////////////////////////////////////////////
/* NOTES
 *
 * Matrices are arranged in column-major order in memory as well as matrix
 * layout. This means that each column of the matrix is a vector and
 * consequently the matrix/vector multiplication is performed by:
 *
 * M * v
 *
 * where `v` is a column vector. The matrix is arranged in memory in a
 * column-major layout, i.e. a 3x3 matrix will be layed out in memory such
 * that mat3x3[0], [1] and [2] indices correspond to the first column
 * vector. Similarly, [3], [4] and [5] indices correspond to the second
 * column vector and so on.
 */

namespace tloc { namespace math { namespace types {

  template <typename T, tl_size T_Size, typename T_Derived = DummyStruct>
  class Matrix_TI
    : public core::data_structs::Table<T, T_Size, T_Size>
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Matrix_TI<T, T_Size, T_Derived>               this_type;
    typedef core::data_structs::Table<T, T_Size, T_Size>  base_type;

    // select this_type as the derived_type if no derived type was passed
    typedef typename Loki::Select
      <Loki::IsSameType<T_Derived, DummyStruct>::value, 
       this_type, T_Derived>::Result                      derived_type;

    typedef typename base_type::table_order               table_order;
    typedef table_order                                   matrix_order;

    typedef typename base_type::value_type                value_type;
    typedef typename base_type::value_type&               reference;
    typedef typename base_type::value_type const&         const_reference;

    typedef Vector_T<value_type, T_Size>                  vec_type;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::GetRow;
    using base_type::Set;
    using base_type::k_size;
    using base_type::m_values;

  protected:

    enum { k_MatrixSize = k_size };

  public:
    //------------------------------------------------------------------------
    // Constructors

    Matrix_TI();
    explicit Matrix_TI(value_type aValue);

    Matrix_TI(const value_type (&values)[k_MatrixSize], matrix_order aOrder);
    Matrix_TI(const core::data_structs::Variadic<T, k_MatrixSize>& a_vars,
           matrix_order a_order);

    template <typename T_Real>
    Matrix_TI(const core_ds::Table<T_Real, T_Size, T_Size>& a_matrix);

  public:
    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this matrix by setting all values to 0
    void MakeZero();

    // Modifes this matrix by making it an identity matrix
    void MakeIdentity();

    // Modifies this matrix to be a diagonal matrix
    void MakeDiagonal(const value_type values[T_Size]);
    void MakeDiagonal(const Vector_T<value_type, T_Size>& a_diagonal);

    //------------------------------------------------------------------------
    // Math operations

    derived_type  Add(const this_type& aMatrix) const;
    void          Add(const this_type& aMatrix1, const this_type& aMatrix2);

    derived_type  Sub(const this_type& aMatrix) const;
    void          Sub(const this_type& aMatrix1, const this_type& aMatrix2);

    derived_type  Mul(const this_type& aMatrix) const;
    void          Mul(const this_type& aMatrix1, const this_type& aMatrix2);
    derived_type  Mul(const_reference aReal) const;
    void          Mul(const vec_type& aVectorIn, vec_type& aVectorOut) const;
    vec_type      Mul(const vec_type& a_vecIn) const;

    derived_type  Div(const_reference aReal) const;

    derived_type  Transpose() const;
    void          Transpose(const this_type& aMatrix);

    //------------------------------------------------------------------------
    // Accessors

    void      GetDiagonal(vec_type& aVector);

    //------------------------------------------------------------------------
    // Operators

    derived_type  operator+ (const this_type& a_matrix) const;
    derived_type  operator- (const this_type& a_matrix) const;
    derived_type  operator* (const this_type& a_matrix) const;
    derived_type  operator* (const_reference a_value) const;
    derived_type  operator/ (const_reference a_value) const;

    Vector_T<value_type, T_Size>
      operator* (const Vector_T<value_type, T_Size>& a_vector) const;

    derived_type& operator+= (const this_type& a_matrix);
    derived_type& operator-= (const this_type& a_matrix);
    derived_type& operator*= (const this_type& a_matrix);
    derived_type& operator*= (const_reference a_value);
    derived_type& operator/= (const_reference a_value);

    //this_type& operator=(const this_type& a_other);
    bool operator== (const this_type& aMatrix);
    bool operator!= (const this_type& aMatrix);

    //------------------------------------------------------------------------
    // Special Matrices

    static const derived_type ZERO;
    static const derived_type IDENTITY;

  private:

    static derived_type DoGetIdentity();
  };

  //------------------------------------------------------------------------
  // Static const definitions

  template <typename T, tl_size T_Size, typename T_DerivedType>
  const typename Matrix_TI<T, T_Size, T_DerivedType>::derived_type
    Matrix_TI<T, T_Size, T_DerivedType>::ZERO =
    typename Matrix_TI<T, T_Size, T_DerivedType>::derived_type(0);

  template <typename T, tl_size T_Size, typename T_DerivedType>
  const typename Matrix_TI<T, T_Size, T_DerivedType>::derived_type 
    Matrix_TI<T, T_Size, T_DerivedType>::IDENTITY =
    Matrix_TI<T, T_Size, T_DerivedType>::derived_type::DoGetIdentity();

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T, tl_size T_Size, typename T_DerivedType>
  template <typename T_Real>
  Matrix_TI<T, T_Size, T_DerivedType>::
    Matrix_TI(const core_ds::Table<T_Real, T_Size, T_Size>& a_matrix)
    : base_type(a_matrix)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size, typename T_DerivedType>
  typename Matrix_TI<T, T_Size, T_DerivedType>::derived_type
    Matrix_TI<T, T_Size, T_DerivedType>::
    DoGetIdentity()
  {
    derived_type temp;
    temp.MakeIdentity();
    return temp;
  }

  //------------------------------------------------------------------------
  // Global operators

  template <typename T, tl_size T_Size, typename T_DT>
  typename Matrix_TI<T, T_Size, T_DT>::derived_type
    operator* (T a_lhs, const Matrix_TI<T, T_Size, T_DT>& a_rhs)
  {
    return a_rhs.operator*(a_lhs);
  }

  template <typename T, tl_size T_Size, typename T_DT>
  typename Matrix_TI<T, T_Size, T_DT>::derived_type
    operator/ (T a_lhs, const Matrix_TI<T, T_Size, T_DT>& a_rhs)
  {
    return a_rhs.operator/(a_lhs);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Matrix_T<> base case

  template <typename T, tl_size T_Size>
  class Matrix_T;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f32 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f32 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f32 TLOC_COMMA 4>);

  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f64 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f64 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Matrix_TI<f64 TLOC_COMMA 4>);

};};};

#endif