#ifndef TLOC_ARRAY_H
#define TLOC_ARRAY_H

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocAlgorithms.h"
#include "tlocIterator.h"
#include "tlocMemory.h"

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
    typedef ArrayBase<T>                                  this_type;
    typedef T                                             value_type;
    typedef T*                                            pointer;
    typedef T&                                            reference;
    typedef const T&                                      const_reference;
    typedef const T*                                      const_pointer;
    typedef T*                                            iterator;
    typedef const T*                                      const_iterator;
    typedef tl_size                                       size_type;
    typedef tl_ptrdiff                                    difference_type;

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
    TL_I size_type       defaultCapacity();

    //------------------------------------------------------------------------
    // Assignment
    
    TL_I this_type&      operator= (const this_type& a_toCopy);

    //------------------------------------------------------------------------
    // Element access

    TL_I reference        at(size_type a_index);
    TL_I const_reference  at(size_type a_index) const;

    TL_I reference        operator[] (size_type a_index);
    TL_I const_reference  operator[] (size_type a_index) const;

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

    TL_I size_type        size() const;
    TL_I size_type        capacity() const;
    // Checks if size is exactly 0, returns true if so. This is for performance,
    // since one should already not be able to underflow the array.
    // To not underflow the array, one must use TLOC_ASSERT_ARRAY_NOT_EMPTY()
    // this assert checks for negative size.
    TL_I bool             empty() const;
    TL_I bool             full() const;

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void             pop_back();
    TL_I void             pop_back(reference a_out);
    // Function assumes that order does not matter
    TL_I iterator         erase(iterator a_position);
    // Ordering of elements is preserved
    TL_I iterator         erase(iterator a_rangeBegin, iterator a_rangeEnd);
    TL_I void             clear();

  protected:
    //------------------------------------------------------------------------
    // Internal Functions

    TL_FI ArrayBase();
    TL_FI ArrayBase(size_type a_size);

    TL_FI ~ArrayBase();

    //------------------------------------------------------------------------
    // Functions that call memory allocators directly

    TL_I pointer          DoAllocate(const size_type& a_size);
    TL_I pointer          DoReAllocate(const size_type& a_size);
    TL_I void             DoFree(pointer a_ptr);

    // Destroys a range of values only
    TL_I void             DoDestroyValues(pointer a_rangeBegin, 
                                          pointer a_rangeEnd);

    // Copies the incoming value to the end pointer and increments the end pointer.
    // NOTE: function performs no safety checks
    TL_I void             DoAddToEnd(const_reference a_valueToCopy);

    // Increases the storage capacity by reallocation. This function automatically
    // resizes the array according to the formula:
    //        newCapacity = m_capacity ? capacity() * 2 : sm_defaultCapacity;
    // and adjusts the iterators. If successful, old iterators are considered
    // invalid.
    TL_I void             DoReAllocate();

    // Assigns

    //------------------------------------------------------------------------
    // Variables
    pointer               m_begin;
    pointer               m_end;
    pointer               m_capacity;

    //------------------------------------------------------------------------
    // Constants

    static const size_type sm_defaultCapacity;
  };

  template <typename T>
  class Array : public ArrayBase<T>
  {
    friend class Array<T>;

  public:

    //------------------------------------------------------------------------
    // typedefs (similar to vector)
    typedef T                                             value_type;
    typedef T*                                            pointer;
    typedef T&                                            reference;
    typedef const T&                                      const_reference;
    typedef const T*                                      const_pointer;
    typedef T*                                            iterator;
    typedef const T*                                      const_iterator;
    typedef tl_size                                       size_type;
    typedef tl_ptrdiff                                    difference_type;

    typedef tloc::core::reverse_iterator<iterator>        reverse_iterator;
    typedef tloc::core::reverse_iterator<const_iterator>  const_reverse_iterator;

    typedef Array<T>                                      this_type;
    typedef ArrayBase<T>                                  base_type;

    //------------------------------------------------------------------------
    // Constructors

    TL_FI Array();
    TL_FI Array( const this_type& a_toCopy);
    TL_FI explicit Array(size_type a_numElemsToInsert, 
                         const_reference a_valueToCopy);
    TL_FI explicit Array(size_type a_count);
    template <typename T_InputIterator>
    TL_FI Array(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd);

    //------------------------------------------------------------------------
    // Capacity

    TL_I void             resize(size_type a_newSize );
    TL_I void             resize(size_type a_newSize, const_reference a_value );
    TL_I void             reserve(size_type a_newCapacity);
    TL_I void             shrink(size_type a_newCapacity);
    TL_I void             shrink_to_fit();

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void             assign(size_type a_repetitionNum, 
                                 const_reference a_elemToCopy);
    template <typename T_InputIterator>
    TL_I void             assign(T_InputIterator a_rangeBegin,
                                 T_InputIterator a_rangeEnd);
    TL_I void             push_back(const_reference a_valueToCopy);
    TL_I iterator         insert(iterator a_position, 
                                 const_reference a_valueToCopy);
    TL_I void             insert(iterator a_position, 
                                 size_type a_numElemsToInsert,
                                 const_reference aValueToCopy);
    template <typename T_InputIterator>
    TL_I void             insert(iterator a_position, 
                                 T_InputIterator a_rangeBegin,
                                 T_InputIterator a_rangeEnd);
    TL_I void             swap(this_type& a_vec);
  protected:

    // Inserts the value in the specified position by moving all the elements
    // range starting from aPosition by one element and increasing the capacity
    // if required
    TL_I void             DoInsertValue(iterator a_position, 
                                        const_reference a_value);

    // Inserts the range of values in the specified position by moving all
    // the elements from position to end and increasing the capacity if required
    TL_I void             DoInsertValues(iterator a_position, 
                                         size_type a_numElemsToInsert,
                                         const_reference a_value);

    //------------------------------------------------------------------------
    // assign() helpers
    
    typedef type_true   is_arith_t;
    typedef type_false  is_not_arith_t;

    // This is the assign() selector, which is invoked with type-traits
    template <typename T_Number>
    TL_I void             DoAssign(T_Number a_repetitionNum,
                                   T_Number a_elemToCopy, is_arith_t);

    // This is the assign() selector, which is invoked with type-traits
    template <typename T_InputIterator>
    TL_I void             DoAssign(T_InputIterator a_rangeBegin,
                                   T_InputIterator a_rangeEnd, is_not_arith_t);

    //------------------------------------------------------------------------
    // insert() helpers

    typedef type_true   is_integral_t;
    typedef type_false  is_not_integral_t;

    // This is the insert selector, which is invoked with type-traits
    template <typename T_Number>
    TL_I void             DoInsert(iterator a_position, T_Number a_n,
                                   T_Number a_value, is_integral_t);

    // This is the insert selector, which is invoked with type-traits
    template <typename T_InputIterator>
    TL_I void             DoInsert(iterator a_position, T_InputIterator a_first,
                                   T_InputIterator a_last, is_not_integral_t);

    // Helper function for DoInsert
    template <typename T_InputIterator>
    TL_I void             DoInsertByIterator(iterator a_position,
                                             T_InputIterator a_first,
                                             T_InputIterator a_last);
  };

};};

#endif