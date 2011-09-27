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

  //------------------------------------------------------------------------
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

  //------------------------------------------------------------------------
  // Predefined iterators from the standard

  //````````````````````````````````````````````````````````````````````````
  // output_iterator_base

  template <typename T_Container>
  class output_iterator_base
    : public iterator<output_iterator_tag, void, void, void, void>
  {
  public:
    typedef T_Container                                    container_type;
    typedef typename T_Container::const_reference          const_reference;
    typedef typename T_Container::iterator                 iterator_type;
    typedef typename output_iterator_base<T_Container>     this_type;

    TL_FI explicit output_iterator_base(T_Container& aContainer);
    TL_FI this_type& operator* ();
    TL_FI this_type& operator++();
    TL_FI this_type& operator++(int);

  protected:

    T_Container&  m_container;

  };

  //````````````````````````````````````````````````````````````````````````
  // back_insert_iterator

  template <typename T_Container>
  class back_insert_iterator : public output_iterator_base<T_Container>
  {
  public:
    typedef typename back_insert_iterator<T_Container>     this_type;

    TL_FI explicit back_insert_iterator(T_Container& aContainer);
    TL_FI this_type& operator= (const_reference aValue);
  };

  //````````````````````````````````````````````````````````````````````````
  // front_insert_iterator

  template <typename T_Container>
  class front_insert_iterator : public output_iterator_base<T_Container>
  {
  public:
    typedef typename front_insert_iterator<T_Container>     this_type;

    TL_FI explicit front_insert_iterator (T_Container& aContainer);
    TL_FI this_type& operator=(const_reference aValue);
  };



  //````````````````````````````````````````````````````````````````````````
  // insert_iterator

  template <typename T_Container>
  class insert_iterator : public output_iterator_base<T_Container>
  {
  public:
    typedef typename insert_iterator<T_Container>     this_type;

    TL_FI explicit insert_iterator (T_Container& aContainer, iterator_type aItr);
    TL_FI this_type& operator=(const_reference aValue);
    TL_FI this_type& operator=(const insert_iterator<T_Container>& aOther);

  protected:
    typename T_Container::iterator m_itr;
  };

  //````````````````````````````````````````````````````````````````````````
  // reverse_iterator

  template <typename T_Itr>
  class reverse_iterator :
    public iterator<typename iterator_traits<T_Itr>::iterator_category,
                    typename iterator_traits<T_Itr>::value_type,
                    typename iterator_traits<T_Itr>::difference_type,
                    typename iterator_traits<T_Itr>::pointer,
                    typename iterator_traits<T_Itr>::reference>
  {
  public:
    typedef typename iterator_traits<T_Itr>::difference_type  difference_type;
    typedef typename iterator_traits<T_Itr>::pointer          pointer;
    typedef typename iterator_traits<T_Itr>::reference        reference;
    typedef reverse_iterator<T_Itr>                           this_type;

    TL_FI reverse_iterator();
    TL_FI explicit
    reverse_iterator(T_Itr aIterator);
    template <typename U>
    TL_FI reverse_iterator(const reverse_iterator<U>& aOther);

    TL_FI T_Itr             base() const;

    template <typename U>
    TL_FI this_type&        operator=   (const reverse_iterator<U>& aOther);
    TL_FI reference         operator*   () const;
    TL_FI reverse_iterator  operator+   (difference_type aDistance) const;
    TL_FI reverse_iterator& operator++  ();
    TL_FI reverse_iterator  operator++  (int);
    TL_FI reverse_iterator& operator+=  (difference_type aDistance);
    TL_FI reverse_iterator  operator-   (difference_type aDistance);
    TL_FI reverse_iterator& operator--  ();
    TL_FI reverse_iterator  operator--  (int);
    TL_FI reverse_iterator& operator-=  (difference_type aDistance);
    TL_FI pointer           operator->  () const;
    TL_FI reference         operator[]  (difference_type aDistance) const;

  protected:
    T_Itr             m_itr;

  };

  //````````````````````````````````````````````````````````````````````````
  // Global operators for reverse_iterator

  template <typename T_Itr1, typename T_Itr2>
  TL_I bool operator==(const reverse_iterator<T_Itr1>& a,
                       const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  TL_I bool operator!=(const reverse_iterator<T_Itr1>& a,
                       const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  TL_I bool operator< (const reverse_iterator<T_Itr1>& a,
                       const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  TL_I bool operator<=(const reverse_iterator<T_Itr1>& a,
                       const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  TL_I bool operator> (const reverse_iterator<T_Itr1>& a,
                       const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  TL_I bool operator>=(const reverse_iterator<T_Itr1>& a,
                       const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  TL_I typename reverse_iterator<T_Itr1>::difference_type
    operator- (const reverse_iterator<T_Itr1>& a, const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr>
  TL_I typename reverse_iterator<T_Itr>::difference_type
    operator+ (typename reverse_iterator<T_Itr>::difference_type aDistance,
               const reverse_iterator<T_Itr>& a);

  //````````````````````````````````````````````````````````````````````````
  // Iterator construction

  template <typename T_Container>
  TL_FI back_insert_iterator<T_Container> back_inserter(T_Container& aContainer);

  template <typename T_Container>
  TL_FI front_insert_iterator<T_Container> front_inserter(T_Container& aContainer);

  template <typename T_Container>
  TL_FI insert_iterator<T_Container>  inserter(T_Container& aContainer);


  //////////////////////////////////////////////////////////////////////////
  // Custom generic iterators (not defined in the standard)

  //````````````````````````````````````````````````````````````````````````
  // Macros

#define LIST_ITR_BASE_TEMP_DEF template <typename T_Node, typename T_Category, \
  typename T, typename T_Distance = tl_ptrdiff, typename T_Ptr = T*, \
  typename T_Ref = T&>

#define SINGLY_LIST_ITR_TEMP_DEF template <typename T_Node, typename T, \
  typename T_Distance = tl_ptrdiff, typename T_Ptr = T*, typename T_Ref = T&>

#define DOUBLY_LIST_ITR_TEMP_DEF template <typename T_Node, typename T, \
  typename T_Distance = tl_ptrdiff, typename T_Ptr = T*, typename T_Ref = T&>

#define LIST_ITR_BASE_TEMP template <typename T_Node, typename T_Category, \
  typename T, typename T_Distance, typename T_Ptr, typename T_Ref>

#define SINGLY_LIST_ITR_TEMP template <typename T_Node, typename T, \
    typename T_Distance, typename T_Ptr, typename T_Ref>

#define DOUBLY_LIST_ITR_TEMP template <typename T_Node, typename T, \
  typename T_Distance, typename T_Ptr, typename T_Ref>

#define LIST_ITR_BASE_TYPE ListItrBase<T_Node, T_Category, T, T_Distance, T_Ptr, T_Ref>
#define SINGLY_LIST_ITR_TYPE SinglyListItr<T_Node, T, T_Distance, T_Ptr, T_Ref>
#define DOUBLY_LIST_ITR_TYPE DoublyListItr<T_Node, T, T_Distance, T_Ptr, T_Ref>

  //````````````````````````````````````````````````````````````````````````
  // List iterator
  //
  // Allows any class to create a quick iterator for its needs that is similar
  // to a list iterator
  //
  // The iterator must have a type, a pointer to the type and a reference to
  // the type. This is to allow creation of const T* pointers as well as T*
  // from the same template.
  // T_Node: Must have public members T* m_value
  LIST_ITR_BASE_TEMP_DEF
  struct ListItrBase :
    public iterator<T_Category, T, T_Distance, T_Ptr, T_Ref>
  {
    typedef LIST_ITR_BASE_TYPE this_type;

    TL_FI ListItrBase();
    TL_FI ListItrBase(const T_Node* aNode);
    TL_FI ListItrBase(const this_type& aOtherItr);

    TL_FI T_Ref     operator*() const;
    TL_FI T_Ptr     operator->() const;

  protected:
    T_Node*   m_node;
  };

  // T_Node: Must have public members T* m_value, T_Node* m_next;
  SINGLY_LIST_ITR_TEMP_DEF
  struct SinglyListItr :
    public ListItrBase<T_Node, forward_iterator_tag, T, T_Distance, T_Ptr, T_Ref>
  {
    typedef SINGLY_LIST_ITR_TYPE this_type;

    TL_FI SinglyListItr();
    TL_FI SinglyListItr(const T_Node* aNode);
    TL_FI SinglyListItr(const this_type& aOtherItr);

    TL_FI this_type&   operator++();
    TL_FI this_type    operator++(int);
  };

  // T_Node: Must have public members T* m_value, T_Node* m_next, T Node* m_prev;
  DOUBLY_LIST_ITR_TEMP_DEF
  struct DoublyListItr :
    public ListItrBase<T_Node, bidirectional_iterator_tag, T, T_Distance, T_Ptr, T_Ref>
  {
    typedef DOUBLY_LIST_ITR_TYPE this_type;

    TL_FI DoublyListItr();
    TL_FI DoublyListItr(const T_Node* aNode);
    TL_FI DoublyListItr(const this_type& aOtherItr);

    TL_FI this_type&   operator++();
    TL_FI this_type    operator++(int);
    TL_FI this_type&   operator--();
    TL_FI this_type    operator--(int);
  };

  //////////////////////////////////////////////////////////////////////////
  // Global functions

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