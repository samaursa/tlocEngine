#include "tlocShaderProgram.h"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/string/tlocString.h>

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
    GetHandle() = glCreateProgram();
  }

  ShaderProgram::~ShaderProgram()
  {
    glDeleteProgram(GetHandle());
  }

  template <ShaderProgram::size_type T_Size>
  bool ShaderProgram::AttachShaders
    (core::Variadic<ShaderComponent, T_Size> a_shaderComponents)
  {
    for (size_type i = 0; i < a_shaderComponents.GetSize(); ++i)
    {
      glAttachShader(GetHandle(), a_shaderComponents[i].GetHandle());
    }

    m_flags.Mark(shader_attached);
    return true;
  }

  bool ShaderProgram::Link()
  {
    TLOC_ASSERT(m_flags[shader_attached],
      "No shaders attached - did you forget to call AttachShaders()?");

    glLinkProgram(GetHandle());

    GLint result;
    glGetShaderiv(GetHandle(), GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
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

  //------------------------------------------------------------------------
  // Explicit initialization
  template bool ShaderProgram::AttachShaders
    (core::Variadic<ShaderComponent, 1>);
  template bool ShaderProgram::AttachShaders
    (core::Variadic<ShaderComponent, 2>);
  template bool ShaderProgram::AttachShaders
    (core::Variadic<ShaderComponent, 3>);
  template bool ShaderProgram::AttachShaders
    (core::Variadic<ShaderComponent, 4>);

};};};