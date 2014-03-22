#include "tlocComponent.h"
#include "tlocComponent.inl.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core_cs::component_vptr);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::core_cs::Component);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(tloc::core_cs::Component);