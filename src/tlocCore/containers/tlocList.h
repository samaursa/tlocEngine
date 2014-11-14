#ifndef TLOC_LIST_H
#define TLOC_LIST_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
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
    typedef T*                              pointer;
    typedef const T*                        const_pointer;
    typedef T&                              reference;
    typedef const T&                        const_reference;
    typedef tl_ptrdiff                      difference_type;

    typedef singly_linked_tag               iterator_category;

    ListNode();
    ListNode(const this_type& aOther);

    void        init();
    static void swap(this_type& a, this_type& b);
    static void swap_after(this_type& a, this_type& b);
    void        insert_after(this_type* aNext);
    void        remove_after();
    void        splice_after(this_type* aFirst, this_type* aLast);
    void        reverse();

    this_type*           getNext();
    const this_type*     getNext() const;
    this_type*           getPrev();
    const this_type*     getPrev() const;
    reference            getValue();
    const_reference      getValue() const;

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
    typedef T*                              pointer;
    typedef const T*                        const_pointer;
    typedef T&                              reference;
    typedef const T&                        const_reference;
    typedef tl_ptrdiff                      difference_type;

    typedef doubly_linked_tag               iterator_category;

    ListNode();
    ListNode(const this_type& aOther);

    void        init();
    static void swap(this_type& a, this_type& b);
    static void swap_after(this_type& a, this_type& b);
    void        insert_after(this_type* aNext);
    void        remove_after();
    void        splice_after(this_type* aFirst, this_type* aLast);
    void        reverse();

    this_type*           getNext();
    const this_type*     getNext() const;
    this_type*           getPrev();
    const this_type*     getPrev() const;
    reference            getValue();
    const_reference      getValue() const;

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
    List();
    explicit List(size_type aNumTimes, const T& aValue = T());

    template <typename T_InputItr>
    List(T_InputItr aFirst, T_InputItr aLast);
    List(const this_type& aOther);

    ~List();

    this_type& operator= (const this_type& aOther);

    //------------------------------------------------------------------------
    // Iterator access

    iterator        begin();
    const_iterator  begin() const;
    const_iterator  cbegin() const;
    iterator        end();
    const_iterator  end() const;
    const_iterator  cend() const;

    reverse_iterator        rbegin();
    const_reverse_iterator  rbegin() const;
    reverse_iterator        rend();
    const_reverse_iterator  rend() const;

    //------------------------------------------------------------------------
    // Capacity

    size_type   size() const;
    bool        empty() const;
    size_type   max_size() const;
    void        resize(size_type aNumElements,
                             const value_type& aValue = value_type());

    //------------------------------------------------------------------------
    // Element Access

    reference       front();
    const_reference front() const;

    reference       back();
    const_reference back() const;

    //------------------------------------------------------------------------
    // Modifiers

    void        assign(size_type aNumTimes, const T& aValueCopy);

    template <class T_InputItr>
    void        assign(T_InputItr aRangeBegin, T_InputItr aRangeEnd);

    void        push_front(const value_type& aVal);
    reference   push_front();
    pointer     push_front_uninitialized();

    void        pop_front();

    void        push_back(const value_type& aVal);
    reference   push_back();
    pointer     push_back_uninitialized();

    void        pop_back();

    iterator    insert(iterator aPos);
    iterator    insert(iterator aPos, const value_type& aValue);
    void        insert(iterator aPos, size_type aNumOfValues,
                             const value_type& aValue);
    template <typename T_Iterator>
    void        insert(iterator aPos, T_Iterator aFirst,
                             T_Iterator aLast);

    iterator    insert_after(iterator aPos);
    iterator    insert_after(iterator aPos, const value_type& aValue);
    void        insert_after(iterator aPos, size_type aNumOfValues,
                                   const value_type& aValue);
    template <typename T_Iterator>
    void        insert_after(iterator aPos, T_Iterator aFirst,
                                   T_Iterator aLast);

    iterator    erase(iterator aPos);
    iterator    erase(iterator aFirst, iterator aLast);

    reverse_iterator erase(reverse_iterator aPos);
    reverse_iterator erase(reverse_iterator aFirst,
                                 reverse_iterator aLast);

    iterator    erase_after(iterator aPos);
    iterator    erase_after(iterator aFirst, iterator aLast);

    reverse_iterator erase_after(reverse_iterator aPos);
    reverse_iterator erase_after(reverse_iterator aFirst,
                                       reverse_iterator aLast);

    void        swap(this_type& aOther);

    void        clear();

    //------------------------------------------------------------------------
    // Operations

    void        splice(iterator aPos, this_type& aFrom);
    void        splice(iterator aPos, this_type& aFrom, iterator aOther);
    void        splice(iterator aPos, this_type& aFrom, iterator aOtherBegin,
                             iterator aOtherEnd);

    void        splice_after(iterator aPos, this_type& aFrom);
    void        splice_after(iterator aPos, this_type& aFrom,
                                   iterator aOther);
    void        splice_after(iterator aPos, this_type& aFrom,
                                   iterator aOtherBegin, iterator aOtherEnd);

    void        remove(const T& aValueToCompare);

    template <typename T_Pred>
    void        remove_if(T_Pred aFunctionToCompare);

    void        unique();

    template <typename T_Pred>
    void        unique(T_Pred aBinaryPred);

    void        merge(this_type& aOther);

    template <typename T_Compare>
    void        merge(this_type& aOther, T_Compare aComp);

    void        sort();

    template <typename T_Compare>
    void        sort(T_Compare aComp);

    void        reverse();

  protected:
    typedef ConditionalType<size_type, true>  size_stored;
    typedef ConditionalType<size_type, false> size_not_stored;

    typedef type_true       is_arith;
    typedef type_false      is_not_arith;

    void DoInit();
    void DoClear();

    node_type* DoAllocateNode();
    void       DoFreeNode(node_type* aNode);

    node_type* DoCreateNode();
    node_type* DoCreateNode(const T& aValueCopy);

    template <typename T_Integer>
    void       DoAssign(T_Integer aNumTimes, const T_Integer& aValueCopy,
                              is_arith);

    template <typename T_InputItr>
    void       DoAssign(T_InputItr aRangeBegin, T_InputItr aRangeEnd,
                              is_not_arith);

    void       DoAssignValues(size_type aNumTimes, const value_type& aValue);

    template <typename T_Integer>
    void       DoInsertAfter(node_type* aPos, T_Integer aNumTimes,
                                   T_Integer aValueCopy, is_arith);

    template <typename T_InputIterator>
    void       DoInsertAfter(node_type* aPos, T_InputIterator aFirst,
                                   T_InputIterator aLast, is_not_arith);

    void       DoInsertValueAfter(node_type* aNode, const T& aValueCopy);
    void       DoInsertValuesAfter(node_type* aNode,
                                         tl_size numElements,
                                         const T& aValueCopy);

    void       DoEraseAfter(node_type* aNode);

    size_type  DoGetSize(size_stored) const;
    size_type  DoGetSize(size_not_stored) const;

    void       DoResize(size_type aNumElements, const value_type& aValue,
                              size_stored);
    void       DoResize(size_type aNumElements, const value_type& aValue,
                              size_not_stored);

    // This function performs the actual splice for a range. It selects the
    // most optimized splicing operation depending on whether the size is stored
    // or not
    void       DoSpliceAfter(iterator aPos, this_type& aFrom,
                                   iterator aBegin, iterator aEnd, size_stored);
    void       DoSpliceAfter(iterator aPos, this_type& aFrom,
                                   iterator aBegin, iterator aEnd,
                                   size_not_stored);

  protected:

    node_type&          m_node();
    const node_type&    m_node() const;
    list_size&          m_size();
    const list_size&    m_size() const;
    size_and_node             m_sizeAndNode;
  };


  //////////////////////////////////////////////////////////////////////////
  // Default types for easy instantiation

  template <typename T, bool T_DedicatedSize = true>
  struct SinglyList : public utils::TypedefHelperBase<T>
  {
    typedef List<T, ListNode<T, singly_linked_tag>, List_Dynamic(),
      T_DedicatedSize> type;
  };

  template <typename T, bool T_DedicatedSize = true>
  struct DoublyList : public utils::TypedefHelperBase<T>
  {
      typedef List<T, ListNode<T, doubly_linked_tag>, List_Dynamic(),
      T_DedicatedSize> type;
  };

  // -----------------------------------------------------------------------
  // extern template

