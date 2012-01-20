#ifndef TLOC_HASH_TABLE_INL 
#define TLOC_HASH_TABLE_INL 

#ifndef TLOC_HASH_TABLE_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.inl"
#include "tlocIterator.inl"

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Hashtable Iterator 

#define HASHTABLE_ITR_BASE_TYPES typename T_Policies, bool T_Const
#define HASHTABLE_ITR_BASE_PARAMS T_Policies, T_Const

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::HashtableItrBase(
    typename HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::bucket_type& a_bucketContainer)
    : m_bucketContainer(a_bucketContainer)
    , m_currNode( (*(a_bucketContainer.begin() )).begin())
    , m_currBucket( a_bucketContainer.begin() )
  {
  }

  template <HASHTABLE_ITR_BASE_TYPES>
  TL_FI HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>
    ::HashtableItrBase(
    typename HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::bucket_type& a_bucketContainer,
    typename const HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::node_iterator& a_currNode,
    typename const HashtableItrBase<HASHTABLE_ITR_BASE_PARAMS>::bucket_iterator& a_currBucket) 
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
    return ( m_bucketContainer == a_other.m_bucketContainer &&
             m_currNode				 == a_other.m_currNode &&
             m_currBucket			 == a_other.m_currBucket );
  }

  //////////////////////////////////////////////////////////////////////////
  // Hashtable

#define HASH_TABLE_TYPES typename T_Policies
#define HASH_TABLE_PARAMS T_Policies
  
  template <HASH_TABLE_TYPES>
  typename Hashtable<HASH_TABLE_PARAMS>::node_type::iterator 
    Hashtable<HASH_TABLE_PARAMS>::m_dummyNode = 
    typename Hashtable<HASH_TABLE_PARAMS>::node_type::iterator();

  template <HASH_TABLE_TYPES>
  Hashtable<HASH_TABLE_PARAMS>::Hashtable()
  {
  }

  template <HASH_TABLE_TYPES>
  TL_FI Hashtable<HASH_TABLE_PARAMS>::Hashtable(size_type a_bucketCount)
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
    return iterator(m_bucketArray, m_dummyNode, m_bucketArray.end()); 
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_iterator 
    Hashtable<HASH_TABLE_PARAMS>::end() const
  {
    return const_iterator(m_bucketArray, m_dummyNode, m_bucketArray.end()); 
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::local_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::begin(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber)
  {
    bucket_type::iterator itr(m_bucketArray.begin());
    advance(itr, a_bucketNumber);
    return (*(itr)).begin(); 
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_local_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::begin(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber) const
  {
    bucket_type::const_iterator itr(m_bucketArray.begin());
    advance(itr, a_bucketNumber);
    return (*(itr)).begin(); 
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::local_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::end(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber)
  {
    bucket_type::iterator itr(m_bucketArray.end());
    advance(itr, a_bucketNumber);
    return (*(itr)).end(); 
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_local_iterator
    Hashtable<HASH_TABLE_PARAMS>
    ::end(typename Hashtable<HASH_TABLE_PARAMS>::size_type a_bucketNumber) const
  {
    bucket_type::const_iterator itr(m_bucketArray.end());
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
    bucket_type::const_iterator itr(m_bucketArray.begin());
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
  // Insert Helpers

  template <HASH_TABLE_TYPES>
  TL_FI Pair<typename Hashtable<HASH_TABLE_PARAMS>::iterator, bool>
    Hashtable<HASH_TABLE_PARAMS>::DoInsertValue
    (const typename Hashtable<HASH_TABLE_PARAMS>::value_type& a_value, 
           typename Hashtable<HASH_TABLE_PARAMS>::keys_are_unique)
  {
    const key_type& k = extract_key(a_value);
    const hash_code_type c = get_hash_code(k);

    TLOC_UNUSED(k);
    TLOC_UNUSED(c);

    return MakePair(begin(), false); 
  }

  template <HASH_TABLE_TYPES>
  TL_FI typename Hashtable<HASH_TABLE_PARAMS>::iterator  
    Hashtable<HASH_TABLE_PARAMS>::DoInsertValue
    (const typename Hashtable<HASH_TABLE_PARAMS>::value_type& a_value, 
           typename Hashtable<HASH_TABLE_PARAMS>::keys_are_not_unique)
  {
    TLOC_UNUSED(a_value);
    return begin(); 
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