#ifndef TLOC_HASH_TABLE_H
#define TLOC_HASH_TABLE_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/tlocFunctional.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

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
namespace tloc { namespace core { namespace containers {

  namespace hash_detail
  {
    extern void*       g_emptyBucketArray[2];
  }

  //------------------------------------------------------------------------
  // Hash functions

  struct hash_to_range_mod
  {
    DECL_BINARY_FUNC(tl_uint, tl_uint, tl_uint);

    result_type operator() (first_argument_type a_hash,
                            second_argument_type a_tableSize) const;
  };

  template <typename T_Key, typename T_Hasher, typename T_HashToRange>
  struct range_hash_default : public T_Hasher, public T_HashToRange
  {
    typedef T_Hasher      hasher;
    typedef T_HashToRange hash_to_range_type;

    DECL_BINARY_FUNC(T_Key,
                     typename hash_to_range_type::second_argument_type,
                     typename hash_to_range_type::result_type);

    result_type operator() (first_argument_type a_key,
                            second_argument_type a_bucketCount) const;
  };

  // ///////////////////////////////////////////////////////////////////////
  // HashTableElementBase

  template <bool T_StoreHash>
  struct HashtableElementBase_TI;

  template <>
  struct HashtableElementBase_TI<true>
  {
  public:
    typedef tl_size           size_type;

    HashtableElementBase_TI() : m_hash(0) { }

    size_type GetHash() const { return m_hash; }
    void      SetHash(size_type a_hash) { m_hash = a_hash; }

  private:
    size_type   m_hash;
  };

  template <>
  struct HashtableElementBase_TI<false>
  {
  public:
    typedef tl_size           size_type;

    size_type GetHash() const { return 0; }
    void      SetHash(size_type ) { }
  };

  ///-------------------------------------------------------------------------
  /// @brief
  /// The standard creates a hash_node instead which is a simple linked
  /// list. We allow the user to choose the type of container they chose
  /// as long as it can accomodate this class as `T`.
  ///-------------------------------------------------------------------------
  template <typename T_Value, bool T_StoreHash = false>
  struct HashtableElement
    : public HashtableElementBase_TI<T_StoreHash>
  {
  public:
    typedef HashtableElementBase_TI<T_StoreHash>    base_type;
    typedef tl_size                                 size_type;
    typedef const tl_size                           const_size_type;
    typedef T_Value                                 value_type;
    typedef const T_Value                           const_value_type;

    typedef HashtableElement<value_type, T_StoreHash> this_type;

  public:
    HashtableElement();
    HashtableElement(const value_type& a_value, const size_type& a_hash);

    this_type operator=(const this_type& a_other)
    {
      m_value = a_other.m_value;
      base_type::SetHash(a_other.GetHash());
      return *this;
    }

    using base_type::GetHash;
    using base_type::SetHash;

    value_type&       GetValue() { return m_value; }
    const value_type& GetValue() const { return m_value; }

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(value_type, SetValue, m_value);

  private:
    value_type        m_value;
  };

  //////////////////////////////////////////////////////////////////////////
  // Iterators

  template <typename T_Policies, bool T_Const>
  class HashtableItrBase
  {
  public:
    template <typename T_PoliciesF> friend class Hashtable;

    typedef HashtableItrBase<T_Policies, T_Const>    this_type;

    typedef T_Policies                               policy_type;
    typedef typename policy_type::bucket_type        bucket_type;
    typedef typename policy_type::buckets_array_type b_array_type;
    typedef typename policy_type::size_type          size_type;
    typedef typename policy_type::value_type         value_type;

