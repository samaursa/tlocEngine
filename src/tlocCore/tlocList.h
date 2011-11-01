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

    typedef doubly_linked_tag           iterator_category;

    TL_FI ListNode();
    TL_FI ListNode(const this_type& aOther);

    TL_STATIC_FI void swap(this_type& a, this_type& b);
    TL_FI        void insert(this_type* aNext);
    TL_FI        void remove();
    TL_FI        void splice(this_type* aFirst, this_type* aLast);
    TL_FI        void reverse();

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
    typedef const T*                                    const_pointer;
    typedef tl_size                                     size_type;
    typedef tl_ptrdiff                                  difference_type;
    typedef tloc::reverse_iterator<iterator>            reverse_iterator;
    typedef tloc::reverse_iterator<const_iterator>      const_reverse_iterator;

    typedef ConditionalType<size_type, T_DedicatedSize> list_size;

  public:
    TL_FI List();
    TL_FI ~List();

    //------------------------------------------------------------------------
    // Iterator access

    TL_FI iterator        begin();
    TL_FI const_iterator  begin() const;
    TL_FI iterator        end();
    TL_FI const_iterator  end() const;

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
    TL_FI void        insert(iterator aPos, T_Iterator aFirst, T_Iterator aLast);

    TL_FI iterator    erase(iterator aPos);
    TL_FI iterator    erase(iterator aFirst, iterator aLast);

    TL_FI reverse_iterator erase(reverse_iterator aPos);
    TL_FI reverse_iterator erase(reverse_iterator aFirst, reverse_iterator aLast);

    TL_FI void        swap(this_type& aOther);

    TL_FI void        clear();

    //------------------------------------------------------------------------
    // Operations

    TL_FI void        splice(iterator aPos, this_type& aFrom);
    TL_FI void        splice(iterator aPos, this_type& aFrom, iterator aOther);
    TL_FI void        splice(iterator aPos, this_type& aFrom, iterator aOtherBegin,
                             iterator aOtherEnd);

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

    TL_FI void DoInit();
    TL_FI void DoClear();

    TL_FI node_type* DoAllocateNode();
    TL_FI void       DoFreeNode(node_type* aNode);

    TL_FI node_type* DoCreateNode();
    TL_FI node_type* DoCreateNode(const T& aValueCopy);

    template <typename T_Integer>
    TL_FI void       DoInsert(node_type* aPos, T_Integer aNumTimes, T_Integer aValue,
                              type_true);

    template <typename T_InputIterator>
    TL_FI void       DoInsert(node_type* aPos, T_InputIterator aFirst,
                              T_InputIterator aLast, type_false);

    TL_FI void       DoInsertValue(node_type* aNode, const T& aValueCopy);
    TL_FI void       DoInsertValues(node_type* aNode, tl_size numElements, const T& aValueCopy);

    TL_FI void       DoErase(node_type* aNode);

    TL_FI size_type  DoGetSize(size_stored) const;
    TL_FI size_type  DoGetSize(size_not_stored) const;

    TL_FI void       DoResize(size_type aNumElements, const value_type& aValue,
                              size_stored);
    TL_FI void       DoResize(size_type aNumElements, const value_type& aValue,
                              size_not_stored);

  protected:
    node_type                 m_node;
    list_size                 m_size;

  };
};

#include "tlocList.inl"

#endif