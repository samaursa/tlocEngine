#include "tlocRigidBodySystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentMapper.h>

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
    typedef RigidBodySystem::entity_ptr           entity_ptr;
    typedef RigidBodySystem::error_type           error_type;

    rb_component&
      GetRigidBodyComponent(entity_ptr a_ent)
    {
      using namespace tloc::core::component_system;


      phys_cs::rigid_body_sptr rigidBodyPtr =
        a_ent->GetComponent<phys_cs::RigidBody>();

      return *rigidBodyPtr;
    }

    error_type
      InitializeRigidBodyShapeComponents(entity_ptr a_ent)
    {
      using namespace tloc::core::component_system;

      typedef rb_component::rigid_body_type               rb_type;

      typedef RigidBodySystem::rigid_body_shape_component_type
                                                          rb_shape_component;
      typedef rb_shape_component::rigid_body_shape_def
                                                          rb_shape_type;

      typedef ComponentMapper
        <rb_shape_component, core_cs::Entity::component_iterator> component_mapper_type;
      typedef component_mapper_type::size_type                    size_type;

      rb_component& rbComponent = GetRigidBodyComponent(a_ent);
      rb_type& rb = rbComponent.GetRigidBody();

      size_type numComponents = a_ent->size_components<phys_cs::RigidBodyShape>();
      error_type result = ErrorSuccess;

      for (size_type i = 0; i < numComponents; ++i)
      {
        const rb_shape_type rbShape =
          a_ent->GetComponent<phys_cs::RigidBodyShape>(i)->GetRigidBodyShape();

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
    RigidBodySystem (event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr,
                     world_type* a_world)
    : base_type(a_eventMgr, a_entityMgr, 
                register_type().Add<phys_cs::RigidBody>())
    , m_world(a_world)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type
    RigidBodySystem::
    InitializeEntity(entity_ptr a_ent)
  {
    error_type result = DoInitializeRigidBodyComponent(a_ent);

    if (result == ErrorSuccess)
    {
      result = InitializeRigidBodyShapeComponents(a_ent);
    }

    return result;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type
    RigidBodySystem::
    ShutdownEntity(entity_ptr a_ent )
  {
    error_type result = DoShutdownRigidBodyComponent(a_ent);

    return result;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodySystem::
    ProcessEntity(entity_ptr a_ent, f64)
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

    math_cs::transform_sptr
      transformPtr = a_ent->GetComponent<math_cs::Transform>();

    transform_type::position_type position((real_type)rbPosition[0],
                                           (real_type)rbPosition[1],
                                           transformPtr->GetPosition()[2]);

    transform_type::orientation_type orientation
      ((real_type)rbOrientation[0], (real_type)rbOrientation[2], (real_type)0,
       (real_type)rbOrientation[1], (real_type)rbOrientation[3], (real_type)0,
       (real_type)0,                (real_type)0,                (real_type)1);

    transformPtr->SetPosition(position);
    transformPtr->SetOrientation(orientation);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type
    RigidBodySystem::
    DoInitializeRigidBodyComponent(entity_ptr a_ent)
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
      TLOC_ASSERT_FALSE("Box2D RigidBody could not be allocated!");
      return TLOC_ERROR(error::error_rigid_body_could_not_be_allocated);
    }

    currRB.DoInitialize(currRBInternal, a_ent);
    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodySystem::error_type
    RigidBodySystem::
    DoShutdownRigidBodyComponent(entity_ptr a_ent)
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

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(RigidBodySystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(RigidBodySystem);