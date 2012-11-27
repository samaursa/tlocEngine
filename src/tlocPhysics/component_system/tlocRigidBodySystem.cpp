#include "tlocRigidBodySystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocFixtureComponent.h>

namespace tloc { namespace physics { namespace component_system {

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
    using namespace tloc::core;
    using namespace tloc::core::component_system;

    typedef RigidBody                               rigid_body_component_type;

    typedef rigid_body_component_type::rigid_body_value_type
                                                    rigid_body_type;

    typedef rigid_body_type::rigid_body_value_type  rigid_body_internal_type;

    typedef rigid_body_component_type::rigid_body_def_type
                                                    rigid_body_def_type;

    typedef rigid_body_def_type::rigid_body_def_value_type
                                                    rigid_body_def_internal_type;

    // TODO: Make this into a function
    const entity_type* ent = a_ent;

    ComponentMapper<rigid_body_component_type> rigidBodyComponents =
      ent->GetComponents(components::k_rigid_body);

    rigid_body_component_type& currRBComponent = rigidBodyComponents[0];
    rigid_body_type& currRB = currRBComponent.GetRigidBodyValue();

    const rigid_body_def_type& currRBDef = currRBComponent.GetRigidBodyDef();
    const rigid_body_def_internal_type& currRBDefInternal =
      currRBDef.GetRigidBodyDef();

    rigid_body_internal_type* currRBInternal =
      m_world->GetWorld().CreateBody(&currRBDefInternal);

    currRB.Initialize(currRBInternal);

    TLOC_UNUSED(a_mgr);

    return ErrorSuccess();
  }

  RigidBodySystem::error_type
    RigidBodySystem::ShutdownEntity(entity_manager* a_mgr, entity_type* a_ent )
  {
    using namespace tloc::core;
    using namespace tloc::core::component_system;

    typedef RigidBody                               rigid_body_component_type;

    typedef rigid_body_component_type::rigid_body_value_type
                                                    rigid_body_type;

    typedef rigid_body_type::rigid_body_value_type  rigid_body_internal_type;

    // TODO: Make this into a function
    const entity_type* ent = a_ent;

    ComponentMapper<rigid_body_component_type> rigidBodyComponents =
      ent->GetComponents(components::k_rigid_body);

    rigid_body_component_type& currRBComponent = rigidBodyComponents[0];
    rigid_body_type& currRB = currRBComponent.GetRigidBodyValue();

    rigid_body_internal_type* currRBInternal = currRB.GetInternalRigidBody();

    m_world->GetWorld().DestroyBody(currRBInternal);

    currRB.Shutdown();

    TLOC_UNUSED(a_mgr);

    return ErrorSuccess();
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

};};};