    typedef typename Loki::Select<T_Const,
                                  const value_type*,
                                  value_type*>::Result        pointer;
    typedef typename Loki::Select<T_Const,
                                  const value_type&,
                                  value_type&>::Result        reference;
    typedef typename Loki::Select<T_Const, const b_array_type,
                                  b_array_type>::Result       bucket_array_type;
    typedef typename Loki::Select<T_Const, const b_array_type*,
                                  b_array_type*>::Result      bucket_array_type_ptr;
    typedef typename Loki::Select<T_Const,
      typename bucket_type::const_iterator,
      typename bucket_type::iterator>::Result                 bucket_iterator;
    typedef typename Loki::Select<T_Const,
      typename bucket_array_type::const_iterator,
      typename bucket_array_type::iterator>::Result           local_iterator;

  public:
    HashtableItrBase();
    HashtableItrBase(bucket_array_type_ptr a_bucketContainer);
    HashtableItrBase(bucket_array_type_ptr a_bucketContainer,
      const local_iterator& a_currBucket, const bucket_iterator& a_currNode);

    void IncrementBucket();
    void Increment();

    this_type& operator=(const this_type& a_other);
    bool       operator==(const this_type& a_other);
    bool       operator!=(const this_type& a_other);

    const bucket_iterator&      GetNode() const;
    const bucket_array_type_ptr GetBucketArray() const;
    const local_iterator&       GetCurrBucket() const;

    // Used mostly for testing
    Pair<bool, size_type>     GetCurrBucketNumber() const;

  //protected:

    bucket_array_type_ptr m_bucketContainer;
    local_iterator        m_currBucket;
    bucket_iterator       m_currNode;

    // Used to mark end() iterator's m_currNode because we cannot dereference
    // the end of the bucket container to get a reference to a bucket_type.
    static bucket_iterator m_dummyNode;
  };

  template <typename T_Policies, bool T_Const>
  class HashtableItr : public HashtableItrBase<T_Policies, T_Const>
  {
  public:

    typedef HashtableItrBase<T_Policies, T_Const>     base_type;
    typedef HashtableItr<T_Policies, T_Const>         this_type;

    // The non-const type is used for the copy constructor. This is because
    // we cannot
    typedef HashtableItr<T_Policies, false>     this_type_non_const;

    typedef typename base_type::bucket_array_type bucket_array_type;
    typedef typename base_type::bucket_array_type_ptr bucket_array_type_ptr;
    typedef typename base_type::local_iterator    local_iterator;
    typedef typename base_type::bucket_iterator   bucket_iterator;
    typedef typename base_type::value_type        value_type;
    typedef typename base_type::pointer           pointer;
    typedef typename base_type::reference         reference;

    typedef tl_ptrdiff                          difference_type;
    typedef forward_iterator_tag                iterator_category;

  public:
    HashtableItr();
    HashtableItr(bucket_array_type_ptr a_bucketContainer);
    HashtableItr(bucket_array_type_ptr a_bucketContainer,
                 const local_iterator& a_currBucket,
                 const bucket_iterator& a_currNode);
    HashtableItr(const this_type_non_const& a_other);

    reference   operator*() const;
    pointer     operator->() const;

    this_type&  operator++();
    this_type   operator++(int);

  };


  ///-------------------------------------------------------------------------
  /// Prime rehash policy. One of the available rehash policies. This one is
  /// referenced from EASTL and changed where deemed fit.
  ///-------------------------------------------------------------------------
  struct prime_rehash_policy
  {
    typedef tl_size size_type;

    f32             m_maxLoadFactor;
    f32             m_growthFactor;
    mutable tl_uint m_nextResize;

    prime_rehash_policy(f32 a_maxLoadFactor = 1.0f);

    void                  set_max_load_factor(f32 a_maxLoadFactor);
    f32                   get_max_load_factor() const;
    size_type             get_next_bucket_count(size_type a_bucketCountHint) const;
    size_type             get_bucket_count(size_type a_numOfElements) const;
    Pair<bool, size_type> get_rehash_required(size_type a_numOfBuckets,
      size_type a_numOfElements, size_type a_numOfElementsToAdd) const;
  };

  //------------------------------------------------------------------------
  // Hashtable hashcode base
  // NOTES: We deviated heavily from EASTL as far as the implementation goes so
  // that we minimize duplicate code and avoid wasted space when any of the
  // hash function objects are essentially empty classes

