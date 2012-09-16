#ifndef TLOC_ALGORITHMS_INL
#define TLOC_ALGORITHMS_INL

#ifndef TLOC_ALGORITHMS_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocPair.inl>
#include <tlocCore/iterators/tlocIterator.inl>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/RNGs/tlocRandom.h>
#include <tlocCore/tlocFunctional.h>

namespace tloc { namespace core {

  // TODO: Make all find functions specialized for char* and use memcmp

  //------------------------------------------------------------------------
  // Range verifier - only works on raw iterators, ignores complex iterators 

  template <typename T_Iterator>
  void TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(T_Iterator a_begin, T_Iterator a_end)
  {
    typedef typename Loki::Int2Type<Loki::TypeTraits<T_Iterator>::isPointer> itr_type;
    detail::DoVerifyRange(a_begin, a_end, itr_type());
  }

  //------------------------------------------------------------------------
  // Non-modifying sequence operations

  template <typename T_Container, typename T_Function>
  T_Function for_each_all(T_Container a_container, T_Function a_func)
  {
    return for_each(a_container.begin(), a_container.end(), a_func);
  }

  template <typename T_InputIterator, typename T_Function>
  T_Function for_each( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                       T_Function aFunc )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    const tl_size rangeSize = distance(a_rangeBegin, a_rangeEnd);

    for (u32 i = 0; i < rangeSize; ++i)
    {
      aFunc(*a_rangeBegin);
      ++a_rangeBegin;
    }

    return aFunc;
  }

