#ifndef _TLOC_MATH_RANGE_INL_
#define _TLOC_MATH_RANGE_INL_

#ifndef _TLOC_MATH_RANGE_H_
#error "Must include header before including the inline file"
#endif

#include <tlocCore/utilities/tlocType.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl>

namespace tloc { namespace math {

#define RANGE_T_TEMP    typename T_NumberType
#define RANGE_T_PARAMS  T_NumberType
#define RANGE_T_TYPE    typename Range_T<RANGE_T_PARAMS>

  //------------------------------------------------------------------------
  // Range_T<>::iterator

#define RANGE_T_ITERATOR_TYPE typename Range_T<RANGE_T_PARAMS>::iterator

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::iterator::
    iterator()
    : m_range()
    , m_index(0)
  {
  }

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::iterator::
    iterator(const range_type& a_range, size_type a_index)
    : m_range(a_range)
    , m_index(a_index)
  { }

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::iterator::
    iterator(const this_type& a_other)
    : m_range(a_other.m_range)
    , m_index(a_other.m_index)
  { }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE ::this_type&
    Range_T<RANGE_T_PARAMS>::iterator::
    operator =(const this_type& a_other)
  {
    m_range = a_other.m_range;
    m_index = a_other.m_index;

    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE ::value_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator *() const
  {
    return m_range[m_index];
  }

  template <RANGE_T_TEMP>
  bool
    Range_T<RANGE_T_PARAMS>::iterator::
    operator==(const iterator& a_other) const
  {
    TLOC_ASSERT_LOW_LEVEL(m_range == a_other.m_range, "Mismatched ranges!");
    return m_index == a_other.m_index;
  }
  
  template <RANGE_T_TEMP>
  bool
    Range_T<RANGE_T_PARAMS>::iterator::
    operator<(const iterator& a_other) const
  {
    return m_index < a_other.m_index;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator+(difference_type a_index) const
  {
    return this_type(m_range, m_index + a_index);
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE ::this_type&
    Range_T<RANGE_T_PARAMS>::iterator::
    operator+=(difference_type a_index)
  {
    *this = this_type(m_range, m_index + a_index);
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator-(difference_type a_index)
  {
    return this_type (m_range, m_index - a_index);
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator-=(difference_type a_index)
  {
    *this = this_type(m_range, m_index - a_index);
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type&
    Range_T<RANGE_T_PARAMS>::iterator::
    operator++()
  {
    ++m_index;
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator++(int)
  {
    this_type temp = *this;
    ++m_index;
    return temp;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type&
    Range_T<RANGE_T_PARAMS>::iterator::
    operator--()
  {
    --m_index;
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator--(int)
  {
    this_type temp = *this;
    --m_index;
    return temp;
  }

  template <RANGE_T_TEMP>
  RANGE_T_ITERATOR_TYPE::value_type
    Range_T<RANGE_T_PARAMS>::iterator::
    operator[](size_type a_index) const
  {
    return m_range[m_index + a_index];
  }

  //------------------------------------------------------------------------
  // Range_T<>::reverse_iterator

#define RANGE_T_REVERSE_ITERATOR_TYPE typename Range_T<RANGE_T_PARAMS>::reverse_iterator

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::reverse_iterator::
    reverse_iterator()
    : m_range()
    , m_index(0)
  {
  }

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::reverse_iterator::
    reverse_iterator(const range_type& a_range, size_type a_index)
    : m_range(a_range)
    , m_index(a_index)
  { }

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::reverse_iterator::
    reverse_iterator(const this_type& a_other)
    : m_range(a_other.m_range)
    , m_index(a_other.m_index)
  { }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type&
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator =(const this_type& a_other)
  {
    m_range = a_other.m_range;
    m_index = a_other.m_index;

    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::value_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator *() const
  {
    return m_range[m_range.size() - 1 - m_index];
  }

  template <RANGE_T_TEMP>
  bool
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator==(const reverse_iterator& a_other) const
  {
    TLOC_ASSERT_LOW_LEVEL(m_range == a_other.m_range, "Mismatched ranges!");
    return m_index == a_other.m_index;
  }
  
  template <RANGE_T_TEMP>
  bool
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator<(const reverse_iterator& a_other) const
  {
    TLOC_ASSERT_LOW_LEVEL(m_range == a_other.m_range, "Mismatched ranges!");
    return m_index < a_other.m_index;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator+(difference_type a_index) const
  {
    return this_type(m_range, m_index + a_index);
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type&
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator+=(difference_type a_index)
  {
    *this = this_type(m_range, m_index + a_index);
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator-(difference_type a_index)
  {
    return this_type (m_range, m_index - a_index);
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator-=(difference_type a_index)
  {
    *this = this_type(m_range, m_index - a_index);
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type&
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator++()
  {
    ++m_index;
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator++(int)
  {
    this_type temp = *this;
    ++m_index;
    return temp;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type&
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator--()
  {
    --m_index;
    return *this;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::this_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator--(int)
  {
    this_type temp = *this;
    --m_index;
    return temp;
  }

  template <RANGE_T_TEMP>
  RANGE_T_REVERSE_ITERATOR_TYPE::value_type
    Range_T<RANGE_T_PARAMS>::reverse_iterator::
    operator[](size_type a_index) const
  {
    reverse_iterator temp(m_range, m_index + a_index);
    return *temp;
  }

  //------------------------------------------------------------------------
  // Range_T

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::
    Range_T()
    : m_begin(0)
    , m_elementCount(0)
    , m_stepSize(1)
  { }

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::
    Range_T(const this_type& a_other)
    : m_begin(a_other.m_begin)
    , m_elementCount(a_other.m_elementCount)
    , m_stepSize(a_other.m_stepSize)
  { }

  template <RANGE_T_TEMP>
  Range_T<RANGE_T_PARAMS>::
    Range_T(value_type a_begin, value_type a_end, step_size a_stepSize)
    : m_begin(a_begin)
    , m_stepSize(a_stepSize)
  {
    TLOC_ASSERT_LOW_LEVEL(a_end >= a_begin, "Invalid range!");
    TLOC_ASSERT_LOW_LEVEL(m_stepSize > 0, "Invalid step size!");

    m_elementCount = (a_end - a_begin) / a_stepSize;

    value_type absDiff = math::Abs<value_type>(a_end - a_begin);
    value_type remainder = math::Remainder(absDiff, m_stepSize);

    if (math::Approx(remainder, (value_type)0) == false)
    { m_elementCount++; }
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::this_type& 
    Range_T<RANGE_T_PARAMS>::
    operator =(const this_type& a_other)
  {
    m_begin         = a_other.m_begin;
    m_elementCount  = a_other.m_elementCount;
    m_stepSize      = a_other.m_stepSize;

    return *this;
  }

  template <RANGE_T_TEMP>
  bool Range_T<RANGE_T_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return m_begin == a_other.m_begin &&
      m_elementCount == a_other.m_elementCount &&
      m_stepSize == a_other.m_stepSize;
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::value_type 
    Range_T<RANGE_T_PARAMS>::
    at(size_type a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL (a_index < size(), "Index out of bounds!");
    return m_begin + (m_stepSize * 
            core_utils::CastNumber<value_type, size_type>(a_index));
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::value_type 
    Range_T<RANGE_T_PARAMS>:: 
    operator[] (size_type a_index) const
  {
    return at(a_index);
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::value_type 
    Range_T<RANGE_T_PARAMS>:: 
    front() const
  {
    return m_begin;
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::value_type 
    Range_T<RANGE_T_PARAMS>:: 
    back() const
  {
    size_type currSize = size();
    return currSize ? operator[](currSize - 1) : 0;
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::const_iterator
    Range_T<RANGE_T_PARAMS>:: 
    begin() const
  {
    return const_iterator(*this, 0);
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::const_reverse_iterator
    Range_T<RANGE_T_PARAMS>:: 
    rbegin() const
  {
    return const_reverse_iterator(*this, 0);
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::const_iterator
    Range_T<RANGE_T_PARAMS>:: 
    end() const
  {
    return const_iterator(*this, size());
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::const_reverse_iterator
    Range_T<RANGE_T_PARAMS>:: 
    rend() const
  {
    return const_reverse_iterator(*this, size());
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::size_type
    Range_T<RANGE_T_PARAMS>::
    size() const
  {
    return core_utils::CastNumber<size_type, value_type>(m_elementCount);
  }

  template <RANGE_T_TEMP>
  RANGE_T_TYPE::size_type
    Range_T<RANGE_T_PARAMS>::
    capacity() const
  {
    return size();
  }
  
  template <RANGE_T_TEMP>
  bool
    Range_T<RANGE_T_PARAMS>::
    empty() const
  {
    return size() == 0;
  }

};};

#endif