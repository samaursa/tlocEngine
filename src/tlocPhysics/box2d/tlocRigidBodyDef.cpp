#include "tlocRigidBodyDef.h"

#include <tlocMath/vector/tlocVector2.inl>

#include <Box2D/Dynamics/b2Body.h>

namespace tloc { namespace physics { namespace box2d {

  namespace p_rigid_body
  {
    const value_type StaticBody   ::s_rigidBodyType = b2_staticBody;
    const value_type KinematicBody::s_rigidBodyType = b2_kinematicBody;
    const value_type DynamicBody  ::s_rigidBodyType = b2_dynamicBody;
  }

  RigidBodyDef::
    RigidBodyDef()
  {
    m_rigidBodyDef = new rigid_body_def_internal_type;

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
    SetType<p_rigid_body::StaticBody>();
    SetActive(true);
    SetGravityScale(1.0f);
  }

  RigidBodyDef::
    ~RigidBodyDef()
  {
    delete m_rigidBodyDef;
  }

  RigidBodyDef::rigid_body_type_type RigidBodyDef::
    GetType() const
  {
    return static_cast<rigid_body_type_type>(m_rigidBodyDef->type);
  }

  RigidBodyDef::vec_type RigidBodyDef::
    GetPosition() const
  {
    return vec_type(m_rigidBodyDef->position.x, m_rigidBodyDef->position.y);
  }

  RigidBodyDef::float_type RigidBodyDef::
    GetAngle() const
  {
    return m_rigidBodyDef->angle;
  }

  RigidBodyDef::vec_type RigidBodyDef::
    GetLinearVelocity() const
  {
    return vec_type(m_rigidBodyDef->linearVelocity.x,
                    m_rigidBodyDef->linearVelocity.y);
  }

  RigidBodyDef::float_type RigidBodyDef::
    GetAngularVelocity() const
  {
    return m_rigidBodyDef->angularVelocity;
  }

  RigidBodyDef::float_type RigidBodyDef::
    GetLinearDamping() const
  {
    return m_rigidBodyDef->linearDamping;
  }

  RigidBodyDef::float_type RigidBodyDef::
    GetAngularDamping() const
  {
    return m_rigidBodyDef->angularDamping;
  }

  bool RigidBodyDef::
    IsBullet() const
  {
    return m_rigidBodyDef->bullet;
  }

  bool RigidBodyDef::
    IsSleepingAllowed() const
  {
    return m_rigidBodyDef->allowSleep;
  }

  bool RigidBodyDef::
    IsAwake() const
  {
    return m_rigidBodyDef->awake;
  }

  bool RigidBodyDef::
    IsActive() const
  {
    return m_rigidBodyDef->active;
  }

  bool RigidBodyDef::
    IsFixedrotation() const
  {
    return m_rigidBodyDef->fixedRotation;
  }

  RigidBodyDef::float_type RigidBodyDef::
    GetGravityScale() const
  {
    return m_rigidBodyDef->gravityScale;
  }

  void RigidBodyDef::
    SetPosition(vec_type a_position)
  {
    m_rigidBodyDef->position.x = a_position[0];
    m_rigidBodyDef->position.y = a_position[1];
  }

  void RigidBodyDef::
    SetAngle(float_type a_angle)
  {
    m_rigidBodyDef->angle = a_angle;
  }

  void RigidBodyDef::
    SetLinearVelocity(vec_type a_linearVelocity)
  {
    m_rigidBodyDef->linearVelocity.x = a_linearVelocity[0];
    m_rigidBodyDef->linearVelocity.y = a_linearVelocity[1];
  }

  void RigidBodyDef::
    SetAngularVelocity(float a_angularVelocity)
  {
    m_rigidBodyDef->angularVelocity = a_angularVelocity;
  }

  void RigidBodyDef::
    SetLinearDamping(float_type a_linearDamping)
  {
    m_rigidBodyDef->linearDamping = a_linearDamping;
  }

  void RigidBodyDef::
    SetAngularDamping(float_type a_angularDamping)
  {
    m_rigidBodyDef->angularDamping = a_angularDamping;
  }

  void RigidBodyDef::
    SetBullet(bool a_bullet)
  {
    m_rigidBodyDef->bullet = a_bullet;
  }

  void RigidBodyDef::
    SetAllowsSleep(bool a_allowSleep)
  {
    m_rigidBodyDef->allowSleep = a_allowSleep;
  }

  void RigidBodyDef::
    SetAwake(bool a_awake)
  {
    m_rigidBodyDef->awake = a_awake;
  }

  void RigidBodyDef::
    SetActive(bool a_active)
  {
    m_rigidBodyDef->active = a_active;
  }

  void RigidBodyDef::
    SetFixedRotation(bool a_fixedRotation)
  {
    m_rigidBodyDef->fixedRotation = a_fixedRotation;
  }

  void RigidBodyDef::
    SetGravityScale(float_type a_gravityScale)
  {
    m_rigidBodyDef->gravityScale = a_gravityScale;
  }

  const RigidBodyDef::rigid_body_def_internal_type& RigidBodyDef::
    GetRigidBodyDef() const
  {
    return *m_rigidBodyDef;
  }

  template <typename T_RigidBodyType>
  void RigidBodyDef::
    DoSetType()
  {
    m_rigidBodyDef->type =
      static_cast<b2BodyType>(T_RigidBodyType::s_rigidBodyType);
  }

  //------------------------------------------------------------------------
  // Explicit instantiation

  template void RigidBodyDef::DoSetType<p_rigid_body::StaticBody>();
  template void RigidBodyDef::DoSetType<p_rigid_body::KinematicBody>();
  template void RigidBodyDef::DoSetType<p_rigid_body::DynamicBody>();

};};};