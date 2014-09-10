#include "tlocArcBallControl.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocInput/component_system/tlocComponentType.h>
#include <tlocInput/component_system/tlocArcBallControl.h>

#include <tlocPrefab/math/tlocTransform.h>
#include <tlocPrefab/graphics/tlocArcBall.h>

namespace tloc { namespace prefab { namespace input {

  using core_sptr::MakeShared;

  // ///////////////////////////////////////////////////////////////////////
  // ArcBall

  ArcBallControl::
    ArcBallControl(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_globalMulti(1)
    , m_rotMulti(1)
    , m_panMulti(1)
    , m_dollyMulti(1)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControl::component_ptr
    ArcBallControl::
    Construct()
  {
    using namespace core_cs;

    typedef ComponentPoolManager              pool_mgr;
    typedef input_cs::arc_ball_control_pool   ab_pool;

    input_cs::arc_ball_control_pool_vptr arcPool 
      = m_compPoolMgr->GetOrCreatePool<input_cs::ArcBallControl>();

    input_cs::ArcBallControl abc;
    abc.SetGlobalMultiplier(m_globalMulti)
       .SetRotationMultiplier(m_rotMulti)
       .SetPanMultiplier(m_panMulti)
       .SetDollyMultiplier(m_dollyMulti);

    ab_pool::iterator itrArcBall = arcPool->GetNext();
    (*itrArcBall)->SetValue(MakeShared<input_cs::ArcBallControl>(abc));

    return *(*itrArcBall)->GetValuePtr();
  }

  ArcBallControl::entity_ptr
    ArcBallControl::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallControl::
    Add(entity_ptr a_ent)
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // arcball component

    if (a_ent->HasComponent<gfx_cs::ArcBall>() == false)
    { pref_gfx::ArcBall(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // arcballcontrol component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()) );
  }

};};};