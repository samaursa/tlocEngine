#ifndef TLOC_CONTAINERS_H
#define TLOC_CONTAINERS_H

// This file includes all containers found in the engine and provides typedefs
// for them. The idea is that the containers can be swapped out across the
// complete engine at any point in time without re-writing code

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocStackArray.h>
#include <tlocCore/containers/tlocStack.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocHashmap.h>

namespace tloc { namespace core {

  template <typename T, typename T_Policy = Array_Ordered>
  struct tl_array
  {
    DECL_TYPEDEF_HELPER(tl_array);
    typedef Array<T, T_Policy>        type;
  };

  template <typename T, tl_size T_Capacity>
  struct tl_array_fixed
  {
    DECL_TYPEDEF_HELPER(tl_array_fixed);
    typedef StackArray<T, T_Capacity> type;
  };

  template <typename T, bool T_DedicatedSize = true>
  struct tl_singly_list
  {
    DECL_TYPEDEF_HELPER(tl_singly_list);
    typedef List<T, ListNode<T, singly_linked_tag>, List_Dynamic(),
                 T_DedicatedSize> type;
  };

  template <typename T, bool T_DedicatedSize = true>
  struct tl_doubly_list
  {
    DECL_TYPEDEF_HELPER(tl_doubly_list);
    typedef List<T, ListNode<T, doubly_linked_tag>, List_Dynamic(),
                 T_DedicatedSize> type;
  };

  template <typename T_Key, typename T_Value>
  struct tl_hash_map
  {
    DECL_TYPEDEF_HELPER(tl_hash_map);
    typedef HashMap<T_Key, T_Value>   type;
  };

  // Common containers
  typedef tl_array<tl_int>::type    tl_array_int;
  typedef tl_array<tl_uint>::type   tl_array_uint;
  typedef tl_array<tl_float>::type  tl_array_float;
  typedef tl_array<tl_size>::type   tl_array_size;

};};

#endif