#include "tlocRigidBodySystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>

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

  RigidBodySystem::error_type
    InitializeRigidBodyShapeComponents(const RigidBodySystem::entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef RigidBodySystem::rigid_body_component_type  rb_component_type;
    typedef rb_component_type::rigid_body_type          rb_type;
    typedef rb_type::error_type                         error_type;

    typedef RigidBodySystem::rigid_body_shape_component_type
                                                        rb_shape_component_type;
    typedef rb_shape_component_type::rigid_body_shape_type
                                                        rb_shape_type;

    typedef ComponentMapper<rb_shape_component_type>    component_mapper_type;
    typedef component_mapper_type::size_type            size_type;

    rb_component_type& rbComponent = GetRigidBodyComponent(a_ent);
    rb_type& rb = rbComponent.GetRigidBody();

    ComponentMapper<rb_shape_component_type> rigidBodyShapeComponents =
      a_ent->GetComponents(components::k_rigid_body_shape);

    size_type numComponents = rigidBodyShapeComponents.size();
    error_type result;

    for (size_type i = 0; i < numComponents; ++i)
    {
      rb_shape_type rbShape = rigidBodyShapeComponents[i].GetRigidBodyShape();

      result = rb.CreateRigidBodyShape(rbShape);

      if (result != ErrorSuccess())
      {
        break;
      }
    }

    return result;
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
    error_type result = DoInitializeRigidBodyComponent(a_ent);

    if (result == ErrorSuccess())
    {
      result = InitializeRigidBodyShapeComponents(a_ent);
    }

    TLOC_UNUSED(a_mgr);

    return result;
  }

  RigidBodySystem::error_type
    RigidBodySystem::ShutdownEntity(entity_manager* a_mgr, entity_type* a_ent )
  {
    error_type result = DoShutdownRigidBodyComponent(a_ent);

    if (result == ErrorSuccess())
    {

    }

    TLOC_UNUSED(a_mgr);

    return result;
  }

  void RigidBodySystem::ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component_type::rigid_body_type  rb_type;
    typedef tloc::math::component_system::Transform     transform_type;
    typedef transform_type::real_type                   real_type;

    rigid_body_component_type& rbComponent = GetRigidBodyComponent(a_ent);
    rb_type& rb = rbComponent.GetRigidBody();

    rb_type::vec_type     rbPosition;
    rb_type::matrix_type  rbOrientation;

    rb.GetTransform(rbPosition, rbOrientation);

    const entity_type* ent = a_ent;

    ComponentMapper<transform_type> transformComponents =
      ent->GetComponents(tloc::math::component_system::components::transform);

    transform_type& transform = transformComponents[0];

    transform_type::position_type position((real_type)rbPosition[0],
                                           (real_type)rbPosition[1],
                                           transform.GetPosition()[2]);

    transform_type::orientation_type orientation
      ((real_type)rbOrientation[0], (real_type)rbOrientation[2], (real_type)0,
       (real_type)rbOrientation[1], (real_type)rbOrientation[3], (real_type)0,
       (real_type)0,                (real_type)0,                (real_type)1);

    transform.SetPosition(position);
    transform.SetOrientation(orientation);

    TLOC_UNUSED(a_mgr);
  }

  RigidBodySystem::error_type RigidBodySystem::
    DoInitializeRigidBodyComponent(entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component_type::rigid_body_type
                                                    rigid_body_type;

    typedef rigid_body_type::rigid_body_internal_type
                                                    rigid_body_internal_type;

    typedef rigid_body_component_type::rigid_body_def_type
                                                    rigid_body_def_type;

    typedef rigid_body_def_type::rigid_body_def_internal_type
                                                    rigid_body_def_internal_type;

    rigid_body_component_type& currRBComponent = GetRigidBodyComponent(a_ent);

    rigid_body_type& currRB = currRBComponent.GetRigidBody();

    const rigid_body_def_type& currRBDef = currRBComponent.GetRigidBodyDef();
    const rigid_body_def_internal_type& currRBDefInternal =
      currRBDef.GetRigidBodyDef();

    rigid_body_internal_type* currRBInternal =
      m_world->GetWorld().CreateBody(&currRBDefInternal);

    currRB.Initialize(currRBInternal, a_ent);
    return ErrorSuccess();
  }

  RigidBodySystem::error_type RigidBodySystem::
    DoShutdownRigidBodyComponent(entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component_type::rigid_body_type rigid_body_type;

    typedef rigid_body_type::rigid_body_internal_type  rigid_body_internal_type;

    rigid_body_component_type& currRBComponent = GetRigidBodyComponent(a_ent);

    rigid_body_type& currRB = currRBComponent.GetRigidBody();
    rigid_body_internal_type* currRBInternal = currRB.GetInternalRigidBody();

    m_world->GetWorld().DestroyBody(currRBInternal);

    currRB.Shutdown();
    return ErrorSuccess();
  }

};};};