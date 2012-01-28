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
    return List::operator=(aOther);
  }

  template <typename T>
  TL_FI void ForwardList<T>::assign(size_type aCount, const T& aValue)
  {
    List::assign(aCount, aValue);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_FI void ForwardList<T>::assign(T_InputIterator aFirst, T_InputIterator aLast)
  {
    List::assign(aFirst, aLast);
  }

  //----------------------------------------------------------------------------
  // Element Access

  template <typename T>
  TL_FI typename ForwardList<T>::reference ForwardList<T>::front()
  {
    return List::front();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_reference ForwardList<T>::front() const
  {
    return List::front();
  }

  //----------------------------------------------------------------------------
  // Iterators

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::before_begin()
  {
    return List::m_node();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::before_begin() const
  {
    return List::m_node();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::cbefore_begin() const
  {
    return List::m_node();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::begin()
  {
    return List::begin();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::begin() const
  {
    return List::begin();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const
  {
    return List::begin();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::end()
  {
    return List::end();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::end() const
  {
    return List::end();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::const_iterator ForwardList<T>::cend() const
  {
    return List::end();
  }

  //----------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_FI bool ForwardList<T>::empty() const
  {
    return List::empty();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::size_type ForwardList<T>::max_size() const
  {
    return List::max_size();
  }

  //----------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_FI void ForwardList<T>::clear()
  {
    List::clear();
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator 
    ForwardList<T>::insert_after(const_iterator aPos, const value_type& aValue)
  {
    return List::insert_after(aPos, aValue);
  }

  template <typename T>
  TL_FI void ForwardList<T>::insert_after(const_iterator aPos, size_type aNumOfValues,
                                          const value_type& aValue)
  {
    List::insert_after(aPos, aNumOfValues, aValue);
  }

  template <typename T>
  template <typename T_Iterator>
  TL_FI void ForwardList<T>::insert_after(const_iterator aPos, T_Iterator aFirst,
                                          T_Iterator aLast)
  {
    List::insert_after(aPos, aFirst, aLast);
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator aPos)
  {
    List::erase_after(aPos);
  }

  template <typename T>
  TL_FI typename ForwardList<T>::iterator 
    ForwardList<T>::erase_after(const_iterator aFirst, const_iterator aLast)
  {
    List::erase_after(aFirst, aLast);
  }

  template <typename T>
  TL_FI void ForwardList<T>::push_front(const T& aValue)
  {
    List::push_front(aValue);
  }

};};


#endif