#define TLOC_EXTERN_TEMPLATE_LIST(_type_)\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_conts::List<_type_ TLOC_COMMA tloc::core_conts::ListNode<_type_ TLOC_COMMA tloc::core::doubly_linked_tag> >);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_conts::List<_type_ TLOC_COMMA tloc::core_conts::ListNode<_type_ TLOC_COMMA tloc::core::singly_linked_tag> >);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_conts::List<_type_ TLOC_COMMA tloc::core_conts::ListNode<_type_ TLOC_COMMA tloc::core::doubly_linked_tag> TLOC_COMMA tloc::core_conts::List_Dynamic TLOC_COMMA false>);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_conts::List<_type_ TLOC_COMMA tloc::core_conts::ListNode<_type_ TLOC_COMMA tloc::core::singly_linked_tag> TLOC_COMMA tloc::core_conts::List_Dynamic TLOC_COMMA false>)

  TLOC_EXTERN_TEMPLATE_LIST(s8);
  TLOC_EXTERN_TEMPLATE_LIST(s32);
  TLOC_EXTERN_TEMPLATE_LIST(s64);

  TLOC_EXTERN_TEMPLATE_LIST(u8);
  TLOC_EXTERN_TEMPLATE_LIST(u32);
  TLOC_EXTERN_TEMPLATE_LIST(u64);

  TLOC_EXTERN_TEMPLATE_LIST(f32);
  TLOC_EXTERN_TEMPLATE_LIST(f64);

};};};

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // swap

  template <typename T, typename T_Node, typename T_Policy, 
            bool T_DedicatedSize>
  void swap(core_conts::List<T, T_Node, T_Policy, T_DedicatedSize>& a,
            core_conts::List<T, T_Node, T_Policy, T_DedicatedSize>& b)
  { a.swap(b); }

};};

#endif