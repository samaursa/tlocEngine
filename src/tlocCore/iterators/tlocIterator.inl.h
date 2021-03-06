#ifndef TLOC_ITERATOR_INL
#define TLOC_ITERATOR_INL

#ifndef TLOC_ITERATOR_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/types/tlocTypes.inl.h>
#include <tlocCore/tlocAssert.h>

namespace tloc { namespace core {
  //////////////////////////////////////////////////////////////////////////
  // Pre-defined iterators

  //````````````````````````````````````````````````````````````````````````
  // back_insert_iterator

  template <typename T_Container>
  back_insert_iterator<T_Container>::
    back_insert_iterator( T_Container& aContainer )
    : m_container(&aContainer)
  {
  }

  template <typename T_Container>
  back_insert_iterator<T_Container>&
    back_insert_iterator<T_Container>::
    operator*()
  {
    return *this;
  }

  template <typename T_Container>
  back_insert_iterator<T_Container>&
    back_insert_iterator<T_Container>::
    operator++()
  {
    return *this;
  }

  template <typename T_Container>
  back_insert_iterator<T_Container>&
    back_insert_iterator<T_Container>::
    operator++( int )
  {
    return *this;
  }

  template <typename T_Container>
  back_insert_iterator<T_Container>&
    back_insert_iterator<T_Container>::
    operator=( const_reference aValue )
  {
    m_container->push_back(aValue);
    return *this;
  }

  //````````````````````````````````````````````````````````````````````````
  // front_insert_iterator

  template <typename T_Container>
  front_insert_iterator<T_Container>::
    front_insert_iterator( T_Container& aContainer )
    : m_container(aContainer)
  {
  }

  template <typename T_Container>
  front_insert_iterator<T_Container>&
    front_insert_iterator<T_Container>::
    operator*()
  {
    return *this;
  }

  template <typename T_Container>
  front_insert_iterator<T_Container>&
    front_insert_iterator<T_Container>::
    operator++()
  {
    return *this;
  }

  template <typename T_Container>
  front_insert_iterator<T_Container>&
    front_insert_iterator<T_Container>::
    operator++( int )
  {
    return *this;
  }

  template <typename T_Container>
  front_insert_iterator<T_Container>&
    front_insert_iterator<T_Container>::
    operator=( const_reference aValue )
  {
    m_container.push_front(aValue);
    return *this;
  }

  template <typename T_Container>
  front_insert_iterator<T_Container>&
    front_insert_iterator<T_Container>::
    operator=( const this_type& aOther )
  {
    return *this;
  }

  //````````````````````````````````````````````````````````````````````````
  // insert_iterator

  template <typename T_Container>
  insert_iterator<T_Container>::
    insert_iterator( T_Container& aContainer, iterator_type aItr )
    : m_container(aContainer), m_itr(aItr)
  {
  }

  template <typename T_Container>
  insert_iterator<T_Container>&
    insert_iterator<T_Container>::
    operator*()
  {
    return *this;
  }

  template <typename T_Container>
  insert_iterator<T_Container>&
    insert_iterator<T_Container>::
    operator++()
  {
    return *this;
  }

  template <typename T_Container>
  insert_iterator<T_Container>&
    insert_iterator<T_Container>::
    operator++( int )
  {
    return *this;
  }

  template <typename T_Container>
  insert_iterator<T_Container>&
    insert_iterator<T_Container>::
    operator=( const_reference aValue )
  {
    m_itr = m_container.insert(m_itr, aValue);
    ++m_itr;
    return *this;
  }

  template <typename T_Container>
  insert_iterator<T_Container>&
    insert_iterator<T_Container>::
    operator=( const this_type& aOther )
  {
    TLOC_ASSERT_ITERATOR(&m_container == aOther.m_container,
      "Iterators belong to different containers!");
    m_itr = aOther.m_itr;
    return *this;
  }

