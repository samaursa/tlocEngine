#ifndef TLOC_GL_SHADER_COMPONENT_H
#define TLOC_GL_SHADER_COMPONENT_H

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

  class ShaderComponent : public Object
  {
  public:
    typedef Object                        base_type;
    using base_type::object_handle;

    typedef core::tl_array<bool>::type  flag_type;

    ShaderComponent();
    ~ShaderComponent();

    template <typename T_ShaderType>
    bool LoadShader(const char* a_shaderSource, T_ShaderType a_type);
    bool CompileShader();

  private:

    core::utils::Checkpoints    m_flags;
  };


};};};

#endif