#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#define protected public
#define private public
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntityManager.inl>

namespace TestingEntityManager
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  struct EmptyComponent1 : public Component
  {
    EmptyComponent1() : Component(components::transform) {}
  };

  struct EmptyComponent2 : public Component
  {
    EmptyComponent2() : Component(components::mesh) {}
  };

  TEST_CASE("Core/component_system/EntityManager/Ctor", "")
  {
  }
};