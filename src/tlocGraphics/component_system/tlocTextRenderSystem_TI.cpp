#include "tlocTextRenderSystem_TI.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/io/tlocFileIO.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocText_I.h>
#include <tlocGraphics/media/tlocFont.h>

#include <tlocPrefab/graphics/tlocQuad.h>
#include <tlocPrefab/graphics/tlocMaterial.h>
#include <tlocPrefab/graphics/tlocSprite.h>
#include <tlocPrefab/graphics/tlocSceneNode.h>

#include <tlocGraphics/component_system/tlocStaticText.h>
#include <tlocGraphics/component_system/tlocDynamicText.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core_ds;

  namespace {

    const core_str::StringW
      g_symbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  L"abcdefghijklmnopqrstuvwxyz" 
                  L"1234567890!@#$%^&*()_+-=[]" 
                  L"{}\\|;:'\",<.>/?`~";
  };

#define TLOC_TEXT_RENDER_SYSTEM_TEMPS   typename T_TextOrStaticTextComponent
#define TLOC_TEXT_RENDER_SYSTEM_PARAMS  T_TextOrStaticTextComponent
#define TLOC_TEXT_RENDER_SYSTEM_TYPE    typename TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // TextRenderSystem_I

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    TextRenderSystem_TI(event_manager_ptr a_eventMgr, 
                        entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(text_type::k_component_type))

    , m_textEntityMgr( MakeArgs(m_textEventMgr.get()) )
    , m_textQuadRenderSys(m_textEventMgr.get(), m_textEntityMgr.get())
    , m_textSceneGraphSys(m_textEventMgr.get(), m_textEntityMgr.get())
    , m_textAnimSys(m_textEventMgr.get(), m_textEntityMgr.get())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    ~TextRenderSystem_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    DoAlignText(const text_quads_pair& a_pair)
  {
    typedef core_cs::const_entity_ptr_array       ent_cont;

    text_ptr text = a_pair.first->GetComponent<text_type>();

    math_cs::transform_sptr textTrans = 
      a_pair.first->GetComponent<math_cs::Transform>();

    real_type totalTextWidth = 0;

    if (a_pair.second.size() == 0)
    { return; }

    {
      core_cs::const_entity_vptr itrFirstChar = a_pair.second.front();
      math_cs::transform_sptr firstCharTrans =
        itrFirstChar->GetComponent<math_cs::Transform>();

      if (a_pair.second.size() > 1)
      {
        core_cs::const_entity_vptr itrSecondChar = a_pair.second.back();
        math_cs::transform_sptr secondCharTrans =
          itrSecondChar->GetComponent<math_cs::Transform>();

        gfx_cs::quad_sptr secondQuad =
          itrSecondChar->GetComponent<gfx_cs::Quad>();

        totalTextWidth = secondCharTrans->GetPosition()[0] -
          firstCharTrans->GetPosition()[0] +
          secondQuad->GetRectangleRef().GetCoord_BottomRight()[0];
      }
      else
      {
        gfx_cs::quad_sptr firstQuad =
          itrFirstChar->GetComponent<gfx_cs::Quad>();

        totalTextWidth = firstQuad->GetRectangleRef().GetWidth();
      }
    }

    real_type advance = 0;

    if (text->GetAlignment() == alignment::k_align_center)
    { advance = totalTextWidth * 0.5f * -1.0f; }
    else if (text->GetAlignment() == alignment::k_align_right)
    { advance = totalTextWidth * -1.0f; }

    tl_int count = 0;
    for (ent_cont::const_iterator 
         itr = a_pair.second.begin(), itrEnd = a_pair.second.end(); 
         itr != itrEnd; ++itr)
    {
      using core_sptr::ToVirtualPtr;

      math_cs::transform_sptr t = (*itr)->GetComponent<math_cs::Transform>();
      gfx_cs::quad_sptr       q = (*itr)->GetComponent<gfx_cs::Quad>();

      if (count != 0)
      {
        advance = 
          DoSetTextQuadPosition(t, q, ToVirtualPtr(text), 
                                text->Get()[count - 1], 
                                text->Get()[count], advance);
      }
      else
      {
        advance = 
          DoSetTextQuadPosition(t, q, ToVirtualPtr(text), 
                                text->Get()[count], advance);
      }

      ++count;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TLOC_TEXT_RENDER_SYSTEM_TYPE::error_type
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TLOC_TEXT_RENDER_SYSTEM_TYPE::error_type
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent)
  { 
    TLOC_ASSERT(a_ent->HasComponent<math_cs::Transform>(),
                "Entity must have a transform node");
    TLOC_ASSERT(a_ent->HasComponent<SceneNode>(),
                "The text entity must have a scene node entity");

    scene_node_sptr sceneNode   = a_ent->GetComponent<SceneNode>();
    text_ptr textPtr = a_ent->GetComponent<text_type>();

    gfx_cs::material_sptr matPtr;
    if (a_ent->HasComponent<gfx_cs::Material>())
    { matPtr = a_ent->GetComponent<gfx_cs::Material>(); }

    // -----------------------------------------------------------------------
    // Do not assert on font errors, log them instead and return

    text_type::font_ptr font = textPtr->GetFont();

    if (font == nullptr)
    {
      TLOC_LOG_GFX_WARN() << "Text entity (" << a_ent->GetDebugName() << ") "
        << "does not have a font assigned";
      return TLOC_ERROR(common_error_types::error_null_pointer);
    }

    if (font->IsInitialized() == false)
    {
      TLOC_LOG_GFX_WARN() << "Text entity (" << a_ent->GetDebugName() << ") "
        << "font is not initialized";
      return TLOC_ERROR(common_error_types::error_initialize);
    }

    if (font->IsCached() == false)
    {
      TLOC_LOG_GFX_WARN() << "Text entity (" << a_ent->GetDebugName() << ") "
        << "font does not have glyphs cached";
      return TLOC_ERROR(common_error_types::error_initialize);
    }

    // -----------------------------------------------------------------------
    // text quad pair

    text_quads_pair tqp(a_ent);

    // -----------------------------------------------------------------------
    // go through all the characters and build the text quads

    core_str::StringW text = textPtr->Get();

    gfx_med::GlyphMetrics::value_type advance = 0;

    for (tl_size i = 0; i < text.length(); ++i)
    {
      gfx_med::Font::const_glyph_metrics_iterator 
        itr = font->GetGlyphMetric(text[i]);

      TLOC_LOG_GFX_WARN_IF(itr == font->end_glyph_metrics())
        << "Glyph metrics not found for (" << text[i] << ")"
        << " - symbol does not exist in the glyph cache";

      // -----------------------------------------------------------------------
      // grab the sprite info

      using gfx_med::algos::compare::sprite_info::MakeName;

      gfx_med::sprite_sheet_ul::const_iterator itrSs, itrEndSs;
      itrSs = core::find_if(font->GetSpriteSheetPtr()->begin(),
                            font->GetSpriteSheetPtr()->end(),
                            gfx_med::algos::compare::sprite_info::MakeName((tl_ulong)text[i]));

      itrEndSs = itrSs;
      core::advance(itrEndSs, 1);

      // -----------------------------------------------------------------------
      // create the quad

      const math_t::Vec2f dim = itr->m_dim.ConvertTo<math_t::Vec2f>();
      const math_t::Vec2f padDim = 
        font->GetCachedParams().m_paddingDim.ConvertTo<math_t::Vec2f>();
      const math_t::Vec2f finalDim = dim + padDim;

      using math_t::Rectf_bl;
      Rectf_bl rect = 
        Rectf_bl(Rectf_bl::width(finalDim[0]), Rectf_bl::height(finalDim[1]));

      entity_ptr q = 
        pref_gfx::Quad(m_textEntityMgr.get(), m_textCompMgr.get()).
        TexCoords(true).Dimensions(rect).Create();

      q->SetDebugName( core_str::String(1, core_str::CharWideToAscii(text[i])) );

      if (matPtr)
      { m_textEntityMgr->InsertComponent(q, matPtr); }

      // we need the quad later for other operations
      tqp.second.push_back(q);

      // -----------------------------------------------------------------------
      // make it a node

      pref_gfx::SceneNode(m_textEntityMgr.get(), m_textCompMgr.get())
        .Parent(core_sptr::ToVirtualPtr(sceneNode)).Add(q);

      // -----------------------------------------------------------------------
      // add sprite animation to quad with one texture coordinate only

      pref_gfx::SpriteAnimation(m_textEntityMgr.get(), m_textCompMgr.get())
        .Paused(false).Add(q, itrSs, itrEndSs);

      // -----------------------------------------------------------------------
      // set the quad position

      if (i > 0)
      {
        advance = DoSetTextQuadPosition(q->GetComponent<math_cs::Transform>(), 
                                        q->GetComponent<gfx_cs::Quad>(),
                                        core_sptr::ToVirtualPtr(textPtr),
                                        text[i - 1], text[i], advance);
      }
      else
      {
        advance = DoSetTextQuadPosition(q->GetComponent<math_cs::Transform>(), 
                                        q->GetComponent<gfx_cs::Quad>(),
                                        core_sptr::ToVirtualPtr(textPtr),
                                        text[i], advance);
      }
    }

    DoAlignText(tqp);
    m_allText.push_back(tqp);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    MarkForReinit(const entity_ptr a_ent)
  {
    m_entsToReinit.push_back(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  typedef tl_float            real_type;

  real_type
    DoSetTextQuadPosition(math_cs::transform_sptr                 a_entPos, 
                          gfx_cs::quad_sptr                       a_entQuad,
                          gfx_cs::text_i_vptr                     a_entText,
                          gfx_med::Font::glyph_metrics::char_code a_charCode, 
                          real_type                               a_startingPosX)
  {
    real_type advanceToRet = a_startingPosX;

    gfx_med::Font::const_glyph_metrics_iterator 
      itr = a_entText->GetFont()->GetGlyphMetric(a_charCode);

    // -----------------------------------------------------------------------
    // set the quad position

    typedef gfx_med::Font::Params               Params;

    Params fParams = a_entText->GetFont()->GetCachedParams();
    math_t::Vec3f padDim = fParams.m_paddingDim
      .ConvertTo<math_t::Vec3f, core_ds::p_tuple::overflow_zero>();

    math_t::Vec2f horBearing =
      itr->m_horizontalBearing.ConvertTo<math_t::Vec2f>();

    using math_cs::transform_sptr;
    math_t::Rectf_bl rect = a_entQuad->GetRectangleRef();

    a_entPos->SetPosition
      (math_t::Vec3f(advanceToRet, 0, 0));

    a_entPos->
      SetPosition(a_entPos->GetPosition() +
      math_t::Vec3f(0 - padDim[0], 
                    horBearing[1] - rect.GetHeight() - padDim[1], 
                    0));

    // advance pen's position
    advanceToRet += itr->m_horizontalAdvance;

    return advanceToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  real_type
    DoSetTextQuadPosition(math_cs::transform_sptr                   a_entPos, 
                          gfx_cs::quad_sptr                         a_entQuad,
                          gfx_cs::text_i_vptr                       a_entText,
                          gfx_med::Font::glyph_metrics:: char_code  a_prevCode, 
                          gfx_med::Font::glyph_metrics:: char_code  a_charCode, 
                          real_type                                 a_startingPosX)
  {
    real_type advanceToRet = 
      DoSetTextQuadPosition(a_entPos, a_entQuad, a_entText, a_charCode, a_startingPosX);

    // -----------------------------------------------------------------------
    // set the quad position

    // kerning
    {
      math_t::Vec2f kerning = a_entText->GetFont()->GetKerning(a_prevCode, a_charCode)
        .ConvertTo<math_t::Vec2f>();
      advanceToRet += kerning[0];

      math_t::Vec3f kerning3 = kerning
        .ConvertTo<math_t::Vec3f, core_ds::p_tuple::overflow_zero>();

      a_entPos->SetPosition(a_entPos->GetPosition() + kerning3);
    }

    return advanceToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    DoRemoveText(const const_entity_ptr a_ent)
  {
    using gfx_cs::SceneNode;
    gfx_cs::scene_node_sptr sn = a_ent->GetComponent<SceneNode>();

    for (SceneNode::node_cont_iterator itr = sn->begin(), itrEnd = sn->end();
         itr != itrEnd; ++itr)
    {
      m_textEntityMgr->DestroyEntity( (*itr)->GetEntity() );
    }

    while (sn->size() > 0)
    { sn->RemoveChild(*sn->begin()); }

    // remove the cached entity
    text_quads_cont::iterator itr = 
      find_if_all(m_allText, core::algos::compare::pair::MakeFirst(a_ent));

    if (itr != m_allText.end())
    { m_allText.erase(itr); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TLOC_TEXT_RENDER_SYSTEM_TYPE::error_type
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    Post_Initialize()
  {
    m_textQuadRenderSys.SetRenderer(GetRenderer());
    m_textQuadRenderSys.SetCamera(GetCamera());
    
    m_textQuadRenderSys.Initialize();
    m_textSceneGraphSys.Initialize();
    m_textAnimSys.Initialize();

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TLOC_TEXT_RENDER_SYSTEM_TYPE::error_type
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    DoReInitializeEntity(entity_ptr a_ent)
  {
    DoRemoveText(a_ent);
    return InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities(f64 )
  {
    typedef core_cs::entity_ptr_array::iterator     itr_type;

    for (itr_type itr = m_entsToReinit.begin(), itrEnd = m_entsToReinit.end();
         itr != itrEnd; ++itr)
    {
      DoReInitializeEntity(*itr);
    }
    m_entsToReinit.clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    Post_ProcessActiveEntities(f64 a_deltaT)
  {
    m_textSceneGraphSys.ProcessActiveEntities(a_deltaT);
    m_textAnimSys.ProcessActiveEntities(a_deltaT);
    m_textQuadRenderSys.ProcessActiveEntities(a_deltaT);
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class TextRenderSystem_TI<StaticText>;
  template class TextRenderSystem_TI<DynamicText>;

};};};