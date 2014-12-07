#include "tlocMaterialSystem.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  namespace {

#ifdef TLOC_OS_WIN
    const char* vsSource =
      "#version 330 core                                        \n\
                                                                \n\
       in vec3 a_vertPos;                                       \n\
       uniform mat4 u_mvp;                                      \n\
                                                                \n\
       void main()                                              \n\
       {                                                        \n\
          mat4 mvp = u_mvp;                                     \n\
          if (u_mvp[0][0] == 0.0 &&                             \n\
              u_mvp[0][1] == 0.0 &&                             \n\
              u_mvp[0][2] == 0.0)                               \n\
          { mvp = mat4(1.0); }                                  \n\
                                                                \n\
          gl_Position = mvp * vec4(a_vertPos, 1);               \n\
       }                                                        \n\
      ";

    const char* fsSource = 
      "#version 330 core                                        \n\
       out vec4 color;                                          \n\
                                                                \n\
       void main()                                              \n\
       {                                                        \n\
         color = vec4(1.0, 0.0, 0.996, 1.0);                    \n\
       }                                                        \n\
      ";
#else
    const char* vsSource =
      "#version 100                                             \n\
                                                                \n\
       attribute lowp vec3 a_vertPos;                           \n\
       uniform mat4 u_mvp;                                      \n\
                                                                \n\
       void main()                                              \n\
       {                                                        \n\
          mat4 mvp = u_mvp;                                     \n\
          if (u_mvp[0][0] == 0.0 &&                             \n\
              u_mvp[0][1] == 0.0 &&                             \n\
              u_mvp[0][2] == 0.0)                               \n\
          { mvp = mat4(1.0); }                                  \n\
                                                                \n\
          gl_Position = u_mvp * vec4(a_vertPos, 1);             \n\
       }                                                        \n\
      ";
    
    const char* fsSource =
      "#version 100                                             \n\
                                                                \n\
       void main()                                              \n\
       {                                                        \n\
         gl_FragColor = vec4(1.0, 0.0, 0.996, 1.0);             \n\
       }                                                        \n\
      ";
