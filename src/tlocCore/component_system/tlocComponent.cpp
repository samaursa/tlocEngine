#include "tlocComponent.h"
#include "tlocComponent.inl"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace core { namespace component_system {

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Component);

  template class containers::ArrayBase<Component*>;
  template class containers::Array<Component*>;

  template class containers::ArrayBase<component_sptr>;
  template class containers::Array<component_sptr>;

};};};