#include "tlocArcBall.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocGraphics/component_system/tlocArcBall.h>

namespace tloc { namespace prefab { namespace graphics {

  void
    ArcBall::
    Add(core_cs::Entity* a_ent)
  {
    TLOC_ASSERT_NOT_NULL(a_ent);

    using gfx_cs::components::arcball;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager        pool_mgr;
    typedef gfx_cs::arcball_sptr_pool   ab_pool;

    gfx_cs::arcball_sptr_pool_sptr      arcPool;

    if (m_compPoolMgr->Exists(arcball) == false)
    {
      arcPool = m_compPoolMgr->CreateNewPool<arcball_sptr>();
    }
    else
    {
      arcPool = m_compPoolMgr->GetPool<arcball_sptr>();
    }

    ab_pool::iterator itrArcBall = arcPool->GetNext();
    itrArcBall->SetValue(arcball_sptr(new gfx_cs::ArcBall(m_focusPoint)) );

    m_entMgr->InsertComponent(a_ent, itrArcBall->GetValue().get());
  }

};};};