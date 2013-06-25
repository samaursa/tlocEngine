#include "tlocMeshRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define MESH_RENDER_SYSTEM_TEMPS    typename Mesh_T
#define MESH_RENDER_SYSTEM_PARAMS   Mesh_T
#define MESH_RENDER_SYSTEM_TYPE     typename MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>

  template <MESH_RENDER_SYSTEM_TEMPS>
  MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    MeshRenderSystem_T(event_manager_sptr a_eventMgr,
                     entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>
                (mesh_type::vertex_storage_policy::k_component_id) )
    , m_sharedCam(nullptr)
  {
    m_uniVpMat.reset(new gl::Uniform());
    m_uniVpMat->SetName("u_mvp");

    m_mvpOperator.reset(new gl::ShaderOperator());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    AttachCamera(const entity_type* a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    TLOC_ASSERT(m_sharedCam->HasComponent(math_cs::components::projection),
      "The passed entity does not have the projection component");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    InitializeEntity(const entity_manager*, const entity_type* a_ent)
  {
    mesh_type* meshType = a_ent->GetComponent<mesh_type>();

    gl::attribute_sptr posAttr = meshType->GetPosAttribute();
    gl::attribute_sptr normAttr = meshType->GetNormAttribute();
    gl::attribute_sptr tcoordAttr = meshType->GetTCoordAttribute();

    posAttr->SetVertexArray(meshType->GetPositions(),
                            gl::p_shader_variable_ti::Shared());
    posAttr->SetName("a_vPos");

    normAttr->SetVertexArray(meshType->GetNormals(),
                            gl::p_shader_variable_ti::Shared());
    normAttr->SetName("a_vNorm");

    tcoordAttr->SetVertexArray(meshType->GetTCoords(),
                            gl::p_shader_variable_ti::Shared());
    tcoordAttr->SetName("a_tCoord");

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ShutdownEntity(const entity_manager*, const entity_type*)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities(f64)
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.MakeIdentity();
    m_vpMatrix.MakeIdentity();

    // vMVP, but since we are doing column major, it becomes PVMv

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(projection))
      {
        math_cs::Projection* projMat =
          m_sharedCam->GetComponent<math_cs::Projection>();
        m_vpMatrix =
          projMat->GetFrustumRef().GetProjectionMatrix().Cast<matrix_type>();
      }

      if (m_sharedCam->HasComponent(transform))
      {
        math_cs::Transform* vMat =
          m_sharedCam->GetComponent<math_cs::Transform>();
        math_cs::Transform vMatInv = vMat->Invert();
        viewMat = vMatInv.GetTransformation().Cast<matrix_type>();
      }
    }

    m_vpMatrix.Mul(viewMat);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ProcessEntity(const entity_manager* , const entity_type* a_ent, f64)
  {
    using namespace core_cs;
    using math::types::Mat4f32;

    typedef math_cs::Transform        transform_type;
    typedef gfx_cs::Material          mat_type;
    typedef mat_type::shader_op_ptr   shader_op_ptr;
    typedef core_sptr::
            SharedPtr<Mesh_T>         mesh_ptr;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material) == false)
    { return; }

    gfx_cs::Material*   matPtr = ent->GetComponent<gfx_cs::Material>();
    math_cs::Transform* posPtr = ent->GetComponent<math_cs::Transform>();
    mesh_type*          meshPtr = ent->GetComponent<Mesh_T>();


    const Mat4f32& tMatrix =
      posPtr->GetTransformation().Cast<Mat4f32>();

    Mat4f32 tFinalMat = m_vpMatrix * tMatrix;

    // Generate the mvp matrix
    m_uniVpMat->SetValueAs(tFinalMat);

    m_mvpOperator->RemoveAllUniforms();
    m_mvpOperator->AddUniform(m_uniVpMat);

    const tl_size numVertices = meshPtr->size();

    shader_op_ptr so_mesh(new shader_op_ptr::value_type());
    so_mesh->AddAttribute(meshPtr->GetPosAttribute());
    so_mesh->AddAttribute(meshPtr->GetNormAttribute());
    so_mesh->AddAttribute(meshPtr->GetTCoordAttribute());

    TLOC_UNUSED_2(matPtr, numVertices);

    mat_type::shader_prog_ptr sp = matPtr->GetShaderProgRef();

    if (m_shaderPtr == nullptr ||
        m_shaderPtr.get() != sp.get())
    {
      sp->Enable();
      m_shaderPtr = sp;

      typedef mat_type::shader_op_cont_const_itr    shader_op_itr;

      const mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

      for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
        itr != itrEnd; ++itr)
      {
        mat_type::shader_op_ptr so = *itr;

        so->EnableAllUniforms(*m_shaderPtr);
        so->EnableAllAttributes(*m_shaderPtr);
      }
    }

    m_mvpOperator->PrepareAllUniforms(*m_shaderPtr);
    m_mvpOperator->EnableAllUniforms(*m_shaderPtr);

    so_mesh->PrepareAllAttributes(*m_shaderPtr);
    so_mesh->EnableAllAttributes(*m_shaderPtr);

    glDrawArrays(GL_TRIANGLES, 0,
                 core_utils::CastNumber<GLsizei, tl_size>(numVertices));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Post_ProcessActiveEntities(f64)
  { }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class MeshRenderSystem_T<Mesh>;

};};};