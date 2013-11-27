#include "tlocJoystickImpl.h"

#include <tlocCore/containers/tlocArrayFixed.inl.h>

namespace tloc { namespace input { namespace hid {

  TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(Component::Pov, 4);
  TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(Component::AxisAbs, 4);

};};};