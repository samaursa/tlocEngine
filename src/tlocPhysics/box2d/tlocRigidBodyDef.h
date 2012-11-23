#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_DEF_H_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_DEF_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/vector/tlocVector2.h>

#include <Box2D/Dynamics/b2Body.h>

namespace tloc { namespace physics { namespace box2d {

  namespace rigid_body
  {
    enum RigidBodyType
    {
      k_staticBody = b2_staticBody,
      k_kinematicBody = b2_kinematicBody,
      k_dynamicBody = b2_dynamicBody
    }; typedef u32 value_type;
  };

  class RigidBodyDef
  {
  public:
    friend class RigidBody;

  public:
    typedef RigidBodyDef  this_type;
    typedef b2BodyDef     rigid_body_def_value_type;

    typedef rigid_body::value_type  rigid_body_type_type;
    typedef b2BodyType              rigid_body_value_type_type;
    typedef math::Vec2f32           vec_type;
    typedef f32                     float_type;

  public:
    RigidBodyDef();

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_type_type, GetType, (rigid_body_type_type)m_rigidBodyDef.type);

    vec_type        GetPosition() const;

    TLOC_DECL_AND_DEF_GETTER
      (float_type,  GetAngle, m_rigidBodyDef.angle);

    vec_type        GetLinearVelocity() const;

    TLOC_DECL_AND_DEF_GETTER
      (float_type,  GetAngularVelocity, m_rigidBodyDef.angularVelocity);

    TLOC_DECL_AND_DEF_GETTER
      (float_type,  GetLinearDamping, m_rigidBodyDef.linearDamping);
    TLOC_DECL_AND_DEF_GETTER
      (float_type,  GetAngularDamping, m_rigidBodyDef.angularDamping);

    TLOC_DECL_AND_DEF_GETTER
      (bool,        IsBullet, m_rigidBodyDef.bullet);

    TLOC_DECL_AND_DEF_GETTER
      (bool,        IsSleepingAllowed, m_rigidBodyDef.allowSleep);
    TLOC_DECL_AND_DEF_GETTER
      (bool,        IsAwake, m_rigidBodyDef.awake);
    TLOC_DECL_AND_DEF_GETTER
      (bool,        IsActive, m_rigidBodyDef.active);

    TLOC_DECL_AND_DEF_GETTER
      (bool,        IsFixedRotation, m_rigidBodyDef.fixedRotation);

    TLOC_DECL_AND_DEF_GETTER
      (float_type,  GetGravityScale, m_rigidBodyDef.gravityScale);

  public:
    void            SetType(rigid_body_type_type a_rigidBodyType);

    void            SetPosition(vec_type a_position);

    TLOC_DECL_AND_DEF_SETTER
      (float_type,  SetAngle, m_rigidBodyDef.angle);

    void            SetLinearVelocity(vec_type a_linearVelocity);

    TLOC_DECL_AND_DEF_SETTER
      (float_type,  SetAngularVelocity, m_rigidBodyDef.angularVelocity);
    TLOC_DECL_AND_DEF_SETTER
      (float_type,  SetLinearDamping, m_rigidBodyDef.linearDamping);
    TLOC_DECL_AND_DEF_SETTER
      (float_type,  SetAngularDamping, m_rigidBodyDef.angularDamping);

    TLOC_DECL_AND_DEF_SETTER
      (bool,        SetBullet, m_rigidBodyDef.bullet);
    
    TLOC_DECL_AND_DEF_SETTER
      (bool,        SetAllowsSleep, m_rigidBodyDef.allowSleep);
    TLOC_DECL_AND_DEF_SETTER
      (bool,        SetAwake, m_rigidBodyDef.awake);
    TLOC_DECL_AND_DEF_SETTER
      (bool,        SetActive, m_rigidBodyDef.active);
    
    TLOC_DECL_AND_DEF_SETTER
      (bool,        SetFixedRotation, m_rigidBodyDef.fixedRotation);

    TLOC_DECL_AND_DEF_SETTER
      (float_type,  SetGravityScale, m_rigidBodyDef.gravityScale);

  protected:
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (rigid_body_def_value_type, GetRigidBodyDef, m_rigidBodyDef);

  private:
    rigid_body_def_value_type m_rigidBodyDef;
  };

};};};

#endif