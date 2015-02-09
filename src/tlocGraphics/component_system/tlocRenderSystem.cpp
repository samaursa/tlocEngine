#include "tlocRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/time/tlocTime.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocVertexArrayObject.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/renderer/tlocDrawCommand.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    // ///////////////////////////////////////////////////////////////////////
    // Entity Compare Materials

    TLOC_DECL_ALGO_WITH_CTOR_UNARY(MaterialCompare_T, gfx_cs::material_sptr, const);
    TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(MaterialCompare_T, const)
    {
      typedef gfx_cs::material_sptr                         ptr_type;
      typedef ptr_type::value_type                          comp_type;

      const auto& aa = extract()(a);

      auto matPtr = aa.first->template GetComponentIfExists<comp_type>();

      if (matPtr)
      { return matPtr == m_value; }

      return false;
    }

    typedef MaterialCompare_T<core::use_reference> MaterialCompare;
    typedef MaterialCompare_T<core::use_pointee>   MaterialComparePointer;

    // ///////////////////////////////////////////////////////////////////////
    // Entity Compare Materials

    TLOC_DECL_ALGO_BINARY(MaterialCompareFromEntity_T, const);
    TLOC_DEFINE_ALGO_BINARY(MaterialCompareFromEntity_T, const)
    {
      typedef gfx_cs::material_sptr                         ptr_type;
      typedef ptr_type::value_type                          comp_type;

      const auto& aa = extract()(a);
      const auto& bb = extract()(b);

      if (aa.first->template HasComponent<comp_type>() == false)
      { return true; }
      else if (bb.first->template HasComponent<comp_type>() == false)
      { return false; }

      ptr_type first = aa.first->template GetComponent<comp_type>();
      ptr_type second = bb.first->template GetComponent<comp_type>();

      return first < second;
    }

    typedef MaterialCompareFromEntity_T<core::use_reference> MaterialCompareFromEntity;
    typedef MaterialCompareFromEntity_T<core::use_pointee>   MaterialCompareFromEntityPointer;

    // ///////////////////////////////////////////////////////////////////////

    TLOC_DECL_ALGO_WITH_CTOR_BINARY(CompareFrontToBack_T, core_cs::const_entity_vptr, const);
    TLOC_DEFINE_ALGO_WITH_CTOR_BINARY(CompareFrontToBack_T, const)
    {
      typedef math_cs::Transform                    comp_type;
      typedef gfx_cs::SceneNode                     scene_node;

      const auto& aa = extract()(a);
      const auto& bb = extract()(b);

      auto aaSceneNode = aa.first->template GetComponentIfExists<scene_node>();
      auto bbSceneNode = bb.first->template GetComponentIfExists<scene_node>();

      const auto& aaLocal = 
        aa.first->template GetComponent<comp_type>()->GetTransformation();
      const auto& bbLocal = 
        bb.first->template GetComponent<comp_type>()->GetTransformation();

      const auto& aaTrans  = 
        aaSceneNode ? aaSceneNode->GetWorldTransform() : aaLocal;
      const auto& bbTrans  = 
        bbSceneNode ? bbSceneNode->GetWorldTransform() : bbLocal;

      const auto& camTrans = m_value->GetComponent<comp_type>();

      const auto& aaPos   = aaTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();
      const auto& bbPos   = bbTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();
      const auto& camPos  = camTrans->GetPosition();

      const auto aaDisToCam = aaPos.DistanceSquared(camPos);
      const auto bbDisToCam = bbPos.DistanceSquared(camPos);

      if (aaDisToCam < bbDisToCam)
      { return true; }

      return false;
    }

    typedef CompareFrontToBack_T<core::use_reference> CompareFrontToBack;
    typedef CompareFrontToBack_T<core::use_pointee>   CompareFrontToBackPointer;

    // ///////////////////////////////////////////////////////////////////////

    TLOC_DECL_ALGO_WITH_CTOR_BINARY(CompareBackToFront_T, core_cs::const_entity_vptr, const);
    TLOC_DEFINE_ALGO_WITH_CTOR_BINARY(CompareBackToFront_T, const)
    {
      typedef math_cs::Transform                    comp_type;
      typedef gfx_cs::SceneNode                     scene_node;

      const auto& aa = extract()(a);
      const auto& bb = extract()(b);

      auto aaSceneNode = aa.first->template GetComponentIfExists<scene_node>();
      auto bbSceneNode = bb.first->template GetComponentIfExists<scene_node>();

      const auto& aaLocal = 
        aa.first->template GetComponent<comp_type>()->GetTransformation();
      const auto& bbLocal = 
        bb.first->template GetComponent<comp_type>()->GetTransformation();

      const auto& aaTrans  = 
        aaSceneNode ? aaSceneNode->GetWorldTransform() : aaLocal;
      const auto& bbTrans  = 
        bbSceneNode ? bbSceneNode->GetWorldTransform() : bbLocal;

      const auto& camTrans = m_value->GetComponent<comp_type>();

      const auto& aaPos   = aaTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();
      const auto& bbPos   = bbTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();
      const auto& camPos  = camTrans->GetPosition();

      const auto aaDisToCam = aaPos.DistanceSquared(camPos);
      const auto bbDisToCam = bbPos.DistanceSquared(camPos);

      if (aaDisToCam > bbDisToCam)
      { return true; }

      return false;
    }

    typedef CompareBackToFront_T<core::use_reference> CompareBackToFront;
    typedef CompareBackToFront_T<core::use_pointee>   CompareBackToFrontPointer;

    // ///////////////////////////////////////////////////////////////////////

    TLOC_DECL_ALGO_BINARY(CompareFrontToBack_2D_T, const);
    TLOC_DEFINE_ALGO_BINARY(CompareFrontToBack_2D_T, const)
    {
      typedef math_cs::Transform                    comp_type;
      typedef gfx_cs::SceneNode                     scene_node;

      const auto& aa = extract()(a);
      const auto& bb = extract()(b);

      auto aaSceneNode = aa.first->template GetComponentIfExists<scene_node>();
      auto bbSceneNode = bb.first->template GetComponentIfExists<scene_node>();

      const auto& aaLocal = 
        aa.first->template GetComponent<comp_type>()->GetTransformation();
      const auto& bbLocal = 
        bb.first->template GetComponent<comp_type>()->GetTransformation();

      const auto& aaTrans  = 
        aaSceneNode ? aaSceneNode->GetWorldTransform() : aaLocal;
      const auto& bbTrans  = 
        bbSceneNode ? bbSceneNode->GetWorldTransform() : bbLocal;

      const auto& aaPos   = aaTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();
      const auto& bbPos   = bbTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();

      if (aaPos[2] > bbPos[2]) { return true; }
      else { return false; }
    }

    typedef CompareFrontToBack_2D_T<core::use_reference> CompareFrontToBack_2D;
    typedef CompareFrontToBack_2D_T<core::use_pointee>   CompareFrontToBackPointer_2D;

    // ///////////////////////////////////////////////////////////////////////

    TLOC_DECL_ALGO_BINARY(CompareBackToFront_2D_T, const);
    TLOC_DEFINE_ALGO_BINARY(CompareBackToFront_2D_T, const)
    {
      typedef math_cs::Transform                    comp_type;
      typedef gfx_cs::SceneNode                     scene_node;

      const auto& aa = extract()(a);
      const auto& bb = extract()(b);

      auto aaSceneNode = aa.first->template GetComponentIfExists<scene_node>();
      auto bbSceneNode = bb.first->template GetComponentIfExists<scene_node>();

      const auto& aaLocal = 
        aa.first->template GetComponent<comp_type>()->GetTransformation();
      const auto& bbLocal = 
        bb.first->template GetComponent<comp_type>()->GetTransformation();

      const auto& aaTrans  = 
        aaSceneNode ? aaSceneNode->GetWorldTransform() : aaLocal;
      const auto& bbTrans  = 
        bbSceneNode ? bbSceneNode->GetWorldTransform() : bbLocal;

      const auto& aaPos   = aaTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();
      const auto& bbPos   = bbTrans.GetCol(3).ConvertTo<math_t::Vec3f32>();

      if (aaPos[2] < bbPos[2]) { return true; }
      else { return false; }
    }

    typedef CompareBackToFront_2D_T<core::use_reference> CompareBackToFront_2D;
    typedef CompareBackToFront_2D_T<core::use_pointee>   CompareBackToFrontPointer_2D;

  };

