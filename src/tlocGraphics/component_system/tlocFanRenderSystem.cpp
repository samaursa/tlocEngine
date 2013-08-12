#include "tlocFanRenderSystem.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocCamera.h>


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
  {
    //
    m_vertList->reserve(30);

    m_vData = gl::attribute_sptr(new gl::Attribute());
    m_vData->SetName("a_vPos");

    m_uniVpMat.reset(new gl::Uniform());
    m_uniVpMat->SetName("u_mvp");

    m_tData = gl::attribute_sptr(new gl::Attribute());
    m_tData->SetName("a_tCoord");

    m_mvpOperator = gl::shader_operator_sptr(new gl::ShaderOperator());
  }

  void FanRenderSystem::AttachCamera(const entity_type* a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    // Ensure that camera entity has the projection component
    TLOC_ASSERT( m_sharedCam->HasComponent(gfx_cs::components::camera),
      "The passed entity is not a camera!");
  }

  error_type FanRenderSystem::Pre_Initialize()
  { return ErrorSuccess; }

  error_type FanRenderSystem::InitializeEntity(const entity_manager*,
                                               const entity_type* )
  { return ErrorSuccess; }

  error_type FanRenderSystem::ShutdownEntity(const entity_manager*,
                                             const entity_type*)
  { return ErrorSuccess; }

  void FanRenderSystem::Pre_ProcessActiveEntities(f64)
  {
    if (m_sharedCam && m_sharedCam->HasComponent(gfx_cs::components::camera))
    {
      m_vpMatrix = m_sharedCam->GetComponent<Camera>()->GetViewProjRef();
    }
    else
    {
      m_vpMatrix.MakeIdentity();
    }
  }

  void FanRenderSystem::ProcessEntity(const entity_manager*,
                                      const entity_type* a_ent,
                                      f64)
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

      const circle_type& circ = fanPtr->GetEllipseRef();

      const size_type numSides = fanPtr->GetNumSides();
      const f32 angleInterval = 360.0f/numSides;

      math_cs::Transform* posPtr = ent->GetComponent<math_cs::Transform>();
      const Mat4f32& tMatrix = posPtr->GetTransformation().Cast<Mat4f32>();

      Mat4f32 tFinalMat = m_vpMatrix * tMatrix;

      m_uniVpMat->SetValueAs(tFinalMat);

      m_mvpOperator->RemoveAllUniforms();
      m_mvpOperator->AddUniform(m_uniVpMat);

      // Push the center vertex
      {
        Vec2f32 newCoord = circ.GetPosition();
        m_vertList->push_back
          (newCoord.ConvertTo<Vec3f32, p_tuple::overflow_zero>());
      }

      for (f32 i = 0; i <= numSides; ++i)
      {
        Vec2f32 newCoord = circ.GetCoord(degree_f32(angleInterval * i));
        m_vertList->push_back
          (newCoord.ConvertTo<Vec3f32, p_tuple::overflow_zero>() );
      }

      const tl_size numVertices = m_vertList->size();

      m_vData->SetVertexArray(m_vertList, gl::p_shader_variable_ti::Shared());

      shader_op_ptr so_fan = shader_op_ptr(new shader_op_ptr::value_type());
      so_fan->AddAttribute(m_vData);

      if (ent->HasComponent(components::texture_coords))
      {
        typedef gfx_cs::TextureCoords::set_index    set_index;

        gfx_cs::TextureCoords* texCoordPtr =
          ent->GetComponent<gfx_cs::TextureCoords>();

        if (texCoordPtr->GetNumSets())
        {
          gfx_cs::TextureCoords::cont_type_sptr
            texCoordCont = texCoordPtr->GetCoords
            (set_index(texCoordPtr->GetCurrentSet()) );

          m_tData->SetVertexArray
            (texCoordCont, gl::p_shader_variable_ti::Shared() );

          so_fan->AddAttribute(m_tData);
        }
      }

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

      // Add the mvp
      m_mvpOperator->PrepareAllUniforms(*m_shaderPtr);
      m_mvpOperator->EnableAllUniforms(*m_shaderPtr);

      so_fan->PrepareAllAttributes(*m_shaderPtr);
      so_fan->EnableAllAttributes(*m_shaderPtr);

      glDrawArrays(GL_TRIANGLE_FAN, 0,
                   core_utils::CastNumber<GLsizei, tl_size>(numVertices));
    }
  }

  void FanRenderSystem::Post_ProcessActiveEntities(f64)
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