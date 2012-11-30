#ifndef _TLOC_PHYSICS_BOX2D_PHYSICS_MANAGER_
#define _TLOC_PHYSICS_BOX2D_PHYSICS_MANAGER_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tloccore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tloccore/error/tlocError.h>
#include <tloccore/utilities/tlocCheckpoints.h>

#include <tlocMath/vector/tlocVector2.h>

namespace tloc { namespace physics { namespace box2d {
  
  class World;

  class PhysicsManager
  {
  public:
    typedef PhysicsManager      this_type;
    typedef s32                 int_type;
    typedef math::Vec2f         vec_type;
    typedef core::error::Error  error_type;
    typedef World               world_type;

    typedef core::types::StrongType_T<int_type, 0> velocity_iterations;
    typedef core::types::StrongType_T<int_type, 1> position_iterations;

    typedef core::types::StrongType_T<vec_type, 0> gravity;

  public:
    PhysicsManager();

    error_type Initialize(gravity a_gravity, 
                          velocity_iterations a_vel = velocity_iterations(8), 
                          position_iterations a_pos = position_iterations(3));

    error_type Shutdown();

    void Update(tl_float a_timeStep);

    world_type& GetWorld();
    const world_type& GetWorld() const;

    TLOC_DECL_AND_DEF_GETTER(int_type, GetVelocityIterations, 
                             m_velocityIterations);
    TLOC_DECL_AND_DEF_GETTER(int_type, GetPositionIterations, 
                             m_positionIterations);

    TLOC_DECL_AND_DEF_SETTER(int_type, SetVelocityIterations, 
                             m_velocityIterations);
    TLOC_DECL_AND_DEF_SETTER(int_type, SetPositionIterations, 
                             m_positionIterations);

  private:
    core::utils::Checkpoints m_flags;
    world_type* m_world;
    int_type m_velocityIterations;
    int_type m_positionIterations;
  };

};};};

#endif