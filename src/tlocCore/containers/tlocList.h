#ifndef TLOC_LIST_H
#define TLOC_LIST_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/utilities/tlocUtils.h>

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_LIST
# define TLOC_ASSERT_LIST(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_LIST(_Expression, _Msg)
#endif

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // Different policies that List can handle

  struct List_Dynamic {};
  struct List_Bucket  {};
  struct List_Fixed   {};

  //////////////////////////////////////////////////////////////////////////
  // List node

  template <typename T, typename T_ItrTag>
  class ListNode
  {
    ListNode();
  };

  template <typename T>
  class ListNode<T, singly_linked_tag>
  {
  public:

    typedef ListNode<T, singly_linked_tag>  this_type;

    typedef T                               value_type;
    typedef T*                              pointer_type;
    typedef const T*                        const_pointer_type;
    typedef T&                              reference_type;
    typedef const T&                        const_reference_type;
    typedef tl_ptrdiff                      difference_type;

    typedef singly_linked_tag               iterator_category;

    TL_FI ListNode();
    TL_FI ListNode(const this_type& aOther);

    TL_FI        void       init();
    TL_STATIC_FI void       swap(this_type& a, this_type& b);
    TL_STATIC_FI void       swap_after(this_type& a, this_type& b);
    TL_FI        void       insert_after(this_type* aNext);
    TL_FI        void       remove_after();
    TL_FI        void       splice_after(this_type* aFirst, this_type* aLast);
    TL_FI        void       reverse();

    TL_FI        this_type*           getNext();
    TL_FI        const this_type*     getNext() const;
    TL_FI        this_type*           getPrev();
    TL_FI        const this_type*     getPrev() const;
    TL_FI        reference_type       getValue();
    TL_FI        const_reference_type getValue() const;
  private:

    this_type*    m_next;
    value_type    m_value;
  };

  template <typename T>
  class ListNode<T, doubly_linked_tag>
  {
  public:

    typedef ListNode<T, doubly_linked_tag>  this_type;

    typedef T                               value_type;
    typedef T*                              pointer_type;
    typedef const T*                        const_pointer_type;
    typedef T&                              reference_type;
    typedef const T&                        const_reference_type;
    typedef tl_ptrdiff                      difference_type;

    typedef doubly_linked_tag               iterator_category;

    TL_FI ListNode();
    TL_FI ListNode(const this_type& aOther);

    TL_FI        void       init();
    TL_STATIC_FI void       swap(this_type& a, this_type& b);
    TL_STATIC_FI void       swap_after(this_type& a, this_type& b);
    TL_FI        void       insert_after(this_type* aNext);
    TL_FI        void       remove_after();
    TL_FI        void       splice_after(this_type* aFirst, this_type* aLast);
    TL_FI        void       reverse();

    TL_FI        this_type*           getNext();
    TL_FI        const this_type*     getNext() const;
    TL_FI        this_type*           getPrev();
    TL_FI        const this_type*     getPrev() const;
    TL_FI        reference_type       getValue();
    TL_FI        const_reference_type getValue() const;

  private:

    this_type*    m_next;
    this_type*    m_prev;
    value_type    m_value;
  };

  template <typename T, bool T_DedicatedSize>
  class ListBase
  {
  protected:
    ConditionalType<T, T_DedicatedSize> m_size;
  };

  template <typename T, typename T_Node = ListNode<T, doubly_linked_tag>,
            typename T_Policy = List_Dynamic(), bool T_DedicatedSize = true>

  ///-------------------------------------------------------------------------
  /// @brief
  /// List class. The list can be bi-directional or uni-directional. Some
  /// operations are very slow in uni-directional lists e.g. operations
  /// which rely on a prev node. In uni-directional lists, this node has
  /// to be found which is an O(n) operation. These operations include
  /// (not an exhaustive list):
  ///   * push_back() - user push_front()
  ///   * pop_back() - use pop_front()
  ///   * erase() - use erase_after()
  ///   * splice() - use splice_after()
  ///   * insert() - use insert_after()
  ///
  /// The above functions can be disabled entirely for a singly_linked list by
  /// defining TLOC_DISABLE_EXTENDED_SINGLY_LIST in which case calling the
  /// functions will result in a compile error
  ///
  /// The class is standard compliant but has extra functionality which
  /// makes it a std::forward_list&lt;&gt; (c++11) as well if a
  /// singly_linked_node is used. Alternatively you can simply use
  /// tlocForwardList&lt;&gt; which does not have some methods such as
  /// erase() and remove() but instead has erase_after()
  /// and remove_after()
  ///
  /// @notes The class's helper functions are sometimes written as
  /// xxxxNext(). The reason for this is to help with a singly linked
  /// list.
  ///-------------------------------------------------------------------------
  class List
  {
  public:
    //------------------------------------------------------------------------
    // typedefs
    typedef List<T, T_Node,T_Policy, T_DedicatedSize>   this_type;
    typedef T_Node                                      node_type;

    typedef list_iterator<node_type, typename node_type::iterator_category, T, T*, T&>  iterator;
    typedef list_iterator<node_type, typename node_type::iterator_category, T, const T*, const T&> const_iterator;

    typedef T                                           value_type;
    typedef T*                                          pointer;
    typedef T&                                          reference;
    typedef const T&                                    const_reference;
    typedef const T*                                    const_pointer;
    typedef tl_size                                     size_type;
    typedef tl_ptrdiff                                  difference_type;
    typedef
      tloc::core::reverse_iterator<iterator>            reverse_iterator;
    typedef
      tloc::core::reverse_iterator<const_iterator>      const_reverse_iterator;

    typedef ConditionalTypePackage
      <node_type*, size_type, T_DedicatedSize>          size_and_node;
    typedef typename size_and_node::cond_type           list_size;

  public:
    TL_FI List();
    TL_FI explicit List(size_type aNumTimes, const T& aValue = T());

    template <typename T_InputItr>
    TL_FI List(T_InputItr aFirst, T_InputItr aLast);
    TL_FI List(const this_type& aOther);

    TL_FI ~List();

    this_type& operator= (const this_type& aOther);

    //------------------------------------------------------------------------
    // Iterator access

    TL_FI iterator        begin();
    TL_FI const_iterator  begin() const;
    TL_FI const_iterator  cbegin() const;
    TL_FI iterator        end();
    TL_FI const_iterator  end() const;
    TL_FI const_iterator  cend() const;

    TL_FI reverse_iterator        rbegin();
    TL_FI const_reverse_iterator  rbegin() const;
    TL_FI reverse_iterator        rend();
    TL_FI const_reverse_iterator  rend() const;

    //------------------------------------------------------------------------
    // Capacity

    TL_FI size_type   size() const;
    TL_FI bool        empty() const;
    TL_FI size_type   max_size() const;
    TL_FI void        resize(size_type aNumElements,
                             const value_type& aValue = value_type());

    //------------------------------------------------------------------------
    // Element Access

    TL_FI reference       front();
    TL_FI const_reference front() const;

    TL_FI reference       back();
    TL_FI const_reference back() const;

    //------------------------------------------------------------------------
    // Modifiers

    TL_FI void        assign(size_type aNumTimes, const T& aValueCopy);

    template <class T_InputItr>
    TL_FI void        assign(T_InputItr aRangeBegin, T_InputItr aRangeEnd);

    TL_FI void        push_front(const value_type& aVal);
    TL_FI reference   push_front();
    TL_FI pointer     push_front_uninitialized();

    TL_FI void        pop_front();

    TL_FI void        push_back(const value_type& aVal);
    TL_FI reference   push_back();
    TL_FI pointer     push_back_uninitialized();

    TL_FI void        pop_back();

    TL_FI iterator    insert(iterator aPos);
    TL_FI iterator    insert(iterator aPos, const value_type& aValue);
    TL_FI void        insert(iterator aPos, size_type aNumOfValues,
                             const value_type& aValue);
    template <typename T_Iterator>
    TL_FI void        insert(iterator aPos, T_Iterator aFirst,
                             T_Iterator aLast);

    TL_FI iterator    insert_after(iterator aPos);
    TL_FI iterator    insert_after(iterator aPos, const value_type& aValue);
    TL_FI void        insert_after(iterator aPos, size_type aNumOfValues,
                                   const value_type& aValue);
    template <typename T_Iterator>
    TL_FI void        insert_after(iterator aPos, T_Iterator aFirst,
                                   T_Iterator aLast);

    TL_FI iterator    erase(iterator aPos);
    TL_FI iterator    erase(iterator aFirst, iterator aLast);

    TL_FI reverse_iterator erase(reverse_iterator aPos);
    TL_FI reverse_iterator erase(reverse_iterator aFirst,
                                 reverse_iterator aLast);

    TL_FI iterator    erase_after(iterator aPos);
    TL_FI iterator    erase_after(iterator aFirst, iterator aLast);

    TL_FI reverse_iterator erase_after(reverse_iterator aPos);
    TL_FI reverse_iterator erase_after(reverse_iterator aFirst,
                                       reverse_iterator aLast);

    TL_FI void        swap(this_type& aOther);

    TL_FI void        clear();

    //------------------------------------------------------------------------
    // Operations

    TL_FI void        splice(iterator aPos, this_type& aFrom);
    TL_FI void        splice(iterator aPos, this_type& aFrom, iterator aOther);
    TL_FI void        splice(iterator aPos, this_type& aFrom, iterator aOtherBegin,
                             iterator aOtherEnd);

    TL_FI void        splice_after(iterator aPos, this_type& aFrom);
    TL_FI void        splice_after(iterator aPos, this_type& aFrom,
                                   iterator aOther);
    TL_FI void        splice_after(iterator aPos, this_type& aFrom,
                                   iterator aOtherBegin, iterator aOtherEnd);

    TL_FI void        remove(const T& aValueToCompare);

    template <typename T_Pred>
    TL_FI void        remove_if(T_Pred aFunctionToCompare);

    TL_FI void        unique();

    template <typename T_Pred>
    TL_FI void        unique(T_Pred aBinaryPred);

    TL_FI void        merge(this_type& aOther);

    template <typename T_Compare>
    TL_FI void        merge(this_type& aOther, T_Compare aComp);

    TL_FI void        sort();

    template <typename T_Compare>
    TL_FI void        sort(T_Compare aComp);

    TL_FI void        reverse();

  protected:
    typedef ConditionalType<size_type, true>  size_stored;
    typedef ConditionalType<size_type, false> size_not_stored;

    typedef type_true       is_arith;
    typedef type_false      is_not_arith;

    TL_FI void DoInit();
    TL_FI void DoClear();

    TL_FI node_type* DoAllocateNode();
    TL_FI void       DoFreeNode(node_type* aNode);

    TL_FI node_type* DoCreateNode();
    TL_FI node_type* DoCreateNode(const T& aValueCopy);

    template <typename T_Integer>
    TL_FI void       DoAssign(T_Integer aNumTimes, const T_Integer& aValueCopy,
                              is_arith);

    template <typename T_InputItr>
    TL_FI void       DoAssign(T_InputItr aRangeBegin, T_InputItr aRangeEnd,
                              is_not_arith);

    TL_FI void       DoAssignValues(size_type aNumTimes, const value_type& aValue);

    template <typename T_Integer>
    TL_FI void       DoInsertAfter(node_type* aPos, T_Integer aNumTimes,
                                   T_Integer aValueCopy, is_arith);

    template <typename T_InputIterator>
    TL_FI void       DoInsertAfter(node_type* aPos, T_InputIterator aFirst,
                                   T_InputIterator aLast, is_not_arith);

    TL_FI void       DoInsertValueAfter(node_type* aNode, const T& aValueCopy);
    TL_FI void       DoInsertValuesAfter(node_type* aNode,
                                         tl_size numElements,
                                         const T& aValueCopy);

    TL_FI void       DoEraseAfter(node_type* aNode);

    TL_FI size_type  DoGetSize(size_stored) const;
    TL_FI size_type  DoGetSize(size_not_stored) const;

    TL_FI void       DoResize(size_type aNumElements, const value_type& aValue,
                              size_stored);
    TL_FI void       DoResize(size_type aNumElements, const value_type& aValue,
                              size_not_stored);

    // This function performs the actual splice for a range. It selects the
    // most optimized splicing operation depending on whether the size is stored
    // or not
    TL_FI void       DoSpliceAfter(iterator aPos, this_type& aFrom,
                                   iterator aBegin, iterator aEnd, size_stored);
    TL_FI void       DoSpliceAfter(iterator aPos, this_type& aFrom,
                                   iterator aBegin, iterator aEnd,
                                   size_not_stored);

  protected:

    TL_FI node_type&          m_node();
    TL_FI const node_type&    m_node() const;
    TL_FI list_size&          m_size();
    TL_FI const list_size&    m_size() const;
    size_and_node             m_sizeAndNode;
  };


  //////////////////////////////////////////////////////////////////////////
  // Default types for easy instantiation

  template <typename T, bool T_DedicatedSize = true>
  struct SinglyList
  {
    DECL_TYPEDEF_HELPER(SinglyList);
    typedef List<T, ListNode<T, singly_linked_tag>, List_Dynamic(),
      T_DedicatedSize> type;
  };

  template <typename T, bool T_DedicatedSize = true>
  struct DoublyList
  {
    DECL_TYPEDEF_HELPER(DoublyList);
    typedef List<T, ListNode<T, doubly_linked_tag>, List_Dynamic(),
      T_DedicatedSize> type;
  };

};};};

#endif