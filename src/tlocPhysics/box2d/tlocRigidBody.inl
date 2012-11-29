#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_INL_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_INL_

#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_H_
#error "Must include header before including the inline file"
#endif

#include <tlocMath/vector/tlocVector2.inl>

#include <tlocPhysics/box2d/tlocWorld.h>
#include <Box2D/Common/b2Math.h>


namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_ASSERT_RIGID_BODY_INITIALIZED() \
  TLOC_ASSERT(m_flags[initialized], "Rigid body has not been initialized!");

#define TLOC_ASSERT_RIGID_BODY_NOT_INITIALIZED() \
  TLOC_ASSERT(!m_flags[initialized], "Rigid body has already been initialized!");

  //////////////////////////////////////////////////////////////////////////
  // Constants

  enum flags
  {
    initialized,
    count
  };

  //////////////////////////////////////////////////////////////////////////
  // RigidBody

  TL_I RigidBody::error_type 
    RigidBody::CreateRigidBodyShape(rigid_body_shape_type& a_rigidBodyShape)
  {
    typedef rigid_body_shape_type::fixture_def_internal_type
      fixture_def_internal_type;
    const fixture_def_internal_type& fixtureDef = 
      a_rigidBodyShape.GetFixtureDef();

    m_rigidBody->CreateFixture(&fixtureDef);
  }
  
  TL_I void RigidBody::GetTransform(vec_type& a_position, angle_type& a_angle) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    GetPosition(a_position);
    a_angle = GetAngle();
  }

  TL_I void RigidBody::GetPosition(math::Vec2f& a_position) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& position = m_rigidBody->GetTransform().p;
    a_position[0] = position.x;
    a_position[1] = position.y;
  }

  TL_I RigidBody::angle_type RigidBody::GetAngle() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return angle_type(m_rigidBody->GetAngle());
  }

  TL_I void RigidBody::GetCenterOfMassWorld(vec_type& a_center) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& center = m_rigidBody->GetWorldCenter();
    a_center[0] = center.x;
    a_center[1] = center.y;
  }

  TL_I void RigidBody::GetCenterOfMassLocal(vec_type& a_center) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& center = m_rigidBody->GetWorldCenter();
    a_center[0] = center.x;
    a_center[1] = center.y;
  }

  TL_I void RigidBody::GetLinearVelocity(vec_type& a_velocity) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& velocity = m_rigidBody->GetLinearVelocity();
    a_velocity[0] = velocity.x;
    a_velocity[1] = velocity.y;
  }

  TL_I RigidBody::angle_type RigidBody::GetAngularVelocity() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return angle_type(m_rigidBody->GetAngularVelocity());
  }

  TL_I RigidBody::float_type RigidBody::GetMass() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetMass();
  }

  TL_I RigidBody::float_type RigidBody::GetInertia() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetInertia();
  }

  TL_I RigidBody::vec_type
    RigidBody::GetLinearVelocityFromWorldPoint(const vec_type& a_worldPoint) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2 worldPoint(a_worldPoint[0], a_worldPoint[1]);
    const b2Vec2 linearVelocity =
      m_rigidBody->GetLinearVelocityFromWorldPoint(worldPoint);

    return vec_type(linearVelocity.x, linearVelocity.y);
  }

  TL_I RigidBody::vec_type
    RigidBody::GetLinearVelocityFromLocalPoint(const vec_type& a_localPoint) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2 localPoint(a_localPoint[0], a_localPoint[1]);
    const b2Vec2 linearVelocity =
      m_rigidBody->GetLinearVelocityFromLocalPoint(localPoint);

    return vec_type(linearVelocity.x, linearVelocity.y);
  }

  TL_I RigidBody::float_type RigidBody::GetLinearDamping() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetLinearDamping();
  }

  TL_I RigidBody::float_type RigidBody::GetAngularDamping() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetAngularDamping();
  }

  TL_I RigidBody::float_type RigidBody::GetGravityScale() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetGravityScale();
  }

  TL_I RigidBody::rigid_body_type_type RigidBody::GetType() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return (rigid_body_type_type)m_rigidBody->GetType();
  }

  TL_I bool RigidBody::IsBullet() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsBullet();
  }

  TL_I bool RigidBody::IsSleepingAllowed() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsSleepingAllowed();
  }

  TL_I bool RigidBody::IsAwake() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsAwake();
  }

  TL_I bool RigidBody::IsActive() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsActive();
  }

  TL_I bool RigidBody::IsFixedRotation() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsFixedRotation();
  }

  TL_I void RigidBody::SetTransform(const vec_type& a_position, angle_type a_angle)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 position(a_position[0], a_position[1]);
    m_rigidBody->SetTransform(position, a_angle.Get());
  }

  TL_I void RigidBody::SetLinearVelocity(const vec_type& a_velocity)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 velocity(a_velocity[0], a_velocity[1]);
    m_rigidBody->SetLinearVelocity(velocity);
  }

  TL_I void RigidBody::SetAngularVelocity(angle_type a_omega)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetAngularVelocity(a_omega.Get());
  }

  TL_I void RigidBody::ApplyForce(const vec_type& a_force, const vec_type& a_point)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    b2Vec2 force(a_force[0], a_force[1]);
    b2Vec2 point(a_point[0], a_point[1]);
    m_rigidBody->ApplyForce(force, point);
  }

  TL_I void RigidBody::ApplyForceToCenter(const vec_type& a_force)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 force(a_force[0], a_force[1]);
    m_rigidBody->ApplyForceToCenter(force);
  }

  TL_I void RigidBody::ApplyTorque(float_type a_torque)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->ApplyTorque(a_torque);
  }

  TL_I void RigidBody::ApplyLinearImpulse(const vec_type& a_impulse,
    const vec_type& a_point)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 impulse(a_impulse[0], a_impulse[1]);
    b2Vec2 point(a_point[0], a_point[1]);
    m_rigidBody->ApplyLinearImpulse(impulse, point);
  }

  TL_I void RigidBody::ApplyAngularImpulse(float_type a_impulse)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->ApplyAngularImpulse(a_impulse);
  }

  TL_I void RigidBody::SetLinearDamping(float_type a_linearDamping)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetLinearDamping(a_linearDamping);
  }

  TL_I void RigidBody::SetAngularDamping(float_type a_angularDamping)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetAngularDamping(a_angularDamping);
  }

  TL_I void RigidBody::SetGravityScale(float_type a_gravityScale)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetGravityScale(a_gravityScale);
  }

  TL_I void RigidBody::SetType(rigid_body_type_type a_type)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetType((rigid_body_internal_type_type)a_type);
  }

  TL_I void RigidBody::SetBullet(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetBullet(a_flag);
  }

  TL_I void RigidBody::SetSleepingAllowed(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetSleepingAllowed(a_flag);
  }

  TL_I void RigidBody::SetAwake(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetAwake(a_flag);
  }

  TL_I void RigidBody::SetActive(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetActive(a_flag);
  }

  TL_I void RigidBody::SetFixedRotation(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetFixedRotation(a_flag);
  }

  TL_I RigidBody::RigidBody()
    : m_flags(count)
    , m_rigidBody(NULL)
  {

  }

  TL_I RigidBody::error_type
    RigidBody::Initialize(rigid_body_internal_type* a_rigidBody, 
                          component_system::RigidBody* a_parent)
  {
    TLOC_ASSERT_RIGID_BODY_NOT_INITIALIZED();
    TLOC_ASSERT_NOT_NULL(a_rigidBody);

    m_rigidBody = a_rigidBody;
    DoSetParent(a_parent);

    m_flags.Mark(initialized);
    return ErrorSuccess();
  }

  TL_I RigidBody::error_type RigidBody::Shutdown()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    m_rigidBody = NULL;
    DoSetParentNull();

    m_flags.Unmark(initialized);
    return ErrorSuccess();
  }

  TL_I RigidBody::rigid_body_internal_type* RigidBody::GetInternalRigidBody()
  {
    return m_rigidBody;
  }

  TL_I component_system::RigidBody* RigidBody::DoGetParent()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return static_cast<component_system::RigidBody*>(m_rigidBody->GetUserData());
  }

  TL_I void RigidBody::DoSetParent(component_system::RigidBody* a_parent)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    TLOC_ASSERT(a_parent != NULL, "Use DoSetParentNull instead!");
    m_rigidBody->SetUserData(a_parent);
  }

  TL_I void RigidBody::DoSetParentNull()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetUserData(NULL);
  }

};};};

#endif