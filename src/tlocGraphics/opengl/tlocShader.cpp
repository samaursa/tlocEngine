#include "tlocShader.h"

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace core::string;

  namespace detail
  {
    Shader_I::object_handle
      CreateShader(p_shader_program::shader_type::Vertex)
    {
      return glCreateShader(GL_VERTEX_SHADER);
    }

    Shader_I::object_handle
      CreateShader(p_shader_program::shader_type::Fragment)
    {
      return glCreateShader(GL_FRAGMENT_SHADER);
    }

    Shader_I::object_handle
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
    k_shaderAttached,
    k_shaderLinked,
    count
  };

  Shader_I::Shader_I() : m_flags(count)
  {
  }

  Shader_I::~Shader_I()
  {
    if (IsLastRef())
    {
      glDeleteShader(GetHandle());
    }
  }

  template <typename T_ShaderType>
  Shader_I::error_type
    Shader_I::DoLoad(const char *a_shaderSource)
  {
    SetHandle( detail::CreateShader(T_ShaderType()) );

    object_handle handle = GetHandle();
    if (!handle)
    {
      return common_error_types::error_invalid_handle;
    }

    // Load the shader
    s32 strLen = (s32)StrLen(a_shaderSource);
    glShaderSource(handle, 1, &a_shaderSource, &strLen);

    // TODO: Log proper OpenGL errors
    if(Error().Failed())
    { return error::error_shader_source; }

    m_flags.Mark(shader_loaded);
    return ErrorSuccess();
  }

  Shader_I::error_type Shader_I::Compile()
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

      DoSetError(logBuffer);

      // TODO: Write shader log
      return error::error_shader_compile;
    }

    m_flags.Mark(shader_compiled);
    return ErrorSuccess();
  }

  //////////////////////////////////////////////////////////////////////////
  // Fragment Shader

  FragmentShader::FragmentShader() : Shader_I()
  { }

  FragmentShader::~FragmentShader()
  { }

  FragmentShader::error_type
    FragmentShader::Load(const char* a_shaderSource)
  {
    typedef p_shader_program::shader_type::Fragment fragment_shader_type;

    return DoLoad<fragment_shader_type>(a_shaderSource);
  }

  //////////////////////////////////////////////////////////////////////////
  // Vertex Shader

  VertexShader::VertexShader() : Shader_I()
  { }

  VertexShader::~VertexShader()
  { }

  VertexShader::error_type
    VertexShader::Load(const char* a_shaderSource)
  {
    typedef p_shader_program::shader_type::Vertex vertex_shader_type;

    return DoLoad<vertex_shader_type>(a_shaderSource);
  }

  //------------------------------------------------------------------------
  // Explicit instantiation
  template Shader_I::error_type
    Shader_I::DoLoad<p_shader_program::shader_type::Vertex>(const char*);
  template Shader_I::error_type
    Shader_I::DoLoad<p_shader_program::shader_type::Fragment>(const char*);
  template Shader_I::error_type
    Shader_I::DoLoad<p_shader_program::shader_type::Geometry>(const char*);

};};};