#ifndef TLOC_HASH_TABLE_H 
#define TLOC_HASH_TABLE_H 

#include "tlocBase.h"
#include "tlocMemory.h"
#include "tlocTypeTraits.h"
#include "tlocAlgorithms.h"
#include "tlocIterator.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_HASH_TABLE
# define TLOC_ASSERT_HASH_TABLE(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_HASH_TABLE(_Expression, _Msg)
#endif

///-------------------------------------------------------------------------
/// @brief The hash_table is written after looking at EASTL hash_table and SGI
/// hash_table. The container will be optimized for games only and may not be 
/// appropriate for application use
///-------------------------------------------------------------------------
namespace tloc { namespace core {

  namespace hash_detail
  {
    extern void*       g_emptyBucketArray[2];
  }

  ///-------------------------------------------------------------------------
  /// @brief
  /// The standard creates a hash_node instead which is a simple linked
  /// list. We allow the user to choose the type of container they chose
  /// as long as it can accomodate this class as `T`.
  ///-------------------------------------------------------------------------
  template <typename T_Value, bool T_StoreHash = false>
  struct HashtableElement 
  {
    typedef tl_size                                 size_type;
    typedef T_Value                                 value_type;
    typedef ConditionalTypePackage<value_type, 
                                   size_type, 
                                   T_StoreHash>     hashcode_type;

    TL_FI value_type m_value() { return m_valueAndHashcode.m_var; }
    TL_FI size_type  m_hashcode() { return (size_type)m_valueAndHashcode; }

    // You can access this variable directly, but it is recommended that you
    // use the inline functions instead for clarity.
    hashcode_type m_valueAndHashcode;
  };

  template <typename T_Policies, bool T_Const>
  class HashtableItrBase
  {
  public:

    typedef HashtableItrBase<T_Policies, T_Const>    this_type;

    typedef T_Policies                               policy_type;
    typedef typename policy_type::node_type          node_type;
    typedef typename policy_type::bucket_type        b_type;
    typedef typename T_Policies::value_type           value_type;

    typedef typename Loki::Select<T_Const, const value_type*, value_type*> pointer;
    typedef typename Loki::Select<T_Const, const value_type&, value_type&> reference;
    typedef typename Loki::Select<T_Const, const b_type, b_type>::Result bucket_type;
    typedef typename Loki::Select<T_Const, 
                                  typename node_type::const_iterator, 
                                  typename node_type::iterator>::Result node_iterator;
    typedef typename Loki::Select<T_Const, 
                                  typename bucket_type::const_iterator, 
                                  typename bucket_type::iterator>::Result bucket_iterator;

  public:
    TL_FI HashtableItrBase(bucket_type& a_bucketContainer);
    TL_FI HashtableItrBase(bucket_type& a_bucketContainer,
      const node_iterator& a_currNode,
      const bucket_iterator& a_currBucket);

    TL_FI void IncrementBucket();
    TL_FI void Increment();

    this_type& operator=(const this_type& a_other);
    bool       operator==(const this_type& a_other);

    node_iterator       m_currNode;

    bucket_type&        m_bucketContainer;
    bucket_iterator     m_currBucket;
  };

  template <typename T_Policies, bool T_Const>
  class HashtableItr : public HashtableItrBase<T_Policies, T_Const>
  {
  public:

    typedef HashtableItrBase<T_Policies, T_Const>     base_type;
    typedef HashtableItr<T_Policies, T_Const>         this_type;
    typedef HashtableItr<T_Policies, false>           this_type_non_const;

    typedef typename base_type::bucket_type           bucket_type;
    typedef typename base_type::bucket_iterator       bucket_iterator;
    typedef typename base_type::node_type             node_type;
    typedef typename base_type::node_iterator         node_iterator;
    typedef typename base_type::value_type            value_type;
    typedef typename base_type::pointer               pointer;
    typedef typename base_type::reference             reference;

    typedef tl_ptrdiff                                difference_type;
    typedef forward_iterator_tag                      iterator_category;

  public:

    HashtableItr(bucket_type& a_bucketContainer)
      : base_type(a_bucketContainer) {}
    HashtableItr(bucket_type& a_bucketContainer, const node_iterator& a_currNode,
      const bucket_iterator& a_currBucket)
      : base_type(a_bucketContainer, a_currNode, a_currBucket) {}
    HashtableItr(const this_type& a_other)
      : base_type(a_other.m_bucketContainer, a_other.m_currNode, a_other.m_currBucket) {}

    reference operator*() const { return base_type::m_currNode->m_value; }
    pointer   operator->() const { return &(base_type::m_currNode->m_value); }
    
    this_type& operator++() { base_type::Increment(); return *this; }
    this_type operator++(int) { this_type temp(*this); base_type::Increment(); return temp; }

    const node_type* get_node() const { return base_type::m_currNode; }

  };


  ///-------------------------------------------------------------------------
  /// Prime rehash policy. One of the available rehash policies. This one is
  /// referenced from EASTL and changed where deemed fit.
  ///-------------------------------------------------------------------------
  struct prime_rehash_policy
  {
    typedef tl_size size_type; 

    f32         m_maxLoadFactor;
    f32         m_growthFactor;
    mutable u32 m_nextResize;

    prime_rehash_policy(f32 a_maxLoadFactor = 1.0f);
    
