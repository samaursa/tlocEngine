#include "tlocArcBall.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocArcBall.h>

#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_sptr::MakeShared;

  void
    ArcBall::
    Add(entity_ptr a_ent)
  {
    TLOC_ASSERT_NOT_NULL(a_ent);

    using gfx_cs::components::arcball;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // arcball component

    typedef ComponentPoolManager        pool_mgr;
    typedef gfx_cs::arcball_pool        ab_pool;

    gfx_cs::arcball_pool_vptr arcPool 
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::ArcBall>();

    ab_pool::iterator itrArcBall = arcPool->GetNext();
    (*itrArcBall)->SetValue(MakeShared<gfx_cs::ArcBall>(m_focusPoint) );

    m_entMgr->InsertComponent(a_ent, *(*itrArcBall)->GetValuePtr());
  }

};};};