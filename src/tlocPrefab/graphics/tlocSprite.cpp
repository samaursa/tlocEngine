#include "tlocSprite.h"

#include <tlocGraphics/component_system/tlocTextureAnimator.h>

namespace tloc { namespace prefab { namespace graphics {

  namespace priv {

    using namespace gfx_med;
    using namespace p_sprite_loader::parser;

    template <typename T_ParserType>
    void
      DoAddSpriteAnimation(core_cs::Entity* a_entity,
                           core_cs::EntityManager& a_mgr,
                           core_cs::ComponentPoolManager& a_poolMgr,
                           typename gfx_med::SpriteLoader_T <T_ParserType>::
                           const_iterator a_begin,
                           typename gfx_med::SpriteLoader_T <T_ParserType>::
                           const_iterator a_end)
    {
      TLOC_ASSERT_NOT_NULL(a_entity);

      using namespace gfx_cs;
      using namespace gfx_cs::components;

      typedef gfx_cs::texture_animator_sptr_pool      ta_pool;
      gfx_cs::texture_animator_sptr_pool_sptr         taPool;

      if (a_poolMgr.Exists(texture_animator) == false)
      { taPool = a_poolMgr.CreateNewPool<texture_animator_sptr>(); }
      else
      { taPool = a_poolMgr.GetPool<texture_animator_sptr>(); }

      ta_pool::iterator itrTa = taPool->GetNext();
      itrTa->SetValue(texture_animator_sptr(new TextureAnimator()) );

      texture_animator_sptr taPtr = itrTa->GetValue();

      while (a_begin != a_end)
      {
        SpriteInfo si = *a_begin;

        TextureCoords tcoord;
        tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordStart) );
        tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordEnd[0],
                                                si.m_texCoordStart[1]) );
        tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordEnd) );
        tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordStart[0],
                                                si.m_texCoordEnd[1]) );
        ++a_begin;
      }

      a_mgr.InsertComponent(a_entity, taPtr.get() );
    }

    template void
      DoAddSpriteAnimation<SpriteSheetPacker>
      (core_cs::Entity* a_entity,
       core_cs::EntityManager&,
       core_cs::ComponentPoolManager&,
       SpriteLoader_T<SpriteSheetPacker>::const_iterator,
       SpriteLoader_T<SpriteSheetPacker>::const_iterator);

  };

};};};