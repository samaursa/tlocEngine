#ifndef _TLOC_PREFAB_GRAPHICS_ARC_BALL_H_
#define _TLOC_PREFAB_GRAPHICS_ARC_BALL_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocArcBall.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace prefab { namespace graphics {

  class ArcBall
    : public Prefab_TI<gfx_cs::ArcBall>
  {
  public:
    typedef Prefab_TI<component_type>                   base_type;
    typedef ArcBall                                     this_type;
    typedef math_t::Vec3f32                             vec_type;

  public:
    ArcBall(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct();

    entity_ptr    Create();
    void          Add(entity_ptr a_ent);

    TLOC_DECL_PARAM_VAR(vec_type, Focus, m_focusPoint);
  };

};};};

#endif