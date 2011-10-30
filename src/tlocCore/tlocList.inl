#include "tlocList.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // ListNode
  
#define LIST_NODE_T ListNode<T, doubly_linked_tag> 

  template <typename T>
  TL_FI LIST_NODE_T::ListNode()
  {
  }

  template <typename T>
  TL_FI LIST_NODE_T::ListNode(const LIST_NODE_T& aOther)
  {
    m_next = aOther.m_next;
    m_prev = aOther.m_prev;
    m_value = aOther.m_value;
  }

  template <typename T>
  TL_FI void LIST_NODE_T::swap(LIST_NODE_T& a, LIST_NODE_T& b)
  {
    TLOC_UNUSED(a);
    TLOC_UNUSED(b);
    TLOC_ASSERT_WIP();
  }

  template <typename T>
  void LIST_NODE_T::insert(LIST_NODE_T* aNext)
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
  void ListNode<T, doubly_linked_tag>::splice(ListNode<T, doubly_linked_tag>* aFirst,
                                              ListNode<T, doubly_linked_tag>* aLast)
  {
    TLOC_UNUSED(aFirst);
    TLOC_UNUSED(aLast);
    TLOC_ASSERT_WIP();
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>::reverse()
  {
    TLOC_ASSERT_WIP();
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
  TL_FI List<LIST_TEMP >::~List()
  {
    DoClear();
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::begin()
  {
    return iterator(m_node.m_next);
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::end()
  {
    return iterator(&m_node);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type List<LIST_TEMP>::size()
  {
    return DoGetSize(list_size());
  }

  template <LIST_TEMP_TYPES>
  TL_FI bool List<LIST_TEMP>::empty()
  {
    return &m_node == m_node.m_next;
  }

  //------------------------------------------------------------------------
  // Modifiers

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
    TLOC_ASSERT_LIST(size() > 0, "Container is empty!");
    DoErase(m_node.m_prev);
  }

  template <LIST_TEMP_TYPES>
  TL_FI void List<LIST_TEMP>::pop_front()
  {
    TLOC_ASSERT_LIST(size() > 0, "Container is empty!");
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
  TL_FI void List<LIST_TEMP>::clear()
  {
    DoClear();
    DoInit();
    m_size = 0;
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
  TL_FI void List<LIST_TEMP>::DoInsert(node_type* aPos, T_Integer aNumTimes, 
                                       T_Integer aValue, type_true)
  {
    DoInsertValues(aPos, aNumTimes, aValue);
  }

  template <LIST_TEMP_TYPES>
  template <typename T_InputIterator>
  TL_FI void List<LIST_TEMP>::DoInsert(node_type* aPos, T_InputIterator aFirst, 
                                       T_InputIterator aLast, type_false)
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
    List<LIST_TEMP>::DoGetSize(size_stored)
  {
    return m_size.value();
  }

  template <LIST_TEMP_TYPES>
  TL_FI typename List<LIST_TEMP>::size_type 
    List<LIST_TEMP>::DoGetSize(size_not_stored)
  {
    return tloc::distance(const_iterator(m_node.m_next), const_iterator(&m_node));
  }

};