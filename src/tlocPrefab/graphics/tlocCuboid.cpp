#include "tlocCuboid.h"

#include <tlocCore/tlocAssert.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>

#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using gfx_cs::mesh_sptr;

  using math_cs::Transform;
  using math_cs::transform_sptr;

  typedef gfx_t::f_vertex::p_vertex_selector::
          Color<false>                                color_selected;

  // ///////////////////////////////////////////////////////////////////////
  // Cuboid

#define CUBOID_TEMPS  bool T_TexCoords, bool T_Normals
#define CUBOID_PARAMS T_TexCoords, T_Normals

  template <CUBOID_TEMPS>
  Cuboid_T<CUBOID_PARAMS>::
    Cuboid_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_cuboid(cuboid_type (cuboid_type::width(1.0f),
                            cuboid_type::height(1.0f),
                            cuboid_type::depth(1.0f)) )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMPS>
  auto
    Cuboid_T<CUBOID_PARAMS>::
    Construct() -> component_ptr
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;
    using namespace gfx_t::f_vertex::p_vertex_selector;

    typedef ComponentPoolManager                          pool_mgr;

    typedef typename gfx_t::f_vertex::VertexSelector
      <Pos3D, 
       normals_selected, 
       color_selected, 
       texcoords_selected>                                vert_selector;

    typedef typename vert_selector::value_type            vert_type;
    typedef core_conts::Array<vert_type>                  vert_cont;
    typedef vert_cont::iterator                           vert_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_pool             mesh_pool;

    gfx_cs::mesh_pool_vptr  meshPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::Mesh>();

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    (*itrMesh)->SetValue(MakeShared<gfx_cs::Mesh>() );

    gfx_cs::mesh_sptr meshPtr = *(*itrMesh)->GetValuePtr();

    // -----------------------------------------------------------------------
    // Generate cuboid vertices

    typedef cuboid_type::point_type        vec_type;

    vec_type tlf = m_cuboid.GetCoord_TopLeftFront();
    vec_type trf = m_cuboid.GetCoord_TopRightFront();
    vec_type blf = m_cuboid.GetCoord_BottomLeftFront();
    vec_type brf = m_cuboid.GetCoord_BottomRightFront();

    vec_type tlb = m_cuboid.GetCoord_TopLeftBack();
    vec_type trb = m_cuboid.GetCoord_TopRightBack();
    vec_type blb = m_cuboid.GetCoord_BottomLeftBack();
    vec_type brb = m_cuboid.GetCoord_BottomRightBack();

    vec_type frontNorm(0, 0, 1);
    vec_type topNorm(0, 1, 0);
    vec_type backNorm(0, 0, -1);
    vec_type leftNorm(1, 0, 0);
    vec_type rightNorm(-1, 0, 0);
    vec_type bottomNorm(0, -1, 0);

    using math_t::Vec2f32;
    Vec2f32 tCoord(0, 0);
    const f32 uMulti = 1.0f / 4.0f;
    const f32 vMulti = 1.0f / 3.0f;

    vert_cont vertCont;
    vertCont.resize(36);

    vert_itr itr = vertCont.begin();
    vert_itr itrEnd = vertCont.end();

#define INCREMENT_AND_CHECK_ITR()\
  ++itr; TLOC_ASSERT(itr != itrEnd, "Not enough vertices reserved for this cube!")

    // Front face

    vert_selector vs;
    *itr = vs.Fill(blf, frontNorm, 0, Vec2f32(uMulti * 0.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trf, frontNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(tlf, frontNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    *itr = vs.Fill(blf, frontNorm, 0, Vec2f32(uMulti * 0.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(brf, frontNorm, 0, Vec2f32(uMulti * 0.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trf, frontNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Top face
    *itr = vs.Fill(tlf, topNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trb, topNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(tlb, topNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    *itr = vs.Fill(tlf, topNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trf, topNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trb, topNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Back face
    *itr = vs.Fill(blb, backNorm, 0, Vec2f32(uMulti * 3.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(tlb, backNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trb, backNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    *itr = vs.Fill(blb, backNorm, 0, Vec2f32(uMulti * 3.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trb, backNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(brb, backNorm, 0, Vec2f32(uMulti * 3.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Side 1 (left face when looking down z-axis)
    *itr = vs.Fill(brf, leftNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 0.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trb, leftNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trf, leftNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    *itr = vs.Fill(brf, leftNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 0.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(brb, leftNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 0.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(trb, leftNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Side 2 (right face when looking down z-axis)
    *itr = vs.Fill(blb, rightNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 3.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(tlf, rightNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(tlb, rightNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    *itr = vs.Fill(blb, rightNorm, 0, Vec2f32(uMulti * 2.0f, vMulti  * 3.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(blf, rightNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 3.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(tlf, rightNorm, 0, Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    // bottom

    *itr = vs.Fill(blf, bottomNorm, 0, Vec2f32(uMulti * 4.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(brb, bottomNorm, 0, Vec2f32(uMulti * 3.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(brf, bottomNorm, 0, Vec2f32(uMulti * 4.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    *itr = vs.Fill(blf, bottomNorm, 0, Vec2f32(uMulti * 4.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(blb, bottomNorm, 0, Vec2f32(uMulti * 3.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    *itr = vs.Fill(brb, bottomNorm, 0, Vec2f32(uMulti * 3.0f, vMulti  * 1.0f));

    // -----------------------------------------------------------------------

    for (itr = vertCont.begin(), itrEnd = vertCont.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    return meshPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMPS>
  auto
    Cuboid_T<CUBOID_PARAMS>::
    Create() -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <CUBOID_TEMPS>
  void
    Cuboid_T<CUBOID_PARAMS>::
    Add(entity_ptr a_ent)
  {

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // mesh component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()) ); 

  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Cuboid_T<>;
  template class Cuboid_T<true, false>;
  template class Cuboid_T<false, true>;

};};};