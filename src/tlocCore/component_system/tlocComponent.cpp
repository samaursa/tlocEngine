#include "tlocComponent.h"
#include "tlocComponent.inl.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace tloc { namespace core { namespace component_system {

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Component);

  template class containers::ArrayBase<Component*>;
  template class containers::Array<Component*>;

  template class containers::ArrayBase<component_sptr>;
  template class containers::Array<component_sptr>;

};};};