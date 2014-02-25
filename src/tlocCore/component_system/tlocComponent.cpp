#include "tlocComponent.h"
#include "tlocComponent.inl.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::Component*);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::component_sptr);
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(tloc::core_cs::Component);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core_cs::Component);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(tloc::core_cs::Component);