  template <typename T_Policy>
  class HashCodeBase : protected T_Policy::extract_key_type,
                       protected T_Policy::key_equal,
                       protected T_Policy::range_hasher_type
  {
  public:
    //------------------------------------------------------------------------
    // typdefs

    typedef tl_uint                              hash_code_type;

    typedef typename T_Policy::bucket_type       bucket_type;
    typedef typename T_Policy::element_type      element_type;
    typedef typename T_Policy::value_type        value_type;
    typedef typename T_Policy::key_type          key_type;
    typedef typename T_Policy::range_hasher_type range_hasher_type;
    typedef typename T_Policy::extract_key_type  extract_key_type;
    typedef typename T_Policy::key_equal         key_equal;
    typedef typename T_Policy::size_type         size_type;

    typedef typename range_hasher_type::hasher             hasher;
    typedef typename range_hasher_type::hash_to_range_type hash_to_range_type;

    //------------------------------------------------------------------------
    // Methods

    hash_code_type get_hash_code(const key_type& a_key) const
    { return (hash_code_type)hasher::operator()(a_key); }

    size_type bucket_index(const tl_uint& a_key, size_type a_bucketCount) const
    {
      typedef typename hash_to_range_type::first_argument_type  arg1;
      typedef typename hash_to_range_type::second_argument_type arg2;

      return (size_type)hash_to_range_type::operator()
        ( (arg1)a_key, (arg2)a_bucketCount);
    }

    size_type bucket_index(const tl_uint&, hash_code_type a_hash,
                           tl_uint a_bucketCount) const
    {
      typedef typename hash_to_range_type::first_argument_type  arg1;
      typedef typename hash_to_range_type::second_argument_type arg2;

      return (size_type)hash_to_range_type::operator()
        ( (arg1)a_hash, (arg2)a_bucketCount);
    }

    size_type bucket_index(const element_type& a_elem, size_type a_bucketCount) const
    {
      typedef typename range_hasher_type::first_argument_type  arg1;
      typedef typename range_hasher_type::second_argument_type arg2;
      typedef typename range_hasher_type::result_type          res;

      return (res)range_hasher_type::operator()
        ((arg1)extract_key_type::operator()( a_elem.GetValue()), (arg2)a_bucketCount);
    }

    key_type extract_key(const value_type& a_value) const
    { return extract_key_type::operator()(a_value); }
  };

  template <typename T_Policy, typename T_CacheHash>
  class HashCode { };

  template <typename T_Policy>
  class HashCode<T_Policy, type_false> : public HashCodeBase<T_Policy>
  {
  public:
    typedef HashCodeBase<T_Policy>                base_type;
    typedef typename base_type::key_type          key_type;
    typedef typename base_type::hash_code_type    hash_code_type;
    typedef typename base_type::element_type      element_type;
    typedef typename base_type::extract_key_type  extract_key_type;
    typedef typename base_type::key_equal         key_equal;

    hash_code_type get_hash_code(const key_type& a_key) const
    {
      return base_type::get_hash_code(a_key);
    }

    hash_code_type get_hash_code(const element_type& a_elem) const
    {
      return get_hash_code(extract_key_type::operator()(a_elem.GetValue()));
    }

    bool compare (hash_code_type a_hashcode, element_type* a_elem) const
    {
      return a_hashcode == get_hash_code(extract_key_type::operator()(a_elem->GetValue()));
    }

    bool compare (const key_type& a_key, hash_code_type, element_type* a_elem) const
    { return key_equal::operator()
    (a_key, extract_key_type::operator()(a_elem->GetValue())); }
  };

  template <typename T_Policy>
  class HashCode<T_Policy, type_true> : public HashCodeBase<T_Policy>
  {
  public:
    typedef HashCodeBase<T_Policy>  base_type;
    typedef typename base_type::key_type          key_type;
    typedef typename base_type::hash_code_type    hash_code_type;
    typedef typename base_type::element_type      element_type;
    typedef typename base_type::extract_key_type  extract_key_type;
    typedef typename base_type::key_equal         key_equal;

