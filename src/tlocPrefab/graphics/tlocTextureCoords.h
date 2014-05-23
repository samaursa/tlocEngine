#ifndef _TLOC_PREFAB_GRAPHICS_TEXTURE_COORDS_H_
#define _TLOC_PREFAB_GRAPHICS_TEXTURE_COORDS_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocTextureCoords.h>

#include <tlocMath/types/tlocVector2.h>

namespace tloc { namespace prefab { namespace graphics {

  class TextureCoords
    : public Prefab_TI<TextureCoords, gfx_cs::TextureCoords>
  {
  public:
    typedef TextureCoords                               this_type;
    typedef Prefab_TI<this_type, component_type>        base_type;

    typedef math_t::Vec2f32                             vec_type;
    typedef tl_size                                     size_type;

    typedef core_t::StrongType_T<size_type, 0>          set_index;

  public:
    struct Coords
    {
      Coords();
      Coords(vec_type a_tcoord, size_type a_setIndex);

      vec_type  m_tcoord;
      size_type m_setIndex;
    };

  public:
    typedef core_conts::Array<Coords>                   coords_cont;

  public:
    TextureCoords(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr       Construct() const;

    entity_ptr          Create() const;
    void                Add(entity_ptr a_ent) const;

    this_type&          AddCoord(vec_type a_coord,
                                 set_index a_setIndex = set_index(0));

    TLOC_DECL_PARAM_VAR(coords_cont, TexCoords, m_coords);
  };

};};};

#endif