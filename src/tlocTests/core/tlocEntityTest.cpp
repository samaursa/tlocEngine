#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#define protected public
#define private public
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponent.h>

namespace TestingEntity
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  const components::value_type  g_component = 
    components::value_type(components::k_listener);

  struct Component1
    : public Component_T<Component1, 
                         component_group::k_core, 
                         components::k_listener>
  {
    typedef Component_T<Component1, 
                        component_group::k_core, 
                        components::k_listener>           base_type;

    Component1()
      : base_type(Component::Info().GroupIndex(component_group::k_core)
                    .Type(components::k_listener), "Component2")
      , m_value(0)
    { }

    tl_int m_value;
  };
  TLOC_TYPEDEF_SHARED_PTR(Component1, comp1);

  struct Component2
    : public Component_T<Component1, 
                         component_group::k_core, 
                         components::k_listener + 1>
  {
    typedef Component_T<Component1, 
                        component_group::k_core, 
                        components::k_listener + 1>       base_type;

    Component2()
      : base_type(Component::Info().GroupIndex(component_group::k_core)
                    .Type(components::k_listener + 1), "Component2")
      , m_value()
    { }

    tl_int m_value;
  };
  TLOC_TYPEDEF_SHARED_PTR(Component2, comp2);

  TEST_CASE("Core/component_system/entity/entity", "")
  {
    entity_vso e( MakeArgs(0) );

    CHECK(e->GetID() == 0);
    CHECK(e->GetComponentGroupList().size() == (tl_size)component_group::k_count);

    e->DoSetID(1);
    CHECK(e->GetID() == 1);

    e->DoSetIndex(1);
    CHECK(e->GetIndex() == 1);

    comp1_sptr c1 = core_sptr::MakeShared<Component1>();
    c1->m_value = 10;
    comp2_sptr c2 = core_sptr::MakeShared<Component2>();
    c2->m_value = 20;

    CHECK_FALSE(e->HasComponent<Component1>() );
    CHECK_FALSE(e->HasComponent<Component2>() );

    e->DoInsertComponent(c1);
    CHECK(e->HasComponent<Component1>() );
    CHECK_FALSE(e->HasComponent<Component2>() );

    e->DoInsertComponent(c2);
    CHECK(e->HasComponent<Component1>() );
    CHECK(e->HasComponent<Component2>() );

    CHECK(*e->GetComponent<Component1>() == *c1);
    CHECK(*e->GetComponent<Component2>() == *c2);

    CHECK(e->GetComponent<Component1>()->m_value == 10);
    CHECK(e->GetComponent<Component2>()->m_value == 20);

    {
      Entity::const_comp_itr_pair_type itrPair =
        e->GetComponents(Component::Info().GroupIndex(component_group::k_core)
                                          .Type(components::k_listener));

      tl_size dist = distance(itrPair.first, itrPair.second);

      REQUIRE(dist == 1);
      CHECK(**itrPair.first == *c1);
    }

    {
      Entity::const_comp_itr_pair_type itrPair =
        e->GetComponents(Component::Info().GroupIndex(component_group::k_core)
                                          .Type(components::k_listener + 1));

      tl_size dist = distance(itrPair.first, itrPair.second);

      REQUIRE(dist == 1);
      CHECK(**itrPair.first == *c2);
    }
  }
};