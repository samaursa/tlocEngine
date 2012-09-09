#ifndef TLOC_SHADER_PROGRAM_H
#define TLOC_SHADER_PROGRAM_H

#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocShaderComponent.h>

namespace tloc { namespace graphics { namespace gl {

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

};};};

#endif