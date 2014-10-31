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

    typedef gfx_cs::Material                            mat_type;
    typedef gfx_cs::material_sptr                       mat_ptr;
    typedef mat_type::shader_prog_ptr                   shader_prog_ptr;
    typedef mat_type::const_shader_prog_ptr             const_shader_prog_ptr;
    typedef gl::p_shader_program::shader_type::Vertex   vertex_shader_type;
    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;


    size_type numMaterialComponen = a_ent->size_components<gfx_cs::Material>();

    // Material should have vertex and fragment shader data, for now we will
    // assume that both exist

    for ( size_type i = 0; i < numMaterialComponen; ++i )
    {
      mat_ptr matPtr = a_ent->GetComponent<gfx_cs::Material>(i);

      gl::VertexShader          vShader;
      gl::FragmentShader        fShader;
      gl::Shader_I::error_type  result = ErrorSuccess;

      shader_prog_ptr sp = matPtr->GetShaderProg();

      if (sp->IsLinked() == false)
      {
        // TODO: Log this instead
        const size_type vertSourceSize = matPtr->GetVertexSource().size();
        const size_type fragSourceSize = matPtr->GetFragmentSource().size();

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
          (shader_prog_ptr::value_type::two_shader_components(&vShader, &fShader) );
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

      typedef mat_type::shader_op_cont::iterator  shader_op_itr;

      mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

      sp->Enable();

      core_err::Error err = ErrorSuccess;
      for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
           itr != itrEnd; ++itr)
      {
				gl::shader_operator_vptr so = itr->get();
        err = so->PrepareAllUniforms(*sp);

        TLOC_LOG_GFX_WARN_IF(err != ErrorSuccess)
          << "Unable to prepare all uniforms";

        err = so->PrepareAllAttributeVBOs(*sp);

        TLOC_LOG_GFX_WARN_IF(err != ErrorSuccess)
          << "Unable to prepare all AttributeVBOs";
      }
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