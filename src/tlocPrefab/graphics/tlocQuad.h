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

  template <bool T_TexCoords = true>
  class Quad_T
    : public Prefab_TI<Quad_T<T_TexCoords>, gfx_cs::Mesh>
  {
  public:
    typedef Quad_T<T_TexCoords>                     this_type;
    typedef Prefab_TI<this_type, gfx_cs::Mesh>      base_type;

    typedef typename base_type::component_ptr       component_ptr;
    typedef typename base_type::insert_params       insert_params;
    typedef typename base_type::entity_mgr_ptr      entity_mgr_ptr;
    typedef typename base_type::comp_pool_mgr_ptr   comp_pool_mgr_ptr;
    typedef typename base_type::entity_ptr          entity_ptr;

    typedef math_t::Rectf32_c                       rect_type;
    typedef core_conts::Array<math_t::Vec2f32>      vec2_cont;

    typedef gfx_t::f_vertex::p_vertex_selector::
            TexCoords<T_TexCoords>                      texcoords_selected;

    using base_type::GetListeners;

  public:
    Quad_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct() const;

    entity_ptr    Create() const;
    void          Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(rect_type, Dimensions, m_rect);
    TLOC_DECL_PARAM_VAR(bool, Sprite, m_sprite);

  private:
    vec2_cont DoGenerateTexCoords() const;

  private:
    using base_type::m_entMgr;
    using base_type::m_compPoolMgr;

    pref_gfx::Mesh    m_meshPref;
  };

  typedef Quad_T<>                                  Quad;
  typedef Quad_T<false>                             QuadNoTexCoords;

};};};

#endif