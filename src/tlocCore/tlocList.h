#ifndef TLOC_LIST_H
#define TLOC_LIST_H

#include "tlocBase.h"
#include "tlocMemory.h"
#include "tlocTypeTraits.h"
#include "tlocIterator.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_LIST
# define TLOC_ASSERT_LIST(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_LIST(_Expression, _Msg)
#endif

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Different policies that List can handle

  struct List_Dynamic  {};
  struct List_Bucket    {};
  struct List_Fixed      {};

  //////////////////////////////////////////////////////////////////////////
  // List node
 
  template <typename T, typename T_ItrTag>
  struct ListNode
  {
  private:
    ListNode();
  };

  template <typename T>
  struct ListNode<T, doubly_linked_tag>
  {
    typedef ListNode<T, doubly_linked_tag>  this_type;

    typedef T               value_type;
    typedef T*              pointer_type;
    typedef T&              reference_type;
    typedef tl_ptrdiff      difference_type;

    typedef bidirectional_iterator_tag  iterator_category;
    typedef doubly_linked_tag           itr_tag;

    ListNode();
    ListNode(const this_type& aOther); 

    void            insert(ListNode* aNext);
    void            remove();
    void            splice(ListNode* aFirst, ListNode* aLast);
    void            reverse();

    ListNode*       m_next;
    ListNode*       m_prev;
    T               m_value;
  };

  //////////////////////////////////////////////////////////////////////////
  // Array class

  template <typename T, typename T_Node = ListNode<T, doubly_linked_tag>, 
            typename T_Policy = List_Dynamic(), bool T_DedicatedSize = true>
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
    //typedef const T*                                    const_pointer;
    //typedef const T*                                    const_iterator;
    typedef tl_size                                     size_type;
    typedef tl_ptrdiff                                  difference_type;
    typedef tloc::reverse_iterator<iterator>            reverse_iterator;
    typedef tloc::reverse_iterator<const_iterator>      const_reverse_iterator;

    typedef ConditionalType<tl_size, T_DedicatedSize>   list_size;

  public:
    List();
    ~List();

    iterator   begin();
    iterator   end();

  protected:
    void DoInit();
    void DoClear();

    node_type* DoAllocateNode();
    void       DoFreeNode(node_type* aNode);

    node_type* DoCreateNode();
    node_type* DoCreateNode(const T& aValueCopy);

    void       DoInsertValues(node_type* aNode, tl_size numElements, const T& aValueCopy);
    void       DoInsertValue(node_type* aNode, const T& aValueCopy);

  protected:
    node_type                 m_node;
    list_size                 m_size;

  };
};

#include "tlocList.inl"

#endif