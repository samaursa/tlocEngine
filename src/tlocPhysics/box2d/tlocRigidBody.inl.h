#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_INL_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_INL_

#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_H_
#error "Must include header before including the inline file"
#endif

#include <tlocMath/types/tlocVector2.inl.h>
#include <tlocMath/types/tlocMatrix2.inl.h>

#include <tlocPhysics/error/tlocErrorTypes.h>
#include <tlocPhysics/box2d/tlocWorld.h>

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_ASSERT_RIGID_BODY_INITIALIZED() \
  TLOC_ASSERT(m_flags[k_initialized], "Rigid body has not been initialized!");

#define TLOC_ASSERT_RIGID_BODY_NOT_INITIALIZED() \
  TLOC_ASSERT(!m_flags[k_initialized], "Rigid body has already been initialized!");

  //////////////////////////////////////////////////////////////////////////
  // Free definitions

  namespace {

    //////////////////////////////////////////////////////////////////////////
    // Typedefs
    typedef f32   float_internal_type;

    //////////////////////////////////////////////////////////////////////////
    // Constants

    enum flags
    {
      k_initialized = 0,
      k_count
    };

  }

  //////////////////////////////////////////////////////////////////////////
  // RigidBody

  TL_I RigidBody::error_type RigidBody::
    CreateRigidBodyShape(const rigid_body_shape_def_type& a_rigidBodyShape)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    typedef rigid_body_shape_def_type::fixture_def_internal_type
                                                      fixture_def_internal_type;

    typedef b2Fixture                                 fixture_interal_type;

    rigid_body_shape_def_type rigidBodyShape = a_rigidBodyShape;

    rigidBodyShape.DoSetParent(DoGetParent());

    const fixture_def_internal_type& fixtureDef =
      rigidBodyShape.DoGetFixtureDef();

    fixture_interal_type* fixture = m_rigidBody->CreateFixture(&fixtureDef);

    if (fixture == nullptr)
    {
      TLOC_ASSERT(false, "Box2D Fixture could not be allocated!");
      return TLOC_ERROR(error::error_rigid_body_shape_could_not_be_created);
    }

    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetTransform(vec_type& a_position, matrix_type& a_orientation) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    GetPosition(a_position);
    GetOrientation(a_orientation);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetTransform(vec_type& a_position, angle_type& a_angle) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    GetPosition(a_position);
    a_angle = GetAngle();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetPosition(vec_type& a_position) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& position = m_rigidBody->GetTransform().p;
    a_position[0] = position.x;
    a_position[1] = position.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetOrientation(matrix_type& a_orientation) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Rot& orientation = m_rigidBody->GetTransform().q;
    float_type values[4] = {orientation.c, -orientation.s,
                            orientation.s,  orientation.c};

    a_orientation.Set(values, matrix_type::k_RowMajor);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::angle_type RigidBody::
    GetAngle() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return angle_type(m_rigidBody->GetAngle());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetCenterOfMassWorld(vec_type& a_center) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& center = m_rigidBody->GetWorldCenter();
    a_center[0] = center.x;
    a_center[1] = center.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetCenterOfMassLocal(vec_type& a_center) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& center = m_rigidBody->GetWorldCenter();
    a_center[0] = center.x;
    a_center[1] = center.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    GetLinearVelocity(vec_type& a_velocity) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& velocity = m_rigidBody->GetLinearVelocity();
    a_velocity[0] = velocity.x;
    a_velocity[1] = velocity.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::angle_type RigidBody::
    GetAngularVelocity() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return angle_type(m_rigidBody->GetAngularVelocity());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::float_type RigidBody::
    GetMass() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetMass();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::float_type RigidBody::
    GetInertia() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetInertia();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::vec_type RigidBody::
    GetLinearVelocityFromWorldPoint(const vec_type& a_worldPoint) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2 worldPoint( static_cast<float_internal_type>(a_worldPoint[0]),
                             static_cast<float_internal_type>(a_worldPoint[1]) );
    const b2Vec2 linearVelocity =
      m_rigidBody->GetLinearVelocityFromWorldPoint(worldPoint);

    return vec_type(linearVelocity.x, linearVelocity.y);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::vec_type RigidBody::
    GetLinearVelocityFromLocalPoint(const vec_type& a_localPoint) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2 localPoint( static_cast<float_internal_type>(a_localPoint[0]),
                             static_cast<float_internal_type>(a_localPoint[1]) );
    const b2Vec2 linearVelocity =
      m_rigidBody->GetLinearVelocityFromLocalPoint(localPoint);

    return vec_type(linearVelocity.x, linearVelocity.y);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::float_type RigidBody::
    GetLinearDamping() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetLinearDamping();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::float_type RigidBody::
    GetAngularDamping() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetAngularDamping();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::float_type RigidBody::
    GetGravityScale() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetGravityScale();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::rigid_body_type_type RigidBody::
    GetType() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return (rigid_body_type_type)m_rigidBody->GetType();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I bool RigidBody::
    IsBullet() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsBullet();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I bool RigidBody::
    IsSleepingAllowed() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsSleepingAllowed();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I bool RigidBody::
    IsAwake() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsAwake();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I bool RigidBody::
    IsActive() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsActive();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I bool RigidBody::
    IsFixedRotation() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsFixedRotation();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetTransform(const vec_type& a_position, angle_type a_angle)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 position( static_cast<float_internal_type>(a_position[0]),
                     static_cast<float_internal_type>(a_position[1]) );

    float_internal_type angle = static_cast<float_internal_type>(a_angle.Get());

    m_rigidBody->SetTransform(position, angle);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetLinearVelocity(const vec_type& a_velocity)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 velocity( static_cast<float_internal_type>(a_velocity[0]),
                     static_cast<float_internal_type>(a_velocity[1]) );

    m_rigidBody->SetLinearVelocity(velocity);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetAngularVelocity(angle_type a_omega)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    float_internal_type omega = static_cast<float_internal_type>(a_omega.Get());

    m_rigidBody->SetAngularVelocity(omega);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    ApplyForce(const vec_type& a_force, const vec_type& a_point)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 force( static_cast<float_internal_type>(a_force[0]),
                  static_cast<float_internal_type>(a_force[1]) );

    b2Vec2 point( static_cast<float_internal_type>(a_point[0]),
                  static_cast<float_internal_type>(a_point[1]) );

    m_rigidBody->ApplyForce(force, point);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    ApplyForceToCenter(const vec_type& a_force)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 force( static_cast<float_internal_type>(a_force[0]),
                  static_cast<float_internal_type>(a_force[1]) );
    m_rigidBody->ApplyForceToCenter(force);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    ApplyTorque(float_type a_torque)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->ApplyTorque( static_cast<float_internal_type>(a_torque) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    ApplyLinearImpulse(const vec_type& a_impulse,
                       const vec_type& a_point)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 impulse( static_cast<float_internal_type>(a_impulse[0]),
                    static_cast<float_internal_type>(a_impulse[1]) );

    b2Vec2 point( static_cast<float_internal_type>(a_point[0]),
                  static_cast<float_internal_type>(a_point[1]) );

    m_rigidBody->ApplyLinearImpulse(impulse, point);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    ApplyAngularImpulse(float_type a_impulse)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      ApplyAngularImpulse( static_cast<float_internal_type>(a_impulse) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetLinearDamping(float_type a_linearDamping)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      SetLinearDamping( static_cast<float_internal_type>(a_linearDamping) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetAngularDamping(float_type a_angularDamping)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      SetAngularDamping( static_cast<float_internal_type>(a_angularDamping) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetGravityScale(float_type a_gravityScale)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      SetGravityScale( static_cast<float_internal_type>(a_gravityScale) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetBullet(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetBullet(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetSleepingAllowed(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetSleepingAllowed(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetAwake(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetAwake(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetActive(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetActive(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    SetFixedRotation(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetFixedRotation(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::
    RigidBody()
    : m_flags(k_count)
    , m_rigidBody(nullptr)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::error_type RigidBody::
    DoInitialize(rigid_body_internal_type* a_rigidBody,
                 const entity_type* a_parent)
  {
    TLOC_ASSERT_RIGID_BODY_NOT_INITIALIZED();
    TLOC_ASSERT_NOT_NULL(a_rigidBody);

    m_rigidBody = a_rigidBody;

    m_flags.Mark(k_initialized);
    DoSetParent(a_parent);

    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::error_type RigidBody::
    DoShutdown()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    m_rigidBody = nullptr;

    m_flags.Unmark(k_initialized);
    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I RigidBody::rigid_body_internal_type* RigidBody::
    DoGetInternalRigidBody()
  {
    return m_rigidBody;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I const RigidBody::entity_type* RigidBody::
    DoGetParent()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return static_cast<const entity_type*>(m_rigidBody->GetUserData());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    DoSetParent(const entity_type* a_parent)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    TLOC_ASSERT(a_parent != nullptr, "Use DoSetParentNull instead!");
    // const_cast is necessary to turn the pointer into a void*, the method
    // DoGetParent ensures that we respect the constness and pass it back
    // as a const ptr
    m_rigidBody->SetUserData( const_cast<entity_type*>(a_parent) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TL_I void RigidBody::
    DoSetParentNull()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetUserData(nullptr);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_RigidBodyType>
  TL_I void RigidBody::
    DoSetType()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2BodyType bodyType =
      static_cast<b2BodyType>(T_RigidBodyType::s_rigidBodyType);

    m_rigidBody->SetType(bodyType);
  }

};};};

#endif