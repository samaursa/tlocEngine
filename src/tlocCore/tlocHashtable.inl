#ifndef TLOC_HASH_TABLE_INL
#define TLOC_HASH_TABLE_INL

#ifndef TLOC_HASH_TABLE_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.inl"
#include "tlocIterator.inl"

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Hashtable Iterator Base

#define HASHTABLE_ITR_BASE_TYPES typename T_Policies, bool T_Const
#define HASHTABLE_ITR_BASE_PARAMS T_Policies, T_Const

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::HashtableItrBase( bucket_type& a_bucketContainer) 
    : m_bucketContainer(a_bucketContainer)
    , m_currBucket( a_bucketContainer.begin() )
    , m_currNode( (*(a_bucketContainer.begin() )).begin())
  {
  }

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::HashtableItrBase( bucket_type& a_bucketContainer, 
                        const bucket_iterator& a_currBucket, 
                        const node_iterator& a_currNode)
                        : m_bucketContainer(a_bucketContainer)
                        , m_currNode(a_currNode)
                        , m_currBucket(a_currBucket)
  {
  }


  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI void HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::Increment()
  {
    bucket_type::const_iterator bucketEnd = m_bucketContainer.end();
    node_type::const_iterator itrEnd = (*m_currBucket).end();
    ++m_currNode;

    while(m_currNode == itrEnd)
    {
      ++m_currBucket;

      if (m_currBucket != bucketEnd)
      {
        m_currNode = *(m_currBucket).begin();
        itrEnd = *(m_currBucket).end();
      }
      else
      {
        m_currBucket = m_bucketContainer.begin();
        m_currNode = *(m_bucketContainer).begin();
        break;
      }
    }
  }

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI void HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::IncrementBucket()
  {
    bucket_iterator bucketEnd = m_bucketContainer.end();

    TLOC_ASSERT_HASH_TABLE(m_currBucket != bucketEnd,
      "Already at the end of the bucket container!");

    ++m_currBucket;
    while( (*(m_currBucket)).size() == 0 )
    {
      ++m_currBucket;
      if (m_currBucket != bucketEnd)
      {
        m_currNode = (*(m_currBucket)).begin();
      }
      else
      {
        m_currBucket = m_bucketContainer.begin();
        m_currNode = (*(m_currBucket)).begin();
      }
    }
  }

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI typename HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::this_type&
    HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::operator = (const typename HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::this_type &a_other)
  {
    m_currNode				= a_other.m_currNode;
    m_bucketContainer	= a_other.m_bucketContainer;
    m_currBucket			= a_other.m_currBucket;
  }

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI bool HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::operator == (const typename HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::this_type &a_other)
  {
    return ( m_currNode				 == a_other.m_currNode &&
             m_currBucket			 == a_other.m_currBucket );
  }

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI bool HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::operator != (const typename HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::this_type &a_other)
  {
    return !(operator==(a_other));
  }

  //------------------------------------------------------------------------
  // Hashtable Iterator

#define HASHTABLE_ITR_TYPES   typename T_Policies, bool T_Const
#define HASHTABLE_ITR_PARAMS  T_Policies, T_Const

  template <HASHTABLE_ITR_TYPES>
  HashtableItr<HASHTABLE_ITR_PARAMS>::HashtableItr(bucket_type& a_bucketContainer) 
    : base_type(a_bucketContainer, a_bucketContainer.begin(), 
                (*(a_bucketContainer.begin())).begin() ) 
  {
  }

  template <HASHTABLE_ITR_TYPES>
  HashtableItr<HASHTABLE_ITR_PARAMS>::HashtableItr(bucket_type& a_bucketContainer, 
    const bucket_iterator& a_currBucket, const node_iterator& a_currNode) 
    : base_type(a_bucketContainer, a_currBucket, a_currNode) 
  {
  }

  template <HASHTABLE_ITR_TYPES>
  HashtableItr<HASHTABLE_ITR_PARAMS>::HashtableItr(const this_type_non_const& a_other)
      : base_type(a_other.m_bucketContainer, a_other.m_currBucket, 
                  a_other.m_currNode)
  {
  }

  template <HASHTABLE_ITR_TYPES>
  typename HashtableItr<HASHTABLE_ITR_PARAMS>::reference 
    HashtableItr<HASHTABLE_ITR_PARAMS>::operator *() const
  { 
    return (*(base_type::m_currNode)).m_value();
  }

  template <HASHTABLE_ITR_TYPES>
  typename HashtableItr<HASHTABLE_ITR_PARAMS>::pointer
    HashtableItr<HASHTABLE_ITR_PARAMS>::operator ->() const
  { 
    return &(base_type::m_currNode->m_value() ); 
  }

  template <HASHTABLE_ITR_TYPES>
  typename HashtableItr<HASHTABLE_ITR_PARAMS>::this_type&
    HashtableItr<HASHTABLE_ITR_PARAMS>::operator ++() 
  { 
    base_type::Increment(); return *this; 
  }

  template <HASHTABLE_ITR_TYPES>
  typename HashtableItr<HASHTABLE_ITR_PARAMS>::this_type
    HashtableItr<HASHTABLE_ITR_PARAMS>::operator ++(int) 
  { 
    this_type temp(*this); base_type::Increment(); return temp; 
  }

  template <HASHTABLE_ITR_TYPES>
  const typename HashtableItr<HASHTABLE_ITR_PARAMS>::node_iterator&
    HashtableItr<HASHTABLE_ITR_PARAMS>::get_node() const
  { 
    return base_type::m_currNode;
  }

  //////////////////////////////////////////////////////////////////////////
  // Hashtable

