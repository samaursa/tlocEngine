#ifndef TLOC_ARRAY_H
#define TLOC_ARRAY_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/utilities/tlocUtils.h>

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ARRAY(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_ARRAY(_Expression, _Msg)
#endif

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // Different policies that Array can handle

  struct Array_Unordered  {};
  struct Array_Ordered    {};

  //////////////////////////////////////////////////////////////////////////
  // Array class

  template <typename T, typename T_Policy = Array_Ordered>
  class ArrayBase
  {
  public:
    //------------------------------------------------------------------------
    // Extended typedefs
    typedef ArrayBase<T, T_Policy>                        this_type;

    typedef T_Policy                                      policy_type;

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

  private:
    typedef type_true                                     array_simple_type;
    typedef type_false                                    array_complex_type;

  public:
    //------------------------------------------------------------------------
    // Functions
    //
    // Notes: The following methods, unlike all other methods in the engine
    // are started with lower case and match std::vector. This is to facilitate
    // switching between the containers easily if need be

    //------------------------------------------------------------------------
    // General

    // returns the lowest capacity an array can have if size > 0
    size_type       defaultCapacity();

    //------------------------------------------------------------------------
    // Assignment

    this_type&      operator= (const this_type& a_toCopy);

    //------------------------------------------------------------------------
    // Element access

    reference        at(size_type a_index);
    const_reference  at(size_type a_index) const;

    reference        operator[] (size_type a_index);
    const_reference  operator[] (size_type a_index) const;

    reference        front();
    const_reference  front() const;

    reference        back();
    const_reference  back() const;

    pointer          data();

    //------------------------------------------------------------------------
    // Iterator access

    iterator         begin();
    const_iterator   begin() const;

    iterator         end();
    const_iterator   end() const;

    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;

    reverse_iterator       rend();
    const_reverse_iterator rend() const;

    //------------------------------------------------------------------------
    // Capacity

    size_type        size() const;
    size_type        capacity() const;
    bool             empty() const;
    bool             full() const;

    //------------------------------------------------------------------------
    // Modifiers

    void             pop_back();
    void             pop_back(reference a_out);
    iterator         erase(iterator a_position);
    iterator         erase(iterator a_rangeBegin, iterator a_rangeEnd);
    void             clear();

    void             swap(this_type& a_vec);

  protected:
    //------------------------------------------------------------------------
    // Internal Functions

    ArrayBase();
    ArrayBase(size_type a_size);

    ~ArrayBase();

    //------------------------------------------------------------------------
    // Functions that call memory allocators directly

    pointer          DoAllocate(const size_type& a_size);
    pointer          DoReAllocate(const size_type& a_size);
    pointer          DoReallocateWithCopy(size_type a_size, array_simple_type);
    pointer          DoReallocateWithCopy(size_type a_size, array_complex_type);

    void             DoFree(pointer a_ptr);

    // Destroys a range of values only
    void             DoDestroyValues(pointer a_rangeBegin,
                                          pointer a_rangeEnd);

    // Copies the incoming value to the end pointer and increments the end
    // pointer. NOTE: function performs no safety checks.
    void             DoAddToEnd(const_reference a_valueToCopy);

    // Increases the storage capacity by reallocation. This function
    // automatically resizes the array according to the formula:
    //        newCapacity = m_capacity ? capacity() * 2 : sm_defaultCapacity;
    // and adjusts the iterators. If successful, old iterators are considered
    // invalid.
    void             DoReAllocate();

    //------------------------------------------------------------------------
    // erase() helpers

    iterator         DoErase(iterator a_position, Array_Ordered);
    iterator         DoErase(iterator a_position, Array_Unordered);

    //------------------------------------------------------------------------
    // Variables
    pointer               m_begin;
    pointer               m_end;
    pointer               m_capacity;

    //------------------------------------------------------------------------
    // Constants

    static const size_type sm_defaultCapacity;
  };

  template <typename T, typename T_Policy = Array_Ordered>
  class Array : public ArrayBase<T, T_Policy>
  {
    friend class Array<T, T_Policy>;

  public:
    //------------------------------------------------------------------------
    // extended typedefs
    typedef Array<T, T_Policy>                            this_type;
    typedef ArrayBase<T, T_Policy>                        base_type;

    typedef typename base_type::policy_type               policy_type;

    //------------------------------------------------------------------------
    // typedefs (similar to vector)
    typedef typename base_type::value_type                value_type;
    typedef typename base_type::pointer                   pointer;
    typedef typename base_type::reference                 reference;
    typedef typename base_type::const_reference           const_reference;
    typedef typename base_type::const_pointer             const_pointer;
    typedef typename base_type::iterator                  iterator;
    typedef typename base_type::const_iterator            const_iterator;
    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::difference_type           difference_type;

    typedef typename base_type::reverse_iterator          reverse_iterator;
    typedef typename base_type::const_reverse_iterator    const_reverse_iterator;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::size;
    using base_type::capacity;
    using base_type::full;
    using base_type::erase;
    using base_type::DoAddToEnd;
    using base_type::DoReAllocate;
    using base_type::m_begin;
    using base_type::m_end;
    using base_type::m_capacity;

    //------------------------------------------------------------------------
    // Constructors

    Array();
    Array( const this_type& a_toCopy);
    explicit Array(size_type a_numElemsToInsert,
                         const_reference a_valueToCopy);
    explicit Array(size_type a_count);
    template <typename T_InputIterator>
    Array(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd);

    //------------------------------------------------------------------------
    // Capacity

    void             resize(size_type a_newSize );
    void             resize(size_type a_newSize, const_reference a_value );
    void             reserve(size_type a_newCapacity);
    void             shrink(size_type a_newCapacity);
    void             shrink_to_fit();

    //------------------------------------------------------------------------
    // Modifiers

    void             assign(size_type a_repetitionNum,
                                 const_reference a_elemToCopy);
    template <typename T_InputIterator>
    void             assign(T_InputIterator a_rangeBegin,
                                 T_InputIterator a_rangeEnd);
    void             push_back(const_reference a_valueToCopy);
    iterator         insert(iterator a_position,
                                 const_reference a_valueToCopy);
    void             insert(iterator a_position,
                                 size_type a_numElemsToInsert,
                                 const_reference aValueToCopy);
    template <typename T_InputIterator>
    void             insert(iterator a_position,
                                 T_InputIterator a_rangeBegin,
                                 T_InputIterator a_rangeEnd);
    void             swap(this_type& a_vec);
  protected:
    //------------------------------------------------------------------------
    // Internal functions

    //------------------------------------------------------------------------
    // assign() helpers

    typedef type_true   is_arith_t;
    typedef type_false  is_not_arith_t;

    // This is the assign() selector, which is invoked with type-traits
    template <typename T_Number>
    void             DoAssign(T_Number a_repetitionNum,
                                   T_Number a_elemToCopy, is_arith_t);

    // This is the assign() selector, which is invoked with type-traits
    template <typename T_InputIterator>
    void             DoAssign(T_InputIterator a_rangeBegin,
                                   T_InputIterator a_rangeEnd, is_not_arith_t);

    //------------------------------------------------------------------------
    // insert() helpers

    // Inserts the value in the specified position by moving all the elements
    // range starting from aPosition by one element and increasing the capacity
    // if required
    void             DoInsertValue(iterator a_position,
                                        const_reference a_value);

    // Inserts the range of values in the specified position by moving all
    // the elements from position to end and increasing the capacity if required
    void             DoInsertValues(iterator a_position,
                                         size_type a_numElemsToInsert,
                                         const_reference a_value);

    typedef type_true   is_integral_t;
    typedef type_false  is_not_integral_t;

    // This is the insert selector, which is invoked with type-traits
    template <typename T_Number>
    void             DoInsert(iterator a_position, T_Number a_n,
                                   T_Number a_value, is_integral_t);

    // This is the insert selector, which is invoked with type-traits
    template <typename T_InputIterator>
    void             DoInsert(iterator a_position, T_InputIterator a_first,
                                   T_InputIterator a_last, is_not_integral_t);

    // Helper function for DoInsert
    template <typename T_InputIterator>
    void             DoInsertByIterator(iterator a_position,
                                             T_InputIterator a_first,
                                             T_InputIterator a_last);
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // swap

  template <typename T, typename T_Policy>
  void swap(Array<T, T_Policy>& a, Array<T, T_Policy>& b)
  { a.swap(b); }

  //////////////////////////////////////////////////////////////////////////
  // default types for easy instantiation

  template <typename T>
  struct ArrayOrdered : public utils::TypedefHelperBase<T>
  {
    typedef Array<T, Array_Ordered> type;
  };

  template <typename T>
  struct ArrayUnordered : public utils::TypedefHelperBase<T>
  {
    typedef Array<T, Array_Unordered> type;
  };

  //////////////////////////////////////////////////////////////////////////
  // Temporary default types to allow the array to work with the template
  // dispatch system because it expects only one argument (temporary because
  // we need a better solution)

  template <typename T>
  class ArrayOrderedTemp
    : public Array<T, Array_Ordered>
  {

  };

  template <typename T>
  class ArrayUnorderedTemp
    : public Array<T, Array_Unordered>
  {
  };

};};};

#endif
