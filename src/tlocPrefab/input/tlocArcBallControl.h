#ifndef _TLOC_PREFAB_INPUT_ARC_BALL_CONTROL_H_
#define _TLOC_PREFAB_INPUT_ARC_BALL_CONTROL_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocVector2.h>

#include <tlocInput/component_system/tlocArcballControl.h>

namespace tloc { namespace prefab { namespace input {

  class ArcBallControl
    : public Prefab_TI<ArcBallControl, input_cs::ArcBallControl>
  {
  public:
    typedef ArcBallControl                              this_type;
    typedef Prefab_TI<this_type, component_type>        base_type;
    typedef math_t::Vec2f32                             vec_type;
    typedef vec_type::value_type                        real_type;

  public:
    ArcBallControl(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct();

    entity_ptr    Create();
    void          Add(entity_ptr a_ent);

    TLOC_DECL_PARAM_VAR(vec_type,   GlobalMultiplier, m_globalMulti);
    TLOC_DECL_PARAM_VAR(vec_type,   RotationMultiplier, m_rotMulti);
    TLOC_DECL_PARAM_VAR(vec_type,   PanMultiplier, m_panMulti);
    TLOC_DECL_PARAM_VAR(real_type,  DollyMultiplier, m_dollyMulti);
  };

};};};

#endif