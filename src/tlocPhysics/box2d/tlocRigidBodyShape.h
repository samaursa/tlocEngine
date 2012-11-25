#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_RIGID_BODY_SHAPE_H_
#define _TLOC_PHYSICS_BOX2D_RIGID_BODY_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocPhysics/box2d/tlocShape.h>

#include <Box2D/Dynamics/b2Fixture.h>

namespace tloc { namespace physics { namespace box2d {

  class RigidBodyShape
  {
  public:
    friend class RigidBody;

  public:
    typedef RigidBodyShape    this_type;
    typedef b2FixtureDef  fixture_def_value_type;
    typedef Shape         shape_type;

    typedef f32 float_type;

  public:
    RigidBodyShape(const shape_type* a_shape)
    {
      SetShape(a_shape);
      SetFriction(0.2f);
      SetRestitution(0.0f);
      SetDensity(0.0f);
      SetSensor(false);
    }

    void SetShape(const Shape* a_shape)
    {
      m_shape = a_shape;
      m_fixtureDef.shape = m_shape->GetShapeValue();
    }

    TLOC_DECL_AND_DEF_GETTER(shape_type*, GetShape, m_shape);
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
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (fixture_def_value_type, GetFixtureDef, m_fixtureDef);

  private:
    fixture_def_value_type m_fixtureDef;
    const shape_type* m_shape;
  };

};};};

#endif