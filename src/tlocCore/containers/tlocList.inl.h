#ifndef TLOC_LIST_INL
#define TLOC_LIST_INL

#ifndef TLOC_LIST_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/iterators/tlocIterator.inl.h>
#include <tlocCore/utilities/tlocType.h>

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_ASSERT_LIST_NOT_EMPTY() \
  TLOC_ASSERT_LIST(!empty(), "List container is empty!")

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define LIST_NODE_TYPES typename T
#define DOUBLY_LIST_NODE_PARAMS T, doubly_linked_tag
#define SINGLY_LIST_NODE_PARAMS T, singly_linked_tag

  //////////////////////////////////////////////////////////////////////////
  // ListNode (singly_linked)

  template <LIST_NODE_TYPES>
  TL_FI ListNode<SINGLY_LIST_NODE_PARAMS>::ListNode()
  {
  }

  template <LIST_NODE_TYPES>
  TL_FI ListNode<SINGLY_LIST_NODE_PARAMS>
    ::ListNode(const ListNode<SINGLY_LIST_NODE_PARAMS>& aOther)
  {
    m_next = aOther.m_next;
    m_value = aOther.m_value;
  }

  template <LIST_NODE_TYPES>
  TL_FI void ListNode<SINGLY_LIST_NODE_PARAMS>
    ::init()
  {
    // We use this node as the terminating node because when the user queries
    // the 'end' iterator, we need to return a valid iterator object
    m_next = this;
  }

  template <LIST_NODE_TYPES>
  TL_FI void ListNode<SINGLY_LIST_NODE_PARAMS>
    ::swap_after(ListNode<SINGLY_LIST_NODE_PARAMS>& a,
                 ListNode<SINGLY_LIST_NODE_PARAMS>& b)
  {
    TLOC_ASSERT_WIP();
  }

  template <LIST_NODE_TYPES>
  TL_FI void ListNode<SINGLY_LIST_NODE_PARAMS>
    ::swap(ListNode<SINGLY_LIST_NODE_PARAMS>& a,
           ListNode<SINGLY_LIST_NODE_PARAMS>& b)
  {
    // Costly operation for a singly linked list because we have to get the
    // previous node of each of the above

    if (a.m_next != &b && b.m_next != &a)
    {
      this_type* prev_a = a.getPrev();
      this_type* prev_b = b.getPrev();

      prev_a->m_next = &b;
      prev_b->m_next = &a;
    }
    else
    {
      if (a.m_next == &b)
      {
        this_type* prev_a = a.getPrev();
        prev_a->m_next = &b;
        a.m_next = &a;
      }
      else
      {
        this_type* prev_b = b.getPrev();
        prev_b->m_next = &a;
        b.m_next = &b;
      }
    }

    const this_type temp(a);
    a = b;
    b = temp;
  }

  template <LIST_NODE_TYPES>
  void ListNode<SINGLY_LIST_NODE_PARAMS>
    ::insert_after(ListNode<SINGLY_LIST_NODE_PARAMS>* aNext)
  {
    m_next = aNext->m_next;
    aNext->m_next = this;
  }

  template <LIST_NODE_TYPES>
  void ListNode<SINGLY_LIST_NODE_PARAMS>::remove_after()
  {
    m_next = m_next->m_next;
  }

  template <LIST_NODE_TYPES>
  void ListNode<SINGLY_LIST_NODE_PARAMS>
    ::splice_after(ListNode<SINGLY_LIST_NODE_PARAMS>* aFirst,
                   ListNode<SINGLY_LIST_NODE_PARAMS>* aLast)
  {
    // Not the most efficient implementation as it requires iteration. Find a
    // way to do it without iterating the other list

#ifndef TLOC_DISABLE_EXTENDED_SINGLY_LIST
    this_type* beforeFirst = aFirst->getPrev();
    this_type* beforeLast  = aLast->getPrev();
#else
    this_type* beforeFirst = aFirst;
    this_type* beforeLast  = aLast;

    while(beforeFirst->m_next != aFirst) { beforeFirst = beforeFirst->m_next; }
    while(beforeLast->m_next != aLast) { beforeLast = beforeLast->m_next; }
#endif

    beforeFirst->m_next = aLast; // For the foreign list

    beforeLast->m_next = m_next;
    m_next = aFirst;
  }

  template <LIST_NODE_TYPES>
  void ListNode<SINGLY_LIST_NODE_PARAMS>::reverse()
  {
    this_type* node = this;
    this_type* nextNode = node->m_next;
    do
    {
      this_type* temp = nextNode->m_next;
      nextNode->m_next = node;
      node = nextNode;
      nextNode = temp;

    } while (node != this);
  }

  template <LIST_NODE_TYPES>
  typename ListNode<SINGLY_LIST_NODE_PARAMS>::this_type*
    ListNode<SINGLY_LIST_NODE_PARAMS>::getNext()
  {
    return m_next;
  }

  template <LIST_NODE_TYPES>
  const typename ListNode<SINGLY_LIST_NODE_PARAMS>::this_type*
    ListNode<SINGLY_LIST_NODE_PARAMS>::getNext() const
  {
    return m_next;
  }

  template <LIST_NODE_TYPES>
  typename ListNode<SINGLY_LIST_NODE_PARAMS>::this_type*
    ListNode<SINGLY_LIST_NODE_PARAMS>::getPrev()
  {
#ifdef TLOC_DISABLE_EXTENDED_SINGLY_LIST
    TLOC_STATIC_ASSERT(false, Singly_linked_node_extended_operations_disabled!);
#endif

    this_type* temp = this;
    while (temp->m_next != this)
    {
      temp = temp->m_next;
    }

    return temp;
  }

  template <LIST_NODE_TYPES>
  const typename ListNode<SINGLY_LIST_NODE_PARAMS>::this_type*
    ListNode<SINGLY_LIST_NODE_PARAMS>::getPrev() const
  {
#ifdef TLOC_DISABLE_EXTENDED_SINGLY_LIST
    TLOC_STATIC_ASSERT(false, Singly_linked_node_extended_operations_disabled!);
#endif

    const this_type* temp = this;
    while (temp->m_next != this)
    {
      temp = temp->m_next;
    }

    return temp;
  }

  template <LIST_NODE_TYPES>
  typename ListNode<SINGLY_LIST_NODE_PARAMS>::reference
    ListNode<SINGLY_LIST_NODE_PARAMS>::getValue()
  {
    return m_value;
  }

  template <LIST_NODE_TYPES>
  typename ListNode<SINGLY_LIST_NODE_PARAMS>::const_reference
    ListNode<SINGLY_LIST_NODE_PARAMS>::getValue() const
  {
    return m_value;
  }

  //////////////////////////////////////////////////////////////////////////
  // ListNode (doubly_linked)

  template <LIST_NODE_TYPES>
  TL_FI ListNode<DOUBLY_LIST_NODE_PARAMS>::ListNode()
  {
  }

  template <LIST_NODE_TYPES>
  TL_FI ListNode<DOUBLY_LIST_NODE_PARAMS>
    ::ListNode(const ListNode<DOUBLY_LIST_NODE_PARAMS>& aOther)
  {
    m_next = aOther.m_next;
    m_prev = aOther.m_prev;
    m_value = aOther.m_value;
  }

  template <LIST_NODE_TYPES>
  TL_FI void ListNode<DOUBLY_LIST_NODE_PARAMS>
    ::init()
  {
    // We use this node as the terminating node because when the user queries
    // the 'end' iterator, we need to return a valid iterator object
    m_next = this;
    m_prev = this;
  }

  template <LIST_NODE_TYPES>
  TL_FI void ListNode<DOUBLY_LIST_NODE_PARAMS>
    ::swap(ListNode<DOUBLY_LIST_NODE_PARAMS>& a,
           ListNode<DOUBLY_LIST_NODE_PARAMS>& b)
  {
    if (a.m_next != &b && b.m_next != &a)
    {
      a.m_prev->m_next = &b;
      a.m_next->m_prev = &b;

      b.m_prev->m_next = &a;
      b.m_next->m_prev = &a;
    }
    else
    {
      if (a.m_next == &b)
      {
        a.m_prev->m_next = &b;
        a.m_next = &a;
        b.m_next->m_prev = &a;
        b.m_prev = &b;
      }
      else
      {
        b.m_prev->m_next = &a;
        b.m_next = &b;
        a.m_next->m_prev = &b;
        a.m_prev = &a;
      }
    }

    const this_type temp(a);
    a = b;
    b = temp;
  }

  template <LIST_NODE_TYPES>
  TL_FI void ListNode<DOUBLY_LIST_NODE_PARAMS>
    ::swap_after(ListNode<DOUBLY_LIST_NODE_PARAMS>& a,
                 ListNode<DOUBLY_LIST_NODE_PARAMS>& b)
  {
    TLOC_ASSERT_WIP();
  }

  template <LIST_NODE_TYPES>
  void ListNode<DOUBLY_LIST_NODE_PARAMS>
    ::insert_after(ListNode<DOUBLY_LIST_NODE_PARAMS>* aNext)
  {
    m_next = aNext->m_next;
    m_prev = aNext;
    aNext->m_next->m_prev = this;
    aNext->m_next = this;
  }

  template <LIST_NODE_TYPES>
  void ListNode<DOUBLY_LIST_NODE_PARAMS>::remove_after()
  {
    this_type* nodeAfter = m_next;
    m_next = nodeAfter->m_next;
    nodeAfter->m_next->m_prev = this;
  }

  template <LIST_NODE_TYPES>
  void ListNode<DOUBLY_LIST_NODE_PARAMS>
    ::splice_after(ListNode<DOUBLY_LIST_NODE_PARAMS>* aFirst,
                   ListNode<DOUBLY_LIST_NODE_PARAMS>* aLast)
  {
    aFirst->m_prev->m_next = aLast; // For the foreign list

    aLast->m_prev->m_next = m_next;
    m_next->m_prev = aLast->m_prev;
    m_next = aFirst;

    aLast->m_prev = aFirst->m_prev; // For the foreign list

    aFirst->m_prev = this;
  }

  template <LIST_NODE_TYPES>
  void ListNode<DOUBLY_LIST_NODE_PARAMS>::reverse()
  {
    this_type* node = this;
    do
    {
      this_type* const temp = node->m_next;
      node->m_next = node->m_prev;
      node->m_prev = temp;
      node         = node->m_prev;
    } while (node != this);
  }

  template <LIST_NODE_TYPES>
  typename ListNode<DOUBLY_LIST_NODE_PARAMS>::this_type*
    ListNode<DOUBLY_LIST_NODE_PARAMS>::getNext()
  {
    return m_next;
  }

  template <LIST_NODE_TYPES>
  const typename ListNode<DOUBLY_LIST_NODE_PARAMS>::this_type*
    ListNode<DOUBLY_LIST_NODE_PARAMS>::getNext() const
  {
    return m_next;
  }

  template <LIST_NODE_TYPES>
  typename ListNode<DOUBLY_LIST_NODE_PARAMS>::this_type*
    ListNode<DOUBLY_LIST_NODE_PARAMS>::getPrev()
  {
    return m_prev;
  }

  template <LIST_NODE_TYPES>
  const typename ListNode<DOUBLY_LIST_NODE_PARAMS>::this_type*
    ListNode<DOUBLY_LIST_NODE_PARAMS>::getPrev() const
  {
    return m_prev;
  }

  template <LIST_NODE_TYPES>
  typename ListNode<DOUBLY_LIST_NODE_PARAMS>::reference
    ListNode<DOUBLY_LIST_NODE_PARAMS>::getValue()
  {
    return m_value;
  }

  template <LIST_NODE_TYPES>
  typename ListNode<DOUBLY_LIST_NODE_PARAMS>::const_reference
    ListNode<DOUBLY_LIST_NODE_PARAMS>::getValue() const
  {
    return m_value;
  }

  //////////////////////////////////////////////////////////////////////////
  // Macros

