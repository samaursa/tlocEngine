#include "tlocEntity.h"
#include "tlocEntity.inl.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace tloc { namespace core { namespace component_system {

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Entity);

  template class containers::ArrayBase<Entity::component_list>;
  template class containers::Array<Entity::component_list>;

  template class containers::ArrayBase<Entity*>;
  template class containers::Array<Entity*>;

  template class containers::ArrayBase<entity_sptr>;
  template class containers::Array<entity_sptr>;
};};};