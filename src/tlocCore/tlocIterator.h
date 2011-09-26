#ifndef TLOC_ITERATOR_H
#define TLOC_ITERATOR_H

#include "tlocBase.h"

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ITERATOR(_Expression, _Msg) TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_ITERATOR(_Expression, _Msg)
#endif

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
  // Iterator traits (from the standard)

  template <typename T_Itr>
  struct iterator_traits
  {
    typedef typename T_Itr::difference_type     difference_type;
    typedef typename T_Itr::value_type          value_type;
    typedef typename T_Itr::pointer             pointer;
    typedef typename T_Itr::reference           reference;
    typedef typename T_Itr::iterator_category   iterator_category;
  };

  template <typename T>
  struct iterator_traits<T*>
  {
    typedef tl_ptrdiff                          difference_type;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef random_access_iterator_tag          iterator_category;
  };

  template <typename T>
  struct iterator_traits<const T*>
  {
    typedef tl_ptrdiff                          difference_type;
    typedef T                                   value_type;
    typedef const T*                            pointer;
    typedef const T&                            reference;
    typedef random_access_iterator_tag          iterator_category;
  };

  //````````````````````````````````````````````````````````````````````````
  // Predefined iterators from the standard

  template <typename T_Container>
  class back_insert_iterator :
    public iterator<output_iterator_tag, void, void, void, void>
  {
  public:
    typedef T_Container                       container_type;
    typedef back_insert_iterator<T_Container> this_type;

    explicit back_insert_iterator(T_Container& aContainer);
    this_type& operator= (typename T_Container::const_reference aValue);
    this_type& operator* ();
    this_type& operator++();
    this_type& operator++(int);

  protected:
    T_Container* m_container;
  };

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
  TL_FI tl_size distance(T_InputItr aBegin, T_InputItr aEnd);

  template <typename T_InputItr, typename T_Distance>
  TL_FI void advance(T_InputItr aBegin, T_Distance aN);

  namespace detail
  {
    typedef type_true   IsPtrItr;
    typedef type_false  IsComplexItr;

    template <typename T_InputItr>
    TL_FI tl_size distance(T_InputItr aBegin, T_InputItr aEnd, IsPtrItr);

    template <typename T_InputItr>
    TL_FI tl_size distance(T_InputItr aItr, T_InputItr aEnd, IsComplexItr);

    template <typename T_InputItr, typename T_Distance>
    TL_FI void advance(T_InputItr aItr, T_Distance aN, input_iterator_tag);

    template <typename T_InputItr, typename T_Distance>
    TL_FI void advance(T_InputItr aItr, T_Distance aN, bidirectional_iterator_tag);

    template <typename T_InputItr, typename T_Distance>
    TL_FI void advance(T_InputItr aItr, T_Distance aN, random_access_iterator_tag);
  };
};

#include "tlocIterator.inl"

#endif