#include "tlocComponent.h"
#include "tlocComponent.inl"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace core { namespace component_system {


  template class smart_ptr::SharedPtr<Component>;
  template class smart_ptr::SharedPtr<const Component>;

  template class core::Array<Component*>;
  template class core::Array<component_sptr>;

};};};