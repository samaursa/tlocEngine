#include "tlocMaterialSystem.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/component_system/tlocEntity.inl>

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

  MaterialSystem::MaterialSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr
    , Variadic<component_type, 1>(components::material))
  { }

  error_type MaterialSystem::InitializeEntity(const entity_manager*,
                                              const entity_type* a_ent)
  {
    using namespace core::component_system;

    typedef graphics::component_system::Material        mat_type;
    typedef mat_type::shader_prog_ptr                   shader_prog_ptr;
    typedef gl::p_shader_program::shader_type::Vertex   vertex_shader_type;
    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;

    ComponentMapper<mat_type> mat = a_ent->GetComponents(components::material);

    // Material should have vertex and fragment shader data, for now we will
    // assume that both exist
    mat_type& currMat = mat[0];

    gl::VertexShader          vShader;
    gl::FragmentShader        fShader;
    gl::Shader_I::error_type  result = ErrorSuccess;

    shader_prog_ptr sp = currMat.GetShaderProgRef();

    if (sp->IsLinked())
    { return ErrorSuccess; }

    vShader.Load(currMat.GetVertexSource().c_str() );
    result = vShader.Compile();
    TLOC_ASSERT(result == ErrorSuccess, "Could not compile vertex shader");

    result = fShader.Load(currMat.GetFragmentSource().c_str());
    result = fShader.Compile();
    TLOC_ASSERT(result == ErrorSuccess, "Could not compile fragment shader");

    result = sp->AttachShaders
      (shader_prog_ptr::value_type::two_shader_components(&vShader, &fShader) );
    TLOC_ASSERT(result == ErrorSuccess, "Could not attach shader programs");

    sp->Enable().Ignore();
    result = sp->Link();
    TLOC_ASSERT(result == ErrorSuccess, "Could not link shaders");
    sp->LoadUniformInfo();
    sp->LoadAttributeInfo();
    sp->Disable();

    //------------------------------------------------------------------------
    // Add user attributes and uniforms

    typedef mat_type::shader_op_ptr          shader_op_ptr;

    sp->Enable();
    for (auto itr = currMat.GetShaderOperators().begin(),
         itrEnd = currMat.GetShaderOperators().end();
         itr != itrEnd; ++itr)
    {
      (*itr)->PrepareAllUniforms(*sp);
      (*itr)->PrepareAllAttributes(*sp);
    }
    sp->Disable();

    return ErrorSuccess;
  }

  error_type
    MaterialSystem::ShutdownEntity(const entity_manager*, const entity_type*)
  { return ErrorSuccess; }

  void MaterialSystem::ProcessEntity(const entity_manager*,
                                     const entity_type* )
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  template class core_sptr::SharedPtr<MaterialSystem>;

};};};
