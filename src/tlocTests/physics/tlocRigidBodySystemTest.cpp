#include "tlocTestCommon.h"

#include <tlocCore/error/tlocError.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocPhysics/box2d/tlocPhysicsManager.h>
#include <tlocPhysics/box2d/tlocRigidBodyShapeDef.h>
#include <tlocPhysics/box2d/tlocRigidBodyDef.h>

#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>

#include <tlocPhysics/component_system/tlocRigidBodySystem.h>
#include <tlocPhysics/component_system/tlocRigidBodyListenerSystem.h>

namespace TestingRigidBodySystem
{
  using namespace tloc;
  using namespace tloc::physics;
  using namespace tloc::physics::component_system;

  struct RigidBodySystemFixture
  {
    typedef core::error::Error  error_type;

    typedef core_cs::event_manager_vso          event_manager_vso;
    typedef core_cs::entity_manager_vso         entity_manager_vso;
    typedef core_cs::Entity                     entity_type;
    typedef core_cs::EntityManager::Params      params_type;

    typedef math_t::Rectf32_c                   rect_shape_type;
    typedef math_t::Circlef32                   circle_shape_type;
    typedef math_cs::Transform                  transform_type;

    typedef box2d::PhysicsManager               physics_manager;
    typedef box2d::ContactEvent                 contact_event_type;
    typedef box2d::RigidBodyShapeDef            rigid_body_shape_def_type;
    typedef box2d::RigidBodyDef                 rigid_body_def_type;
    typedef box2d::rigid_body_def_sptr          rigid_body_def_sptr;

    typedef RigidBodyShape                      rigid_body_shape_component;
    typedef RigidBody                           rigid_body_component;
    typedef phys_cs::RigidBodyListener          rigid_body_listener_component;
    typedef phys_cs::rigid_body_listener_vso    rigid_Body_listener_vso;

    typedef rigid_body_component::rigid_body_type::vec_type  vec_type;

    typedef RigidBodySystem         rigid_body_system;
    typedef RigidBodyListenerSystem rigid_body_listener_system;
  };

  typedef RigidBodySystemFixture rb_sys_fixture;

  class WorldContactCallback
  {
  public:

    WorldContactCallback()
      : m_numContactBegin(0)
      , m_numContactEnd(0)
    {}

    bool OnContactBegin(const rb_sys_fixture::contact_event_type& a_event)
    {
      ++m_numContactBegin;
      TLOC_UNUSED(a_event);
      return false;
    }

    bool OnContactEnd(const rb_sys_fixture::contact_event_type& a_event)
    {
      ++m_numContactEnd;
      TLOC_UNUSED(a_event);
      return false;
    }

    tl_size m_numContactBegin;
    tl_size m_numContactEnd;
  };

  class ComponentContactCallback
    : public  physics::RigidBodyListener
  {
  public:

    ComponentContactCallback()
      : m_numContactBegin(0)
      , m_numContactEnd(0)
    {}

    void OnContactBegin(const_entity_ptr a_ent)
    {
      ++m_numContactBegin;
      TLOC_UNUSED(a_ent);
    }

    void OnContactEnd(const_entity_ptr a_ent)
    {
      ++m_numContactEnd;
      TLOC_UNUSED(a_ent);
    }

    tl_size m_numContactBegin;
    tl_size m_numContactEnd;
  };

  TLOC_TYPEDEF_VIRTUAL_PTR(ComponentContactCallback, comp_contact_callback);

};

TLOC_DEF_TYPE(TestingRigidBodySystem::WorldContactCallback);


namespace TestingRigidBodySystem
{
  using namespace core_sptr;

