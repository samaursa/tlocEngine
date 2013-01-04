#include "tlocQuadRenderSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocMath/data_types/tlocRectangle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocProjectionComponent.h>


namespace tloc { namespace graphics { namespace component_system {

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef QuadRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  QuadRenderSystem::QuadRenderSystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 core::Variadic<component_type, 1>(components::quad))
     , m_sharedCam(nullptr)
  {
    m_quadList.resize(4); // number of vertexes a quad has

    m_vData = gl::AttributePtr(new gl::Attribute());
    m_vData->SetName("a_vPos");

    m_projectionOperator = gl::ShaderOperatorPtr(new gl::ShaderOperator());
  }

  void QuadRenderSystem::AttachCamera(const entity_type* a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    // Ensure that camera entity has the projection component
    TLOC_ASSERT( m_sharedCam->HasComponent(components::projection),
      "The passed entity does not have the projection component!");
  }

  error_type QuadRenderSystem::Pre_Initialize()
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.Identity();

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(transform))
      {
        ComponentMapper<math::component_system::Transform> viewMatList =
          m_sharedCam->GetComponents(math::component_system::components::transform);
      }

      if (m_sharedCam->HasComponent(projection))
      {
      }
    }

    return ErrorSuccess();
  }

  error_type QuadRenderSystem::InitializeEntity(entity_manager*,
    entity_type* a_ent)
  {
    TLOC_UNUSED(a_ent);
    return ErrorSuccess();
  }

  error_type QuadRenderSystem::ShutdownEntity(entity_manager*, entity_type*)
  { return ErrorSuccess(); }

  void QuadRenderSystem::Pre_ProcessActiveEntities()
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.Identity();
    m_vpMatrix.Identity();

    // vMVP, but since we are doing column major, it becomes PVMv

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(projection))
      {
        ComponentMapper<graphics::component_system::Projection> projMatList =
          m_sharedCam->GetComponents(graphics::component_system::components::projection);
        m_vpMatrix = projMatList[0].GetFrustumRef().GetProjectionMatrix();
      }

      if (m_sharedCam->HasComponent(transform))
      {
        ComponentMapper<math::component_system::Transform> viewMatList =
          m_sharedCam->GetComponents(math::component_system::components::transform);
        viewMat = viewMatList[0].GetTransformation();
      }
    }

    m_vpMatrix.Mul(viewMat);

    gl::UniformPtr vpMat(new gl::Uniform());
    vpMat->SetName("u_mvp").SetValueAs(m_vpMatrix);

    m_projectionOperator->RemoveAllUniforms();
    m_projectionOperator->AddUniform(vpMat);
  }

  void QuadRenderSystem::ProcessEntity(entity_manager*, entity_type* a_ent)
  {
    TLOC_UNUSED(a_ent);
    using namespace core::component_system;
    typedef math::component_system::Transform     transform_type;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  material_type;
    typedef material_type::shader_op_ptr          shader_op_ptr;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material))
    {

      ComponentMapper<material_type> matArr =
        ent->GetComponents(components::material);
      material_type& mat = matArr[0];

      ComponentMapper<quad_type> quad = ent->GetComponents(components::quad);
      Quad& q = quad[0];

      //------------------------------------------------------------------------
      // Prepare the Quad

      typedef math::types::Rectf32    rect_type;

      const rect_type& rect = q.GetRectangleRef();

      m_quadList[0] = vec3_type(rect.GetValue<rect_type::right>(),
                                rect.GetValue<rect_type::top>(), 0);
      m_quadList[1] = vec3_type(rect.GetValue<rect_type::left>(),
                                rect.GetValue<rect_type::top>(), 0);
      m_quadList[2] = vec3_type(rect.GetValue<rect_type::right>(),
                                rect.GetValue<rect_type::bottom>(), 0);
      m_quadList[3] = vec3_type(rect.GetValue<rect_type::left>(),
                                rect.GetValue<rect_type::bottom>(), 0);

      ComponentMapper<transform_type> posList =
        ent->GetComponents(math::component_system::components::transform);
      math::component_system::Transform& pos = posList[0];

      // Change the position of the quad
      const math::Mat4f32& tMatrix = pos.GetTransformation();

      math::Vec4f32 qPos;
      for (int i = 0; i < 4; ++i)
      {
        qPos = m_quadList[i].ConvertTo<math::Vec4f32>();
        qPos = tMatrix * qPos;

        m_quadList[i].ConvertFrom(qPos);
      }

      m_vData->SetVertexArray(m_quadList, gl::p_shader_variable_ti::CopyArray() );

      shader_op_ptr so_quad = shader_op_ptr(new shader_op_ptr::value_type());
      so_quad->AddAttribute(m_vData);


      //------------------------------------------------------------------------
      // Enable the shader

      material_type::shader_prog_ptr sp = mat.GetShaderProgRef();

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if ( !m_shaderPtr && m_shaderPtr.get() != sp.get() )
      {
        sp->Enable();
        m_shaderPtr = sp;
      }

      material_type::shader_op_cont::iterator itr, itrEnd;
      material_type::shader_op_cont& cont = mat.DoGetShaderOpContainerRef();

      for (itr = cont.begin(), itrEnd = cont.end(); itr != itrEnd; ++itr)
      {
        material_type::shader_op_ptr so = *itr;

        so->EnableAllUniforms(*m_shaderPtr);
        so->EnableAllUniforms(*m_shaderPtr);
      }

      so_quad->PrepareAllAttributes(*m_shaderPtr);
      so_quad->EnableAllAttributes(*m_shaderPtr);

      // Add the mvp
      m_projectionOperator->PrepareAllUniforms(*m_shaderPtr);
      m_projectionOperator->EnableAllUniforms(*m_shaderPtr);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      //sp->Disable();
    }
  }

  void QuadRenderSystem::Post_ProcessActiveEntities()
  {
    m_shaderPtr->Disable();
    m_shaderPtr.reset();
  }

};};};