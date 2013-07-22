#include "tlocCuboid.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/types/tlocCuboid.h>

#include <tlocGraphics/component_system/tlocMesh.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::mesh_sptr;

  using math_cs::Transform;
  using math_cs::transform_sptr;

  // ///////////////////////////////////////////////////////////////////////
  // Cuboid

  Cuboid::entity_type*
    Cuboid::
    Create()
  {
    Entity* ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Cuboid::
    Add(entity_type* a_ent)
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef ComponentPoolManager        pool_mgr;

    typedef core_conts::Array<gfx_cs::Mesh::vert_type>    vert_cont;
    typedef vert_cont::const_iterator                     vert_cont_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_sptr_pool        mesh_pool;
    gfx_cs::mesh_sptr_pool_sptr           meshPool;

    if (m_compPoolMgr->Exists(mesh) == false)
    { meshPool = m_compPoolMgr->CreateNewPool<mesh_sptr>(); }
    else
    { meshPool = m_compPoolMgr->GetPool<mesh_sptr>(); }

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    itrMesh->SetValue(mesh_sptr(new gfx_cs::Mesh()) );

    mesh_sptr meshPtr = itrMesh->GetValue();

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

    typedef   mesh_sptr::value_type::vert_type      vert_type;
    typedef   mesh_sptr::value_type::cont_type      vert_cont_type;
    typedef   mesh_sptr::value_type::iterator       vert_itr;

    vert_cont_type vertCont;
    vertCont.resize(36);

    vert_itr itr = vertCont.begin();
    vert_itr itrEnd = vertCont.end();

#define INCREMENT_AND_CHECK_ITR()\
  ++itr; TLOC_ASSERT(itr != itrEnd, "Not enough vertices reserved for this cube!")

    // Front face
    itr->SetPosition(blf);
    itr->SetNormal(frontNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 0.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trf);
    itr->SetNormal(frontNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(tlf);
    itr->SetNormal(frontNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    itr->SetPosition(blf);
    itr->SetNormal(frontNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 0.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(brf);
    itr->SetNormal(frontNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 0.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trf);
    itr->SetNormal(frontNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Top face
    itr->SetPosition(tlf);
    itr->SetNormal(topNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trb);
    itr->SetNormal(topNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(tlb);
    itr->SetNormal(topNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    itr->SetPosition(tlf);
    itr->SetNormal(topNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trf);
    itr->SetNormal(topNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trb);
    itr->SetNormal(topNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Back face
    itr->SetPosition(blb);
    itr->SetNormal(backNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 3.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(tlb);
    itr->SetNormal(backNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trb);
    itr->SetNormal(backNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    itr->SetPosition(blb);
    itr->SetNormal(backNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 3.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trb);
    itr->SetNormal(backNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(brb);
    itr->SetNormal(backNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 3.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Side 1 (left face when looking down z-axis)
    itr->SetPosition(brf);
    itr->SetNormal(leftNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 0.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trb);
    itr->SetNormal(leftNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trf);
    itr->SetNormal(leftNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    itr->SetPosition(brf);
    itr->SetNormal(leftNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 0.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(brb);
    itr->SetNormal(leftNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 0.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(trb);
    itr->SetNormal(leftNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    // Side 2 (right face when looking down z-axis)
    itr->SetPosition(blb);
    itr->SetNormal(rightNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 3.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(tlf);
    itr->SetNormal(rightNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(tlb);
    itr->SetNormal(rightNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    itr->SetPosition(blb);
    itr->SetNormal(rightNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 2.0f, vMulti  * 3.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(blf);
    itr->SetNormal(rightNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 3.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(tlf);
    itr->SetNormal(rightNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 1.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();

    // bottom

    itr->SetPosition(blf);
    itr->SetNormal(bottomNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 4.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(brb);
    itr->SetNormal(bottomNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 3.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(brf);
    itr->SetNormal(bottomNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 4.0f, vMulti  * 1.0f));
    INCREMENT_AND_CHECK_ITR();

    itr->SetPosition(blf);
    itr->SetNormal(bottomNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 4.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(blb);
    itr->SetNormal(bottomNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 3.0f, vMulti  * 2.0f));
    INCREMENT_AND_CHECK_ITR();
    itr->SetPosition(brb);
    itr->SetNormal(bottomNorm);
    itr->SetTexCoord(Vec2f32(uMulti * 3.0f, vMulti  * 1.0f));

    // -----------------------------------------------------------------------

    for (itr = vertCont.begin(), itrEnd = vertCont.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    // -----------------------------------------------------------------------

    typedef math_cs::transform_f32_sptr_pool      t_pool;
    math_cs::transform_f32_sptr_pool_sptr         tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<transform_sptr>(); }
    else
    { tPool = m_compPoolMgr->GetPool<transform_sptr>(); }

    t_pool::iterator  itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    // -----------------------------------------------------------------------

    m_entMgr->InsertComponent(a_ent, itrTransform->GetValue().get() );
    m_entMgr->InsertComponent(a_ent, itrMesh->GetValue().get() );

  }
};};};