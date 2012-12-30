#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_DEF_H_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_DEF_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocMath/vector/tlocVector2.h>

struct b2BodyDef;

namespace tloc { namespace physics { namespace component_system {

  class RigidBodySystem;

};};};

namespace tloc { namespace physics { namespace box2d {

  namespace p_rigid_body
  {
    typedef u32   value_type;
    struct StaticBody     { static const value_type s_rigidBodyType; };
    struct KinematicBody  { static const value_type s_rigidBodyType; };
    struct DynamicBody    { static const value_type s_rigidBodyType; };
  };

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyDef is used in conjunction with RigidBody and RigidBody
  /// component. Used to define "invisible" attributes of the RigidBody before
  /// construction.
  ///-------------------------------------------------------------------------
  class RigidBodyDef
  {
  public:
    friend class component_system::RigidBodySystem;

  public:
    typedef RigidBodyDef  this_type;

    typedef b2BodyDef                         rigid_body_def_internal_type;

    typedef core::smart_ptr::SharedPtr<rigid_body_def_internal_type>
                                              rigid_body_def_internal_type_ptr;

    typedef p_rigid_body::value_type  rigid_body_type_type;
    typedef math::Vec2f               vec_type;
    typedef tl_float                  float_type;

  public:
    RigidBodyDef();
    ~RigidBodyDef();

    rigid_body_type_type GetType() const;

    vec_type   GetPosition() const;
    float_type GetAngle() const;

    vec_type   GetLinearVelocity() const;
    float_type GetAngularVelocity() const;

    float_type GetLinearDamping() const;
    float_type GetAngularDamping() const;

    bool IsBullet() const;

    bool IsSleepingAllowed() const;
    bool IsAwake() const;
    bool IsActive() const;

    bool IsFixedrotation() const;

    float_type GetGravityScale() const;

  public:
    template <typename T_RigidBodyType>
    void SetType()
    {
      type_traits::AssertTypeIsSupported
        < T_RigidBodyType,
        p_rigid_body::StaticBody,
        p_rigid_body::KinematicBody,
        p_rigid_body::DynamicBody>();
      DoSetType<T_RigidBodyType>();
    }

    void SetPosition(vec_type a_position);
    void SetAngle(float_type a_angle);

    void SetLinearVelocity(vec_type a_linearVelocity);
    void SetAngularVelocity(float_type a_angularVelocity);

    void SetLinearDamping(float_type a_linearDamping);
    void SetAngularDamping(float_type a_angularDamping);

    void SetBullet(bool a_bullet);

    void SetAllowsSleep(bool a_allowSleep);
    void SetAwake(bool a_awake);
    void SetActive(bool a_active);

    void SetFixedRotation(bool a_fixedRotation);

    void SetGravityScale(float_type a_gravityScale);

  protected:
    const rigid_body_def_internal_type& DoGetRigidBodyDef() const;

  private:
    template <typename T_RigidBodyType>
    void DoSetType();

  private:
    rigid_body_def_internal_type_ptr m_rigidBodyDef;
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef core::smart_ptr::SharedPtr<RigidBodyDef> rigid_body_def_sptr;

};};};

#endif