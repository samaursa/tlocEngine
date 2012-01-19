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
  // Rehash policies

  //------------------------------------------------------------------------
  // Prime rehash policy

  prime_rehash_policy::prime_rehash_policy(f32 a_maxLoadFactor) 
    : m_maxLoadFactor(a_maxLoadFactor), m_growthFactor(2.0f), m_nextResize(0)
  {
  }

  prime_rehash_policy::size_type prime_rehash_policy
    ::GetBucketCount(prime_rehash_policy::size_type a_numOfElements) const
  {
    const u32 minBucketCount = u32 (a_numOfElements / m_maxLoadFactor);
    TLOC_UNUSED(minBucketCount);
    //const u32 prime = 
    return 0;
  }

  Pair<bool, prime_rehash_policy::size_type> prime_rehash_policy
    ::GetRehashRequired(size_type a_numOfBuckets, size_type a_numOfElements, 
                        size_type a_numOfElementsToAdd) const
  {
    TLOC_UNUSED(a_numOfBuckets);
    TLOC_UNUSED(a_numOfElements);
    TLOC_UNUSED(a_numOfElementsToAdd);
    return MakePair<bool, size_type>(false, 0);
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

};};

#endif