#ifndef TLOC_HASH_TABLE_INL 
#define TLOC_HASH_TABLE_INL 

#ifndef TLOC_HASH_TABLE_H
#error "Must include header before including the inline file"
#endif

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Hashtable Iterator 

#define HASH_TABLE_ITERATOR_BASE_TYPES typename T_Policies
#define HASH_TABLE_ITERATOR_BASE_PARAMS T_Policies

  template <HASH_TABLE_ITERATOR_BASE_TYPES>
  HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>
    ::HashtableIteratorBase(
    typename HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>::node_type& a_nodeContainer, 
    typename HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>::bucket_type& a_bucketContainer,
    typename HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>::node_type::const_iterator& a_currNode,
    typename HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>::bucket_type::const_iterator& a_currBucket) 
    : m_nodeContainer(a_nodeContainer)
    , m_bucketContainer(a_bucketContainer)
    , m_currNode(a_currNode)
    , m_currBucket(a_currBucket)
  {
  }

  template <HASH_TABLE_ITERATOR_BASE_TYPES>
  void HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>::Increment()
  {

  }

  template <HASH_TABLE_ITERATOR_BASE_TYPES>
  void HashtableIteratorBase<HASH_TABLE_ITERATOR_BASE_PARAMS>::IncrementBucket()
  {
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
  Hashtable<HASH_TABLE_PARAMS>::Hashtable(size_type a_bucketCount)
  {
    TLOC_ASSERT_HASH_TABLE(a_bucketCount < 10000000, "Bucket count is too large!");
    size_type newBucketCount = 
      (size_type)m_rehashPolicy.GetNextBucketCount((u32)a_bucketCount);
    DoAllocateBuckets(newBucketCount);
  }

  template <HASH_TABLE_TYPES>
  Hashtable<HASH_TABLE_PARAMS>::Hashtable(const this_type& a_other)
  {
    TLOC_UNUSED(a_other);
  }

  template <HASH_TABLE_TYPES>
  Hashtable<HASH_TABLE_PARAMS>::~Hashtable()
  {
  }

  template <HASH_TABLE_TYPES>
  void Hashtable<HASH_TABLE_PARAMS>::DoAllocateBuckets(size_type a_numBuckets)
  {
    m_bucketArray.resize(a_numBuckets);
  }

};};

#endif