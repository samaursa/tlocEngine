#include "tlocEntity.h"
#include "tlocEntity.inl.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::Entity::component_list);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::Entity*);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::entity_sptr);
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(tloc::core_cs::Entity);