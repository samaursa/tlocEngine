#include "tlocRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/tlocAlgorithms.h>

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

    TLOC_DECL_ALGO_BINARY(MaterialCompareFromEntity_T, const);
    TLOC_DEFINE_ALGO_BINARY(MaterialCompareFromEntity_T, const)
    {
      typedef gfx_cs::material_sptr                         ptr_type;
      typedef core_cs::EntitySystemBase::entity_count_pair  entity_ptr_type;
      typedef ptr_type::value_type                          comp_type;

      const auto& aa = extract()(a);
      const auto& bb = extract()(b);

      if (aa.first->HasComponent<comp_type>() == false)
      { return true; }
      else if (bb.first->HasComponent<comp_type>() == false)
      { return false; }

      ptr_type first = aa.first->GetComponent<comp_type>();
      ptr_type second = bb.first->GetComponent<comp_type>();

      return first < second;
    }

    typedef MaterialCompareFromEntity_T<core::use_reference> MaterialCompareFromEntity;
    typedef MaterialCompareFromEntity_T<core::use_pointee>   MaterialCompareFromEntityPointer;

  };

#define RENDER_SYSTEM_TEMPS   typename T_RendererSptr
#define RENDER_SYSTEM_PARAMS  T_RendererSptr
#define RENDER_SYSTEM_TYPE    typename RenderSystem_TI<RENDER_SYSTEM_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_TI

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    SortEntities()
  {
    if (IsSortingByMaterialEnabled())
    {
      core::sort(DoGetActiveEntities().begin(), DoGetActiveEntities().end(), 
                 MaterialCompareFromEntity(), core::sort_insertionsort());
    }
  }

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
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  { 
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
      << "Entity (" << a_ent->GetDebugName() << ") doesn't have a material.";

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
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class RenderSystem_TI<gfx_rend::renderer_depth32_sptr>;
  template class RenderSystem_TI<gfx_rend::renderer_depth64_sptr>;

};};};