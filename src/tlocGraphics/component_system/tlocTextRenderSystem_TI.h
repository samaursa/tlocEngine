#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_RENDER_SYSTEM_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_RENDER_SYSTEM_TI_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/media/tlocFont.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocQuadRenderSystem.h>
#include <tlocGraphics/component_system/tlocSceneGraphSystem.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>
#include <tlocGraphics/component_system/tlocTextureAnimatorSystem.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_TextOrStaticTextComponent>
  class TextRenderSystem_TI
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;
    typedef T_TextOrStaticTextComponent                       text_type;
    typedef core_sptr::SharedPtr<text_type>                   text_ptr;
    typedef TextRenderSystem_TI<text_type>                    this_type;

    typedef gfx_med::font_sptr                                font_ptr;
    typedef core_str::String                                  string_type;
    typedef math_t::Mat2f32                                   scale_type;
    typedef tl_float                                          real_type;

  public:
    typedef core::Pair<const_entity_ptr, 
                       core_cs::const_entity_ptr_array>       text_quads_pair;
    typedef core_conts::Array<text_quads_pair>                text_quads_cont;

  public:

    void               SetShaders(core_io::Path a_vertexShader, 
                                  core_io::Path a_fragmentShader);

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();

    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

  protected:
    TextRenderSystem_TI(event_manager_ptr a_eventMgr,
                       entity_manager_ptr a_entityMgr,
                       const font_ptr& a_initializedFont);
    
    ~TextRenderSystem_TI();

    void         DoAlignText(const text_quads_pair& a_pair);
    real_type    DoSetTextQuadPosition(const_entity_ptr a_ent,
                                       gfx_med::Font::glyph_metrics::
                                       char_code a_charCode,
                                       real_type a_startingPosX);

    real_type    DoSetTextQuadPosition(const_entity_ptr a_ent,
                                       gfx_med::Font::glyph_metrics::
                                       char_code a_prevCode,
                                       gfx_med::Font::glyph_metrics::
                                       char_code a_charCode,
                                       real_type a_startingPosX);
  protected:
    font_ptr                            m_font;
    text_quads_cont                     m_allText;

    core_io::Path                       m_vertexShader;
    core_io::Path                       m_fragmentShader;

    core_str::String                    m_vertexShaderContents;
    core_str::String                    m_fragmentShaderContents;

    gfx_cs::material_sptr               m_sharedMat;

    core_cs::component_pool_mgr_vso     m_fontCompMgr;
    core_cs::event_manager_vso          m_fontEventMgr;
    core_cs::entity_manager_vso         m_fontEntityMgr;
    gfx_cs::QuadRenderSystem            m_fontQuadRenderSys;
    gfx_cs::SceneGraphSystem            m_fontSceneGraphSys;
    gfx_cs::MaterialSystem              m_fontMaterialSys;
    gfx_cs::TextureAnimatorSystem       m_fontAnimSys;
  };

};};};

#endif