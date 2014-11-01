#include "tlocFanRenderSystem.h"

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/types/tlocVector3.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  typedef math::types::Vec3f32                              vec3_type;
  typedef math::types::Vec2f32                              vec2_type;

  typedef core_conts::tl_array<vec3_type>::type             vec3_cont_type;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef FanRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // FanRenderSystem

  FanRenderSystem::
    FanRenderSystem(event_manager_ptr a_eventMgr,
                    entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<gfx_cs::Fan>())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoMakeFanVertices(const gfx_cs::fan_sptr& a_fan, vec3_cont_type& a_out)
  {
    //------------------------------------------------------------------------
    // Prepare the Fan

    typedef math::types::Circlef32 circle_type;
    using namespace math::types;

    const circle_type& circ   = a_fan->GetEllipseRef();
    const tl_size numSides    = a_fan->GetNumSides();
    const f32 angleInterval   = 360.0f / numSides;

    a_out.reserve(numSides + 2);

    // Push the center vertex
    {
      Vec2f32 newCoord = circ.GetPosition();
      a_out.push_back
        (newCoord.ConvertTo<Vec3f32, p_tuple::overflow_zero>());
    }

    for (f32 i = 0; i <= numSides; ++i)
    {
      Vec2f32 newCoord = circ.GetCoord(degree_f32(angleInterval * i));
      a_out.push_back
        (newCoord.ConvertTo<Vec3f32, p_tuple::overflow_zero>());
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    FanRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    using namespace core::component_system;
    using math_t::degree_f32;

    gfx_cs::fan_sptr      fanPtr = a_ent->GetComponent<gfx_cs::Fan>();
    fanPtr->SetUpdateRequired(false);


    const gfx_gl::shader_operator_vptr so =  fanPtr->GetShaderOperator().get();

    vec3_cont_type vertList;
    DoMakeFanVertices(fanPtr, vertList);

    gfx_gl::AttributeVBO vbo;
    vbo.AddName(base_type::GetVertexAttributeName())
       .SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                   gfx_gl::p_vbo::usage::StaticDraw>(vertList);

    so->AddAttributeVBO(vbo);

    if (a_ent->HasComponent<gfx_cs::TextureCoords>())
    { base_type::DoInitializeTexCoords(a_ent, *so); }

    return base_type::InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    FanRenderSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoUpdateFan(FanRenderSystem& a_sys, FanRenderSystem::entity_ptr a_ent, 
                 gfx_cs::fan_sptr a_fanPtr)
  {
    //------------------------------------------------------------------------
    // Update the quad

    const gfx_gl::shader_operator_vptr so =  a_fanPtr->GetShaderOperator().get();

    using gl::algos::shader_operator::compare::AttributeVBOName;
    gl::ShaderOperator::attributeVBO_iterator itr = 
      core::find_if(so->begin_attributeVBOs(), so->end_attributeVBOs(), 
                    AttributeVBOName(a_sys.GetVertexAttributeName()));

    if (itr == so->end_attributeVBOs())
    { return; }

    a_fanPtr->SetUpdateRequired(false);

    vec3_cont_type      fanList;
    DoMakeFanVertices(a_fanPtr, fanList);

    itr->first->UpdateData(fanList);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    FanRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    gfx_cs::fan_sptr      fanPtr = a_ent->GetComponent<gfx_cs::Fan>();

    if (fanPtr->IsUpdateRequired())
    { DoUpdateFan(*this, a_ent, fanPtr); }

    const tl_size numVertices = fanPtr->GetNumSides() + 2;

    base_type::DrawInfo di(a_ent, GL_TRIANGLE_FAN, numVertices);
    di.m_shaderOp = core_sptr::ToVirtualPtr(fanPtr->GetShaderOperator());
    di.m_meshVAO  = fanPtr->GetVAO();

    base_type::DoDrawEntity(di);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(FanRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(FanRenderSystem);