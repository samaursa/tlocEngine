#include "tlocTextRenderSystem_TI.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/io/tlocFileIO.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>
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

#define TLOC_TEXT_RENDER_SYSTEM_TEMPS   typename T_TextOrStaticTextComponent
#define TLOC_TEXT_RENDER_SYSTEM_PARAMS  T_TextOrStaticTextComponent
#define TLOC_TEXT_RENDER_SYSTEM_TYPE    typename TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // TextRenderSystem_I

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    TextRenderSystem_TI(event_manager_ptr a_eventMgr, 
                        entity_manager_ptr a_entityMgr,
                        BufferArg a_debugName)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<text_type>(), a_debugName)
    , m_textEntityMgr(m_textEventMgr.get())
    , m_textSceneGraphSys(m_textEventMgr.get(), m_textEntityMgr.get())
    , m_textMeshRenderSys(m_textEventMgr.get(), m_textEntityMgr.get())
    , m_textAnimSys(m_textEventMgr.get(), m_textEntityMgr.get())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    ~TextRenderSystem_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  auto
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    DoAlignLine(const_glyph_info_itr a_begin, 
                const_glyph_info_itr a_end, 
                tl_int a_beginIndex,
                text_ptr a_text, 
                size_type a_lineNumber) -> real_pair
  {
    typedef core_cs::const_entity_ptr_array       ent_cont;

    real_type advance = 0;
    real_type maxHeight = 0;
    real_type minHeight = 0;

    const auto& fontParams = a_text->GetFont()->GetCachedParams();

    math_t::Vec3f starPos, endPos;
    tl_int count = a_beginIndex;

    auto itrLast = a_begin;

    for (auto itr = a_begin, itrEnd = a_end; 
         itr != itrEnd; ++itr)
    {
      itrLast = itr;
      using core_sptr::ToVirtualPtr;

      auto t = itr->m_trans;
      auto q = itr->m_rect;

      if (count != a_beginIndex)
      {
        advance = 
          DoSetTextQuadPosition(t, q, ToVirtualPtr(a_text), 
                                a_text->Get()[count - 1], 
                                a_text->Get()[count], advance, a_lineNumber);
      }
      else
      {
        advance = 
          DoSetTextQuadPosition(t, q, ToVirtualPtr(a_text), 
                                a_text->Get()[count], advance, a_lineNumber);
        starPos = t->GetPosition();
      }

      // Algorithm: maxHeight is the absolute maximum this line of text has, 
      // which is the position of the quad + its height (because the quad starts
      // at bottom left). The minHeight is the absolute minimum which is just 
      // the position (i.e. bottom left of the quad)
      const auto& newPos = t->GetPosition();
      const auto& actualHeight = q.GetHeight() - (fontParams.PaddingDim()[1]);

      if (maxHeight < newPos[1] + actualHeight)
      { maxHeight = newPos[1] + actualHeight; }
      else if (minHeight > newPos[1] + (fontParams.PaddingDim()[1]) )
      { minHeight = newPos[1] + (fontParams.PaddingDim()[1]); }

      ++count;
    }

    math_t::Vec3f totalTextWidth(advance, 0, 0);
    
    // only center and right alignment needs adjustment
    if (a_text->GetAlignment() != alignment::k_align_left)
    {
      if (a_text->GetAlignment() == alignment::k_align_center)
      { totalTextWidth = totalTextWidth * 0.5f * -1.0f; }
      else if (a_text->GetAlignment() == alignment::k_align_right)
      { totalTextWidth = totalTextWidth * -1.0f; }

      for (auto itr = a_begin, itrEnd = a_end; itr != itrEnd; ++itr)
      {
        math_cs::transform_sptr t = itr->m_trans;
        t->SetPosition(t->GetPosition() + totalTextWidth);
      }
    }

    return core::MakePair(minHeight, maxHeight);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    DoAlignText(const text_quads_pair& a_pair)
  {
    typedef core_cs::const_entity_ptr_array       ent_cont;

    text_ptr text = a_pair.first->template GetComponent<text_type>();

    if (a_pair.second.size() == 0)
    { return; }

    auto itr    = a_pair.second.begin();
    auto prevItr = itr;
    auto itrEnd = a_pair.second.end();

    const typename text_type::str_type& str = text->Get();

    tl_int count = 0;
    tl_int beginIndex = count;
    tl_int lineNumber = 0;

    typedef core_conts::Array<real_pair>          real_cont;
    real_cont heights;
    real_type allLinesHeight = 0;

    for ( ; itr != itrEnd; ++itr)
    {
      if (core_str::g_newlineStrW.find(str[count]) != core_str::StringW::npos)
      {
        auto minMax = DoAlignLine(prevItr, itr, beginIndex, text, lineNumber);
        allLinesHeight += (minMax.second - minMax.first);
        heights.push_back(minMax);

        prevItr = itr + 1;
        beginIndex = count + 1;
        ++lineNumber;
      }

      ++count;
    }

    auto minMax = DoAlignLine(prevItr, itr, beginIndex, text, lineNumber);
    allLinesHeight += (minMax.second - minMax.first);
    heights.push_back(minMax);

    // Algorithm: Take total height of all lines divided by 2. That is the 
    // 'main' offset. But the first line starts on the baseline. We will pretend
    // that it starts just below the baseline which means we have to subtract
    // the amount of text that is 'above' the baseline.
    if (text->GetHorizontalAlignment() == horizontal_alignment::k_align_middle)
    {
      const auto vertKerningTotal = text->GetVerticalKerning() * (heights.size()-1);

      // our parent entity (which is the text component the user created) is
      // our base line
      const auto& parentEntPos =
        a_pair.first->template GetComponent<math_cs::Transform>()->GetPosition();
      const auto firstLineOffset = heights[0].second - parentEntPos[1];

      auto allLinesHeightHalf = 
        allLinesHeight * 0.5f + vertKerningTotal - firstLineOffset;

      count = 0;
      itr = a_pair.second.begin();
      prevItr = itr;
      for ( ; itr != itrEnd; ++itr)
      {
        auto t = itr->m_trans;
        t->SetPosition(t->GetPosition() + math_t::Vec3f(0, allLinesHeightHalf, 0));
      }
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

    typename text_type::font_ptr font = textPtr->GetFont();

    if (font == nullptr)
    {
      TLOC_LOG_GFX_WARN() << "Text Entity " << *a_ent 
        << "does not have a font assigned";
      return TLOC_ERROR(common_error_types::error_null_pointer);
    }

    if (font->IsInitialized() == false)
    {
      TLOC_LOG_GFX_WARN() << "Text Entity " << *a_ent 
        << "font is not initialized";
      return TLOC_ERROR(common_error_types::error_initialize);
    }

    if (font->IsCached() == false)
    {
      TLOC_LOG_GFX_WARN() << "Text Entity " << *a_ent
        << "font does not have glyphs cached";
      return TLOC_ERROR(common_error_types::error_initialize);
    }

    // -----------------------------------------------------------------------
    // text quad pair

    text_quads_pair tqp(a_ent);

    // -----------------------------------------------------------------------
    // go through all the characters and build the text quads

    core_str::StringW text = textPtr->Get();

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
        font->GetCachedParams().PaddingDim().template ConvertTo<math_t::Vec2f>();
      const math_t::Vec2f finalDim = dim + (padDim * 2);

      using math_t::Rectf_bl;
      Rectf_bl rect = 
        Rectf_bl(Rectf_bl::width(finalDim[0]), Rectf_bl::height(finalDim[1]));

      entity_ptr character = 
        pref_gfx::QuadNoTexCoords(m_textEntityMgr.get(), m_textCompMgr.get())
        .Sprite(true).Dimensions(rect).Create();

      const char8 currChar = core_str::CharWideToAscii(text[i]);
      character->SetDebugName( core_str::String(1, currChar) );

      if (matPtr)
      { 
        m_textEntityMgr->InsertComponent
          (entity_manager::Params(character, matPtr).Orphan(true));
      }

      // set the user shader operator which may have unique uniforms
      const auto& mesh = character->GetComponent<gfx_cs::Mesh>();
      *mesh->GetUserShaderOperator() = *textPtr->GetUserShaderOperator();

      // we need the quad later for other operations
      auto ci = CharacterInfo()
        .Transformation(character->GetComponent<math_cs::Transform>())
        .Rectangle(rect)
        .Character(text[i]);
      tqp.second.push_back(ci);

      // disable rendering of empty characters (spaces, \n) - we could simply
      // not create it but other logic relies on these characters
      // TODO: Refactor later to not create the quad in the first place
      if (core_str::IsSpace(core_str::CharWideToAscii(text[i])))
      { character->Deactivate(); }

      // -----------------------------------------------------------------------
      // make it a node

      pref_gfx::SceneNode(m_textEntityMgr.get(), m_textCompMgr.get())
        .Parent(core_sptr::ToVirtualPtr(sceneNode)).Add(character);

      // -----------------------------------------------------------------------
      // add sprite animation to quad with one texture coordinate only

      pref_gfx::SpriteAnimation(m_textEntityMgr.get(), m_textCompMgr.get())
        .Paused(false).Add(character, itrSs, itrEndSs);

      if (a_ent->IsActive() == false)
      { character->Deactivate(); }
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
  typedef tl_size             size_type;

  real_type
    DoSetTextQuadPosition(math_cs::transform_sptr                 a_entPos, 
                          math_t::Rectf32_bl                      a_rect,
                          gfx_cs::text_i_vptr                     a_entText,
                          gfx_med::Font::glyph_metrics::char_code a_charCode, 
                          real_type                               a_startingPosX,
                          size_type                               a_lineNumber)
  {
    real_type advanceToRet = a_startingPosX;

    gfx_med::Font::const_glyph_metrics_iterator 
      itr = a_entText->GetFont()->GetGlyphMetric(a_charCode);

    // -----------------------------------------------------------------------
    // set the quad position

    typedef gfx_med::Font::Params               Params;

    Params fParams = a_entText->GetFont()->GetCachedParams();
    math_t::Vec3f padDim = fParams.PaddingDim()
      .ConvertTo<math_t::Vec3f, core_ds::p_tuple::overflow_zero>();

    math_t::Vec2f horBearing =
      itr->m_horizontalBearing.ConvertTo<math_t::Vec2f>();

    using math_cs::transform_sptr;

    const real_type yPos = (fParams.FontSize().GetHeightInPixels() + 
                            a_entText->GetVerticalKerning()) * a_lineNumber;

    a_entPos->SetPosition
      (math_t::Vec3f(advanceToRet, -yPos, 0));

    a_entPos->
      SetPosition(a_entPos->GetPosition() +
      math_t::Vec3f(horBearing[0] - padDim[0], 
                    horBearing[1] - a_rect.GetHeight() + padDim[1], 
                    0));

    // advance pen's position
    advanceToRet += itr->m_horizontalAdvance;

    return advanceToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  real_type
    DoSetTextQuadPosition(math_cs::transform_sptr                   a_entPos, 
                          math_t::Rectf32_bl                        a_rect,
                          gfx_cs::text_i_vptr                       a_entText,
                          gfx_med::Font::glyph_metrics:: char_code  a_prevCode, 
                          gfx_med::Font::glyph_metrics:: char_code  a_charCode, 
                          real_type                                 a_startingPosX,
                          size_type                                 a_lineNumber)
  {
    real_type advanceToRet = 
      DoSetTextQuadPosition(a_entPos, a_rect, a_entText, a_charCode, 
                            a_startingPosX, a_lineNumber);

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
    typename text_quads_cont::iterator itr =
      find_if_all(m_allText, core::algos::pair::compare::MakeFirst(a_ent));

    if (itr != m_allText.end())
    { m_allText.erase(itr); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  TLOC_TEXT_RENDER_SYSTEM_TYPE::error_type
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    Post_Initialize()
  {
    m_textMeshRenderSys->SetRenderer(GetRenderer());

    if (GetCamera() != nullptr)
    { m_textMeshRenderSys->SetCamera(GetCamera()); }
    
    m_textMeshRenderSys->Initialize();
    m_textSceneGraphSys->Initialize();
    m_textAnimSys->Initialize();

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
    { DoReInitializeEntity(*itr); }
    m_entsToReinit.clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    Post_ProcessActiveEntities(f64 a_deltaT)
  {
    m_textSceneGraphSys->ProcessActiveEntities(a_deltaT);
    m_textAnimSys->ProcessActiveEntities(a_deltaT);
    m_textMeshRenderSys->ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    SetEnabledSortingByMaterial(bool a_value)
  { 
    base_type::SetEnabledSortingByMaterial(a_value); 
    m_textMeshRenderSys->SetEnabledSortingByMaterial(a_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    SetEnabledSortingFrontToBack(bool a_value)
  { 
    base_type::SetEnabledSortingFrontToBack(a_value); 
    m_textMeshRenderSys->SetEnabledSortingFrontToBack(a_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    SetEnabledSortingBackToFront(bool a_value)
  { 
    base_type::SetEnabledSortingBackToFront(a_value); 
    m_textMeshRenderSys->SetEnabledSortingBackToFront(a_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    SetEnabledSortingFrontToBack_2D(bool a_value)
  { 
    base_type::SetEnabledSortingFrontToBack_2D(a_value); 
    m_textMeshRenderSys->SetEnabledSortingFrontToBack_2D(a_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_TEXT_RENDER_SYSTEM_TEMPS>
  void
    TextRenderSystem_TI<TLOC_TEXT_RENDER_SYSTEM_PARAMS>::
    SetEnabledSortingBackToFront_2D(bool a_value)
  { 
    base_type::SetEnabledSortingBackToFront_2D(a_value); 
    m_textMeshRenderSys->SetEnabledSortingBackToFront_2D(a_value);
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class TextRenderSystem_TI<StaticText>;
  template class TextRenderSystem_TI<DynamicText>;

};};};
