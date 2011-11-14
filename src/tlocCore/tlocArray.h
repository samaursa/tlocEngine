#ifndef TLOC_ARRAY_H
#define TLOC_ARRAY_H

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocAlgorithms.h"
#include "tlocIterator.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ARRAY(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_ARRAY(_Expression, _Msg)
#endif

namespace tloc { namespace core {

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
    typedef T                                       value_type;
    typedef T*                                      pointer;
    typedef T&                                      reference;
    typedef const T&                                const_reference;
    typedef const T*                                const_pointer;
    typedef T*                                      iterator;
    typedef const T*                                const_iterator;
    typedef tl_size                                 size_type;
    typedef tl_ptrdiff                              difference_type;

    typedef tloc::core::reverse_iterator<iterator>        reverse_iterator;
    typedef tloc::core::reverse_iterator<const_iterator>  const_reverse_iterator;

    //------------------------------------------------------------------------
    // Functions
    //
    // Notes: The following methods, unlike all other methods in the engine
    // are started with lower case and match std::vector. This is to facilitate
    // switching between the containers easily if need be

    //------------------------------------------------------------------------
    // General

    // returns the lowest capacity an array can have if size > 0
    TL_I tl_size         defaultCapacity();

    //------------------------------------------------------------------------
    // Element access

    TL_I reference        at(tl_size aIndex);
    TL_I const_reference  at(tl_size aIndex) const;

    TL_I reference        operator[] (tl_size aIndex);
    TL_I const_reference  operator[] (tl_size aIndex) const;

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

    TL_I tl_size          size() const;
    TL_I tl_size          capacity() const;
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
    ArrayBase(tl_size aSize);

    ~ArrayBase();

    //------------------------------------------------------------------------
    // Functions that call memory allocators directly

    TL_I T*               DoAllocate(const tl_size& aSize);
    TL_I T*               DoReAllocate(const tl_size& aSize);
    TL_I void             DoFree(T* aPtr);

    // Destroys a range of values only
    TL_I void             DoDestroyValues(T* aRangeBegin, T* aRangeEnd);

    // Copies the incoming value to the end pointer and increments the end pointer.
    // NOTE: function performs no safety checks
    TL_I void             DoAddToEnd(const T& aValueToCopy);

    // Increases the storage capacity by reallocation. This function automatically
    // resizes the array according to the formula:
    //        newCapacity = m_capacity ? capacity() * 2 : sm_defaultCapacity;
    // and adjusts the iterators. If successful, old iterators are considered
    // invalid.
    TL_I void             DoReAllocate();

    // Assigns

    //------------------------------------------------------------------------
    // Variables
    T*                    m_begin;
    T*                    m_end;
    T*                    m_capacity;

    //------------------------------------------------------------------------
    // Constants

    static const tl_size sm_defaultCapacity;
  };

  template <typename T>
  class Array : public ArrayBase<T>
  {
    friend class Array<T>;

  public:

    //------------------------------------------------------------------------
    // typedefs (similar to vector)
    typedef T                                       value_type;
    typedef T*                                      pointer;
    typedef T&                                      reference;
    typedef const T&                                const_reference;
    typedef const T*                                const_pointer;
    typedef T*                                      iterator;
    typedef const T*                                const_iterator;
    typedef tl_size                                 size_type;
    typedef tl_ptrdiff                              difference_type;

    typedef tloc::core::reverse_iterator<iterator>        reverse_iterator;
    typedef tloc::core::reverse_iterator<const_iterator>  const_reverse_iterator;

    typedef Array<T>                          this_type;
    typedef ArrayBase<T>                      base_type;

    //------------------------------------------------------------------------
    // Constructors

    Array();
    explicit Array(tl_size aSize);
    Array( const Array<T>& toCopy);
    Array(tl_size aNumElemsToInsert, const T& aValueToCopy = T());
    template <typename T_InputIterator>
    Array(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd);

    //------------------------------------------------------------------------
    // Capacity

    TL_I void             resize(tl_size aNewSize );
    TL_I void             resize(tl_size aNewSize, const T& aValue );
    TL_I void             reserve(tl_size aNewCapacity);
    TL_I void             shrink(tl_size aNewCapacity);
    TL_I void             shrink_to_fit();

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void             assign(tl_size aRepetitionNum, const T& aElemToCopy);
    template <typename T_InputIterator>
    TL_I void             assign(T_InputIterator aRangeBegin,
                                 T_InputIterator aRangeEnd);
    TL_I void             push_back(const T& aValueToCopy);
    TL_I iterator         insert(iterator aPosition, const T& aValueToCopy);
    TL_I void             insert(T* aPosition, tl_size aNumElemsToInsert,
                                 const T& aValueToCopy);
    template <typename T_InputIterator>
    TL_I void             insert(iterator aPosition, T_InputIterator aRangeBegin,
                                 T_InputIterator aRangeEnd);
    TL_I void             swap(Array<T>& aVec);
  protected:

    // Inserts the value in the specified position by moving all the elements
    // range starting from aPosition by one element and increasing the capacity
    // if required
    TL_I void             DoInsertValue(T* aPosition, const T& aValue);

    // Inserts the range of values in the specified position by moving all
    // the elements from position to end and increasing the capacity if required
    TL_I void             DoInsertValues(T* position, tl_size aNumElemsToInsert,
                                         const T& aValue);

    // This is the assign() selector, which is invoked with type-traits
    template <typename T_Number>
    TL_I void             DoAssign(T_Number aRepetitionNum,
                                   T_Number aElemToCopy, type_true);

    // This is the assign() selector, which is invoked with type-traits
    template <typename T_InputIterator>
    TL_I void             DoAssign(T_InputIterator aRangeBegin,
                                   T_InputIterator aRangeEnd, type_false);


    // This is the insert selector, which is invoked with type-traits
    template <typename T_Number>
    TL_I void             DoInsert(iterator aPosition, T_Number aN,
                                   T_Number aValue, type_true);

    // This is the insert selector, which is invoked with type-traits
    template <typename T_InputIterator>
    TL_I void             DoInsert(iterator position, T_InputIterator first,
                                   T_InputIterator last, type_false);

    // Helper function for DoInsert
    template <typename T_InputIterator>
    TL_I void             DoInsertByIterator(iterator position,
                                             T_InputIterator first,
                                             T_InputIterator last);
  };

};};

#endif