#define RENDER_SYSTEM_TEMPS   typename T_RendererSptr
#define RENDER_SYSTEM_PARAMS  T_RendererSptr
#define RENDER_SYSTEM_TYPE    typename RenderSystem_TI<RENDER_SYSTEM_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_TI

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    RenderSystem_TI(event_manager_ptr   a_eventMgr,
                    entity_manager_ptr  a_entityMgr,
                    register_type       a_registerTypes, 
                    BufferArg           a_debugName)

    : base_type(a_eventMgr, a_entityMgr, a_registerTypes, a_debugName)
    , m_sharedCam(nullptr)
    , m_renderer(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    ForceSortEntitiesByMaterial()
  {
    auto& activeEnts = DoGetActiveEntities();
    auto end         = activeEnts.end();

    core::sort(activeEnts.begin(), end, 
               MaterialCompareFromEntity(), core::sort_insertionsort());

    m_entPairsSegmentByMat.clear();

    auto currItr = activeEnts.begin();
    while (currItr != activeEnts.end())
    {
      material_sptr matPtr = currItr->first->template GetComponentIfExists<Material>();
      if (matPtr == nullptr)
      {
        ++currItr;
        continue;
      }
      
      auto endItr = currItr;
      if (matPtr)
      {
        endItr = core::find_if_not(currItr, end, MaterialCompare(matPtr));
        if (endItr != end)
        { ++endItr; } // we are always looking for past-the-end itr
      }

      m_entPairsSegmentByMat.push_back(core::MakePair(currItr, endItr));
      currItr = endItr;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    ForceSortEntitiesFrontToBack()
  {
    if (m_sharedCam)
    {
      if (m_entPairsSegmentByMat.size() > 0)
      {
        for (auto itr = m_entPairsSegmentByMat.begin(), itrEnd = m_entPairsSegmentByMat.end();
             itr != itrEnd; ++itr)
        {
          core::sort(itr->first, itr->second, 
                     CompareFrontToBack(m_sharedCam), core::sort_insertionsort());
        }
      }
      else
      {
        auto& activeEnts = DoGetActiveEntities();

        core::sort(activeEnts.begin(), activeEnts.end(),
                   CompareFrontToBack(m_sharedCam), core::sort_insertionsort());
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    ForceSortEntitiesBackToFront()
  {
    if (m_sharedCam)
    {
      auto& activeEnts = DoGetActiveEntities();
      
      core::sort(activeEnts.begin(), activeEnts.end(),
                 CompareBackToFront(m_sharedCam), core::sort_insertionsort());
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    ForceSortEntitiesFrontToBack_2D()
  {
    if (m_entPairsSegmentByMat.size() > 0)
    {
      for (auto itr = m_entPairsSegmentByMat.begin(), itrEnd = m_entPairsSegmentByMat.end();
           itr != itrEnd; ++itr)
      {
        core::sort(itr->first, itr->second, 
                   CompareFrontToBack_2D(), core::sort_insertionsort());
      }
    }
    else
    {
      auto& activeEnts = DoGetActiveEntities();

      core::sort(activeEnts.begin(), activeEnts.end(),
                 CompareFrontToBack_2D(), core::sort_insertionsort());
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    ForceSortEntitiesBackToFront_2D()
  {
    if (m_sharedCam)
    {
      auto& activeEnts = DoGetActiveEntities();
      
      core::sort(activeEnts.begin(), activeEnts.end(),
                 CompareBackToFront_2D(), core::sort_insertionsort());
    }
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    SortEntities()
  {
    if (IsSortingFrontToBackEnabled())
    { ForceSortEntitiesFrontToBack(); }
    else if (IsSortingBackToFrontEnabled())
    { ForceSortEntitiesBackToFront(); }
    else if (IsSortingFrontToBackEnabled_2D())
    { ForceSortEntitiesFrontToBack_2D(); }
    else if (IsSortingBackToFrontEnabled_2D())
    { ForceSortEntitiesBackToFront_2D(); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Post_Shutdown()
  { 
    if (this->IsSortingByMaterialEnabled())
    { ForceSortEntitiesByMaterial(); }
    else
    { m_entPairsSegmentByMat.clear(); }

    SortEntities();

    return base_type::Post_Shutdown(); 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  { 
    if (this->IsSortingByMaterialEnabled())
    { ForceSortEntitiesByMaterial(); }
    else
    { m_entPairsSegmentByMat.clear(); }

    SortEntities();

    return ErrorSuccess; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent)
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->HasComponent<gfx_cs::Material>() == false) 
      << "Entity " << *a_ent << " doesn't have a material.";

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    SetCamera(const_entity_ptr a_cameraEntity)
  {
    TLOC_ASSERT(a_cameraEntity->HasComponent<gfx_cs::Camera>(),
      "The passed entity is not a camera!");

    m_sharedCam = a_cameraEntity;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Post_ReInitialize()
  {
    if (this->IsSortingByMaterialEnabled())
    { ForceSortEntitiesByMaterial(); }
    else
    { m_entPairsSegmentByMat.clear(); }

    SortEntities();
    return base_type::Post_ReInitialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities( f64 a_deltaT )
  {
    if (m_sharedCam && m_sharedCam->HasComponent<gfx_cs::Camera>())
    {
      m_vpMatrix = m_sharedCam->GetComponent<Camera>()->GetViewProjRef();
      m_viewMatrix = m_sharedCam->GetComponent<Camera>()->GetViewMatrix();
      m_projMat = m_sharedCam->GetComponent<Camera>()->GetProjectionMatrix();
    }
    else
    {
      m_vpMatrix.MakeIdentity();
      m_viewMatrix.MakeIdentity();
      m_projMat.MakeIdentity();
    }

    base_type::Pre_ProcessActiveEntities(a_deltaT);
    SortEntities();
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class RenderSystem_TI<gfx_rend::renderer_depth32_sptr>;
  template class RenderSystem_TI<gfx_rend::renderer_depth64_sptr>;

};};};