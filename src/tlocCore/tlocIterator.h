#ifndef TLOC_ITERATOR_H
#define TLOC_ITERATOR_H

#include "tlocBase.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Iterators

  //````````````````````````````````````````````````````````````````````````
  // Iterator categories

  struct input_iterator_tag {};
  struct output_iterator_tag {};
  struct forward_iterator_tag : public input_iterator_tag {};
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};

  //````````````````````````````````````````````````````````````````````````
  // Base class from the standard

  template <typename T_Category, typename T, typename T_Distance = tl_ptrdiff,
            typename T_Ptr = T*, typename T_Ref = T&>
  struct iterator
  {
    typedef T           value_type;
    typedef T_Distance  difference_type;
    typedef T_Ptr       pointer;
    typedef T_Ref       reference;
    typedef T_Category  iterator_category;
  };

  //````````````````````````````````````````````````````````````````````````
  // Predefined iterators from the standard

  //struct tlBackInsertIterator

  //````````````````````````````````````````````````````````````````````````
  // List iterator
  //
  // Allows any class to create a quick iterator for its needs that is similar
  // to a list iterator
  //
  // The iterator must have a type, a pointer to the type and a reference to
  // the type. This is to allow creation of const T* pointers as well as T*
  // from the same template.
  // T_Node: Must have public members T* m_value, T_Node* m_next, T Node* m_prev;
  template <typename T_Node, typename T, typename T_Ptr = T*,
            typename T_Ref = T&, typename T_Distance = tl_ptrdiff>
  struct ListIterator : public iterator<forward_iterator_tag, T, T_Distance, T_Ptr, T_Ref>
  {
    typedef ListIterator<T, T_Ptr, T_Ref, T_Node> ForwardItrT;

    ListIterator* m_next;

    ListIterator();
    ListIterator(const T_Node* aNode);
    ListIterator(const ForwardItrT& aOtherItr);

    T_Ref            operator*() const;
    T_Ptr            operator->() const;

    ForwardItrT&     operator++();
    ForwardItrT      operator++(int);

    ForwardItrT&     operator--();
    ForwardItrT      operator--(int);
  };

  //////////////////////////////////////////////////////////////////////////
  // Free functions

  template <typename T_InputItr>
  tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd);

  namespace detail
  {
    typedef type_true   IsPtrItr;
    typedef type_false  IsComplexItr;

    template <typename T_InputItr>
    tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd, IsPtrItr);

    template <typename T_InputItr>
    tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd, IsComplexItr);
  };
};

#include "tlocIterator.inl"

#endif