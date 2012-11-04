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

    const u32 g_buffSize = 40; // u32 because of OpenGL's types

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      shader_attached = 0,
      shader_linked,
      shader_enabled,
      count
    };

    //------------------------------------------------------------------------
    // Structs

    struct glslVarInfo
    {
      typedef core::ProtectedBuffer<char8, g_buffSize>  buff_type;

      GLsizei     m_nameLength;
      GLint       m_arraySize;
      GLint       m_location;
      GLenum      m_type;
      buff_type   m_name;
    };
    typedef core::tl_array<glslVarInfo>::type     glsl_var_info_cont_type;

    //------------------------------------------------------------------------
    // Functions

    void DoGetUniformInfo(const ShaderProgram& a_shaderProgram,
                          glsl_var_info_cont_type& a_infoOut)
    {
      typedef ShaderProgram::size_type  size_type;

      const size_type uniformMaxLength =
        a_shaderProgram.Get<p_shader_program::ActiveUniformMaxLength>();
      const size_type numOfUniforms =
        a_shaderProgram.Get<p_shader_program::ActiveUniforms>();

      TLOC_ASSERT(uniformMaxLength < g_buffSize,
        "Uniform name length larger than buffer!");

      a_infoOut.resize(numOfUniforms);
      for (u32 i = 0; i < numOfUniforms; ++i)
      {

        glslVarInfo& currInfo = a_infoOut[i];
        glGetActiveUniform(a_shaderProgram.GetHandle(), i, g_buffSize,
                           &currInfo.m_nameLength, &currInfo.m_arraySize,
                           &currInfo.m_type, currInfo.m_name.Get());
      }

      glsl_var_info_cont_type::iterator itr, itrEnd;
      for (itr = a_infoOut.begin(), itrEnd = a_infoOut.end();
           itr != itrEnd; ++itr)
      {
        itr->m_location = glGetUniformLocation
          (a_shaderProgram.GetHandle(), itr->m_name.Get());
      }
    }

    void DoSetUniform(const glslVarInfo& a_info, const Uniform& a_uniform)
    {
      using namespace core;

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          const f32& f = a_uniform.GetValueAs<f32>();
          glUniform1f(a_info.m_location, f);
          break;
        }
      case GL_FLOAT_VEC2:
        {
          const Vec2f32& v = a_uniform.GetValueAs<Vec2f32>();
          glUniform2f(a_info.m_location, v[0], v[1]);
        }
      case GL_FLOAT_VEC3:
        {
          const Vec3f32& v = a_uniform.GetValueAs<Vec3f32>();
          glUniform3f(a_info.m_location, v[0], v[1], v[2]);
          break;
        }
      case GL_FLOAT_VEC4:
        {
          const Vec4f32& v = a_uniform.GetValueAs<Vec4f32>();
          glUniform4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          break;
        }
      case GL_INT:
        {
          const s32& i = a_uniform.GetValueAs<s32>();
          glUniform1i(a_info.m_location, i);
          break;
        }
      case GL_INT_VEC2:
        {
          const Tuple2s32& t = a_uniform.GetValueAs<Tuple2s32>();
          glUniform2i(a_info.m_location, t[0], t[1]);
          break;
        }
      case GL_INT_VEC3:
        {
          const Tuple3s32& t = a_uniform.GetValueAs<Tuple3s32>();
          glUniform3i(a_info.m_location, t[0], t[1], t[2]);
          break;
        }

      case GL_INT_VEC4:
        {
          const Tuple4s32& t = a_uniform.GetValueAs<Tuple4s32>();
          glUniform4i(a_info.m_location, t[0], t[1], t[2], t[3]);
          break;
        }
      case GL_FLOAT_MAT2:
        {
          const Mat2f32& m = a_uniform.GetValueAs<Mat2f32>();
          TLOC_ASSERT(a_info.m_arraySize == Mat2f32::k_TableSize,
            "Mismatched uniform array size!");
          glUniformMatrix2fv(a_info.m_location, GL_FALSE,
            Mat2f32::k_TableSize, m);
          break;
        }
      case GL_FLOAT_MAT3:
        {
          const Mat3f32& m = a_uniform.GetValueAs<Mat3f32>();
          TLOC_ASSERT(a_info.m_arraySize == Mat3f32::k_TableSize,
            "Mismatched uniform array size!");
          glUniformMatrix3fv(a_info.m_location, GL_FALSE,
            Mat3f32::k_TableSize, m);
          break;
        }
      case GL_FLOAT_MAT4:
        {
          const Mat4f32& m = a_uniform.GetValueAs<Mat4f32>();
          TLOC_ASSERT(a_info.m_arraySize == Mat3f32::k_TableSize,
            "Mismatched uniform array size!");
          glUniformMatrix4fv(a_info.m_location, GL_FALSE,
            Mat3f32::k_TableSize, m);
          break;
        }
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

  ShaderProgram::error_type ShaderProgram::LoadAllUniforms()
  {
    TLOC_ASSERT(m_flags[shader_linked],
                "Shader not linked - did you forget to call Link()?");

    glsl_var_info_cont_type uniCont;
    DoGetUniformInfo(*this, uniCont);

    uniform_cont_type::iterator itr, itrEnd;
    for (itr = m_uniforms.begin(), itrEnd = m_uniforms.end(); itr != itrEnd;
         ++itr)
    {
      glsl_var_info_cont_type::iterator itrInfo, itrInfoEnd;
      for (itrInfo = uniCont.begin(), itrInfoEnd = uniCont.end();
           itrInfo != itrInfoEnd; ++itrInfo)
      {
        if (itr->GetName().compare(itrInfo->m_name.Get()) == 0)
        {
          if (itr->GetType() == itrInfo->m_type && itrInfo->m_location != -1)
          {
            DoSetUniform(*itrInfo, *itr);

            // Check with OpenGL
            if (gl::Error().Failed())
            {
              return error::error_shader_uniform_not_attached;
            }
          }
          else
          {
            // TODO: Convert this assertion to a log
            TLOC_ASSERT(false, "Mismatched uniform type!");
            return ErrorFailure();
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

  ShaderProgram::error_type
    ShaderProgram::Enable() const
  {
    glUseProgram(GetHandle());
    if (gl::Error().Failed())
    {
      return error::error_shader_program_enable;
    }

    return ErrorSuccess();
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