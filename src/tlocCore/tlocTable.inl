namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Table<N, N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_TABLE for (u32 i = 0; i < TABLE_SIZE; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>::Table()
  {
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>::Table(const Table<T, T_Rows, T_Cols>& aTable)
  {
    operator=(aTable);
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>::Table(const T& aValue)
  {
    Set(aValue);
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>::Table(const T values[TABLE_SIZE], 
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

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI T& Table<T, T_Rows, T_Cols>::operator() (int aRow, int aCol)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI const T& Table<T, T_Rows, T_Cols>::operator() (int aRow, int aCol) const
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI T& Table<T, T_Rows, T_Cols>::Get(u32 aRow, u32 aCol)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI const T& Table<T, T_Rows, T_Cols>::Get(u32 aRow, u32 aCol) const
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    return m_values[aRow + aCol * T_Rows];
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::GetRow(u32 aRow, Tuple<T, T_Cols>& aRowOut) const
  {
    ASSERT_NUM_ROWS;

    for (u32 i = 0; i < T_Cols; ++i)
    {
      aRowOut[i] = m_values[(i * T_Cols) + aRow];
    }
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::GetCol(u32 aCol, Tuple<T, T_Rows>& aColOut) const
  {
    ASSERT_NUM_COLS;

    memcpy(aColOut, m_values + (aCol * T_Rows), sizeof(T) * T_Cols);
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>::operator T*()
  {
    return m_values;
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>::operator const T*() const
  {
    return m_values;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::Set(const T& aValue)
  {
    ITERATE_TABLE
    {
      m_values[i] = aValue;
    }
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::Set(const T values[TABLE_SIZE], TABLE_ORDER aTableOrder)
  {
    if (aTableOrder == ROW_MAJOR)
    {
      for (u32 currRow = 0; currRow < T_Rows; ++currRow)
      {
        for (u32 currCol = 0; currCol < T_Cols; ++currCol)
        {
          Set(currRow, currCol, values[(currRow * T_Cols) + currCol] );
        }
      }
    }
    else
    {
      memcpy(m_values, values, sizeof(T) * TABLE_SIZE);
    }
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::Set(u32 aRow, u32 aCol, const T& aValue)
  {
    ASSERT_NUM_ROWS;
    ASSERT_NUM_COLS;

    m_values[aRow + aCol * T_Rows] = aValue;
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::SetRow(u32 aRow, const Tuple<T, T_Cols>& aRowIn)
  {
    ASSERT_NUM_ROWS;

    for (u32 i = 0; i < T_Cols; ++i)
    {
      m_values[ ((i * T_Cols) + aRow) ] = aRowIn[i];
    }
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI void Table<T, T_Rows, T_Cols>::SetCol(u32 aCol, const Tuple<T, T_Rows>& aColIn)
  { 
    ASSERT_NUM_COLS;

    memcpy(m_values + (aCol * T_Rows), aColIn, sizeof(T) * T_Rows);
  }

  template <typename T, u32 T_Rows, u32 T_Cols>
  TL_FI Table<T, T_Rows, T_Cols>& Table<T, T_Rows, T_Cols>::operator = (const Table& aTable)
  {
    memcpy(m_values, aTable, sizeof(T) * TABLE_SIZE);
    return *this;
  }
};