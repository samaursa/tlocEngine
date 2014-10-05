#include "tlocShaderOperator.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/containers/tlocArray.inl.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocShaderVariableInfo.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

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
      k_attributesCached,
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
      DoSet(const ShaderVariableInfo& a_info, const Attribute& a_attribute, 
            tl_size a_interleaveIndex)
    {
      TLOC_UNUSED(a_interleaveIndex);

      using namespace core;

      bool isArray = a_attribute.IsArray();
      bool isShared = a_attribute.IsArrayPtr();
      bool isVertexArray = a_attribute.IsAttribArray();

      DoSetReturn toRet;

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          if (isArray == false)
          {
            const f32& f =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<f32>()
              : a_attribute.GetValueAs<f32>();
            glVertexAttrib1f(a_info.m_location, f);
          }
          else if (isVertexArray)
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 1, GL_FLOAT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttrib1fv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_FLOAT_VEC2:
        {
          typedef Vec2f32                     data_type;

          if (isArray == false)
          {
            const Vec2f32& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Vec2f32>()
              : a_attribute.GetValueAs<Vec2f32>();
            glVertexAttrib2f(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 2, GL_FLOAT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttrib2fv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
      case GL_FLOAT_VEC3:
        {
          typedef Vec3f32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Vec3f32>()
              : a_attribute.GetValueAs<Vec3f32>();
            glVertexAttrib3f(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 3, GL_FLOAT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              f32       const * farawFloat = reinterpret_cast<f32 const*>(faraw);
              glVertexAttrib3fv(a_info.m_location, farawFloat);
            }
          }
          break;
        }
      case GL_FLOAT_VEC4:
        {
          typedef Vec4f32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Vec4f32>()
              : a_attribute.GetValueAs<Vec4f32>();
            glVertexAttrib4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 4, GL_FLOAT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttrib4fv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      case GL_INT:
        {
          if (isArray == false)
          {
            const s32& f =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<s32>()
              : a_attribute.GetValueAs<s32>();
            glVertexAttribI1i(a_info.m_location, f);
          }
          else if (isVertexArray)
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 1, GL_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI1iv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_INT_VEC2:
        {
          typedef Tuple2s32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Tuple2s32>()
              : a_attribute.GetValueAs<Tuple2s32>();
            glVertexAttribI2i(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 2, GL_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttribI2iv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
      case GL_INT_VEC3:
        {
          typedef Tuple3s32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Tuple3s32>()
              : a_attribute.GetValueAs<Tuple3s32>();
            glVertexAttribI3i(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 3, GL_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttribI3iv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
      case GL_INT_VEC4:
        {
          typedef Tuple4s32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Tuple4s32>()
              : a_attribute.GetValueAs<Tuple4s32>();
            glVertexAttribI4i(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 4, GL_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttribI4iv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT:
        {
          if (isArray == false)
          {
            const u32& f =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<u32>()
              : a_attribute.GetValueAs<u32>();
            glVertexAttribI1ui(a_info.m_location, f);
          }
          else if (isVertexArray)
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 1, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI1uiv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC2:
        {
          typedef Tuple2u32                     data_type;
          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Tuple2u32>()
              : a_attribute.GetValueAs<Tuple2u32>();
            glVertexAttribI2ui(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 2, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttribI2uiv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC3:
        {
          typedef Tuple3u32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Tuple3u32>()
              : a_attribute.GetValueAs<Tuple3u32>();
            glVertexAttribI3ui(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 3, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttribI3uiv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC4:
        {
          typedef Tuple4u32                     data_type;

          if (isArray == false)
          {
            const data_type& v =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<Tuple4u32>()
              : a_attribute.GetValueAs<Tuple4u32>();
            glVertexAttribI4ui(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 4, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              gl::vertex_attrib_array::EnableIfDisabled(a_info.m_location);
              toRet.VertexAttribArrayIndex(a_info.m_location);
            }
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsArrayPtr<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              data_type::value_type const * farawFlat =
                reinterpret_cast<data_type::value_type const*>(faraw);
              glVertexAttribI4uiv(a_info.m_location, farawFlat);
            }
          }
          break;
        }
#endif
      default:
        {
          TLOC_ASSERT_FALSE("Unsupported Attribute type!");
        }
      }

      return toRet;
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    DoSetReturn
      DoSet(const ShaderVariableInfo& a_info, const AttributeVBO& a_attribute, 
            tl_size)
    {
      using namespace core;

      DoSetReturn toRet;

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          AttributeVBO::bind_array_buffer vboBind(a_attribute);
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 1, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case GL_FLOAT_VEC2:
        {
          AttributeVBO::bind_array_buffer vboBind(a_attribute);
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case GL_FLOAT_VEC3:
        {
          AttributeVBO::bind_array_buffer vboBind(a_attribute);
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      case GL_FLOAT_VEC4:
        {
          AttributeVBO::bind_array_buffer vboBind(a_attribute);
          gl::vertex_attrib_array::Enable(a_info.m_location);
          glVertexAttribPointer(a_info.m_location, 4, GL_FLOAT, GL_FALSE, 0, 0);
          break;
        }
      default:
        {
          TLOC_ASSERT_FALSE("Unsupported AttributeVBO type!");
        }
      }

      return toRet;
    }
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
    typedef typename svcInfo::const_iterator      svcInfo_const_iterator;
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
        TLOC_LOG_GFX_WARN() << "Uniform*/Attribute*/AttributeVBO ("
          << shaderVarPtr->GetName()
          << ") Does not have a type. Did you forget to populate it with data?";
        shaderVarPtr->SetEnabled(false);
        continue;
      }

      // attributes can have upto four names due to interleaving (see the
      // Vertex_T<> class) - this includes VBOs
      for (tl_size interleaveIndex = 0; 
           interleaveIndex < itr->second.size(); 
           ++interleaveIndex)
      {
        // this is over-ridden with the correct location if found
        itr->second[interleaveIndex] = g_unableToFindIndex;

        ShaderOperator::index_type index = 0;
        svcInfo_const_iterator itrInfo, itrInfoEnd;
        for (itrInfo = a_shaderVarsInfo.begin(),
             itrInfoEnd = a_shaderVarsInfo.end();
             itrInfo != itrInfoEnd; ++itrInfo)
        {
          if ( shaderVarPtr->GetName(interleaveIndex).compare(itrInfo->m_name.get()) == 0)
          {
            if ( shaderVarPtr->GetType() == itrInfo->m_type &&
                itrInfo->m_location != g_unableToFindIndex)
            {
              itr->second[interleaveIndex] = index;

              DoSetReturn doSetRet = 
                DoSet(a_shaderVarsInfo[itr->second[interleaveIndex] ], 
                      *shaderVarPtr, interleaveIndex);

              variableLocations.push_back(doSetRet);

              TLOC_LOG_GFX_WARN_IF(gl::Error().Succeeded() == false)
                << "glUniform*/glAttribute* failed for: " << shaderVarPtr->GetName();
              break;
            }
            else
            {
              TLOC_LOG_GFX_WARN() << "Mismatched uniform/attribute type for: "
                << shaderVarPtr->GetName();
              retError = ErrorFailure;
              break;
            }
          }
          ++index;
        }

        // We could not find the user specified uniform in the shader
        if (itrInfo == itrInfoEnd)
        {
          TLOC_LOG_GFX_WARN() << "Uniform/Attribute type not found in shader: "
            << shaderVarPtr->GetName();
          retError = ErrorFailure;
        }
      }
    }

    return core::MakePair(retError, variableLocations);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::
    ShaderOperator()
    : m_flags(k_count)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::
    ~ShaderOperator()
  {
    for (index_iterator itr = m_enabledVertexAttrib.begin(),
                        itrEnd = m_enabledVertexAttrib.end();
                        itr != itrEnd; ++itr)
    {
      TLOC_ASSERT(*itr < gl::Get<gl::p_get::MaxVertexAttribs>(),
        "Vertex attribute location is greater than maximum number of attributes");

      glDisableVertexAttribArray(*itr);
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::uniform_ptr
    ShaderOperator::
    AddUniform(const uniform_type& a_uniform)
  {
    TLOC_ASSERT(a_uniform.GetName().size() > 0, "Uniform name is empty");
    m_uniforms.push_back(core::MakePair(uniform_vso(MakeArgs(a_uniform)),
                                        index_type(-1)) );
    m_flags.Unmark(k_uniformsCached);

    return m_uniforms.back().first.get();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::attribute_ptr
    ShaderOperator::
    AddAttribute(const attribute_type& a_attribute)
  {
    TLOC_ASSERT(a_attribute.GetName().size() > 0, "Attribute name is empty");

    const gfx_t::gl_int type = a_attribute.GetType();

    if (type == TLOC_GL_POSITION2F_NORMAL3F ||
        type == TLOC_GL_POSITION3F_NORMAL3F ||
        type == TLOC_GL_POSITION2F_TEXTURE2F ||
        type == TLOC_GL_POSITION3F_TEXTURE2F ||
        type == TLOC_GL_POSITION2F_COLOR4F ||
        type == TLOC_GL_POSITION3F_COLOR4F)
    {
      TLOC_ASSERT(a_attribute.GetSecondName().size() > 0, "Second attribute name is empty");
    }
    else if (type == TLOC_GL_POSITION2F_NORMAL3F_COLOR4F ||
             type == TLOC_GL_POSITION3F_NORMAL3F_COLOR4F ||
             type == TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F ||
             type == TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F)
    {
      TLOC_ASSERT(a_attribute.GetSecondName().size() > 0, "Second attribute name is empty");
      TLOC_ASSERT(a_attribute.GetThirdName().size() > 0, "Third attribute name is empty");
    }
    else if (type == TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F ||
             type == TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F )
    {
      TLOC_ASSERT(a_attribute.GetSecondName().size() > 0, "Second attribute name is empty");
      TLOC_ASSERT(a_attribute.GetThirdName().size() > 0, "Third attribute name is empty");
      TLOC_ASSERT(a_attribute.GetFourthName().size() > 0, " attribute name is empty");
    }

    m_attributes.push_back(core::MakePair(attribute_vso(MakeArgs(a_attribute)),
                                          index_type(-1)) );
    m_flags.Unmark(k_attributesCached);

    return m_attributes.back().first.get();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::vbo_ptr
    ShaderOperator::
    AddVBO(const vbo_type& a_vbo)
  {
    TLOC_ASSERT(a_vbo.GetName().size() > 0, "VBO name is empty");

    m_VBOs.push_back(vbo_vso(MakeArgs(a_vbo)) );
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
    RemoveAttribute(const attribute_iterator& a_attribute)
  {
    m_attributes.erase(a_attribute);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    RemoveVBO(const vbo_iterator& a_vbo)
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
    RemoveAllAttributes()
  {
    m_attributes.clear();
    ClearAttributesCache();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    ShaderOperator::
    RemoveAllVBOs()
  {
    m_VBOs.clear();
    ClearVBOsCache();
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
        TLOC_LOG_GFX_WARN()
          << "Uniform (" << itr->first->GetName()
          << ") cannot be set. Did you forget to call PrepareAllUniforms?";
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    EnableAllAttributes(const ShaderProgram& a_shaderProgram) const
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_attributesCached),
      "Attributes not loaded - did you forget to call PrepareAllAttributes()?");

    const glsl_var_info_cont_type&
      attrCont = a_shaderProgram.GetAttributeInfoRef();

    attribute_cont_type::const_iterator itr, itrEnd;
    for (itr = m_attributes.begin(), itrEnd = m_attributes.end();
         itr != itrEnd; ++itr)
    {
      if (itr->first->IsEnabled() == false)
      { continue; }

      const_attribute_ptr attribPtr = itr->first.get();

      // we don't warn for g_unableToFindIndex because the user has already
      // been warned about that
      for (size_type interleavedIndex = 0; 
           interleavedIndex < index_cont_4::k_capacity; ++interleavedIndex)
      {
        if (itr->second[interleavedIndex] >= 0)
        {
          DoAssertVariablesMatch(attrCont[itr->second[0] ], attribPtr);
          DoSet(attrCont[itr->second[interleavedIndex] ], *attribPtr, interleavedIndex);
        }
        else if (itr->second[interleavedIndex] == g_invalidIndex)
        {
          TLOC_LOG_GFX_WARN()
            << "Attribute (" << itr->first->GetName()
            << ") cannot be set. Did you forget to call PrepareAllAttributes?";
        }
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::vao_bind_ptr
    ShaderOperator::
    EnableAllVBOs(const ShaderProgram& a_shaderProgram) const
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_attributesCached),
      "Attributes not loaded - did you forget to call PrepareAllAttributes()?");

    if (m_vao) { return core_sptr::MakeShared<vao_bind_type>(*m_vao); }
    
    return nullptr;
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
      if (GetNumberOfUniforms() == 0) { return retError; }

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
    PrepareAllAttributes(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(a_shaderProgram.IsEnabled(),
                "Shader not enabled - did you forget to call Enable()?");

    error_type retError = ErrorSuccess;

    if (m_flags.ReturnAndMark(k_attributesCached) == false)
    {

      // bail early
      if (GetNumberOfAttributes() == 0) { return retError; }

      const glsl_var_info_cont_type&
        attrCont = a_shaderProgram.GetAttributeInfoRef();

      ErrorShaderVarIndexContPair errAndIndex = DoPrepareVariables(m_attributes, attrCont);
      retError = errAndIndex.first;

      for (do_set_return_cont::iterator itr = errAndIndex.second.begin(),
           itrEnd = errAndIndex.second.end(); itr != itrEnd; ++itr)
      {
        index_type index = itr->m_vertexAttribArrayIndex;

        TLOC_LOG_GFX_WARN_IF
          (core::find_all(m_enabledVertexAttrib, index) 
          != m_enabledVertexAttrib.end()) << "Vertex attribute at index " 
          << index << " over-ridden by gl::Attribute";


        if (index >= 0)
        { m_enabledVertexAttrib.push_back(index); }
      }
    }

    return retError;

  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::error_type
    ShaderOperator::
    PrepareAllVBOs(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(a_shaderProgram.IsEnabled(),
                "Shader not enabled - did you forget to call Enable()?");

    error_type retError = ErrorSuccess;

    if (m_flags.ReturnAndMark(k_VBOsCached) == false)
    {
      // bail early
      if (GetNumberOfVBOs() == 0) { return retError; }

      if (!m_vao) { m_vao = core_sptr::MakeShared<vao_type>(); }

      VertexArrayObject::Bind vaoBind(*m_vao);

      const glsl_var_info_cont_type& 
        attrCont = a_shaderProgram.GetAttributeInfoRef();

      ErrorShaderVarIndexContPair errAndIndex = DoPrepareVariables(m_VBOs, attrCont);
      retError = errAndIndex.first;

      for (do_set_return_cont::iterator itr = errAndIndex.second.begin(),
           itrEnd = errAndIndex.second.end(); itr != itrEnd; ++itr)
      {
        index_type index = itr->m_vertexAttribArrayIndex;

        TLOC_LOG_GFX_WARN_IF
          (core::find_all(m_enabledVertexAttrib, index) 
          != m_enabledVertexAttrib.end()) << "Vertex attribute at index " 
          << index << " over-ridden by gl::AttributeVBO";

        if (index >= 0)
        { m_enabledVertexAttrib.push_back(index); }
      }
    }

    return retError;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::uniform_iterator ShaderOperator::
    begin_uniforms()
  {
    return m_uniforms.begin();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::uniform_iterator ShaderOperator::
    end_uniforms()
  {
    return m_uniforms.end();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::attribute_iterator ShaderOperator::
    begin_attributes()
  {
    return m_attributes.begin();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ShaderOperator::attribute_iterator ShaderOperator::
    end_attributes()
  {
    return m_attributes.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ShaderOperator::
    reserve_uniforms(size_type a_capacity)
  { m_uniforms.reserve(a_capacity); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ShaderOperator::
    reserve_attributes(size_type a_capacity)
  { m_attributes.reserve(a_capacity); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearAttributesCache()
  { 
    m_enabledVertexAttrib.clear();
    m_flags.Unmark(k_attributesCached);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearUniformsCache()
  { m_flags.Unmark(k_uniformsCached); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearVBOsCache()
  { 
    m_enabledVertexAttrib.clear();
    m_flags.Unmark(k_VBOsCached);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearCache()
  {
    ClearAttributesCache();
    ClearUniformsCache();
    ClearVBOsCache();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ShaderOperator::
    IsAttributesCached()
  { return m_flags[k_attributesCached]; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ShaderOperator::
    IsUniformsCached()
  { return m_flags[k_uniformsCached]; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ShaderOperator::
    IsVBOsCached()
  { return m_flags[k_VBOsCached]; }

};};};


//------------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ShaderOperator);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(ShaderOperator);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(ShaderOperator::uniform_pair_type);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(ShaderOperator::attribute_pair_type);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(vbo_vso);
