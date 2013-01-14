#ifndef TLOC_HASH_MAP_H
#define TLOC_HASH_MAP_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/tlocPair.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocHashtable.h>

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_HASH_MAP
# define TLOC_ASSERT_HASH_MAP(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_HASH_MAP(_Expression, _Msg)
#endif

namespace tloc { namespace core { namespace containers {

  template <typename T_Key, typename T_ValueType,
            typename T_HashFunc = hash<T_Key>,
            typename T_KeyEqual = equal_to<T_Key>,
            bool T_CacheHashCode = false,
            typename T_BucketType
            = Array<List<HashtableElement<Pair</*const*/T_Key, T_ValueType>, T_CacheHashCode > > > >
  class HashMap
    : public Hashtable<
                       HashtablePolicy<T_Key,
                       use_first<typename T_BucketType::value_type::value_type::value_type >,
                       T_HashFunc, hash_to_range_mod, range_hash_default,
                       T_KeyEqual, prime_rehash_policy, T_BucketType,
                       T_CacheHashCode, true> >
  {
  public:
    //////////////////////////////////////////////////////////////////////////
    // Typedefs

    typedef Hashtable<
                       HashtablePolicy<T_Key,
                       use_first<typename T_BucketType::value_type::value_type::value_type >,
                       T_HashFunc, hash_to_range_mod, tloc::core::containers::range_hash_default,
                       T_KeyEqual, prime_rehash_policy, T_BucketType,
                       T_CacheHashCode, true> >                     base_type;
    typedef HashMap<T_Key, T_ValueType, T_HashFunc, T_KeyEqual,
                    T_CacheHashCode, T_BucketType>                  this_type;

    // Typedefs from T_Policies
    typedef typename base_type::size_type                           size_type;
    typedef typename base_type::key_type                            key_type;
    typedef T_ValueType                                             mapped_type;
    typedef typename base_type::value_type                          value_type;
    typedef typename base_type::element_type                        node_type;
    typedef typename base_type::insert_return_type                  insert_return_type;
    typedef typename base_type::iterator                            iterator;

    //////////////////////////////////////////////////////////////////////////
    // Methods

    //------------------------------------------------------------------------
    // Constructors

    TL_FI explicit HashMap();
    TL_FI explicit HashMap(size_type aBucketCount,
                           const T_HashFunc& aHashFunction = T_HashFunc(),
                           const T_KeyEqual& aKeyEqual = T_KeyEqual());
    // TODO: Implement an iterator copy constructor

    //------------------------------------------------------------------------
    // Modifiers

    // TODO: Implement an "insert" function that only takes in a key, and makes it paired with a default constructed mapped_type
    // This ultimately prevents us from creating the pair (ultimately copying
    // the element) and then copying it into the hash_map. We can simply create
    // a spot in the hash_map with the key, and then copy the value directly
    // to that spot.

    //------------------------------------------------------------------------
    // Operations

    TL_FI mapped_type& operator[](const key_type& aKey);
  };

};};};

#endif