    hash_code_type get_hash_code(const key_type& a_key) const
    {
      return base_type::get_hash_code(a_key);
    }

    hash_code_type get_hash_code(const element_type& a_elem) const
    {
      return a_elem.GetHash();
    }

    bool compare (hash_code_type a_hashcode, element_type* a_elem) const
    {
      return a_hashcode == a_elem->GetHash();
    }

    bool compare (const key_type& a_key, hash_code_type a_hashCode,
                  element_type* a_elem) const
    { return (a_elem->GetHash() == a_hashCode) && key_equal::operator()
    (a_key, extract_key_type::operator()(a_elem->GetValue())); }
  };

  //------------------------------------------------------------------------
  // Hashtable Policy

  template <typename T_Key, typename T_ExtractKey, typename T_HashFunc,
    typename T_HashToRange,
    template <typename T_KeyF, typename T_HashFuncF, typename T_HashToRangeF> class T_RangeHashFunc,
    typename T_KeyEqual,
    typename T_RehashPolicy, typename T_BucketType,
    bool T_CacheHashCode, bool T_UniqueKeys>

  ///-------------------------------------------------------------------------
  /// A policy class that combines all the policies with all the necessary
  /// typedefs.
  ///
  /// - T_Key: Any object that is compatible with the T_HashFunc for conversion
  /// of the key to a hash.
  /// - T_ExtractKey: A function object that tells us how to get the key from
  /// the value object. The value object may be as simple as a pair (storing
  /// the key and the value) or it may be more complex in which case we want to
  /// know how to extract the 'key' from the complex 'value' object.
  /// - T_RangeHashFunc<>: A template class that takes in the Key, the hash
  /// function and the hash to range function. This class essentially returns
  /// the correct bucket number from the key by using the hash function and the
  /// range hash function.
  /// - T_BucketType: The container for storing the buckets of a container of
  /// some type. The container must be such that:
  /// BucketContainer<ElementContainer< HashtableElement<T>>> where
  /// BucketContainer and ElementContainer can be the same type containers. For
  /// example: List<List<HashtableElement<s32>>>
  ///-------------------------------------------------------------------------
  struct HashtablePolicy
  {
    typedef T_Key						          key_type;
    typedef T_ExtractKey              extract_key_type;
    typedef T_HashFunc                hasher; // No _type because the standard says so
    typedef T_HashToRange		          hash_to_range_type;
    typedef T_RangeHashFunc<key_type, hasher, hash_to_range_type> range_hasher_type;
    typedef T_KeyEqual			          key_equal;
    typedef T_BucketType		          buckets_array_type;
    typedef T_RehashPolicy	          rehash_policy_type;

    typedef typename buckets_array_type::value_type bucket_type;
    typedef typename bucket_type::value_type        element_type;
    typedef typename element_type::value_type       value_type;

    typedef tl_ptrdiff     difference_type;
    typedef tl_size        size_type;

    typedef typename Loki::Int2Type<T_CacheHashCode> cache_hash;
    typedef typename Loki::Int2Type<T_UniqueKeys>    unique_keys;
  };

  //------------------------------------------------------------------------
  // Hashtable itself

  template <typename T_Policies>

  ///-------------------------------------------------------------------------
  /// The Hashtable is a base class for associative containers like the
  /// Hashmap. We used EASTL and SGI as reference but tried to keep it as
  /// simple as possible while retaining some flexibility.
  ///
  /// @note Public inheritance from Hashcode<> may seem complicated but it
  /// really isn't. The second parameter is determining whether in T_Policies,
  /// unique_keys was true or not.
  ///
  /// @sa
  /// tloc::core::HashCode<T_Policies,Loki::IsSameType<typename T_Policies::unique_keys,type_true>::value>
  ///-------------------------------------------------------------------------
  class Hashtable : public HashCode<T_Policies, typename T_Policies::cache_hash>
  {
  public:
    //////////////////////////////////////////////////////////////////////////
    // Typedefs

