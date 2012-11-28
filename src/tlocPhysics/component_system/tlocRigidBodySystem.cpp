#include "tlocRigidBodySystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocFixtureComponent.h>

namespace tloc { namespace physics { namespace component_system {

  //------------------------------------------------------------------------
  // Free Functions

  RigidBodySystem::rigid_body_component_type&
    GetRigidBodyComponent(const RigidBodySystem::entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    ComponentMapper<RigidBodySystem::rigid_body_component_type>
      rigidBodyComponents = a_ent->GetComponents(components::k_rigid_body);

    return rigidBodyComponents[0];
  }

  //------------------------------------------------------------------------
  // RigidBodySystem

  RigidBodySystem::RigidBodySystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr, world_type* a_world)
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::k_rigid_body))
    , m_world(a_world)
  {
  }

  RigidBodySystem::error_type
    RigidBodySystem::InitializeEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    rigid_body_component_type& currRBComponent = GetRigidBodyComponent(a_ent);

    error_type result = DoInitializeRigidBodyComponent(currRBComponent);

    if (result == ErrorSuccess())
    {
    }

    TLOC_UNUSED(a_mgr);

    return result;
  }

  RigidBodySystem::error_type
    RigidBodySystem::ShutdownEntity(entity_manager* a_mgr, entity_type* a_ent )
  {
    rigid_body_component_type& currRBComponent = GetRigidBodyComponent(a_ent);

    error_type result = DoShutdownRigidBodyComponent(currRBComponent);

    if (result == ErrorSuccess())
    {
    }

    TLOC_UNUSED(a_mgr);

    return result;
  }

  void RigidBodySystem::ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    using namespace tloc::core;
    using namespace tloc::core::component_system;

    const entity_type* ent = a_ent;
    ComponentMapper<RigidBody> rigidBodyComponents =
      ent->GetComponents(components::k_rigid_body);

    RigidBody& currRigidBody = rigidBodyComponents[0];

    // Transfer the transform to the transform component
    TLOC_UNUSED(currRigidBody);

    TLOC_UNUSED(a_mgr);
  }

  RigidBodySystem::error_type RigidBodySystem::
    DoInitializeRigidBodyComponent(rigid_body_component_type& a_component)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component_type::rigid_body_value_type
                                                    rigid_body_type;

    typedef rigid_body_type::rigid_body_value_type  rigid_body_internal_type;

    typedef rigid_body_component_type::rigid_body_def_type
                                                    rigid_body_def_type;

    typedef rigid_body_def_type::rigid_body_def_value_type
                                                    rigid_body_def_internal_type;

    rigid_body_type& currRB = a_component.GetRigidBodyValue();

    const rigid_body_def_type& currRBDef = a_component.GetRigidBodyDef();
    const rigid_body_def_internal_type& currRBDefInternal =
      currRBDef.GetRigidBodyDef();

    rigid_body_internal_type* currRBInternal =
      m_world->GetWorld().CreateBody(&currRBDefInternal);

    currRB.Initialize(currRBInternal);
    return ErrorSuccess();
  }

  RigidBodySystem::error_type RigidBodySystem::
    DoShutdownRigidBodyComponent(rigid_body_component_type& a_component)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component_type::rigid_body_value_type
                                                    rigid_body_type;

    typedef rigid_body_type::rigid_body_value_type  rigid_body_internal_type;

    rigid_body_type& currRB = a_component.GetRigidBodyValue();
    rigid_body_internal_type* currRBInternal = currRB.GetInternalRigidBody();

    m_world->GetWorld().DestroyBody(currRBInternal);

    currRB.Shutdown();
    return ErrorSuccess();
  }

};};};