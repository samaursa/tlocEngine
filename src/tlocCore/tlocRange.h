#ifndef _TLOC_CORE_RANGE_H_
#define _TLOC_CORE_RANGE_H_

#include <tlocCore/tlocBase.h>

#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>

// This class takes its design from https://bitbucket.org/AraK/range by Khaled
// Alshaya.

namespace tloc { namespace core {

  template <typename T_IntegerType>
  class Range_T
  {
  public:
    typedef Range_T<T_IntegerType>  this_type;
    typedef T_IntegerType           value_type;
    typedef tl_size                 size_type;
    typedef value_type*             pointer;
    typedef value_type const *      const_pointer;
    typedef value_type&             reference;
    typedef value_type const &      const_reference;

    typedef types::StrongType_T<value_type, 0> step_size;

  public:
    class iterator
      : public core::iterator<bidirectional_iterator_tag, T_IntegerType>
    {
    public:
      typedef core::iterator
        <bidirectional_iterator_tag, T_IntegerType> base_type;

      typedef Range_T<T_IntegerType>                range_type;
      typedef typename range_type::value_type       value_type;
      typedef typename range_type::size_type        size_type;
      typedef typename range_type::iterator         this_type;

      typedef typename base_type::difference_type   difference_type;
      typedef typename base_type::pointer           pointer;
      typedef typename base_type::reference         reference;
      typedef typename base_type::iterator_category iterator_category;

    public:
      iterator();
      iterator(const range_type& a_range, size_type a_index = 0);
      iterator(const this_type& a_other);

      this_type& operator= (const this_type& a_other);
      value_type operator* () const;

      bool       operator==(const iterator& a_other) const;
      bool       operator< (const iterator& a_other) const;
      TLOC_DECLARE_OPERATORS(iterator);

      this_type   operator+ (difference_type a_index) const;
      this_type&  operator+= (difference_type a_index);
      this_type   operator- (difference_type a_index);
      this_type   operator-= (difference_type a_index);
      this_type&  operator++ ();
      this_type   operator++ (int);
      this_type&  operator-- ();
      this_type   operator-- (int);

      value_type  operator[] (size_type a_index) const;

    private:
      range_type  m_range;
      size_type   m_index;

    };

  public:
    class reverse_iterator
      : public core::iterator<bidirectional_iterator_tag, T_IntegerType>
    {
    public:
      typedef core::iterator
        <bidirectional_iterator_tag, T_IntegerType> base_type;

      typedef Range_T<T_IntegerType>                range_type;
      typedef typename range_type::value_type       value_type;
      typedef typename range_type::size_type        size_type;
      typedef typename range_type::reverse_iterator this_type;

      typedef typename base_type::difference_type   difference_type;
      typedef typename base_type::pointer           pointer;
      typedef typename base_type::reference         reference;
      typedef typename base_type::iterator_category iterator_category;

    public:
      reverse_iterator();
      reverse_iterator(const range_type& a_range, size_type a_index = 0);
      reverse_iterator(const this_type& a_other);

      this_type& operator= (const this_type& a_other);
      value_type operator*() const;

      bool operator== (const reverse_iterator& a_other) const;
      bool operator<  (const reverse_iterator& a_other) const;
      TLOC_DECLARE_OPERATORS(reverse_iterator);

      this_type   operator+ (difference_type a_index) const;
      this_type&  operator+= (difference_type a_index);
      this_type   operator- (difference_type a_index);
      this_type   operator-= (difference_type a_index);
      this_type&  operator++ ();
      this_type   operator++ (int);
      this_type&  operator-- ();
      this_type   operator-- (int);

      value_type  operator[] (size_type a_index) const;

    private:
      range_type  m_range;
      size_type   m_index;
    };

  public:
    typedef iterator                const_iterator;
    typedef reverse_iterator        const_reverse_iterator;

  public:

    Range_T();
    Range_T(const this_type& a_other);
    Range_T(value_type a_begin, value_type a_end,
            step_size a_stepSize = step_size(1));

    this_type& operator=(const this_type& a_other);
    bool       operator== (const this_type& a_other) const;

    TLOC_DECLARE_OPERATOR_NOT_EQUAL(Range_T);

    value_type at(size_type a_index) const;
    value_type operator[] (size_type a_index) const;

    value_type front() const;
    value_type back() const;

    const_iterator         begin() const;
    const_reverse_iterator rbegin() const;
    const_iterator         end() const;
    const_reverse_iterator rend() const;

    size_type size() const;
    size_type capacity() const;
    bool      empty() const;

  private:
    value_type m_begin;
    value_type m_elementCount;
    value_type m_stepSize;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef Range_T<tl_int>         Range;
  typedef Range_T<tl_float>       Rangef;

  typedef Range_T<s32>            range_s32;
  typedef Range_T<s64>            range_s64;
  typedef Range_T<u32>            range_u32;
  typedef Range_T<u64>            range_u64;

};};

#endif