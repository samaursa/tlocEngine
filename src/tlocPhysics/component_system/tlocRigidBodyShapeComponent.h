#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <Box2D/Dynamics/b2Fixture.h>


namespace tloc { namespace physics { namespace component_system {

  class RigidBodyShape : public core::component_system::Component_T<RigidBodyShape>
  {
  public:
    typedef core::component_system::Component_T<RigidBodyShape>  base_type;
    typedef b2FixtureDef                                  rigid_body_shape_type;
    typedef b2Fixture                                     fixture_type;

  public:
    RigidBodyShape(const rigid_body_shape_type& a_box2dFixtureDef);

    TLOC_DECL_AND_DEF_GETTER(rigid_body_shape_type, GetBox2dFixtureDef,
                             m_box2dFixtureDef);
    TLOC_DECL_AND_DEF_GETTER(fixture_type*, GetBox2dFixture,
                             m_box2dFixture);

    void SetBox2dFixture(fixture_type* a_box2dFixture);
    void SetBox2dFixtureToNull();

  private:
    rigid_body_shape_type m_box2dFixtureDef;
    fixture_type* m_box2dFixture;
  };

};};};

#endif