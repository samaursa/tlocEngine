#ifndef TLOC_SHADER_PROGRAM_H
#define TLOC_SHADER_PROGRAM_H

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

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

  class ShaderProgram
  {
  public:
    typedef core::tl_array<bool>::type  flag_type;
    typedef tl_uint                     shader_handle;

    ShaderProgram();
    ~ShaderProgram();

    template <typename T_ShaderType>
    bool LoadShader(const char* a_shaderSource, T_ShaderType a_type);
    bool CompileShader();

  private:

    core::utils::Checkpoints    m_flags;
    shader_handle               m_handle;

  };

};};

#endif