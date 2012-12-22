#include "tlocWorld.h"

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Free definitions

  namespace {

    typedef f32 float_type;

  }

  World::
    World(gravity a_gravity)
    : m_world
    (b2Vec2( static_cast<float_type>(((gravity::const_sel_return_type)a_gravity)[0]),
             static_cast<float_type>(((gravity::const_sel_return_type)a_gravity)[1])) )
  {
  }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiation

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::physics::box2d::World::vec_type);