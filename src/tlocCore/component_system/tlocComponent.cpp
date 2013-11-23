#include "tlocComponent.h"
#include "tlocComponent.inl.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::Component*);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::component_sptr);
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(tloc::core_cs::Component);