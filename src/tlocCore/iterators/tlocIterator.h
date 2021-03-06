#ifndef TLOC_ITERATOR_H
#define TLOC_ITERATOR_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>

#ifndef TLOC_DISABLE_ASSERT_ITERATOR
# define TLOC_ASSERT_ITERATOR(_Expression, _Msg) TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_ITERATOR(_Expression, _Msg)
#endif

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // Standard begin/end functions that work on raw/complex containers

  template <class T_Container>
  typename T_Container::iterator
    begin(T_Container& a_container) { return a_container.begin(); }

  template <class T_Container>
  typename T_Container::iterator
    begin(const T_Container& a_container) { return a_container.begin(); }

  template <class T, tl_size T_Size>
  T* begin(T (&a_array)[T_Size]) { return a_array; }

  template <class T, tl_size T_Size>
  T* begin(const T (&a_array)[T_Size]) { return a_array; }

  template <class T_Container>
  typename T_Container::iterator
    end(T_Container& a_container) { return a_container.end(); }

  template <class T_Container>
  typename T_Container::iterator
    end(const T_Container& a_container) { return a_container.end(); }

  template <class T, tl_size T_Size>
  T* end(T (&a_array)[T_Size]) { return a_array + T_Size; }

  template <class T, tl_size T_Size>
  T* end(const T (&a_array)[T_Size]) { return a_array + T_Size; }

  //////////////////////////////////////////////////////////////////////////
  // Iterators

  //````````````````````````````````````````````````````````````````````````
  // Iterator categories

  struct input_iterator_tag {};
  struct output_iterator_tag {};
  struct forward_iterator_tag : public input_iterator_tag {};
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};
  struct singly_linked_tag : public forward_iterator_tag {};
  struct doubly_linked_tag : public bidirectional_iterator_tag {};

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
  // back_insert_iterator

  template <typename T_Container>
  class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
  {
  public:
    typedef T_Container                                    container_type;
    typedef typename T_Container::const_reference          const_reference;
    typedef typename T_Container::iterator                 iterator_type;
    typedef back_insert_iterator<T_Container>              this_type;

    explicit back_insert_iterator(T_Container& aContainer);
    this_type& operator* ();
    this_type& operator++();
    this_type& operator++(int);
    this_type& operator= (const_reference aValue);

  protected:
    T_Container* m_container;
  };

  template <typename T_Container>
  back_insert_iterator<T_Container>
    MakeBackInsertIterator(T_Container& a_container)
  { return back_insert_iterator<T_Container>(a_container); }

  //````````````````````````````````````````````````````````````````````````
  // front_insert_iterator

  template <typename T_Container>
  class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
  {
  public:
    typedef T_Container                                    container_type;
    typedef typename T_Container::const_reference          const_reference;
    typedef typename T_Container::iterator                 iterator_type;
    typedef front_insert_iterator<T_Container>             this_type;

    explicit front_insert_iterator (T_Container& aContainer);
    this_type& operator* ();
    this_type& operator++();
    this_type& operator++(int);
    this_type& operator=(const_reference aValue);
    this_type& operator=(const this_type& aOther);

  protected:
    T_Container& m_container;
  };

  template <typename T_Container>
  front_insert_iterator<T_Container>
    MakeFrontInsertIterator(T_Container& a_container)
  { return front_insert_iterator<T_Container>(a_container); }


  //````````````````````````````````````````````````````````````````````````
  // insert_iterator

  template <typename T_Container>
  class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
  {
  public:
    typedef T_Container                                    container_type;
    typedef typename T_Container::const_reference          const_reference;
    typedef typename T_Container::iterator                 iterator_type;
    typedef insert_iterator<T_Container>                   this_type;

    explicit insert_iterator (T_Container& aContainer, iterator_type aItr);
    this_type& operator* ();
    this_type& operator++();
    this_type& operator++(int);
    this_type& operator=(const_reference aValue);
    this_type& operator=(const insert_iterator<T_Container>& aOther);

  protected:
    T_Container&                    m_container;
    typename T_Container::iterator  m_itr;
  };

  template <typename T_Container, typename T_IteratorType>
  insert_iterator<T_Container>
    MakeInsertIterator(T_Container& a_container, T_IteratorType a_itr)
  { return insert_iterator<T_Container>(a_container, a_itr); }

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

    reverse_iterator();
    explicit
    reverse_iterator(T_Itr aIterator);
    template <typename U>
    reverse_iterator(const reverse_iterator<U>& aOther);

    T_Itr             base() const;

    template <typename U>
    this_type&        operator=   (const reverse_iterator<U>& aOther);
    reference         operator*   () const;
    reverse_iterator  operator+   (difference_type aDistance) const;
    reverse_iterator& operator++  ();
    reverse_iterator  operator++  (int);
    reverse_iterator& operator+=  (difference_type aDistance);
    reverse_iterator  operator-   (difference_type aDistance);
    reverse_iterator& operator--  ();
    reverse_iterator  operator--  (int);
    reverse_iterator& operator-=  (difference_type aDistance);
    pointer           operator->  () const;
    reference         operator[]  (difference_type aDistance) const;

  protected:
    T_Itr             m_itr;

  };

  //````````````````````````````````````````````````````````````````````````
  // Global operators for reverse_iterator

  template <typename T_Itr1, typename T_Itr2>
  bool operator==(const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  bool operator!=(const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  bool operator< (const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  bool operator<=(const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  bool operator> (const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  bool operator>=(const reverse_iterator<T_Itr1>& a,
                  const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr1, typename T_Itr2>
  typename reverse_iterator<T_Itr1>::difference_type
    operator- (const reverse_iterator<T_Itr1>& a,
               const reverse_iterator<T_Itr2>& b);

  template <typename T_Itr>
  typename reverse_iterator<T_Itr>::difference_type
    operator+ (typename reverse_iterator<T_Itr>::difference_type aDistance,
               const reverse_iterator<T_Itr>& a);

  //````````````````````````````````````````````````````````````````````````
  // Iterator construction

  template <typename T_Container>
  back_insert_iterator<T_Container> back_inserter(T_Container& aContainer);

  template <typename T_Container>
  front_insert_iterator<T_Container> front_inserter(T_Container& aContainer);

  template <typename T_Container>
  insert_iterator<T_Container>  inserter(T_Container& aContainer);


  //////////////////////////////////////////////////////////////////////////
  // Custom generic iterators (not defined in the standard)

  // TODO: Clean this up to take one bool value instead of 3 different types

  //````````````````````````````````````````````````````````````````````````
  // List iterator
  //
  // Allows any class to create a quick iterator for its needs that is similar
  // to a list iterator
  //
  // The iterator must have a type, a pointer to the type and a reference to
  // the type. This is to allow creation of const T* pointers as well as T*
  // from the same template.
  //
  // T_Itr_Type: Can be singly_linked_tag or doubly_linked_tag
  //
  // T_Node: Must have public members T* m_value, T_Node* m_next, T_Node* m_prev
  //         Must also have: typedef tl_ptrdiff difference_type;
  template <typename T_Node, typename T_Itr_Type, typename T,
            typename T_Ptr = T*, typename T_Ref = T&>
  struct list_iterator :
    public iterator<T_Itr_Type, T, typename T_Node::difference_type,
                    T_Ptr, T_Ref>
  {
    typedef T_Ptr                                      pointer;
    typedef T_Ref                                      reference;

    typedef list_iterator<T_Node, T_Itr_Type, T, T_Ptr, T_Ref>  this_type;
    typedef list_iterator<T_Node, T_Itr_Type, T, T*, T&>        iterator;
    typedef T_Itr_Type                                 iterator_category;

    list_iterator();
    list_iterator(const T_Node* aNode);
    list_iterator(const iterator& aOtherItr);
    //template <typename T_Ptr2, typename T_Ref2>
    //list_iterator(const list_iterator<T_Node, T_Itr_Type, T, T_Ptr2, T_Ref2>& a_other);

    reference       operator*() const;
    pointer         operator->() const;
    this_type&      operator++();
    this_type       operator++(int);
    this_type&      operator--();
    this_type       operator--(int);
    template <typename T_Ptr2, typename T_Ref2>
    bool            operator==(const list_iterator<T_Node, T_Itr_Type, T,
                                                   T_Ptr2, T_Ref2>& a_other);
    template <typename T_Ptr2, typename T_Ref2>
    bool            operator!=(const list_iterator<T_Node, T_Itr_Type, T,
                                                   T_Ptr2, T_Ref2>& a_other);

    template <typename T_Ptr2, typename T_Ref2>
    void            operator=
      (const list_iterator<T_Node, T_Itr_Type, T, T_Ptr2, T_Ref2>& a_other);

    T_Node*               m_node;

  protected:
    this_type&      subOperation(singly_linked_tag);
    this_type       subOperation(int, singly_linked_tag);
    this_type&      subOperation(doubly_linked_tag);
    this_type       subOperation(int, doubly_linked_tag);
  };

  template <typename T_Node, typename T, typename T_Ptr, typename T_Ref,
  typename T_ConstPtr, typename T_ConstRef>
  bool operator==(const list_iterator<T_Node, T, T_Ptr, T_Ref>& a,
                  const list_iterator<T_Node, T, T_ConstPtr, T_ConstRef>& b)
  {
    return a.m_node == b.m_node;
  }

  //////////////////////////////////////////////////////////////////////////
  // Global functions

  template <typename T_InputItr>
  typename iterator_traits<T_InputItr>::difference_type
    distance(T_InputItr aBegin, T_InputItr aEnd);

  template <typename T_InputItr, typename T_Distance>
  void advance(T_InputItr& aItr, T_Distance aN);

  namespace detail
  {
    template <typename T_InputItr>
    typename iterator_traits<T_InputItr>::difference_type
      distance(T_InputItr aBegin, T_InputItr aEnd, random_access_iterator_tag);

    template <typename T_InputItr>
    typename iterator_traits<T_InputItr>::difference_type
      distance(T_InputItr aItr, T_InputItr aEnd, input_iterator_tag);

    template <typename T_InputItr, typename T_Distance>
    void advance(T_InputItr& aItr, T_Distance aN, input_iterator_tag);

    template <typename T_InputItr, typename T_Distance>
    void advance(T_InputItr& aItr, T_Distance aN, bidirectional_iterator_tag);

    template <typename T_InputItr, typename T_Distance>
    void advance(T_InputItr& aItr, T_Distance aN, random_access_iterator_tag);
  };

};};

#endif
