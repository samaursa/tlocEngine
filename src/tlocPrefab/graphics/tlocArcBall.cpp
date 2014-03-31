#include "tlocArcBall.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocComponentType.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocArcBall.h>

namespace tloc { namespace prefab { namespace graphics {

  void
    ArcBall::
    Add(entity_ptr a_ent)
  {
    TLOC_ASSERT_NOT_NULL(a_ent);

    using gfx_cs::components::arcball;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager        pool_mgr;
    typedef gfx_cs::arcball_pool        ab_pool;

    gfx_cs::arcball_pool_vptr           arcPool;

    if (m_compPoolMgr->Exists(arcball) == false)
    {
      arcPool = m_compPoolMgr->CreateNewPool<gfx_cs::ArcBall>();
    }
    else
    {
      arcPool = m_compPoolMgr->GetPool<gfx_cs::ArcBall>();
    }

    ab_pool::iterator itrArcBall = arcPool->GetNext();
    (*itrArcBall)->SetValue(gfx_cs::ArcBall(m_focusPoint) );

    m_entMgr->InsertComponent(a_ent, (*itrArcBall)->GetValue());
  }

};};};