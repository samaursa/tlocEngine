#include "tlocShader.h"

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  namespace detail
  {
    Shader::object_handle
      CreateShader(p_shader_program::shader_type::Vertex)
    {
      return glCreateShader(GL_VERTEX_SHADER);
    }

    Shader::object_handle
      CreateShader(p_shader_program::shader_type::Fragment)
    {
      return glCreateShader(GL_FRAGMENT_SHADER);
    }

    Shader::object_handle
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

  Shader::Shader() : m_flags(count)
  {
  }

  Shader::~Shader()
  {
    if (IsLastRef())
    {
      glDeleteShader(GetHandle());
    }
  }

  template <typename T_ShaderType>
  bool Shader::LoadShader(const char *a_shaderSource, T_ShaderType a_type)
  {
    SetHandle(detail::CreateShader(a_type));

    object_handle handle = GetHandle();
    if (!handle)
    {
      return false;
    }

    // Load the shader
    s32 strLen = (s32)core::StrLen(a_shaderSource);
    glShaderSource(handle, 1, &a_shaderSource, &strLen);

    // TODO: Log proper OpenGL errors
    if(Error().Failed())
    { return false; }

    m_flags.Mark(shader_loaded);
    return true;
  }

  bool Shader::CompileShader()
  {
    TLOC_ASSERT(m_flags[shader_loaded],
      "No shader loaded - did you forget to call LoadShader()?");

    object_handle handle = GetHandle();
    glCompileShader(handle);

    GLint result;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
      s32     logLen;
      char    logBuffer[1000];
      glGetShaderInfoLog(handle, sizeof(logBuffer), &logLen, logBuffer);

      // TODO: Write shader log
      return false;
    }

    m_flags.Mark(shader_compiled);
    return true;
  }

  void Shader::DoDestroy()
  {
  }

  //------------------------------------------------------------------------
  // Explicit instantiation
  template bool Shader::LoadShader(const char*, p_shader_program::shader_type::Vertex);
  template bool Shader::LoadShader(const char*, p_shader_program::shader_type::Fragment);
  template bool Shader::LoadShader(const char*, p_shader_program::shader_type::Geometry);

};};};