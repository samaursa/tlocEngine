#ifndef _TLOC_PREFAB_GRAPHICS_QUAD_H_
#define _TLOC_PREFAB_GRAPHICS_QUAD_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace prefab { namespace graphics {

  class Quad
    : public Prefab_I
  {
  public:
    typedef Quad                  this_type;
    typedef math_t::Rectf32       rect_type;

  public:
    Quad(core_cs::EntityManager*  a_entMgr,
         core_cs::ComponentPoolManager* a_poolMgr)
         : Prefab_I(a_entMgr, a_poolMgr)
         , m_texCoords(true)
         , m_rect(rect_type(rect_type::width(1.0f),
                            rect_type::height(1.0f)) )
    { }

    entity_type* Create();
    void         Add(entity_type* a_ent);


    TLOC_DECL_PARAM_VAR(bool, TexCoords, m_texCoords);
    TLOC_DECL_PARAM_VAR(rect_type, Dimensions, m_rect);
  };

};};};

#endif