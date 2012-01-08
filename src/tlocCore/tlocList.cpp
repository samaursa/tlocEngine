#include "tlocList.h"
#include "tlocList.inl"

namespace tloc { namespace core {

  template List<f32>;
  template List<s32, ListNode<s32, singly_linked_tag> >;

};};