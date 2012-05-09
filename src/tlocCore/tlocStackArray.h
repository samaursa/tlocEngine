#ifndef TLOC_STACK_ARRAY_H
#define TLOC_STACK_ARRAY_H

#include "tlocBase.h"
#include "tlocTypes.h"
#include "tlocTuple.h"

#ifndef TLOC_DISABLE_ASSERT_STACK_ARRAY
# define TLOC_ASSERT_STACK_ARRAY(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_STACK_ARRAY(_Expression, _Msg)
#endif

namespace tloc { namespace core {

  template <typename T, tl_size T_Capacity>
  class StackArray
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to vector)
    typedef StackArray<T, T_Capacity>                     this_type;
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
    // Notes:: The Following Methods, unlike all other methods in the engine 
    // are starting with lower case and match std::vector. This is to facilitate 
    // switching between the containers easily if need be

    //------------------------------------------------------------------------
    // constructors
    
    TL_FI StackArray();
    TL_FI StackArray(const this_type& a_toCopy);
    TL_FI explicit StackArray(size_type a_numElemsToInsert, 
                              const value_type& a_valueToCopy);
    TL_FI explicit StackArray(size_type a_count);
    template <typename T_InputIterator>
    TL_FI StackArray(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd);

    TL_FI ~StackArray();

    //------------------------------------------------------------------------
    // Assignment
    
    TL_I this_type&       operator= (const this_type& a_toCopy);

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
    
    TL_I tl_size          size() const;
    TL_I tl_size          capacity() const;

    TL_I bool             empty() const;
    TL_I bool             full() const;

    //------------------------------------------------------------------------
    // Modifiers

    TL_I void             assign(size_type a_repetitionNum, 
                                 const value_type& a_elemToCopy);
    template <typename T_InputIterator>
    TL_I void             assign(T_InputIterator a_rangeBegin, 
                                 T_InputIterator a_rangeEnd);
    
    TL_I void             push_back(const value_type& a_valueToCopy);

    TL_I void             pop_back();
    TL_I void             pop_back(value_type& a_out);

    TL_I iterator         insert(iterator a_position, 
                                 const value_type& a_valueToCopy);
    TL_I void             insert(value_type* a_position, 
                                 size_type a_numElemsToInsert, 
                                 const value_type& a_valueToCopy);
    template <typename T_InputIterator>
    TL_I void             insert(iterator a_position, 
                                 T_InputIterator a_rangeBegin, 
                                 T_InputIterator a_rangeEnd);
    
    TL_I iterator         erase(iterator a_position);
    TL_I iterator         erase(iterator a_rangeBegin, iterator a_rangeEnd);
    
    TL_I void             clear();

    TL_I void             swap(this_type& a_vec);

  protected:

    //------------------------------------------------------------------------
    // Insert Helpers
    TL_I void             DoAddToEnd(const value_type& a_valueToCopy);

    TL_I void             DoInsertValue(value_type* a_position, 
                                        const value_type& a_value);
    TL_I void             DoInsertValues(value_type* a_position, 
                                         size_type a_numElemsToInsert, 
                                         const value_type& a_value);

    typedef type_true   is_integral_t;
    typedef type_false  is_not_integral_t;

    template <typename T_Number>
    TL_I void             DoInsert(iterator a_position, T_Number a_n, 
                                   T_Number a_value, is_integral_t);

    template <typename T_InputIterator>
    TL_I void             DoInsert(iterator a_position, T_InputIterator a_first, 
                                   T_InputIterator a_last, is_not_integral_t);

    template <typename T_InputIterator>
    TL_I void             DoInsertByIterator(iterator a_position, 
                                             T_InputIterator a_first, 
                                             T_InputIterator a_last);

    //------------------------------------------------------------------------
    // assign() helpers

    typedef type_true is_arith_t;
    typedef type_false is_not_arith_t;

    template <typename T_Number>
    TL_I void             DoAssign(T_Number a_repetitionNum, 
                                   T_Number a_elemToCopy, is_arith_t);

    template <typename T_InputIterator>
    TL_I void             DoAssign(T_InputIterator a_rangeBegin, 
                                   T_InputIterator a_rangeEnd, is_not_arith_t);

    //------------------------------------------------------------------------
    // Variables
    Tuple<value_type, T_Capacity>     m_values;
    value_type*                       m_end;

  };

};};

#endif