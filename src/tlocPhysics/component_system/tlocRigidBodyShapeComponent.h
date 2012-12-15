#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocPhysics/box2d/tlocRigidBodyShapeDef.h>

namespace tloc { namespace physics { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyShape component defines the "visible" physical structure
  /// of a RigidBody. Multiple RigidBodyShapes can be attached to one RigidBody.
  ///-------------------------------------------------------------------------
  class RigidBodyShape : public core::component_system::Component_T<RigidBodyShape>
  {
  public:
    typedef core::component_system::Component_T<RigidBodyShape> base_type;
    
    typedef RigidBodyShape            this_type;
    typedef box2d::RigidBodyShapeDef  rigid_body_shape_def_type;

  public:
    RigidBodyShape(const rigid_body_shape_def_type* a_rigidBodyShape);

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_shape_def_type*, GetRigidBodyShape, m_rigidBodyShape);

  private:
    const rigid_body_shape_def_type* m_rigidBodyShape;
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef core::smart_ptr::SharedPtr<RigidBodyShape>  RigidBodyShapePtr;
  
  typedef core::component_system::ComponentPool_TI<RigidBodyShapePtr> 
                                                      rigid_body_shape_pool;

};};};

#endif