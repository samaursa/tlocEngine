#include "tlocFan.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocPrefab/math/tlocTransform.h>
#include <tlocPrefab/graphics/tlocTextureCoords.h>
#include <tlocPrefab/graphics/tlocMesh.h>
#include <tlocPrefab/graphics/tlocBoundingBox.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using namespace core_cs;
  using namespace math_cs;
  using namespace math_cs::components;
  using namespace tloc::graphics::component_system;
  using namespace tloc::graphics::component_system::components;

  using math_t::Circle_T;

  typedef gfx_t::f_vertex::p_vertex_selector::
          Normals<false>                              normals_selected;
  typedef gfx_t::f_vertex::p_vertex_selector::
          Color<false>                                color_selected;

  // ///////////////////////////////////////////////////////////////////////
  // Fan

#define FAN_TEMPS   bool T_TexCoords
#define FAN_PARAMS  T_TexCoords

  template <FAN_TEMPS>
  Fan_T<FAN_PARAMS>::
    Fan_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_circle(circle_type(circle_type::radius(1.0f)) )
    , m_numSides(8)
    , m_sectorAngle(360.0f)
    , m_sprite(false)
    , m_drawMode(gfx_rend::mode::k_triangle_fan)
    , m_boundingBox(false)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FAN_TEMPS>
  auto
    Fan_T<FAN_PARAMS>::
    Construct() const -> component_ptr
  {
    pref_gfx::Mesh meshPref(m_entMgr, m_compPoolMgr);
    meshPref.DrawMode(m_drawMode);

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

    typedef core_conts::Array<Vec2f32>                    vec2_cont;

    const auto angleInterval = m_sectorAngle.Get() / m_numSides;

    // POSITIONS

    vec2_cont positions;
    // push the center vertex
    {
      auto newCoord = m_circle.GetPosition();
      positions.push_back(newCoord);
    }

    for (f32 i = 0; i <= m_numSides; ++i)
    {
      auto newCoord = m_circle.GetCoord(degree_f32(angleInterval * i));
      positions.push_back(newCoord);
    }

    // TEXTURE COORDINATES
    const auto& texCoords = DoGenerateTexCoords();

    // VERTEXES
    TLOC_ASSERT(positions.size() == texCoords.size(), 
                "Position/texcoords size mismatch");

    vert_cont verts;
    verts.reserve(m_numSides + 2);

    for (tl_size i = 0; i < positions.size(); ++i)
    {
      verts.push_back(vert_selector().Fill(positions[i], 0, 0, texCoords[i]));
    }

    return meshPref.Construct(verts);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FAN_TEMPS>
  auto
    Fan_T<FAN_PARAMS>::
    Create() const -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  template <FAN_TEMPS>
  void
    Fan_T<FAN_PARAMS>::
    Add(entity_ptr a_ent) const
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // bounding box

    if (a_ent->HasComponent<gfx_cs::BoundingBox2D>() == false && m_boundingBox)
    { pref_gfx::BoundingBox2D(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // sprite

    if (m_sprite)
    {
      DoIssueTextureCoordinateWarning(texcoords_selected());

      const auto& texCoords = DoGenerateTexCoords();

      TextureCoords tCoords(m_entMgr, m_compPoolMgr);
      {
        for (auto itr = texCoords.begin(), itrEnd = texCoords.end(); 
             itr != itrEnd; ++itr)
        { tCoords.AddCoord(*itr); }
        tCoords.Add(a_ent);
      }
    }

    // -----------------------------------------------------------------------
    // fan component

    m_entMgr->InsertComponent( insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FAN_TEMPS>
  auto
    Fan_T<FAN_PARAMS>::
    DoGenerateTexCoords() const -> vec2_cont
  {
    using namespace math_t;
    // TEXTURE COORDINATES

    const auto angleInterval = m_sectorAngle.Get() / m_numSides;

    vec2_cont texCoords;

    typedef Circlef32 circle_type;
    // Create the texture co-ordinates
    circle_type circForTex;
    circForTex.SetRadius(0.5f);
    circForTex.SetPosition(Vec2f32(0.5f, 0.5f));

    texCoords.push_back(circForTex.GetPosition());
    for (f32 i = 0; i <= m_numSides; ++i)
    {
      auto newTexCoord =
        circForTex.GetCoord(degree_f32(angleInterval * i));
      texCoords.push_back(newTexCoord);
    }

    return texCoords;
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Fan_T<true>;
  template class Fan_T<false>;

};};};