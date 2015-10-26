#include "tlocDebugTransformRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

#include <tlocPrefab/graphics/tlocMaterial.h>

namespace {

#ifdef TLOC_OS_WIN
  const char* vsSource =
    "#version 330 core                                        \n\
                                                              \n\
     in vec3 a_vPos;                                          \n\
     in vec4 a_color;                                         \n\
     uniform mat4 u_mvp;                                      \n\
                                                              \n\
     out vec4 a_lineColor;                                    \n\
                                                              \n\
     void main()                                              \n\
     {                                                        \n\
        gl_Position = u_mvp * vec4(a_vPos, 1);                \n\
        a_lineColor = a_color;                                \n\
     }                                                        \n\
    ";

  const char* fsSource = 
    "#version 330 core                                        \n\
                                                              \n\
     in vec4 a_lineColor;                                     \n\
     out vec4 color;                                          \n\
                                                              \n\
     void main()                                              \n\
     {                                                        \n\
        color = a_lineColor;                                  \n\
     }                                                        \n\
    ";
#else
  const char* vsSource =
    "#version 100                                             \n\
                                                              \n\
     attribute lowp vec3 a_vPos;                              \n\
     attribute lowp vec4 a_color;                             \n\
     uniform mat4 u_mvp;                                      \n\
                                                              \n\
     varying vec4 v_lineColor;                                \n\
                                                              \n\
     void main()                                              \n\
     {                                                        \n\
        gl_Position = u_mvp * vec4(a_vPos, 1);                \n\
        v_lineColor = a_color;                                \n\
     }                                                        \n\
    ";
  
  const char* fsSource =
    "#version 100                                             \n\
                                                              \n\
     varying lowp vec4 v_lineColor;                           \n\
                                                              \n\
     void main()                                              \n\
     {                                                        \n\
        gl_FragColor = v_lineColor;                           \n\
     }                                                        \n\
    ";
#endif


};

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef DebugTransformRenderSystem::error_type          error_type;

  // ///////////////////////////////////////////////////////////////////////
  // DebugTransformRenderSystem

  DebugTransformRenderSystem::
    DebugTransformRenderSystem(event_manager_ptr a_eventMgr, 
                               entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr, 
                register_type().Add<math_cs::Transform>(), 
                "DebugTransformRenderSystem")
    , m_linesEntMgr(m_linesEventMgr.get())
    , m_linesMaterialSys(m_linesEventMgr.get(), m_linesEntMgr.get())
    , m_scale(1.0f)
  { 
    m_linesOperator->reserve_uniforms(1); // mvp 
    m_uniVpMat = m_linesOperator->AddUniform(gl::Uniform().SetName("u_mvp"));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DebugTransformRenderSystem::
    ~DebugTransformRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DebugTransformRenderSystem::
    Pre_Initialize()
  { 
    m_linesMaterial = 
      pref_gfx::Material(m_linesEntMgr.get(), m_linesPoolMgr.get())
      .Create(core_io::FileContents(core_io::Path("Hard-coded shader"), vsSource), 
              core_io::FileContents(core_io::Path("Hard-coded shader"), fsSource));

    {
      gfx_t::Vert3fpc v1, v2;
      v1.SetPosition(math_t::Vec3f32(0, 0, 0));
      v2.SetPosition(math_t::Vec3f32(1 * m_scale, 0, 0));

      v1.SetColor(gfx_t::Color(1.0f, 0.0f, 0.0f, 1.0f));
      v2.SetColor(gfx_t::Color(1.0f, 0.0f, 0.0f, 1.0f));

      m_lineList.push_back(v1);
      m_lineList.push_back(v2);
    }

    {
      gfx_t::Vert3fpc v1, v2;
      v1.SetPosition(math_t::Vec3f32(0, 0, 0));
      v2.SetPosition(math_t::Vec3f32(0, 1 * m_scale, 0));

      v1.SetColor(gfx_t::Color(0.0f, 1.0f, 0.0f, 1.0f));
      v2.SetColor(gfx_t::Color(0.0f, 1.0f, 0.0f, 1.0f));

      m_lineList.push_back(v1);
      m_lineList.push_back(v2);
    }

    {
      gfx_t::Vert3fpc v1, v2;
      v1.SetPosition(math_t::Vec3f32(0, 0, 0));
      v2.SetPosition(math_t::Vec3f32(0, 0, 1 * m_scale));

      v1.SetColor(gfx_t::Color(0.0f, 0.0f, 1.0f, 1.0f));
      v2.SetColor(gfx_t::Color(0.0f, 0.0f, 1.0f, 1.0f));

      m_lineList.push_back(v1);
      m_lineList.push_back(v2);
    }

    gfx_gl::AttributeVBO vbo;
    vbo.AddName("a_vPos")
       .AddName("a_color")
       .SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                   gfx_gl::p_vbo::usage::StaticDraw>(m_lineList);

    m_linesOperator->AddAttributeVBO(vbo);

    return base_type::Pre_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DebugTransformRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { return ErrorSuccess; }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DebugTransformRenderSystem::
    Post_Initialize()
  {
    m_linesMaterialSys->Initialize();
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DebugTransformRenderSystem::
    ShutdownEntity(entity_ptr )
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DebugTransformRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64 )
  {
      using math::types::Mat4f32;
      using math::types::Vec4f32;

      using namespace core::component_system;
      typedef math::component_system::Transform     transform_type;

      math_cs::transform_f32_sptr t = a_ent->GetComponent<math_cs::Transformf32>();

      Mat4f32 tMatrix;
      if (a_ent->HasComponent<gfx_cs::SceneNode>())
      { tMatrix = a_ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
      else
      { tMatrix = t->GetTransformation().Cast<Mat4f32>(); }

      Mat4f32 tFinalMat = m_vpMatrix * tMatrix;

      // Generate the mvp matrix
      m_uniVpMat->SetValueAs(tFinalMat);

      gfx_cs::material_sptr matPtr = m_linesMaterial->GetComponent<gfx_cs::Material>();
      auto sp = matPtr->GetShaderProg();

      error_type uniformErr = ErrorSuccess;
      error_type attribErr = ErrorSuccess;

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if (m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get())
      {
        if (m_shaderPtr)
        { m_shaderPtr->Disable(); }

        m_shaderPtr = sp;

        if (sp->Enable().Failed())
        {
          TLOC_LOG_GFX_WARN() << "ShaderProgram #" << sp->GetHandle()
            << " could not be enabled.";
          return;
        }

        uniformErr = m_linesOperator->PrepareAllUniforms(*m_shaderPtr);
        attribErr = m_linesOperator->PrepareAllAttributeVBOs(*m_shaderPtr, 
                                                             *m_vao);
      }

      // Add the mvp
      if (uniformErr.Succeeded())
      { m_linesOperator->EnableAllUniforms(*m_shaderPtr); }

      gfx_gl::VertexArrayObject::Bind b(*m_vao);

      glDrawArrays(GL_LINES, 0,
                   core_utils::CastNumber<gfx_t::gl_sizei>(m_lineList.size()));

      gl::Error err; TLOC_UNUSED(err);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DebugTransformRenderSystem::
    Post_ProcessActiveEntities(f64 a_deltaT)
  {
    m_shaderPtr.reset();
    base_type::Post_ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DebugTransformRenderSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DebugTransformRenderSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
  void 
    DebugTransformRenderSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { } 

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DebugTransformRenderSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(DebugTransformRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(DebugTransformRenderSystem);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(DebugTransformRenderSystem::vertex_cont);