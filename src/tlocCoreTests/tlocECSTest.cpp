#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocECS.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

namespace 
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  enum {

    k_initializeCalled = 0,
    k_initializeEntityCalled,

    k_preProcessCalled,
    k_processingCalled,
    k_postProcessCalled,

    k_count
  };

  // ///////////////////////////////////////////////////////////////////////
  // DummyComp1

  class DummyComp1
    : public core_cs::Component_T<DummyComp1, 
                                  core_cs::component_group::k_core, 
                                  core_cs::components::k_listener>
  {
  public:
    typedef core_cs::Component_T
      <DummyComp1, 
       core_cs::component_group::k_core, 
       core_cs::components::k_listener>                     base_type;

  public:
    DummyComp1()
      : base_type("DummyComp1") { }
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(DummyComp1, dymmy_comp1);

  // ///////////////////////////////////////////////////////////////////////
  // DummyComp2

  class DummyComp2
    : public core_cs::Component_T<DummyComp2, 
                                  core_cs::component_group::k_core, 
                                  core_cs::components::k_listener>
  {
  public:
    typedef core_cs::Component_T
      <DummyComp2, 
       core_cs::component_group::k_core, 
       core_cs::components::k_listener>                     base_type;

  public:
    DummyComp2()
      : base_type("DummyComp2") { }
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(DummyComp2, dymmy_comp2);

  // ///////////////////////////////////////////////////////////////////////
  // DummySys1

  class DummySys1
    : public core_cs::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem      base_type;

  public:
    DummySys1(event_manager_ptr a_eventMgr, entity_manager_ptr a_entityMgr)
      : base_type(a_eventMgr, a_entityMgr, register_type().Add<DummyComp1>(), 
                  "DummySys1")
      , m_flags(k_count)
    { }

    virtual error_type Pre_Initialize() 
    { 
      m_flags.Mark(k_initializeCalled);
      return ErrorSuccess;
    }

    virtual error_type InitializeEntity(entity_ptr)
    { 
      m_flags.Mark(k_initializeEntityCalled);
      return ErrorSuccess;
    }

    virtual error_type ShutdownEntity(entity_ptr)
    { return ErrorSuccess; }

    virtual void Pre_ProcessActiveEntities(f64 ) {}
    virtual void Post_ProcessActiveEntities(f64 ) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

    virtual void ProcessEntity(entity_ptr, f64 )
    { m_flags.Mark(k_processingCalled); }

    core_utils::Checkpoints     m_flags;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(DummySys1, dummy_sys1);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(DummySys1, dummy_sys1);

  // ///////////////////////////////////////////////////////////////////////
  // DummySys2

  class DummySys2
    : public core_cs::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem      base_type;

  public:
    DummySys2(event_manager_ptr a_eventMgr, entity_manager_ptr a_entityMgr, int a_dummyArg)
      : base_type(a_eventMgr, a_entityMgr, register_type().Add<DummyComp2>(), 
                  "DummySys2")
      , m_flags(k_count)
    { TLOC_UNUSED(a_dummyArg); }

    virtual error_type Pre_Initialize() 
    { 
      m_flags.Mark(k_initializeCalled);
      return ErrorSuccess;
    }

    virtual error_type InitializeEntity(entity_ptr)
    { 
      m_flags.Mark(k_initializeEntityCalled);
      return ErrorSuccess;
    }

    virtual error_type ShutdownEntity(entity_ptr)
    { return ErrorSuccess; }

    virtual void Pre_ProcessActiveEntities(f64 ) {}
    virtual void Post_ProcessActiveEntities(f64 ) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

    virtual void ProcessEntity(entity_ptr, f64 )
    { m_flags.Mark(k_processingCalled); }

    core_utils::Checkpoints     m_flags;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(DummySys2, dummy_sys2);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(DummySys2, dummy_sys2);

  // ///////////////////////////////////////////////////////////////////////
  // TESTS

  TEST_CASE("core/component_system/ECS/", "")
  {
    ECS ecs;
    auto sys1 = ecs.AddSystem<DummySys1>();
    auto sys2 = ecs.AddSystem<DummySys2>(ECS::GetDefaultGroupName(), 5);

    auto dummyComp1 = core_sptr::MakeShared<DummyComp1>();
    auto dummyComp2 = core_sptr::MakeShared<DummyComp2>();

    auto ent = ecs.GetEntityManager()->CreateEntity();
    auto ent2 = ecs.GetEntityManager()->CreateEntity();

    ecs.InsertComponent(ent, dummyComp1);
    ecs.InsertComponent(ent2, dummyComp2);

    SECTION("Initialize", "")
    {
      CHECK_FALSE(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_initializeCalled));
      CHECK_FALSE(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_processingCalled));

      ecs.Initialize();

      REQUIRE(ecs.GetSystemsGroup()->GetSystemsProcessor()->size_systems() == 2);
      CHECK(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK(sys2->m_flags.IsMarked(k_initializeCalled));
      CHECK_FALSE(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_processingCalled));

      ecs.Process(1.0/60.0);

      REQUIRE(ecs.GetSystemsGroup()->GetSystemsProcessor()->size_systems() == 2);
      CHECK(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK(sys2->m_flags.IsMarked(k_initializeCalled));
      CHECK(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK(sys2->m_flags.IsMarked(k_processingCalled));
    }
  }

 };
