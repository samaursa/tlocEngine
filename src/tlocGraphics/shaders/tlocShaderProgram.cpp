#include "tlocShaderProgram.h"

#include <tlocCore/containers/tlocContainers.inl>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics {

  namespace detail
  {
    ShaderProgram::shader_handle
      CreateShader(p_shader_program::shader_type::Vertex)
    {
      return glCreateShader(GL_VERTEX_SHADER);
    }

    ShaderProgram::shader_handle
      CreateShader(p_shader_program::shader_type::Fragment)
    {
      return glCreateShader(GL_FRAGMENT_SHADER);
    }

    ShaderProgram::shader_handle
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
    count
  };

  ShaderProgram::ShaderProgram() : m_flags(count)
  {
  }

  ShaderProgram::~ShaderProgram()
  {
  }

  template <typename T_ShaderType>
  bool ShaderProgram::LoadShader(const char *a_shaderSource, T_ShaderType a_type)
  {
    m_handle = detail::CreateShader(a_type);
    if (!m_handle)
    {
      return false;
    }

    m_flags.Mark(shader_loaded);
    return true;
  }

};};