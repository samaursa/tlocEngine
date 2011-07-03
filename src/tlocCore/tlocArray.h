#ifndef TLOC_ARRAY_H
#define TLOC_ARRAY_H

#include "tlocBase.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ARRAY(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_ARRAY(_Expression, _Msg)
#endif

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
    //------------------------------------------------------------------------
    // Functions
    // 
    // Notes: The following methods, unlike all other methods in the engine
    // are started with lower case and match std::vector. This is to facilitate
    // switching between the containers easily if need be

    TL_I tl_sizet size()
    {
      return m_size;
    }

    TL_I bool empty()
    {
      return (m_size > 0) ? true : false;
    }

  protected:
    //------------------------------------------------------------------------
    // Functions
    
    ArrayBase() : m_data(NULL), m_size(0)
    {
    }
    ArrayBase(tl_sizet aSize)
    {
      Allocate(aSize);
    }

    TL_I T* Allocate(tl_sizet aSize)
    { 
      return aSize ? (T*)TL_MALLOC(aSize * sizeof(t));
    }

    TL_I T* ReAllocate(tl_sizet aSize)
    {
      return (T*)TL_REALLOC(m_data, aSize);
    }

    TL_I void Free(T* aPtr, tl_sizet aSize)
    {
      TL_FREE(aPtr);
    }

    TL_I void DestroyValues(size_t aStartIndex, size_t aEndIndex)
    {
      TLOC_ASSERT_ARRAY(aStartIndex < m_size, "Start index out of bounds!");
      TLOC_ASSERT_ARRAY(aEndIndex < m_size, "End index out of bounds!");
      TLOC_ASSERT_ARRAY(aStartIndex <= aEndIndex, "Start index > End index!");

      for (tl_sizet i = aStartIndex; i < aEndIndex; ++i)
      {
        (m_data + i)->~T();
      }
    }

    //------------------------------------------------------------------------
    // Variables
    T*        m_data;    
    tl_sizet  m_size;
  };

  template <typename T>
  class Array : public ArrayBase<T>
  {
  public:
    Array() : m_data(NULL), m_size(0)
    {
    }

    Array(tl_sizet aSize)
    {
      Allocate(aSize);
    }

  private:

  };
};

#endif