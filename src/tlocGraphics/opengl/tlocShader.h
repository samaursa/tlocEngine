#ifndef _TLOC_GRAPHICS_GL_SHADER_H_
#define _TLOC_GRAPHICS_GL_SHADER_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_shader_program
  {
    namespace shader_type
    {
      struct Vertex{};
      struct Fragment{};
      struct Geometry{};
    };
  };

  //////////////////////////////////////////////////////////////////////////
  // Base class for shaders

  class Shader_I : public Object_T<Shader_I, p_object::WithError>
  {
  public:
    template <typename T> friend class ObjectRefCounted;

  public:
    typedef Object_T<Shader_I>                      base_type;
    typedef base_type::object_handle                object_handle;
    typedef base_type::error_type                   error_type;

    typedef core::containers::tl_array<bool>::type  flag_type;

  public:
    error_type Compile();

  protected:
    Shader_I();
    ~Shader_I();

    template <typename T_ShaderType>
    error_type DoLoad(const char* a_shaderSource);

  private:
    core::utils::Checkpoints    m_flags;
  };

  //////////////////////////////////////////////////////////////////////////
  // Fragment shader

  class FragmentShader : public Shader_I
  {
  public:
    typedef Shader_I                            base_type;
    typedef base_type::object_handle            object_handle;
    typedef base_type::error_type               error_type;

  public:
    FragmentShader();
    ~FragmentShader();

    error_type  Load(const char* a_shaderSource);
  };

  //////////////////////////////////////////////////////////////////////////
  // Vertex Shader

  class VertexShader : public Shader_I
  {
  public:
    typedef Shader_I                            base_type;
    typedef base_type::object_handle            object_handle;
    typedef base_type::error_type               error_type;

  public:
    VertexShader();
    ~VertexShader();

    error_type Load(const char* a_shaderSource);
  };


};};};

#endif