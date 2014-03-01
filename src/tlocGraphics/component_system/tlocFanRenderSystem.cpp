#include "tlocFanRenderSystem.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
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
  // FanRenderSystem

  FanRenderSystem::
    FanRenderSystem(event_manager_sptr a_eventMgr,
                    entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::fan))
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    FanRenderSystem::
    InitializeEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    FanRenderSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    FanRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    using namespace core::component_system;
    using math_t::degree_f32;

    typedef gfx_cs::Material::shader_op_ptr          shader_op_ptr;

    if (a_ent->HasComponent(components::material))
    {
      gfx_cs::material_vptr matPtr = a_ent->GetComponent<gfx_cs::Material>();
      gfx_cs::fan_vptr      fanPtr = a_ent->GetComponent<gfx_cs::Fan>();

      //------------------------------------------------------------------------
      // Prepare the Fan

      typedef math::types::Circlef32 circle_type;
      using namespace math::types;

      m_vertList->clear();

      const circle_type& circ = fanPtr->GetEllipseRef();

      const size_type numSides = fanPtr->GetNumSides();
      const f32 angleInterval = 360.0f/numSides;

      math_cs::transform_vptr posPtr = a_ent->GetComponent<math_cs::Transform>();

      Mat4f32 tMatrix;
      if (a_ent->HasComponent(components::scene_node))
      { tMatrix = a_ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
      else
      { tMatrix = posPtr->GetTransformation().Cast<Mat4f32>(); }

      Mat4f32 tFinalMat = GetViewProjectionMatrix() * tMatrix;

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

      if (a_ent->HasComponent(components::texture_coords))
      {
        typedef gfx_cs::TextureCoords::set_index    set_index;

        gfx_cs::texture_coords_vptr texCoordPtr =
          a_ent->GetComponent<gfx_cs::TextureCoords>();

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    FanRenderSystem::
    Post_ProcessActiveEntities(f64)
  {
    // No materials/entities may have been loaded initially
    // (m_shaderPtr would have remained NULL)
    if (m_shaderPtr)
    {
      m_shaderPtr->Disable();
      m_shaderPtr.reset();
    }

    base_type::Post_ProcessActiveEntities(f64());
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(FanRenderSystem);