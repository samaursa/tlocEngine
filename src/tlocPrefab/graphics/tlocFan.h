#ifndef _TLOC_PREFAB_GRAPHICS_FAN_H_
#define _TLOC_PREFAB_GRAPHICS_FAN_H_

#include <tlocPrefab/tlocPrefabBase.h>
#include <tlocPrefab/graphics/tlocMesh.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocFan.h>

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/types/tlocAngle.h>

namespace tloc { namespace prefab { namespace graphics {

  template <bool T_TexCoords = true>
  class Fan_T
    : public Prefab_TI<Fan_T<T_TexCoords>, gfx_cs::Mesh>
  {
  public:
    typedef Fan_T<T_TexCoords>                          this_type;
    typedef Prefab_TI<this_type, gfx_cs::Mesh>          base_type;
    typedef math_t::Circlef32                           circle_type;
    typedef core_conts::Array<math_t::Vec2f32>          vec2_cont;

    typedef typename base_type::component_ptr           component_ptr;
    typedef typename base_type::insert_params           insert_params;
    typedef typename base_type::entity_mgr_ptr          entity_mgr_ptr;
    typedef typename base_type::comp_pool_mgr_ptr       comp_pool_mgr_ptr;
    typedef typename base_type::entity_ptr              entity_ptr;

    typedef gfx_t::f_vertex::p_vertex_selector::
            TexCoords<T_TexCoords>                      texcoords_selected;

    using base_type::GetListeners;

  public:
    Fan_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct() const;

    entity_ptr    Create() const;
    void          Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(circle_type, Circle, m_circle);
    TLOC_DECL_PARAM_VAR(tl_size, Sides, m_numSides);
    TLOC_DECL_PARAM_VAR(math_t::Degree, SectorAngle, m_sectorAngle);
    TLOC_DECL_PARAM_VAR(bool, Sprite, m_sprite);

  private:
    vec2_cont DoGenerateTexCoords() const;

  private:
    using base_type::m_entMgr;
    using base_type::m_compPoolMgr;

    pref_gfx::Mesh    m_meshPref;
  };

  typedef Fan_T<>                                         Fan;
  typedef Fan_T<false>                                    FanNoTexCoords;

};};};

#endif