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

#define HASH_TABLE_ITR_TYPES typename T_Policies
#define HASH_TABLE_ITR_PARAMS T_Policies

  template <HASH_TABLE_ITR_TYPES>
  TL_FI HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>
    ::HashtableIteratorBase(
    typename HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::bucket_type& a_bucketContainer,
    typename HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::node_type::const_iterator& a_currNode,
    typename HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::bucket_type::const_iterator& a_currBucket) 
    : m_bucketContainer(a_bucketContainer)
    , m_currNode(a_currNode)
    , m_currBucket(a_currBucket)
  {
  }

  template <HASH_TABLE_ITR_TYPES>
  TL_FI HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>
    ::HashtableIteratorBase(
    typename HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::bucket_type& a_bucketContainer)
    : m_bucketContainer(a_bucketContainer)
    , m_currNode( (*(a_bucketContainer.begin())).begin())
    , m_currBucket( a_bucketContainer.begin() )
  {
  }

  template <HASH_TABLE_ITR_TYPES>
  TL_FI void HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::Increment()
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

  template <HASH_TABLE_ITR_TYPES>
  TL_FI void HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::IncrementBucket()
  {
    bucket_type::iterator bucketEnd = m_bucketContainer.end();
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

  template <HASH_TABLE_ITR_TYPES>
  TL_FI typename HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>::this_type&
    HashtableIteratorBase<HASH_TABLE_ITR_PARAMS>
    ::operator =(const typename HashtableIteratorBase<T_Policies>::this_type &a_other)
  {
    m_currNode				= a_other.m_currNode;
    m_bucketContainer	= a_other.m_bucketContainer;
    m_currBucket			= a_other.m_currBucket;
  }

  //////////////////////////////////////////////////////////////////////////
  // Hashtable

#define HASH_TABLE_TYPES typename T_Policies
#define HASH_TABLE_PARAMS T_Policies

  template <HASH_TABLE_TYPES>
  Hashtable<HASH_TABLE_PARAMS>::Hashtable()
  {
  }

  template <HASH_TABLE_TYPES>
  TL_FI Hashtable<HASH_TABLE_PARAMS>::Hashtable(size_type a_bucketCount)
  {
    TLOC_ASSERT_HASH_TABLE(a_bucketCount < 10000000, "Bucket count is too large!");
    size_type newBucketCount = 
      (size_type)m_rehashPolicy.GetNextBucketCount((u32)a_bucketCount);
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

  //template <HASH_TABLE_TYPES>
  //TL_FI typename Hashtable<HASH_TABLE_PARAMS>::const_iterator
  //  Hashtable<HASH_TABLE_PARAMS>::begin() const
  //{
  //}

};};

#endif