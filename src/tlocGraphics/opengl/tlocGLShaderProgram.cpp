#include "tlocGLShaderProgram.h"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/string/tlocString.h>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocGlError.h>

namespace tloc { namespace graphics {

  namespace detail
  {
    GLShaderComponent::object_handle
      CreateShader(p_shader_program::shader_type::Vertex)
    {
      return glCreateShader(GL_VERTEX_SHADER);
    }

    GLShaderComponent::object_handle
      CreateShader(p_shader_program::shader_type::Fragment)
    {
      return glCreateShader(GL_FRAGMENT_SHADER);
    }

    GLShaderComponent::object_handle
      CreateShader(p_shader_program::shader_type::Geometry)
    {
      // TODO: glew.h does not have geometry shaders yet
      //return glCreateShader(GL_GEOMETRY_SHADER);
      return 0;
    }
  };

  enum flags
  {
    shader_loaded = 0,
    shader_compiled,
    shader_attached,
    shader_linked,
    count
  };

  //------------------------------------------------------------------------
  // ShaderComponent

  GLShaderComponent::GLShaderComponent() : m_flags(count)
  {
  }

  GLShaderComponent::~GLShaderComponent()
  {
    glDeleteShader(GetHandle());
  }

  template <typename T_ShaderType>
  bool GLShaderComponent::LoadShader(const char *a_shaderSource, T_ShaderType a_type)
  {
    GetHandle() = detail::CreateShader(a_type);
    if (!GetHandle())
    {
      return false;
    }

    // Load the shader
    tl_int strLen = (tl_int)core::StrLen(a_shaderSource);
    glShaderSource(GetHandle(), 1, &a_shaderSource, &strLen);

    // TODO: Log proper OpenGL errors
    if(GlError().Failed())
    { return false; }

    m_flags.Mark(shader_loaded);
    return true;
  }

  bool GLShaderComponent::CompileShader()
  {
    TLOC_ASSERT(m_flags[shader_loaded],
      "No shader loaded - did you forget to call LoadShader()?");

    glCompileShader(GetHandle());

    GLint result;
    glGetShaderiv(GetHandle(), GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
      // TODO: Write shader log
      return false;
    }

    m_flags.Mark(shader_compiled);
    return true;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation
  template bool GLShaderComponent::LoadShader(const char*, p_shader_program::shader_type::Vertex);
  template bool GLShaderComponent::LoadShader(const char*, p_shader_program::shader_type::Fragment);
  template bool GLShaderComponent::LoadShader(const char*, p_shader_program::shader_type::Geometry);

  //------------------------------------------------------------------------
  // ShaderProgram

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

};};