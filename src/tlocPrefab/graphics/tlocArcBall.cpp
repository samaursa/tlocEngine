#include "tlocArcBall.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocGraphics/component_system/tlocArcBall.h>

namespace tloc { namespace prefab { namespace graphics {

  void
    AddArcBall(core_cs::Entity* a_ent,
               core_cs::EntityManager& a_mgr,
               core_cs::ComponentPoolManager& a_poolMgr,
               const math_t::Vec3f32 a_focusPoint)
  {
    TLOC_ASSERT_NOT_NULL(a_ent);

    using gfx_cs::components::arcball;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager        pool_mgr;
    typedef gfx_cs::arcball_sptr_pool   ab_pool;

    gfx_cs::arcball_sptr_pool_sptr      arcPool;

    if (a_poolMgr.Exists(arcball) == false)
    {
      arcPool = a_poolMgr.CreateNewPool<arcball_sptr>();
    }
    else
    {
      arcPool = a_poolMgr.GetPool<arcball_sptr>();
    }

    ab_pool::iterator itrArcBall = arcPool->GetNext();
    itrArcBall->SetValue(arcball_sptr(new ArcBall(a_focusPoint)) );

    a_mgr.InsertComponent(a_ent, itrArcBall->GetValue().get());
  }

};};};