#include "tlocMaterialSystem.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
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
                Variadic<component_type, 1>(components::material))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    MaterialSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    using namespace core::component_system;

    typedef gfx_cs::Material                            mat_type;
    typedef gfx_cs::material_vptr                       mat_ptr;
    typedef mat_type::shader_prog_ptr                   shader_prog_ptr;
    typedef gl::p_shader_program::shader_type::Vertex   vertex_shader_type;
    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;

    typedef ComponentMapper<mat_type>                   mat_mapper;

    mat_mapper mat = a_ent->GetComponents(components::material);

    // Material should have vertex and fragment shader data, for now we will
    // assume that both exist

    for (mat_mapper::size_type i = 0; i < mat.size(); ++i)
    {
      mat_ptr matPtr = mat[i];

      gl::VertexShader          vShader;
      gl::FragmentShader        fShader;
      gl::Shader_I::error_type  result = ErrorSuccess;

      shader_prog_ptr sp = matPtr->GetShaderProgRef();

      if (sp->IsLinked())
      { continue; }

      // TODO: Log this instead
      TLOC_ASSERT(matPtr->GetVertexSource().size() > 0, "Vertex shader is empty");
      TLOC_ASSERT(matPtr->GetFragmentSource().size() > 0, "Fragment shader is empty");

      vShader.Load(matPtr->GetVertexSource().c_str() );
      result = vShader.Compile();
      TLOC_ASSERT(result == ErrorSuccess, "Could not compile vertex shader");

      result = fShader.Load(matPtr->GetFragmentSource().c_str());
      result = fShader.Compile();
      TLOC_ASSERT(result == ErrorSuccess, "Could not compile fragment shader");

      result = sp->AttachShaders
        (shader_prog_ptr::value_type::two_shader_components(&vShader, &fShader) );
      TLOC_ASSERT(result == ErrorSuccess, "Could not attach shader programs");

      result = sp->Link();
      TLOC_ASSERT(result == ErrorSuccess, "Could not link shaders");
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

        err = so->PrepareAllAttributes(*sp);

        TLOC_LOG_GFX_WARN_IF(err != ErrorSuccess)
          << "Unable to prepare all attributes";
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

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(MaterialSystem);
