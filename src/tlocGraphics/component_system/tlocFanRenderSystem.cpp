#include "tlocFanRenderSystem.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocMaterial.h>


namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef FanRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  FanRenderSystem::FanRenderSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 Variadic<component_type, 1>(components::fan))
     , m_sharedCam(nullptr)
     , m_vertList(new vec3_cont_type())
     , m_texList(new vec2_cont_type())
  {
    //
    m_vertList->reserve(30);
    m_texList->reserve(30);

    m_vData = gl::attribute_sptr(new gl::Attribute());
    m_vData->SetName("a_vPos");

    m_tData = gl::attribute_sptr(new gl::Attribute());
    m_tData->SetName("a_tCoord");

    m_projectionOperator = gl::shader_operator_sptr(new gl::ShaderOperator());
  }

  void FanRenderSystem::AttachCamera(const entity_type* a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    // Ensure that camera entity has the projection component
    TLOC_ASSERT( m_sharedCam->HasComponent(math_cs::components::projection),
      "The passed entity does not have the projection component!");
  }

  error_type FanRenderSystem::Pre_Initialize()
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.Identity();

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(transform))
      { }

      if (m_sharedCam->HasComponent(projection))
      { }
    }

    return ErrorSuccess;
  }

  error_type FanRenderSystem::InitializeEntity(const entity_manager*,
                                               const entity_type* )
  { return ErrorSuccess; }

  error_type FanRenderSystem::ShutdownEntity(const entity_manager*,
                                             const entity_type*)
  { return ErrorSuccess; }

  void FanRenderSystem::Pre_ProcessActiveEntities()
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
        math_cs::Projection* projMat =
          m_sharedCam->GetComponent<math_cs::Projection>();
        m_vpMatrix = projMat->GetFrustumRef().GetProjectionMatrix().Cast<matrix_type>();
      }

      if (m_sharedCam->HasComponent(transform))
      {
        math_cs::Transform* vMat =
          m_sharedCam->GetComponent<math_cs::Transform>();
        viewMat = vMat->GetTransformation().Cast<matrix_type>();
      }
    }

    m_vpMatrix.Mul(viewMat);

    gl::uniform_sptr vpMat(new gl::Uniform());
    vpMat->SetName("u_mvp").SetValueAs(m_vpMatrix);

    m_projectionOperator->RemoveAllUniforms();
    m_projectionOperator->AddUniform(vpMat);
  }

  void FanRenderSystem::ProcessEntity(const entity_manager*,
                                      const entity_type* a_ent)
  {
    using namespace core::component_system;
    using math_t::degree_f32;

    typedef gfx_cs::Material::shader_op_ptr          shader_op_ptr;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material))
    {
      gfx_cs::Material* matPtr = ent->GetComponent<gfx_cs::Material>();

      gfx_cs::Fan* fanPtr = ent->GetComponent<gfx_cs::Fan>();

      //------------------------------------------------------------------------
      // Prepare the Fan

      typedef math::types::Circlef32 circle_type;
      using namespace math::types;

      m_vertList->clear();
      m_texList->clear();

      const circle_type& circ = fanPtr->GetEllipseRef();

      const size_type numSides = fanPtr->GetNumSides();
      const f32 angleInterval = 360.0f/numSides;

      math_cs::Transform* posPtr = ent->GetComponent<math_cs::Transform>();
      const Mat4f32& tMatrix = posPtr->GetTransformation().Cast<Mat4f32>();

      // Push the center vertex
      {
        Vec2f32 newCoord = circ.GetPosition();
        Vec4f32 coord4f = newCoord.ConvertTo<Vec4f32, p_tuple::overflow_zero>();
        coord4f[3] = 1;
        coord4f = tMatrix * coord4f;
        m_vertList->push_back(coord4f.ConvertTo<Vec3f32>());
      }

      for (f32 i = 0; i <= numSides; ++i)
      {
        Vec2f32 newCoord = circ.GetCoord(degree_f32(angleInterval * i));
        Vec4f32 coord4f =
          newCoord.ConvertTo<Vec4f32, p_tuple::overflow_zero>();

        coord4f[3] = 1;
        coord4f = tMatrix * coord4f ;

        m_vertList->push_back(coord4f .ConvertTo<Vec3f32>());
      }

      // Create the texture co-ordinates
      circle_type circForTex;
      circForTex.SetRadius(0.5f);
      m_texList->push_back(Vec2f32(0.5f, 0.5f)); // Push the center vertex
      for (f32 i = 0; i <= numSides; ++i)
      {
        Vec2f32 newTexCoord = circForTex.GetCoord(degree_f32(angleInterval * i));
        newTexCoord += Vec2f32(0.5f, 0.5f); // tex co-ordinates start from 0, 0
        m_texList->push_back(newTexCoord);
      }

      const tl_size numVertices = m_vertList->size();

      m_vData->SetVertexArray(m_vertList, gl::p_shader_variable_ti::Shared());
      m_tData->SetVertexArray(m_texList, gl::p_shader_variable_ti::Shared());

      shader_op_ptr so_fan = shader_op_ptr(new shader_op_ptr::value_type());
      so_fan->AddAttribute(m_vData);
      so_fan->AddAttribute(m_tData);

      //------------------------------------------------------------------------
      // Enable the shader

      gfx_cs::Material::shader_prog_ptr sp = matPtr->GetShaderProgRef();

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if ( m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get() )
      {
        if (m_shaderPtr)
        { m_shaderPtr->Disable(); }

        sp->Enable();
        m_shaderPtr = sp;

        // Add the mvp
        m_projectionOperator->PrepareAllUniforms(*m_shaderPtr);
        m_projectionOperator->EnableAllUniforms(*m_shaderPtr);

      typedef gfx_cs::Material::shader_op_cont::const_iterator     const_itr_type;
      const gfx_cs::Material::shader_op_cont& cont = matPtr->GetShaderOperators();

      for (const_itr_type itr = cont.begin(), itrEnd = cont.end();
           itr != itrEnd; ++itr)
      {
        gfx_cs::Material::shader_op_ptr so = *itr;

          so->EnableAllUniforms(*m_shaderPtr);
          so->EnableAllAttributes(*m_shaderPtr);
        }
      }

      so_fan->PrepareAllAttributes(*m_shaderPtr);
      so_fan->EnableAllAttributes(*m_shaderPtr);

      glDrawArrays(GL_TRIANGLE_FAN, 0,
                   core_utils::CastNumber<GLsizei, tl_size>(numVertices));
    }
  }

  void FanRenderSystem::Post_ProcessActiveEntities()
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

  template class core_sptr::SharedPtr<FanRenderSystem>;

};};};