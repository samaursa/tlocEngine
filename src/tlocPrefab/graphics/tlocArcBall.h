#ifndef _TLOC_PREFAB_GRAPHICS_ARC_BALL_H_
#define _TLOC_PREFAB_GRAPHICS_ARC_BALL_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace prefab { namespace graphics {

  class ArcBall
    : public Prefab_I
  {
  public:
    typedef ArcBall                                     this_type;
    typedef math_t::Vec3f32                             vec_type;

  public:
    ArcBall(core_cs::EntityManager*  a_entMgr,
            core_cs::ComponentPoolManager* a_poolMgr)
            : Prefab_I(a_entMgr, a_poolMgr)
            , m_focusPoint(vec_type::ZERO)
    { }

    void Add(entity_type* a_ent);

    TLOC_DECL_PARAM_VAR(vec_type, Focus, m_focusPoint);
  };

};};};

#endif