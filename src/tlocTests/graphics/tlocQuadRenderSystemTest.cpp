#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocQuadRenderSystem.h>

namespace TestingQuadRenderSystem
{
  using namespace tloc;
  using namespace tloc::graphics::component_system;

  TEST_CASE("Graphics/component_system/QuadRenderSystem", "")
  {
    // No tests for now, just instantiating the system to make sure it compiles
    // and links
    core_cs::event_manager_sptr evntMgr(new core_cs::EventManager());
    core_cs::entity_manager_sptr entityMgr(new core_cs::EntityManager(evntMgr));
    QuadRenderSystem qrs(evntMgr, entityMgr);
  }
};