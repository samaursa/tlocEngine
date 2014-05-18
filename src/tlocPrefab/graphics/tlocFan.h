#ifndef _TLOC_PREFAB_GRAPHICS_FAN_H_
#define _TLOC_PREFAB_GRAPHICS_FAN_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocFan.h>

#include <tlocMath/types/tlocCircle.h>

namespace tloc { namespace prefab { namespace graphics {

  class Fan
    : public Prefab_TI<gfx_cs::Fan>
  {
  public:
    typedef Prefab_TI<component_type>                     base_type;
    typedef Fan                                           this_type;
    typedef math_t::Circlef32                             circle_type;

  public:
    Fan(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct() const;

    entity_ptr    Create() const;
    void          Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(circle_type, Circle, m_circle);
    TLOC_DECL_PARAM_VAR(tl_size, Sides, m_numSides);
    TLOC_DECL_PARAM_VAR(bool, TexCoords, m_texCoords);

  };

};};};

#endif