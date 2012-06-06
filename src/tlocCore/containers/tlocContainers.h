#ifndef TLOC_CONTAINERS_H
#define TLOC_CONTAINERS_H

// This file includes all containers found in the engine and provides typedefs
// for them. The idea is that the containers can be swapped out across the
// complete engine at any point in time without re-writing code

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocHashmap.h>

namespace tloc { namespace core {

  template <typename T, typename T_Policy = Array_Ordered>
  struct tl_array
  {
    DECL_TYPEDEF_HELPER(tl_array);
    typedef Array<T, T_Policy>        type;
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

};};

#endif