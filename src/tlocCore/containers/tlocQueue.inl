#ifndef TLOC_QUEUE_INL
#define TLOC_QUEUE_INL

#ifndef TLOC_QUEUE_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/containers/tlocList.inl>

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_ASSERT_QUEUE_NOT_EMPTY() \
  TLOC_ASSERT_QUEUE(!empty(), "Queue container is empty!")

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define QUEUE_TYPES typename T, typename T_Container
#define QUEUE_PARAMS T, T_Container

  //------------------------------------------------------------------------
  // Ctors

  template <QUEUE_TYPES>
  Queue<QUEUE_PARAMS>::Queue()
    : m_container()
  {
  }

  template <QUEUE_TYPES>
  Queue<QUEUE_PARAMS>::Queue(const T_Container& aCont)
    : m_container(aCont)
  {
  }

  //------------------------------------------------------------------------
  // Capacity

  template <QUEUE_TYPES>
  TL_I typename Queue<QUEUE_PARAMS>::size_type
    Queue<QUEUE_PARAMS>::size() const
  {
    return m_container.size();
  }

  template <QUEUE_TYPES>
  TL_I bool Queue<QUEUE_PARAMS>::empty() const
  {
    return m_container.empty();
  }

  //------------------------------------------------------------------------
  // Element Access

  template <QUEUE_TYPES>
  TL_I typename Queue<QUEUE_PARAMS>::reference
    Queue<QUEUE_PARAMS>::front()
  {
    TLOC_ASSERT_QUEUE_NOT_EMPTY();
    return m_container.front();
  }

  template <QUEUE_TYPES>
  TL_I typename Queue<QUEUE_PARAMS>::const_reference
    Queue<QUEUE_PARAMS>::front() const
  {
    TLOC_ASSERT_QUEUE_NOT_EMPTY();
    return m_container.front();
  }

  template <QUEUE_TYPES>
  TL_I typename Queue<QUEUE_PARAMS>::reference
    Queue<QUEUE_PARAMS>::back()
  {
    TLOC_ASSERT_QUEUE_NOT_EMPTY();
    return m_container.back();
  }

  template <QUEUE_TYPES>
  TL_I typename Queue<QUEUE_PARAMS>::const_reference
    Queue<QUEUE_PARAMS>::back() const
  {
    TLOC_ASSERT_QUEUE_NOT_EMPTY();
    return m_container.back();
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <QUEUE_TYPES>
  TL_I void Queue<QUEUE_PARAMS>::push(const value_type& aVal)
  {
    m_container.push_back(aVal);
  }

  template <QUEUE_TYPES>
  TL_I void Queue<QUEUE_PARAMS>::pop()
  {
    TLOC_ASSERT_QUEUE_NOT_EMPTY();
    m_container.pop_front();
  }

};};};

#endif
