#include "tlocFanRenderSystem.h"

#include <tlocMath/types/tlocCircle.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef FanRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // FanRenderSystem

  FanRenderSystem::
    FanRenderSystem(event_manager_ptr a_eventMgr,
                    entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::fan))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    FanRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    using namespace core::component_system;
    using math_t::degree_f32;

    gfx_cs::fan_sptr      fanPtr = a_ent->GetComponent<gfx_cs::Fan>();

    //------------------------------------------------------------------------
    // Prepare the Fan

    typedef math::types::Circlef32 circle_type;
    using namespace math::types;

    vec3_cont_type vertList;

    const circle_type& circ   = fanPtr->GetEllipseRef();
    const size_type numSides  = fanPtr->GetNumSides();
    const f32 angleInterval   = 360.0f / numSides;

    // Push the center vertex
    {
      Vec2f32 newCoord = circ.GetPosition();
      vertList.push_back
        (newCoord.ConvertTo<Vec3f32, p_tuple::overflow_zero>());
    }

    for (f32 i = 0; i <= numSides; ++i)
    {
      Vec2f32 newCoord = circ.GetCoord(degree_f32(angleInterval * i));
      vertList.push_back
        (newCoord.ConvertTo<Vec3f32, p_tuple::overflow_zero>());
    }

    const gfx_gl::shader_operator_vptr so =  fanPtr->GetShaderOperator().get();

    gfx_gl::AttributeVBO vbo;
    vbo.AddName(base_type::GetVertexAttributeName())
       .SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                   gfx_gl::p_vbo::usage::StaticDraw>(vertList);

    so->AddAttributeVBO(vbo);

    if (a_ent->HasComponent<gfx_cs::TextureCoords>())
    { base_type::DoInitializeTexCoords(a_ent, so); }

    return base_type::InitializeEntity(a_ent);
  }

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
    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    gfx_cs::fan_sptr      fanPtr = a_ent->GetComponent<gfx_cs::Fan>();

    const tl_size numVertices = fanPtr->GetNumSides() + 2;

    base_type::DrawInfo di(a_ent, GL_TRIANGLE_FAN, numVertices);
    di.m_shaderOp = core_sptr::ToVirtualPtr(fanPtr->GetShaderOperator());
    base_type::DoDrawEntity(di);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(FanRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(FanRenderSystem);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(FanRenderSystem::vec3_cont_type);