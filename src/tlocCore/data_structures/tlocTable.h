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
    enum { k_TableSize = k_Rows * k_Cols };

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
    Table(const T_ArrayType(&values)[k_TableSize], table_order aTableOrder);

    Table(const Variadic<value_type, k_TableSize>& a_vars,
                table_order a_tableOrder);

    //------------------------------------------------------------------------
    // Accessors

    // Access range is that of an integer, approx. 2.1 billion rows & cols.
    // If size is more than that, use the get function instead
    value_type& operator() (tl_int aRow, tl_int aCol);
    const value_type& operator() (tl_int aRow, tl_int aCol) const;

    value_type& Get(size_type aRow, size_type aCol);
    const value_type& Get(size_type aRow, size_type aCol) const;

    void GetRow(size_type aRow, tuple_col_type& aRowOut) const;
    void GetCol(size_type aCol, tuple_row_type& aColOut) const;

    value_type& operator[] (tl_int aIndex);
    const value_type& operator[] (tl_int aIndex) const;

    // Direct array access. Generally not recommended but useful for memcpy
    T*        data();
    T const*  data() const;

    template <typename T_TableType>
    T_TableType Cast() const;

    //------------------------------------------------------------------------
    // Modifiers

    void Set(const value_type& aValue);

    void Set(const Variadic<value_type, k_TableSize>& a_vars,
                   table_order a_tableOrder);

    template <typename T_ArrayType>
    void Set(const T_ArrayType(&values)[k_TableSize],
                   table_order aTableOrder);

    void Set(size_type aRow, size_type aCol, const T& aValue);
    void SetRow(size_type aRow, const tuple_col_type& aRowIn);
    void SetCol(size_type aCol, const tuple_row_type& aColIn);

    //------------------------------------------------------------------------
    // Operators

    Table& operator= (const Table& aTable);
    bool operator == (const Table& aTable);
    bool operator != (const Table& aTable);

  protected:
    T m_values[k_TableSize];

  };

};};};

#endif