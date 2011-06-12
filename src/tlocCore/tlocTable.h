#ifndef TLOC_TABLE_H
#define TLOC_TABLE_H

#include "tlocCore\tlocBase.h"
#include "tlocCore\tlocStandardFuncs.h"
#include "tlocMath\tlocMath.h"

namespace tloc
{
  #define ITERATE_TABLE for (u32 i = 0; i < TABLE_SIZE; ++i)

  template <typename T, u32 T_ROWS, u32 T_COLS>
  class Table
  {
  public:

    Table() {}
    Table(const Table<T, T_ROWS, T_COLS>& aTable);

    explicit Table(const T& aValue);    

    //------------------------------------------------------------------------
    // Accessors   

    TL_I T& operator[](u32 aIndex);
    TL_I const T& operator[](u32 aIndex) const;
  
  protected:
    enum { TABLE_SIZE = T_ROWS * T_COLS };
    T values[TABLE_SIZE];

  };

#include "tlocTable.inl"
};

#endif