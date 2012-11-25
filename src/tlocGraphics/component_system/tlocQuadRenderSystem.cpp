#include "tlocQuadRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace component_system {

  QuadRenderSystem::QuadRenderSystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::quad))
  { }

  QuadRenderSystem::error_type QuadRenderSystem::Initialize()
  {
    using namespace core::component_system;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  material_type;

    m_quadList.reserve(4); // number of vertexes a quad has

    typedef entity_array::const_iterator  itr_type;
    itr_type itr = DoGetActiveEntities().begin();
    itr_type itrEnd = DoGetActiveEntities().end();

    // Add relevant attributes and uniforms to the shader
    for (; itr != itrEnd; ++itr)
    {
      const entity_type* ent = *itr;
      ComponentMapper<quad_type> mesh = ent->GetComponents(components::mesh);
      Quad& q = mesh[0];

      if (ent->HasComponent(components::material))
      {
        ComponentMapper<material_type> matArr =
          ent->GetComponents(components::material);
        material_type& mat = matArr[0];

        m_quadList.clear();
        m_quadList.push_back(q.GetVertex<Quad::vert_ne>().GetPosition());
        m_quadList.push_back(q.GetVertex<Quad::vert_nw>().GetPosition());
        m_quadList.push_back(q.GetVertex<Quad::vert_sw>().GetPosition());
        m_quadList.push_back(q.GetVertex<Quad::vert_se>().GetPosition());

        gl::Attribute a_vData;
        a_vData.SetName("a_vPos").SetVertexArray
          (m_quadList, gl::p_shader_variable_ti::CopyArray() );

        mat.GetShaderProgRef().AddAttribute(a_vData);
      }
    }

    return ErrorSuccess();
  }

  QuadRenderSystem::error_type QuadRenderSystem::Shutdown()
  { return ErrorSuccess(); }

  void QuadRenderSystem::ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    TLOC_UNUSED(a_mgr);

    using namespace core::component_system;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  material_type;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material))
    {
      ComponentMapper<material_type> matArr =
        ent->GetComponents(components::material);
      material_type& mat = matArr[0];

      mat.GetShaderProgRef().Enable();
      mat.GetShaderProgRef().LoadAllUniforms();
      mat.GetShaderProgRef().LoadAllAttributes();

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      mat.GetShaderProgRef().Disable();
    }
  }

  void QuadRenderSystem::Pre_OnEvent(const event_type& a_event)
  { TLOC_UNUSED(a_event); }

  void QuadRenderSystem::Post_OnEvent(const event_type& a_event)
  { TLOC_UNUSED(a_event); }

};};};