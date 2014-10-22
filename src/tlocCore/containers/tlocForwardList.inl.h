#ifndef TLOC_FORWARD_LIST_INL
#define TLOC_FORWARD_LIST_INL

#ifndef TLOC_FORWARD_LIST_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/containers/tlocList.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define TLOC_FORWARD_LIST_TYPES  typename T, typename T_Container
#define TLOC_FORWARD_LIST_PARAMS T, T_Container
#define TLOC_FORWARD_LIST_TYPE   typename ForwardListT<TLOC_FORWARD_LIST_PARAMS>

  //----------------------------------------------------------------------------
  // Ctors

  template <TLOC_FORWARD_LIST_TYPES>
  ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    ForwardListT()
    : m_container()
  {
  }

  template <TLOC_FORWARD_LIST_TYPES>
  ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    ForwardListT(size_type aCount,
                                                        const T& value /* = T */)
    : m_container(aCount, value)
  {
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_InputIterator>
  ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    ForwardListT(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd)
    : m_container(aRangeBegin, aRangeEnd)
  {
  }

  template <TLOC_FORWARD_LIST_TYPES>
  ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    ForwardListT(const this_type& aOther)
    : m_container(aOther.m_container)
  {
  }

  //----------------------------------------------------------------------------
  // General

  template <TLOC_FORWARD_LIST_TYPES>
  const T_Container&
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    DoGetContainer() const
  {
    return m_container;
  }

  //----------------------------------------------------------------------------
  // Assignment

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    assign(size_type aCount, const T& aValue)
  {
    m_container.assign(aCount, aValue);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_InputIterator>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    assign(T_InputIterator aFirst, T_InputIterator aLast)
  {
    m_container.assign(aFirst, aLast);
  }

  //----------------------------------------------------------------------------
  // Element Access

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::reference
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    front()
  {
    return m_container.front();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_reference
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    front() const
  {
    return m_container.front();
  }

  //----------------------------------------------------------------------------
  // Iterators

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    before_begin()
  {
    return m_container.end();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    before_begin() const
  {
    return m_container.cend();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    cbefore_begin() const
  {
    return before_begin();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    begin()
  {
    return m_container.begin();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    begin() const
  {
    return m_container.begin();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    cbegin() const
  {
    return m_container.begin();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    end()
  {
    return m_container.end();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    end() const
  {
    return m_container.end();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::const_iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    cend() const
  {
    return m_container.end();
  }

  //----------------------------------------------------------------------------
  // Capacity

  template <TLOC_FORWARD_LIST_TYPES>
  bool 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    empty() const
  {
    return m_container.empty();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::size_type
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    max_size() const
  {
    return m_container.max_size();
  }

  //----------------------------------------------------------------------------
  // Modifiers

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    clear()
  {
    m_container.clear();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    insert_after(iterator aPos, const value_type& aValue)
  {
    return m_container.insert_after(aPos, aValue);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    insert_after(iterator aPos, size_type aNumOfValues, const value_type& aValue)
  {
    m_container.insert_after(aPos, aNumOfValues, aValue);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_Iterator>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    insert_after(iterator aPos, T_Iterator aFirst, T_Iterator aLast)
  {
    m_container.insert_after(aPos, aFirst, aLast);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    erase_after(iterator aPos)
  {
    return m_container.erase_after(aPos);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  TLOC_FORWARD_LIST_TYPE::iterator
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    erase_after(iterator aFirst, iterator aLast)
  {
    return m_container.erase_after(aFirst, aLast);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    push_front(const T& aValue)
  {
    m_container.push_front(aValue);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    pop_front()
  {
    m_container.pop_front();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    swap(this_type& aOther)
  {
    m_container.swap(aOther.m_container);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    merge(this_type& aOther)
  {
    m_container.merge(aOther.m_container);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_Compare>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    merge(this_type& aOther, T_Compare aComp)
  {
    m_container.merge(aOther.m_container, aComp);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    splice_after(iterator aPos, this_type& aFrom)
  {
    m_container.splice_after(aPos, aFrom.m_container);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    splice_after(iterator aPos, this_type& aFrom, iterator aOther)
  {
    m_container.splice_after(aPos, aFrom.m_container, aOther);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    splice_after(iterator aPos, this_type& aFrom, 
                 iterator aOtherBegin, iterator aOtherEnd)
  {
    m_container.splice_after(aPos, aFrom.m_container, aOtherBegin, aOtherEnd);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_Pred>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    remove_if(T_Pred aFunctionToCompare)
  {
    m_container.remove_if(aFunctionToCompare);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    reverse()
  {
    m_container.reverse();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    unique()
  {
    m_container.unique();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_Pred>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    unique(T_Pred aBinaryPred)
  {
    m_container.unique(aBinaryPred);
  }

  template <TLOC_FORWARD_LIST_TYPES>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    sort()
  {
    m_container.sort();
  }

  template <TLOC_FORWARD_LIST_TYPES>
  template <typename T_Compare>
  void 
    ForwardListT<TLOC_FORWARD_LIST_PARAMS>::
    sort(T_Compare aComp)
  {
    m_container.sort(aComp);
  }

};};};


#endif