#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#define protected public
#define private public
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl>
#include <tlocCore/component_system/tlocComponent.h>

namespace TestingEntity
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  components::value_type  g_component = components::listener;

  struct EmptyComponent1 : public Component
  {
    EmptyComponent1() : Component(g_component) {}
  };

  struct EmptyComponent2 : public Component
  {
    EmptyComponent2() : Component(g_component + 1) {}
  };

  TEST_CASE("Core/component_system/entity/entity", "")
  {
    Entity* e = new Entity(0);

    CHECK(e->GetID() == 0);
    CHECK(e->GetComponentsList().size() == (tl_size)components_group::count);

    e->SetID(1);
    CHECK(e->GetID() == 1);

    e->SetIndex(1);
    CHECK(e->GetIndex() == 1);

    EmptyComponent1 c1;
    EmptyComponent2 c2;

    CHECK(e->HasComponent(g_component) == false);
    CHECK(e->HasComponent(g_component + 1) == false);

    e->InsertComponent(&c1);
    CHECK(e->HasComponent(g_component) == true);
    CHECK(e->HasComponent(g_component + 1) == false);

    e->InsertComponent(&c2);
    CHECK(e->HasComponent(g_component) == true);
    CHECK(e->HasComponent(g_component + 1) == true);

    Entity::component_list& clist = e->GetComponents(g_component);

    REQUIRE(clist.size() == 1);
    CHECK(clist[0] == &c1);

    clist = e->GetComponents(g_component + 1);
    REQUIRE(clist.size() == 1);
    CHECK(clist[0] == &c2);
  }
};