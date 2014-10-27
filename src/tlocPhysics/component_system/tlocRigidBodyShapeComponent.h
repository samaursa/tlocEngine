#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocPhysics/box2d/tlocRigidBodyShapeDef.h>
#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyShape component defines the "visible" physical structure
  /// of a RigidBody. Multiple RigidBodyShapes can be attached to one RigidBody.
  ///-------------------------------------------------------------------------
  class RigidBodyShape
    : public core_cs::Component_T<RigidBodyShape, 
                                  core_cs::component_group::k_physics, 
                                  components::k_rigidBodyShape>
  {
  public:
    typedef RigidBodyShape                              this_type;
    typedef core_cs::Component_T
      <this_type, k_component_group, k_component_type>  base_type;

    typedef box2d::RigidBodyShapeDef                    rigid_body_shape_def;

  public:
    RigidBodyShape();
    RigidBodyShape(const rigid_body_shape_def& a_rigidBodyShape);

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_shape_def, GetRigidBodyShape, m_rigidBodyShape);

  private:
    rigid_body_shape_def m_rigidBodyShape;
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(RigidBodyShape, rigid_body_shape);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(RigidBodyShape, rigid_body_shape);
  TLOC_TYPEDEF_COMPONENT_POOL(RigidBodyShape, rigid_body_shape);

};};};

#endif