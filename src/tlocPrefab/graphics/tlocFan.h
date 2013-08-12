#ifndef _TLOC_PREFAB_GRAPHICS_FAN_H_
#define _TLOC_PREFAB_GRAPHICS_FAN_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocMath/types/tlocCircle.h>

namespace tloc { namespace prefab { namespace graphics {

  class Fan
    : public Prefab_I
  {
  public:
    typedef Fan                                           this_type;
    typedef math_t::Circlef32                             circle_type;

  public:
    Fan(core_cs::EntityManager*  a_entMgr,
        core_cs::ComponentPoolManager* a_poolMgr)
        : Prefab_I(a_entMgr, a_poolMgr)
        , m_circle(circle_type(circle_type::radius(1.0f)) )
        , m_numSides(8)
        , m_texCoords(true)
    { }

    entity_type*  Create();
    void          Add(entity_type* a_ent);

    TLOC_DECL_PARAM_VAR(circle_type, Circle, m_circle);
    TLOC_DECL_PARAM_VAR(tl_size, Sides, m_numSides);
    TLOC_DECL_PARAM_VAR(bool, TexCoords, m_texCoords);

  };

};};};

#endif