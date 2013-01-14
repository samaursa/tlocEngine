#include "tlocList.h"
#include "tlocList.inl"

namespace tloc { namespace core { namespace containers {

  template class List<s32>;
  template class List<f32>;
  template class List<s64>;
  template class List<f64>;
  template class List<s32, ListNode<s32, singly_linked_tag> >;
  template class List<f32, ListNode<f32, singly_linked_tag> >;
  template class List<s64, ListNode<s64, singly_linked_tag> >;
  template class List<f64, ListNode<f64, singly_linked_tag> >;

};};};