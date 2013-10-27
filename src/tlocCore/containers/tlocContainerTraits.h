#ifndef _TLOC_CORE_CONTAINERS_TYPE_TRAITS_H_
#define _TLOC_CORE_CONTAINERS_TYPE_TRAITS_H_

#include <tlocCore/containers/tlocContainers.h>

namespace tloc { namespace core { namespace containers { namespace type_traits {

  // ------------------------------------------------------------------------
  //  Container types
  //
  //  @note this 'should' be in tlocTypeTraits, but due to circular
  //  dependencies, we have to separate out container traits.

  template <typename T>
  struct IsContainer
  { static const bool value = false; };

  template <typename T, typename T_Policy>
  struct IsContainer< core_conts::Array<T, T_Policy> >
  { static const bool value = true; };

  template <typename T, typename T_Node, typename T_Policy, bool T_DedicatedSize>
  struct IsContainer< core_conts::List<T, T_Node, T_Policy, T_DedicatedSize> >
  { static const bool value = true; };

  template <typename T_Key, typename T_ValueType,
    typename T_HashFunc,
    typename T_KeyEqual,
    bool T_CacheHashCode,
    typename T_BucketType>
  struct IsContainer
    <
    core_conts::HashMap
    <T_Key, T_ValueType, T_HashFunc, T_KeyEqual, T_CacheHashCode,
    T_BucketType>
    >
  { static const bool value = true; };

};};};};

#endif