    typedef Hashtable<T_Policies>                   this_type;
    typedef HashCode<T_Policies,
            typename T_Policies::cache_hash>        base_type;
    typedef T_Policies                              policy_type;

    // typedefs from T_Policies
    typedef typename policy_type::key_type					 key_type;
    typedef typename policy_type::value_type				 value_type;
    typedef typename policy_type::element_type			 element_type;
    typedef typename policy_type::hasher             hasher;
    typedef typename policy_type::key_equal					 key_equal;
    typedef typename policy_type::bucket_type        bucket_type;
    typedef typename policy_type::buckets_array_type buckets_array_type;
    typedef typename policy_type::size_type					 size_type;
    typedef typename policy_type::rehash_policy_type rehash_policy_type;

    typedef HashtableItr<policy_type, false>         iterator;
    typedef HashtableItr<policy_type, true>          const_iterator;

    typedef typename policy_type::cache_hash		     cache_hash;
    typedef typename policy_type::unique_keys        unique_keys;
    typedef typename
      Loki::Select< Loki::IsSameType<unique_keys,
                    type_true>::value,
                    Pair<iterator, bool>,
                    iterator >::Result               insert_return_type;

    typedef typename
      Loki::Select< Loki::IsSameType<unique_keys,
      type_true>::value, use_first<insert_return_type>,
      use_self<insert_return_type> >::Result            insert_return_selector;

    typedef typename buckets_array_type::iterator       local_iterator;
    typedef typename buckets_array_type::const_iterator const_local_iterator;
    typedef typename bucket_type::iterator              bucket_iterator;
    typedef typename bucket_type::const_iterator        const_bucket_iterator;

    typedef typename iterator_traits
      <bucket_iterator>::iterator_category              bucket_iterator_type;

    typedef core::reverse_iterator<iterator>            reverse_iterator;
    typedef core::reverse_iterator<const_iterator>      const_reverse_iterator;

    typedef tl_ptrdiff                                  difference_type;
    typedef HashCode<T_Policies, unique_keys>           hash_code_base_type;

    // typedefs inherited from HashCode<>
    typedef typename hash_code_base_type::hash_code_type    hash_code_type;

    //////////////////////////////////////////////////////////////////////////
    // using declarations for access to base class

    using base_type::bucket_index;
    using base_type::extract_key;
    using base_type::get_hash_code;
    using base_type::compare;

    //////////////////////////////////////////////////////////////////////////
    // Methods

    //------------------------------------------------------------------------
    // Constructors

    ///-------------------------------------------------------------------------
    /// Default constructor.
    ///-------------------------------------------------------------------------
    Hashtable();

    ///-------------------------------------------------------------------------
    /// Construct a Hashtable with at least a_bucketCount buckets.
    ///
    /// @param  a_bucketCount Number of buckets.
    ///-------------------------------------------------------------------------
    Hashtable(size_type a_bucketCount);

    ///-------------------------------------------------------------------------
    /// Copy constructor.
    ///
    /// @param  a_other The other hashtable.
    ///-------------------------------------------------------------------------
    Hashtable(const this_type& a_other);

    ///-------------------------------------------------------------------------
    /// Destructor.
    ///-------------------------------------------------------------------------
    ~Hashtable();

    this_type&  operator=(const this_type& a_other);

    //------------------------------------------------------------------------
    // Iterator Access

    iterator        begin();
    const_iterator  begin() const;

    iterator        end();
    const_iterator  end() const;

    bucket_iterator			  begin(size_type a_bucketNumber);
    const_bucket_iterator begin(size_type a_bucketNumber) const;
    bucket_iterator			  end(size_type a_bucketNumber);
    const_bucket_iterator end(size_type a_bucketNumber) const;

    //------------------------------------------------------------------------
    // Capacity

