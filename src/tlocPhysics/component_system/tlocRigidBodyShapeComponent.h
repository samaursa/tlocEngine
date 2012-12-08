#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocPhysics/box2d/tlocRigidBodyShape.h>

namespace tloc { namespace physics { namespace component_system {

  class RigidBodyShape : public core::component_system::Component_T<RigidBodyShape>
  {
  public:
    typedef core::component_system::Component_T<RigidBodyShape> base_type;
    
    typedef RigidBodyShape        this_type;
    typedef box2d::RigidBodyShape rigid_body_shape_type;

  public:
    RigidBodyShape(const rigid_body_shape_type* a_rigidBodyShape);

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_shape_type*, GetRigidBodyShape, m_rigidBodyShape);

  private:
    const rigid_body_shape_type* m_rigidBodyShape;
  };

};};};

#endif