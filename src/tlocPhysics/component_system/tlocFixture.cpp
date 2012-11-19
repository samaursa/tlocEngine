#include "tlocFixture.h"

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace box2d { namespace component_system {

  Fixture::Fixture(const fixture_def_type& a_box2dFixtureDef)
    : base_type(components::k_fixture)
    , m_box2dFixtureDef(a_box2dFixtureDef)
    , m_box2dFixture(NULL)
  {
  }

  void Fixture::SetBox2dFixture(fixture_type* a_box2dFixture)
  {
    TLOC_ASSERT(a_box2dFixture != NULL,
                "Internal fixture cannot be set to null! \
                Use SetBox2dFixtureToNull");

    m_box2dFixture = a_box2dFixture;
  }

  void Fixture::SetBox2dFixtureToNull()
  {
    m_box2dFixture = NULL;
  }

};};};};