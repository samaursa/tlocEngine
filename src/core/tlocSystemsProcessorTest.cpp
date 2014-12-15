#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocSystemsProcessor.h>
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
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(DummySys1, dummy_sys1);

  // ///////////////////////////////////////////////////////////////////////
  // DummySys2

  class DummySys2
    : public core_cs::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem      base_type;

  public:
    DummySys2(event_manager_ptr a_eventMgr, entity_manager_ptr a_entityMgr)
      : base_type(a_eventMgr, a_entityMgr, register_type().Add<DummyComp2>(), 
                  "DummySys2")
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
  TLOC_TYPEDEF_ALL_SMART_PTRS(DummySys2, dummy_sys2);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(DummySys2, dummy_sys2);

  // ///////////////////////////////////////////////////////////////////////
  // TESTS

  TEST_CASE("core/component_system/SystemsProcessor/", "")
  {
    core_cs::event_manager_vso          eventMgr;
    core_cs::entity_manager_vso         entMgr(MakeArgs(eventMgr.get()));

    dummy_sys1_vso sys1( MakeArgs(eventMgr.get(), entMgr.get()) );
    dummy_sys2_vso sys2( MakeArgs(eventMgr.get(), entMgr.get()) );

    auto dummyComp1 = core_sptr::MakeShared<DummyComp1>();
    auto dummyComp2 = core_sptr::MakeShared<DummyComp2>();

    auto ent = entMgr->CreateEntity();
    auto ent2 = entMgr->CreateEntity();

    entMgr->InsertComponent(EntityManager::Params(ent, dummyComp1) );
    entMgr->InsertComponent(EntityManager::Params(ent2, dummyComp2) );

    SECTION("Initialize and Process", "")
    {
      core_cs::SystemsProcessor sp;
      CHECK(sp.empty_systems());

      sp.Add(sys1.get());
      sp.Add(sys2.get());

      CHECK(sp.size_systems() == 2);

      CHECK_FALSE(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_initializeCalled));
      sp.Initialize();
      CHECK(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK(sys2->m_flags.IsMarked(k_initializeCalled));

      TLOC_TEST_ASSERT
      {
        sp.Initialize();
      }
      TLOC_TEST_ASSERT_CHECK();

      CHECK_FALSE(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_processingCalled));
      sp.Process(0.0f);
      CHECK(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK(sys2->m_flags.IsMarked(k_processingCalled));
    }

    SECTION("Initialize and Process disabled", "")
    {
      core_cs::SystemsProcessor sp;
      CHECK(sp.empty_systems());

      sys1->SetDisableProcessing();

      sp.Add(sys1.get());
      sp.Add(sys2.get());

      CHECK(sp.size_systems() == 2);

      CHECK_FALSE(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_initializeCalled));
      sp.Initialize();
      CHECK(sys1->m_flags.IsMarked(k_initializeCalled));
      CHECK(sys2->m_flags.IsMarked(k_initializeCalled));

      CHECK_FALSE(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK_FALSE(sys2->m_flags.IsMarked(k_processingCalled));
      sp.Process(0.0f);
      CHECK_FALSE(sys1->m_flags.IsMarked(k_processingCalled));
      CHECK(sys2->m_flags.IsMarked(k_processingCalled));
    }
  }
}