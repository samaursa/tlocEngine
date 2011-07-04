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

  struct Array_Unordered  {};
  struct Array_Ordered    {};
  struct Array_Fixed      {};
  struct Array_Dynamic    {};

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

    //------------------------------------------------------------------------
    // Element access

    TL_I T&           at(tl_sizet aIndex);
    TL_I const T&     at(tl_sizet aIndex) const;

    TL_I T&           operator[] (tl_sizet aIndex);
    TL_I const T&     operator[] (tl_sizet aIndex) const;

    TL_I T&           front();
    TL_I const T&     front() const;

    TL_I T&           back();
    TL_I const T&     back() const;

    TL_I T*           data();

    //------------------------------------------------------------------------
    // Iterator access

    TL_I T*           begin();
    TL_I const T*     begin() const;

    TL_I T*           end();
    TL_I const T*     end() const;

    //------------------------------------------------------------------------
    // Capacity

    TL_I tl_sizet     size() const;
    TL_I tl_sizet     capacity() const;
    TL_I bool         empty() const;
    TL_I bool         full() const;

  protected:
    //------------------------------------------------------------------------
    // Internal Functions

    ArrayBase();
    ArrayBase(tl_sizet aSize);

    TL_I T*       Allocate(tl_sizet aSize);
    TL_I T*       ReAllocate(tl_sizet aSize);
    TL_I void     Free(T* aPtr, tl_sizet aSize);
    TL_I void     DestroyValues(size_t aStartIndex, size_t aEndIndex);

    //------------------------------------------------------------------------
    // Variables
    T*        m_begin;
    T*        m_end;
    T*        m_capacity;
  };

  template <typename T>
  class Array : public ArrayBase<T>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    Array();
    Array(tl_sizet aSize);

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void         assign(T* rangeBegin, T* rangeEnd);
    TL_I void         assign(tl_sizet aRepetitionNum, const T& aElemToCopy);

    void              push_back(const T& aValueToCopy);
    void              pop_back();
    void              pop_back(T& aOut);

  private:

  };
};

#include "tlocArray.inl"

#endif