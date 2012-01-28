#ifndef TLOC_FORWARD_LIST_INL
#define TLOC_FORWARD_LIST_INL

#ifndef TLOC_FORWARD_LIST_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {

  //----------------------------------------------------------------------------
  // Ctors

  template <typename T>
  TL_FI ForwardList<T>::ForwardList()
    : List()
  {
  }

  template <typename T>
  TL_FI ForwardList<T>::ForwardList(size_type aCount, const T& value /* = T */)
    : List(aCount, value)
  {
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_FI ForwardList<T>::ForwardList(T_InputIterator aRangeBegin, 
                                             T_InputIterator aRangeEnd)
                                             : List(aRangeBegin, aRangeEnd)
  {
  }

  template <typename T>
  TL_FI ForwardList<T>::ForwardList(const typename ForwardList::this_type& aOther)
    : List(aOther)
  {
  }

  //----------------------------------------------------------------------------
  // Assignment

  template <typename T>
  TL_FI typename ForwardList<T>::this_type& 
    ForwardList<T>::operator=(const this_type& aOther)
  {
    return this_type::operator=(aOther);
  }

  template <typename T>
  TL_FI void ForwardList<T>::assign(size_type aCount, const T& aValue)
  {
    this_type::assign(aCount, aValue);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_FI void ForwardList<T>::assign(T_InputIterator aFirst, T_InputIterator aLast)
  {
    this_type::assign(aFirst, aLast);
  }

  //----------------------------------------------------------------------------
  // Element Access

  template <typename T>
  TL_FI typename ForwardList<T>::reference ForwardList<T>::front()
  {
    return this_type::front();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_reference ForwardList<T>::front() const
  {
    return this_type::front();
  }

  //----------------------------------------------------------------------------
  // Iterators

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::before_begin()
  {
    return this_type::m_node();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::before_begin() const
  {
    return this_type::m_node();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::cbefore_begin() const
  {
    return this_type::m_node();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::begin()
  {
    return this_type::begin();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::begin() const
  {
    return this_type::begin();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const
  {
    return this_type::begin();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::end()
  {
    return this_type::end();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::end() const
  {
    return this_type::end();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::cend() const
  {
    return this_type::end();
  }

  //----------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_FI bool ForwardList<T>::empty() const
  {
    return this_type::empty();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::size_type ForwardList<T>::max_size() const
  {
    return this_type::max_size();
  }

  //----------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_FI void ForwardList<T>::clear()
  {
    this_type::clear();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator 
    ForwardList<T>::insert_after(const_iterator aPos, const value_type& aValue)
  {
    return this_type::insert_after(aPos, aValue);
  }

  template <typename T>
  TL_FI void ForwardList<T>::insert_after(const_iterator aPos, size_type aNumOfValues,
                                          const value_type& aValue)
  {
    this_type::insert_after(aPos, aNumOfValues, aValue);
  }

  template <typename T>
  template <typename T_Iterator>
  TL_FI void ForwardList<T>::insert_after(const_iterator aPos, T_Iterator aFirst,
                                          T_Iterator aLast)
  {
    this_type::insert_after(aPos, aFirst, aLast);
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator aPos)
  {
    this_type::erase_after(aPos);
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator 
    ForwardList<T>::erase_after(const_iterator aFirst, const_iterator aLast)
  {
    this_type::erase_after(aFirst, aLast);
  }

  template <typename T>
  TL_FI void ForwardList<T>::push_front(const T& aValue)
  {
    this_type::push_front(aValue);
  }

  template <typename T>
  TL_FI void ForwardList<T>::pop_front()
  {
    this_type::pop_front();
  }

  template <typename T>
  TL_FI void ForwardList<T>::swap(this_type& aOther)
  {
    this_type::swap(aOther);
  }

  template <typename T>
  TL_FI void ForwardList<T>::merge(this_type& aOther)
  {
    this_type::merge(aOther);
  }

  template <typename T>
  template <typename T_Compare>
  TL_FI void ForwardList<T>::merge(this_type& aOther, T_Compare aComp)
  {
    this_type::merge(aOther, aComp);
  }

  template <typename T>
  TL_FI void ForwardList<T>::splice_after(iterator aPos, this_type& aFrom)
  {
    this_type::splice_after(aPos, aFrom);
  }

  template <typename T>
  TL_FI void ForwardList<T>::splice_after(iterator aPos, this_type& aFrom, 
                                          iterator aOther)
  {
    this_type::splice_after(aPos, aFrom, aOther);
  }

  template <typename T>
  TL_FI void ForwardList<T>::splice_after(iterator aPos, this_type& aFrom, 
                                          iterator aOtherBegin, 
                                          iterator aOtherEnd)
  {
    this_type::splice_after(aPos, aFrom, aOtherBegin, aOtherEnd);
  }

  template <typename T>
  template <typename T_Pred>
  TL_FI void ForwardList<T>::remove_if(T_Pred aFunctionToCompare)
  {
    this_type::remove_if(aFunctionToCompare);
  }

  template <typename T>
  TL_FI void ForwardList<T>::reverse()
  {
    this_type::reverse();
  }

  template <typename T>
  TL_FI void ForwardList<T>::unique()
  {
    this_type::unique();
  }

  template <typename T>
  template <typename T_Pred>
  TL_FI void ForwardList<T>::unique(T_Pred aBinaryPred)
  {
    this_type::unique(aBinaryPred);
  }

  template <typename T>
  TL_FI void ForwardList<T>::sort()
  {
    this_type::sort();
  }

  template <typename T>
  template <typename T_Compare>
  TL_FI void ForwardList<T>::sort(T_Compare aComp)
  {
    this_type::sort(aComp);
  }

};};


#endif