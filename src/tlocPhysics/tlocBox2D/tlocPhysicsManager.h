#ifndef _TLOC_PHYSICS_BOX2D_PHYSICS_MANAGER_
#define _TLOC_PHYSICS_BOX2D_PHYSICS_MANAGER_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace math {

  template <typename T>
  class Vector2;
  typedef Vector2<tl_float> Vec2f;

};};

namespace tloc { namespace physics { namespace box2d {
  
  class World;

  class PhysicsManager
  {
  public:
    PhysicsManager();
    ~PhysicsManager();

    void Initialize(const math::Vec2f& a_gravity, 
                    s32 a_velocityIterations = 8.0f, 
                    s32 a_positionIterations = 3.0f);

    void Update(tl_float a_timeStep);

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(World, GetWorld, *m_world);

    TLOC_DECL_AND_DEF_GETTER(s32, GetVelocityIterations, m_velocityIterations);
    TLOC_DECL_AND_DEF_GETTER(s32, GetPositionIterations, m_positionIterations);

    TLOC_DECL_AND_DEF_SETTER(s32, SetVelocityIterations, m_velocityIterations);
    TLOC_DECL_AND_DEF_SETTER(s32, SetPositionIterations, m_positionIterations);

  private:
    World* m_world;
    s32 m_velocityIterations;
    s32 m_positionIterations;
  };

};};};

#endif