#define LIST_TEMP_TYPES typename T, typename T_Node, typename T_Policy, \
  bool T_DedicatedSize
#define LIST_TEMP T, T_Node, T_Policy, T_DedicatedSize

  //------------------------------------------------------------------------
  // Ctors / Dtors

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP >::List() : m_sizeAndNode()
  {
    DoInit();
  }

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP>::List(size_type aNumTimes, const T& aValue)
    : m_sizeAndNode()
  {
    DoInit();
    DoInsertValuesAfter(&m_node(), aNumTimes, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputItr>
  TL_FI List<LIST_TEMP>::List(T_InputItr aFirst, T_InputItr aLast)
    : m_sizeAndNode()
  {
    DoInit();
    insert(&m_node(), aFirst, aLast);
  }

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP>::List(const this_type& aOther) : m_sizeAndNode()
  {
    DoInit();
    DoInsertAfter(&m_node(), aOther.begin(), aOther.end(), is_not_arith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP >::~List()
  {
    DoClear();

    // Delete the sentry node
    delete m_sizeAndNode.m_var;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::this_type&
    List<LIST_TEMP>::operator= (const typename List<LIST_TEMP>::this_type& aOther)
  {
    TLOC_ASSERT_LIST(this != &aOther, "Assigning list to itself!");

    assign(aOther.begin(), aOther.end());
    return *this;
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::begin()
  {
    return iterator(m_node().getNext());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_iterator List<LIST_TEMP>::begin() const
  {
    return const_iterator(m_node().getNext());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_iterator List<LIST_TEMP>::cbegin() const
  {
    return begin();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::end()
  {
    return iterator(&m_node());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_iterator List<LIST_TEMP>::end() const
  {
    return const_iterator(&m_node());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_iterator List<LIST_TEMP>::cend() const
  {
    return end();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator List<LIST_TEMP>::rbegin()
  {
    return reverse_iterator(&m_node());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reverse_iterator
    List<LIST_TEMP>::rbegin() const
  {
    return const_reverse_iterator(&m_node());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator List<LIST_TEMP>::rend()
  {
    return reverse_iterator(m_node().getNext());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reverse_iterator
    List<LIST_TEMP>::rend() const
  {
    return const_reverse_iterator(m_node().getNext());
  }

  //------------------------------------------------------------------------
  // Capacity

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type List<LIST_TEMP>::size() const
  {
    return DoGetSize(list_size());
  }

  template <LIST_TEMP_TYPES>
  TL_FI bool List<LIST_TEMP>::empty() const
  {
    return &m_node()== m_node().getNext();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type
    List<LIST_TEMP>::max_size() const
  {
    return TL_UINT_MAX;
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::resize(size_type aNumElements,
                                     const value_type& aValue/* = value_type */)
  {
    // Since we can have lists that have a dedicated size variable and lists
    // that do not, we call different functions to avoid traversing the list
    // if possible (in case that size is stored)

    DoResize(aNumElements, aValue, list_size());
  }

  //------------------------------------------------------------------------
  // Elements Access

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference
    List<LIST_TEMP>::front()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node().getNext()->getValue();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reference
    List<LIST_TEMP>::front() const
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node().getNext()->getValue();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference
    List<LIST_TEMP>::back()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node().getPrev()->getValue();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reference
    List<LIST_TEMP>::back() const
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node().getPrev()->getValue();
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::assign(size_type aNumTimes, const T& aValueCopy)
  {
    DoAssignValues(aNumTimes, aValueCopy);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputItr>
  TL_FI void List<LIST_TEMP>::assign(T_InputItr aRangeBegin, T_InputItr aRangeEnd)
  {
    typedef typename Loki::TypeTraits<T_InputItr> inputUnknown;
    typedef typename Loki::Int2Type<inputUnknown::isArith> inputArith;

    DoAssign(aRangeBegin, aRangeEnd, inputArith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::push_front(const value_type& aVal)
  {
    DoInsertValueAfter(&m_node(), aVal);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference List<LIST_TEMP>::push_front()
  {
    node_type* const node = DoCreateNode();
    node->insert_after(&m_node());
    ++m_size();
    return m_node().getNext()->getValue();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::pointer
    List<LIST_TEMP>::push_front_uninitialized()
  {
    node_type* const node = DoAllocateNode();
    node->insert_after(&m_node());
    ++m_size();
    return &(node->getValue());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::push_back(const value_type& aVal)
  {
    DoInsertValueAfter(m_node().getPrev(), aVal);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference List<LIST_TEMP>::push_back()
  {
    node_type* const node = DoCreateNode();
    node->insert_after(m_node().getPrev());
    ++m_size();
    return m_node().getPrev()->getValue();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::pointer
    List<LIST_TEMP>::push_back_uninitialized()
  {
    node_type* const node = DoAllocateNode();
    node->insert_after(&m_node());
    ++m_size();
    return &(node->getValue());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::pop_back()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    DoEraseAfter(m_node().getPrev()->getPrev());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::pop_front()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    DoEraseAfter(&m_node());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::insert(iterator aPos)
  {
    node_type* const node = DoCreateNode(value_type());
    node->insert_after(aPos.m_node->getPrev());
    ++m_size();
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::insert(iterator aPos, const value_type& aValue)
  {
    node_type* const node = DoCreateNode(aValue);
    node->insert_after(aPos.m_node->getPrev());
    ++m_size();
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::insert(iterator aPos, size_type aNumOfValues,
                                     const value_type& aValue)
  {
    DoInsertValuesAfter(aPos.m_node->getPrev(),
                        aNumOfValues, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Iterator>
  TL_FI void List<LIST_TEMP>::insert(iterator aPos, T_Iterator aFirst,
                                     T_Iterator aLast)
  {
    typedef typename Loki::TypeTraits<T_Iterator> inputUnknown;
    typedef typename Loki::Int2Type<inputUnknown::isArith> inputArith;

    DoInsertAfter(aPos.m_node->getPrev(), aFirst, aLast,
                  inputArith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::insert_after(iterator aPos)
  {
    node_type* const node = DoCreateNode(value_type());
    node->insert_after(aPos.m_node);
    ++m_size();
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::insert_after(iterator aPos, const value_type& aValue)
  {
    node_type* const node = DoCreateNode(aValue);
    node->insert_after(aPos.m_node);
    ++m_size();
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::insert_after(iterator aPos, size_type aNumOfValues,
                                           const value_type& aValue)
  {
    DoInsertValuesAfter(aPos.m_node, aNumOfValues, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Iterator>
  TL_FI void List<LIST_TEMP>::insert_after(iterator aPos, T_Iterator aFirst,
                                           T_Iterator aLast)
  {
    typedef typename Loki::TypeTraits<T_Iterator> inputUnknown;
    typedef typename Loki::Int2Type<inputUnknown::isArith> inputArith;

    DoInsertAfter(aPos.m_node, aFirst, aLast, inputArith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::erase(iterator aPos)
  {
    iterator itrToDel = aPos;
    ++aPos;
    DoEraseAfter(itrToDel.m_node->getPrev());
    return aPos;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::erase(iterator aFirst, iterator aLast)
  {
    while(aFirst != aLast)
    {
      aFirst = erase(aFirst);
    }
    return aLast;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator
    List<LIST_TEMP>::erase(reverse_iterator aPos)
  {
    ++aPos;
    return reverse_iterator( erase(aPos.base()) );
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator
    List<LIST_TEMP>::erase(reverse_iterator aFirst, reverse_iterator aLast)
  {
    ++aFirst;
    ++aLast;
    return reverse_iterator( erase(aLast.base(), aFirst.base()) );
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::erase_after(iterator aPos)
  {
    DoEraseAfter(aPos.m_node);
    return ++aPos;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::erase_after(iterator aFirst, iterator aLast)
  {
    while(aFirst.m_node->getNext() != aLast.m_node)
    {
      erase_after(aFirst);
    }
    return aLast;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator
    List<LIST_TEMP>::erase_after(reverse_iterator aPos)
  {
    ++aPos;
    return reverse_iterator( erase_after(aPos.base()) );
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator
    List<LIST_TEMP>::erase_after(reverse_iterator aFirst, reverse_iterator aLast)
  {
    ++aFirst;
    ++aLast;
    return reverse_iterator( erase_after(aLast.base(), aFirst.base()) );
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::swap(this_type& aOther)
  {
    // We swap the pointers rather than the node that the pointer is pointing
    // to. This is a much faster O(1) operation on a singly linked list whereas
    // a node swap is an O(n) operation
    core::swap(m_sizeAndNode.m_var, aOther.m_sizeAndNode.m_var);
    core::swap(m_size(), aOther.m_size());

    //node_type::swap(m_node(), aOther.m_node());
    //core::swap(m_size(), aOther.m_size());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::clear()
  {
    DoClear();
    DoInit();
    m_size() = 0;
  }

  //------------------------------------------------------------------------
  // Operations

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice(iterator aPos, this_type& aFrom)
  {
    TLOC_ASSERT_LIST(&aFrom != this,
      "Cannot call this version of splice on itself");
    if (!aFrom.empty())
    {
      DoSpliceAfter(--aPos, aFrom, aFrom.begin(), aFrom.end(), list_size());
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice(iterator aPos, this_type& aFrom,
                                     iterator aOther)
  {
    iterator itr(aOther);
    ++itr;

    TLOC_ASSERT_LIST( aPos != aOther,
      "Cannot perform splice at the position itself!");
    TLOC_ASSERT_LIST( aPos != itr, "Cannot perform splice at (position + 1)!");

    aPos.m_node->getPrev()->
      splice_after(aOther.m_node, itr.m_node);
    ++m_size();
    --aFrom.m_size();

  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice(iterator aPos, this_type& aFrom,
                                     iterator aOtherBegin, iterator aOtherEnd)
  {
    DoSpliceAfter(--aPos, aFrom, aOtherBegin, aOtherEnd, list_size());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice_after(iterator aPos, this_type& aFrom)
  {
    TLOC_ASSERT_LIST(&aFrom != this,
      "Cannot call this version of splice on itself");
    if (!aFrom.empty())
    {
      DoSpliceAfter(aPos, aFrom, aFrom.begin(), aFrom.end(), list_size());
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice_after(iterator aPos, this_type& aFrom,
                                           iterator aOther)
  {
    iterator itr(aOther);
    ++itr;

    TLOC_ASSERT_LIST( aPos != aOther,
      "Cannot perform splice at the position itself!");
    TLOC_ASSERT_LIST( aPos != itr, "Cannot perform splice at (position + 1)!");

    aPos.m_node->splice_after(aOther.m_node, itr.m_node);
    ++m_size();
    --aFrom.m_size();

  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice_after(iterator aPos, this_type& aFrom,
                                           iterator aOtherBegin,
                                           iterator aOtherEnd)
  {
    // According to the standard, the splice begins AFTER aOtherBegin, i.e.
    // aOtherBegin is NOT going to be a part of this list

    DoSpliceAfter(aPos, aFrom, ++aOtherBegin, aOtherEnd, list_size());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::remove(const T& aValueToCompare)
  {
    iterator itr(&m_node());
    while (itr.m_node->getNext() != &m_node())
    {
      if (itr.m_node->getNext()->getValue() != aValueToCompare)
      {
        ++itr;
      }
      else
      {
        DoEraseAfter(itr.m_node);
      }
    }
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Pred>
  TL_FI void List<LIST_TEMP>::remove_if(T_Pred aFunctionToCompare)
  {
    iterator itr(&m_node());
    while (itr.m_node->getNext() != &m_node())
    {
      if (!aFunctionToCompare( itr.m_node->getNext()->getValue()))
      {
        ++itr;
      }
      else
      {
        DoEraseAfter(itr.m_node);
      }
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::unique()
  {
    iterator        itrBegin(begin());
    const iterator  itrEnd(end());

    // Make sure there is atleast one element
    if (itrBegin != itrEnd)
    {
      iterator currElem(itrBegin);

      while(++itrBegin != itrEnd)
      {
        if (*itrBegin == *currElem)
        {
          DoEraseAfter(itrBegin.m_node->getPrev());
          itrBegin = currElem;
        }
        else
        {
          currElem = itrBegin;
        }
      }
    }
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Pred>
  TL_FI void List<LIST_TEMP>::unique(T_Pred aBinaryPred)
  {
    iterator        itrBegin(begin());
    const iterator  itrEnd(end());

    // Make sure there is atleast one element
    if (itrBegin != itrEnd)
    {
      iterator currElem(itrBegin);

      while(++itrBegin != itrEnd)
      {
        if (aBinaryPred(*currElem, *itrBegin))
        {
          DoEraseAfter(itrBegin.m_node->getPrev());
          itrBegin = currElem;
        }
        else
        {
          currElem = itrBegin;
        }
      }
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::merge(this_type& aOther)
  {
    TLOC_ASSERT_LIST(this != &aOther, "Cannot merge List<> with itself!");

    iterator itr(begin());
    iterator itrEnd(end());
    iterator itrOther(aOther.begin());
    iterator itrOtherEnd(aOther.end());

    while ( (itr != itrEnd) && (itrOther != itrOtherEnd) )
    {
      if (*itrOther < *itr)
      {
        iterator itrOtherNext(itrOther);

        splice(itr, aOther, itrOther, ++itrOtherNext);
        itrOther = itrOtherNext; //itrOther is invalid unless we do this
      }
      else
      {
        ++itr;
      }
    }

    // If we have not exhausted the other list, then insert the remaining
    // elements
    if (itrOther != itrOtherEnd)
    {
      insert(itrEnd, itrOther, itrOtherEnd);
    }
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Compare>
  TL_FI void List<LIST_TEMP>::merge(this_type& aOther, T_Compare aComp)
  {
    TLOC_ASSERT_LIST(this != &aOther, "Cannot merge List<> with itself!");

    iterator itr(begin());
    iterator itrEnd(end());
    iterator itrOther(aOther.begin());
    iterator itrOtherEnd(aOther.end());

    while ( (itr != itrEnd) && (itrOther != itrOtherEnd) )
    {
      if ( aComp(*itrOther, *itr) )
      {
        iterator itrOtherNext(itrOther);

        splice(itr, aOther, itrOther, ++itrOtherNext);
        itrOther = itrOtherNext; //itrOther is invalid unless we do this
      }
      else
      {
        ++itr;
      }
    }

    // If we have not exhausted the other list, then insert the remaining
    // elements
    if (itrOther != itrOtherEnd)
    {
      insert(itrEnd, itrOther, itrOtherEnd);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::sort()
  {
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Compare>
  TL_FI void List<LIST_TEMP>::sort(T_Compare aComp)
  {
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::reverse()
  {
    m_node().reverse();
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP >::DoInit()
  {
    // We need to new our sentry node
    m_sizeAndNode.m_var = new node_type();

    m_size() = 0;
    m_node().init();
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP >::DoClear()
  {
    node_type* node = m_node().getNext();

    while (node != &m_node())
    {
      node_type* tempNode = node;
      node = node->getNext();

      tempNode->~node_type();
      TL_FREE(tempNode);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::node_type*
    List<LIST_TEMP>::DoAllocateNode()
  {
   return (node_type*)TL_MALLOC(sizeof(node_type));
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoFreeNode(node_type* aNode)
  {
    TL_FREE(aNode);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::node_type*
    List<LIST_TEMP>::DoCreateNode()
  {
    node_type* node = DoAllocateNode();

    TLOC_ASSERT_LIST(node, "Unable to allocate memory for the list node!");

    new(&node->getValue()) value_type;
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::node_type*
    List<LIST_TEMP>::DoCreateNode(const T& aValueCopy)
  {
    node_type* node = DoAllocateNode();
    new(&node->getValue()) value_type(aValueCopy);
    return node;
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Integer>
  TL_FI void List<LIST_TEMP>::DoAssign(T_Integer aNumTimes,
                                       const T_Integer& aValueCopy, is_arith)
  {
    DoAssignValues(static_cast<size_type>(aNumTimes),
                   core_utils::CastNumber<value_type>(aValueCopy));
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputItr>
  TL_FI void List<LIST_TEMP>::DoAssign(T_InputItr aRangeBegin,
                                       T_InputItr aRangeEnd, is_not_arith)
  {
    node_type* node = m_node().getNext();

    // Fill as much as we can
    while ( (aRangeBegin != aRangeEnd) && (node != &m_node()) )
    {
      node->getValue() = *aRangeBegin;
      node = node->getNext();
      ++aRangeBegin;
    }

    // Deal with over/under flow
    if (aRangeBegin != aRangeEnd)
    {
      DoInsertAfter(m_node().getPrev(), aRangeBegin, aRangeEnd,
                    is_not_arith());
    }
    else
    {
      erase(iterator(node), &m_node());
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoAssignValues(size_type aNumTimes,
                                             const value_type& aValueCopy)
  {
    node_type* node = m_node().getNext();

    // Fill as much as we can
    while ((node != &m_node()) && (aNumTimes > 0))
    {
      node->getValue() = aValueCopy;
      node = node->getNext();
      --aNumTimes;
    }

    // Deal with over/under flow
    if (aNumTimes > 0)
    {
      DoInsertValuesAfter(m_node().getPrev(), aNumTimes,
                          aValueCopy);
    }
    else
    {
      erase(iterator(node), &m_node());
    }
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Integer>
  TL_FI void List<LIST_TEMP>::DoInsertAfter(node_type* aPos, T_Integer aNumTimes,
                                            T_Integer aValue, is_arith)
  {
    DoInsertValuesAfter(aPos, aNumTimes, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputIterator>
  TL_FI void List<LIST_TEMP>::DoInsertAfter(node_type* aPos,
    T_InputIterator aFirst, T_InputIterator aLast, is_not_arith)
  {
    while (aFirst != aLast)
    {
      DoInsertValueAfter(aPos, *aFirst);
      aPos = aPos->getNext();
      ++aFirst;
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoInsertValueAfter(node_type* aNode,
                                                 const T& aValueCopy)
  {
    node_type* const newNode = DoCreateNode(aValueCopy);
    newNode->insert_after(aNode);
    ++m_size();
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoInsertValuesAfter(node_type* aNode,
                                                  tl_size numElements,
                                                  const T& aValueCopy)
  {
    for (; numElements > 0; --numElements)
    {
      DoInsertValueAfter(aNode, aValueCopy);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoEraseAfter(node_type* aNode)
  {
    node_type* nodeAfter = aNode->getNext();
    aNode->remove_after();
    nodeAfter->~node_type();
    DoFreeNode(nodeAfter);
    --m_size();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type
    List<LIST_TEMP>::DoGetSize(size_stored) const
  {
    return m_size().Value();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type
    List<LIST_TEMP>::DoGetSize(size_not_stored) const
  {
    return distance(const_iterator(m_node().getNext()),
                    const_iterator(&m_node()));
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoResize (size_type aNumElements,
                                        const value_type& aValue, size_stored)
  {
    // Assuming the user would usually want to grow the list when calling resize
    if (aNumElements > m_size())
    {
      insert(&m_node(), aNumElements - size(), aValue);
    }
    else
    {
      iterator itr(m_node().getNext());
      advance(itr, aNumElements);
      erase(itr, &m_node());
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoResize (size_type aNumElements,
                                        const value_type& aValue,
                                        size_not_stored)
  {
    iterator itr(m_node().getNext());
    size_type count = 0;

    while ( (itr.m_node != &m_node()) &&
            (count < aNumElements) )
    {
      ++count; ++itr;
    }

    if (count == aNumElements)
    {
      erase(itr, &m_node());
    }
    else
    {
      insert(&m_node(), aNumElements - count, aValue);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoSpliceAfter (iterator aPos, this_type& aFrom,
                                             iterator aBegin, iterator aEnd,
                                             size_stored)
  {
    TLOC_UNUSED(aPos);
    TLOC_UNUSED(aFrom);
    TLOC_UNUSED(aBegin);
    TLOC_UNUSED(aEnd);

    const size_type addedSize = distance(aBegin, aEnd);
    if (addedSize != 0)
    {
      aPos.m_node->splice_after(aBegin.m_node, aEnd.m_node);

      m_size()       += addedSize;
      aFrom.m_size() -= addedSize;
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoSpliceAfter (iterator aPos, this_type& aFrom,
                                             iterator aBegin, iterator aEnd,
                                             size_not_stored)
  {
    TLOC_UNUSED(aFrom);

    if (aBegin != aEnd)
    {
      aPos.m_node->splice_after(aBegin.m_node, aEnd.m_node);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Helper functions for m_sizeAndNode

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::node_type&
    List<LIST_TEMP>::m_node()
  {
    return *(m_sizeAndNode.m_var);
  }

  template <LIST_TEMP_TYPES>
  TL_FI const typename List<LIST_TEMP>::node_type&
    List<LIST_TEMP>::m_node() const
  {
    return *(m_sizeAndNode.m_var);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::list_size&
    List<LIST_TEMP>::m_size()
  {
    return (list_size&)m_sizeAndNode;
  }

  template <LIST_TEMP_TYPES>
  TL_FI const typename List<LIST_TEMP>::list_size&
    List<LIST_TEMP>::m_size() const
  {
    return (list_size&)m_sizeAndNode;
  }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_LIST(_type_)\
  template class tloc::core_conts::List<_type_, tloc::core_conts::ListNode<_type_, tloc::core::doubly_linked_tag> >;\
  template class tloc::core_conts::List<_type_, tloc::core_conts::ListNode<_type_, tloc::core::singly_linked_tag> >;\
  template class tloc::core_conts::List<_type_, tloc::core_conts::ListNode<_type_, tloc::core::doubly_linked_tag>, tloc::core_conts::List_Dynamic, false>;\
  template class tloc::core_conts::List<_type_, tloc::core_conts::ListNode<_type_, tloc::core::singly_linked_tag>, tloc::core_conts::List_Dynamic, false>

#endif
