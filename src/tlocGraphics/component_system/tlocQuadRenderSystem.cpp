#include "tlocQuadRenderSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>


namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef QuadRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  QuadRenderSystem::QuadRenderSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 Variadic<component_type, 1>(components::quad))
     , m_sharedCam(nullptr)
     , m_quadList(new vec3_cont_type(4))
  {
    m_vData.reset(new gl::Attribute());
    m_vData->SetName("a_vPos");

    m_uniVpMat.reset(new gl::Uniform());
    m_uniVpMat->SetName("u_mvp");

    m_tData = gl::attribute_sptr(new gl::Attribute());
    m_tData->SetName("a_tCoord");

    m_mvpOperator = gl::shader_operator_sptr(new gl::ShaderOperator());
  }

  void QuadRenderSystem::AttachCamera(const entity_type* a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    // Ensure that camera entity has the projection component
    TLOC_ASSERT( m_sharedCam->HasComponent(math_cs::components::projection),
      "The passed entity does not have the projection component!");
  }

  error_type QuadRenderSystem::Pre_Initialize()
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.MakeIdentity();

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(transform))
      {
        ComponentMapper<math::component_system::Transform> viewMatList =
          m_sharedCam->GetComponents(math::component_system::components::transform);
        TLOC_UNUSED(viewMatList);
      }

      if (m_sharedCam->HasComponent(projection))
      {
      }
    }

    return ErrorSuccess;
  }

  error_type QuadRenderSystem::InitializeEntity(const entity_manager*,
                                                const entity_type*)
  {
    return ErrorSuccess;
  }

  error_type QuadRenderSystem::ShutdownEntity(const entity_manager*,
                                              const entity_type*)
  { return ErrorSuccess; }

  void QuadRenderSystem::Pre_ProcessActiveEntities(f64)
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
        m_vpMatrix = projMat->GetFrustumRef().GetProjectionMatrix().Cast<matrix_type>();
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

  void QuadRenderSystem::ProcessEntity(const entity_manager*,
                                       const entity_type* a_ent,
                                       f64)
  {
    using namespace core::component_system;
    typedef math::component_system::Transform     transform_type;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  mat_type;
    typedef mat_type::shader_op_ptr               shader_op_ptr;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material))
    {
      gfx_cs::Material* matPtr = ent->GetComponent<gfx_cs::Material>();
      gfx_cs::Quad*     quadPtr = ent->GetComponent<gfx_cs::Quad>();

      //------------------------------------------------------------------------
      // Prepare the Quad

      typedef math::types::Rectf32    rect_type;
      using math::types::Mat4f32;
      using math::types::Vec4f32;

      const rect_type& rect = quadPtr->GetRectangleRef();

      (*m_quadList)[0] = vec3_type(rect.GetValue<rect_type::right>(),
                                   rect.GetValue<rect_type::top>(), 0);
      (*m_quadList)[1] = vec3_type(rect.GetValue<rect_type::left>(),
                                   rect.GetValue<rect_type::top>(), 0);
      (*m_quadList)[2] = vec3_type(rect.GetValue<rect_type::right>(),
                                   rect.GetValue<rect_type::bottom>(), 0);
      (*m_quadList)[3] = vec3_type(rect.GetValue<rect_type::left>(),
                                   rect.GetValue<rect_type::bottom>(), 0);

      math_cs::Transform* posPtr = ent->GetComponent<math_cs::Transform>();
      const Mat4f32& tMatrix = posPtr->GetTransformation().Cast<Mat4f32>();

      Mat4f32 tFinalMat = m_vpMatrix * tMatrix;

      // Generate the mvp matrix
      m_uniVpMat->SetValueAs(tFinalMat);

      m_mvpOperator->RemoveAllUniforms();
      m_mvpOperator->AddUniform(m_uniVpMat);

      const tl_size numVertices = m_quadList->size();

      m_vData->SetVertexArray(m_quadList, gl::p_shader_variable_ti::Shared() );

      shader_op_ptr so_quad(new shader_op_ptr::value_type());
      so_quad->AddAttribute(m_vData);

      if (ent->HasComponent(components::texture_coords))
      {
        typedef gfx_cs::TextureCoords::set_index    set_index;

        gfx_cs::TextureCoords* texCoordPtr =
          ent->GetComponent<gfx_cs::TextureCoords>();

        gfx_cs::TextureCoords::cont_type_sptr
          texCoordCont = texCoordPtr->GetCoords
          (set_index(texCoordPtr->GetCurrentSet()) );

        m_tData->SetVertexArray
          (texCoordCont, gl::p_shader_variable_ti::Shared() );

        so_quad->AddAttribute(m_tData);
      }

      //------------------------------------------------------------------------
      // Enable the shader

      mat_type::shader_prog_ptr sp = matPtr->GetShaderProgRef();

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if ( m_shaderPtr == nullptr ||
           m_shaderPtr.get() != sp.get() )
      {
        sp->Enable();
        m_shaderPtr = sp;

        typedef mat_type::shader_op_cont_const_itr  shader_op_itr;

        const mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

        for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
             itr != itrEnd; ++itr)
        {
          mat_type::shader_op_ptr so = *itr;

          so->EnableAllUniforms(*m_shaderPtr);
          so->EnableAllAttributes(*m_shaderPtr);
        }
      }

      // Add the mvp
      m_mvpOperator->PrepareAllUniforms(*m_shaderPtr);
      m_mvpOperator->EnableAllUniforms(*m_shaderPtr);

      so_quad->PrepareAllAttributes(*m_shaderPtr);
      so_quad->EnableAllAttributes(*m_shaderPtr);

      glDrawArrays(GL_TRIANGLE_STRIP, 0,
                   core_utils::CastNumber<GLsizei, tl_size>(numVertices));
    }
  }

  void QuadRenderSystem::Post_ProcessActiveEntities(f64)
  {
    // No materials/entities may have been loaded initially
    // (m_shaderPtr would have remained NULL)
    if (m_shaderPtr)
    {
      m_shaderPtr->Disable();
      m_shaderPtr.reset();
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  template class core_sptr::SharedPtr<QuadRenderSystem>;

};};};