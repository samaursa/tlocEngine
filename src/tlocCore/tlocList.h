#ifndef TLOC_LIST_H
#define TLOC_LIST_H

#include "tlocBase.h"
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

  template <typename T, doubly_linked_tag>
  struct ListNode
  {
    typedef T       value_type;
    typedef T*      pointer_type;
    typedef T&      reference_type;
    tl_ptrdiff      difference_type;

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

  template <bool T_DedicatedSize>
  struct ListSize
  {
  };

  template <>
  struct ListSize<true>
  {
    tl_size m_size;
  };

  template <typename T, typename T_Policy = List_Dynamic(),
            typename T_ItrTag = doubly_linked_tag, bool T_DedicatedSize = true>
  class List
  {
  public:
    //------------------------------------------------------------------------
    // typedefs
    typedef List<T, T_Policy, T_ItrTag>                 this_type;
    typedef ListNode<T, T_ItrTag>                       node_type;

    typedef list_iterator<ListNode, T_ItrTag, T, T*, T&>  iterator;
    typedef list_iterator<ListNode, T_ItrTag, T, const T*, const T&> const_iterator;

    typedef T                                           value_type;
    typedef T*                                          pointer;
    typedef T&                                          reference;
    typedef const T&                                    const_reference;
    typedef const T*                                    const_pointer;
    typedef const T*                                    const_iterator;
    typedef tl_size                                     size_type;
    typedef tl_ptrdiff                                  difference_type;
    typedef tloc::reverse_iterator<iterator>            reverse_iterator;
    typedef tloc::reverse_iterator<const_iterator>      const_reverse_iterator;

  protected:
    node_type                 m_node;
    ListSize<T_DedicatedSize> m_size;

  };
};

#include "tlocArray.inl"

#endif