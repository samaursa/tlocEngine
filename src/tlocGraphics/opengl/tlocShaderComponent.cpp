#include "tlocShaderComponent.h"

#include <tlocCore/string/tlocString.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  namespace detail
  {
    ShaderComponent::object_handle
      CreateShader(p_shader_program::shader_type::Vertex)
    {
      return glCreateShader(GL_VERTEX_SHADER);
    }

    ShaderComponent::object_handle
      CreateShader(p_shader_program::shader_type::Fragment)
    {
      return glCreateShader(GL_FRAGMENT_SHADER);
    }

    ShaderComponent::object_handle
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

  ShaderComponent::ShaderComponent() : m_flags(count)
  {
  }

  ShaderComponent::~ShaderComponent()
  {
    glDeleteShader(GetHandle());
  }

  template <typename T_ShaderType>
  bool ShaderComponent::LoadShader(const char *a_shaderSource, T_ShaderType a_type)
  {
    GetHandle() = detail::CreateShader(a_type);
    if (!GetHandle())
    {
      return false;
    }

    // Load the shader
    s32 strLen = (s32)core::StrLen(a_shaderSource);
    glShaderSource(GetHandle(), 1, &a_shaderSource, &strLen);

    // TODO: Log proper OpenGL errors
    if(Error().Failed())
    { return false; }

    m_flags.Mark(shader_loaded);
    return true;
  }

  bool ShaderComponent::CompileShader()
  {
    TLOC_ASSERT(m_flags[shader_loaded],
      "No shader loaded - did you forget to call LoadShader()?");

    glCompileShader(GetHandle());

    GLint result;
    glGetShaderiv(GetHandle(), GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
      s32     logLen;
      char    logBuffer[1000];
      glGetShaderInfoLog(GetHandle(), sizeof(logBuffer), &logLen, logBuffer);

      // TODO: Write shader log
      return false;
    }

    m_flags.Mark(shader_compiled);
    return true;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation
  template bool ShaderComponent::LoadShader(const char*, p_shader_program::shader_type::Vertex);
  template bool ShaderComponent::LoadShader(const char*, p_shader_program::shader_type::Fragment);
  template bool ShaderComponent::LoadShader(const char*, p_shader_program::shader_type::Geometry);

};};};