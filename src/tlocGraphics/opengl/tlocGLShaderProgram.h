#ifndef TLOC_SHADER_PROGRAM_H
#define TLOC_SHADER_PROGRAM_H

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/string/tlocString.h>

namespace tloc { namespace graphics {

  namespace p_shader_program
  {
    namespace shader_type
    {
      struct Vertex{};
      struct Fragment{};
      struct Geometry{};
    };
  };

  class GLObject
  {
  public:
    typedef tl_uint                     object_handle;

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(object_handle, GetHandle, m_handle);

  private:
    object_handle m_handle;
  };

  class GLShaderComponent : public GLObject
  {
  public:
    typedef GLObject                    base_type;
    using base_type::object_handle;

    typedef core::tl_array<bool>::type  flag_type;

    GLShaderComponent();
    ~GLShaderComponent();

    template <typename T_ShaderType>
    bool LoadShader(const char* a_shaderSource, T_ShaderType a_type);
    bool CompileShader();

  private:

    core::utils::Checkpoints    m_flags;
  };

  class GLShaderProgram : public GLObject
  {
  public:
    typedef GLObject                    base_type;
    using base_type::object_handle;

    typedef tl_size                     size_type;

    GLShaderProgram();
    ~GLShaderProgram();

    template <size_type T_Size>
    bool AttachShaders(core::Variadic<GLShaderComponent, T_Size>
                       a_shaderComponents);
    bool Link();

  private:

    core::utils::Checkpoints    m_flags;
  };

};};

#endif