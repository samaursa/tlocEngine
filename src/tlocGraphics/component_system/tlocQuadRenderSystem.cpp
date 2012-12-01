#include "tlocQuadRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

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
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::quad))
  { }

  error_type QuadRenderSystem::InitializeEntity(entity_manager*,
    entity_type* a_ent)
  {
    using namespace core::component_system;
    typedef graphics::component_system::Quad      quad_type;
    typedef graphics::component_system::Material  material_type;

    m_quadList.reserve(4); // number of vertexes a quad has

    const entity_type* ent = a_ent;
    ComponentMapper<quad_type> quad = ent->GetComponents(components::quad);
    Quad& q = quad[0];

    if (ent->HasComponent(components::material))
    {
      ComponentMapper<material_type> matArr =
        ent->GetComponents(components::material);
      material_type& mat = matArr[0];

      m_quadList.clear();
      m_quadList.push_back(q.GetVertex<Quad::vert_ne>().GetPosition());
      m_quadList.push_back(q.GetVertex<Quad::vert_nw>().GetPosition());
      m_quadList.push_back(q.GetVertex<Quad::vert_se>().GetPosition());
      m_quadList.push_back(q.GetVertex<Quad::vert_sw>().GetPosition());

      gl::Attribute a_vData;
      a_vData.SetName("a_vPos").SetVertexArray
        (m_quadList, gl::p_shader_variable_ti::CopyArray() );

      mat.GetShaderProgRef().AddAttribute(a_vData);
    }

    return ErrorSuccess();
  }

  error_type QuadRenderSystem::ShutdownEntity(entity_manager*, entity_type*)
  { return ErrorSuccess(); }

  void QuadRenderSystem::ProcessEntity(entity_manager*, entity_type* a_ent)
  {
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

};};};