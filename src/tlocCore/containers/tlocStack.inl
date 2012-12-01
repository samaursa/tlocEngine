#ifndef TLOC_STACK_INL
#define TLOC_STACK_INL

#ifndef TLOC_STACK_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/containers/tlocList.inl>

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_ASSERT_STACK_NOT_EMPTY() \
  TLOC_ASSERT_STACK(!empty(), "Stack container is empty")

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define STACK_TYPES typename T, typename T_Container
#define STACK_PARAMS T, T_Container

  //------------------------------------------------------------------------
  // Ctors

  template <STACK_TYPES>
  Stack<STACK_PARAMS>::Stack() 
    : m_container()
  {
  }

  template <STACK_TYPES>
  Stack<STACK_PARAMS>::Stack(const T_Container& aCont)
    : m_container(aCont)
  {
  }

  //------------------------------------------------------------------------
  // General

  template <STACK_TYPES>
  TL_I const T_Container& Stack<STACK_PARAMS>::_Get_container() const
  {
    return m_container;
  }

  //------------------------------------------------------------------------
  // Capacity

  template <STACK_TYPES>
  TL_I typename Stack<STACK_PARAMS>::size_type 
    Stack<STACK_PARAMS>::size() const
  {
    return m_container.size();
  }

  template <STACK_TYPES>
  TL_I bool Stack<STACK_PARAMS>::empty() const
  {
    return m_container.empty();
  }

  //------------------------------------------------------------------------
  // Element Access

  template <STACK_TYPES>
  TL_I typename Stack<STACK_PARAMS>::reference
    Stack<STACK_PARAMS>::top()
  {
    TLOC_ASSERT_STACK_NOT_EMPTY();
    return m_container.back();
  }

  template <STACK_TYPES>
  TL_I typename Stack<STACK_PARAMS>::const_reference
    Stack<STACK_PARAMS>::top() const
  {
    TLOC_ASSERT_STACK_NOT_EMPTY();
    return m_container.back();
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <STACK_TYPES>
  TL_I void Stack<STACK_PARAMS>::push(const value_type& aVal)
  {
    m_container.push_back(aVal);
  }

  template <STACK_TYPES>
  TL_I void Stack<STACK_PARAMS>::pop()
  {
    TLOC_ASSERT_STACK_NOT_EMPTY();
    m_container.pop_back();
  }

};};

#endif