#include "tlocShaderProgram.h"

#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocVariadic.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

#include <tlocCore/utilities/tlocType.h>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace core::data_structs;
  using namespace core::string;

  namespace
  {
    typedef ShaderProgram::glsl_var_info_cont_type   glsl_var_info_cont_type;
    typedef ShaderProgram::size_type                 size_type;

    //------------------------------------------------------------------------
    // Variables

    const u32 g_buffSize = 40; // u32 because of OpenGL's types

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      k_shaderAttached = 0,
      k_shaderLinked,
      k_shaderEnabled,
      k_uniformInfoLoaded,
      k_attributeInfoLoaded,
      k_count
    };

    //------------------------------------------------------------------------
    // Shader variables info

    //````````````````````````````````````````````````````````````````````````
    // Uniforms

    void DoGetUniformInfo(const ShaderProgram& a_shaderProgram,
                          glsl_var_info_cont_type& a_infoOut)
    {
      const size_type uniformMaxLength =
        a_shaderProgram.Get<p_shader_program::ActiveUniformMaxLength>();
      const size_type numOfUniforms =
        a_shaderProgram.Get<p_shader_program::ActiveUniforms>();

      TLOC_ASSERT(uniformMaxLength < g_buffSize,
                  "Uniform name length larger than buffer!");
      TLOC_UNUSED(uniformMaxLength);

      a_infoOut.resize(numOfUniforms);
      String fixedName;
      for (u32 i = 0; i < numOfUniforms; ++i)
      {
        ShaderVariableInfo& currInfo = a_infoOut[i];
        glGetActiveUniform(a_shaderProgram.GetHandle(), i, g_buffSize,
                           &currInfo.m_nameLength, &currInfo.m_arraySize,
                           &currInfo.m_type, currInfo.m_name.Get());

        // remove [0] from the names which appears on some cards
        fixedName = currInfo.m_name.Get();
        fixedName = fixedName.substr(0, fixedName.find('['));
        core::copy(fixedName.begin(), fixedName.end(), currInfo.m_name.Get());
        currInfo.m_name.Get()[fixedName.length()] = '\0';

        TLOC_ASSERT(currInfo.m_nameLength > 0, "Name length should not be 0!");
      }

      glsl_var_info_cont_type::iterator itr, itrEnd;
      for (itr = a_infoOut.begin(), itrEnd = a_infoOut.end();
           itr != itrEnd; ++itr)
      {
        itr->m_location = glGetUniformLocation
          (a_shaderProgram.GetHandle(), itr->m_name.Get());
      }
    }

    //````````````````````````````````````````````````````````````````````````
    // Attributes

    void DoGetAttributeInfo(const ShaderProgram& a_shaderProgram,
                            glsl_var_info_cont_type& a_infoOut)
    {
      const size_type attributeMaxLength =
        a_shaderProgram.Get<p_shader_program::ActiveAttributeMaxLength>();
      const size_type numOfAttributes =
        a_shaderProgram.Get<p_shader_program::ActiveAttributes>();

      TLOC_ASSERT(attributeMaxLength < g_buffSize,
                  "Attribute name length larger than buffer!");
      TLOC_UNUSED(attributeMaxLength);

      a_infoOut.resize(numOfAttributes);
      for (u32 i = 0; i < numOfAttributes; ++i)
      {
        ShaderVariableInfo& currInfo = a_infoOut[i];
        glGetActiveAttrib(a_shaderProgram.GetHandle(), i, g_buffSize,
                          &currInfo.m_nameLength, &currInfo.m_arraySize,
                          &currInfo.m_type, currInfo.m_name.Get());

        TLOC_ASSERT(currInfo.m_nameLength > 0, "Name length should not be 0!");
      }

      glsl_var_info_cont_type::iterator itr, itrEnd;
      for (itr = a_infoOut.begin(), itrEnd = a_infoOut.end();
           itr != itrEnd; ++itr)
      {
        itr->m_location = glGetAttribLocation
          (a_shaderProgram.GetHandle(), itr->m_name.Get());
      }

    }

  };

  namespace p_shader_program
  {
    const tl_int DeleteStatus            ::s_glStatusName = GL_DELETE_STATUS;
    const tl_int LinkStatus              ::s_glStatusName = GL_LINK_STATUS;
    const tl_int ValidateStatus          ::s_glStatusName = GL_VALIDATE_STATUS;
    const tl_int InfoLogLength           ::s_glStatusName = GL_INFO_LOG_LENGTH;
    const tl_int AttachedShaders         ::s_glStatusName = GL_ATTACHED_SHADERS;
    const tl_int ActiveAttributes        ::s_glStatusName = GL_ACTIVE_ATTRIBUTES;
    const tl_int ActiveAttributeMaxLength::s_glStatusName =
                                                 GL_ACTIVE_ATTRIBUTE_MAX_LENGTH;
    const tl_int ActiveUniforms          ::s_glStatusName = GL_ACTIVE_UNIFORMS;
    const tl_int ActiveUniformMaxLength  ::s_glStatusName =
                                                 GL_ACTIVE_UNIFORM_MAX_LENGTH;
  };

  //////////////////////////////////////////////////////////////////////////
  // Shader Program

  ShaderProgram::ShaderProgram() : m_flags(k_count)
  {
    SetHandle(glCreateProgram());
    TLOC_ASSERT(gl::Error().Succeeded(), "Could not create shader program");
  }

  ShaderProgram::~ShaderProgram()
  {
    if (IsLastRef())
    {
      glDeleteProgram(GetHandle());
    }
  }

  template <ShaderProgram::size_type T_Size>
  ShaderProgram::error_type
    ShaderProgram::AttachShaders
    (Variadic<Shader_I*, T_Size> a_shaderComponents)
  {
    for (size_type i = 0; i < a_shaderComponents.GetSize(); ++i)
    {
      glAttachShader(GetHandle(), a_shaderComponents[i]->GetHandle());
      TLOC_ASSERT(gl::Error().Succeeded(), "Could not attach shader");
    }

    m_flags.Mark(k_shaderAttached);
    return ErrorSuccess();
  }

  ShaderProgram::error_type ShaderProgram::Link()
  {
    TLOC_ASSERT(m_flags[k_shaderAttached],
      "No shaders attached - did you forget to call AttachShaders()?");

    object_handle handle = GetHandle();

    glLinkProgram(handle);

    GLint result = Get<p_shader_program::LinkStatus>();
    if (result == GL_FALSE)
    {
      s32 logLen;
      char logBuffer[1000];
      glGetProgramInfoLog(handle, sizeof(logBuffer), &logLen, logBuffer);

      DoSetError(logBuffer);

      // TODO: Write shader log
      return error::error_shader_program_link;
    }

    m_flags.Mark(k_shaderLinked);
    return ErrorSuccess();
  }

  bool ShaderProgram::IsLinked() const
  {
    return m_flags[k_shaderLinked];
  }

  void ShaderProgram::LoadUniformInfo()
  {
    TLOC_ASSERT(m_flags.IsMarked(k_shaderLinked),
                "Shader not linked! - Did you forget to call Link()?");

    if (m_flags.ReturnAndMark(k_uniformInfoLoaded) == false)
    { DoGetUniformInfo(*this, m_uniformInfo); }
  }

  void ShaderProgram::LoadAttributeInfo()
  {
    TLOC_ASSERT(m_flags.IsMarked(k_shaderLinked),
                "Shader not linked! - Did you forget to call Link()?");

    if (m_flags.ReturnAndMark(k_attributeInfoLoaded) == false)
    { DoGetAttributeInfo(*this, m_attributeInfo); }
  }

  const ShaderProgram::glsl_var_info_cont_type& ShaderProgram::
    GetUniformInfoRef() const
  {
    TLOC_ASSERT(m_flags.IsMarked(k_uniformInfoLoaded),
          "Uniforms not loaded! - Did you forget to call LoadUniformInfo()?");
    return m_uniformInfo;
  }

  const ShaderProgram::glsl_var_info_cont_type& ShaderProgram::
    GetAttributeInfoRef() const
  {
    TLOC_ASSERT(m_flags.IsMarked(k_attributeInfoLoaded),
          "Attributes not loaded! - Did you forget to call LoadUniformInfo()?");
    return m_attributeInfo;
  }

  ShaderProgram::error_type
    ShaderProgram::Enable() const
  {
    glUseProgram(GetHandle());
    if (gl::Error().Failed())
    {
      return error::error_shader_program_enable;
    }

    ResetTextureUnits();
    return ErrorSuccess();
  }

  bool ShaderProgram::
    IsEnabled() const
  {
    // NOTE: OpenGL defines program name to be u32 but glGetIntegeriv returns
    //       s32, thus the cast.
    if (gl::Get<gl::p_get::CurrentProgram>() ==
        core::utils::CastNumber<GLint, object_handle>(GetHandle()) )
    { return true; }

    return false;
  }

  ShaderProgram::error_type
    ShaderProgram::Disable() const
  {
    glUseProgram(0);

    if (gl::Error().Failed())
    {
      return error::error_shader;
    }

    return ErrorSuccess();
  }

  //------------------------------------------------------------------------
  // Private methods

  namespace
  {
    template <typename T_ProgramIvParam>
    struct DoGetOperation
    {
      void operator()(ShaderProgram::object_handle)
      { /* intentionally empty */ }
    };

    template <>
    struct DoGetOperation<p_shader_program::ValidateStatus>
    {
      void operator()(ShaderProgram::object_handle a_shaderHandle)
      {
        // This is required BEFORE a call to
        // glGetProgramiv(#, GL_VALIDATE_STATUS, ...) is called.
        glValidateProgram(a_shaderHandle);
      }
    };
  }

  template <typename T_ProgramIvParam>
  ShaderProgram::gl_result_type
    ShaderProgram::DoGet() const
  {
    GLint result;
    object_handle handle = GetHandle();

    // Perform any operation that may be required before the following call
    // 'means' anything
    DoGetOperation<T_ProgramIvParam>()(handle);

    glGetProgramiv(handle, T_ProgramIvParam::s_glStatusName, &result);
    return (gl_result_type)result;
  }

  //------------------------------------------------------------------------
  // Explicit initialization

  // Supporting up to 4 shader attachments
  template class Variadic<Shader_I*, 1>;
  template class Variadic<Shader_I*, 2>;
  template class Variadic<Shader_I*, 3>;
  template class Variadic<Shader_I*, 4>;

  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (Variadic<Shader_I*, 1>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (Variadic<Shader_I*, 2>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (Variadic<Shader_I*, 3>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (Variadic<Shader_I*, 4>);

  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::DeleteStatus>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::LinkStatus>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ValidateStatus>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::InfoLogLength>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::AttachedShaders>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveAttributes>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveAttributeMaxLength>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveUniforms>() const;
  template ShaderProgram::gl_result_type
    ShaderProgram::DoGet<p_shader_program::ActiveUniformMaxLength>() const;

  // SmartPtr

  template class tloc::core::smart_ptr::SharedPtr<ShaderProgram>;

};};};