#ifndef TLOC_TABLE_H
#define TLOC_TABLE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <memory.h>

namespace tloc { namespace core {
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
  protected:
    enum { k_Rows = T_Rows, k_Cols = T_Cols };
    enum { k_TableSize = k_Rows * k_Cols };
    T m_values[k_TableSize];

  public:
    //------------------------------------------------------------------------
    // Constructors

    // Currently only useful for constructor/function accepting an array
    // of values
    typedef enum TABLE_ORDER { k_RowMajor, k_ColMajor } TABLE_ORDER;

    typedef T                                           value_type;
    typedef tl_size                                     size_type;
    typedef Table<value_type, k_Rows, k_Cols>           this_type;
    typedef Tuple<value_type, k_Rows>                   tuple_row_type;
    typedef Tuple<value_type, k_Cols>                   tuple_col_type;

    TL_FI Table();
    TL_FI Table(const this_type& aTable);

    TL_FI explicit Table(const value_type& aValue);
    TL_FI Table(const value_type (&values)[k_TableSize], TABLE_ORDER aTableOrder);

    //------------------------------------------------------------------------
    // Accessors

    // Access range is that of an integer, approx. 2.1 billion rows & cols.
    // If size is more than that, use the get function instead
    TL_FI value_type& operator() (tl_int aRow, tl_int aCol);
    TL_FI const value_type& operator() (tl_int aRow, tl_int aCol) const;

    TL_FI value_type& Get(size_type aRow, size_type aCol);
    TL_FI const value_type& Get(size_type aRow, size_type aCol) const;

    TL_FI void GetRow(size_type aRow, tuple_col_type& aRowOut) const;
    TL_FI void GetCol(size_type aCol, tuple_row_type& aColOut) const;

    // Direct array access. Generally not recommended but useful for memcpy
    TL_FI operator T* ();
    TL_FI operator const T* () const;

    //------------------------------------------------------------------------
    // Modifiers

    TL_FI void Set(const value_type& aValue);
    TL_FI void Set(const value_type (&values)[k_TableSize],
                   TABLE_ORDER aTableOrder);
    TL_FI void Set(size_type aRow, size_type aCol, const T& aValue);
    TL_FI void SetRow(size_type aRow, const tuple_col_type& aRowIn);
    TL_FI void SetCol(size_type aCol, const tuple_row_type& aColIn);

    //------------------------------------------------------------------------
    // Operators

    TL_FI this_type& operator = (const this_type& aTable);
    TL_FI bool operator == (const Table& aTable);
    TL_FI bool operator != (const Table& aTable);
  };

};};

#ifdef TLOC_FULL_SOURCE
#include "tlocTable.inl"
#endif

#endif