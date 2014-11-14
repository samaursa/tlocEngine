#include "tlocMaterialSystem.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

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

      TLOC_LOG_GFX_WARN_IF(matPtr->GetShaderOperator()->size_attributeVBOs() > 0)
        << "Material's ShaderOperator should not have any AttributeVBOs.";

      gl::VertexShader          vShader;
      gl::FragmentShader        fShader;

      auto  result = ErrorSuccess;
      auto  sp = matPtr->GetShaderProg();

      if (sp->IsLinked() == false)
      {
        // TODO: Log this instead
        const auto vertSourceSize = matPtr->GetVertexSource().size();
        const auto fragSourceSize = matPtr->GetFragmentSource().size();

        TLOC_LOG_GFX_WARN_IF(vertSourceSize == 0)
          << "Vertex shader source is empty";
        TLOC_LOG_GFX_WARN_IF(fragSourceSize == 0)
          << "Fragment shader source is empty";

        vShader.Load(matPtr->GetVertexSource().c_str() );
        result = vShader.Compile();
        TLOC_LOG_GFX_WARN_IF(result != ErrorSuccess)
          << "Could not compile vertex shader:\n"
          << vShader.GetError().c_str();

        result = fShader.Load(matPtr->GetFragmentSource().c_str());
        result = fShader.Compile();
        TLOC_LOG_GFX_WARN_IF(result != ErrorSuccess)
          << "Could not compile fragment shader:\n"
          << fShader.GetError().c_str();

        result = sp->AttachShaders
          (gl::ShaderProgram::two_shader_components(&vShader, &fShader) );
        TLOC_LOG_GFX_WARN_IF(result != ErrorSuccess)
          << "Could not attach shader program(s)";

        result = sp->Link();

        TLOC_LOG_GFX_WARN_IF(result != ErrorSuccess)
          << "Could not link shader(s):\n"
          << sp->GetError().c_str();
      }

      sp->LoadUniformInfo();
      sp->LoadAttributeInfo();
      sp->Disable();

      //------------------------------------------------------------------------
      // Add user attributes and uniforms

      sp->Enable();

      auto so = matPtr->GetShaderOperator();
      auto err = ErrorSuccess;

      err = so->PrepareAllUniforms(*sp);
      TLOC_LOG_GFX_WARN_IF(err != ErrorSuccess)
        << "Unable to prepare all uniforms";

      sp->Disable();
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
    ProcessEntity(entity_ptr, f64)
  { }

};};};


//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MaterialSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MaterialSystem);