#endif

  // ///////////////////////////////////////////////////////////////////////

    core_err::Error
      DoCompileAndLinkShaderProgram(gfx_cs::material_vptr a_matPtr)
    {
      gl::VertexShader          vShader;
      gl::FragmentShader        fShader;

      auto  result   = ErrorSuccess;
      auto  sp       = a_matPtr->GetShaderProg();
      auto& vsSource = a_matPtr->GetVertexSource();
      auto& fsSource = a_matPtr->GetFragmentSource();

      if (sp->IsLinked() == false)
      {
        // TODO: Log this instead
        const auto vertSourceSize = vsSource.size();
        const auto fragSourceSize = fsSource.size();

        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(vertSourceSize == 0)
          << "Vertex shader source is empty";
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(fragSourceSize == 0)
          << "Fragment shader source is empty";

        result = vShader.Load(a_matPtr->GetVertexSource().c_str() );
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Failed to load the shader: " << a_matPtr->GetVertexPath().GetPath();
        result = vShader.Compile();
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not compile vertex shader: " 
          << a_matPtr->GetVertexPath().GetPath() << "\n"
          << vShader.GetError().c_str();

        result = fShader.Load(a_matPtr->GetFragmentSource().c_str());
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Failed to load the shader: " << a_matPtr->GetVertexPath().GetPath();
        result = fShader.Compile();
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not compile fragment shader: "
          << a_matPtr->GetFragmentPath().GetPath() << "\n"
          << fShader.GetError().c_str();

        result = sp->AttachShaders
          (gl::ShaderProgram::two_shader_components(&vShader, &fShader) );
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not attach shader program(s)";

        result = sp->Link();

        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not link shader(s): " << a_matPtr->GetVertexPath().GetPath()
          << " and " << a_matPtr->GetFragmentPath().GetPath() << "\n"
          << sp->GetError().c_str();

        if (result == ErrorSuccess)
        {
          core_str::String vsFileName, fsFileName;
          a_matPtr->GetVertexPath().GetFileName(vsFileName);
          a_matPtr->GetFragmentPath().GetFileName(fsFileName);

          TLOC_LOG_GFX_INFO() << "Shader #" << sp->GetHandle() 
            << " compiled successfully with programs (" << vsFileName 
            << ") and (" << fsFileName << ")";
        }
      }

      if (result == ErrorSuccess)
      {

        sp->LoadUniformInfo();
        sp->LoadAttributeInfo();
        sp->Disable();

        //------------------------------------------------------------------------
        // Add user attributes and uniforms

        sp->Enable();

        auto so = a_matPtr->GetShaderOperator();
        auto err = ErrorSuccess;

        err = so->PrepareAllUniforms(*sp);
        TLOC_LOG_GFX_WARN_IF(err != ErrorSuccess)
          << "Unable to prepare all uniforms";

        sp->Disable();
      }

      return result;
    }

  };

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef MaterialSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // MaterialSystem

  MaterialSystem::
    MaterialSystem(event_manager_ptr a_eventMgr,
                   entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<gfx_cs::Material>(), 
                "MaterialSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  MaterialSystem::this_type&
    MaterialSystem::
    SetDefaultShaders(core_io::FileContents a_vs, core_io::FileContents a_fs)
  {
    TLOC_LOG_GFX_WARN_NO_FILENAME_IF(IsInitialized()) 
      << "MaterialSystem already Initialized(). Set default shaders BEFORE "
      << "initializing the system";

    m_vsSource = a_vs;
    m_fsSource = a_fs;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    MaterialSystem::
    Pre_Initialize()
  {
    // initialize our default material
    if (m_defaultMaterial == nullptr)
    {
      m_defaultMaterial = core_sptr::MakeUnique<gfx_cs::Material>();

      if (m_fsSource.GetContents().empty() || m_vsSource.GetContents().empty())
      {
        m_vsSource = core_io::FileContents
          (core_io::Path("hard_coded_default_shader/defaultVS.glsl"), vsSource);
        m_fsSource = core_io::FileContents
          (core_io::Path("hard_coded_default_shader/defaultFS.glsl"), fsSource);
      }

      m_defaultMaterial->SetVertexSource(m_vsSource);
      m_defaultMaterial->SetFragmentSource(m_fsSource);

      auto result = 
        DoCompileAndLinkShaderProgram(core_sptr::ToVirtualPtr(m_defaultMaterial));

      TLOC_LOG_GFX_WARN_NO_FILENAME_IF(result != ErrorSuccess)
        << "Default engine shader failed to compile and/or link";
    }

    return base_type::Pre_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    MaterialSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    using namespace core::component_system;

    auto numMaterialComponents = a_ent->size_components<gfx_cs::Material>();

    // Material should have vertex and fragment shader data, for now we will
    // assume that both exist

    for ( size_type i = 0; i < numMaterialComponents; ++i )
    {
      auto matPtr = a_ent->GetComponent<gfx_cs::Material>(i);

      TLOC_LOG_GFX_WARN_NO_FILENAME_IF
        (matPtr->GetShaderOperator()->size_attributeVBOs() > 0)
        << "Material's ShaderOperator should not have any AttributeVBOs.";

      gl::VertexShader          vShader;
      gl::FragmentShader        fShader;

      auto  result = 
        DoCompileAndLinkShaderProgram(core_sptr::ToVirtualPtr(matPtr));

      if (result != ErrorSuccess)
      { *matPtr->GetShaderProg() = *m_defaultMaterial->GetShaderProg(); }
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    MaterialSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    MaterialSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  { 
    auto matPtr = a_ent->GetComponent<gfx_cs::Material>();
    if (matPtr->m_isDirty)
    {
      matPtr->m_isDirty = false;
      matPtr->m_internalShaderOp->ClearCache();
    }
  }

};};};


//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MaterialSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MaterialSystem);