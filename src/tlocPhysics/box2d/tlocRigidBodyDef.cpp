#include "tlocRigidBodyDef.h"

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace physics { namespace box2d {

  RigidBodyDef::RigidBodyDef()
  {
    SetPosition(vec_type(0.0f,0.0f));
    SetAngle(0.0f);
    SetLinearVelocity(vec_type(0.0f,0.0f));
    SetAngularVelocity(0.0f);
    SetLinearDamping(0.0f);
    SetAngularDamping(0.0f);
    SetAllowsSleep(true);
    SetAwake(true);
    SetFixedRotation(false);
    SetBullet(false);
    SetType(k_staticBody);
    SetActive(true);
    SetGravityScale(1.0f);
  }

  RigidBodyDef::vec_type RigidBodyDef::GetPosition() const
  {
    return vec_type(m_rigidBodyDef.position.x, m_rigidBodyDef.position.y);
  }

  RigidBodyDef::vec_type RigidBodyDef::GetLinearVelocity() const
  {
    return vec_type(m_rigidBodyDef.linearVelocity.x,
      m_rigidBodyDef.linearVelocity.y);
  }

  void RigidBodyDef::SetType(rigid_body_type a_rigidBodyType)
  {
    m_rigidBodyDef.type = (rigid_body_value_type)a_rigidBodyType;
  }

  void RigidBodyDef::SetPosition(vec_type a_position)
  {
    m_rigidBodyDef.position.x = a_position[0];
    m_rigidBodyDef.position.y = a_position[1];
  }

  void RigidBodyDef::SetLinearVelocity(vec_type a_linearVelocity)
  {
    m_rigidBodyDef.linearVelocity.x = a_linearVelocity[0];
    m_rigidBodyDef.linearVelocity.y = a_linearVelocity[1];
  }

};};};