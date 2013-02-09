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
    class iterator
      : public core::iterator<bidirectional_iterator_tag, T_IntegerType>
    {
    public:
      typedef core::iterator
        <bidirectional_iterator_tag, T_IntegerType> base_type;

      typedef T_IntegerType                         value_type;
      typedef Range_T<value_type>                   range_type;
      typedef typename range_type::iterator         this_type;

      typedef typename base_type::difference_type   difference_type;
      typedef typename base_type::pointer           pointer;
      typedef typename base_type::reference         reference;
      typedef typename base_type::iterator_category iterator_category;

    public:
      iterator() : m_range(), m_index(0)
      { }

      iterator(const range_type& a_range, value_type a_index = 0)
        : m_range(a_range)
        , m_index(a_index)
      { }

      iterator (const this_type& a_other)
        : m_range(a_other.m_range)
        , m_index(a_other.m_index)
      { }

      this_type& operator= (const this_type& a_other)
      {
        m_range = a_other.m_range;
        m_index = a_other.m_index;

        return *this;
      }

      value_type operator*() const
      {
        return m_range[m_index];
      }

      bool operator== (const iterator& a_other) const
      {
        TLOC_ASSERT_LOW_LEVEL(m_range == a_other.m_range, "Mismatched ranges!");
        return m_index == a_other.m_index;
      }

      bool operator< (const iterator& a_other) const
      {
        return m_index < a_other.m_index;
      }

      TLOC_DECLARE_OPERATORS(iterator);

      this_type operator+ (difference_type a_index) const
      {
        return this_type(m_range, m_index + a_index);
      }

      this_type& operator++ ()
      {
        ++m_index;
        return *this;
      }

      this_type operator++ (int)
      {
        this_type temp = *this;
        ++m_index;
        return temp;
      }

      this_type& operator+= (difference_type a_index)
      {
        *this = this_type(m_range, m_index + a_index);
        return *this;
      }

      this_type operator- (difference_type a_index)
      {
        return this_type (m_range, m_index - a_index);
      }

      this_type& operator-- ()
      {
        --m_index;
        return *this;
      }

      this_type operator-- (int)
      {
        this_type temp = *this;
        --m_index;
        return temp;
      }

      this_type operator-= (difference_type a_index)
      {
        *this = this_type(m_range, m_index - a_index);
        return *this;
      }

      value_type operator[] (difference_type a_index) const
      {
        return m_range[m_index + a_index];
      }

    private:
      range_type  m_range;
      value_type  m_index;

    };

  public:
    class reverse_iterator
      : public core::iterator<bidirectional_iterator_tag, T_IntegerType>
    {
    public:
      typedef core::iterator
        <bidirectional_iterator_tag, T_IntegerType> base_type;

      typedef T_IntegerType                         value_type;
      typedef Range_T<value_type>                   range_type;
      typedef typename range_type::reverse_iterator this_type;

      typedef typename base_type::difference_type   difference_type;
      typedef typename base_type::pointer           pointer;
      typedef typename base_type::reference         reference;
      typedef typename base_type::iterator_category iterator_category;

    public:
      reverse_iterator() : m_range(), m_index(0)
      { }

      reverse_iterator(const range_type& a_range, value_type a_index = 0)
        : m_range(a_range)
        , m_index(a_index)
      { }

      reverse_iterator (const this_type& a_other)
        : m_range(a_other.m_range)
        , m_index(a_other.m_index)
      { }

      this_type& operator= (const this_type& a_other)
      {
        m_range = a_other.m_range;
        m_index = a_other.m_index;
        return *this;
      }

      value_type operator*() const
      {
        return m_range[m_range.size() - 1 - m_index];
      }

      bool operator== (const iterator& a_other) const
      {
        TLOC_ASSERT_LOW_LEVEL(m_range == a_other.m_range, "Mismatched ranges!");
        return m_index == a_other.m_index;
      }

      bool operator< (const iterator& a_other) const
      {
        TLOC_ASSERT_LOW_LEVEL(m_range == a_other.m_range, "Mismatched ranges!");
        return m_index < a_other.m_index;
      }

      TLOC_DECLARE_OPERATORS(iterator);

      this_type operator+ (difference_type a_index) const
      {
        return this_type(m_range, m_index + a_index);
      }

      this_type& operator++ ()
      {
        ++m_index;
        return *this;
      }

      this_type operator++ (int)
      {
        this_type temp = *this;
        ++m_index;
        return temp;
      }

      this_type& operator+= (difference_type a_index)
      {
        *this = this_type(m_range, m_index + a_index);
        return *this;
      }

      this_type operator- (difference_type a_index)
      {
        return this_type (m_range, m_index - a_index);
      }

      this_type& operator-- ()
      {
        --m_index;
        return *this;
      }

      this_type operator-- (int)
      {
        this_type temp = *this;
        --m_index;
        return temp;
      }

      this_type operator-= (difference_type a_index)
      {
        *this = this_type(m_range, m_index - a_index);
        return *this;
      }

      value_type operator[] (difference_type a_index) const
      {
        reverse_iterator temp(m_range, m_index + a_index);
        return *temp;
      }

    private:
      range_type  m_range;
      value_type  m_index;
    };

  public:
    typedef Range_T<T_IntegerType>  this_type;
    typedef T_IntegerType           value_type;
    typedef tl_size                 size_type;
    typedef value_type*             pointer;
    typedef value_type const *      const_pointer;
    typedef value_type&             reference;
    typedef value_type const &      const_reference;

    typedef iterator                const_iterator;
    typedef reverse_iterator        const_reverse_iterator;

    typedef types::StrongType_T<value_type, 0> step_size;

  public:

    Range_T()
      : m_begin(0)
      , m_elementCount(0)
      , m_stepSize(1)
    { }

    Range_T(value_type a_begin, value_type a_end,
            step_size a_stepSize = step_size(1))
      : m_begin(a_begin)
      , m_stepSize(a_stepSize)
    {
      m_elementCount = (a_end - a_begin) / a_stepSize;
      if ( (a_end - a_begin) % a_stepSize != 0)
      { m_elementCount++; }

      TLOC_ASSERT_LOW_LEVEL(a_end >= a_begin, "Invalid range!");
      TLOC_ASSERT_LOW_LEVEL(m_stepSize > 0, "Invalid step size!");
    }

    Range_T(const this_type& a_other)
      : m_begin(a_other.m_begin)
      , m_elementCount(a_other.m_elementCount)
      , m_stepSize(a_other.m_stepSize)
    { }

    this_type& operator=(const this_type& a_other)
    {
      m_begin         = a_other.m_begin;
      m_elementCount  = a_other.m_elementCount;
      m_stepSize      = a_other.m_stepSize;

      return *this;
    }

    bool operator== (const this_type& a_other) const
    {
      return m_begin == a_other.m_begin &&
             m_elementCount == a_other.m_elementCount &&
             m_stepSize == a_other.m_stepSize;
    }

    TLOC_DECLARE_OPERATOR_NOT_EQUAL(Range_T);

    value_type at(size_type a_index) const
    {
      TLOC_ASSERT_LOW_LEVEL (a_index < size(), "Index out of bounds!");
      return m_begin + (m_stepSize * a_index);
    }

    value_type operator[] (size_type a_index) const
    {
      return at(a_index);
    }

    value_type front() const
    {
      return m_begin;
    }

    value_type back() const
    {
      return operator[](size() - 1);
    }

    const_iterator begin() const
    {
      return const_iterator(*this, 0);
    }

    const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(*this, 0);
    }

    const_iterator end() const
    {
      return const_iterator(*this, size());
    }

    const_reverse_iterator rend() const
    {
      return const_reverse_iterator(*this, size());
    }

    size_type size() const
    {
      return m_elementCount;
    }

    size_type capacity() const
    {
      return size();
    }

    bool empty() const
    {
      return size() == 0;
    }

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
  typedef Range_T<f32>            range_f32;
  typedef Range_T<f64>            range_f64;

};};

#endif