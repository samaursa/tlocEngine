#include "tlocQuadRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocCamera.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef QuadRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  QuadRenderSystem::
    QuadRenderSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 Variadic<component_type, 1>(components::quad))
  {
    m_quadList->resize(4);

    m_vData->SetName("a_vPos");
    m_uniVpMat->SetName("u_mvp");

    m_tData.push_back(gl::attribute_vso() );
    m_tData.back()->SetName("a_tCoord");

    m_tData.push_back(gl::attribute_vso() );
    m_tData.back()->SetName("a_tCoord2");

    m_tData.push_back(gl::attribute_vso() );
    m_tData.back()->SetName("a_tCoord3");

    m_tData.push_back(gl::attribute_vso() );
    m_tData.back()->SetName("a_tCoord4");
  }

  error_type QuadRenderSystem::InitializeEntity(entity_ptr)
  { return ErrorSuccess; }

  error_type QuadRenderSystem::ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  void QuadRenderSystem::ProcessEntity(entity_ptr a_ent, f64)
  {
    using namespace core::component_system;
    typedef math::component_system::Transform     transform_type;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  mat_type;

    if (a_ent->HasComponent(components::material))
    {
      gfx_cs::material_vptr matPtr = a_ent->GetComponent<gfx_cs::Material>();
      gfx_cs::quad_vptr     quadPtr = a_ent->GetComponent<gfx_cs::Quad>();

      //------------------------------------------------------------------------
      // Prepare the Quad

      typedef math::types::Rectf32    rect_type;
      using math::types::Mat4f32;
      using math::types::Vec4f32;

      const rect_type& rect = quadPtr->GetRectangleRef();

      m_quadList->at(0) = vec3_type(rect.GetValue<rect_type::right>(),
                                    rect.GetValue<rect_type::top>(), 0);
      m_quadList->at(1) = vec3_type(rect.GetValue<rect_type::left>(),
                                    rect.GetValue<rect_type::top>(), 0);
      m_quadList->at(2) = vec3_type(rect.GetValue<rect_type::right>(),
                                    rect.GetValue<rect_type::bottom>(), 0);
      m_quadList->at(3) = vec3_type(rect.GetValue<rect_type::left>(),
                                    rect.GetValue<rect_type::bottom>(), 0);

      math_cs::transform_vptr posPtr = a_ent->GetComponent<math_cs::Transform>();

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

      const tl_size numVertices = m_quadList->size();

      m_vData->SetVertexArray(m_quadList.get(), gl::p_shader_variable_ti::Pointer() );

      m_so_quad->RemoveAllAttributes();
      m_so_quad->AddAttribute(*m_vData);

      if (a_ent->HasComponent(components::texture_coords))
      {
        typedef gfx_cs::TextureCoords::set_index    set_index;

        const tl_size numTexCoords =
          a_ent->GetComponents(gfx_cs::TextureCoords::k_component_type).size();

        TLOC_ASSERT(numTexCoords <= 4,
          "QuadSystem does not support more than 4 texture coordinates");

        for (tl_size i = 0; i < numTexCoords; ++i)
        {
          gfx_cs::texture_coords_vptr texCoordPtr =
            a_ent->GetComponent<gfx_cs::TextureCoords>(i);

          if (texCoordPtr && texCoordPtr->GetNumSets())
          {
            gfx_cs::TextureCoords::cont_type_ptr
              texCoordCont = texCoordPtr->GetCoords
              (set_index(texCoordPtr->GetCurrentSet()) );

            m_tData[i]->SetVertexArray(texCoordCont,
                                       gl::p_shader_variable_ti::Pointer() );

            m_so_quad->AddAttribute(*m_tData[i]);
          }
        }
      }

      //------------------------------------------------------------------------
      // Enable the shader

      const_shader_prog_ptr sp = matPtr->GetShaderProg();

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if ( m_shaderPtr == nullptr ||
           m_shaderPtr.get() != sp.get() )
      {
        sp->Enable();
        m_shaderPtr = sp;

        typedef mat_type::shader_op_cont::const_iterator  shader_op_itr;

        const mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

        for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
             itr != itrEnd; ++itr)
        {
          gl::const_shader_operator_vptr so = itr->get();

          so->EnableAllUniforms(*m_shaderPtr);
          so->EnableAllAttributes(*m_shaderPtr);
        }
      }

      // Add the mvp
      m_mvpOperator->PrepareAllUniforms(*m_shaderPtr);
      m_mvpOperator->EnableAllUniforms(*m_shaderPtr);

      m_so_quad->PrepareAllAttributes(*m_shaderPtr);
      m_so_quad->EnableAllAttributes(*m_shaderPtr);

      TLOC_UNUSED(numVertices);
      glDrawArrays(GL_TRIANGLE_STRIP, 0,
                   core_utils::CastNumber<gfx_t::gl_sizei, tl_size>(numVertices));
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

    base_type::Post_ProcessActiveEntities(f64());
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(QuadRenderSystem);