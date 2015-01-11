#include "tlocQuad.h"

#include <tlocCore/logging/tlocLogger.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocPrefab/graphics/tlocTextureCoords.h>
#include <tlocPrefab/math/tlocTransform.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::quad_sptr;
  using core_sptr::MakeShared;

  using gfx_cs::texture_coords_sptr;

  using math_t::Rectangle_T;

  typedef gfx_t::f_vertex::p_vertex_selector::
          Normals<false>                              normals_selected;
  typedef gfx_t::f_vertex::p_vertex_selector::
          Color<false>                                color_selected;

  // ///////////////////////////////////////////////////////////////////////
  // Quad

#define QUAD_TEMPS  bool T_TexCoords 
#define QUAD_PARAMS T_TexCoords

  template <QUAD_TEMPS>
  Quad_T<QUAD_PARAMS>::
    Quad_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_rect(rect_type(rect_type::width(1.0f),
                       rect_type::height(1.0f)) )
    , m_meshPref(a_entMgr, a_poolMgr)
    , m_sprite(false)
  { 
    m_meshPref.DrawMode(gfx_rend::mode::k_triangle_strip);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <QUAD_TEMPS>
  auto
    Quad_T<QUAD_PARAMS>::
    Construct() const -> component_ptr
  {
    // prepare vertices
    using namespace gfx_t::f_vertex::p_vertex_selector;
    using namespace math_t;

    typedef typename gfx_t::f_vertex::VertexSelector
      <Pos2D, 
       normals_selected, 
       color_selected, 
       texcoords_selected>                                vert_selector;

    typedef typename vert_selector::value_type            vert_type;
    typedef core_conts::Array<vert_type>                  vert_cont;
    typedef vert_cont::iterator                           vert_itr;

    auto pos0 = Vec2f32(m_rect.GetValue<rect_type::right>(), 
                        m_rect.GetValue<rect_type::top>());
    auto pos1 = Vec2f32(m_rect.GetValue<rect_type::left>(), 
                        m_rect.GetValue<rect_type::top>());
    auto pos2 = Vec2f32(m_rect.GetValue<rect_type::right>(), 
                        m_rect.GetValue<rect_type::bottom>());
    auto pos3 = Vec2f32(m_rect.GetValue<rect_type::left>(), 
                        m_rect.GetValue<rect_type::bottom>());

    const auto& texCoords = DoGenerateTexCoords();

    vert_cont verts;
    verts.push_back(vert_selector().Fill(pos0, 0, 0, texCoords[0]));
    verts.push_back(vert_selector().Fill(pos1, 0, 0, texCoords[1]));
    verts.push_back(vert_selector().Fill(pos2, 0, 0, texCoords[2]));
    verts.push_back(vert_selector().Fill(pos3, 0, 0, texCoords[3]));

    return m_meshPref.Construct(verts);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <QUAD_TEMPS>
  auto
    Quad_T<QUAD_PARAMS>::
    Create() const -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  namespace {

    using namespace gfx_t::f_vertex::p_vertex_selector;

    void DoIssueTextureCoordinateWarning(TexCoords<true>)
    {
      TLOC_LOG_GFX_WARN_FILENAME_ONLY()
        << "Interleaved texture coordinates of this Quad will be overridden by "
        << "its animated (sprite) texture coordinates";
    }

    void DoIssueTextureCoordinateWarning(TexCoords<false>)
    {
      // intentionally empty
    }

  }

  template <QUAD_TEMPS>
  void
    Quad_T<QUAD_PARAMS>::
    Add(entity_ptr a_ent) const
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // sprite

    if (m_sprite)
    {
      DoIssueTextureCoordinateWarning(texcoords_selected());

      const auto& texCoords = DoGenerateTexCoords();
      TextureCoords(m_entMgr, m_compPoolMgr)
        .AddCoord(texCoords[0])
        .AddCoord(texCoords[1])
        .AddCoord(texCoords[2])
        .AddCoord(texCoords[3])
        .Add(a_ent);
    }

    // -----------------------------------------------------------------------
    // quad component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <QUAD_TEMPS>
  auto
    Quad_T<QUAD_PARAMS>::
    DoGenerateTexCoords() const -> vec2_cont
  {
    using namespace math_t;

    vec2_cont texCoords;
    
    texCoords.push_back(Vec2f32(1.0f, 1.0f));
    texCoords.push_back(Vec2f32(0.0f, 1.0f));
    texCoords.push_back(Vec2f32(1.0f, 0.0f));
    texCoords.push_back(Vec2f32(0.0f, 0.0f));

    return texCoords;
  }


  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Quad_T<true>;
  template class Quad_T<false>;

};};};