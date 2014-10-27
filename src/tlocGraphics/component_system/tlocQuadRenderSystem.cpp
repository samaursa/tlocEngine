#include "tlocQuadRenderSystem.h"

#include <tlocCore/tlocAssert.h>

#include <tlocMath/types/tlocRectangle.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  typedef math::types::Vec3f32                              vec3_type;
  typedef math::types::Mat4f32                              matrix_type;

  typedef core_conts::tl_array<vec3_type>::type             vec3_cont_type;


  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef QuadRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  QuadRenderSystem::
    QuadRenderSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 register_type().Add<Quad>())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  QuadRenderSystem::
    ~QuadRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoMakeQuadVertices(const gfx_cs::quad_sptr& a_quad, vec3_cont_type& a_out)
  {
    typedef math::types::Rectf32_c    rect_type;

    const rect_type& rect = a_quad->GetRectangleRef();

    a_out.resize(4);
    a_out.at(0) = vec3_type(rect.GetValue<rect_type::right>(),
                            rect.GetValue<rect_type::top>(), 0);
    a_out.at(1) = vec3_type(rect.GetValue<rect_type::left>(),
                            rect.GetValue<rect_type::top>(), 0);
    a_out.at(2) = vec3_type(rect.GetValue<rect_type::right>(),
                            rect.GetValue<rect_type::bottom>(), 0);
    a_out.at(3) = vec3_type(rect.GetValue<rect_type::left>(),
                            rect.GetValue<rect_type::bottom>(), 0);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type 
    QuadRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    gfx_cs::quad_sptr quadPtr = a_ent->GetComponent<gfx_cs::Quad>();
    quadPtr->SetUpdateRequired(false);

    vec3_cont_type quadList;
    DoMakeQuadVertices(quadPtr, quadList);

    const gfx_gl::shader_operator_vptr so =  quadPtr->GetShaderOperator().get();

    gfx_gl::AttributeVBO vbo;
    vbo.AddName(base_type::GetVertexAttributeName())
       .SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                   gfx_gl::p_vbo::usage::StaticDraw>(quadList);

    so->AddAttributeVBO(vbo);

    if (a_ent->HasComponent<gfx_cs::TextureCoords>())
    { base_type::DoInitializeTexCoords(a_ent, *so); }

    return base_type::InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type 
    QuadRenderSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoUpdateQuad(QuadRenderSystem& a_sys, QuadRenderSystem::entity_ptr a_ent, 
                 gfx_cs::quad_sptr a_quadPtr)
  {
    //------------------------------------------------------------------------
    // Update the quad

    typedef math::types::Rectf32_c            rect_type;

    const gfx_gl::shader_operator_vptr so =  a_quadPtr->GetShaderOperator().get();

    using gl::algos::shader_operator::compare::AttributeVBOName;
    gl::ShaderOperator::attributeVBO_iterator itr = 
      core::find_if(so->begin_attributeVBOs(), so->end_attributeVBOs(), 
                    AttributeVBOName(a_sys.GetVertexAttributeName()));

    if (itr == so->end_attributeVBOs())
    { return; }

    a_quadPtr->SetUpdateRequired(false);

    vec3_cont_type      quadList;
    DoMakeQuadVertices(a_quadPtr, quadList);

    itr->first->UpdateData(quadList);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    QuadRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    gfx_cs::quad_sptr quadPtr = a_ent->GetComponent<gfx_cs::Quad>();

    if (quadPtr->IsUpdateRequired())
    { DoUpdateQuad(*this, a_ent, quadPtr); }

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