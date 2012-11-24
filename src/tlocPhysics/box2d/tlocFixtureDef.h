#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_FIXTURE_DEF_H_
#define _TLOC_PHYSICS_BOX2D_FIXTURE_DEF_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <Box2D/Dynamics/b2Fixture.h>

namespace tloc { namespace physics { namespace box2d {

  class FixtureDef
  {
  public:
    friend class Fixture;

  public:
    typedef FixtureDef    this_type;
    typedef b2FixtureDef  fixture_def_value_type;

    typedef f32 float_type;

  public:
    FixtureDef()
    {
      SetFriction(0.2f);
      SetRestitution(0.0f);
      SetDensity(0.0f);
      SetSensor(false);
    }

    //TODO: Get Shape
    TLOC_DECL_AND_DEF_GETTER(float_type, GetFriction, m_fixtureDef.friction);
    TLOC_DECL_AND_DEF_GETTER(float_type, GetRestitution, m_fixtureDef.restitution);
    TLOC_DECL_AND_DEF_GETTER(float_type, GetDensity, m_fixtureDef.density);
    TLOC_DECL_AND_DEF_GETTER(bool, IsSensor, m_fixtureDef.isSensor);
    //TODO: Get collision filter

  public:
    //TODO: Set Shape
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
  };

};};};

#endif