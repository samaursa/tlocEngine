#include "tlocShaderProgram.h"

#include <tlocCore/string/tlocString.h>
#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/data_structures/tlocVariadic.inl>

#include <tlocCore/containers/tlocProtectedBuffer.h>
#include <tlocCore/containers/tlocProtectedBuffer.inl>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

// GL Includes
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace tloc::math;

  namespace
  {
    //------------------------------------------------------------------------
    // Variables

    const tl_size g_buffSize = 40;

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      shader_attached = 0,
      shader_linked,
      count
    };

    //------------------------------------------------------------------------
    // Structs

    struct glUniformInfo
    {
      typedef core::ProtectedBuffer<char8, g_buffSize>  buff_type;

      GLsizei     m_nameLength;
      GLint       m_arraySize;
      GLint       m_location;
      GLenum      m_type;
      buff_type   m_name;
    };
    typedef core::tl_array<glUniformInfo>::type     uniform_info_cont_type;

    //------------------------------------------------------------------------
    // Funcitons

    void DoGetUniformInfo(const ShaderProgram& a_shaderProgram,
                          uniform_info_cont_type& a_infoOut)
    {
      typedef ShaderProgram::size_type  size_type;

      const size_type uniformMaxLength =
        a_shaderProgram.Get<p_shader_program::ActiveUniformMaxLength>();
      const size_type numOfUniforms =
        a_shaderProgram.Get<p_shader_program::ActiveUniforms>();

      TLOC_ASSERT(uniformMaxLength < g_buffSize,
        "Uniform name length larger than buffer!");

      a_infoOut.resize(numOfUniforms);
      for (size_type i = 0; i < numOfUniforms; ++i)
      {

        glUniformInfo& currInfo = a_infoOut[i];
        glGetActiveUniform(a_shaderProgram.GetHandle(), i, g_buffSize,
                           &currInfo.m_nameLength, &currInfo.m_arraySize,
                           &currInfo.m_type, currInfo.m_name.Get());
      }

      uniform_info_cont_type::iterator itr, itrEnd;
      for (itr = a_infoOut.begin(), itrEnd = a_infoOut.end();
           itr != itrEnd; ++itr)
      {
        itr->m_location = glGetUniformLocation
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

  ShaderProgram::ShaderProgram() : m_flags(count)
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
    (core::Variadic<Shader_I*, T_Size> a_shaderComponents)
  {
    for (size_type i = 0; i < a_shaderComponents.GetSize(); ++i)
    {
      glAttachShader(GetHandle(), a_shaderComponents[i]->GetHandle());
      TLOC_ASSERT(gl::Error().Succeeded(), "Could not attach shader");
    }

    m_flags.Mark(shader_attached);
    return true;
  }

  ShaderProgram::error_type ShaderProgram::Link()
  {
    TLOC_ASSERT(m_flags[shader_attached],
      "No shaders attached - did you forget to call AttachShaders()?");

    object_handle handle = GetHandle();

    glLinkProgram(handle);

    GLint result = Get<p_shader_program::LinkStatus>();
    if (result == GL_FALSE)
    {
      core::String errorString;
      gl::Error().GetErrorAsString(errorString);

      // TODO: Write shader log
      return error::error_shader_program_link;
    }

    m_flags.Mark(shader_linked);
    return ErrorSuccess();
  }

  ShaderProgram::error_type ShaderProgram::AttachUniforms()
  {
    TLOC_ASSERT(m_flags[shader_linked],
                "Shader not linked - did you forget to call Link()?");

    uniform_info_cont_type uniCont;
    DoGetUniformInfo(*this, uniCont);

    uniform_cont_type::iterator itr, itrEnd;
    for (itr = m_uniforms.begin(), itrEnd = m_uniforms.end(); itr != itrEnd;
         ++itr)
    {
      uniform_info_cont_type::iterator itrInfo, itrInfoEnd;
      for (itrInfo = uniCont.begin(), itrInfoEnd = uniCont.end();
           itr != itrEnd; ++itr)
      {
        if (itr->GetName().compare(itrInfo->m_name.Get()) == 0)
        {
          if (itr->GetType() == itrInfo->m_type && itrInfo->m_location != -1)
          {
            switch(itrInfo->m_type)
            {
            case GL_FLOAT_VEC3:
              {
                const Vec3f& v = itr->GetValueAs<Vec3f>();
                glUniform3f(itrInfo->m_location, v[0], v[1], v[2]);
                break;
              }
            case GL_FLOAT_VEC4:
              {
                const Vec4f& v = itr->GetValueAs<Vec4f>();
                glUniform4f(itrInfo->m_location, v[0], v[1], v[2], v[3]);
                break;
              }
            case GL_FLOAT_MAT3:
              {
                const Mat3f& m = itr->GetValueAs<Mat3f>();
                TLOC_ASSERT(itrInfo->m_arraySize == Mat3f::k_TableSize,
                            "Mismatched uniform array size!");
                glUniformMatrix3fv(itrInfo->m_location, GL_FALSE,
                                   Mat3f::k_TableSize, m);
                  break;
              }
            case GL_FLOAT_MAT4:
              {
                const Mat4f& m = itr->GetValueAs<Mat4f>();
                TLOC_ASSERT(itrInfo->m_arraySize == Mat3f::k_TableSize,
                            "Mismatched uniform array size!");
                glUniformMatrix4fv(itrInfo->m_location, GL_FALSE,
                                   Mat3f::k_TableSize, m);
                break;
              }
            }
          }
          else
          {
            // TODO: Convert this assertion to a log
            TLOC_ASSERT(false, "Mismatched uniform type!");
          }
        }
      }
    }

    return ErrorSuccess();
  }

  void ShaderProgram::AddUniform(const Uniform& a_uniform)
  {
    m_uniforms.push_back(a_uniform);
  }

  void ShaderProgram::Enable()
  {
    glUseProgram(GetHandle());
  }

  //------------------------------------------------------------------------
  // Private methods

  template <typename T_ProgramIvParam>
  ShaderProgram::gl_result_type
    ShaderProgram::DoGet() const
  {
    GLint result;
    object_handle handle = GetHandle();
    glGetProgramiv(handle, T_ProgramIvParam::s_glStatusName, &result);
    return (gl_result_type)result;
  }

  //------------------------------------------------------------------------
  // Explicit initialization
  template class core::Variadic<Shader_I*, 1>;
  template class core::Variadic<Shader_I*, 2>;
  template class core::Variadic<Shader_I*, 3>;
  template class core::Variadic<Shader_I*, 4>;

  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 1>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 2>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 3>);
  template ShaderProgram::error_type ShaderProgram::AttachShaders
    (core::Variadic<Shader_I*, 4>);

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

};};};