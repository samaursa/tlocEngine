#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocEntitySystemBase.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

namespace TestingEntitySystemBase
{
  using namespace tloc;
  using namespace core;
  using namespace core_cs;

  // ///////////////////////////////////////////////////////////////////////
  // test components

  struct EmptyComponent1 
    : public Component_T<EmptyComponent1, components::listener>
  {
    typedef Component_T<EmptyComponent1, components::listener>    base_type;

    EmptyComponent1()
      : base_type(k_component_type)
    { }

    ~EmptyComponent1()
    { m_dtor++; }

    static tl_int m_dtor;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(EmptyComponent1, empty_comp1);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(EmptyComponent1, empty_comp1);

  tl_int EmptyComponent1::m_dtor = 0;

  struct EmptyComponent2 
    : public Component_T<EmptyComponent2, components::listener + 1>
  {
    typedef Component_T<EmptyComponent2, components::listener + 1>    base_type;

    EmptyComponent2()
      : base_type(k_component_type)
    { }

    ~EmptyComponent2()
    { m_dtor++; }

    static tl_int m_dtor;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(EmptyComponent2, empty_comp2);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(EmptyComponent2, empty_comp2);
  
  tl_int EmptyComponent2::m_dtor = 0;

  // ///////////////////////////////////////////////////////////////////////
  // EntSys

  class EntSys
    : public EntitySystemBase
  {
  public:
    typedef EntitySystemBase                      base_type;

  public:
    EntSys(event_manager_ptr a_eventMgr,
          entity_manager_ptr a_entMgr)
          : base_type(a_eventMgr, a_entMgr, 
                      core_ds::Variadic<components::value_type, 1>
                      (EmptyComponent1::k_component_type))
    { }

    ~EntSys()
    { }

    virtual error_type Pre_Initialize()
    {
      return ErrorSuccess;
    }

    virtual error_type DoInitialize(const entity_count_cont& )
    {
      return ErrorSuccess;
    }

    virtual error_type Post_Initialize()
    {
      return ErrorSuccess;
    }

    virtual error_type Pre_Shutdown()
    {
      return ErrorSuccess;
    }

    virtual error_type DoShutdown(const entity_count_cont& )
    {
      return ErrorSuccess;
    }

    virtual error_type Post_Shutdown()
    {
      return ErrorSuccess;
    }

    virtual bool CheckProcessing()
    {
      return true;
    }

    virtual void Pre_ProcessActiveEntities(f64 )
    {
    }

    virtual void DoProcessActiveEntities(const entity_count_cont& ,
                                         f64 )
    { }

    virtual void Post_ProcessActiveEntities(f64 )
    { }

    virtual void OnComponentInsert(const EntityComponentEvent& )
    {
    }

    virtual void OnComponentRemove(const EntityComponentEvent& )
    {
    }

    virtual void OnComponentDisable(const EntityComponentEvent& )
    {
    }

    virtual void OnComponentEnable(const EntityComponentEvent& )
    {
    }

    virtual void SortEntities()
    { }

    using base_type::DoGetActiveEntities;

  };

  TEST_CASE("core/component_system/EntitySystemBase", "")
  {
    empty_comp1_vso e1_a, e1_b, e1_c;
    empty_comp2_vso e2_a, e2_b, e2_c;

    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr( MakeArgs(evtMgr.get()) );

    EntSys e(evtMgr.get(), entMgr.get());
    CHECK(e.DoGetActiveEntities().size() == 0);

    core_cs::entity_vptr ent = entMgr->CreateEntity();

    entMgr->InsertComponent(ent, e2_a.get());
    // adding unrelated components does not add entities to the system
    CHECK(e.DoGetActiveEntities().size() == 0);

    entMgr->InsertComponent(ent, e1_a.get());
    // we have one active entity due to the above component
    CHECK(e.DoGetActiveEntities().size() == 1);

    entMgr->InsertComponent(ent, e1_b.get());
    // we still have one active entity because the component belongs to the 
    // same entity
    CHECK(e.DoGetActiveEntities().size() == 1);

    entMgr->RemoveComponent(ent, e1_a.get());
    entMgr->Update();

    entMgr->InsertComponent(ent, e1_a.get());
    CHECK(e.DoGetActiveEntities().size() == 1);

    entMgr->RemoveComponent(ent, e1_a.get());
    CHECK(e.DoGetActiveEntities().size() == 1);
    entMgr->RemoveComponent(ent, e1_b.get());
    CHECK(e.DoGetActiveEntities().size() == 0);

    entMgr->Update();

    entMgr->InsertComponent(ent, e1_a.get());
    entMgr->InsertComponent(ent, e1_b.get());

    core_cs::entity_vptr ent2 = entMgr->CreateEntity();

    entMgr->InsertComponent(ent2, e1_a.get());
    entMgr->InsertComponent(ent2, e1_b.get());
    CHECK(e.DoGetActiveEntities().size() == 2);

    entMgr->DestroyEntity(ent2);
    CHECK(e.DoGetActiveEntities().size() == 2);

    CHECK(entMgr->GetUnusedEntities() == 0);
    entMgr->Update();
    CHECK(entMgr->GetUnusedEntities() == 1);
    CHECK(e.DoGetActiveEntities().size() == 1);
  }
};