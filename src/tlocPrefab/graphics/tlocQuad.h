#ifndef _TLOC_PREFAB_GRAPHICS_QUAD_H_
#define _TLOC_PREFAB_GRAPHICS_QUAD_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMesh.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace prefab { namespace graphics {

  template <bool T_TexCoords = true>
  class Quad_T
    : public Prefab_TI<Quad_T<T_TexCoords>, gfx_cs::Mesh>
  {
  public:
    typedef Quad_T<T_TexCoords>                     this_type;
    typedef Prefab_TI<this_type, component_type>    base_type;
    typedef math_t::Rectf32_c                       rect_type;
    typedef core_conts::Array<math_t::Vec2f32>      vec2_cont;
    typedef gfx_rend::mode::value_type              draw_mode;

    typedef gfx_t::f_vertex::p_vertex_selector::
            TexCoords<T_TexCoords>                      texcoords_selected;

  public:
    Quad_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct() const;

    entity_ptr    Create() const;
    void          Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(rect_type, Dimensions, m_rect);
    TLOC_DECL_PARAM_VAR(bool, Sprite, m_sprite);
    TLOC_DECL_PARAM_VAR(draw_mode, DrawMode, m_drawMode);
    TLOC_DECL_PARAM_VAR(bool, BoundingBox, m_boundingBox);

  private:
    vec2_cont DoGenerateTexCoords() const;
  };

  typedef Quad_T<>                                  Quad;
  typedef Quad_T<false>                             QuadNoTexCoords;

};};};

#endif