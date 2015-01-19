#include "tlocBoundingBoxSystem.h"

#include <tlocGraphics/component_system/tlocBoundingBox.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBoxSystem

  BoundingBoxSystem::
    BoundingBoxSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entMgr)
    : base_type(a_eventMgr, a_entMgr,
                register_type().Add<BoundingBox2D>().Add<BoundingBox3D>(),
                "BoundingBoxSystem")
  { }


};};};