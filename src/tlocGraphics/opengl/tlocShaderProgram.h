#ifndef TLOC_SHADER_PROGRAM_H
#define TLOC_SHADER_PROGRAM_H

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderVariableInfo.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_shader_program
  {
    struct DeleteStatus            { static const tl_int s_glStatusName; };
    struct LinkStatus              { static const tl_int s_glStatusName; };
    struct ValidateStatus          { static const tl_int s_glStatusName; };
    struct InfoLogLength           { static const tl_int s_glStatusName; };
    struct AttachedShaders         { static const tl_int s_glStatusName; };
    struct ActiveAttributes        { static const tl_int s_glStatusName; };
    struct ActiveAttributeMaxLength{ static const tl_int s_glStatusName; };
    struct ActiveUniforms          { static const tl_int s_glStatusName; };
    struct ActiveUniformMaxLength  { static const tl_int s_glStatusName; };
  };

  class ShaderProgram : public Object_T<ShaderProgram>
  {
  public:
    template <typename T> friend class ObjectRefCounted;

  public:
    // Supported number of shader components
    typedef core::Variadic<Shader_I*, 1>     one_shader_component;
    typedef core::Variadic<Shader_I*, 2>     two_shader_components;
    typedef core::Variadic<Shader_I*, 3>     three_shader_components;
    typedef core::Variadic<Shader_I*, 4>     four_shader_components;

    typedef Object_T<ShaderProgram>     base_type;
    typedef base_type::object_handle    object_handle;
    typedef base_type::error_type       error_type;

    typedef tl_size                     size_type;
    typedef s32                         gl_result_type;

    typedef ShaderVariableInfo                        glsl_var_info_type;
    typedef core::tl_array<ShaderVariableInfo>::type  glsl_var_info_cont_type;

  public:
    ShaderProgram();
    ~ShaderProgram();

    template <size_type T_Size>
    error_type AttachShaders(core::Variadic<Shader_I*, T_Size>
                             a_shaderComponents);
    error_type Link();
    bool       IsLinked() const;

    void LoadUniformInfo();
    void LoadAttributeInfo();

    TLOC_DECL_GETTER_CONST_DIRECT
      (glsl_var_info_cont_type, GetUniformInfoRef);
    TLOC_DECL_GETTER_CONST_DIRECT
      (glsl_var_info_cont_type, GetAttributeInfoRef);

    template <typename T_ProgramIvParam>
    gl_result_type Get() const
    {
      type_traits::AssertTypeIsSupported
        < T_ProgramIvParam,
        p_shader_program::DeleteStatus,
        p_shader_program::LinkStatus,
        p_shader_program::ValidateStatus,
        p_shader_program::InfoLogLength,
        p_shader_program::AttachedShaders,
        p_shader_program::ActiveAttributes,
        p_shader_program::ActiveAttributeMaxLength,
        p_shader_program::ActiveUniforms,
        p_shader_program::ActiveUniformMaxLength>();
      return DoGet<T_ProgramIvParam>();
    }

    error_type Enable() const;
    bool       IsEnabled() const;
    error_type Disable() const;

  private:
    template <typename T_ProgramIvParam>
    gl_result_type DoGet() const;

  private:
    core::utils::Checkpoints         m_flags;
    glsl_var_info_cont_type          m_attributeInfo;
    glsl_var_info_cont_type          m_uniformInfo;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef tloc::core::smart_ptr::SharedPtr<ShaderProgram>     ShaderProgramPtr;

};};};

#endif