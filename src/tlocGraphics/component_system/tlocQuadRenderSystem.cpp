#include "tlocQuadRenderSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

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
    m_quadList.reserve(4); // number of vertexes a quad has
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
    //using namespace core::component_system;
    //typedef graphics::component_system::Quad      quad_type;
    //typedef graphics::component_system::Material  material_type;
    //typedef material_type::shader_op_ptr          shader_op_ptr;

    //const entity_type* ent = a_ent;

    //// TODO: This is also where you enable the shader, add attributes and
    //// uniforms, and then cache their locations for next use

    ////if (ent->HasComponent(components::material))
    ////{
    ////  ComponentMapper<material_type> matArr =
    ////    ent->GetComponents(components::material);
    ////  material_type& mat = matArr[0];

    ////  //m_quadList.clear();
    ////  //m_quadList.push_back(q.GetVertex<Quad::vert_ne>().GetPosition());
    ////  //m_quadList.push_back(q.GetVertex<Quad::vert_nw>().GetPosition());
    ////  //m_quadList.push_back(q.GetVertex<Quad::vert_se>().GetPosition());
    ////  //m_quadList.push_back(q.GetVertex<Quad::vert_sw>().GetPosition());

    ////  //gl::AttributePtr a_vData = gl::AttributePtr(new gl::Attribute());
    ////  //a_vData->SetName("a_vPos").SetVertexArray
    ////  //  (m_quadList, gl::p_shader_variable_ti::CopyArray() );

    ////  //shader_op_ptr so = shader_op_ptr(new shader_op_ptr::value_type());
    ////  //so->AddAttribute(a_vData);

    ////  mat.DoGetShaderOpContainerRef().push_back(so);
    ////}

    return ErrorSuccess();
  }

  error_type QuadRenderSystem::ShutdownEntity(entity_manager*, entity_type*)
  { return ErrorSuccess(); }

  void QuadRenderSystem::ProcessEntity(entity_manager*, entity_type* a_ent)
  {
    using namespace core::component_system;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  material_type;
    typedef material_type::shader_op_ptr          shader_op_ptr;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material))
    {

      ComponentMapper<material_type> matArr =
        ent->GetComponents(components::material);
      material_type& mat = matArr[0];

      //------------------------------------------------------------------------
      // Prepare the Quad

      ComponentMapper<quad_type> quad = ent->GetComponents(components::quad);
      Quad& q = quad[0];

      m_quadList.clear();
      m_quadList.push_back(q.GetVertex<Quad::vert_ne>().GetPosition());
      m_quadList.push_back(q.GetVertex<Quad::vert_nw>().GetPosition());
      m_quadList.push_back(q.GetVertex<Quad::vert_se>().GetPosition());
      m_quadList.push_back(q.GetVertex<Quad::vert_sw>().GetPosition());

      gl::AttributePtr a_vData = gl::AttributePtr(new gl::Attribute());
      a_vData->SetName("a_vPos").SetVertexArray
        (m_quadList, gl::p_shader_variable_ti::CopyArray() );

      shader_op_ptr so_quad = shader_op_ptr(new shader_op_ptr::value_type());
      so_quad->AddAttribute(a_vData);

      //------------------------------------------------------------------------
      // Enable the shader

      material_type::shader_prog_ptr sp = mat.GetShaderProgRef();

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if ( m_shaderPtr.IsNull() || m_shaderPtr.Expose() != sp.Expose() )
      {
        sp->Enable();
        m_shaderPtr = sp;
      }

      material_type::shader_op_cont::iterator itr, itrEnd;
      material_type::shader_op_cont& cont = mat.DoGetShaderOpContainerRef();

      for (itr = cont.begin(), itrEnd = cont.end(); itr != itrEnd; ++itr)
      {
        material_type::shader_op_ptr so = *itr;

        so->LoadAllUniforms(*m_shaderPtr);
        so->LoadAllAttributes(*m_shaderPtr);
      }

      so_quad->LoadAllUniforms(*m_shaderPtr);
      so_quad->LoadAllAttributes(*m_shaderPtr);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      //sp->Disable();
    }
  }

  void QuadRenderSystem::Post_ProcessActiveEntities()
  {
    m_shaderPtr = shader_prog_ptr();
  }

};};};