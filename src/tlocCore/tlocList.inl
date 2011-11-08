#include "tlocList.h"
#include "tlocAlgorithms.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_ASSERT_LIST_NOT_EMPTY() \
  TLOC_ASSERT_LIST(!empty(), "List container is empty!")

  //////////////////////////////////////////////////////////////////////////
  // ListNode

  template <typename T>
  TL_FI ListNode<T, doubly_linked_tag>::ListNode()
  {
  }

  template <typename T>
  TL_FI ListNode<T, doubly_linked_tag>
    ::ListNode(const ListNode<T, doubly_linked_tag>& aOther)
  {
    m_next = aOther.m_next;
    m_prev = aOther.m_prev;
    m_value = aOther.m_value;
  }

  template <typename T>
  TL_FI void ListNode<T, doubly_linked_tag>
    ::swap(ListNode<T, doubly_linked_tag>& a, ListNode<T, doubly_linked_tag>& b)
  {
    TLOC_UNUSED(a);
    TLOC_UNUSED(b);
    TLOC_ASSERT_WIP();
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>
    ::insert(ListNode<T, doubly_linked_tag>* aNext)
  {
    m_next = aNext;
    m_prev = aNext->m_prev;
    aNext->m_prev->m_next = this;
    aNext->m_prev = this;
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>::remove()
  {
    m_prev->m_next = m_next;
    m_next->m_prev = m_prev;
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>
    ::splice(ListNode<T, doubly_linked_tag>* aFirst,
             ListNode<T, doubly_linked_tag>* aLast)
  {
    aLast->m_prev->m_next = this;
    aFirst->m_prev->m_next = aLast;
    m_prev->m_next = aFirst;

    this_type* const temp = m_prev;
    m_prev = aLast->m_prev;
    aLast->m_prev = aFirst->m_prev;
    aFirst->m_prev = temp;
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>::reverse()
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

  //////////////////////////////////////////////////////////////////////////
  // Macros

#define LIST_TEMP_TYPES typename T, typename T_Node, typename T_Policy, \
  bool T_DedicatedSize
#define LIST_TEMP T, T_Node, T_Policy, T_DedicatedSize

  //------------------------------------------------------------------------
  // Ctors / Dtors

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP >::List()
    : m_node(), m_size(0)
  {
    DoInit();
  }

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP>::List(size_type aNumTimes, const T& aValue)
    : m_node(), m_size(0)
  {
    DoInit();
    DoInsertValues(&m_node, aNumTimes, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputItr>
  TL_FI List<LIST_TEMP>::List(T_InputItr aFirst, T_InputItr aLast)
    : m_node(), m_size(0)
  {
    DoInit();
    insert(&m_node, aFirst, aLast);
  }

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP>::List(const this_type& aOther)
    : m_node(), m_size(0)
  {
    DoInit();
    DoInsert(&m_node, aOther.begin(), aOther.end(), is_not_arith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI List<LIST_TEMP >::~List()
  {
    DoClear();
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
    return iterator(m_node.m_next);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_iterator List<LIST_TEMP>::begin() const
  {
    return const_iterator(m_node.m_next);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::end()
  {
    return iterator(&m_node);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_iterator List<LIST_TEMP>::end() const
  {
    return const_iterator(&m_node);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator List<LIST_TEMP>::rbegin()
  {
    return reverse_iterator(&m_node);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reverse_iterator
    List<LIST_TEMP>::rbegin() const
  {
    return const_reverse_iterator(&m_node);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reverse_iterator List<LIST_TEMP>::rend()
  {
    return reverse_iterator(m_node.m_next);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reverse_iterator
    List<LIST_TEMP>::rend() const
  {
    return const_reverse_iterator(m_node.m_next);
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
    return &m_node == m_node.m_next;
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
    return m_node.m_next->m_value;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reference
    List<LIST_TEMP>::front() const
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node.m_next->m_value;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference
    List<LIST_TEMP>::back()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node.m_prev->m_value;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::const_reference
    List<LIST_TEMP>::back() const
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    return m_node.m_prev->m_value;
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
    typedef Loki::TypeTraits<T_InputItr> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isArith> inputArith;

    DoAssign(aRangeBegin, aRangeEnd, inputArith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::push_front(const typename List<LIST_TEMP>::value_type& aVal)
  {
    DoInsertValue(m_node.m_next, aVal);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference List<LIST_TEMP>::push_front()
  {
    node_type* const node = DoCreateNode();
    node->insert(m_node.m_next);
    ++m_size;
    return m_node.m_next->m_value;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::pointer
    List<LIST_TEMP>::push_front_uninitialized()
  {
    node_type* const node = DoAllocateNode();
    node->insert(m_node.m_next);
    ++m_size;
    return &(node->m_value);
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::push_back(const typename List<LIST_TEMP>::value_type& aVal)
  {
    DoInsertValue(&m_node, aVal);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::reference List<LIST_TEMP>::push_back()
  {
    node_type* const node = DoCreateNode();
    node->insert(&m_node);
    ++m_size;
    return m_node.m_prev->m_value;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::pointer
    List<LIST_TEMP>::push_back_uninitialized()
  {
    node_type* const node = DoAllocateNode();
    node->insert(m_node.m_next);
    ++m_size;
    return &(node->m_value);
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::pop_back()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    DoErase(m_node.m_prev);
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::pop_front()
  {
    TLOC_ASSERT_LIST_NOT_EMPTY();
    DoErase(m_node.m_next);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::insert(iterator aPos)
  {
    node_type* const node = DoCreateNode(value_type());
    node->insert(aPos.m_node);
    ++m_size;
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::insert(iterator aPos, const value_type& aValue)
  {
    node_type* const node = DoCreateNode(aValue);
    node->insert(aPos.m_node);
    ++m_size;
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::insert(iterator aPos, size_type aNumOfValues,
                                     const value_type& aValue)
  {
    DoInsertValues(aPos.m_node, aNumOfValues, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Iterator>
  TL_FI void List<LIST_TEMP>::insert(iterator aPos, T_Iterator aFirst,
                                     T_Iterator aLast)
  {
    typedef Loki::TypeTraits<T_Iterator> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isArith> inputArith;

    DoInsert(aPos.m_node, aFirst, aLast, inputArith());
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator
    List<LIST_TEMP>::erase(iterator aPos)
  {
    ++aPos;
    DoErase(aPos.m_node->m_prev);
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
  TL_FI void List<LIST_TEMP>::swap(this_type& aOther)
  {
    tlSwap(*this, aOther);
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::clear()
  {
    DoClear();
    DoInit();
    m_size = 0;
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
      DoSplice(aPos, aFrom, aFrom.begin(), aFrom.end(), list_size());
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

    aPos.m_node->splice(aOther.m_node, itr.m_node);
    ++m_size;
    --aFrom.m_size;

  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::splice(iterator aPos, this_type& aFrom,
                                     iterator aOtherBegin, iterator aOtherEnd)
  {
    DoSplice(aPos, aFrom, aOtherBegin, aOtherEnd, list_size());
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::remove(const T& aValueToCompare)
  {
    iterator itr(m_node.m_next);
    while (itr.m_node != &m_node)
    {
      if (*itr != aValueToCompare)
      {
        ++itr;
      }
      else
      {
        ++itr;
        DoErase(itr.m_node->m_prev);
      }
    }
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Pred>
  TL_FI void List<LIST_TEMP>::remove_if(T_Pred aFunctionToCompare)
  {
    iterator itr(m_node.m_next);
    while (itr.m_node != &m_node)
    {
      if (!T_Pred(*itr))
      {
        ++itr;
      }
      else
      {
        ++itr;
        DoErase(itr.m_node->m_prev);
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
          DoErase(itrBegin.m_node);
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
          DoErase(itrBegin.m_node);
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
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Compare>
  TL_FI void List<LIST_TEMP>::merge(this_type& aOther, T_Compare aComp)
  {
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
    m_node.reverse();
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP >::DoInit()
  {
    // We use this node as the terminating node because when the user queries
    // the 'end' iterator, we need to return a valid iterator object
    m_node.m_next = &m_node;
    m_node.m_prev = &m_node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP >::DoClear()
  {
    node_type* node = m_node.m_next;

    while (node->m_next != &m_node)
    {
      node_type* tempNode = node;
      node = node->m_next;

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
    new(&node->m_value) value_type;
    return node;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::node_type*
    List<LIST_TEMP>::DoCreateNode(const T& aValueCopy)
  {
    node_type* node = DoAllocateNode();
    new(&node->m_value) value_type(aValueCopy);
    return node;
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Integer>
  TL_FI void List<LIST_TEMP>::DoAssign(T_Integer aNumTimes,
                                       const T_Integer& aValueCopy, is_arith)
  {
    DoAssignValues(static_cast<size_type>(aNumTimes),
                   static_cast<size_type>(aValueCopy));
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputItr>
  TL_FI void List<LIST_TEMP>::DoAssign(T_InputItr aRangeBegin,
                                       T_InputItr aRangeEnd, is_not_arith)
  {
    node_type* node = m_node.m_next;

    // Fill as much as we can
    while ( (aRangeBegin != aRangeEnd) && (node != &m_node) )
    {
      node->m_value = *aRangeBegin;
      node = node->m_next;
      ++aRangeBegin;
    }

    // Deal with over/under flow
    if (aRangeBegin != aRangeEnd)
    {
      DoInsert(&m_node, aRangeBegin, aRangeEnd, is_not_arith());
    }
    else
    {
      erase(iterator(node), &m_node);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoAssignValues(size_type aNumTimes,
                                             const value_type& aValueCopy)
  {
    node_type* node = m_node.m_next;

    // Fill as much as we can
    while ((node != &m_node) && (aNumTimes > 0))
    {
      node->m_value = aValueCopy;
      node = node->m_next;
      --aNumTimes;
    }

    // Deal with over/under flow
    if (aNumTimes > 0)
    {
      DoInsertValues(&m_node, aNumTimes, aValueCopy);
    }
    else
    {
      erase(iterator(node), &m_node);
    }
  }

  template <LIST_TEMP_TYPES>
  template <typename T_Integer>
  TL_FI void List<LIST_TEMP>::DoInsert(node_type* aPos, T_Integer aNumTimes,
                                       T_Integer aValue, is_arith)
  {
    DoInsertValues(aPos, aNumTimes, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputIterator>
  TL_FI void List<LIST_TEMP>::DoInsert(node_type* aPos, T_InputIterator aFirst,
                                       T_InputIterator aLast, is_not_arith)
  {
    while (aFirst != aLast)
    {
      DoInsertValue(aPos, *aFirst);
      ++aFirst;
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoInsertValue(node_type* aNode,
                                                  const T& aValueCopy)
  {
    node_type* const newNode = DoCreateNode(aValueCopy);
    newNode->insert(aNode);
    ++m_size;
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoInsertValues(node_type* aNode,
                                                   tl_size numElements,
                                                   const T& aValueCopy)
  {
    for (; numElements > 0; --numElements)
    {
      DoInsertValue(aNode, aValueCopy);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoErase(node_type* aNode)
  {
    aNode->remove();
    aNode->~node_type();
    DoFreeNode(aNode);
    --m_size;
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type
    List<LIST_TEMP>::DoGetSize(typename List<LIST_TEMP>::size_stored) const
  {
    return m_size.value();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type
    List<LIST_TEMP>::DoGetSize(typename List<LIST_TEMP>::size_not_stored) const
  {
    return tloc::distance(const_iterator(m_node.m_next), const_iterator(&m_node));
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoResize
    (typename List<LIST_TEMP>::size_type aNumElements,
     const typename List<LIST_TEMP>::value_type& aValue,
     typename List<LIST_TEMP>::size_stored)
  {
    // Assuming the user would usually want to grow the list when calling resize
    if (aNumElements > m_size)
    {
      insert(&m_node, aNumElements - m_size, aValue);
    }
    else
    {
      iterator itr(m_node.m_next);
      tloc::advance(itr, aNumElements);
      erase(itr, &m_node);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoResize
    (typename List<LIST_TEMP>::size_type aNumElements,
    const typename List<LIST_TEMP>::value_type& aValue,
    typename List<LIST_TEMP>::size_not_stored)
  {
    iterator itr(m_node.m_next);
    size_type count = 0;

    while ( (itr.m_node != &m_node) && (count < aNumElements) )
    {
      ++count; ++itr;
    }

    if (count == aNumElements)
    {
      erase(itr, &m_node);
    }
    else
    {
      insert(&m_node, aNumElements - count, aValue);
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoSplice(typename List<LIST_TEMP>::iterator aPos,
                                       typename List<LIST_TEMP>::this_type& aFrom,
                                       typename List<LIST_TEMP>::iterator aBegin,
                                       typename List<LIST_TEMP>::iterator aEnd,
                                       typename List<LIST_TEMP>::size_stored)
  {
    TLOC_UNUSED(aPos);
    TLOC_UNUSED(aFrom);
    TLOC_UNUSED(aBegin);
    TLOC_UNUSED(aEnd);

    const size_type addedSize = tloc::distance(aBegin, aEnd);
    if (addedSize != 0)
    {
      aPos.m_node->splice(aBegin.m_node, aEnd.m_node);
      m_size += addedSize;
      aFrom.m_size -= addedSize;
    }
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::DoSplice(typename List<LIST_TEMP>::iterator aPos,
                                       typename List<LIST_TEMP>::this_type& aFrom,
                                       typename List<LIST_TEMP>::iterator aBegin,
                                       typename List<LIST_TEMP>::iterator aEnd,
                                       typename List<LIST_TEMP>::size_not_stored)
  {
    TLOC_UNUSED(aFrom);

    if (aBegin != aEnd)
    {
      aPos.m_node->splice(aBegin.m_node, aEnd.m_node);
    }
  }

};