    size_type       size() const;
    size_type       bucket_count() const;
    size_type       bucket_size(size_type a_bucketNumber) const;

    //------------------------------------------------------------------------
    // Hashing queries

    f32									load_factor() const;

    ///-------------------------------------------------------------------------
    /// Gets the current rehash policy.
    ///
    /// @return rehash_policy_type The current rehash policy.
    ///-------------------------------------------------------------------------
    const rehash_policy_type&	get_rehash_policy() const;

    ///-------------------------------------------------------------------------
    /// Sets a rehash policy. This function is added just for the sake of
    /// completeness. It is better to create a new hashtable with a different
    /// hash policy.
    ///
    /// @param  rehash_policy_type The new rehash policy.
    ///-------------------------------------------------------------------------
    void								set_rehash_policy(const rehash_policy_type&
                                            a_rehashPolicy);

    ///-------------------------------------------------------------------------
    /// Gets the maximum load factor. This function calls overloads that take
    /// in their respective rehash policy.
    ///
    /// @return The maximum load factor.
    ///-------------------------------------------------------------------------
    f32                 get_max_load_factor() const;

    ///-------------------------------------------------------------------------
    /// Sets a maximum load factor. This funtion calls the overloads that take
    /// in their respective rehash policy.
    ///
    /// @param  a_maxLoadFactor The maximum load factor.
    ///-------------------------------------------------------------------------
    void                set_max_load_factor(f32 a_maxLoadFactor);

    //------------------------------------------------------------------------
    // Modifiers

    insert_return_type  insert(const value_type& a_value);
    iterator						insert(const_iterator a_position,
                               const value_type& a_value);
    template <typename T_InputItr>
    void                insert(T_InputItr a_first, T_InputItr a_last);

    ///-------------------------------------------------------------------------
    /// Please note that this operation is a bit slower for Hashtables with the
    /// buckets as list<singly_linked> or Vector_T<> that maintains element order
    /// when erasing (instead of using swap() and pop_back() - check Array<>
    /// policies).
    ///
    /// @param  a_position The position.
    ///
    /// @return .
    ///-------------------------------------------------------------------------
    iterator            erase(iterator a_position);
    iterator            erase(iterator a_first, iterator a_last);
    //reverse_iterator    erase(reverse_iterator a_position);
    //reverse_iterator    erase(reverse_iterator a_first, reverse_iterator a_last);
    size_type           erase(const key_type& a_key);

    void                clear();

    //------------------------------------------------------------------------
    // Operations

    iterator        find(const key_type& a_key);
    const_iterator  find(const key_type& a_key) const;

    ///-------------------------------------------------------------------------
    /// Non-standard function that is present in EASTL as well. Use this when
    /// providing your own hash code to prevent the usual find() function from
    /// recalculating the hash (which may be an expensive operation especially
    /// if carried out multiple times)
    ///
    /// @param  a_hashCode The hash code.
    ///
    /// @return
    /// iterator or const_iterator to the found object or end() if not
    /// found.
    ///-------------------------------------------------------------------------
    iterator        find_by_hash(tl_uint a_hashCode);
    const_iterator  find_by_hash(tl_uint a_hashCode) const;

    size_type       count(const key_type& a_key) const;

    Pair<iterator, iterator>             equal_range(const key_type& a_key);
    Pair<const_iterator, const_iterator> equal_range
                                                  (const key_type& a_key) const;

  protected:

    void            DoAllocateBuckets(size_type a_numBuckets);

    //--------------------------------------------------------------------------
    // Find Helpers

    ///-------------------------------------------------------------------------
    /// Non-standard functions formulated from EASTL. DoFindNode performs a
    /// search with the key provided with a certain bucket in the bucket array.
    /// The search is performed by a default comparison if a key is not
    /// provided. If a key is provided the search is performed with the
    /// comparison predicate provided.
    ///
    /// @param [in,out] a_itr The iterator that points to the bucket we want to
    ///                       search.
    /// @param  a_key         The key that is tied with the element.
    /// @param  a_hashCode    The hash code.
    ///
    /// @return
    /// Iterator to element, within the bucket. End of bucket is
    /// returned if not found.
    ///-------------------------------------------------------------------------
    bucket_iterator DoFindNode(local_iterator& a_itr, const key_type& a_key,
                                     hash_code_type a_hashCode) const;
    bucket_iterator DoFindNode(local_iterator& a_itr,
                                     hash_code_type a_hashCode) const;

