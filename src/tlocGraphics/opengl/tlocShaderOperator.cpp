#include "tlocShaderOperator.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/configs/tlocBuildConfig.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocShaderVariableInfo.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

// GL_SAMPLER_2D_SHADOW only exists in the extentions in OpenGLES 2.0
#if !defined(GL_SAMPLER_2D_SHADOW) && defined(GL_SAMPLER_2D_SHADOW_EXT)
#define GL_SAMPLER_2D_SHADOW  GL_SAMPLER_2D_SHADOW_EXT
#endif

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace gl {

  namespace {

    const ShaderOperator::index_type g_invalidIndex = -2;
    const ShaderOperator::index_type g_unableToFindIndex = -1;

  };

  using namespace math::types;
  using namespace core::containers;
  using namespace core::smart_ptr;
  using namespace core::data_structs;

  namespace
  {
    typedef core::containers::
      tl_array<ShaderVariableInfo>::type   glsl_var_info_cont_type;

    //------------------------------------------------------------------------
    // Cacher

    ///-------------------------------------------------------------------------
    /// @brief Unsafe class, only used internally when variables are cached
    ///-------------------------------------------------------------------------
    struct GLSLCacher_I
    {
      typedef tl_int    data_type;

      gfx_t::gl_int     m_location;
      gfx_t::gl_int     m_arraySize;
      bool              m_isArray;
      void*             m_data;
    };

    struct GLSLUniformCacher : GLSLCacher_I
    {
      typedef GLSLCacher_I::data_type   data_type;

      enum {data_float, data_float2, data_float3};

      void LoadUniform()
      {
      }

      data_type   m_dataType;
    };

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      k_uniformsCached = 0,
      k_VBOsCached,
      k_count
    };

    // -----------------------------------------------------------------------
    // DoSetReturn

    struct DoSetReturn
    {
    public:
      typedef DoSetReturn                               this_type;


    public:
      DoSetReturn()
        : m_vertexAttribArrayIndex(g_unableToFindIndex)
        , m_location(g_unableToFindIndex)
      { }

      bool IsVertexAttribArrayEnabled()
      { return m_vertexAttribArrayIndex == -1; }

      TLOC_DECL_PARAM_VAR(GLint, VertexAttribArrayIndex, m_vertexAttribArrayIndex);
      TLOC_DECL_PARAM_VAR(GLint, Location, m_location);
    };
    typedef core_conts::Array<DoSetReturn>              do_set_return_cont;

    typedef core::Pair<ShaderOperator::error_type, 
                       DoSetReturn >                    ErrorShaderVarIndexPair;

    typedef core::Pair<ShaderOperator::error_type, 
                       do_set_return_cont >             ErrorShaderVarIndexContPair;

    //------------------------------------------------------------------------
    // Functions

    DoSetReturn
      DoSet(const ShaderVariableInfo& a_info, const Uniform& a_uniform, tl_size)
    {
      using namespace core;

      bool isArray = a_uniform.IsArray();
      bool isShared = a_uniform.IsArrayPtr();

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          typedef f32                     data_type;

          if (isArray == false)
          {
            data_type f =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform1f(a_info.m_location, f);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
            GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
            glUniform1fv(a_info.m_location, arraySize, faraw);
          }
          break;
        }
      case GL_FLOAT_VEC2:
        {
          typedef Vec2f32           data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform2f(a_info.m_location, v[0], v[1]);
          }
          else
          {
            typedef Vec2f32                 data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform2fv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_FLOAT_VEC3:
        {
          typedef Vec3f32                 data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform3f(a_info.m_location, v[0], v[1], v[2]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform3fv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_FLOAT_VEC4:
        {
          typedef Vec4f32                 data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform4fv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_INT:
        {
          typedef s32                     data_type;

          if (isArray == false)
          {
            data_type i =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform1i(a_info.m_location, i);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform1iv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_INT_VEC2:
        {
          typedef Tuple2s32               data_type;

          if (isArray == false)
          {
            const data_type& t =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform2i(a_info.m_location, t[0], t[1]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform2iv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_INT_VEC3:
        {
          typedef Tuple3s32               data_type;

          if (isArray == false)
          {
            const data_type& t =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform3i(a_info.m_location, t[0], t[1], t[2]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform3iv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }

      case GL_INT_VEC4:
        {
          typedef Tuple4s32               data_type;

          if (isArray == false)
          {
            const data_type& t =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform4i(a_info.m_location, t[0], t[1], t[2], t[3]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform4iv(a_info.m_location, arraySize, faraw);
            }
          }

          break;
        }
#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      case GL_UNSIGNED_INT:
        {
          typedef u32                     data_type;

          if (isArray == false)
          {
            data_type i =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform1ui(a_info.m_location, i);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform1uiv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC2:
        {
          typedef Tuple2u32               data_type;

          if (isArray == false)
          {
            const data_type& t =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform2ui(a_info.m_location, t[0], t[1]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform2uiv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC3:
        {
          typedef Tuple3u32               data_type;

          if (isArray == false)
          {
            const data_type& t =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform3ui(a_info.m_location, t[0], t[1], t[2]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform3uiv(a_info.m_location, arraySize, faraw);
            }
          }
          break;
        }

      case GL_UNSIGNED_INT_VEC4:
        {
          typedef Tuple4u32               data_type;

          if (isArray == false)
          {
            const data_type& t =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform4ui(a_info.m_location, t[0], t[1], t[2], t[3]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<array_type>()
              : a_uniform.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type::value_type const * faraw =
                reinterpret_cast<data_type::value_type const*>(&(fa[0]));
              GLint arraySize = core::utils::CastNumber<u32>(fa.size() );
              glUniform4uiv(a_info.m_location, arraySize, faraw);
            }
          }

          break;
        }
#endif
      case GL_FLOAT_MAT2:
        {
          const GLint matSize = 2 * 2;
          TLOC_STATIC_ASSERT( matSize == Mat2f32::k_size,
                              Mismatched_uniform_array_size );
          TLOC_UNUSED(matSize);

          typedef f32                 data_type;

          const Mat2f32& m =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<Mat2f32>()
              : a_uniform.GetValueAs<Mat2f32>();

          data_type const * faraw = reinterpret_cast<data_type const*>(&(m[0]));
          glUniformMatrix2fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_FLOAT_MAT3:
        {
          const GLint matSize = 3 * 3;
          TLOC_STATIC_ASSERT( matSize == Mat3f32::k_size,
                              Mismatched_uniform_array_size );
          TLOC_UNUSED(matSize);

          typedef f32                 data_type;

          const Mat3f32& m =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<Mat3f32>()
              : a_uniform.GetValueAs<Mat3f32>();

          data_type const * faraw = reinterpret_cast<data_type const*>(&(m[0]));
          glUniformMatrix3fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_FLOAT_MAT4:
        {
          const GLint matSize = 4 * 4;
          TLOC_STATIC_ASSERT( matSize == Mat4f32::k_size,
                              Mismatched_uniform_array_size );
          TLOC_UNUSED(matSize);

          typedef f32                 data_type;

          const Mat4f32& m =
              isShared
              ? *a_uniform.GetValueAsArrayPtr<Mat4f32>()
              : a_uniform.GetValueAs<Mat4f32>();

          data_type const * faraw = reinterpret_cast<data_type const*>(&(m[0]));
          glUniformMatrix4fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_SAMPLER_2D:
      case GL_SAMPLER_2D_SHADOW:
        {
          using namespace texture_units;

          const TextureObject& m =
            isShared
            ? *a_uniform.GetValueAsArrayPtr<TextureObject>()
            : a_uniform.GetValueAs<TextureObject>();

          GLint texImgUnit;
          if (m.HasReservedTextureUnit())
          { texImgUnit = m.GetReservedTexImageUnit(); }
          else
          { image_units::GetNext(texImgUnit); }

          image_units::Activate(texImgUnit);
          m.Bind();
          glUniform1i(a_info.m_location,
                      FromTextureImageUnit(texImgUnit));
          break;
        }
      default:
        {
          TLOC_ASSERT_FALSE("Unsupported Uniform type!");
        }
      }

      return DoSetReturn();
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    DoSetReturn
      DoSet(const ShaderVariableInfo& a_info, const AttributeVBO& a_attributeVBO,
            tl_size a_interleaveIndex)
    {
      using namespace core;

      DoSetReturn toRet;

      const auto attributeVBOType = a_attributeVBO.GetType();

      switch(attributeVBOType)
      {
      case GL_INT:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 1, GL_INT, GL_FALSE, 0, 0);
          break;
        }
      case GL_INT_VEC2:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 2, GL_INT, GL_FALSE, 0, 0);
          break;
        }
      case GL_INT_VEC3:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 3, GL_INT, GL_FALSE, 0, 0);
          break;
        }
      case GL_INT_VEC4:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 4, GL_INT, GL_FALSE, 0, 0);
          break;
        }
      case GL_UNSIGNED_INT:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 1, GL_INT, GL_FALSE, 0, 0);
          break;
        }
#ifdef TLOC_OS_WIN // TODO: Change to TLOC_GFX_PLATFORM_GL
      case GL_UNSIGNED_INT_VEC2:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 2, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
          break;
        }
      case GL_UNSIGNED_INT_VEC3:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
          break;
        }
      case GL_UNSIGNED_INT_VEC4:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
          break;
        }
#endif
      case GL_FLOAT:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 1, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case GL_FLOAT_VEC2:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case GL_FLOAT_VEC3:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case GL_FLOAT_VEC4:
        {
          VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 4, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case TLOC_GL_POSITION2F_NORMAL3F:
      case TLOC_GL_POSITION2F_TEXTURE2F:
      case TLOC_GL_POSITION2F_COLOR4F:
      case TLOC_GL_POSITION2F_NORMAL3F_COLOR4F:
      case TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F:
      case TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F:

      case TLOC_GL_POSITION3F_NORMAL3F:
      case TLOC_GL_POSITION3F_TEXTURE2F:
      case TLOC_GL_POSITION3F_COLOR4F:
      case TLOC_GL_POSITION3F_NORMAL3F_COLOR4F:
      case TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F:
      case TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F:

      case GL_FLOAT_MAT2:
      case GL_FLOAT_MAT3:
      case GL_FLOAT_MAT4:
      case TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F_ORIENTATION:
      case TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F_ORIENTATION:
       {
          // handle TLOC_GL types
          // the interleaveIndex = the index of the interleaved attribute
          // e.g: if it is 0 (Position3F), 1(Normal3F) etc.
          gl::AttributeVBO::StrideInfo si =
            a_attributeVBO.GetStrideInfo(a_interleaveIndex);

          // iteration number is 1 unless a Mat2/Mat3/Mat4 is encountered
          tl_int iterations = si.m_totalElements / si.m_numElements;

          for (tl_int i = 0; i < iterations; ++i)
          {
            // substride is 0 unless it is a Mat2/Mat3/Mat4 where Mat*::vec_type's 
            // size is the substride in each iteration
            const tl_size subStride = sizeof(f32) * si.m_numElements * i;

            VertexBufferObject::bind_array vboBind(a_attributeVBO.GetVBO());
            gl::vertex_attrib_array::Enable(a_info.m_location + i);
            glVertexAttribPointer(a_info.m_location + i, 
                                  si.m_numElements,
                                  GL_FLOAT, 
                                  GL_FALSE, 
                                  si.m_strideInBytes, 
                                  (void*)(sizeof(f32) * si.m_dataStartIndex + subStride));
          }

          break;
        }
      default:
        {
          TLOC_ASSERT_FALSE("Unsupported AttributeVBO type!");
        }
      }

      return toRet;
    }

    template <typename T_ShaderVariableContainer,
    typename T_ShaderVariableInfoContainer>
    ErrorShaderVarIndexContPair
    DoPrepareVariables(T_ShaderVariableContainer& a_shaderUserVars,
                       const T_ShaderVariableInfoContainer& a_shaderVarsInfo)
    {
      typedef T_ShaderVariableContainer             svc;
      typedef T_ShaderVariableInfoContainer         svcInfo;
      typedef typename svc::iterator                svc_iterator;
      typedef typename svcInfo::iterator            svcInfo_iterator;
      typedef typename svc::value_type::
              first_type::pointer                   shader_var_ptr;

      ShaderOperator::error_type retError = ErrorSuccess;

      core_conts::Array<DoSetReturn> variableLocations;

      svc_iterator itr, itrEnd;
      for (itr = a_shaderUserVars.begin(), itrEnd = a_shaderUserVars.end();
           itr != itrEnd; ++itr)
      {
        shader_var_ptr shaderVarPtr = itr->first.get();

        if (shaderVarPtr->IsEnabled() == false)
        { continue; }

        if (shaderVarPtr->GetType() == GL_NONE)
        {
          TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Uniform*/Attribute*/AttributeVBO ("
            << shaderVarPtr->GetName()
            << ") Does not have a type. Did you forget to populate it with data?";
          shaderVarPtr->SetEnabled(false);
          continue;
        }

        // copy of a_shaderVarsInfo is used because we remove matched variables
        svcInfo svcInfoCopy(a_shaderVarsInfo);

        // attributes can have upto four names due to interleaving (see the
        // Vertex_T<> class) - this includes VBOs
        for (gfx_t::gl_enum interleaveIndex = 0;
             interleaveIndex < itr->second.size(); 
             ++interleaveIndex)
        {
          // this is over-ridden with the correct location if found
          itr->second[interleaveIndex] = g_unableToFindIndex;

          ShaderOperator::index_type index = 0;
          svcInfo_iterator itrInfo, itrInfoEnd;
          for (itrInfo = svcInfoCopy.begin(),
               itrInfoEnd = svcInfoCopy.end();
               itrInfo != itrInfoEnd; ++itrInfo)
          {
            if ( shaderVarPtr->GetName(interleaveIndex).compare(itrInfo->m_name.get()) == 0)
            {
              gfx_t::gl_enum shaderVarType = shaderVarPtr->GetType();

              if (shaderVarType >= TLOC_GL_POSITION2F &&
                  shaderVarType <= TLOC_GL_ORIENTATION4F)
              {
                shaderVarType = shaderVarPtr->GetInterleavedType(interleaveIndex);
              }

              if ( shaderVarType == itrInfo->m_type &&
                   itrInfo->m_location != g_unableToFindIndex)
              {
                itr->second[interleaveIndex] = index;
                DoSetReturn doSetRet = DoSet(*itrInfo, *shaderVarPtr, interleaveIndex);
                variableLocations.push_back(doSetRet);

                TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(gl::Error().Succeeded() == false)
                  << "glUniform*/glAttribute* failed for: " << shaderVarPtr->GetName();

                itrInfo = svcInfoCopy.erase(itrInfo);

                break;
              }
              else
              {
                TLOC_LOG_GFX_WARN_FILENAME_ONLY() 
                  << "Mismatched uniform/attribute type for: "
                  << shaderVarPtr->GetName();
                shaderVarPtr->SetEnabled(false);
                retError = ErrorFailure;
                break;
              }
            }
            ++index;
          }

          // We could not find the user specified uniform in the shader
          if (itrInfo == itrInfoEnd)
          {
            TLOC_LOG_GFX_WARN_FILENAME_ONLY() 
              << "Uniform/Attribute type not found in shader: "
              << shaderVarPtr->GetName();
            shaderVarPtr->SetEnabled(false);
            retError = ErrorFailure;
          }
        }
      }

      return core::MakePair(retError, variableLocations);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Container, typename T_BuildConfig>
    bool 
      DoWillAnyPointersInvalidate(T_Container& a_variables, T_BuildConfig)
    {
      // we have enough capacity to not invalidate previous pointers
      if (a_variables.size() < a_variables.capacity())
      { return false; }

      typedef typename T_Container::iterator itr_type;
     
      itr_type itr = a_variables.begin();
      itr_type itrEnd = a_variables.end();

      for ( ; itr != itrEnd; ++itr)
      {
        // 1 is cached in the VSO and 1 is when we call .get(). Any other
        // references and we return true (so that a warning can be issued)
        if (itr->first.get().use_count() > 2)
        { return true; }
      }

      return false;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Iterator>
    bool 
      DoWillAnyPointersInvalidate(T_Iterator , T_Iterator , 
                                  core_cfg::p_build_config::Release)
    { return false; }
  }

  // ///////////////////////////////////////////////////////////////////////
  // ShaderOperator

  ShaderOperator::
    ShaderOperator()
    : m_flags(k_count)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::
    ~ShaderOperator()
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::uniform_ptr
    ShaderOperator::
    AddUniform(const uniform_type& a_uniform)
  {
    TLOC_ASSERT(a_uniform.GetName().size() > 0, "Uniform name is empty");
    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF
      (DoWillAnyPointersInvalidate(m_uniforms,
                                   core_cfg::BuildConfig::build_config_type()))
      << "Adding Uniform will invalidate previous Uniform pointers";

    m_uniforms.push_back(core::MakePair(uniform_vso(MakeArgs(a_uniform)),
                                        index_cont_1(1, -1)) );
    m_flags.Unmark(k_uniformsCached);

    return m_uniforms.back().first.get();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::attributeVBO_ptr
    ShaderOperator::
    AddAttributeVBO(const vbo_type& a_vbo)
  {
    TLOC_ASSERT(a_vbo.Validate() == ErrorSuccess, "VBO is invalid");
    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF
      (DoWillAnyPointersInvalidate(m_VBOs,
                                   core_cfg::BuildConfig::build_config_type()))
      << "Adding AttributeVBO will invalidate previous AttributeVBO pointers";

    index_cont indexCont(a_vbo.size_names(), -1);

    m_VBOs.push_back(core::MakePair(vbo_vso(MakeArgs(a_vbo)), indexCont) );
    m_flags.Unmark(k_VBOsCached);

    return m_VBOs.back().first.get();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    RemoveUniform(const uniform_iterator& a_uniform)
  {
    m_uniforms.erase(a_uniform);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    RemoveAttributeVBO(const attributeVBO_iterator& a_vbo)
  {
    m_VBOs.erase(a_vbo);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    RemoveAllUniforms()
  {
    m_uniforms.clear();
    ClearUniformsCache();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    RemoveAllAttributeVBOs()
  {
    m_VBOs.clear();
    ClearAttributeVBOsCache();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_ShaderVar, typename T_CachedVar>
  void
    DoAssertVariablesMatch(const T_ShaderVar& a_sVar, const T_CachedVar& a_cVar)
  {
    TLOC_UNUSED_2(a_sVar, a_cVar);
    TLOC_ASSERT(a_cVar->GetName().compare(a_sVar.m_name.get()) == 0,
      "Mismatched shader variable name - was variable name changed AFTER caching?"
      " Requires caching by calling PrepareAll*ShaderVariableType*() again");
    TLOC_ASSERT(a_sVar.m_type == a_cVar->GetType(),
      "Mismatched shader variable type - was variable type changed AFTER caching?"
      " Requires caching by calling PrepareAll*ShaderVariableType*() again");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void ShaderOperator::
    EnableAllUniforms(const ShaderProgram& a_shaderProgram) const
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_uniformsCached),
      "Uniforms not loaded - did you forget to call PrepareAllUniforms()?");

    const glsl_var_info_cont_type& uniCont = a_shaderProgram.GetUniformInfoRef();

    uniform_cont_type::const_iterator itr, itrEnd;
    for (itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
         itr != itrEnd; ++itr)
    {
      if (itr->first->IsEnabled() == false)
      { continue; }

      const_uniform_ptr  uniformPtr = itr->first.get();

      // we don't warn for g_unableToFindIndex because the user has already
      // been warned about that
      if (itr->second[0] >= 0)
      {
        DoAssertVariablesMatch(uniCont[itr->second[0] ], uniformPtr);
        DoSet(uniCont[itr->second[0] ], *uniformPtr, 0);
      }
      else if (itr->second[0] == g_invalidIndex)
      {
        TLOC_LOG_GFX_WARN_FILENAME_ONLY()
          << "Uniform (" << itr->first->GetName()
          << ") cannot be set. Did you forget to call PrepareAllUniforms?";
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::error_type
    ShaderOperator::
    PrepareAllUniforms(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(a_shaderProgram.IsEnabled(),
                "Shader not enabled - did you forget to call Enable()?");

    error_type retError = ErrorSuccess;

    if (m_flags.ReturnAndMark(k_uniformsCached) == false)
    {
      // bail early
      if (size_uniforms() == 0) { return retError; }

      const glsl_var_info_cont_type& uniCont = a_shaderProgram.GetUniformInfoRef();

      // no need to check for attrib index since glEnableAttribArray applies
      // to attributes only
      retError = DoPrepareVariables(m_uniforms, uniCont).first;
    }

    return retError;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::error_type
    ShaderOperator::
    PrepareAllAttributeVBOs(const ShaderProgram& a_shaderProgram, 
                            const vao_type& a_vao)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(a_shaderProgram.IsEnabled(),
                "Shader not enabled - did you forget to call Enable()?");

    error_type retError = ErrorSuccess;

    if (m_flags.ReturnAndMark(k_VBOsCached) == false)
    {
      // bail early
      if (size_attributeVBOs() == 0) { return retError; }

      VertexArrayObject::Bind vaoBind(a_vao);

      const glsl_var_info_cont_type& 
        attrCont = a_shaderProgram.GetAttributeInfoRef();

      ErrorShaderVarIndexContPair errAndIndex = DoPrepareVariables(m_VBOs, attrCont);
      retError = errAndIndex.first;
    }

    return retError;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::uniform_iterator 
    ShaderOperator::
    begin_uniforms()
  { return m_uniforms.begin(); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::uniform_iterator 
    ShaderOperator::
    end_uniforms()
  { return m_uniforms.end(); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::attributeVBO_iterator 
    ShaderOperator::
    begin_attributeVBOs()
  {
    return m_VBOs.begin();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::attributeVBO_iterator
    ShaderOperator::
    end_attributeVBOs()
  {
    return m_VBOs.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ShaderOperator::
    reserve_uniforms(size_type a_capacity)
  { m_uniforms.reserve(a_capacity); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ShaderOperator::
    reserve_attributeVBOs(size_type a_capacity)
  { m_VBOs.reserve(a_capacity); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    ClearUniformsCache()
  { m_flags.Unmark(k_uniformsCached); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    ClearAttributeVBOsCache()
  { 
    m_flags.Unmark(k_VBOsCached);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    ClearCache()
  {
    ClearUniformsCache();
    ClearAttributeVBOsCache();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    ShaderOperator::
    IsUniformsCached()
  { return m_flags[k_uniformsCached]; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    ShaderOperator::
    IsAttributeVBOsCached()
  { return m_flags[k_VBOsCached]; }

  // -----------------------------------------------------------------------

  namespace f_shader_operator {

    uniform_ptr
      GetUniform(ShaderOperator& a_so, BufferArg a_name)
    {
      using algos::shader_operator::compare::UniformName;
      typedef ShaderOperator::uniform_iterator      itr_type;

      uniform_ptr ptrToRet;
      
      itr_type itrBegin = a_so.begin_uniforms(),
               itrEnd   = a_so.end_uniforms();


      itr_type itr = core::find_if(itrBegin, itrEnd, UniformName(a_name));

      if (itr != a_so.end_uniforms()) { ptrToRet = itr->first.get(); }

      return ptrToRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    attributeVBO_ptr
      GetAttributeVBO(ShaderOperator& a_so, BufferArg a_name)
    {
      using algos::shader_operator::compare::AttributeVBOName;
      typedef ShaderOperator::attributeVBO_iterator      itr_type;

      attributeVBO_ptr ptrToRet;
      
      itr_type itrBegin = a_so.begin_attributeVBOs(),
               itrEnd   = a_so.end_attributeVBOs();

      itr_type itr = core::find_if(itrBegin, itrEnd, AttributeVBOName(a_name));

      if (itr != a_so.end_attributeVBOs()) { ptrToRet = itr->first.get(); }

      return ptrToRet;
    }

  };

};};};


//------------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ShaderOperator);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(ShaderOperator);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(ShaderOperator::uniform_pair_type);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(vbo_vso);
