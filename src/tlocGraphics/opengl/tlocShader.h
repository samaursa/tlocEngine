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

  class Shader : public Object_T<Shader>
  {
  public:
    template <typename T> friend class ObjectRefCounted;

  public:
    typedef Object_T<Shader>   base_type;
    using base_type::object_handle;

    typedef core::tl_array<bool>::type  flag_type;

    Shader();
    ~Shader();

    template <typename T_ShaderType>
    bool LoadShader(const char* a_shaderSource, T_ShaderType a_type);
    bool CompileShader();

  private:
    void DoDestroy();

  private:
    core::utils::Checkpoints    m_flags;
  };


};};};

#endif