    //------------------------------------------------------------------------
    // Insert helpers

    /// Used by DoInsertValue()
    typedef type_true  keys_are_unique;
    typedef type_false keys_are_not_unique;

    Pair<iterator, bool>  DoInsertValue(const value_type& a_value,
                                              keys_are_unique);
    iterator              DoInsertValue(const value_type& a_value,
                                              keys_are_not_unique);

    ///-------------------------------------------------------------------------
    /// This function is for internal use only. It selects push_front() or
    /// push_back() depending on the type of iterator. It assumes that the
    /// iterator is valid.
    ///
    /// @param  a_itr         The bucket to which the element will be added
    /// @param  a_elem        The element to add
    ///
    /// @return Iterator to the inserted element
    ///-------------------------------------------------------------------------
    template <TLOC_DUMMY_TYPE>
    bucket_iterator DoPushSelect (local_iterator& a_itr,
      const element_type& a_elem, forward_iterator_tag);
    template <TLOC_DUMMY_TYPE>
    bucket_iterator DoPushSelect (local_iterator& a_itr,
      const element_type& a_elem, bidirectional_iterator_tag);

    ///-------------------------------------------------------------------------
    /// The function is for internal use only. It selects insert_after() or
    /// insert() depending on the type of iterator. It assumes that the
    /// iterator is valid.
    ///
    /// @param [in,out] a_currNode The node after or before which to insert
    /// @param  a_elem             The element to insert
    ///
    /// @return Iterator to the inserted element
    ///-------------------------------------------------------------------------
    template <TLOC_DUMMY_TYPE>
    bucket_iterator DoInsertSelect (local_iterator& a_itr,
      bucket_iterator a_currNode, const element_type& a_elem,
      forward_iterator_tag);
    template <TLOC_DUMMY_TYPE>
    bucket_iterator DoInsertSelect (local_iterator& a_itr,
      bucket_iterator a_currNode, const element_type& a_elem,
      bidirectional_iterator_tag);

    //------------------------------------------------------------------------
    // Erase helpers

    iterator DoErase(iterator a_position, forward_iterator_tag);
    iterator DoErase(iterator a_position, bidirectional_iterator_tag);

    size_type DoErase(const key_type& a_key, keys_are_unique);
    size_type DoErase(const key_type& a_key, keys_are_not_unique);

    //------------------------------------------------------------------------
    // Count helpers

    size_type DoCount(const key_type& a_key, keys_are_unique) const;
    size_type DoCount(const key_type& a_key, keys_are_not_unique) const;

    //------------------------------------------------------------------------
    // Rehashing

    void DoRehash(size_type a_bucketCount);

    //------------------------------------------------------------------------
    // Load factor overloads and sanity checks

    template <typename T>
    f32               DoGetMaxLoadFactor(T) const
    {
      TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value),
                         Rehash_policy_type_not_supported);
    }

    template <typename T>
    void              DoSetMaxLoadFactor(f32, T)
    {
      TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value),
                         Rehash_policy_type_not_supported);
    }

    f32               DoGetMaxLoadFactor(prime_rehash_policy) const;
    void              DoSetMaxLoadFactor(f32 a_maxLoadFactor,
                                               prime_rehash_policy);

  protected:
    template<typename, bool> friend class HashtableItrBase;

    //////////////////////////////////////////////////////////////////////////
    // Variables

    buckets_array_type m_bucketArray;
    size_type          m_elementCount;
    rehash_policy_type m_rehashPolicy;
  };

};};};

#endif
