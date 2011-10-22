#include "tlocList.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // ListNode

  template <typename T>
  ListNode<T, doubly_linked_tag>::ListNode()
  {
  }

  template <typename T>
  ListNode<T, doubly_linked_tag>::ListNode(const ListNode<T, doubly_linked_tag>& aOther)
  {
    m_next = aOther.m_next;
    m_prev = aOther.m_prev;
    m_value = aOther.m_value;
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>::insert(ListNode<T, doubly_linked_tag>* aNext)
  {
    m_next = aNext;
    m_prev = aNext->m_prev;
    aNext->m_prev->m_next = this;
    aNext->m_prev = this;
  }

  template <typename T>
  void ListNode<T, doubly_linked_tag>::remove()
  {
    TLOC_ASSERT_WIP();
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

#define LIST_TEMP_PARAMS typename T, typename T_Node, typename T_Policy, \
  bool T_DedicatedSize
#define LIST_TEMP T, T_Node, T_Policy, T_DedicatedSize

  //------------------------------------------------------------------------
  // Ctors / Dtors

  template <LIST_TEMP_PARAMS>
  TL_FI List<LIST_TEMP >::List()
    : m_node(), m_size(0)
  {
    DoInit();
  }

  template <LIST_TEMP_PARAMS>
  TL_FI List<LIST_TEMP >::~List()
  {
    DoClear();
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::begin()
  {
    return iterator(m_node.m_next);
  }

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::iterator List<LIST_TEMP>::end()
  {
    return iterator(&m_node);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::iterator 
    List<LIST_TEMP>::insert(iterator aPos)
  {
    node_type* const node = DoCreateNode(value_type());
    node->insert(aPos.m_node);
    ++m_size;
    return node;
  }

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::iterator 
    List<LIST_TEMP>::insert(iterator aPos, const value_type& aValue)
  {
    node_type* const node = DoCreateNode(aValue);
    node->insert(aPos.m_node);
    ++m_size;
    return node;
  }

  template <LIST_TEMP_PARAMS>
  TL_FI void List<LIST_TEMP>::insert(iterator aPos, size_type aNumValues, 
                                     const value_type& aValue)
  {
    TLOC_UNUSED(aPos);
    TLOC_UNUSED(aNumValues);
    TLOC_UNUSED(aValue);
    TLOC_ASSERT_WIP();
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <LIST_TEMP_PARAMS>
  TL_FI void List<LIST_TEMP >::DoInit()
  {
    // We use this node as the terminating node because when the user queries
    // the 'end' iterator, we need to return a valid iterator object
    m_node.m_next = &m_node;
    m_node.m_prev = &m_node;
  }

  template <LIST_TEMP_PARAMS>
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

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::node_type* 
    List<LIST_TEMP>::DoAllocateNode()
  {
    return (node_type*)TL_MALLOC(sizeof(node_type));
  }

  template <LIST_TEMP_PARAMS>
  TL_FI void List<LIST_TEMP>::DoFreeNode(node_type* aNode)
  {
    TL_FREE(aNode);
  }

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::node_type*
    List<LIST_TEMP>::DoCreateNode()
  {
    node_type* node = DoAllocateNode();
    new(&node->m_value) value_type;
    return node;
  }

  template <LIST_TEMP_PARAMS>
  TL_FI typename List<LIST_TEMP>::node_type*
    List<LIST_TEMP>::DoCreateNode(const T& aValueCopy)
  {
    node_type* node = DoAllocateNode();
    new(&node->m_value) value_type(aValueCopy);
    return node;
  }

  template <LIST_TEMP_PARAMS>
  TL_FI void List<LIST_TEMP>::DoInsertValues(node_type* aNode,
                                                   tl_size numElements,
                                                   const T& aValueCopy)
  {
    TLOC_UNUSED(aNode);
    TLOC_UNUSED(numElements);
    TLOC_UNUSED(aValueCopy);
    TLOC_ASSERT_WIP();
  }

  template <LIST_TEMP_PARAMS>
  TL_FI void List<LIST_TEMP>::DoInsertValue(node_type* aNode,
                                                  const T& aValueCopy)
  {
    node_type* const newNode = DoCreateNode(aValueCopy);
    newNode->insert(aNode);
    ++m_size;
  }
};