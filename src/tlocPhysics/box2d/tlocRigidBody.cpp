#include "tlocRigidBody.h"
#include "tlocRigidBody.inl.h"

#include <tlocCore/tlocAssert.h>

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

  RigidBody::error_type
    RigidBody::
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
      TLOC_ASSERT_FALSE("Box2D Fixture could not be allocated!");
      return TLOC_ERROR(error::error_rigid_body_shape_could_not_be_created);
    }

    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetTransform(vec_type& a_position, matrix_type& a_orientation) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    GetPosition(a_position);
    GetOrientation(a_orientation);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetTransform(vec_type& a_position, angle_type& a_angle) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    GetPosition(a_position);
    a_angle = GetAngle();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetPosition(vec_type& a_position) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& position = m_rigidBody->GetTransform().p;
    a_position[0] = position.x;
    a_position[1] = position.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetOrientation(matrix_type& a_orientation) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Rot& orientation = m_rigidBody->GetTransform().q;
    float_type values[4] = {orientation.c, -orientation.s,
                            orientation.s,  orientation.c};

    a_orientation.Set(values, matrix_type::k_RowMajor);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::angle_type
    RigidBody::
    GetAngle() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return angle_type(m_rigidBody->GetAngle());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetCenterOfMassWorld(vec_type& a_center) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& center = m_rigidBody->GetWorldCenter();
    a_center[0] = center.x;
    a_center[1] = center.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetCenterOfMassLocal(vec_type& a_center) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& center = m_rigidBody->GetWorldCenter();
    a_center[0] = center.x;
    a_center[1] = center.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    GetLinearVelocity(vec_type& a_velocity) const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    const b2Vec2& velocity = m_rigidBody->GetLinearVelocity();
    a_velocity[0] = velocity.x;
    a_velocity[1] = velocity.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::angle_type
    RigidBody::
    GetAngularVelocity() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return angle_type(m_rigidBody->GetAngularVelocity());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::float_type
    RigidBody::
    GetMass() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetMass();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::float_type
    RigidBody::
    GetInertia() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetInertia();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::vec_type
    RigidBody::
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

  RigidBody::vec_type
    RigidBody::
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

  RigidBody::float_type
    RigidBody::
    GetLinearDamping() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetLinearDamping();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::float_type
    RigidBody::
    GetAngularDamping() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetAngularDamping();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::float_type
    RigidBody::
    GetGravityScale() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->GetGravityScale();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::rigid_body_type_type
    RigidBody::
    GetType() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return (rigid_body_type_type)m_rigidBody->GetType();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBody::
    IsBullet() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsBullet();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBody::
    IsSleepingAllowed() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsSleepingAllowed();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBody::
    IsAwake() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsAwake();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBody::
    IsActive() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsActive();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBody::
    IsFixedRotation() const
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return m_rigidBody->IsFixedRotation();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetTransform(const vec_type& a_position, angle_type a_angle)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 position( static_cast<float_internal_type>(a_position[0]),
                     static_cast<float_internal_type>(a_position[1]) );

    float_internal_type angle = static_cast<float_internal_type>(a_angle.Get());

    m_rigidBody->SetTransform(position, angle);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetLinearVelocity(const vec_type& a_velocity)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 velocity( static_cast<float_internal_type>(a_velocity[0]),
                     static_cast<float_internal_type>(a_velocity[1]) );

    m_rigidBody->SetLinearVelocity(velocity);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetAngularVelocity(angle_type a_omega)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    float_internal_type omega = static_cast<float_internal_type>(a_omega.Get());

    m_rigidBody->SetAngularVelocity(omega);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
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

  void
    RigidBody::
    ApplyForceToCenter(const vec_type& a_force)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2Vec2 force( static_cast<float_internal_type>(a_force[0]),
                  static_cast<float_internal_type>(a_force[1]) );
    m_rigidBody->ApplyForceToCenter(force);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    ApplyTorque(float_type a_torque)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->ApplyTorque( static_cast<float_internal_type>(a_torque) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
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

  void
    RigidBody::
    ApplyAngularImpulse(float_type a_impulse)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      ApplyAngularImpulse( static_cast<float_internal_type>(a_impulse) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetLinearDamping(float_type a_linearDamping)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      SetLinearDamping( static_cast<float_internal_type>(a_linearDamping) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetAngularDamping(float_type a_angularDamping)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      SetAngularDamping( static_cast<float_internal_type>(a_angularDamping) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetGravityScale(float_type a_gravityScale)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->
      SetGravityScale( static_cast<float_internal_type>(a_gravityScale) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetBullet(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetBullet(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetSleepingAllowed(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetSleepingAllowed(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetAwake(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetAwake(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetActive(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetActive(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    SetFixedRotation(bool a_flag)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetFixedRotation(a_flag);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::
    RigidBody()
    : m_flags(k_count)
    , m_rigidBody(nullptr)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::error_type
    RigidBody::
    DoInitialize(rigid_body_internal_type* a_rigidBody,
                 const_entity_ptr a_parent)
  {
    TLOC_ASSERT_RIGID_BODY_NOT_INITIALIZED();
    TLOC_ASSERT_NOT_NULL(a_rigidBody);

    m_rigidBody = a_rigidBody;

    m_flags.Mark(k_initialized);
    DoSetParent(a_parent);

    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::error_type
    RigidBody::
    DoShutdown()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();

    m_rigidBody = nullptr;

    m_flags.Unmark(k_initialized);
    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::rigid_body_internal_type*
    RigidBody::
    DoGetInternalRigidBody()
  {
    return m_rigidBody;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const RigidBody::entity_type*
    RigidBody::
    DoGetParent()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    return static_cast<const entity_type*>(m_rigidBody->GetUserData());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    DoSetParent(const_entity_ptr a_parent)
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    TLOC_ASSERT(a_parent != nullptr, "Use DoSetParentNull instead!");
    // const_cast is necessary to turn the pointer into a void*, the method
    // DoGetParent ensures that we respect the constness and pass it back
    // as a const ptr
    m_rigidBody->SetUserData( const_cast<entity_type*>(a_parent.get()) );
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    DoSetParentNull()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    m_rigidBody->SetUserData(nullptr);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_RigidBodyType>
  void
    RigidBody::
    DoSetType()
  {
    TLOC_ASSERT_RIGID_BODY_INITIALIZED();
    b2BodyType bodyType =
      static_cast<b2BodyType>(T_RigidBodyType::s_rigidBodyType);

    m_rigidBody->SetType(bodyType);
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiation

  template void RigidBody::DoSetType<p_rigid_body::StaticBody>();
  template void RigidBody::DoSetType<p_rigid_body::KinematicBody>();
  template void RigidBody::DoSetType<p_rigid_body::DynamicBody>();

};};};
