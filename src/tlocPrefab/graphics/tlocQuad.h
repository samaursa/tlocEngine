#ifndef _TLOC_PREFAB_GRAPHICS_QUAD_H_
#define _TLOC_PREFAB_GRAPHICS_QUAD_H_

#include <tlocPrefab/tlocPrefabBase.h>
#include <tlocPrefab/graphics/tlocMesh.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocQuad.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace prefab { namespace graphics {

  template <bool T_TextureCoords = true>
  class Quad_T
    : public Prefab_TI<Quad_T<T_TextureCoords>, gfx_cs::Quad>
  {
  public:
    typedef Quad_T<T_TextureCoords>                 this_type;
    typedef Prefab_TI<this_type, component_type>    base_type;
    typedef math_t::Rectf32_c                       rect_type;

  public:
    Quad(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct() const;

    entity_ptr    Create() const;
    void          Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(rect_type, Dimensions, m_rect);

  private:
    pref_gfx::Mesh    m_meshPref;
  };

};};};

#endif