  //````````````````````````````````````````````````````````````````````````
  // reverse_iterator

  template <typename T_Itr>
  reverse_iterator<T_Itr>::
    reverse_iterator() : m_itr()
  { }

  template <typename T_Itr>
  reverse_iterator<T_Itr>::
    reverse_iterator( const T_Itr aIterator )
    : m_itr(aIterator)
  { }

  template <typename T_Itr>
  template <typename U>
  reverse_iterator<T_Itr>::
    reverse_iterator( const reverse_iterator<U>& aOther )
    : m_itr(aOther.base())
  { }

  template <typename T_Itr>
  T_Itr reverse_iterator<T_Itr>::
    base() const
  { return m_itr; }

  template <typename T_Itr>
  template <typename U>
  reverse_iterator<T_Itr>&
    reverse_iterator<T_Itr>::
    operator=( const reverse_iterator<U>& aOther )
  {
    m_itr = aOther.base();
    return *this;
  }

  template <typename T_Itr>
  typename reverse_iterator<T_Itr>::reference
    reverse_iterator<T_Itr>::
    operator*() const
  {
    // reverse iterator is always pointer 1 past the element
    T_Itr itr(m_itr);
    --itr;
    return *itr;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>
    reverse_iterator<T_Itr>::
    operator+( difference_type aDistance ) const
  {
    reverse_iterator<T_Itr> itr(m_itr - aDistance);
    return itr;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>&
    reverse_iterator<T_Itr>::
    operator++()
  {
    --m_itr;
    return *this;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>
    reverse_iterator<T_Itr>::
    operator++( int )
  {
    reverse_iterator itr(*this);
    --m_itr;
    return *this;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>&
    reverse_iterator<T_Itr>::
    operator+=( difference_type aDistance )
  {
    m_itr -= aDistance;
    return *this;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>
    reverse_iterator<T_Itr>::
    operator-( difference_type aDistance )
  {
    reverse_iterator<T_Itr> itr(m_itr + aDistance);
    return itr;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>&
    reverse_iterator<T_Itr>::
    operator--()
  {
    ++m_itr;
    return *this;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>
    reverse_iterator<T_Itr>::
    operator--( int )
  {
    T_Itr itr(*this);
    ++m_itr;
    return *this;
  }

  template <typename T_Itr>
  reverse_iterator<T_Itr>&
    reverse_iterator<T_Itr>::
    operator-=( difference_type aDistance )
  {
    m_itr += aDistance;
    return *this;
  }

  template <typename T_Itr>
  typename reverse_iterator<T_Itr>::pointer
    reverse_iterator<T_Itr>::
    operator->() const
  {
    return &(operator*());
  }

  template <typename T_Itr>
  typename reverse_iterator<T_Itr>::reference
    reverse_iterator<T_Itr>::
    operator[]( difference_type aDistance ) const
  {
    return m_itr[ - aDistance - 1];
  }

  //````````````````````````````````````````````````````````````````````````
  // Global operators for reverse_iterator

  template <typename T_Itr1, typename T_Itr2>
  bool operator==( const reverse_iterator<T_Itr1>& a,
                        const reverse_iterator<T_Itr2>& b )
  {
    return a.base() == b.base();
  }

  template <typename T_Itr1, typename T_Itr2>
  bool operator!=( const reverse_iterator<T_Itr1>& a,
                   const reverse_iterator<T_Itr2>& b )
  {
    return a.base() != b.base();
  }

  template <typename T_Itr1, typename T_Itr2>
  bool operator<( const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b )
  {
    return a.base() > b.base();
  }

  template <typename T_Itr1, typename T_Itr2>
  bool operator<=( const reverse_iterator<T_Itr1>& a,
                   const reverse_iterator<T_Itr2>& b )
  {
    return a.base() >= b.base();
  }

  template <typename T_Itr1, typename T_Itr2>
  bool operator>( const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b )
  {
    return a.base() < b.base();
  }

  template <typename T_Itr1, typename T_Itr2>
  bool operator>=( const reverse_iterator<T_Itr1>& a,
                   const reverse_iterator<T_Itr2>& b )
  {
    return a.base() <= b.base();
  }

  template <typename T_Itr1, typename T_Itr2>
  typename reverse_iterator<T_Itr1>::difference_type
    operator-( const reverse_iterator<T_Itr1>& a,
               const reverse_iterator<T_Itr2>& b )
  {
    return b.base() - a.base();
  }

  template <typename T_Itr>
  typename reverse_iterator<T_Itr>::difference_type
    operator+( typename reverse_iterator<T_Itr>::difference_type aDistance,
               const reverse_iterator<T_Itr>& a )
  {
    reverse_iterator<T_Itr> itr(a.base() - aDistance);
    return itr;
  }

  //````````````````````````````````````````````````````````````````````````
  // Iterator construction

  template <typename T_Container>
  back_insert_iterator<T_Container> back_inserter( T_Container& aContainer )
  {
    return back_insert_iterator<T_Container>(aContainer);
  }

  template <typename T_Container>
  front_insert_iterator<T_Container> front_inserter( T_Container& aContainer )
  {
    return front_insert_iterator<T_Container>(aContainer);
  }

  template <typename T_Container>
  insert_iterator<T_Container> inserter( T_Container& aContainer )
  {
    return insert_iterator<T_Container>(aContainer);
  }

  //////////////////////////////////////////////////////////////////////////
  // Gobal functions

  template <typename T_InputItr>
  typename iterator_traits<T_InputItr>::difference_type
    distance( T_InputItr aBegin, T_InputItr aEnd )
  {
    typedef typename iterator_traits<T_InputItr>::iterator_category itrCat;

    return detail::distance(aBegin, aEnd, itrCat());
  }


  template <typename T_InputItr, typename T_Distance>
  void advance( T_InputItr& aItr, T_Distance aN )
  {
    typedef typename iterator_traits<T_InputItr>::iterator_category itrCat;

    detail::advance(aItr, aN, itrCat());
  }

  //////////////////////////////////////////////////////////////////////////
  // Custom generic iterators (not defined in the standard)

  //````````````````````````````````````````````````````````````````````````
  // Macros

#define LIST_ITR_TEMP typename T_Node, typename T_Itr_Type, \
  typename T, typename T_Ptr, typename T_Ref

#define LIST_ITR_PARAMS T_Node, T_Itr_Type, T, T_Ptr, T_Ref

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>::
    list_iterator() : m_node()
  {
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>::
    list_iterator(const T_Node* aNode) : m_node(const_cast<T_Node*>(aNode))
  {
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>::
    list_iterator(const iterator& aOtherItr)
  : m_node(aOtherItr.m_node)
  {
  }

  template <LIST_ITR_TEMP>
  typename list_iterator<LIST_ITR_PARAMS>::reference
    list_iterator<LIST_ITR_PARAMS>::
    operator* () const
  {
    return m_node->getValue();
  }

  template <LIST_ITR_TEMP>
  typename list_iterator<LIST_ITR_PARAMS>::pointer
    list_iterator<LIST_ITR_PARAMS>::
    operator-> () const
  {
    return &m_node->getValue();
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>&
    list_iterator<LIST_ITR_PARAMS>::
    operator++()
  {
    m_node = m_node->getNext();
    return *this;
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>
    list_iterator<LIST_ITR_PARAMS>::
    operator++(int)
  {
    this_type tempItr(*this);
    m_node = m_node->getNext();
    return tempItr;
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>&
    list_iterator<LIST_ITR_PARAMS>::
    operator--()
  {
    // The function calls subOperation() because initially singly_linked nodes
    // were not required to have a prev() function. Now the restriction is
    // lifted and the burden falls on the implementation of the node.
    return subOperation(iterator_category());
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>
    list_iterator<LIST_ITR_PARAMS>::
    operator--(int)
  {
    // The function calls subOperation() because initially singly_linked nodes
    // were not required to have a prev() function. Now the restriction is
    // lifted and the burden falls on the implementation of the node.
    return subOperation(int(), iterator_category());
  }

  template <LIST_ITR_TEMP>
  template <typename T_Ptr2, typename T_Ref2>
  bool list_iterator<LIST_ITR_PARAMS>::
    operator==(const list_iterator
                      <T_Node, T_Itr_Type, T, T_Ptr2, T_Ref2>& a_other)
  {
    return m_node == a_other.m_node;
  }

  template <LIST_ITR_TEMP>
  template <typename T_Ptr2, typename T_Ref2>
  bool list_iterator<LIST_ITR_PARAMS>::
    operator!=(const list_iterator
                      <T_Node, T_Itr_Type, T, T_Ptr2, T_Ref2>& a_other)
  {
    return m_node != a_other.m_node;
  }

  template <LIST_ITR_TEMP>
  template <typename T_Ptr2, typename T_Ref2>
  void list_iterator<LIST_ITR_PARAMS>::
    operator=(const list_iterator
                      <T_Node, T_Itr_Type, T, T_Ptr2, T_Ref2>& a_other)
  {
    m_node = a_other.m_node;
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>&
    list_iterator<LIST_ITR_PARAMS>::
    subOperation(singly_linked_tag)
  {
    m_node = m_node->getPrev();
    return *this;
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>
    list_iterator<LIST_ITR_PARAMS>::
    subOperation(int, singly_linked_tag)
  {
    this_type tempItr(*this);
    m_node = m_node->getPrev();
    return tempItr;
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>&
    list_iterator<LIST_ITR_PARAMS>::
    subOperation(doubly_linked_tag)
  {
    m_node = m_node->getPrev();
    return *this;
  }

  template <LIST_ITR_TEMP>
  list_iterator<LIST_ITR_PARAMS>
    list_iterator<LIST_ITR_PARAMS>::
    subOperation(int, doubly_linked_tag)
  {
    this_type tempItr(*this);
    m_node = m_node->getPrev();
    return tempItr;
  }

  //////////////////////////////////////////////////////////////////////////
  // Detail

  namespace detail
  {
    template <typename T_InputItr>
    typename iterator_traits<T_InputItr>::difference_type
      distance(T_InputItr aBegin, T_InputItr aEnd, random_access_iterator_tag)
    {
      TLOC_ASSERT_ITERATOR(aBegin <= aEnd, "Invalid iterator range!");

      return aEnd - aBegin;
    }

    template <typename T_InputItr>
    typename iterator_traits<T_InputItr>::difference_type
      distance(T_InputItr aBegin, T_InputItr aEnd, input_iterator_tag)
    {
      typename iterator_traits<T_InputItr>::difference_type dist = 0;
      while (aBegin != aEnd)
      {
        ++aBegin;
        ++dist;
      }

      return dist;
    }

    template <typename T_InputItr, typename T_Distance>
    void advance( T_InputItr& aItr, T_Distance aN, input_iterator_tag )
    {
      TLOC_ASSERT_ITERATOR(aN >= 0,
        "Iterator can only advance in the positive direction!");

      while (aN) { ++aItr; --aN; }
    }

    template <typename T_InputItr, typename T_Distance>
    void advance( T_InputItr& aItr, T_Distance aN, bidirectional_iterator_tag )
    {
      if (aN > 0)
      {
        while (aN) { ++aItr; --aN; }
      }
      else
      {
        while (aN) { ++aItr; ++aN; }
      }
    }

    template <typename T_InputItr, typename T_Distance>
    void advance( T_InputItr& aItr, T_Distance aN, random_access_iterator_tag )
    {
      aItr = aItr + aN;
    }
  };

};};

#endif
