#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_H_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/matrix/tlocMatrix2.h>
#include <tlocMath/types/tlocAngle.h>

#include <tlocPhysics/box2d/tlocRigidBodyDef.h>
#include <tlocPhysics/box2d/tlocRigidBodyShapeDef.h>

class b2Body;

namespace tloc { namespace physics { namespace component_system {

  class RigidBodySystem;
  class RigidBody;

};};};

namespace tloc { namespace physics { namespace box2d {

  class World;

  ///-------------------------------------------------------------------------
  /// @brief  RigidBody is an internal class used in RigidBodyComponent. Defines
  /// the "invisible" physical attributes of a rigid body.
  ///-------------------------------------------------------------------------
  class RigidBody
  {
  public:
    friend class component_system::RigidBody;
    friend class component_system::RigidBodySystem;

  public:
    typedef RigidBody             this_type;
    typedef b2Body                rigid_body_internal_type;
    typedef core::error::Error    error_type;

    typedef tl_float              float_type;
    typedef math::Vec2f           vec_type;
    typedef math::Mat2f           matrix_type;
    typedef math::Radian          angle_type;

    typedef RigidBodyDef                       rigid_body_def_type;

    typedef rigid_body_def_type::rigid_body_type_type
                                               rigid_body_type_type;

    typedef RigidBodyShapeDef                  rigid_body_shape_def_type;

    typedef World                              world_type;

  public:
    error_type
      CreateRigidBodyShape(const rigid_body_shape_def_type& a_rigidBodyShape);

  public:

    void GetTransform(vec_type& a_position, matrix_type& a_orientation) const;
    void GetTransform(vec_type& a_position, angle_type& a_angle) const;

    void GetPosition(math::Vec2f& a_position) const;
    void GetOrientation(matrix_type& a_orientation) const;
    angle_type GetAngle() const;

    void GetCenterOfMassWorld(vec_type& a_center) const;
    void GetCenterOfMassLocal(vec_type& a_center) const;

    void GetLinearVelocity(vec_type& a_velocity) const;
    angle_type GetAngularVelocity() const;

    float_type GetMass() const;

    float_type GetInertia() const;

    vec_type GetLinearVelocityFromWorldPoint(const vec_type& a_worldPoint) const;
    vec_type GetLinearVelocityFromLocalPoint(const vec_type& a_localPoint) const;

    float_type GetLinearDamping() const;
    float_type GetAngularDamping() const;

    float_type GetGravityScale() const;

    rigid_body_type_type GetType() const;

    bool IsBullet() const;

    bool IsSleepingAllowed() const;
    bool IsAwake() const;
    bool IsActive() const;

    bool IsFixedRotation() const;

  public:
    void SetTransform(const vec_type& a_position, angle_type a_angle);

    void SetLinearVelocity(const vec_type& a_velocity);
    void SetAngularVelocity(angle_type a_omega);

    void ApplyForce(const vec_type& a_force, const vec_type& a_point);
    void ApplyForceToCenter(const vec_type& a_force);

    void ApplyTorque(float_type a_torque);

    void ApplyLinearImpulse(const vec_type& a_impulse, const vec_type& a_point);
    void ApplyAngularImpulse(float_type a_impulse);

    void SetLinearDamping(float_type a_linearDamping);
    void SetAngularDamping(float_type a_angularDamping);

    void SetGravityScale(float_type a_gravityScale);

    template <typename T_RigidBodyType>
    void SetType(rigid_body_type_type a_type)
    {
      type_traits::AssertTypeIsSupported
        < T_RigidBodyType,
        p_rigid_body::StaticBody,
        p_rigid_body::KinematicBody,
        p_rigid_body::DynamicBody>();
      DoSetType<T_RigidBodyType>();
    }

    void SetBullet(bool a_flag);

    void SetSleepingAllowed(bool a_flag);
    void SetAwake(bool a_flag);
    void SetActive(bool a_flag);

    void SetFixedRotation(bool a_flag);

  protected:
    typedef core::component_system::Entity  entity_type ;

    RigidBody();

    error_type DoInitialize(rigid_body_internal_type* a_rigidBody,
                            entity_type* a_parent);
    error_type DoShutdown();

  protected:
    rigid_body_internal_type* DoGetInternalRigidBody();

    entity_type* DoGetParent();
    void DoSetParent(entity_type* a_parent);
    void DoSetParentNull();

  private:
    template <typename T_RigidBodyType>
    void DoSetType();

  private:
    core::utils::Checkpoints m_flags;
    rigid_body_internal_type* m_rigidBody;

  };

};};};

#endif