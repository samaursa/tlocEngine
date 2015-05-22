#include "tlocMaterialSystem.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/utilities/tlocPointerUtils.h>
#include <tlocCore/io/tlocFileIO.h>

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
       uniform mat4 u_vp;                                       \n\
       uniform mat4 u_model;                                    \n\
                                                                \n\
       void main()                                              \n\
       {                                                        \n\
          mat4 vp = u_vp;                                       \n\
          if (u_vp[0][0] == 0.0 &&                              \n\
              u_vp[0][1] == 0.0 &&                              \n\
              u_vp[0][2] == 0.0)                                \n\
          { vp = mat4(1.0); }                                   \n\
                                                                \n\
          mat4 model = u_model;                                 \n\
          if (u_model[0][0] == 0.0 &&                           \n\
              u_model[0][1] == 0.0 &&                           \n\
              u_model[0][2] == 0.0)                             \n\
          { model = mat4(1.0); }                                \n\
                                                                \n\
          gl_Position = vp * model * vec4(a_vertPos, 1);        \n\
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
    , m_vsSource(core_io::FileContents(core_io::Path
        ("hard_coded_default_shader/defaultVS.glsl"), vsSource))
    , m_fsSource(core_io::FileContents(core_io::Path
        ("hard_coded_default_shader/defaultFS.glsl"), fsSource))
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

      m_defaultMaterial->SetVertexSource(m_vsSource);
      m_defaultMaterial->SetFragmentSource(m_fsSource);

      auto result = 
        f_material::CompileAndLinkShaderProgram(*m_defaultMaterial);

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

      auto result = ErrorFailure;
      if (matPtr->GetVertexSource().empty() == false || 
          matPtr->GetFragmentSource().empty() == false)
      { result = f_material::CompileAndLinkShaderProgram(*matPtr); }

      if (result != ErrorSuccess)
      { *matPtr->GetShaderProg() = *m_defaultMaterial->GetShaderProg(); }
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    MaterialSystem::
    ReInitializeEntity(entity_ptr a_ent)
  {
    using namespace core::component_system;

    auto numMaterialComponents = a_ent->size_components<gfx_cs::Material>();

    // Material should have vertex and fragment shader data, for now we will
    // assume that both exist

    for ( size_type i = 0; i < numMaterialComponents; ++i )
    {
      auto matPtr = a_ent->GetComponent<gfx_cs::Material>(i);

      if (matPtr->GetVertexSource().empty() || matPtr->GetFragmentSource().empty())
      { 
        *matPtr->GetShaderProg() = *m_defaultMaterial->GetShaderProg();
        return ErrorSuccess;
      }

      const auto& currVSContents = matPtr->GetVertexSource();
      const auto& currFSContents = matPtr->GetFragmentSource();

      core_io::FileContents vs, fs;
      auto vsError = ErrorSuccess;
      auto fsError = ErrorSuccess;
      {
        using namespace core_io;
        vsError =
          f_file_io::OpenAndGetContents<p_file_io::Ascii>(matPtr->GetVertexPath(), vs);
        TLOC_LOG_GFX_ERR_FILENAME_ONLY_IF(vsError != ErrorSuccess) 
          << "Failed to open shader: " << matPtr->GetVertexPath();
      }
      {
        using namespace core_io;
        auto fsError =
          f_file_io::OpenAndGetContents<p_file_io::Ascii>(matPtr->GetFragmentPath(), fs);
        TLOC_LOG_GFX_ERR_FILENAME_ONLY_IF(fsError != ErrorSuccess)
          << "Failed to open shader: " << matPtr->GetFragmentPath();
      }

      if (currVSContents != vs.GetContents() ||
          currFSContents != fs.GetContents() ||
          matPtr->GetShaderProg()->IsLinked() == false)
      {
        if (vsError == ErrorSuccess) { matPtr->SetVertexSource(vs); }
        if (fsError == ErrorSuccess) { matPtr->SetFragmentSource(fs); }

        *matPtr->GetShaderProg() = gfx_gl::ShaderProgram();
        matPtr->SetUpdateRequired(true);

        TLOC_LOG_GFX_WARN_NO_FILENAME_IF
          (matPtr->GetShaderOperator()->size_attributeVBOs() > 0)
          << "Material's ShaderOperator should not have any AttributeVBOs.";

        auto  result = 
          f_material::CompileAndLinkShaderProgram(*matPtr);

        if (result != ErrorSuccess)
        { *matPtr->GetShaderProg() = *m_defaultMaterial->GetShaderProg(); }
      }
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
    if (matPtr->IsUpdateRequired())
    {
      matPtr->SetUpdateRequired(false);
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