  TEST_CASE_METHOD(rb_sys_fixture,
                   "Physics/component_system/RigidBodySystem/General", "")
  {
    const float gravityY = -1000.0f;

    // Initialize essential systems
    physics_manager physicsMgr;
    physics_manager::vec_type gravity(0.0f, gravityY);

    physicsMgr.Initialize(physics_manager::gravity(gravity));

    WorldContactCallback myWorldContactCallback;
    physicsMgr.Register(&myWorldContactCallback);

    event_manager_vso evntMgr;
    entity_manager_vso entityMgr( MakeArgs(evntMgr.get()) );

    SharedPtr<transform_type> transformComponent = 
      MakeShared<transform_type>();

    rigid_body_system rigidBodySys(evntMgr.get(), entityMgr.get(), &physicsMgr.GetWorld());

    rigid_body_listener_system
      rigidBodyListenerSys(evntMgr.get(), entityMgr.get(), &physicsMgr);

    //------------------------------------------------------------------------
    // Create a static rigid body entity (Box)
    core_cs::entity_vptr rbStaticRectEntity = entityMgr->CreateEntity();

    rigid_body_def_sptr rbDef(new rigid_body_def_type);
    SharedPtr<rigid_body_component> rbStaticRectComponent = 
      MakeShared<rigid_body_component>(rbDef);

    rect_shape_type rectShape(rect_shape_type::width(20.0f),
                              rect_shape_type::height(2.0f) );

    rigid_body_shape_def_type rbRectShape(rectShape);
    SharedPtr<rigid_body_shape_component> rbShapeComponent = 
      MakeShared<rigid_body_shape_component>(rbRectShape);

    entityMgr->InsertComponent(params_type(rbStaticRectEntity, transformComponent));
    entityMgr->InsertComponent(params_type(rbStaticRectEntity, rbStaticRectComponent));
    entityMgr->InsertComponent(params_type(rbStaticRectEntity, rbShapeComponent));

    //------------------------------------------------------------------------
    // Create a static rigid body entity (Circle)
    core_cs::entity_vptr rbStaticCircleEntity = entityMgr->CreateEntity();

    SharedPtr<transform_type> transformComponent1 = 
      MakeShared<transform_type>();

    const float circleStartPosition = 3.0f;

    rigid_body_def_sptr rbDef1(new rigid_body_def_type);
    rbDef1->SetPosition(vec_type(-2.0f, circleStartPosition));
    SharedPtr<rigid_body_component> rbStaticComponent = 
      MakeShared<rigid_body_component>(rbDef1);

    circle_shape_type circleShape;
    circleShape.SetRadius(1.0f);

    rigid_body_shape_def_type rbCircleShape(circleShape);
    SharedPtr<rigid_body_shape_component> rbShapeComponent1 = 
      MakeShared<rigid_body_shape_component>(rbCircleShape);

    entityMgr->InsertComponent(params_type(rbStaticCircleEntity, transformComponent1));
    entityMgr->InsertComponent(params_type(rbStaticCircleEntity, rbStaticComponent));
    entityMgr->InsertComponent(params_type(rbStaticCircleEntity, rbShapeComponent1));

    //------------------------------------------------------------------------
    // Create a dynamic rigid body (Circle)
    core_cs::entity_vptr rbDynamicCircleEntity = entityMgr->CreateEntity();

    SharedPtr<transform_type> transformComponent2 = 
      MakeShared<transform_type>();

    rigid_body_def_sptr rbDef2(new rigid_body_def_type);
    rbDef2->SetType<box2d::p_rigid_body::DynamicBody>();
    rbDef2->SetPosition(vec_type(2.0f, circleStartPosition));

    SharedPtr<rigid_body_component> rbDynamicComponent = 
      MakeShared<rigid_body_component>(rbDef2);

    SharedPtr<rigid_body_shape_component> rbShapeComponent2 = 
      MakeShared<rigid_body_shape_component>(rbCircleShape);

    ComponentContactCallback myComponentContactCallback;
    SharedPtr<rigid_body_listener_component>
      rbListenerComponent = MakeShared<rigid_body_listener_component>
      ( VirtualPtr<ComponentContactCallback>(&myComponentContactCallback) );

    entityMgr->InsertComponent(params_type(rbDynamicCircleEntity, transformComponent2));
    entityMgr->InsertComponent(params_type(rbDynamicCircleEntity, rbDynamicComponent));
    entityMgr->InsertComponent(params_type(rbDynamicCircleEntity, rbShapeComponent2));
    entityMgr->InsertComponent(params_type(rbDynamicCircleEntity, rbListenerComponent));

    //------------------------------------------------------------------------
    CHECK(rigidBodySys.Initialize() == ErrorSuccess);
    CHECK(rigidBodyListenerSys.Initialize() == ErrorSuccess);

    // Update everything once so everything is in the right position
    rigidBodySys.ProcessActiveEntities();

    vec_type position;
    rbDynamicComponent->GetRigidBody().GetPosition(position);
    CHECK(position[1] == Approx(3.0f));

    CHECK(myWorldContactCallback.m_numContactBegin == 0);
    CHECK(myComponentContactCallback.m_numContactBegin == 0);

    // Note: The "tolerance" of 0.25f is only valid within the first 4
    // iterations on the Box2D platform. Adjust if necessary.
    const tl_float tolerance = 0.25f;

    vec_type previousPosition;
    const tl_float timeStep = 0.01f;
    const tl_size maxIterations = 4;

    // Ball is falling. At the end of the max iterations it will hit
    // another ball and stop
    bool deltaPTest = true;
    bool actualPTest = true;
    for (tl_size i = 0; i < maxIterations; ++i)
    {
      physicsMgr.Update(timeStep);
      rigidBodySys.ProcessActiveEntities();
      rigidBodyListenerSys.ProcessActiveEntities();

      previousPosition = position;
      rbDynamicComponent->GetRigidBody().GetPosition(position);

      if((position[1] < previousPosition[1]) == false)
      { deltaPTest = false; break; }

      // +1 since we've already told the physics manager to move "ahead" one step.
      tl_float time = timeStep * (i + 1);
      tl_float calculatedPositionY =
        circleStartPosition + 0.5f * gravityY * time * time;

      if(math::Approx(calculatedPositionY, position[1], tolerance) == false)
      { actualPTest = false; break; }
    }
    CHECK(deltaPTest);
    CHECK(actualPTest);

    // Ball has hit the floor, But has not registered the hit yet
    CHECK(myWorldContactCallback.m_numContactBegin == 0);
    CHECK(myComponentContactCallback.m_numContactBegin == 0);

    // Update one more time. The ball should have hit the floor and "stopped"
    {
      physicsMgr.Update(timeStep);
      rigidBodySys.ProcessActiveEntities();
      rigidBodyListenerSys.ProcessActiveEntities();

      previousPosition = position;
      rbDynamicComponent->GetRigidBody().GetPosition(position);
      CHECK(position[1] >= previousPosition[1]);
    }

    CHECK(myWorldContactCallback.m_numContactBegin == 1);
    CHECK(myComponentContactCallback.m_numContactBegin == 1);

    CHECK(rigidBodyListenerSys.Shutdown() == ErrorSuccess);
    CHECK(rigidBodySys.Shutdown() == ErrorSuccess);
    CHECK(physicsMgr.Shutdown() == ErrorSuccess);
  }
};