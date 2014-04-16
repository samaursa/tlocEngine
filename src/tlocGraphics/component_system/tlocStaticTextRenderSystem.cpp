#include "tlocStaticTextRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocStaticText.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/media/tlocFont.h>

#include <tlocPrefab/graphics/tlocQuad.h>
#include <tlocPrefab/graphics/tlocMaterial.h>
#include <tlocPrefab/graphics/tlocSprite.h>
#include <tlocPrefab/graphics/tlocSceneNode.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core_ds;

  namespace {

    const core_str::StringW
      g_symbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  L"abcdefghijklmnopqrstuvwxyz" 
                  L"1234567890!@#$%^&*()_+-=[]" 
                  L"{}\\|;:'\",<.>/?`~";
  };

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef StaticTextRenderSystem::error_type    error_type;

  // ///////////////////////////////////////////////////////////////////////
  // StaticTextRenderSystem

  StaticTextRenderSystem::
    StaticTextRenderSystem(event_manager_ptr a_eventMgr, 
                           entity_manager_ptr a_entityMgr,
                           const font_ptr& a_initializedFont,
                           scale_type a_globalScale)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::static_text))

    , m_font(a_initializedFont)
    , m_globalScale(a_globalScale)

    , m_vertexShader("Invalid Path")
    , m_fragmentShader("Invalid Path")

    , m_fontEntityMgr(m_fontEventMgr.get())
    , m_fontQuadRenderSys(m_fontEventMgr.get(), m_fontEntityMgr.get())
    , m_fontSceneGraphSys(m_fontEventMgr.get(), m_fontEntityMgr.get())
    , m_fontMaterialSys(m_fontEventMgr.get(), m_fontEntityMgr.get())
    , m_fontAnimSys(m_fontEventMgr.get(), m_fontEntityMgr.get())
  {
    TLOC_ASSERT(m_font->IsInitialized(), 
                "Font must already be initialized - Font::Initialize()");
    TLOC_ASSERT(m_font->IsCached(),
                "Font must already be cached - Font::GenerateGlyphCache()");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticTextRenderSystem::
    ~StaticTextRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    DoAlignText(const text_quads_pair& a_pair)
  {
    typedef core_cs::const_entity_ptr_array       ent_cont;

    static_text_vptr staticText = a_pair.first->GetComponent<StaticText>();
    math_cs::transform_f32_vptr staticTextTrans = 
      a_pair.first->GetComponent<math_cs::Transformf32>();

    f32 totalTextWidth = 0;

    {
      core_cs::const_entity_vptr itrFirstChar = a_pair.second.front();
      math_cs::transform_f32_vptr firstCharTrans =
        itrFirstChar->GetComponent<math_cs::Transformf32>();

      core_cs::const_entity_vptr itrSecondChar = a_pair.second.back();
      math_cs::transform_f32_vptr secondCharTrans =
        itrSecondChar->GetComponent<math_cs::Transformf32>();

      gfx_cs::quad_vptr secondQuad =
        itrSecondChar->GetComponent<gfx_cs::Quad>();

      totalTextWidth = secondCharTrans->GetPosition()[0] - 
        firstCharTrans->GetPosition()[0] + 
        secondQuad->GetRectangleRef().GetCoord_BottomRight()[0];
    }

    f32 advance = 0;

    if (staticText->GetAlignment() == StaticText::k_align_center)
    { advance = totalTextWidth * 0.5f * -1.0f; }
    else if (staticText->GetAlignment() == StaticText::k_align_right)
    { advance = totalTextWidth * -1.0f; }

    tl_int count = 0;
    for (ent_cont::const_iterator 
         itr = a_pair.second.begin(), itrEnd = a_pair.second.end(); 
         itr != itrEnd; ++itr)
    {
      if (count != 0)
      {
        advance = 
        DoSetTextQuadPosition(*itr, staticText->Get()[count - 1], 
                              staticText->Get()[count], advance);
      }
      else
      {
        advance = 
        DoSetTextQuadPosition(*itr, staticText->Get()[count], advance);
      }

      math_cs::transform_f32_vptr t =
        (*itr)->GetComponent<math_cs::Transformf32>();

      ++count;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    StaticTextRenderSystem::
    SetShaders(core_io::Path a_vertexShader, core_io::Path a_fragmentShader)
  {
    m_vertexShader = a_vertexShader;
    m_fragmentShader = a_fragmentShader;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    StaticTextRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    TLOC_ASSERT(a_ent->HasComponent<math_cs::Transform>(),
                "Entity must have a transform node");
    TLOC_ASSERT(a_ent->HasComponent<SceneNode>(),
                "The static text entity must have a scene node entity");

    scene_node_vptr sceneNode   = a_ent->GetComponent<SceneNode>();
    static_text_vptr staticText = a_ent->GetComponent<StaticText>();

    // -----------------------------------------------------------------------
    // text quad pair

    text_quads_pair tqp(a_ent);

    // -----------------------------------------------------------------------
    // prepare the shader operator

    gfx_gl::texture_object_vso to;
    gfx_gl::TextureObject::Params toParams;
    to->SetParams(toParams);

    to->Initialize(*m_font->GetSpriteSheetPtr()->GetSpriteSheet());
    to->Activate();

    gfx_gl::uniform_vso u_to;
    u_to->SetName("s_texture").SetValueAs(*to);

    gfx_gl::shader_operator_vso so;
    so->AddUniform(*u_to);

    // -----------------------------------------------------------------------
    // go through all the characters and build the text quads

    core_str::StringW text = staticText->Get();

    gfx_med::GlyphMetrics::value_type advance = 0;

    for (tl_size i = 0; i < text.length(); ++i)
    {
      gfx_med::Font::const_glyph_metrics_iterator 
        itr = m_font->GetGlyphMetric(text[i]);

      TLOC_LOG_GFX_WARN_IF(itr == m_font->end_glyph_metrics())
        << "Glyph metrics not found for (" << text[i] << ")"
        << " - symbol does not exist in the glyph cache";

      // -----------------------------------------------------------------------
      // grab the sprite info

      using gfx_med::algos::compare::sprite_info::MakeName;

      gfx_med::sprite_sheet_ul::const_iterator itrSs, itrEndSs;
      itrSs = core::find_if(m_font->GetSpriteSheetPtr()->begin(),
                            m_font->GetSpriteSheetPtr()->end(),
                            gfx_med::algos::compare::sprite_info::MakeName((tl_ulong)text[i]));

      itrEndSs = itrSs;
      core::advance(itrEndSs, 1);

      // -----------------------------------------------------------------------
      // create the quad

      math_t::Vec2f32 dim = itr->m_dim.Cast<math_t::Vec2f32>();
      dim = m_globalScale * dim;

      using math_t::Rectf32_bl;
      Rectf32_bl rect = 
        Rectf32_bl(Rectf32_bl::width(dim[0]), Rectf32_bl::height(dim[1]));

      entity_ptr q = 
        pref_gfx::Quad(m_fontEntityMgr.get(), m_fontCompMgr.get()).
        TexCoords(true).Dimensions(rect).Create();

      pref_gfx::Material(m_fontEntityMgr.get(), m_fontCompMgr.get())
        .AddUniform(u_to.get())
        .Add(q, m_vertexShader, m_fragmentShader);

      // we need the quad later for other operations
      tqp.second.push_back(q);

      // -----------------------------------------------------------------------
      // make it a node

      pref_gfx::SceneNode(m_fontEntityMgr.get(), m_fontCompMgr.get())
        .Parent(sceneNode).Add(q);

      // -----------------------------------------------------------------------
      // add sprite animation to quad with one texture coordinate only

      pref_gfx::SpriteAnimation(m_fontEntityMgr.get(), m_fontCompMgr.get())
        .Paused(false).Add(q, itrSs, itrEndSs);

      // -----------------------------------------------------------------------
      // set the quad position

      if (i > 0)
      {
        advance = DoSetTextQuadPosition(q, text[i - 1], text[i], advance);
      }
      else
      {
        advance = DoSetTextQuadPosition(q, text[i], advance);
      }
    }

    DoAlignText(tqp);
    m_allText.push_back(tqp);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  f32
    StaticTextRenderSystem::
    DoSetTextQuadPosition(const_entity_ptr a_ent, 
                          gfx_med::Font::glyph_metrics:: char_code a_charCode, 
                          f32 a_startingPosX)
  {
    f32 advanceToRet = a_startingPosX;

    gfx_med::Font::const_glyph_metrics_iterator 
      itr = m_font->GetGlyphMetric(a_charCode);

    // -----------------------------------------------------------------------
    // set the quad position

    math_t::Vec2f32 horBearing =
      itr->m_horizontalBearing.Cast<math_t::Vec2f32>();

    using math_cs::transform_f32_vptr;
    transform_f32_vptr textPos = a_ent->GetComponent<math_cs::Transformf32>();
    math_t::Rectf32_bl rect = a_ent->GetComponent<gfx_cs::Quad>()->GetRectangleRef();

    textPos->SetPosition
      (math_t::Vec3f32(advanceToRet, 0, 0));

    textPos->
      SetPosition(textPos->GetPosition() +
      math_t::Vec3f32(0, 
                      ( horBearing[1] * m_globalScale[3] ) - rect.GetHeight(), 
                      0));

    // advance pen's position
    advanceToRet += itr->m_horizontalAdvance;

    return advanceToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  f32
    StaticTextRenderSystem::
    DoSetTextQuadPosition(const_entity_ptr a_ent, 
                          gfx_med::Font::glyph_metrics:: char_code a_prevCode, 
                          gfx_med::Font::glyph_metrics:: char_code a_charCode, 
                          f32 a_startingPosX)
  {
    f32 advanceToRet = DoSetTextQuadPosition(a_ent, a_charCode, a_startingPosX);

    // -----------------------------------------------------------------------
    // set the quad position

    using math_cs::transform_f32_vptr;
    transform_f32_vptr textPos = a_ent->GetComponent<math_cs::Transformf32>();
    math_t::Rectf32_bl rect = a_ent->GetComponent<gfx_cs::Quad>()->GetRectangleRef();

    // kerning
    {
      math_t::Vec2f32 kerning = m_font->GetKerning(a_prevCode, a_charCode);
      kerning = m_globalScale * kerning;

      advanceToRet += kerning[0];

      math_t::Vec3f32 kerning3 = kerning
        .ConvertTo<math_t::Vec3f32, core_ds::p_tuple::overflow_zero>();

      textPos->SetPosition(textPos->GetPosition() + kerning3);
    }

    return advanceToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    StaticTextRenderSystem::
    Post_Initialize()
  {
    m_fontQuadRenderSys.SetRenderer(GetRenderer());
    m_fontQuadRenderSys.SetCamera(GetCamera());
    
    m_fontQuadRenderSys.Initialize();
    m_fontSceneGraphSys.Initialize();
    m_fontMaterialSys.Initialize();
    m_fontAnimSys.Initialize();

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    StaticTextRenderSystem::
    ShutdownEntity(entity_ptr )
  { 
    return ErrorSuccess;
  }

  void
    StaticTextRenderSystem::
    Pre_ProcessActiveEntities(f64 a_deltaT)
  {
    m_fontSceneGraphSys.ProcessActiveEntities(a_deltaT);
    m_fontAnimSys.ProcessActiveEntities(a_deltaT);
    m_fontQuadRenderSys.ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64 )
  { 
    static_text_vptr staticText = a_ent->GetComponent<StaticText>();

    if (staticText->IsUpdateRequired())
    {
      text_quads_cont::const_iterator itr = core::find_if_all
        (m_allText, core::algos::compare::pair::MakeFirst(const_entity_ptr(a_ent)));

      TLOC_ASSERT(itr != m_allText.end(), 
                  "StaticText should be stored in m_allText container");

      DoAlignText(*itr);

      staticText->SetUpdateRequired(false);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    Post_ProcessActiveEntities(f64 )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

};};};