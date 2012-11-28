#include "tlocRigidBodyShapeComponent.h"

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyShape::RigidBodyShape(const rigid_body_shape_type& a_box2dFixtureDef)
    : base_type(components::k_rigid_body_shape)
    , m_box2dFixtureDef(a_box2dFixtureDef)
    , m_box2dFixture(NULL)
  {
  }

  void RigidBodyShape::SetBox2dFixture(fixture_type* a_box2dFixture)
  {
    TLOC_ASSERT(a_box2dFixture != NULL,
                "Internal fixture cannot be set to null! \
                Use SetBox2dFixtureToNull");

    m_box2dFixture = a_box2dFixture;
  }

  void RigidBodyShape::SetBox2dFixtureToNull()
  {
    m_box2dFixture = NULL;
  }

};};};