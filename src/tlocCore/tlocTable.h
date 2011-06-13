#ifndef TLOC_TABLE_H
#define TLOC_TABLE_H

#include "tlocCore\tlocBase.h"
#include "tlocCore\tlocStandardFuncs.h"
#include "tlocCore\tlocTuple.h"

namespace tloc
{
  // Column major ordering (because OpenGL uses it. Switching back and forth
  // is not a problem as long as we are consistent)
  // 
  // PERFORMANCE NOTES: In the column major order, some table operations 
  // may be faster. These include Setting the columns via a Tuple<> and 
  // getting a column via a Tuple<>. Vice-versa is true for row major order
  // (not yet supported).
  template <typename T, u32 T_ROWS, u32 T_COLS>
  class Table
  {
  protected:
    enum { TABLE_SIZE = T_ROWS * T_COLS };
    T m_values[TABLE_SIZE];

  public:
    //------------------------------------------------------------------------
    // Constructors

    // Currently only useful for constructor/function accepting an array
    // of values
    typedef enum TABLE_ORDER { ROW_MAJOR, COL_MAJOR } TABLE_ORDER;

    TL_FI Table();
    TL_FI Table(const Table<T, T_ROWS, T_COLS>& aTable);

    TL_FI explicit Table(const T& aValue);    
    TL_FI Table(const T values[TABLE_SIZE], TABLE_ORDER aTableOrder);

    //------------------------------------------------------------------------
    // Accessors   

    // Access range is that of an integer, approx. 2.1 billion rows & cols. 
    // If size is more than that, use the get function instead
    TL_FI T& operator() (int aRow, int aCol);
    TL_FI const T& operator() (int aRow, int aCol) const;

    TL_FI T& Get(u32 aRow, u32 aCol);
    TL_FI const T& Get(u32 aRow, u32 aCol) const;

    TL_FI void GetRow(u32 aRow, Tuple<T, T_COLS>& aRowOut) const;
    TL_FI void GetCol(u32 aCol, Tuple<T, T_ROWS>& aColOut) const;

    // Direct array access. Generally not recommended but useful for memcpy
    TL_FI operator T* ();
    TL_FI operator const T* () const;

    //------------------------------------------------------------------------
    // Modifiers

    TL_FI void Set(const T& aValue);
    TL_FI void Set(const T values[TABLE_SIZE], TABLE_ORDER aTableOrder);
    TL_FI void Set(u32 aRow, u32 aCol, const T& aValue);
    TL_FI void SetRow(u32 aRow, const Tuple<T, T_COLS>& aRowIn);
    TL_FI void SetCol(u32 aCol, const Tuple<T, T_ROWS>& aColIn);    

    TL_FI Table<T, T_ROWS, T_COLS>& operator = (const Table& aTable);
  };

#include "tlocTable.inl"
};

#endif