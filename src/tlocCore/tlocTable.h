#ifndef TLOC_TABLE_H
#define TLOC_TABLE_H

#include "tlocCore\tlocBase.h"
#include "tlocCore\tlocStandardFuncs.h"
#include "tlocMath\tlocMath.h"

namespace tloc
{
  #define ITERATE_TABLE for (tl_uint32 i = 0; i < TABLE_SIZE; ++i)

  template <typename T, tl_uint32 T_ROWS, tl_uint32 T_COLS>
  class Table
  {
  public:

    Table() {}
    Table(const Table<T, T_ROWS, T_COLS>& aTable);

    explicit Table(const T& aValue);    

    TL_I T& operator[](tl_uint32 aIndex);
    TL_I const T& operator[](tl_uint32 aIndex) const;

    //------------------------------------------------------------------------
    // Accessors   

    
  
  protected:
    enum { TABLE_SIZE = T_ROWS * T_COLS };
    T values[TABLE_SIZE];

  };
};

#endif