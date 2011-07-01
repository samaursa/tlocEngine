#ifndef TLOC_ARRAY_H
#define TLOC_ARRAY_H

#include "tlocBase.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Different policies that Array can handle

  struct Array_Unordered {};
  struct Array_Ordered {};
  struct Array_Fast {};
  struct Array_Small {};

  //////////////////////////////////////////////////////////////////////////
  // Array class

  template <typename T>
  class ArrayBase
  {
  public:
    typedef u32 tl_size_t;

  protected:
    //------------------------------------------------------------------------
    // Functions
    
    ArrayBase() : m_data(NULL), m_size(0)
    {
    }
    ArrayBase(tl_size_t aSize)
    {
    }

    T* Allocate(tl_size_t aSize)
    {
      return aSize ? (T*)
    }

    //------------------------------------------------------------------------
    // Variables
    T*      m_data;
    u32     m_size;
  };

  template <typename T>
  class Array
  {
  public:
    Array() : m_data(NULL), m_size(0)
    {
    }

    Array(u32 aSize)
    {      
    }

  private:
    

  private:
    T*    m_data;
    u32   m_size;

  };
};

#endif