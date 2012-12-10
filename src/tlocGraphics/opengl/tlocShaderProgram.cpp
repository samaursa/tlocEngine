#include "tlocShaderProgram.h"

#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocVariadic.inl>
#include <tlocCore/smart_ptr/tlocSmartPtr.inl>

#include <tlocCore/utilities/tlocType.h>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace
  {
    //------------------------------------------------------------------------
    // Variables

    const u32 g_buffSize = 40; // u32 because of OpenGL's types

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      k_shaderAttached = 0,
      k_shaderLinked,
      k_shaderEnabled,
      k_count
    };

  };

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

  //////////////////////////////////////////////////////////////////////////
  // Shader Program

  ShaderProgram::ShaderProgram() : m_flags(k_count)
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

    m_flags.Mark(k_shaderAttached);
    return ErrorSuccess();
  }

  ShaderProgram::error_type ShaderProgram::Link()
  {
    TLOC_ASSERT(m_flags[k_shaderAttached],
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

    m_flags.Mark(k_shaderLinked);
    return ErrorSuccess();
  }

  bool ShaderProgram::IsLinked() const
  {
    return m_flags[k_shaderLinked];
  }

  ShaderProgram::error_type
    ShaderProgram::Enable() const
  {
    glUseProgram(GetHandle());
    if (gl::Error().Failed())
    {
      return error::error_shader_program_enable;
    }

    return ErrorSuccess();
  }

  ShaderProgram::error_type
    ShaderProgram::Disable() const
  {
    glUseProgram(0);

    if (gl::Error().Failed())
    {
      return error::error_shader;
    }

    return ErrorSuccess();
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

  // Supporting up to 4 shader attachments
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

  // SmartPtr

  template class tloc::core::smart_ptr::SharedPtr<ShaderProgram>;

};};};