#ifndef TLOC_TABLE_H
#define TLOC_TABLE_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <memory.h>

namespace tloc { namespace core { namespace data_structs {

  // Column major ordering (because OpenGL uses it. Switching back and forth
  // is not a problem as long as we are consistent)
  //
  // PERFORMANCE NOTES: In the column major order, some table operations
  // may be faster. These include Setting the columns via a Tuple<> and
  // getting a column via a Tuple<>. Vice-versa is true for row major order
  // (not yet supported).
  template <typename T, tl_size T_Rows, tl_size T_Cols>
  class Table
  {
  public:
    enum { k_Rows = T_Rows, k_Cols = T_Cols };
    enum { k_size = k_Rows * k_Cols };

  public:
    //------------------------------------------------------------------------
    // Constructors

    // Currently only useful for constructor/function accepting an array
    // of values
    typedef enum table_order { k_RowMajor, k_ColMajor } table_order;

    typedef T                                           value_type;
    typedef T&                                          reference;
    typedef T*                                          pointer;
    typedef const T&                                    const_reference;
    typedef const T*                                    const_pointer;

    typedef tl_size                                     size_type;
    typedef Table<value_type, k_Rows, k_Cols>           this_type;
    typedef Tuple<value_type, k_Rows>                   tuple_row_type;
    typedef Tuple<value_type, k_Cols>                   tuple_col_type;

    Table();
    template <typename T_RealType>
    Table(const Table<T_RealType, k_Rows, k_Cols>& aTable);
    Table(const this_type& aTable);

    explicit Table(const value_type& aValue);

    template <typename T_ArrayType>
    Table(const T_ArrayType(&values)[k_size], table_order aTableOrder);

    Table(const Variadic<value_type, k_size>& a_vars,
                table_order a_tableOrder);

    //------------------------------------------------------------------------
    // Accessors

    // Access range is that of an integer, approx. 2.1 billion rows & cols.
    // If size is more than that, use the get function instead
    value_type& operator() (size_type aRow, size_type aCol);
    const value_type& operator() (size_type aRow, size_type aCol) const;

    value_type Get(size_type aRow, size_type aCol) const;

    void GetRow(size_type aRow, tuple_col_type& aRowOut) const;
    void GetCol(size_type aCol, tuple_row_type& aColOut) const;

    tuple_col_type GetRow(size_type aRow) const;
    tuple_row_type GetCol(size_type aCol) const;

    value_type& operator[] (size_type aIndex);
    const value_type& operator[] (size_type aIndex) const;

    // Direct array access. Generally not recommended but useful for memcpy
    T*        data();
    T const*  data() const;

    template <typename T_OtherValueType, tl_size T_OtherRows, tl_size T_OtherCols>
    void ConvertFrom(const Table<T_OtherValueType, T_OtherRows, T_OtherCols>& a_other);

    template <typename T_OtherValueType, tl_size T_OtherRows, tl_size T_OtherCols, 
              typename T_Policy>
    void ConvertFrom(const Table<T_OtherValueType, T_OtherRows, T_OtherCols>& a_other, 
                     T_Policy a_conversionPolicy);

    template <typename T_OtherTable>
    T_OtherTable  ConvertTo() const;

    template <typename T_OtherTable, typename T_Policy>
    T_OtherTable  ConvertTo() const;

    template <typename T_OtherTable>
    T_OtherTable  Extract(size_type a_rowIndex = 0, size_type a_colIndex = 0) const;

    template <typename T_OtherTable, tl_size T_RowIndex, tl_size T_ColIndex>
    T_OtherTable  Extract() const;

    template <typename T_TableType>
    T_TableType Cast() const;

    //------------------------------------------------------------------------
    // Modifiers

    void Set(const value_type& aValue);

    void Set(const Variadic<value_type, k_size>& a_vars,
                   table_order a_tableOrder);

    template <typename T_ArrayType>
    void Set(const T_ArrayType(&values)[k_size],
                   table_order aTableOrder);

    void Set(size_type aRow, size_type aCol, const T& aValue);
    void SetRow(size_type aRow, const tuple_col_type& aRowIn);
    void SetCol(size_type aCol, const tuple_row_type& aColIn);

    //------------------------------------------------------------------------
    // Operators

    Table& operator= (const Table& aTable);
    bool operator == (const Table& aTable);
    bool operator != (const Table& aTable);

  private:
    typedef type_true     incoming_cols_bigger;
    typedef type_false    incoming_cols_smaller;

    template <typename T_OtherTable, typename T_Policy>
    void DoConvertFrom(const T_OtherTable& a_other, incoming_cols_bigger);

    template <typename T_OtherTable, typename T_Policy>
    void DoConvertFrom(const T_OtherTable& a_other, incoming_cols_smaller);

    template <tl_size T_OtherCols>
    void DoFillRemaining(p_tuple::overflow_same);
    template <tl_size T_OtherCols>
    void DoFillRemaining(p_tuple::overflow_one);
    template <tl_size T_OtherCols>
    void DoFillRemaining(p_tuple::overflow_zero);

  protected:
    T m_values[k_size];

  };

  // -----------------------------------------------------------------------
  // extern template

#define TLOC_EXTERN_TEMPLATE_TABLE(_type_, _rows_, _cols_)\
  TLOC_EXTERN_TEMPLATE(tloc::core_ds::Table<_type_ TLOC_COMMA _rows_ TLOC_COMMA _cols_>)

  TLOC_EXTERN_TEMPLATE_TABLE(s32, 1, 1);
  TLOC_EXTERN_TEMPLATE_TABLE(s32, 2, 2);
  TLOC_EXTERN_TEMPLATE_TABLE(s32, 3, 3);
  TLOC_EXTERN_TEMPLATE_TABLE(s32, 4, 4);

  TLOC_EXTERN_TEMPLATE_TABLE(u32, 1, 1);
  TLOC_EXTERN_TEMPLATE_TABLE(u32, 2, 2);
  TLOC_EXTERN_TEMPLATE_TABLE(u32, 3, 3);
  TLOC_EXTERN_TEMPLATE_TABLE(u32, 4, 4);

  TLOC_EXTERN_TEMPLATE_TABLE(f32, 1, 1);
  TLOC_EXTERN_TEMPLATE_TABLE(f32, 2, 2);
  TLOC_EXTERN_TEMPLATE_TABLE(f32, 3, 3);
  TLOC_EXTERN_TEMPLATE_TABLE(f32, 4, 4);

  TLOC_EXTERN_TEMPLATE_TABLE(s64, 1, 1);
  TLOC_EXTERN_TEMPLATE_TABLE(s64, 2, 2);
  TLOC_EXTERN_TEMPLATE_TABLE(s64, 3, 3);
  TLOC_EXTERN_TEMPLATE_TABLE(s64, 4, 4);

  TLOC_EXTERN_TEMPLATE_TABLE(u64, 1, 1);
  TLOC_EXTERN_TEMPLATE_TABLE(u64, 2, 2);
  TLOC_EXTERN_TEMPLATE_TABLE(u64, 3, 3);
  TLOC_EXTERN_TEMPLATE_TABLE(u64, 4, 4);

  TLOC_EXTERN_TEMPLATE_TABLE(f64, 1, 1);
  TLOC_EXTERN_TEMPLATE_TABLE(f64, 2, 2);
  TLOC_EXTERN_TEMPLATE_TABLE(f64, 3, 3);
  TLOC_EXTERN_TEMPLATE_TABLE(f64, 4, 4);

};};};

#include "tlocTable.inl.h"

#endif