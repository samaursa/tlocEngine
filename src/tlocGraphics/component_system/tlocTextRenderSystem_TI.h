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

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/types/tlocRectangle.h>

#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocRenderSystem.h>
#include <tlocGraphics/component_system/tlocMeshRenderSystem.h>
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

    typedef core_str::String                                  string_type;
    typedef math_t::Mat2f32                                   scale_type;
    typedef tl_float                                          real_type;
    typedef core::Pair<real_type, real_type>                  real_pair;

  public:
    struct CharacterInfo
    {
      typedef CharacterInfo     this_type;

      TLOC_DECL_PARAM_VAR(math_cs::transform_sptr, Transformation, m_trans);
      TLOC_DECL_PARAM_VAR(math_t::Rectf_bl, Rectangle, m_rect);
      TLOC_DECL_PARAM_VAR(tl_ulong, Character, m_char);
    };

  public:
    typedef core_conts::Array<CharacterInfo>                  glyph_info_cont;
    typedef typename glyph_info_cont::iterator                glyph_info_itr;
    typedef typename glyph_info_cont::const_iterator          const_glyph_info_itr;
    typedef core::Pair<const_entity_ptr, glyph_info_cont>     text_quads_pair;
    typedef core_conts::Array<text_quads_pair>                text_quads_cont;
    typedef typename text_quads_cont::iterator                text_quads_iterator;

  public:

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();

    void               MarkForReinit(const entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    TLOC_DECL_AND_DEF_GETTER_NON_CONST(gfx_cs::mesh_render_system_vptr, 
                             GetMeshRenderSystem, m_textMeshRenderSys.get());

    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingByMaterial);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingFrontToBack);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingBackToFront);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingFrontToBack_2D);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingBackToFront_2D);

  protected:
    TextRenderSystem_TI(event_manager_ptr a_eventMgr,
                        entity_manager_ptr a_entityMgr,
                        BufferArg a_debugName);
    
    ~TextRenderSystem_TI();

    real_pair    DoAlignLine(const_glyph_info_itr a_begin, 
                             const_glyph_info_itr a_end,
                             tl_int a_beginIndex,
                             text_ptr a_text,
                             size_type a_lineNumber);
    void         DoAlignText(const text_quads_pair& a_pair);

  private:
    error_type   DoReInitializeEntity(entity_ptr a_ent);
    void         DoRemoveText(const const_entity_ptr a_ent);

  protected:
    text_quads_cont                     m_allText;
    core_cs::entity_ptr_array           m_entsToReinit;

    core_cs::component_pool_mgr_vso       m_textCompMgr;
    core_cs::event_manager_vso            m_textEventMgr;
    core_cs::entity_manager_vso           m_textEntityMgr;
    gfx_cs::scene_graph_system_vso        m_textSceneGraphSys;
    gfx_cs::mesh_render_system_vso        m_textMeshRenderSys;
    gfx_cs::texture_animation_system_vso  m_textAnimSys;
  };

  // -----------------------------------------------------------------------
  // extern template

  class StaticText; class DynamicText;
  TLOC_EXTERN_TEMPLATE_CLASS(TextRenderSystem_TI<StaticText>);
  TLOC_EXTERN_TEMPLATE_CLASS(TextRenderSystem_TI<DynamicText>);

};};};

#endif