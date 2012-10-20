#include "tlocShaderProgram.h"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocVariadic.inl>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_shader_program
  {
    const tl_int DeleteStatus            ::s_glStatusName = GL_DELETE_STATUS;
    const tl_int LinkStatus              ::s_glStatusName = GL_LINK_STATUS;
    const tl_int ValidateStatus          ::s_glStatusName = GL_VALIDATE_STATUS;
    const tl_int InfoLogLength           ::s_glStatusName = GL_INFO_LOG_LENGTH;
    const tl_int AttachedShaders         ::s_glStatusName = GL_ATTACHED_SHADERS;
    const tl_int ActiveAttributes        ::s_glStatusName = GL_ACTIVE_ATTRIBUTES;
    const tl_int ActiveAttributeMaxLength::s_glStatusName =
                                                 GL_ACTIVE_ATTRIBUTE_MAX_LENGTH;
    const tl_int ActiveUniforms          ::s_glStatusName = GL_ACTIVE_UNIFORMS;
    const tl_int ActiveUniformMaxLength  ::s_glStatusName =
                                                 GL_ACTIVE_UNIFORM_MAX_LENGTH;
  };

  enum flags
  {
    shader_attached = 0,
    shader_linked,
    count
  };

  ShaderProgram::ShaderProgram() : m_flags(count)
  {
    SetHandle(glCreateProgram());
    TLOC_ASSERT(gl::Error().Succeeded(), "Could not create shader program");
  }

  ShaderProgram::~ShaderProgram()
  {
    if (IsLastRef())
    {
      glDeleteProgram(GetHandle());
    }
  }

  template <ShaderProgram::size_type T_Size>
  ShaderProgram::error_type
    ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, T_Size> a_shaderComponents)
  {
    for (size_type i = 0; i < a_shaderComponents.GetSize(); ++i)
    {
      glAttachShader(GetHandle(), a_shaderComponents[i]->GetHandle());
      TLOC_ASSERT(gl::Error().Succeeded(), "Could not attach shader");
    }

    m_flags.Mark(shader_attached);
    return true;
  }

  ShaderProgram::error_type ShaderProgram::Link()
  {
    TLOC_ASSERT(m_flags[shader_attached],
      "No shaders attached - did you forget to call AttachShaders()?");

    object_handle handle = GetHandle();

    glLinkProgram(handle);

    GLint result = Get<p_shader_program::LinkStatus>();
    if (result == GL_FALSE)
    {
      core::String errorString;
      gl::Error().GetErrorAsString(errorString);

      // TODO: Write shader log
      return error::error_shader_program_link;
    }

    m_flags.Mark(shader_linked);
    return ErrorSuccess();
  }

  void ShaderProgram::Enable()
  {
    glUseProgram(GetHandle());
  }

  //------------------------------------------------------------------------
  // Private methods

  template <typename T_ProgramIvParam>
  ShaderProgram::gl_result_type
    ShaderProgram::DoGet() const
  {
    GLint result;
    object_handle handle = GetHandle();
    glGetProgramiv(handle, T_ProgramIvParam::s_glStatusName, &result);
    return (gl_result_type)result;
  }

  //------------------------------------------------------------------------
  // Explicit initialization
  template class core::Variadic<Shader_I*, 1>;
  template class core::Variadic<Shader_I*, 2>;
  template class core::Variadic<Shader_I*, 3>;
  template class core::Variadic<Shader_I*, 4>;

  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 1>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 2>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 3>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 4>);

  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::DeleteStatus>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::LinkStatus>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ValidateStatus>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::InfoLogLength>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::AttachedShaders>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveAttributes>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveAttributeMaxLength>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveUniforms>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveUniformMaxLength>() const;

};};};