  template <typename T_Container, typename T>
  typename T_Container::iterator 
    find_all(T_Container& a_container, const T& a_value)
  {
    return find(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_Container, typename T>
  typename T_Container::const_iterator 
    find_all(const T_Container& a_container, const T& a_value)
  {
    return find(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_InputIterator, typename T>
  T_InputIterator find( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                        const T& a_value )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef typename Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef typename Loki::Int2Type<charTestResult::value> IsChar8;

    return detail::DoFind(a_rangeBegin, a_rangeEnd, a_value, IsChar8());
  }

  template <typename T_Container, typename T_Predicate>
  typename T_Container::iterator find_if(T_Container a_container, 
                                         const T_Predicate& a_pred)
  {
    return find_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator find_if( T_InputIterator a_rangeBegin,
                           T_InputIterator a_rangeEnd, T_Predicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (a_pred(*a_rangeBegin)) break;
      ++a_rangeBegin;
    }

    return a_rangeBegin;
  }


  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_end( T_ForwardIterator1 a_rangeToSearchBegin,
                               T_ForwardIterator1 a_rangeToSearchEnd,
                               T_ForwardIterator2 a_rangeToFindBegin,
                               T_ForwardIterator2 a_rangeToFindEnd )
  {
    return find_end(a_rangeToSearchBegin, a_rangeToSearchEnd, a_rangeToFindBegin, 
      a_rangeToFindEnd, equal_to<iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
  T_ForwardIterator1 find_end( T_ForwardIterator1 a_rangeToSearchBegin,
                               T_ForwardIterator1 a_rangeToSearchEnd,
                               T_ForwardIterator2 a_rangeToFindBegin,
                               T_ForwardIterator2 a_rangeToFindEnd,
                               T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);
    const tl_size compareSize = distance(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator1 retItr = a_rangeToSearchEnd;

    if (sourceSize >= compareSize)
    {
      T_ForwardIterator1 sourceItr;
      T_ForwardIterator2 compareItr;
      T_ForwardIterator1 sourceLimit = a_rangeToSearchEnd - compareSize + 1;

      while (a_rangeToSearchBegin != sourceLimit)
      {
        sourceItr = a_rangeToSearchBegin;
        compareItr = a_rangeToFindBegin;
        while (compareItr != a_rangeToFindEnd)
        {
          if (!a_pred(*sourceItr, *compareItr)) { break; }
          ++compareItr;
          ++sourceItr;
        }

        if (compareItr == a_rangeToFindEnd)
        {
          retItr = a_rangeToSearchBegin;
        }

        ++a_rangeToSearchBegin;
      }
    }

    return retItr;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                    T_ForwardIterator1 a_rangeToSearchEnd,
                                    T_ForwardIterator2 a_rangeToFindBegin,
                                    T_ForwardIterator2 a_rangeToFindEnd )
  {
    return find_first_of(a_rangeToSearchBegin, a_rangeToSearchEnd, 
      a_rangeToFindBegin, a_rangeToFindEnd, 
      equal_to<iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                    T_ForwardIterator1 a_rangeToSearchEnd,
                                    T_ForwardIterator2 a_rangeToFindBegin,
                                    T_ForwardIterator2 a_rangeToFindEnd,
                                    T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (a_rangeToSearchBegin != a_rangeToSearchEnd)
    {
      compareItr = a_rangeToFindBegin;
      while (compareItr != a_rangeToFindEnd)
      {
        if (a_pred(*a_rangeToSearchBegin, *compareItr))
        {
          return a_rangeToSearchBegin;
        }
        ++compareItr;
      }

      ++a_rangeToSearchBegin;
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                        T_ForwardIterator1 a_rangeToSearchEnd,
                                        T_ForwardIterator2 a_rangeToFindBegin,
                                        T_ForwardIterator2 a_rangeToFindEnd )
  {
    return find_first_not_of(a_rangeToSearchBegin, a_rangeToSearchEnd, 
      a_rangeToFindBegin, a_rangeToFindEnd, 
      equal_to<iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                        T_ForwardIterator1 a_rangeToSearchEnd,
                                        T_ForwardIterator2 a_rangeToFindBegin,
                                        T_ForwardIterator2 a_rangeToFindEnd,
                                        T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (a_rangeToSearchBegin != a_rangeToSearchEnd)
    {
      compareItr = a_rangeToFindBegin;

      while (compareItr != a_rangeToFindEnd)
      {
        if (a_pred(*compareItr, *a_rangeToSearchBegin)) { break; }

        ++compareItr;
      }

      if (compareItr == a_rangeToFindEnd)
      {
        return a_rangeToSearchBegin;
      }

      ++a_rangeToSearchBegin;
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_last_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                       T_ForwardIterator1 a_rangeToSearchEnd,
                                       T_ForwardIterator2 a_rangeToFindBegin,
                                       T_ForwardIterator2 a_rangeToFindEnd )
  {
     return find_last_not_of(a_rangeToSearchBegin, a_rangeToSearchEnd, 
      a_rangeToFindBegin, a_rangeToFindEnd, 
      equal_to<iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
    T_ForwardIterator1 find_last_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                         T_ForwardIterator1 a_rangeToSearchEnd,
                                         T_ForwardIterator2 a_rangeToFindBegin,
                                         T_ForwardIterator2 a_rangeToFindEnd,
                                         T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    const tl_size searchSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);
    const tl_size findSize = distance(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator1 ret = a_rangeToSearchEnd;

    if (findSize > 0)
    {
      for (u32 i = 0; i < searchSize; ++i)
      {
        u32 j = 0;
        for (; j < findSize; ++j)
        {
          if ( a_pred(*(a_rangeToSearchBegin + i), *(a_rangeToFindBegin + j)) )
          {
            break;
          }
        }

        if (j == findSize)
        {
          ret = a_rangeToSearchBegin + i;
        }
      }
    }

    return ret;
  }

  template <typename T_Container, typename T>
  tl_size count_all(T_Container a_container, const T& a_value)
  {
    return count(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_InputIterator, typename T>
  tl_size count( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                 const T& a_value )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    const tl_size rangeSize = a_rangeEnd - a_rangeBegin;
    tl_size count = 0;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      if (a_rangeBegin[i] == a_value) ++count;
    }

    return count;
  }

  template <typename T_Container, typename T_Predicate>
  tl_size count_if_all(T_Container a_container, T_Predicate a_pred)
  {
    return count_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T_Predicate>
  tl_size count_if( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                    T_Predicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    const tl_size rangeSize = a_rangeEnd - a_rangeBegin;
    tl_size count = 0;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      if (a_pred(a_rangeBegin[i])) ++count;
    }

    return count;
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare )
  {
    return mismatch(a_rangeBegin, a_rangeEnd, a_rangeToCompare, 
      equal_to<iterator_traits<T_InputIterator1>::value_type>());
  }

  template <typename T_InputIterator1, typename T_InputIterator2, typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare, T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (!a_pred(*a_rangeBegin,*a_rangeToCompare))
        break;

      ++a_rangeBegin;
      ++a_rangeToCompare;
    }

    return MakePair(a_rangeBegin, a_rangeToCompare);
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool equal( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare )
  {
    return equal(a_rangeBegin, a_rangeEnd, a_rangeToCompare, 
      equal_to<iterator_traits<T_InputIterator1>::value_type>());
  }

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  bool equal( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare, T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (!a_pred(*a_rangeBegin,*a_rangeToCompare)) { return false; }

      ++a_rangeBegin;
      ++a_rangeToCompare;
    }

    return true;
  }

  template <typename T_RandomAccessIterator>
  void random_shuffle(T_RandomAccessIterator a_first, 
                      T_RandomAccessIterator a_last)
  {
    typename iterator_traits<T_RandomAccessIterator>::difference_type 
      rangeSize, i;
    rangeSize = a_last - a_first;

    typedef typename rng_default::int_type int_type;
    for (i = rangeSize - 1; i > 0; --i)
    {
      tlSwap(a_first[i], 
             a_first[g_defaultRNG.GetRandomInteger(static_cast<int_type>(i) + 1)]);
    }
  }

  template <typename T_RandomAccessIterator, class T_RandomNumberGenerator>
  void random_shuffle(T_RandomAccessIterator a_first, 
                      T_RandomAccessIterator a_last,
                      T_RandomNumberGenerator a_rng)
  {
    typename iterator_traits<T_RandomAccessIterator>::difference_type 
      rangeSize, i;
    rangeSize = a_last - a_first;

    for (i = rangeSize - 1; i > 0; --i)
    {
      tlSwap(a_first[i], a_first[a_rng(static_cast<tl_size>(i) + 1)]);
    }
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 search( T_ForwardIterator1 a_rangeToSearchBegin,
                             T_ForwardIterator1 a_rangeToSearchEnd,
                             T_ForwardIterator2 a_rangeToFindBegin,
                             T_ForwardIterator2 a_rangeToFindEnd )
  {
    return search(a_rangeToSearchBegin, a_rangeToSearchEnd, a_rangeToFindBegin, 
      a_rangeToFindEnd, equal_to<iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
    T_ForwardIterator1 search( T_ForwardIterator1 a_rangeToSearchBegin,
                               T_ForwardIterator1 a_rangeToSearchEnd,
                               T_ForwardIterator2 a_rangeToFindBegin,
                               T_ForwardIterator2 a_rangeToFindEnd,
                               T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);
    const tl_size compareSize = distance(a_rangeToFindBegin, a_rangeToFindEnd);
    T_ForwardIterator1 sourceLimit = a_rangeToSearchEnd - compareSize + 1;

    T_ForwardIterator1 sourceItr;
    T_ForwardIterator2 compareItr;

    if (sourceSize >= compareSize)
    {
      while (a_rangeToSearchBegin != sourceLimit)
      {
        sourceItr = a_rangeToSearchBegin;
        compareItr = a_rangeToFindBegin;
        while (compareItr != a_rangeToFindEnd)
        {
          if (!a_pred(*sourceItr, *compareItr)) { break; }
          ++sourceItr;
          ++compareItr;
        }

        if (compareItr == a_rangeToFindEnd)
        {
          return a_rangeToSearchBegin;
        }

        ++a_rangeToSearchBegin;
      }
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator search_n( T_ForwardIterator a_rangeToSearchBegin,
                              T_ForwardIterator a_rangeToSearchEnd,
                              T_Size a_count, const T& a_value )
  {
    return search_n(a_rangeToSearchBegin, a_rangeToSearchEnd, a_count, a_value, 
                  equal_to<T>());
  }

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
    T_ForwardIterator search_n( T_ForwardIterator a_rangeToSearchBegin,
                                T_ForwardIterator a_rangeToSearchEnd,
                                T_Size a_count, const T& a_value,
                                T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);

    if (sourceSize >= (tl_size)a_count)
    {
      T_ForwardIterator sourceLimit = a_rangeToSearchEnd - a_count + 1;

      T_ForwardIterator retItr = a_rangeToSearchEnd;
      T_ForwardIterator retItrEnd;

      while(a_rangeToSearchBegin != sourceLimit)
      {
        retItr = a_rangeToSearchBegin;
        retItrEnd = a_rangeToSearchBegin + a_count;
        while (retItr != retItrEnd)
        {
          if (!a_pred(*retItr, a_value) ) { break; }
          ++retItr;
        }

        if (retItr == retItrEnd)
        {
          return a_rangeToSearchBegin;
        }

        ++a_rangeToSearchBegin;
      }
    }

    return a_rangeToSearchEnd;
  }

  //------------------------------------------------------------------------
  // Modifiers 

  template <typename T_Container, typename T>
  typename T_Container::iterator remove_all(T_Container& a_in, const T& a_value)
  {
    return remove(a_in.begin(), a_in.end(), a_value);
  }

  template <typename T_Container, typename T_Pred>
  typename T_Container::iterator remove_if_all(T_Container& a_in, T_Pred a_pred)
  {
    return remove_if(a_in.begin(), a_in.end(), a_pred);
  }

  template <typename T_Container1, typename T_Container2, typename T>
  void remove_copy_all(const T_Container1& a_in, T_Container2& a_out,
                       const T& a_value)
  {
    remove_copy(a_in.begin(), a_in.end(), back_insert_iterator(a_out), a_value);
  }

  template <typename T_Container1, typename T_Container2, typename T_Pred>
  void remove_copy_if_all(const T_Container1& a_in, T_Container2& a_out,
                          T_Pred a_pred)
  {
    remove_copy_if(a_in.begin(), a_in.end(), back_insert_iterator(a_out), a_pred);
  }

  template <typename T_ForwardItr, typename T>
  T_ForwardItr remove(T_ForwardItr a_begin, T_ForwardItr a_end, const T& a_value)
  {
    // See NOTES_ITERATOR_VALUE_TYPE_TYPEDEF @ eof
    typedef typename iterator_traits<T_ForwardItr>::value_type itr_value_type;

    return remove_if(a_begin, a_end, equal_to_stored<itr_value_type>(a_value));
  }

  template <typename T_ForwardItr, typename T_Pred>
  T_ForwardItr remove_if(T_ForwardItr a_begin, T_ForwardItr a_end, T_Pred a_pred)
  {
    T_ForwardItr result = a_begin;
    for (; a_begin != a_end; ++a_begin)
    {
      if (a_pred(*a_begin) == false)
      {
        *result = *a_begin;
        ++result;
      }
    }
    return result;
  }

  template <typename T_InputItr, typename T_OutputItr, typename T>
  T_OutputItr remove_copy(T_InputItr a_begin, T_InputItr a_end,
                          T_OutputItr a_output, const T& a_value)
  {
    // See NOTES_ITERATOR_VALUE_TYPE_TYPEDEF @ eof
    typedef typename iterator_traits<T_InputItr>::value_type itr_value_type;

    return remove_copy_if(a_begin, a_end, a_output, 
                          equal_to_stored<itr_value_type>(a_value));
  }

  template <typename T_InputItr, typename T_OutputItr, typename T_Pred>
  T_OutputItr remove_copy_if(T_InputItr a_begin, T_InputItr a_end,
                             T_OutputItr a_output, T_Pred a_pred)
  {
    for (; a_begin != a_end; ++a_begin)
    {
      if (a_pred(*a_begin) == false)
      {
        *a_output = *a_begin;
        ++a_output;
      }
    }

    return a_output;
  }

  template <typename T_Container, typename T>
  void replace_all(T_Container& a_in, const T& a_oldValue, const T& a_newValue)
  {
    replace(a_in.begin(), a_in.end(), a_oldValue, a_newValue);
  }

  template <typename T_Container, typename T_Pred, typename T>
  void replace_if_all(T_Container& a_in, T_Pred a_pred, const T& a_newValue)
  {
    replace_if(a_in.begin(), a_in.end(), a_pred, a_newValue);
  }

  template <typename T_Container1, typename T_Container2, typename T>
  void replace_copy_all(const T_Container1& a_in, T_Container2& a_out,
                        const T& a_oldValue, const T& a_newValue)
  {
    // See NOTES_ITERATOR_VALUE_TYPE_TYPEDEF @ eof
    typedef typename T_Container1::value_type cont_value_type;

    replace_copy_if_all(a_in, a_out, 
                        equal_to_stored<cont_value_type>(a_oldValue), a_newValue);
  }

  template <typename T_Container1, typename T_Container2, typename T_Pred,
            typename T>
  void replace_copy_if_all(const T_Container1& a_in, T_Container2& a_out,
                           T_Pred a_pred, const T& a_newValue)
  {
    replace_copy_if(a_in.begin(), a_in.end(), back_inserter(a_out), 
                    a_pred, a_newValue); 
  }

  template <typename T_ForwardItr, typename T>
  void replace(T_ForwardItr a_begin, T_ForwardItr a_end,
                       const T& a_oldValue, const T& a_newValue)
  {
    replace_if(a_begin, a_end, equal_to_stored<T>(a_oldValue), a_newValue);
  }

  template <typename T_ForwardItr, typename T_Pred, typename T>
  void replace_if(T_ForwardItr a_begin, T_ForwardItr a_end,
                          T_Pred a_pred, const T& a_newValue)
  {
    for (; a_begin != a_end; ++a_begin)
    {
      if (a_pred(*a_begin)) 
      { *a_begin = a_newValue; }
    }
  }

  template <typename T_InputItr, typename T_OutputItr, typename T>
  void replace_copy(T_InputItr a_begin, T_InputItr a_end,
                           T_OutputItr a_output, const T& a_oldValue,
                           const T& a_newValue)
  {
    replace_copy_if(a_begin, a_end, a_output, equal_to_stored<T>(a_oldValue), 
                    a_newValue);
  }

  template <typename T_InputItr, typename T_OutputItr, typename T_Pred,
            typename T>
  T_OutputItr replace_copy_if(T_InputItr a_begin, T_InputItr a_end,
                              T_OutputItr a_output, T_Pred a_pred,
                              const T& a_newValue)
  {
    for (; a_begin != a_end; ++a_begin, ++a_output)
    {
      if (a_pred(*a_begin))
      { *a_output = a_newValue; }
      else
      { *a_output = *a_begin; }
    }

    return a_output;
  }

  template <typename T_ForwardItr>
  T_ForwardItr unique(T_ForwardItr a_first, T_ForwardItr a_end)
  {
    unique(a_first, a_last, equal_to<iterator_traits<T_ForwardItr>::value_type>());
  }

  template <typename T_ForwardItr, typename T_BinaryPred>
  T_ForwardItr unique(T_ForwardItr a_first, T_ForwardItr a_end,
                      T_BinaryPred)
  {
    T_ForwardItr prevItr = a_first++;

    for (; a_first != a_end; ++a_first)
    {
      if (T_BinaryPred()(*itr, *prevItr) == false)
      { 
        ++prevItr;
        *prevItr = *itr;
      }
    }

    return ++prevItr;
  }

  template <typename T_Container>
  typename T_Container::iterator unique_all(T_Container& a_inOut)
  {
    return unique(a_inOut.being(), a_inOut.end());
  }

  template <typename T_Container1, typename T_Container2>
  void unique_copy_all(const T_Container1& a_in, T_Container2& a_out)
  {
    typedef T_Container1::value_type value_type;
    unique_copy_all(a_in, a_out, equal_to<value_type>());
  }

  template <typename T_Container1, typename T_Container2, typename T_BinaryPred>
  void unique_copy_all(const T_Container1& a_in, T_Container2& a_out, 
                                    T_BinaryPred)
  {
    typedef T_Container1::const_iterator     itr_type_1;
    typedef T_Container1::value_type         value_type_1;
    typedef T_Container2::value_type         value_type_2;

    TLOC_STATIC_ASSERT( (Loki::IsSameType<value_type_1, value_type_2>::value),
      Container_value_type_must_match);

    a_out.push_back( *(a_in.begin()) );

    itr_type_1 prevItr  = a_in.begin();
    itr_type_1 itr      = a_in.begin(); advance(itr, 1);
    itr_type_1 itrEnd   = a_in.end();

    for (; itr != itrEnd; ++itr)
    {
      if (T_BinaryPred()(*itr, *prevItr) == false)
      { 
        a_out.push_back(*itr);
        prevItr = itr;
      }
    }
  }

  template <typename T_Container1, typename T_Container2, typename T_Container3>
  void unique_copy_only_all(const T_Container1& a_in, 
                                             T_Container2& a_out, 
                                             const T_Container3& a_dupList)
  {
    typedef T_Container1::value_type value_type;
    unique_copy_only_all(a_in, a_out, a_dupList, 
                                          equal_to<value_type>());
  }

  template <typename T_Container1, typename T_Container2, typename T_Container3,
            typename T_BinaryPred>
  void unique_copy_only_all(const T_Container1& a_in, 
                                             T_Container2& a_out, 
                                             const T_Container3& a_dupList, 
                                             T_BinaryPred)
  {
    typedef T_Container1::const_iterator     itr_type_1;
    typedef T_Container1::value_type         value_type_1;

    typedef T_Container2::value_type         value_type_2;

    typedef T_Container3::const_iterator     itr_type_3;
    typedef T_Container3::value_type         value_type_3;

    TLOC_STATIC_ASSERT( (Loki::IsSameType<value_type_1, value_type_2>::value),
      Container_value_type_must_match);
    TLOC_STATIC_ASSERT( (Loki::IsSameType<value_type_1, value_type_3>::value),
      Container_value_type_must_match);

    a_out.push_back( *(a_in.begin()) );

    itr_type_1 prevItr  = a_in.begin();
    itr_type_1 itr      = a_in.begin(); advance(itr, 1);
    itr_type_1 itrEnd   = a_in.end();

    for (; itr != itrEnd; ++itr)
    {
      itr_type_3 itrDup = find_all(a_dupList, *itr);
      if (itrDup != a_dupList.end())
      {
        if (T_BinaryPred()(*itr, *prevItr) == false)
        { 
          a_out.push_back(*itr);
          prevItr = itr;
        }
      }
      else
      {
        a_out.push_back(*itr);
        prevItr = itr;
      }
    }
  }

  //------------------------------------------------------------------------
  // Sorting

  template <typename T_InputIterator>
  void sort(T_InputIterator aFirst, T_InputIterator aLast)
  {
    detail::DoSort(aFirst, aLast, sort_quicksort_randompivot());
  }  

  template <typename T_InputIterator, typename T_SortAlgorithm>
  void sort(T_InputIterator aFirst, T_InputIterator aLast, 
            T_SortAlgorithm aSortAlg)
  {
    detail::DoSort(aFirst, aLast, aSortAlg); 
  }

  //------------------------------------------------------------------------
  // Min / Max

  template <typename T>
  TL_I const T& tlMin(const T& a, const T& b)
  {
    return a < b ? a : b;
  }

  template <typename T>
  TL_I const T& tlMax(const T& a, const T& b)
  {
    return a < b ? b : a;
  }

  //------------------------------------------------------------------------
  // Modifying sequence operations

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator copy(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                             T_OutputIterator aDestRangeBegin)
  {
    // We assume that the inputs are pointers. We can then find out whether they
    // are integral pointers or complex
    typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef typename Loki::TypeTraits<T_OutputIterator>::PointeeType outputDeref;
    typedef typename Loki::TypeTraits<inputDeref> inputUnknown;
    typedef typename Loki::TypeTraits<outputDeref> outputUknown;
    typedef typename Loki::Int2Type<inputUnknown::isArith && outputUknown::isArith> inputArith;

    return detail::DoCopy(a_rangeBegin, a_rangeEnd, aDestRangeBegin, inputArith());
  }

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator copy_backward(T_InputIterator a_rangeBegin,
                                      T_InputIterator a_rangeEnd,
                                      T_OutputIterator aDestRangeEnd)
  {
    typedef typename Loki::Int2Type<Loki::TypeTraits<T_InputIterator>::isPointer> input_type;
    typedef typename Loki::Int2Type<Loki::TypeTraits<T_OutputIterator>::isPointer> output_type;
    typedef typename Loki::Select<input_type::value && output_type::value, 
      detail::IsRawItr, detail::IsComplexItr>::Result  itr_type;

    detail::DoCopyBackwardChecks(a_rangeBegin, a_rangeEnd, aDestRangeEnd, itr_type());

    while (a_rangeEnd != a_rangeBegin)
    {
      --aDestRangeEnd;
      --a_rangeEnd;
      *(aDestRangeEnd) = *(a_rangeEnd);
    }

    return aDestRangeEnd;
  }

  template <typename T_InputIterator, typename T>
  TL_I void fill(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                 const T& a_value)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef typename Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef typename Loki::Int2Type<charTestResult::value> IsChar8;

    detail::DoFill(a_rangeBegin, a_rangeEnd, a_value, IsChar8());

  }

  template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
  TL_I void fill_n(T_OutputIterator a_first, T_Count a_count, 
                   const T_ValueType& a_value)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef typename Loki::TypeTraits<T_OutputIterator>::PointeeType inputDeref;
    typedef typename Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef typename Loki::Int2Type<charTestResult::value> IsChar8;

    detail::DoFill_n(a_first, a_count, a_value, IsChar8());
  }

  template <typename T>
  TL_I void tlSwap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  template <typename T_ForwardIterator, typename T>
  T_ForwardIterator lower_bound(T_ForwardIterator a_first, 
    T_ForwardIterator a_last, const T& a_value)
  {
    return lower_bound(a_first, a_last, a_value, less<T>());
  }

  template <typename T_ForwardIterator, typename T, typename T_BinaryPred>
  T_ForwardIterator lower_bound(T_ForwardIterator a_first, 
    T_ForwardIterator a_last, const T& a_value, T_BinaryPred a_comp)
  {
    T_ForwardIterator itr;
    typename iterator_traits<T_ForwardIterator>::difference_type count, step;

    count = distance(a_first, a_last);

    while (count > 0)
    {
      itr = a_first;
      step = count / 2;
      advance(itr, step);

      if (a_comp(*itr, a_value)) 
      {
        a_first = ++itr; 
        count -= step - 1;
      }
      else
      {
        count = step;
      }
    }

    return a_first;
  }

  template <typename T_ForwardItr>
  void delete_ptrs(T_ForwardItr a_first, T_ForwardItr a_last)
  {
    typedef typename iterator_traits<T_ForwardItr>::pointer pointer_type;
    TLOC_STATIC_ASSERT(Loki::TypeTraits<pointer_type>::isPointer, 
      Function_only_works_with_iterators_storing_simple_pointers);

    for (; a_first != a_last; ++a_first)
    {
      delete *a_first;
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Internal use only

  namespace detail
  {
    //------------------------------------------------------------------------
    // Range verification for raw iterators

    template <typename T_Iterator>
    void DoVerifyRange(T_Iterator a_begin, T_Iterator a_end, IsRawItr)
    {
      TLOC_UNUSED_2(a_begin, a_end);
      TLOC_ASSERT_ALGORITHMS( a_begin <= a_end, 
                              "Invalid range (a_rangeBegin > a_rangeEnd)!");
    }

    template <typename T_Iterator>
    void DoVerifyRange(T_Iterator, T_Iterator, IsComplexItr)
    {
      // Do nothing, since we cannot verify non-pointer iterators in a fast way 
    }

    //------------------------------------------------------------------------
    // Copy() helpers

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator DoCopy(T_InputIterator a_rangeBegin, 
                                 T_InputIterator a_rangeEnd, 
                                 T_OutputIterator aDestRangeBegin, IsNotArith)
    {
      while (a_rangeBegin != a_rangeEnd)
      {
        *(aDestRangeBegin++) = *(a_rangeBegin++);
      }

      return aDestRangeBegin;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator DoCopy(T_InputIterator a_rangeBegin, 
                                 T_InputIterator a_rangeEnd, 
                                 T_OutputIterator aDestRangeBegin, IsArith)
    {
      // We need the size of what the pointer is pointing to, not the pointer
      // itself
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;

      tl_size rangeSize = a_rangeEnd - a_rangeBegin;
      memmove( aDestRangeBegin, a_rangeBegin,
        (tl_size)(rangeSize) * sizeof(inputDeref) );
      return aDestRangeBegin + rangeSize;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I void DoCopyBackwardChecks(T_InputIterator a_rangeBegin,
                                   T_InputIterator a_rangeEnd,
                                   T_OutputIterator a_destRangeEnd, IsRawItr)
    {
      TLOC_ASSERT_ALGORITHMS(a_destRangeEnd < a_rangeBegin || a_destRangeEnd > a_rangeEnd,
        "Output past-the-end iterator is within the begin/end range (data "
        L"over-writing)! - Try Copy");
      TLOC_ASSERT_ALGORITHMS(a_rangeBegin <= a_rangeEnd,
        "a_rangeBegin > a_rangeEnd (infinite loop)");

      TLOC_UNUSED_3(a_rangeBegin, a_rangeEnd, a_destRangeEnd);
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I void DoCopyBackwardChecks(T_InputIterator,
                                   T_InputIterator,
                                   T_OutputIterator, IsComplexItr)
    {
      // Do nothing, since we cannot verify non-pointer iterators in a fast way 
    }

    //------------------------------------------------------------------------
    // Fill helpers

    template <typename T_InputIterator, typename T>
    TL_I void DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                      const T& a_value, IsNotChar )
    {
      while (a_rangeBegin != a_rangeEnd)
      {
        *a_rangeBegin = a_value;
        ++a_rangeBegin;
      }
    }

    template <typename T_InputIterator, typename T>
    TL_I void DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                      const T& a_value, IsChar )
    {
      memset(a_rangeBegin, a_value, sizeof(T) * (a_rangeEnd - a_rangeBegin));
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, IsNotChar)
    {
      typedef typename iterator_traits<T_OutputIterator>::iterator_category 
        iterator_category;

      // The correct fill_n() will be called depending on whether the output
      // iterator has a random or lesser tag associated with it. 
      DoFill_n(a_first, a_count, a_value, iterator_category());
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, IsChar)
    {
      memset(a_first, a_value, (tl_size)a_count);
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, random_access_iterator_tag)
    {
      // Grabbing a range by adding to a_first and using fill is faster than
      // using two variables in a for loop. This is only possible if the output
      // iterator has a random tag. 
      tloc::core::fill(a_first, a_first + a_count, a_value);
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, input_iterator_tag)
    {
      for (/* */; a_count > 0; --a_count, ++a_first)
      {
        *a_first = a_value;
      }
    }

    template <typename T_InputIterator, typename T>
    T_InputIterator DoFind( T_InputIterator a_rangeBegin,
                            T_InputIterator a_rangeEnd,
                            const T& a_value, IsNotChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

      while (a_rangeBegin != a_rangeEnd)
      {
        if (*a_rangeBegin == a_value) break;
        ++a_rangeBegin;
      }

      return a_rangeBegin;
    }

    template <typename T_InputIterator, typename T>
    T_InputIterator DoFind( T_InputIterator a_rangeBegin,
                            T_InputIterator a_rangeEnd,
                            const T& a_value, IsChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

      return (char8*)memchr(a_rangeBegin, a_value, sizeof(char8) *
                            (tl_size)(a_rangeEnd - a_rangeBegin));
    }

    //------------------------------------------------------------------------
    // Sort helpers

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_autoselect)
    {
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_randompivot)
    {
      const tl_ptrdiff size      = tloc::core::distance(aFirst, aLast);
      const tl_ptrdiff randomPiv = g_defaultRNG.GetRandomInteger(0, 
                                                  (rng_default::int_type)size);

      T_InputIterator randItr = aFirst;
      tloc::core::advance(randItr, randomPiv);

      tlSwap(*aFirst, *randItr);
      DoSort(aFirst, aLast, sort_quicksort_leftpivot() );
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_middlepivot)
    {
      const tl_ptrdiff halfSize = tloc::core::distance(aFirst, aLast) / 2;

      T_InputIterator midItr = aFirst;
      tloc::core::advance(midItr, halfSize);

      tlSwap(*aFirst, *midItr);
      DoSort(aFirst, aLast, sort_quicksort_leftpivot() );
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_rightpivot)
    {
      // Swap the rightpivot with the left most element. We can then call
      // quicksort_leftpivot
      T_InputIterator rightPivot = aLast;
      --rightPivot;

      tlSwap(*aFirst, *rightPivot);
      DoSort(aFirst, aLast, sort_quicksort_leftpivot() );
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_leftpivot)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoQuicksortLeftPivot(aFirst, aLast, pointer_type());
    }

    template <typename T_InputIterator>
    void DoQuicksortLeftPivot(T_InputIterator aFirst, T_InputIterator aLast, 
                              IsRawItr)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoQuicksort(aFirst, aLast, value_type()); 
    }

    template <typename T_InputIterator>
    void DoQuicksortLeftPivot(T_InputIterator aFirst, T_InputIterator aLast, 
                              IsComplexItr)
    {
      // It is assumed, since the inputer iterator is complex, it has a typedef
      // for value_type. If there is a COMPILE ERROR here then the complex
      // object is either not an iterator OR does not have a value_type typedef
      DoQuicksort(aFirst, aLast, typename T_InputIterator::value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoQuicksort(T_InputIterator aFirst, T_InputIterator aLast, T_ValueType)
    {
      if (aFirst == aLast) { return; }

      T_ValueType pivot = *aFirst;

      T_InputIterator startItr = aFirst;
      T_InputIterator endItr   = aLast--;

      T_InputIterator currItr  = aFirst;

      while (aFirst != aLast)
      {
        if (currItr == aFirst)
        {
          if (*aLast < pivot)
          {
            *aFirst = *aLast;
            ++aFirst;
            currItr = aLast;
          }
          else
          {
            --aLast;
          }
        }
        else
        {
          if (*aFirst > pivot)
          {
            *aLast = *aFirst;
            --aLast;
            currItr = aFirst;
          }
          else
          {
            ++aFirst;
          }
        }
      }

      *aFirst = pivot;
      if (startItr != aFirst) 
      { DoSort(startItr, aFirst, sort_quicksort_leftpivot() ); }
      if (++aLast != endItr)
      { DoSort(aLast, endItr, sort_quicksort_leftpivot() ); }
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
      sort_insertionsort)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoInsertionsortWithItrType(aFirst, aLast, pointer_type());
    }

    template <typename T_InputIterator>
    void DoInsertionsortWithItrType(T_InputIterator aFirst, T_InputIterator aLast, 
      IsRawItr)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoInsertionsortWithValueType(aFirst,aLast, value_type());
    }

    template <typename T_InputIterator>
    void DoInsertionsortWithItrType(T_InputIterator aFirst, T_InputIterator aLast, 
      IsComplexItr)
    {
      DoInsertionsortWithValueType(aFirst, aLast, 
                                   typename T_InputIterator::value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoInsertionsortWithValueType(T_InputIterator aFirst, 
                                      T_InputIterator aLast,
                                      T_ValueType)
    {
      if (aFirst != aLast)
      {
        T_InputIterator unsortedItr = aFirst;
        ++unsortedItr;

        T_InputIterator currentItr;
        T_InputIterator currentItrMinusOne;

        T_ValueType currentValue;

        for (/* */; unsortedItr != aLast; ++unsortedItr)
        {
          currentItr = unsortedItr;
          currentValue = *currentItr;

          currentItrMinusOne = currentItr;
          --currentItrMinusOne;
          
          while (currentItr != aFirst 
                 && *currentItrMinusOne > currentValue)
          {
            *currentItr = *currentItrMinusOne;

            currentItr = currentItrMinusOne;
            --currentItrMinusOne;
          }

          *currentItr = currentValue;
        }
      }
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, sort_mergesort)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoMergesortWithItrType(aFirst, aLast, pointer_type());
    }

    template <typename T_InputIterator>
    void DoMergesortWithItrType(T_InputIterator aFirst, T_InputIterator aLast,
                     IsComplexItr)
    {
      DoMergesortWithValueType(aFirst, 
                               aLast, 
                               typename T_InputIterator::value_type());
    }

    template <typename T_InputIterator>
    void DoMergesortWithItrType(T_InputIterator aFirst, T_InputIterator aLast,
                     IsRawItr)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;

      DoMergesortWithValueType(aFirst, aLast, value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoMergesortWithValueType(T_InputIterator aFirst, T_InputIterator aLast,
                     T_ValueType)
    {
      if (aFirst != aLast)
      {
        const tl_ptrdiff size = tloc::core::distance(aFirst, aLast);
        typedef Array<T_ValueType> T_Container;
        T_Container unsortedArray(size);

        tloc::core::copy(aFirst, aLast, unsortedArray.begin());

        T_Container sortedArray = DoMergesort(unsortedArray);
        //unsortedArray = DoMergesort(unsortedArray);

        tloc::core::copy(sortedArray.begin(), sortedArray.end(), aFirst);
        //tloc::core::copy(unsortedArray.begin(), unsortedArray.end(), aFirst);
      }
    }

    template <typename T_Container>
    T_Container DoMergesort(const T_Container& aUnsorted)
    {
      const tl_size size = aUnsorted.size();
      if ((size - 1) != 0)
      {
        TLOC_ASSERT_LOW_LEVEL(size > 1, "Size is <= 1");

        typename T_Container::const_iterator first = aUnsorted.begin();
        typename T_Container::const_iterator last = aUnsorted.end();

        tl_size halfSize = size / 2;

        typename T_Container::const_iterator midItr = first;
        tloc::core::advance(midItr, halfSize);

        T_Container leftSide(halfSize);
        T_Container rightSide(size - halfSize);

        tloc::core::copy(first, midItr, leftSide.begin());
        tloc::core::copy(midItr, last, rightSide.begin());

        T_Container LeftSideSorted = DoMergesort(leftSide);
        T_Container RightSideSorted = DoMergesort(rightSide);

        return DoMerge(LeftSideSorted, RightSideSorted);
      }
      else
      {
        return aUnsorted;
      }
    }

    template <typename T_Container>
    T_Container DoMerge(const T_Container& aLeftFirst, 
                        const T_Container& aRightFirst)
    {
      const typename T_Container::size_type size = aLeftFirst.size() + aRightFirst.size();
      T_Container mergedContainer(size);

      typename T_Container::const_iterator leftItr   = aLeftFirst.begin();
      typename T_Container::const_iterator rightItr  = aRightFirst.begin();
      typename T_Container::iterator mergedItr       = mergedContainer.begin();

      const typename T_Container::const_iterator endLeftItr   = aLeftFirst.end();
      const typename T_Container::const_iterator endRightItr  = aRightFirst.end();

      while ((leftItr != endLeftItr) && (rightItr != endRightItr))
      {
        if (*leftItr < *rightItr)
        {
          *mergedItr = *leftItr;
          ++leftItr;
        }
        else
        {
          *mergedItr = *rightItr;
          ++rightItr;
        }
        ++mergedItr;
      }

      while (leftItr != endLeftItr)
      {
        *mergedItr = *leftItr;
        ++leftItr;
        ++mergedItr;
      }

      while (rightItr != endRightItr)
      {
        *mergedItr = *rightItr;
        ++rightItr;
        ++mergedItr;
      }

      return mergedContainer;
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_merge_insertionsort)
    {
      if (aFirst != aLast)
      {
        DoMergeInsertionSort(aFirst, aLast);
      }
    }

    template <typename T_InputIterator>
    void DoMergeInsertionSort(T_InputIterator aFirst, T_InputIterator aLast)
    {
      const tl_ptrdiff size = tloc::core::distance(aFirst, aLast);
      if ((size - 1) != 0)
      {
        const tl_ptrdiff halfSize = size / 2;
        T_InputIterator midItr = aFirst;
        tloc::core::advance(midItr, halfSize);

        DoMergeInsertionSort(aFirst, midItr);
        DoMergeInsertionSort(midItr, aLast);
        DoMergeInsertion(aFirst, midItr, aLast);
      }
    }

    template <typename T_InputIterator>
    void DoMergeInsertion(T_InputIterator aLeftFirst,
                          T_InputIterator aRightFirst,
                          T_InputIterator aLast)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      for (/* */; aLeftFirst != aRightFirst; ++aLeftFirst)
      {
        if (*aLeftFirst > *aRightFirst)
        {
          tlSwap(*aLeftFirst, *aRightFirst);
          DoSortFirstElementWithItrType(aRightFirst, aLast, pointer_type());
        }
      }
    }

    template <typename T_InputIterator>
    void DoSortFirstElementWithItrType(T_InputIterator aFirst, 
                                       T_InputIterator aLast,
                                       IsComplexItr)
    {
      DoSortFirstElementWithValueType(aFirst, 
                                      aLast, 
                                      typename T_InputIterator::value_type());
    }

    template <typename T_InputIterator>
    void DoSortFirstElementWithItrType(T_InputIterator aFirst, 
                                       T_InputIterator aLast,
                                       IsRawItr)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;

      DoSortFirstElementWithValueType(aFirst, aLast, value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoSortFirstElementWithValueType(T_InputIterator aFirst, 
                                         T_InputIterator aLast,
                                         T_ValueType)
    {
      T_ValueType valueToBeSorted = *aFirst;

      T_InputIterator currentItr = aFirst;
      T_InputIterator currentItrPlusOne = currentItr;
      ++currentItrPlusOne;

      while (currentItrPlusOne != aLast && *currentItrPlusOne < valueToBeSorted)
      {
        *currentItr = *currentItrPlusOne;
        ++currentItr;
        ++currentItrPlusOne;
      }

      *currentItr = valueToBeSorted;
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                sort_bubblesort)
    {
      T_InputIterator endOfUnsortedItr;
      T_InputIterator currentItr;
      T_InputIterator currentItrPlusOne;
      
      bool swapped;

      for (endOfUnsortedItr = aLast; endOfUnsortedItr != aFirst; --endOfUnsortedItr)
      {
        currentItr = aFirst;
        currentItrPlusOne = currentItr;
        ++currentItrPlusOne;

        swapped = false;

        for (/* */; 
             currentItrPlusOne != endOfUnsortedItr; 
             currentItr = currentItrPlusOne, ++currentItrPlusOne)
        {
          if (*currentItr > *currentItrPlusOne)
          {
            tlSwap(*currentItr, *currentItrPlusOne);
            swapped = true;
          }
        }

        if (!swapped)
        {
          break;
        }
      }
    }

  }

};};

#endif

//////////////////////////////////////////////////////////////////////////
// NOTES
// 
// These notes are put here to avoid cluttering the code above
// 
// NOTES_ITERATOR_VALUE_TYPE_TYPEDEF
//    Why use itr_value_type?
//    We need to make equal_to_stored the same type as the iterator's type,
//    otherwise we may get warnings of casting from itr_value_type to T when
//    the predicate is called in remove_if() 
