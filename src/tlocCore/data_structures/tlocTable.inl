#ifndef TLOC_TABLE_INL
#define TLOC_TABLE_INL

#ifndef TLOC_TABLE_H
#error "Must include header before including the inline file"
#endif

#include "tlocTable.h"
#include <tlocCore/data_structures/tlocVariadic.inl>

namespace tloc { namespace core { namespace data_structs {
  //////////////////////////////////////////////////////////////////////////
  // Table<N, N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_TABLE for (tl_int i = 0; i < k_TableSize; ++i)

#define TABLE_TEMPS  typename T, tl_size T_Rows, tl_size T_Cols
#define TABLE_PARAMS T, T_Rows, T_Cols
#define TABLE_TYPE   typename Table<TABLE_PARAMS>

  //------------------------------------------------------------------------
  // Constructors

  template <TABLE_TEMPS>
  Table<TABLE_PARAMS>::
    Table()
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  template <typename T_RealType>
  Table<TABLE_PARAMS>::
    Table(const Table<T_RealType, k_Rows, k_Cols>& aTable)
  {
    ITERATE_TABLE
    { m_values[i] = aTable[i]; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  Table<TABLE_PARAMS>::
    Table(const this_type& aTable)
  { operator=(aTable); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  Table<TABLE_PARAMS>::
    Table(const T& aValue)
  { Set(aValue); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  template <typename T_ArrayType>
  Table<TABLE_PARAMS>::
    Table(const T_ArrayType (&values)[k_TableSize], table_order aTableOrder)
  { Set(values, aTableOrder); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  Table<TABLE_PARAMS>::
    Table (const Variadic<value_type, k_TableSize>& a_vars, 
           table_order a_tableOrder)
  { Set(a_vars, a_tableOrder); }

  //------------------------------------------------------------------------
  // Accessors

#define ASSERT_NUM_ROWS \
  TLOC_ASSERT_LOW_LEVEL(aRow < T_Rows, "The passed ROW for this table is out of bounds!")
#define ASSERT_NUM_COLS \
  TLOC_ASSERT_LOW_LEVEL(aCol < T_Cols, "The passed COL for this table is out of bounds!")

  template <TABLE_TEMPS>
  T& Table<TABLE_PARAMS>::
    operator() (tl_int aRow, tl_int aCol)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;
    return m_values[aRow + aCol * T_Rows];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  const T& Table<TABLE_PARAMS>::
    operator() (tl_int aRow, tl_int aCol) const
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;
    return m_values[aRow + aCol * T_Rows];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  T& Table<TABLE_PARAMS>::Get(size_type aRow, size_type aCol)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;
    return m_values[aRow + aCol * T_Rows];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  const T& Table<TABLE_PARAMS>::
    Get(size_type aRow, size_type aCol) const
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;
    return m_values[aRow + aCol * T_Rows];
  }
  
  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  void Table<TABLE_PARAMS>
    ::GetRow(tl_size aRow, tuple_col_type& aRowOut) const
  {
    ASSERT_NUM_ROWS;

    for (tl_int i = 0; i < T_Cols; ++i)
    { aRowOut[i] = m_values[(i * T_Cols) + aRow]; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  void Table<TABLE_PARAMS>
    ::GetCol(tl_size aCol, tuple_row_type& aColOut) const
  {
    ASSERT_NUM_COLS;
    memcpy(aColOut.data(), m_values + (aCol * T_Rows), sizeof(T) * T_Cols);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  T& Table<TABLE_PARAMS>::
    operator [](tl_int aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < k_TableSize, "Index is out of bounds!");

    return m_values[aIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  const T& Table<TABLE_PARAMS>::
    operator [](tl_int aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < k_TableSize, "Index is out of bounds!");
    return m_values[aIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  TABLE_TYPE::value_type* 
    Table<TABLE_PARAMS>::
    data()
  { return m_values; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  typename Table<TABLE_PARAMS>::value_type const * Table<TABLE_PARAMS>::
    data() const
  { return m_values; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  namespace 
  {
    typedef type_true       typesAreSame;
    typedef type_false      typesAreDifferent;

    template <typename T_OtherType, typename T_ValueType, 
              tl_size T_Rows, tl_size T_Cols>
    const Table<T_OtherType, T_Rows, T_Cols>&
      DoCast(const Table<T_ValueType, T_Rows, T_Cols>& a_table, typesAreSame)
    {
      return a_table;
    }

    template <typename T_OtherType, typename T_ValueType, 
              tl_size T_Rows, tl_size T_Cols>
    Table<T_OtherType, T_Rows, T_Cols>
      DoCast(const Table<T_ValueType, T_Rows, T_Cols>& a_table, typesAreDifferent)
    {
      Table<T_OtherType, T_Rows, T_Cols> temp;
      for(tl_int i = 0; i < T_Rows * T_Cols; ++i)
      {
        temp[i] = core_utils::
          CastNumber<T_OtherType, T_ValueType>(a_table[i]);
      }

      return temp;
    }
  }

  template <TABLE_TEMPS>
  template <typename T_TableType>
  T_TableType Table<TABLE_PARAMS>::
    Cast() const
  {
    typedef typename T_TableType::value_type                other_value_type;
    typedef Loki::IsSameType<value_type, other_value_type>  type_result;
    typedef Loki::Int2Type<type_result::value>              types_same_or_not;

    TLOC_STATIC_ASSERT((T_TableType::k_Rows == k_Rows && 
                        T_TableType::k_Cols == k_Cols), 
                        Rows_and_cols_must_be_same);

    return DoCast<other_value_type, value_type, T_Rows, T_Cols>
      (*this, types_same_or_not());
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <TABLE_TEMPS>
  void Table<TABLE_PARAMS>::
    Set(const T& aValue)
  {
    ITERATE_TABLE
    { m_values[i] = aValue; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  template <typename T_ArrayType>
  void 
    Table<TABLE_PARAMS>::
    Set(const T_ArrayType (&values)[k_TableSize], table_order aTableOrder)
  {
    TLOC_ASSERT_LOW_LEVEL(&values != &m_values, "Set() called on itself. "
      "Undefined behavior.");

    Set(Variadic<value_type, k_TableSize>(values), aTableOrder);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  void 
    Table<TABLE_PARAMS>::
    Set(const Variadic<value_type, k_TableSize>& a_vars, 
        table_order a_tableOrder)
  {
    if (a_tableOrder == k_ColMajor)
    { memcpy(m_values, &a_vars, sizeof(T) * k_TableSize); }
    else
    {
      for (tl_size currRow = 0; currRow < k_Rows; ++currRow)
      {
        for (tl_size currCol = 0; currCol < k_Cols; ++currCol)
        {
          Set(currRow, currCol, a_vars.operator[]( (currRow * k_Cols) + currCol) );
        }
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  void Table<TABLE_PARAMS>::
    Set(tl_size aRow, tl_size aCol, const T& aValue)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;
    m_values[aRow + aCol * T_Rows] = aValue;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  void Table<TABLE_PARAMS>::
    SetRow(tl_size aRow, const tuple_col_type& aRowIn)
  {
    ASSERT_NUM_ROWS;

    for (tl_int i = 0; i < T_Cols; ++i)
    { m_values[ ((i * T_Cols) + aRow) ] = aRowIn[i]; }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  void Table<TABLE_PARAMS>::
    SetCol(tl_size aCol, const tuple_row_type& aColIn)
  {
    ASSERT_NUM_COLS;
    memcpy(m_values + (aCol * T_Rows), aColIn.data(), sizeof(T) * T_Rows);
  }

  //------------------------------------------------------------------------
  // Operators

  template <TABLE_TEMPS>
  Table<TABLE_PARAMS>& Table<TABLE_PARAMS>::
    operator= (const Table& aTable)
  {
    memcpy(m_values, aTable.data(), sizeof(T) * k_TableSize);
    return *this;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TABLE_TEMPS>
  bool Table<TABLE_PARAMS>::
    operator== (const Table<TABLE_PARAMS>& aTable)
  {
    ITERATE_TABLE
    { if (m_values[i] != aTable[i]) { return false; } }

    return true;
  }

  template <TABLE_TEMPS>
  bool Table<TABLE_PARAMS>::
    operator!= (const Table<T, T_Rows, T_Cols>& aTable)
  {
    return !operator==(aTable);
  }

};};};

#endif