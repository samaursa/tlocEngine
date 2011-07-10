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
    // typedefs (similar to vector)
    typedef T         value_type;
    typedef T*        pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef const T*  const_pointer;
    typedef T*        iterator;
    typedef const T*  const_iterator;

    //------------------------------------------------------------------------
    // Functions
    //
    // Notes: The following methods, unlike all other methods in the engine
    // are started with lower case and match std::vector. This is to facilitate
    // switching between the containers easily if need be

    //------------------------------------------------------------------------
    // General

    // returns the lowest capacity an array can have if size > 0
    TL_I tl_sizet         defaultCapacity();

    //------------------------------------------------------------------------
    // Element access

    TL_I reference        at(tl_sizet aIndex);
    TL_I const_reference  at(tl_sizet aIndex) const;

    TL_I reference        operator[] (tl_sizet aIndex);
    TL_I const_reference  operator[] (tl_sizet aIndex) const;

    TL_I reference        front();
    TL_I const_reference  front() const;

    TL_I reference        back();
    TL_I const_reference  back() const;

    TL_I pointer          data();

    //------------------------------------------------------------------------
    // Iterator access

    TL_I iterator         begin();
    TL_I const_iterator   begin() const;

    TL_I iterator         end();
    TL_I const_iterator   end() const;

    //------------------------------------------------------------------------
    // Capacity

    TL_I tl_sizet         size() const;
    TL_I tl_sizet         capacity() const;
    TL_I bool             empty() const;
    TL_I bool             full() const;

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void             pop_back();
    TL_I void             pop_back(T& aOut);
    // Function assumes that order does not matter
    TL_I void             erase(iterator aPosition);
    // Ordering of elements is preserved
    TL_I void             erase(iterator aRangeBegin, iterator aRangeEnd);
    TL_I void             clear();

  protected:
    //------------------------------------------------------------------------
    // Internal Functions

    ArrayBase();
    ArrayBase(tl_sizet aSize);

    ~ArrayBase();

    //------------------------------------------------------------------------
    // Functions that call memory allocators directly

    TL_I T*               DoAllocate(tl_sizet aSize);
    TL_I T*               DoReAllocate(tl_sizet aSize);
    TL_I void             DoFree(T* aPtr);

    // Destroys a range of values only
    TL_I void             DoDestroyValues(T* aRangeBegin, T* aRangeEnd);

    // Copies the incoming value to the end pointer and increments the end pointer.
    // NOTE: function performs no safety checks
    TL_I void             DoAddToEnd(const T& aValueToCopy);

    // Increases the storage capacity by reallocation. This function automatically
    // resizes the array according to the formula:
    //        newCapacity = m_capacity ? capacity() * 2 : sm_defaultCapacity;
    TL_I void             DoReAllocate();

    // Assigns

    //------------------------------------------------------------------------
    // Variables
    T*                    m_begin;
    T*                    m_end;
    T*                    m_capacity;

    //------------------------------------------------------------------------
    // Constants

    static const tl_sizet sm_defaultCapacity;
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
    // Capacity

    TL_I void             resize(tl_sizet aNewSize );
    TL_I void             resize(tl_sizet aNewSize, const T& aValue );

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void             assign(tl_sizet aRepetitionNum, const T& aElemToCopy);
    template <typename T_InputIterator>
    TL_I void             assign(T_InputIterator aRangeBegin,
                                 T_InputIterator aRangeEnd);
    TL_I void             push_back(const T& aValueToCopy);
    TL_I iterator         insert(iterator aPosition, const T& aValueToCopy);
    TL_I iterator         insert(iterator aPosition, tl_sizet aNumElemsToInsert,
                                 const T& aValueToCopy);
    template <typename T_InputIterator>
    TL_I iterator         insert(iterator aPosition, T_InputIterator aRangeBegin,
                                 T_InputIterator aRangeEnd);
  protected:

    // Inserts the value in the specified position by moving all the elements
    // range starting from aPosition by one element and increasing the capacity
    // if required
    TL_I void             DoInsertValue(T* aPosition, const T& aValue);

    // Inserts the range of values in the specified position by moving all
    // the elements from position to end and increasing the capacity if required
    TL_I void             DoInsertValues(T* position, tl_sizet aNumElemsToInsert,
                                         const T& aValue);

  };
};

#include "tlocArray.inl"

#endif