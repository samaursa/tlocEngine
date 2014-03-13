#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#define protected public
#define private public
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

namespace TestingEntity
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  const components::value_type  g_component = components::listener;

  struct Component1
    : public Component_T<Component1, g_component>
  {
    typedef Component_T<Component1, g_component>   base_type;

    Component1()
      : base_type(g_component)
      , m_value(0)
    { }

    tl_int m_value;
  };

  struct Component2
    : public Component_T<Component1, g_component + 1>
  {
    typedef Component_T<Component1, g_component + 1>   base_type;

    Component2()
      : Component_T(g_component + 1)
      , m_value()
    { }

    tl_int m_value;
  };

  TEST_CASE("Core/component_system/entity/entity", "")
  {
    entity_vso e(0);

    CHECK(e->GetID() == 0);
    CHECK(e->GetComponentsList().size() == (tl_size)components_group::count);

    e->SetID(1);
    CHECK(e->GetID() == 1);

    e->SetIndex(1);
    CHECK(e->GetIndex() == 1);

    Component1 c1;
    c1.m_value = 10;
    Component2 c2;
    c2.m_value = 20;

    CHECK_FALSE(e->HasComponent<Component1>() );
    CHECK_FALSE(e->HasComponent<Component2>() );

    e->InsertComponent(component_vptr(&c1));
    CHECK(e->HasComponent<Component1>() );
    CHECK_FALSE(e->HasComponent<Component2>() );

    e->InsertComponent(component_vptr(&c2));
    CHECK(e->HasComponent<Component1>() );
    CHECK(e->HasComponent<Component2>() );

    CHECK(e->GetComponent<Component1>().get() == &c1);
    CHECK(e->GetComponent<Component2>().get() == &c2);

    CHECK(e->GetComponent<Component1>()->m_value == 10);
    CHECK(e->GetComponent<Component2>()->m_value == 20);

    Entity::component_list& clist = e->DoGetComponents(g_component);

    REQUIRE(clist.size() == 1);
    CHECK(clist[0].get() == &c1);

    clist = e->GetComponents(g_component + 1);
    REQUIRE(clist.size() == 1);
    CHECK(clist[0].get() == &c2);
  }
};