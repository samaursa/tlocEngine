#ifndef TLOC_CONTAINERS_H
#define TLOC_CONTAINERS_H

// This file includes all containers found in the engine and provides typedefs
// for them. The idea is that the containers can be swapped out across the
// complete engine at any point in time without re-writing code

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/containers/tlocStack.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocHashmap.h>

namespace tloc { namespace core { namespace containers {

  template <typename T, typename T_Policy = Array_Ordered>
  struct tl_array : public utils::TypedefHelperBase<T>
  {
    typedef Array<T, T_Policy>        type;
  };

  template <typename T, tl_size T_Capacity>
  struct tl_array_fixed : public utils::TypedefHelperBase<T>
  {
    typedef ArrayFixed<T, T_Capacity> type;
  };

  template <typename T, bool T_DedicatedSize = true>
  struct tl_singly_list : public utils::TypedefHelperBase<T>
  {
    typedef List<T, ListNode<T, singly_linked_tag>, List_Dynamic(),
                 T_DedicatedSize> type;
  };

  template <typename T, bool T_DedicatedSize = true>
  struct tl_doubly_list : public utils::TypedefHelperBase<T>
  {
    typedef List<T, ListNode<T, doubly_linked_tag>, List_Dynamic(),
                 T_DedicatedSize> type;
  };

  template <typename T_Key, typename T_Value>
  struct tl_hash_map : public utils::TypedefHelperBase<T_Key>
  {
    typedef HashMap<T_Key, T_Value>   type;
  };

  // Common containers
  typedef tl_array<tl_int>::type    tl_array_int;
  typedef tl_array<tl_uint>::type   tl_array_uint;
  typedef tl_array<tl_float>::type  tl_array_float;
  typedef tl_array<tl_size>::type   tl_array_size;

};};};

#endif