    size_type             GetNextBucketCount(size_type a_bucketCountHint) const;
    size_type             GetBucketCount(size_type a_numOfElements) const;
    Pair<bool, size_type> GetRehashRequired(size_type a_numOfBuckets,
      size_type a_numOfElements, size_type a_numOfElementsToAdd) const;
  };

  ///-------------------------------------------------------------------------
  /// Hashtable rehash class. Called when the load factor in the Hashtable
  /// exceeds and the table needs to rehash.
  ///-------------------------------------------------------------------------
  template <typename T_Policies, typename T_Hashtable>
  class HashtableRehash
  {
  };

  template <typename T_Key, typename T_HashFunc, 
            typename T_KeyEqual, typename T_RehashPolicy, typename T_BucketType, 
            bool T_CacheHashCode>

  ///-------------------------------------------------------------------------
  /// A policy class that combines all the policies with all the necessary
  /// typedefs.
  /// 
  /// - T_Key
  /// - Any object that is compatible with the T_HashFunc for
  /// conversion of the key to a hash.
  /// - T_BucketType
  /// - The container for storing the buckets of a container of some type. The
  /// container must be such that this is true: BucketContainer&lt;
  /// ElementContainer&lt; HashtableElement&lt;T&gt; &gt; &gt; where
  /// BucketContainer and ElementContainer can be the same type containers. For
  /// example: List&lt; List&lt;HashtableElement&lt;s32&gt; &gt; &gt;.
  ///-------------------------------------------------------------------------
  struct HashtablePolicy
  {
    typedef T_Key					 key_type;
    typedef T_HashFunc		 hasher_func;
    typedef T_KeyEqual		 key_equal;
    typedef T_BucketType	 bucket_type;
    typedef T_RehashPolicy rehash_policy_type;

    typedef typename bucket_type::value_type	node_type;
    typedef typename node_type::value_type		element_type;
    typedef typename element_type::value_type	value_type;

    typedef tl_ptrdiff     difference_type;
    typedef tl_size        size_type;

    typedef Loki::Int2Type<T_CacheHashCode> cache_hash_type;
  };

  template <typename T_Policies>

  ///-------------------------------------------------------------------------
  /// The Hashtable is a base class for associative containers like the
  /// Hashmap. We used EASTL and SGI as reference but tried to keep it as
  /// simple as possible while retaining some flexibility.
  ///
  /// @sa
  /// tloc::core::HashtableRehash<T_Policies::rehash_policy_type,Hashtable<T_Policies,T_RehashPolicy>
  /// >
  ///-------------------------------------------------------------------------
  class Hashtable : public HashtableRehash<typename T_Policies::rehash_policy_type, 
                                           Hashtable<T_Policies> >
  {
  public:
    typedef Hashtable<T_Policies>                 this_type;
    typedef T_Policies                            policy_type;

    typedef typename policy_type::key_type					 key_type;
    typedef typename policy_type::value_type				 value_type;
    typedef typename policy_type::element_type			 element_type;
    typedef typename policy_type::hasher_func				 hasher;
    typedef typename policy_type::key_equal					 key_equal;
    typedef typename policy_type::node_type					 node_type;
    typedef typename policy_type::bucket_type				 bucket_type;
    typedef typename policy_type::size_type					 size_type;
    typedef typename policy_type::cache_hash_type		 cache_hash_type;
    typedef typename policy_type::rehash_policy_type rehash_policy_type;

    typedef HashtableItr<policy_type, false> iterator;
    typedef HashtableItr<policy_type, true>  const_iterator;

    typedef typename node_type::iterator             local_iterator;
    typedef typename node_type::const_iterator       const_local_iterator;
    typedef core::reverse_iterator<iterator>         reverse_iterator;
    typedef core::reverse_iterator<const_iterator>   const_reverse_iterator;

    typedef tl_ptrdiff                               difference_type;

    //------------------------------------------------------------------------
    // Constructors

    ///-------------------------------------------------------------------------
    /// Default constructor.
    ///-------------------------------------------------------------------------
    TL_FI Hashtable();

    ///-------------------------------------------------------------------------
    /// Construct a Hashtable with at least a_bucketCount buckets.
    ///
    /// @param  a_bucketCount Number of buckets.
    ///-------------------------------------------------------------------------
    TL_FI Hashtable(size_type a_bucketCount);

    ///-------------------------------------------------------------------------
    /// Copy constructor.
    ///
    /// @param  a_other The other hashtable.
    ///-------------------------------------------------------------------------
    TL_FI Hashtable(const this_type& a_other);

    ///-------------------------------------------------------------------------
    /// Destructor.
    ///-------------------------------------------------------------------------
    TL_FI ~Hashtable();

    //------------------------------------------------------------------------
    // Iterator Access

    TL_FI iterator        begin();
    TL_FI const_iterator  begin() const;

    TL_FI iterator        end();
    TL_FI const_iterator  end() const;


  protected:

    TL_FI void DoAllocateBuckets(size_type a_numBuckets);

  protected:
    bucket_type				 m_bucketArray;
    size_type					 m_elementCount;
    rehash_policy_type m_rehashPolicy;

    // Used to mark end() iterator's m_currNode
    static typename node_type::iterator   m_dummyNode; 
  };

};};

#endif