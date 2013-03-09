#include "tlocComponent.h"
#include "tlocComponent.inl"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace core { namespace component_system {

  template class smart_ptr::SharedPtr<Component>;
  template class smart_ptr::SharedPtr<const Component>;

  template class containers::ArrayBase<Component*>;
  template class containers::Array<Component*>;

  template class containers::ArrayBase<component_sptr>;
  template class containers::Array<component_sptr>;

};};};