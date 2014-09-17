#include "tlocFanRenderSystem.h"

#include <tlocMath/types/tlocCircle.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocMaterial.h>

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
  {
    m_vertList->reserve(30);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    FanRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    base_type::InitializeEntity(a_ent);
    return ErrorSuccess;
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
    using namespace core::component_system;
    using math_t::degree_f32;

    if (a_ent->HasComponent(components::material))
    {
      gfx_cs::material_sptr matPtr = a_ent->GetComponent<gfx_cs::Material>();
      gfx_cs::fan_sptr      fanPtr = a_ent->GetComponent<gfx_cs::Fan>();

      //------------------------------------------------------------------------
      // Prepare the Fan

      typedef math::types::Circlef32 circle_type;
      using namespace math::types;

      m_vertList->clear();

      const circle_type& circ = fanPtr->GetEllipseRef();

      const size_type numSides = fanPtr->GetNumSides();
      const f32 angleInterval = 360.0f/numSides;

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

      DoGetVertexDataAttribute()->
        SetVertexArray(m_vertList.get(), gl::p_shader_variable_ti::Pointer() );

      base_type::DrawInfo di(a_ent, GL_TRIANGLE_FAN, numVertices);
      base_type::DoDrawEntity(di);
    }
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(FanRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(FanRenderSystem);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(FanRenderSystem::vec3_cont_type);