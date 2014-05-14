#include "tlocMeshRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

#define MESH_RENDER_SYSTEM_TEMPS    typename Mesh_T
#define MESH_RENDER_SYSTEM_PARAMS   Mesh_T
#define MESH_RENDER_SYSTEM_TYPE     typename MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    MeshRenderSystem_T(event_manager_ptr a_eventMgr,
                       entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>
                (mesh_type::vertex_storage_policy::k_component_id) )
  {
    m_uniVpMat->SetName("u_mvp");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent)
  {
    base_type::InitializeEntity(a_ent);

    mesh_ptr meshType = a_ent->GetComponent<mesh_type>();

    gl::attribute_vso posAttr, normAttr, tcoordAttr;

    { // Positions
      posAttr->SetVertexArray(meshType->GetPositions(),
                              gl::p_shader_variable_ti::Pointer());
      posAttr->SetName("a_vPos");
      meshType->SetPosAttribute(*posAttr);
    }

    // Normals
    if (meshType->IsNormalsEnabled())
    {
      normAttr->SetVertexArray(meshType->GetNormals(),
                              gl::p_shader_variable_ti::Pointer());
      normAttr->SetName("a_vNorm");
      meshType->SetNormAttribute(*normAttr);
    }

    // TexCoords
    if (meshType->IsTexCoordsEnabled())
    {
      tcoordAttr->SetVertexArray(meshType->GetTCoords(),
                              gl::p_shader_variable_ti::Pointer());
      tcoordAttr->SetName("a_tCoord");
      meshType->SetTCoordAttribute(*tcoordAttr);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    using namespace core_cs;
    using math::types::Mat4f32;

    typedef math_cs::Transform        transform_type;
    typedef gfx_cs::Material          mat_type;
    typedef mat_type::shader_op_ptr   shader_op_ptr;

    if (a_ent->HasComponent(components::material) == false)
    { return; }

    gfx_cs::material_sptr   matPtr = a_ent->GetComponent<gfx_cs::Material>();
    math_cs::transform_sptr posPtr = a_ent->GetComponent<math_cs::Transform>();
    mesh_ptr                meshPtr = a_ent->GetComponent<Mesh_T>();

    Mat4f32 tMatrix;
    if (a_ent->HasComponent(components::scene_node))
    { tMatrix = a_ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
    else
    { tMatrix = posPtr->GetTransformation().Cast<Mat4f32>(); }

    Mat4f32 tFinalMat = GetViewProjectionMatrix() * tMatrix;

    // Generate the mvp matrix
    m_uniVpMat->SetValueAs(tFinalMat);

    m_mvpOperator->RemoveAllUniforms();
    m_mvpOperator->AddUniform(*m_uniVpMat);

    const tl_size numVertices = meshPtr->size();

    so_mesh->RemoveAllAttributes();
    so_mesh->AddAttribute(*meshPtr->GetPosAttribute());

    if (meshPtr->IsTexCoordsEnabled())
    { so_mesh->AddAttribute(*meshPtr->GetTCoordAttribute()); }

    if (meshPtr->IsNormalsEnabled())
    { so_mesh->AddAttribute(*meshPtr->GetNormAttribute()); }

    const_shader_prog_ptr sp = matPtr->GetShaderProg();

    if ( m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get())
    {
      if (m_shaderPtr)
      { m_shaderPtr->Disable(); }

      if (sp->Enable().Failed())
      {
        TLOC_LOG_GFX_WARN() << "ShaderProgram #" << sp->GetHandle()
          << " could not be enabled.";
        return;
      }

      m_shaderPtr = sp;

      typedef mat_type::shader_op_cont::const_iterator    shader_op_itr;

      const mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

      for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
        itr != itrEnd; ++itr)
      {
        gl::const_shader_operator_vptr so = itr->get();

        so->EnableAllUniforms(*m_shaderPtr);
        so->EnableAllAttributes(*m_shaderPtr);
      }
    }

    if (m_mvpOperator->PrepareAllUniforms(*m_shaderPtr).Succeeded())
    { m_mvpOperator->EnableAllUniforms(*m_shaderPtr); }

    if (so_mesh->PrepareAllAttributes(*m_shaderPtr).Succeeded())
    { so_mesh->EnableAllAttributes(*m_shaderPtr); }

    glDrawArrays(GL_TRIANGLES, 0,
                 core_utils::CastNumber<GLsizei, tl_size>(numVertices));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Post_ProcessActiveEntities(f64)
  {
    m_shaderPtr.reset();

    base_type::Post_ProcessActiveEntities(f64());
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class MeshRenderSystem_T<Mesh>;

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MeshRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MeshRenderSystem);