#define HASH_TABLE_TYPES typename T_Policies
#define HASH_TABLE_PARAMS T_Policies

  template <HASH_TABLE_TYPES>
  typename Hashtable<HASH_TABLE_PARAMS>::bucket_iterator
    Hashtable<HASH_TABLE_PARAMS>::m_dummyNode =
    typename Hashtable<HASH_TABLE_PARAMS>::buckets_type::iterator();

  template <HASH_TABLE_TYPES>
  Hashtable<HASH_TABLE_PARAMS>::Hashtable()
    : m_elementCount(0), m_rehashPolicy()
  {
  }

  template <HASH_TABLE_TYPES>
  TL_FI Hashtable<HASH_TABLE_PARAMS>::Hashtable(size_type a_bucketCount)
    : m_elementCount(0)
  {
    TLOC_ASSERT_HASH_TABLE(a_bucketCount < 10000000, "Bucket count is too large!");

    size_type newBucketCount =
      (size_type)m_rehashPolicy.get_next_bucket_count((u32)a_bucketCount);
    DoAllocateBuckets(newBucketCount);
  }

  template <HASH_TABLE_TYPES>
  TL_FI Hashtable<HASH_TABLE_PARAMS>::Hashtable(const this_type& a_other)
  {
    TLOC_UNUSED(a_other);
  }

  template <HASH_TABLE_TYPES>
  TL_FI Hashtable<HASH_TABLE_PARAMS>::~Hashtable()
  {
  }

  template <HASH_TABLE_TYPES>
  TL_FI void Hashtable<HASH_TABLE_PARAMS>
    ::DoAllocateBuckets(size_type a_numBuckets)
  {
    m_bucketArray.resize(a_numBuckets);
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::iterator
    Hashtable<HASH_TABLE_PARAMS>::begin()
  {
    iterator itr(m_bucketArray);
    if ( (*(itr.m_currBucket)).empty())
    {
      itr.IncrementBucket();
    }
    return itr;
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_iterator
    Hashtable<HASH_TABLE_PARAMS>::begin() const
  {
    const_iterator itr(m_bucketArray);
    if ( (*(itr.m_currBucket)).empty() )
    {
      itr.IncrementBucket();
    }
    return itr;
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::iterator
    Hashtable<HASH_TABLE_PARAMS>::end()
  {
    return iterator(m_bucketArray, m_bucketArray.end(), m_dummyNode);
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_iterator
    Hashtable<HASH_TABLE_PARAMS>::end() const
  {
    return const_iterator(m_bucketArray, m_bucketArray.end(), m_dummyNode);
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::bucket_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::begin(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber)
  {
    buckets_array_type::iterator itr(m_bucketArray.begin());
    advance(itr, a_bucketNumber);
    return (*(itr)).begin();
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_bucket_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::begin(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber) const
  {
    buckets_array_type::const_iterator itr(m_bucketArray.begin());
    advance(itr, a_bucketNumber);
    return (*(itr)).begin();
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::bucket_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::end(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber)
  {
    buckets_array_type::iterator itr(m_bucketArray.end());
    advance(itr, a_bucketNumber);
    return (*(itr)).end();
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_bucket_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::end(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber) const
  {
    buckets_array_type::const_iterator itr(m_bucketArray.end());
    advance(itr, a_bucketNumber);
    return (*(itr)).end();
  }

  //------------------------------------------------------------------------
  // Capacity

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::size_type
    Hashtable<HASH_TABLE_PARAMS>::size() const
  {
    return m_elementCount;
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::size_type
    Hashtable<HASH_TABLE_PARAMS>::bucket_count() const
  {
    return (size_type)m_bucketArray.size();
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::size_type
    Hashtable<HASH_TABLE_PARAMS>::bucket_size
    (typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber) const
  {
    buckets_array_type::const_iterator itr(m_bucketArray.begin());
    advance(itr, a_bucketNumber);
    return (*itr).size();
  }

  //------------------------------------------------------------------------
  // Hashing queries

  template <HASH_TABLE_TYPES>
  TL_FI f32 Hashtable<HASH_TABLE_PARAMS>::load_factor() const
  {
    return (f32)m_elementCount / (f32)bucket_count();
  }

  template <HASH_TABLE_TYPES>
  TL_FI const typename Hashtable<HASH_TABLE_PARAMS>::rehash_policy_type&
    Hashtable<HASH_TABLE_PARAMS>::get_rehash_policy() const
  {
    return m_rehashPolicy;
  }

  template <HASH_TABLE_TYPES>
  TL_FI void Hashtable<HASH_TABLE_PARAMS>::set_rehash_policy(const
    typename Hashtable<HASH_TABLE_PARAMS>::rehash_policy_type& a_rehashPolicy)
  {
    m_rehashPolicy = a_rehashPolicy;
  }

  template <HASH_TABLE_TYPES>
  TL_FI f32 Hashtable<HASH_TABLE_PARAMS>::get_max_load_factor() const
  {
    return DoGetMaxLoadFactor(m_rehashPolicy);
  }

  template <HASH_TABLE_TYPES>
  TL_FI void Hashtable<HASH_TABLE_PARAMS>::
    set_max_load_factor(f32 a_maxLoadFactor)
  {
    DoSetMaxLoadFactor(a_maxLoadFactor, m_rehashPolicy);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::insert_return_type
    Hashtable<HASH_TABLE_PARAMS>::insert(const value_type& a_value)
  {
  }

  //------------------------------------------------------------------------
  // Operations

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::iterator
    Hashtable<HASH_TABLE_PARAMS>::find(const key_type& a_value)
  {
    const key_type& k = extract_key(a_value);
    const hash_code_type hc = get_hash_code(k);
    return find_by_hash(hc);
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_iterator
    Hashtable<HASH_TABLE_PARAMS>::find(const key_type& a_value) const
  {
    const key_type& k = extract_key(a_value);
    const hash_code_type hc = get_hash_code(k);
    return find_by_hash(hc);
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::iterator
    Hashtable<HASH_TABLE_PARAMS>::find_by_hash(u32 a_hashCode)
  {
    const size_type n = (size_type)bucket_index(a_hashCode, (u32)bucket_count());

    buckets_array_type::iterator itr = m_bucketArray.begin();
    advance(itr, n);

    buckets_type::iterator itrN    = (*itr).begin();
    buckets_type::iterator itrNEnd = (*itr).end();

    while (itrN != itrNEnd)
    {
      if (compare(a_hashCode, &(*itrN)))
      {
        return iterator(m_bucketArray, itr, itrN);
      }

      ++itrN;
    }

    return end();
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_iterator
    Hashtable<HASH_TABLE_PARAMS>::find_by_hash(u32 a_hashCode) const
  {
    const_iterator itr = (remove_const(this))->find_by_hash(a_hashCode);
    add_const(this);
    return itr;
  }

  //------------------------------------------------------------------------
  // Insert Helpers

  template <HASH_TABLE_TYPES>
  TL_FI Pair<typename Hashtable<HASH_TABLE_PARAMS>::iterator, bool>
    Hashtable<HASH_TABLE_PARAMS>::DoInsertValue
    (const typename Hashtable<HASH_TABLE_PARAMS>::value_type& a_value,
           typename Hashtable<HASH_TABLE_PARAMS>::keys_are_unique)
  {
    const key_type& k = extract_key(a_value);
    const hash_code_type c = get_hash_code(k);

    iterator itr = find_by_hash(c);

    // TODO: Remove extra copies created by end() here and when returning <false>
    if (itr == end())
    {
      const Pair<bool, u32> rehash = m_rehashPolicy.get_rehash_required
        ( (u32)bucket_count(), (u32)m_elementCount, (u32)1);

      if (rehash.first) { DoRehash(rehash.second); }

      element_type newElement (a_value, c);

      const size_type n = (size_type)bucket_index(c, (u32)bucket_count());
      buckets_array_type::iterator itrB = m_bucketArray.begin(); 
      advance(itrB, n);

      typedef iterator_traits<buckets_type::iterator>::iterator_category itr_cat;

      // Select the appropriate push() function (front or back)
      return Pair<iterator(m_bucketArray, itrB, 
        DoPushSelect(itrB, newElement, itr_cat()) ), true>;
    }

    return Pair<end(), false>;
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::iterator
    Hashtable<HASH_TABLE_PARAMS>::DoInsertValue
    (const typename Hashtable<HASH_TABLE_PARAMS>::value_type& a_value,
           typename Hashtable<HASH_TABLE_PARAMS>::keys_are_not_unique)
  {
    const Pair<bool, u32> rehash = m_rehashPolicy.get_rehash_required
      ( (u32)bucket_count(), (u32)m_elementCount, (u32)1);

    if (rehash.first) { DoRehash(rehash.second); }

    const key_type& k = extract_key(a_value);
    const hash_code_type c = get_hash_code(k);

    iterator itr = find_by_hash(c);
    element_type newElement (a_value, c);

    typedef iterator_traits<buckets_type::iterator>::iterator_category itr_cat;

    if (itr != end())
    {
      buckets_array_type::iterator itrB = itr.m_currBucket;
      // Select the appropriate insert() function (insert() or insert_after())
      return iterator(m_bucketArray, itrB, 
                      DoInsertSelect(itr.m_currBucket, itr.m_currNode, 
                                     newElement, itr_cat()) );
    }
    else
    {
      const size_type n = (size_type)bucket_index(c, (u32)bucket_count());

      buckets_array_type::iterator itrB = m_bucketArray.begin(); 
      advance(itrB, n);

      // Select the appropriate push() function (front or back)
      return iterator(m_bucketArray, itrB, 
                      DoPushSelect(itrB, newElement, itr_cat()) );
    }
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::buckets_type::iterator
    Hashtable<HASH_TABLE_PARAMS>::DoPushSelect(local_iterator& a_itr,
      const element_type& a_elem, bidirectional_iterator_tag)
  {
    (*(a_itr)).push_back(a_elem);

    bucket_iterator itrN = (*(a_itr)).end();
    return --itrN;
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::buckets_type::iterator
    Hashtable<HASH_TABLE_PARAMS>::DoPushSelect(local_iterator& a_itr,
      const element_type& a_elem, forward_iterator_tag)
  {
    (*(a_itr)).push_front(a_elem);

    return (*(a_itr)).front();
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::buckets_type::iterator
    Hashtable<HASH_TABLE_PARAMS>::DoInsertSelect(local_iterator& a_itr, 
      bucket_iterator a_currNode, const element_type& a_elem, 
      forward_iterator_tag)
  {
    return (*(a_itr)).insert_after(a_currNode, a_elem);
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::buckets_type::iterator
    Hashtable<HASH_TABLE_PARAMS>::DoInsertSelect(local_iterator& a_itr, 
      bucket_iterator a_currNode, const element_type& a_elem, 
      bidirectional_iterator_tag)
  {
    return (*(a_itr)).insert(a_currNode, a_elem);
  }

  //------------------------------------------------------------------------
  // Rehashing

  template <HASH_TABLE_TYPES>
  TL_FI void Hashtable<HASH_TABLE_PARAMS>::DoRehash(size_type a_bucketCount)
  {
    buckets_array_type newArray;
    newArray.resize(a_bucketCount);

    const_local_iterator itrB = m_bucketArray.begin();
    const_local_iterator itrBEnd = m_bucketArray.end();

    for (; itrB != itrBEnd; ++itrB)
    {
      buckets_type::const_iterator itrN = (*itrB).begin();
      buckets_type::const_iterator itrNEnd = (*itrB).end();

      while(itrN != itrNEnd)
      {
        const element_type& currElem = *itrN;
        const size_type newBucketIndex =
          (size_type)bucket_index(currElem, a_bucketCount);

        TLOC_ASSERT_HASH_TABLE(newBucketIndex < a_bucketCount,
          "Invalid bucket index!");

        local_iterator itrNew(newArray.begin());
        advance(itrNew, newBucketIndex);

        (*itrNew).push_back(currElem);

        ++itrN;
      }
    }

    m_bucketArray.swap(newArray);

  }

  //------------------------------------------------------------------------
  // Load factor overloads and sanity checks

  template <HASH_TABLE_TYPES>
  TL_FI f32 Hashtable<HASH_TABLE_PARAMS>::
    DoGetMaxLoadFactor(prime_rehash_policy) const
  {
    return m_rehashPolicy.get_max_load_factor();
  }

  template <HASH_TABLE_TYPES>
  TL_FI void Hashtable<HASH_TABLE_PARAMS>::DoSetMaxLoadFactor
    (f32 a_maxLoadFactor, prime_rehash_policy)
  {
    m_rehashPolicy.set_max_load_factor(a_maxLoadFactor);
  }

};};

#endif