#include "tlocRigidBodySystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocPhysics/error/tlocErrorTypes.h>
#include <tlocPhysics/component_system/tlocComponentType.h>
#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>

namespace tloc { namespace physics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // Free Functions

  namespace {

    typedef RigidBodySystem::rigid_body_component rb_component;
    typedef RigidBodySystem::entity_type          entity_type;
    typedef RigidBodySystem::error_type           error_type;

    rb_component&
      GetRigidBodyComponent(const entity_type* a_ent)
    {
      using namespace tloc::core::component_system;

      ComponentMapper<rb_component> rigidBodyComponents =
        a_ent->GetComponents(components::k_rigidBody);

      return rigidBodyComponents[0];
    }

    error_type
      InitializeRigidBodyShapeComponents(const entity_type* a_ent)
    {
      using namespace tloc::core::component_system;

      typedef rb_component::rigid_body_type               rb_type;

      typedef RigidBodySystem::rigid_body_shape_component_type
                                                          rb_shape_component;
      typedef rb_shape_component::rigid_body_shape_def_type
                                                          rb_shape_type;

      typedef ComponentMapper<rb_shape_component>         component_mapper_type;
      typedef component_mapper_type::size_type            size_type;

      rb_component& rbComponent = GetRigidBodyComponent(a_ent);
      rb_type& rb = rbComponent.GetRigidBody();

      ComponentMapper<rb_shape_component> rigidBodyShapeComponents =
        a_ent->GetComponents(components::k_rigidBodyShape);

      size_type numComponents = rigidBodyShapeComponents.size();
      error_type result = ErrorSuccess;

      for (size_type i = 0; i < numComponents; ++i)
      {
        const rb_shape_type rbShape = rigidBodyShapeComponents[i].GetRigidBodyShape();

        result = rb.CreateRigidBodyShape(rbShape);

        if (result != ErrorSuccess)
        {
          break;
        }
      }

      return result;
    }

  };

  //////////////////////////////////////////////////////////////////////////
  // RigidBodySystem

  RigidBodySystem::
    RigidBodySystem (event_manager_sptr a_eventMgr,
                     entity_manager_sptr a_entityMgr,
                     world_type* a_world)
    : base_type(a_eventMgr, a_entityMgr
    , Variadic<component_type, 1>(components::k_rigidBody))
    , m_world(a_world)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type RigidBodySystem::
    InitializeEntity(const entity_manager* a_mgr,
                     const entity_type* a_ent)
  {
    error_type result = DoInitializeRigidBodyComponent(a_ent);

    if (result == ErrorSuccess)
    {
      result = InitializeRigidBodyShapeComponents(a_ent);
    }

    TLOC_UNUSED(a_mgr);

    return result;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type RigidBodySystem::
    ShutdownEntity(const entity_manager* a_mgr, const entity_type* a_ent )
  {
    error_type result = DoShutdownRigidBodyComponent(a_ent);

    TLOC_UNUSED(a_mgr);
    return result;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void RigidBodySystem::
    ProcessEntity(const entity_manager* a_mgr, const entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component::rigid_body_type  rb_type;
    typedef tloc::math::component_system::Transform     transform_type;
    typedef transform_type::real_type                   real_type;

    rigid_body_component& rbComponent = GetRigidBodyComponent(a_ent);
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

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type RigidBodySystem::
    DoInitializeRigidBodyComponent(const entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component::rigid_body_type
                                                    rb_type;

    typedef rb_type::rigid_body_internal_type       rb_internal_type;

    typedef rigid_body_component::rigid_body_def_sptr::value_type
                                                    rb_def_type;

    typedef rb_def_type::rigid_body_def_internal_type
                                                    rb_def_internal_type;

    rigid_body_component& currRBComponent = GetRigidBodyComponent(a_ent);

    rb_type& currRB = currRBComponent.GetRigidBody();

    const rb_def_type currRBDef = *(currRBComponent.GetRigidBodyDef());
    const rb_def_internal_type& currRBDefInternal =
      currRBDef.DoGetRigidBodyDef();

    rb_internal_type* currRBInternal =
      m_world->GetWorld().CreateBody(&currRBDefInternal);

    if (currRBInternal == nullptr)
    {
      TLOC_ASSERT(false, "Box2D RigidBody could not be allocated!");
      return error::error_rigid_body_could_not_be_allocated;
    }

    currRB.DoInitialize(currRBInternal, a_ent);
    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type RigidBodySystem::
    DoShutdownRigidBodyComponent(const entity_type* a_ent)
  {
    using namespace tloc::core::component_system;

    typedef rigid_body_component::rigid_body_type  rb_type;

    typedef rb_type::rigid_body_internal_type           rb_internal_type;

    rigid_body_component& currRBComponent = GetRigidBodyComponent(a_ent);

    rb_type& currRB = currRBComponent.GetRigidBody();
    rb_internal_type* currRBInternal = currRB.DoGetInternalRigidBody();

    m_world->GetWorld().DestroyBody(currRBInternal);

    error_type result = currRB.DoShutdown();

    return result;
  }

};};};