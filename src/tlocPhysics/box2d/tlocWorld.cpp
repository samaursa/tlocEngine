#include "tlocWorld.h"

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace physics { namespace box2d {

  World::
    World(gravity a_gravity)
    : m_world(b2Vec2( ((gravity::const_sel_return_type)a_gravity)[0],
                      ((gravity::const_sel_return_type)a_gravity)[1]) )
  {
  }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiation

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::physics::box2d::World::vec_type);