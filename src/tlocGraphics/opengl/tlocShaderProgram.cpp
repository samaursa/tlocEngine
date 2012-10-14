#include "tlocShaderProgram.h"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocVariadic.inl>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

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

  template <ShaderProgram::size_type T_Size>
  bool ShaderProgram::AttachShaders
    (core::Variadic<Shader*, T_Size> a_shaderComponents)
  {
    for (size_type i = 0; i < a_shaderComponents.GetSize(); ++i)
    {
      glAttachShader(GetHandle(), a_shaderComponents[i]->GetHandle());
      TLOC_ASSERT(gl::Error().Succeeded(), "Could not attach shader");
    }

    m_flags.Mark(shader_attached);
    return true;
  }

  bool ShaderProgram::Link()
  {
    TLOC_ASSERT(m_flags[shader_attached],
      "No shaders attached - did you forget to call AttachShaders()?");

    object_handle handle = GetHandle();

    glLinkProgram(handle);

    GLint result;

    glGetProgramiv(handle, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
      core::String errorString;
      gl::Error().GetErrorAsString(errorString);

      // TODO: Write shader log
      return false;
    }

    m_flags.Mark(shader_linked);
    return true;
  }

  void ShaderProgram::Enable()
  {
    glUseProgram(GetHandle());
  }

  void ShaderProgram::DoDestroy()
  {
    glDeleteProgram(GetHandle());
  }

  //------------------------------------------------------------------------
  // Explicit initialization
  template class core::Variadic<Shader*, 1>;
  template class core::Variadic<Shader*, 2>;
  template class core::Variadic<Shader*, 3>;
  template class core::Variadic<Shader*, 4>;

  template bool ShaderProgram::AttachShaders
    (core::Variadic<Shader*, 1>);
  template bool ShaderProgram::AttachShaders
    (core::Variadic<Shader*, 2>);
  template bool ShaderProgram::AttachShaders
    (core::Variadic<Shader*, 3>);
  template bool ShaderProgram::AttachShaders
    (core::Variadic<Shader*, 4>);

};};};