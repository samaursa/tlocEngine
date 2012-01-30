#ifndef TLOC_FORWARD_LIST_INL
#define TLOC_FORWARD_LIST_INL

#ifndef TLOC_FORWARD_LIST_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Template Macros
  
#define FORWARD_LIST_TYPES typename T, typename T_Container
#define FORWARD_LIST_PARAMS T, T_Container

  //----------------------------------------------------------------------------
  // Ctors

  template <FORWARD_LIST_TYPES>
  TL_FI ForwardListT<FORWARD_LIST_PARAMS>::ForwardListT()
    : m_container()
  {
  }

  template <FORWARD_LIST_TYPES>
  TL_FI ForwardListT<FORWARD_LIST_PARAMS>::ForwardListT(size_type aCount, 
                                                      const T& value /* = T */)
                                                      : m_container(aCount, value)
  {
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_InputIterator>
  TL_FI ForwardListT<FORWARD_LIST_PARAMS>::ForwardListT(T_InputIterator aRangeBegin, 
                                                      T_InputIterator aRangeEnd)
                                                      : m_container(aRangeBegin, 
                                                                    aRangeEnd)
  {
  }

  template <FORWARD_LIST_TYPES>
  TL_FI ForwardListT<FORWARD_LIST_PARAMS>::ForwardListT(const this_type& aOther)
    : m_container(aOther)
  {
  }

  //----------------------------------------------------------------------------
  // Assignment

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::this_type& 
    ForwardListT<FORWARD_LIST_PARAMS>::operator=(const this_type& aOther)
  {
    return m_container.operator=(aOther);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::assign(size_type aCount, 
                                                      const T& aValue)
  {
    m_container.assign(aCount, aValue);
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_InputIterator>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::assign(T_InputIterator aFirst, 
                                                      T_InputIterator aLast)
  {
    m_container.assign(aFirst, aLast);
  }

  //----------------------------------------------------------------------------
  // Element Access

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::reference 
    ForwardListT<FORWARD_LIST_PARAMS>::front()
  {
    return m_container.front();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_reference 
    ForwardListT<FORWARD_LIST_PARAMS>::front() const
  {
    return m_container.front();
  }

  //----------------------------------------------------------------------------
  // Iterators

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::before_begin()
  {
    return m_container.m_node();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::before_begin() const
  {
    return m_container.m_node();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::cbefore_begin() const
  {
    return m_container.m_node();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::begin()
  {
    return m_container.begin();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::begin() const
  {
    return m_container.begin();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::cbegin() const
  {
    return m_container.begin();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::end()
  {
    return m_container.end();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::end() const
  {
    return m_container.end();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::const_iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::cend() const
  {
    return m_container.end();
  }

  //----------------------------------------------------------------------------
  // Capacity

  template <FORWARD_LIST_TYPES>
  TL_FI bool ForwardListT<FORWARD_LIST_PARAMS>::empty() const
  {
    return m_container.empty();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::size_type 
    ForwardListT<FORWARD_LIST_PARAMS>::max_size() const
  {
    return m_container.max_size();
  }

  //----------------------------------------------------------------------------
  // Modifiers

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::clear()
  {
    m_container.clear();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::insert_after(const_iterator aPos, 
                                                   const value_type& aValue)
  {
    return m_container.insert_after(aPos, aValue);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::insert_after(const_iterator aPos, 
                                                            size_type aNumOfValues,
                                                            const value_type& aValue)
  {
    m_container.insert_after(aPos, aNumOfValues, aValue);
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_Iterator>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::insert_after(const_iterator aPos, 
                                                            T_Iterator aFirst,
                                                            T_Iterator aLast)
  {
    m_container.insert_after(aPos, aFirst, aLast);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::erase_after(const_iterator aPos)
  {
    m_container.erase_after(aPos);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI typename ForwardListT<FORWARD_LIST_PARAMS>::iterator 
    ForwardListT<FORWARD_LIST_PARAMS>::erase_after(const_iterator aFirst, 
                                                  const_iterator aLast)
  {
    m_container.erase_after(aFirst, aLast);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::push_front(const T& aValue)
  {
    m_container.push_front(aValue);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::pop_front()
  {
    m_container.pop_front();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::swap(this_type& aOther)
  {
    m_container.swap(aOther);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::merge(this_type& aOther)
  {
    m_container.merge(aOther);
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_Compare>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::merge(this_type& aOther, 
                                                     T_Compare aComp)
  {
    m_container.merge(aOther, aComp);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::splice_after(iterator aPos, 
                                                            this_type& aFrom)
  {
    m_container.splice_after(aPos, aFrom);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::splice_after(iterator aPos, 
                                                            this_type& aFrom, 
                                                            iterator aOther)
  {
    m_container.splice_after(aPos, aFrom, aOther);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::splice_after(iterator aPos, 
                                                            this_type& aFrom, 
                                                            iterator aOtherBegin, 
                                                            iterator aOtherEnd)
  {
    m_container.splice_after(aPos, aFrom, aOtherBegin, aOtherEnd);
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_Pred>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::remove_if(T_Pred aFunctionToCompare)
  {
    m_container.remove_if(aFunctionToCompare);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::reverse()
  {
    m_container.reverse();
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::unique()
  {
    m_container.unique();
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_Pred>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::unique(T_Pred aBinaryPred)
  {
    m_container.unique(aBinaryPred);
  }

  template <FORWARD_LIST_TYPES>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::sort()
  {
    m_container.sort();
  }

  template <FORWARD_LIST_TYPES>
  template <typename T_Compare>
  TL_FI void ForwardListT<FORWARD_LIST_PARAMS>::sort(T_Compare aComp)
  {
    m_container.sort(aComp);
  }

};};


#endif