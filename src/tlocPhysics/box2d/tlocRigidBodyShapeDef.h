#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_SHAPE_H_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/types/tlocCircle.h>

#include <Box2D/Dynamics/b2Fixture.h>

class b2Shape;

namespace tloc { namespace physics { namespace box2d {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyShapeDef is used in conjunction with RigidBodyShape
  /// component. Used to define "visible" physical attributes of the RigidBody.
  ///-------------------------------------------------------------------------
  class RigidBodyShapeDef
  {
  public:
    friend class RigidBody;

  public:
    typedef RigidBodyShapeDef   this_type;
    typedef f32                 float_type;

    typedef math::types::Rectangle<float_type>  rect_type;
    typedef math::types::Circle<float_type>     circle_type;

  public:

    template <typename T_Shape>
    RigidBodyShapeDef(const T_Shape& a_shape)
    {
      type_traits::AssertTypeIsSupported
        < T_Shape,
        rect_type,
        circle_type>();
      DoSetShape(a_shape);

      SetFriction(0.2f);
      SetRestitution(0.0f);
      SetDensity(1.0f);
      SetSensor(false);
    }

    TLOC_DECL_AND_DEF_GETTER(float_type, GetFriction, m_fixtureDef.friction);
    TLOC_DECL_AND_DEF_GETTER(float_type, GetRestitution, m_fixtureDef.restitution);
    TLOC_DECL_AND_DEF_GETTER(float_type, GetDensity, m_fixtureDef.density);
    TLOC_DECL_AND_DEF_GETTER(bool, IsSensor, m_fixtureDef.isSensor);
    //TODO: Get collision filter

    TLOC_DECL_AND_DEF_SETTER(float_type, SetFriction, m_fixtureDef.friction);
    TLOC_DECL_AND_DEF_SETTER(float_type, SetRestitution, m_fixtureDef.restitution);
    TLOC_DECL_AND_DEF_SETTER(float_type, SetDensity, m_fixtureDef.density);
    TLOC_DECL_AND_DEF_SETTER(bool, SetSensor, m_fixtureDef.isSensor);
    //TODO: Set collision filter

  protected:
    typedef b2FixtureDef                      fixture_def_internal_type;
    typedef core::component_system::Entity    entity_type;

    void DoSetShape(const rect_type& a_rect);
    void DoSetShape(const circle_type& a_circle);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (fixture_def_internal_type, DoGetFixtureDef, m_fixtureDef);

    TLOC_DECL_AND_DEF_SETTER
      (entity_type*, DoSetParent, m_fixtureDef.userData);

  private:
    typedef b2Shape                                     shape_internal_type;
    typedef core::smart_ptr::SharedPtr<shape_internal_type>
                                                        shape_internal_type_sptr;

    shape_internal_type_sptr    m_internalShape;
    fixture_def_internal_type   m_fixtureDef;
  };

};};};

#endif