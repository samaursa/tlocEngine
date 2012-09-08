#include "tlocGLShaderProgram.h"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/string/tlocString.h>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocGlError.h>

namespace tloc { namespace graphics { namespace gl {

  enum flags
  {
    shader_attached = 0,
    shader_linked,
    count
  };

  GLShaderProgram::GLShaderProgram() : m_flags(count)
  {
    GetHandle() = glCreateProgram();
  }

  GLShaderProgram::~GLShaderProgram()
  {
    glDeleteProgram(GetHandle());
  }

  template <GLShaderProgram::size_type T_Size>
  bool GLShaderProgram::AttachShaders
    (core::Variadic<GLShaderComponent, T_Size> a_shaderComponents)
  {
    for (size_type i = 0; i < a_shaderComponents.GetSize(); ++i)
    {
      glAttachShader(GetHandle(), a_shaderComponents[i].GetHandle());
    }

    m_flags.Mark(shader_attached);
    return true;
  }

  bool GLShaderProgram::Link()
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

  //------------------------------------------------------------------------
  // Explicit initialization
  template bool GLShaderProgram::AttachShaders
    (core::Variadic<GLShaderComponent, 1>);
  template bool GLShaderProgram::AttachShaders
    (core::Variadic<GLShaderComponent, 2>);
  template bool GLShaderProgram::AttachShaders
    (core::Variadic<GLShaderComponent, 3>);
  template bool GLShaderProgram::AttachShaders
    (core::Variadic<GLShaderComponent, 4>);

};};};