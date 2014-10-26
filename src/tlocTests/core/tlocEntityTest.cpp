#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

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
      : base_type("Component2")
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
      : base_type("Component2")
      , m_value()
    { }

    tl_int m_value;
  };
  TLOC_TYPEDEF_SHARED_PTR(Component2, comp2);

  class EntityMock
    : public Entity
  {
  public:
    EntityMock(entity_id a_id) 
      : Entity(a_id) 
    { }

    EntityMock(entity_id a_id, BufferArg a_debugName) 
      : Entity(a_id, a_debugName) 
    { }

    component_itr_type  begin_components(component_group_type a_groupIndex)
    { return Entity::begin_components(a_groupIndex); }

    component_itr_type  end_components(component_group_type a_groupIndex)
    { return Entity::end_components(a_groupIndex); }

    component_itr_type  begin_components(component_info_type a_info)
    { return Entity::begin_components(a_info); }

    component_itr_type  end_components(component_info_type a_info)
    { return Entity::end_components(a_info); }

    component_group_iterator begin_component_groups()
    { return Entity::begin_component_groups(); }

    component_group_iterator end_component_groups()
    { return Entity::end_component_groups(); }

    void                DoInsertComponent(component_sptr a_component)
    { Entity::DoInsertComponent(a_component); }

    void                DoRemoveComponent(component_sptr a_component)
    { Entity::DoRemoveComponent(a_component); }
  };
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(EntityMock, entity_mock);


  TEST_CASE("Core/component_system/entity/entity", "")
  {
    entity_mock_vso e( MakeArgs(0) );

    CHECK(e->GetID() == 0);
    CHECK(e->GetComponentGroupList().size() == (tl_size)component_group::k_count);

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
      Component::Info ci;
      ci.GroupIndex(component_group::k_core)
        .Type(components::k_listener);

      Entity::const_component_iterator  itr, itrEnd;
      itr = e->begin_components(ci);
      itrEnd = e->end_components(ci);

      tl_size dist = distance(itr, itrEnd);

      REQUIRE(dist == 1);
      CHECK(**itr == *c1);
    }

    {
      Component::Info ci;
      ci.GroupIndex(component_group::k_core)
        .Type(components::k_listener + 1);

      Entity::const_component_iterator  itr, itrEnd;
      itr = e->begin_components(ci);
      itrEnd = e->end_components(ci);

      tl_size dist = distance(itr, itrEnd);

      REQUIRE(dist == 1);
      CHECK(**itr == *c2);
    }
  }
};