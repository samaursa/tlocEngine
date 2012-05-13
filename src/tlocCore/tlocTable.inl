#ifndef TLOC_TABLE_INL
#define TLOC_TABLE_INL

#ifndef TLOC_TABLE_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {
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
  TL_FI Table<TABLE_PARAMS>::Table()
  {
  }

  template <TABLE_TEMPS>
  TL_FI Table<TABLE_PARAMS>::Table(const this_type& aTable)
  {
    operator=(aTable);
  }

  template <TABLE_TEMPS>
  TL_FI Table<TABLE_PARAMS>::Table(const T& aValue)
  {
    Set(aValue);
  }

  template <TABLE_TEMPS>
  TL_FI Table<TABLE_PARAMS>::Table(const T (&values)[k_TableSize],
    TABLE_ORDER aTableOrder)
  {
    Set(values, aTableOrder);
  }

  //------------------------------------------------------------------------
  // Accessors

#define ASSERT_NUM_ROWS \
  TLOC_ASSERT_LOW_LEVEL(aRow < T_Rows, "The passed ROW for this table is out of bounds!")
#define ASSERT_NUM_COLS \
  TLOC_ASSERT_LOW_LEVEL(aCol < T_Cols, "The passed COL for this table is out of bounds!")

  template <TABLE_TEMPS>
  TL_FI T& Table<TABLE_PARAMS>::operator() (tl_int aRow, tl_int aCol)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <TABLE_TEMPS>
  TL_FI const T& Table<TABLE_PARAMS>::operator() (tl_int aRow, 
                                                       tl_int aCol) const
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <TABLE_TEMPS>
  TL_FI T& Table<TABLE_PARAMS>::Get(size_type aRow, size_type aCol)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <TABLE_TEMPS>
  TL_FI const T& Table<TABLE_PARAMS>::Get(size_type aRow, 
                                               size_type aCol) const
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>
    ::GetRow(tl_size aRow, tuple_col_type& aRowOut) const
  {
    ASSERT_NUM_ROWS;

    for (tl_int i = 0; i < T_Cols; ++i)
    {
      aRowOut[i] = m_values[(i * T_Cols) + aRow];
    }
  }

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>
    ::GetCol(tl_size aCol, tuple_row_type& aColOut) const
  {
    ASSERT_NUM_COLS;

    memcpy(aColOut, m_values + (aCol * T_Rows), sizeof(T) * T_Cols);
  }

  template <TABLE_TEMPS>
  TL_FI Table<TABLE_PARAMS>::operator T*()
  {
    return m_values;
  }

  template <TABLE_TEMPS>
  TL_FI Table<TABLE_PARAMS>::operator const T*() const
  {
    return m_values;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>::Set(const T& aValue)
  {
    ITERATE_TABLE
    {
      m_values[i] = aValue;
    }
  }

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>
    ::Set(const T (&values)[k_TableSize], TABLE_ORDER aTableOrder)
  {
    TLOC_ASSERT_LOW_LEVEL(&values != &m_values, "Set() called on itself. "
      L"Undefined behavior.");

    if (aTableOrder == k_ColMajor)
    {
      memcpy(m_values, values, sizeof(T) * k_TableSize);
    }
    else
    {
      for (tl_size currRow = 0; currRow < T_Rows; ++currRow)
      {
        for (tl_size currCol = 0; currCol < T_Cols; ++currCol)
        {
          Set(currRow, currCol, values[(currRow * T_Cols) + currCol] );
        }
      }
    }
  }

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>::Set(tl_size aRow, tl_size aCol, const T& aValue)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    m_values[aRow + aCol * T_Rows] = aValue;
  }

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>::SetRow(tl_size aRow, 
                                         const tuple_col_type& aRowIn)
  {
    ASSERT_NUM_ROWS;

    for (tl_int i = 0; i < T_Cols; ++i)
    {
      m_values[ ((i * T_Cols) + aRow) ] = aRowIn[i];
    }
  }

  template <TABLE_TEMPS>
  TL_FI void Table<TABLE_PARAMS>::SetCol(tl_size aCol, 
                                         const tuple_row_type& aColIn)
  {
    ASSERT_NUM_COLS;

    memcpy(m_values + (aCol * T_Rows), aColIn, sizeof(T) * T_Rows);
  }

  //------------------------------------------------------------------------
  // Operators

  template <TABLE_TEMPS>
  TL_FI TABLE_TYPE::this_type& Table<TABLE_PARAMS>
    ::operator = (const this_type& aTable)
  {
    memcpy(m_values, aTable, sizeof(T) * k_TableSize);

    return *this;
  }

  template <TABLE_TEMPS>
  TL_FI bool Table<TABLE_PARAMS>
    ::operator == (const Table<TABLE_PARAMS>& aTable)
  {
    ITERATE_TABLE
    {
      if (m_values[i] != aTable[i]) { return false; }
    }

    return true;
  }

  template <TABLE_TEMPS>
  TL_FI bool Table<TABLE_PARAMS>
    ::operator != (const Table<T, T_Rows, T_Cols>& aTable)
  {
    return !operator==(aTable);
  }
};};

#endif