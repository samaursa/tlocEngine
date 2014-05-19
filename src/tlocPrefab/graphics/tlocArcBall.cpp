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

  // ///////////////////////////////////////////////////////////////////////
  // ArcBall

  ArcBall::
    ArcBall(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_focusPoint(vec_type::ZERO)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBall::component_ptr
    ArcBall::
    Construct()
  {
    using namespace core_cs;

    typedef ComponentPoolManager        pool_mgr;
    typedef gfx_cs::arcball_pool        ab_pool;

    gfx_cs::arcball_pool_vptr arcPool 
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::ArcBall>();

    ab_pool::iterator itrArcBall = arcPool->GetNext();
    (*itrArcBall)->SetValue(MakeShared<gfx_cs::ArcBall>(m_focusPoint) );

    return *(*itrArcBall)->GetValuePtr();
  }

  ArcBall::entity_ptr
    ArcBall::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBall::
    Add(entity_ptr a_ent)
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // arcball component

    m_entMgr->InsertComponent(a_ent, Construct());
  }

};};};