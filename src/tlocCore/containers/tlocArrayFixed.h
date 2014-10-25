#ifndef TLOC_STACK_ARRAY_H
#define TLOC_STACK_ARRAY_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/memory/tlocMemory.h>

#ifndef TLOC_DISABLE_ASSERT_STACK_ARRAY
# define TLOC_ASSERT_STACK_ARRAY(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_STACK_ARRAY(_Expression, _Msg)
#endif

namespace tloc { namespace core { namespace containers {

  template <typename T, tl_size T_Capacity>
  class ArrayFixed
  {
  public:
    enum { k_capacity = T_Capacity };

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to vector)
    typedef ArrayFixed<T, T_Capacity>                     this_type;
    typedef T                                             value_type;
    typedef T*                                            pointer;
    typedef T&                                            reference;
    typedef const T&                                      const_reference;
    typedef const T*                                      const_pointer;
    typedef T*                                            iterator;
    typedef const T*                                      const_iterator;
    typedef tl_size                                       size_type;
    typedef tl_ptrdiff                                    difference_type;

    typedef data_structs::Tuple<value_type, T_Capacity>   container_type;

    typedef tloc::core::reverse_iterator<iterator>        reverse_iterator;
    typedef tloc::core::reverse_iterator<const_iterator>  const_reverse_iterator;

    //------------------------------------------------------------------------
    // Functions
    //
    // Notes:: The Following Methods, unlike all other methods in the engine
    // are starting with lower case and match std::vector. This is to facilitate
    // switching between the containers easily if need be

    //------------------------------------------------------------------------
    // constructors

    ArrayFixed();
    ArrayFixed(const this_type& a_toCopy);
    template <tl_size T_OtherCapacity>
    ArrayFixed(const ArrayFixed<value_type, T_OtherCapacity>& a_toCopy);
    explicit ArrayFixed(size_type a_numElemsToInsert,
                              const value_type& a_valueToCopy);
    explicit ArrayFixed(size_type a_count);
    template <typename T_InputIterator>
    ArrayFixed(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd);

    //------------------------------------------------------------------------
    // Assignment

    this_type&
      operator= (const this_type& a_toCopy);

    template <tl_size T_OtherCapacity>
    this_type&
      operator= (const ArrayFixed<value_type, T_OtherCapacity>& a_toCopy);

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

    //------------------------------------------------------------------------
    // Capacity

    tl_size          size() const;
    tl_size          capacity() const;

    bool             empty() const;
    bool             full() const;

    void             resize(size_type a_newSize);
    void             resize(size_type a_newSize, const value_type& a_value);

    //------------------------------------------------------------------------
    // Modifiers

    void             assign(size_type a_repetitionNum,
                                 const value_type& a_elemToCopy);
    template <typename T_InputIterator>
    void             assign(T_InputIterator a_rangeBegin,
                                 T_InputIterator a_rangeEnd);

    void             push_back(const value_type& a_valueToCopy);

    void             pop_back();
    void             pop_back(value_type& a_out);

    iterator         insert(iterator a_position,
                                 const value_type& a_valueToCopy);
    void             insert(iterator a_position,
                                 size_type a_numElemsToInsert,
                                 const value_type& a_valueToCopy);
    template <typename T_InputIterator>
    void             insert(iterator a_position,
                                 T_InputIterator a_rangeBegin,
                                 T_InputIterator a_rangeEnd);

    iterator         erase(iterator a_position);
    iterator         erase(iterator a_rangeBegin, iterator a_rangeEnd);

    void             clear();

    template <tl_size T_OtherCapacity>
    void             swap(ArrayFixed<value_type, T_OtherCapacity>& a_vec);

  protected:

    //------------------------------------------------------------------------
    // operator=() Helper

    template <tl_size T_OtherCapacity>
    this_type&
      DoOperatorEqual(const ArrayFixed<value_type, T_OtherCapacity>& a_toCopy);

    //------------------------------------------------------------------------
    // resize() Helper

    void             DoResize(size_type a_newSize,
                                   const value_type& a_value);

    //------------------------------------------------------------------------
    // assign() helpers

    typedef type_true is_arith_t;
    typedef type_false is_not_arith_t;

    template <typename T_Number>
    void             DoAssign(T_Number a_repetitionNum,
      T_Number a_elemToCopy, is_arith_t);

    template <typename T_InputIterator>
    void             DoAssign(T_InputIterator a_rangeBegin,
      T_InputIterator a_rangeEnd, is_not_arith_t);

    //------------------------------------------------------------------------
    // push_back() Helpers

    void             DoAddToEnd(const value_type& a_valueToCopy);

    //------------------------------------------------------------------------
    // insert() Helpers

    void             DoInsertValue(value_type* a_position,
                                        const value_type& a_value);
    void             DoInsertValues(value_type* a_position,
                                         size_type a_numElemsToInsert,
                                         const value_type& a_value);

    typedef type_true   is_integral_t;
    typedef type_false  is_not_integral_t;

    template <typename T_Number>
    void             DoInsert(iterator a_position, T_Number a_n,
                                   T_Number a_value, is_integral_t);

    template <typename T_InputIterator>
    void             DoInsert(iterator a_position, T_InputIterator a_first,
                                   T_InputIterator a_last, is_not_integral_t);

    template <typename T_InputIterator>
    void             DoInsertByIterator(iterator a_position,
                                             T_InputIterator a_first,
                                             T_InputIterator a_last);

    //------------------------------------------------------------------------
    // Variables
    container_type        m_begin;
    value_type*           m_end;

  };

  // -----------------------------------------------------------------------
  // extern template

#define TLOC_EXTERN_TEMPLATE_ARRAY_FIXED(_type_, _size_)\
  TLOC_EXTERN_TEMPLATE(tloc::core_conts::ArrayFixed<_type_ TLOC_COMMA _size_>)

};};};

#endif