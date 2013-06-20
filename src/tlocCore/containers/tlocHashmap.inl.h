#ifndef TLOC_HASH_MAP_INL
#define TLOC_HASH_MAP_INL

#ifndef TLOC_HASH_MAP_H
#error "Must include header before including inline file"
#endif

#include <tlocCore/tlocPair.inl.h>
#include <tlocCore/containers/tlocHashtable.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/containers/tlocList.inl.h>

#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // HashMap

  //------------------------------------------------------------------------
  // Template Macros

#define HASH_MAP_TYPES typename T_Key, typename T_ValueType, \
  typename T_HashFunc, typename T_KeyEqual, bool T_CacheHashCode, \
  typename T_BucketType
#define HASH_MAP_PARAMS T_Key, T_ValueType, T_HashFunc, T_KeyEqual, \
  T_CacheHashCode, T_BucketType

  //------------------------------------------------------------------------
  // Constructors

  template <HASH_MAP_TYPES>
  TL_FI HashMap<HASH_MAP_PARAMS>::HashMap()
    : base_type()
  {
  }

  template <HASH_MAP_TYPES>
  TL_FI HashMap<HASH_MAP_PARAMS>::HashMap(size_type aBucketCount,
                                          const T_HashFunc& aHashFunction,
                                          const T_KeyEqual& aKeyEqual)
    : base_type(aBucketCount)
  {
  }

  //------------------------------------------------------------------------
  // Modifiers

  //------------------------------------------------------------------------
  // Operations

  template <HASH_MAP_TYPES>
  TL_FI typename HashMap<HASH_MAP_PARAMS>::mapped_type&
    HashMap<HASH_MAP_PARAMS>::operator[](const key_type& aKey)
  {
    typename base_type::iterator itr = base_type::find(aKey);
    if (itr != base_type::end())
    {
      return (*itr).second;
    }
    else
    {
      return (*base_type::insert(value_type(aKey, mapped_type())).first).second;
    }
  }

};};};


#endif