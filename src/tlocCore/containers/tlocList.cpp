#include "tlocList.h"
#include "tlocList.inl"

namespace tloc { namespace core {

  template List<s32>;
  template List<f32>;
  template List<s64>;
  template List<f64>;
  template List<s32, ListNode<s32, singly_linked_tag> >;
  template List<f32, ListNode<f32, singly_linked_tag> >;
  template List<s64, ListNode<s64, singly_linked_tag> >;
  template List<f64, ListNode<f64, singly_linked_tag> >;

};};