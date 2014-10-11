#include "tlocQuadRenderSystem.h"

#include <tlocCore/tlocAssert.h>

#include <tlocMath/types/tlocRectangle.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
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

  QuadRenderSystem::
    QuadRenderSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 Variadic<component_type, 1>(components::quad))
  {
    m_quadList->resize(4);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  QuadRenderSystem::
    ~QuadRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type 
    QuadRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    gfx_cs::quad_sptr quadPtr = a_ent->GetComponent<gfx_cs::Quad>();

    //------------------------------------------------------------------------
    // Prepare the Quad

    typedef math::types::Rectf32_c    rect_type;
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

    const gfx_gl::shader_operator_vptr so =  quadPtr->GetShaderOperator().get();

    gfx_gl::AttributeVBO vbo;
    vbo.AddName(base_type::GetVertexAttributeName())
       .SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                   gfx_gl::p_vbo::usage::StaticDraw>(*m_quadList);

    so->AddAttributeVBO(vbo);

    if (a_ent->HasComponent<gfx_cs::TextureCoords>())
    { base_type::DoInitializeTexCoords(a_ent, so); }

    return base_type::InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type 
    QuadRenderSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    QuadRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    gfx_cs::quad_sptr quadPtr = a_ent->GetComponent<gfx_cs::Quad>();

    base_type::DrawInfo di(a_ent, GL_TRIANGLE_STRIP, 4);
    di.m_shaderOp = core_sptr::ToVirtualPtr(quadPtr->GetShaderOperator());

    base_type::DoDrawEntity(di);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(QuadRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(QuadRenderSystem);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(QuadRenderSystem::vec3_cont_type);