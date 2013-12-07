#include "tlocJoystickImpl.h"

#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/containers/tlocArrayFixed.inl.h>

using namespace tloc::input_hid;

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(JoystickEvent::axis_type);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(JoystickEvent::slider_type, 4);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(JoystickEvent::pov_type, 4);
