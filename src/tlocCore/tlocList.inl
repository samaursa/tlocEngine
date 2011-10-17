namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Macros

#define LIST_TEMP_PARAMS typename T, typename T_Node, typename T_Policy, \
  bool T_DedicatedSize
#define LIST_TEMP_TEMPS T, T_Node, T_Policy, T_DedicatedSize

  template <LIST_TEMP_PARAMS>
  List<LIST_TEMP_TEMPS >::List()
    : m_node(), m_size(0)
  {
    DoInit();
  }

  template <LIST_TEMP_PARAMS>
  List<LIST_TEMP_TEMPS >::~List()
  {
    DoClear();
  }

  template <LIST_TEMP_PARAMS>
  void List<LIST_TEMP_TEMPS >::DoInit()
  {
    // We use this node as the terminating node because when the user queries
    // the 'end' iterator, we need to return a valid iterator object
    m_node.m_next = &m_node;
    m_node.m_prev = &m_node;
  }

  template <LIST_TEMP_PARAMS>
  void List<LIST_TEMP_TEMPS >::DoClear()
  {
    node_type* node = m_node.m_next;

    while (node->m_next != NULL)
    {
      node_type* tempNode = node;
      node = node->m_next;

      tempNode->~node_type();
      TL_FREE(tempNode);
    }
  }

  template <LIST_TEMP_PARAMS>
  typename List<LIST_TEMP_TEMPS>::node_type* List<LIST_TEMP_TEMPS>::DoAllocateNode()
  {
    return (node_type*)TL_MALLOC(sizeof(node_type));
  }

  template <LIST_TEMP_PARAMS>
  void List<LIST_TEMP_TEMPS>::DoFreeNode(node_type* aNode)
  {
    TL_FREE(aNode);
  }

  template <LIST_TEMP_PARAMS>
  typename List<LIST_TEMP_TEMPS>::node_type*
    List<LIST_TEMP_TEMPS>::DoCreateNode()
  {
    node_type* node = DoAllocateNode();
    new(&node->m_value) value_type;
    return node;
  }

  template <LIST_TEMP_PARAMS>
  typename List<LIST_TEMP_TEMPS>::node_type*
    List<LIST_TEMP_TEMPS>::DoCreateNode(const T& aValueCopy)
  {
    node_type* node = DoAllocateNode();
    new(&node->m_value) value_type(aValueCopy);
    return node;
  }

  template <LIST_TEMP_PARAMS>
  typename List<LIST_TEMP_TEMPS>::iterator List<LIST_TEMP_TEMPS>::begin()
  {
    return iterator(m_node.m_next);
  }

  template <LIST_TEMP_PARAMS>
  typename List<LIST_TEMP_TEMPS>::iterator List<LIST_TEMP_TEMPS>::end()
  {
    return iterator(&m_node);
  }

  template <LIST_TEMP_PARAMS>
  void List<LIST_TEMP_TEMPS>::DoInsertValues(node_type* aNode,
                                             tl_size numElements,
                                             const T& aValueCopy)
  {
    TLOC_UNUSED(aNode);
    TLOC_UNUSED(numElements);
    TLOC_UNUSED(aValueCopy);
  }

  template <LIST_TEMP_PARAMS>
  void List<LIST_TEMP_TEMPS>::DoInsertValue(node_type* aNode, const T& aValueCopy)
  {
    node_type* const newNode = DoCreateNode(aValueCopy);
    newNode->insert(aNode);
    ++m_size;
  }
};