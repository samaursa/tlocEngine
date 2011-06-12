//////////////////////////////////////////////////////////////////////////
// Table<N, N>

//------------------------------------------------------------------------
// Macros

#define ITERATE_TABLE for (u32 i = 0; i < TABLE_SIZE; ++i)

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI Table<T, T_ROWS, T_COLS>::Table()
{
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI Table<T, T_ROWS, T_COLS>::Table(const Table<T, T_ROWS, T_COLS>& aTable)
{
  operator=(aTable);
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI Table<T, T_ROWS, T_COLS>::Table(const T& aValue)
{
  ITERATE_TABLE
  {
    m_values[i] = aValue;
  }
}

//------------------------------------------------------------------------
// Accessors

#define ASSERT_NUM_ROWS \
  TLOC_ASSERT_LOW_LEVEL(aRow < T_ROWS, "The passed ROW for this table is out of bounds!")
#define ASSERT_NUM_COLS \
  TLOC_ASSERT_LOW_LEVEL(aCol < T_COLS, "The passed COL for this table is out of bounds!")

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI T& Table<T, T_ROWS, T_COLS>::operator() (int aRow, int aCol)
{
  ASSERT_NUM_ROWS;
  ASSERT_NUM_COLS;

  return m_values[aRow + aCol * T_ROWS];
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI const T& Table<T, T_ROWS, T_COLS>::operator() (int aRow, int aCol) const
{
  ASSERT_NUM_ROWS;
  ASSERT_NUM_COLS;

  return m_values[aRow + aCol * T_ROWS];
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI T& Table<T, T_ROWS, T_COLS>::Get(u32 aRow, u32 aCol)
{
  ASSERT_NUM_ROWS;
  ASSERT_NUM_COLS;

  return m_values[aRow + aCol * T_ROWS];
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI const T& Table<T, T_ROWS, T_COLS>::Get(u32 aRow, u32 aCol) const
{
  ASSERT_NUM_ROWS;
  ASSERT_NUM_COLS;

  return m_values[aRow + aCol * T_ROWS];
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI void Table<T, T_ROWS, T_COLS>::GetRow(u32 aRow, Tuple<T, T_COLS>& aRowOut) const
{
  ASSERT_NUM_ROWS;

  for (u32 i = 0; i < T_COLS; ++i)
  {
    aRowOut[i] = m_values[(i * T_COLS) + aRow];
  }
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI void Table<T, T_ROWS, T_COLS>::GetCol(u32 aCol, Tuple<T, T_ROWS>& aColOut) const
{
  ASSERT_NUM_COLS;

  memcpy(aColOut, m_values + (aCol * T_ROWS), sizeof(T) * T_COLS);
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI Table<T, T_ROWS, T_COLS>::operator T*()
{
  return m_values;
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI Table<T, T_ROWS, T_COLS>::operator const T*() const
{
  return m_values;
}


//------------------------------------------------------------------------
// Modifiers

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI void Table<T, T_ROWS, T_COLS>::Set(u32 aRow, u32 aCol, const T& aValue)
{
  ASSERT_NUM_ROWS;
  ASSERT_NUM_COLS;

  m_values[aRow + aCol * T_ROWS] = aValue;
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI void Table<T, T_ROWS, T_COLS>::SetRow(u32 aRow, const Tuple<T, T_COLS>& aRowIn)
{
  ASSERT_NUM_ROWS;

  for (u32 i = 0; i < T_COLS; ++i)
  {
    m_values[ ((i * T_COLS) + aRow) ] = aRowIn[i];
  }
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI void Table<T, T_ROWS, T_COLS>::SetCol(u32 aCol, const Tuple<T, T_ROWS>& aColIn)
{ 
  ASSERT_NUM_COLS;

  memcpy(m_values + (aCol * T_ROWS), aColIn, sizeof(T) * T_ROWS);
}

template <typename T, u32 T_ROWS, u32 T_COLS>
TL_FI Table<T, T_ROWS, T_COLS>& Table<T, T_ROWS, T_COLS>::operator = (const Table& aTable)
{
  memcpy(m_values, aTable, sizeof(T) * TABLE_SIZE);
  return *this;
}