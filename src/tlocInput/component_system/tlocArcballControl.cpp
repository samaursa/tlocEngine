#include "tlocArcBallControl.h"


namespace tloc { namespace input { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // ArcBallControl

  ArcBallControl::
    ArcBallControl()
    : base_type(k_component_type, "ArcBallControl")
    , m_globalMulti(1)
    , m_rotMulti(1)
    , m_panMulti(1)
    , m_dollyMulti(1)
  { }

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::input_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ArcBallControl);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(ArcBallControl);