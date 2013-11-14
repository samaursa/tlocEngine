#include "tlocShaderOperator.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/containers/tlocContainers.inl.h>

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

  using namespace math::types;
  using namespace core::containers;
  using namespace core::smart_ptr;
  using namespace core::data_structs;

  typedef core::Pair<ShaderOperator::error_type, GLint> ErrorAttribIndexPair;

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

      GLint   m_location;
      GLint   m_arraySize;
      bool    m_isArray;
      void*   m_data;
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
    // Variables

    // u32 because of OpenGL's types
    const u32 g_buffSize = ShaderVariableInfo::g_buffSize;

    //------------------------------------------------------------------------
    // Enums

    enum flags
    {
      k_uniformsCached = 0,
      k_attributesCached,
      k_count
    };

    bool DoCheckIfShaderIsAttached()
    {
      return Get<p_get::CurrentProgram>() != 0;
    }

    //------------------------------------------------------------------------
    // Functions

    GLint DoSet(const ShaderVariableInfo& a_info, const Uniform& a_uniform)
    {
      using namespace core;

      bool isArray = a_uniform.IsArray();
      bool isShared = a_uniform.IsShared();

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          typedef f32                     data_type;

          if (isArray == false)
          {
            data_type f =
              isShared
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform1f(a_info.m_location, f);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
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
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform3f(a_info.m_location, v[0], v[1], v[2]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform1i(a_info.m_location, i);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform2i(a_info.m_location, t[0], t[1]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform3i(a_info.m_location, t[0], t[1], t[2]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform4i(a_info.m_location, t[0], t[1], t[2], t[3]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform1ui(a_info.m_location, i);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform2ui(a_info.m_location, t[0], t[1]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform3ui(a_info.m_location, t[0], t[1], t[2]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
              ? *a_uniform.GetValueAsShared<data_type>()
              : a_uniform.GetValueAs<data_type>();
            glUniform4ui(a_info.m_location, t[0], t[1], t[2], t[3]);
          }
          else
          {
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_uniform.GetValueAsShared<array_type>()
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
          TLOC_ASSERT( matSize == Mat2f32::k_TableSize,
                       "Mismatched uniform array size!");
          TLOC_UNUSED(matSize);

          typedef f32                 data_type;

          const Mat2f32& m =
              isShared
              ? *a_uniform.GetValueAsShared<Mat2f32>()
              : a_uniform.GetValueAs<Mat2f32>();

          data_type const * faraw = reinterpret_cast<data_type const*>(&(m[0]));
          glUniformMatrix2fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_FLOAT_MAT3:
        {
          const GLint matSize = 3 * 3;
          TLOC_ASSERT( matSize == Mat3f32::k_TableSize,
                       "Mismatched uniform array size!");
          TLOC_UNUSED(matSize);

          typedef f32                 data_type;

          const Mat3f32& m =
              isShared
              ? *a_uniform.GetValueAsShared<Mat3f32>()
              : a_uniform.GetValueAs<Mat3f32>();

          data_type const * faraw = reinterpret_cast<data_type const*>(&(m[0]));
          glUniformMatrix3fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_FLOAT_MAT4:
        {
          const GLint matSize = 4 * 4;
          TLOC_ASSERT( matSize == Mat4f32::k_TableSize,
                       "Mismatched uniform array size!");
          TLOC_UNUSED(matSize);

          typedef f32                 data_type;

          const Mat4f32& m =
              isShared
              ? *a_uniform.GetValueAsShared<Mat4f32>()
              : a_uniform.GetValueAs<Mat4f32>();

          data_type const * faraw = reinterpret_cast<data_type const*>(&(m[0]));
          glUniformMatrix4fv(a_info.m_location, 1, GL_FALSE, faraw);
          break;
        }
      case GL_SAMPLER_2D:
        {
          const TextureObject& m =
            isShared
            ? *a_uniform.GetValueAsShared<TextureObject>()
            : a_uniform.GetValueAs<TextureObject>();

          TLOC_ASSERT(m.IsActive(),
            "TextureObject is NOT active - did you forget to call Activate()?");
          GLint texImgUnit = m.GetTextureImageUnit();

          ActivateTextureImageUnit(texImgUnit);
          m.Bind();
          glUniform1i(a_info.m_location,
                      GetTextureUnitFromTextureImageUnit(texImgUnit));
          break;
        }
      default:
        {
          TLOC_ASSERT(false, "Unsupported shader variable type!");
        }
      }

      return -1;
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    GLint DoSet(const ShaderVariableInfo& a_info, const Attribute& a_attribute)
    {
      using namespace core;

      bool isArray = a_attribute.IsArray();
      bool isShared = a_attribute.IsShared();
      bool isVertexArray = a_attribute.IsAttribArray();

      GLint enabledVertexAttribArray = -1; // -1 means no attrib array enabled

      switch(a_info.m_type)
      {
      case GL_FLOAT:
        {
          if (isArray == false)
          {
            const f32& f =
              isShared
              ? *a_attribute.GetValueAsShared<f32>()
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
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 1, GL_FLOAT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
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
          if (isArray == false)
          {
            const Vec2f32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Vec2f32>()
              : a_attribute.GetValueAs<Vec2f32>();
            glVertexAttrib2f(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 2, GL_FLOAT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttrib2fv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_FLOAT_VEC3:
        {
          if (isArray == false)
          {
            const Vec3f32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Vec3f32>()
              : a_attribute.GetValueAs<Vec3f32>();
            glVertexAttrib3f(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 3, GL_FLOAT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttrib3fv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_FLOAT_VEC4:
        {
          if (isArray == false)
          {
            const Vec4f32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Vec4f32>()
              : a_attribute.GetValueAs<Vec4f32>();
            glVertexAttrib4f(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 4, GL_FLOAT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef f32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttrib4fv(a_info.m_location, faraw);
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
              ? *a_attribute.GetValueAsShared<s32>()
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
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 1, GL_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
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
          if (isArray == false)
          {
            const Tuple2s32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Tuple2s32>()
              : a_attribute.GetValueAs<Tuple2s32>();
            glVertexAttribI2i(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 2, GL_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI2iv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_INT_VEC3:
        {
          if (isArray == false)
          {
            const Tuple3s32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Tuple3s32>()
              : a_attribute.GetValueAs<Tuple3s32>();
            glVertexAttribI3i(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 3, GL_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI3iv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_INT_VEC4:
        {
          if (isArray == false)
          {
            const Tuple4s32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Tuple4s32>()
              : a_attribute.GetValueAs<Tuple4s32>();
            glVertexAttribI4i(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 4, GL_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef s32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI4iv(a_info.m_location, faraw);
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
              ? *a_attribute.GetValueAsShared<u32>()
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
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 1, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
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
          if (isArray == false)
          {
            const Tuple2u32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Tuple2u32>()
              : a_attribute.GetValueAs<Tuple2u32>();
            glVertexAttribI2ui(a_info.m_location, v[0], v[1]);
          }
          else if (isVertexArray)
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 2, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI2uiv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC3:
        {
          if (isArray == false)
          {
            const Tuple3u32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Tuple3u32>()
              : a_attribute.GetValueAs<Tuple3u32>();
            glVertexAttribI3ui(a_info.m_location, v[0], v[1], v[2]);
          }
          else if (isVertexArray)
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 3, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI3uiv(a_info.m_location, faraw);
            }
          }
          break;
        }
      case GL_UNSIGNED_INT_VEC4:
        {
          if (isArray == false)
          {
            const Tuple4u32& v =
              isShared
              ? *a_attribute.GetValueAsShared<Tuple4u32>()
              : a_attribute.GetValueAs<Tuple4u32>();
            glVertexAttribI4ui(a_info.m_location, v[0], v[1], v[2], v[3]);
          }
          else if (isVertexArray)
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribPointer
                (a_info.m_location, 4, GL_UNSIGNED_INT, GL_FALSE, 0, faraw);
              glEnableVertexAttribArray(a_info.m_location);
              enabledVertexAttribArray = a_info.m_location;
            }
          }
          else
          {
            typedef u32                     data_type;
            typedef Array<data_type>        array_type;
            typedef SharedPtr<array_type>   shared_type;

            array_type const & fa =
              isShared
              ? *a_attribute.GetValueAsShared<array_type>()
              : a_attribute.GetValueAs<array_type>();

            if (fa.size() > 0)
            {
              data_type const * faraw = reinterpret_cast<data_type const*>(&(fa[0]));
              glVertexAttribI4uiv(a_info.m_location, faraw);
            }
          }
          break;
        }
#endif
      default:
        {
          TLOC_ASSERT(false, "Unsupported shader variable type!");
        }
      }

      return enabledVertexAttribArray;
    }
  }

  template <typename T_ShaderVariableContainer,
  typename T_ShaderVariableInfoContainer>
  ErrorAttribIndexPair
  DoPrepareVariables(T_ShaderVariableContainer& a_shaderVars,
                     const T_ShaderVariableInfoContainer& a_shaderVarsInfo)
  {
    typedef T_ShaderVariableContainer             svc;
    typedef T_ShaderVariableInfoContainer         svcInfo;
    typedef typename svc::iterator                svc_iterator;
    typedef typename svcInfo::const_iterator      svcInfo_const_iterator;
    typedef typename svc::value_type::first_type  shader_var_ptr_type;

    ShaderOperator::error_type retError = ErrorSuccess;
    GLint attribLocation = -1;

    svc_iterator itr, itrEnd;
    for (itr = a_shaderVars.begin(), itrEnd = a_shaderVars.end();
         itr != itrEnd; ++itr)
    {
      shader_var_ptr_type shaderVarPtr = itr->first;

      ShaderOperator::index_type index = 0;
      svcInfo_const_iterator itrInfo, itrInfoEnd;
      for (itrInfo = a_shaderVarsInfo.begin(),
           itrInfoEnd = a_shaderVarsInfo.end();
           itrInfo != itrInfoEnd; ++itrInfo)
      {
        if ( shaderVarPtr->GetName().compare(itrInfo->m_name.Get()) == 0)
        {
          if ( shaderVarPtr->GetType() == itrInfo->m_type &&
              itrInfo->m_location != -1)
          {
            itr->second = index;
            attribLocation =
              DoSet(a_shaderVarsInfo[itr->second], *shaderVarPtr);

            gl::Error err; TLOC_UNUSED(err);
            TLOC_ASSERT(err.Succeeded(),
                        "glUniform*/glAttribute* failed in DoSet()");
            break;
          }
          else
          {
            // TODO: Convert this assertion to a log
            TLOC_ASSERT(false, "Mismatched uniform/attribute type!");
            retError = ErrorFailure;
            break;
          }
        }
        ++index;
      }

      // We could not find the user specified uniform in the shader
      if (itrInfo == itrInfoEnd)
      {
        TLOC_ASSERT(false, "Uniform/Attribute type not found in shader!");
        retError = ErrorFailure;
      }
    }

    return core::MakePair(retError, attribLocation);
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

  void ShaderOperator::
    AddUniform(const uniform_ptr_type& a_uniform)
  {
    TLOC_ASSERT(a_uniform->GetName().size() > 0, "Uniform name is empty");
    m_uniforms.push_back(core::MakePair(a_uniform, index_type(-1)) );
    m_flags.Unmark(k_uniformsCached);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    AddAttribute(const attribute_ptr_type& a_attribute)
  {
    TLOC_ASSERT(a_attribute->GetName().size() > 0, "Attribute name is empty");
    m_attributes.push_back(core::MakePair(a_attribute, index_type(-1)) );
    m_flags.Unmark(k_attributesCached);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveUniform(const uniform_ptr_type& a_uniform)
  {
    uniform_iterator itr, itrEnd;
    for(itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
        itr != itrEnd; ++itr)
    {
      if (itr->first.get() == a_uniform.get())
      { break; }
    }

    if (itr != m_uniforms.end())
    { m_uniforms.erase(itr); }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveAttribute(const attribute_ptr_type& a_attribute)
  {
    attribute_iterator itr, itrEnd;
    for(itr = m_attributes.begin(), itrEnd = m_attributes.end();
        itr != itrEnd; ++itr)
    {
      if (itr->first == a_attribute)
      { break; }
    }

    if (itr != m_attributes.end())
    { m_attributes.erase(itr); }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveAllUniforms()
  {
    m_flags.Unmark(k_uniformsCached);
    m_uniforms.clear();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    RemoveAllAttributes()
  {
    m_flags.Unmark(k_attributesCached);
    m_attributes.clear();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void ShaderOperator::
    EnableAllUniforms(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_uniformsCached),
      "Uniforms not loaded - did you forget to call PrepareAllUniforms()?");

    const glsl_var_info_cont_type& uniCont = a_shaderProgram.GetUniformInfoRef();

    uniform_cont_type::iterator itr, itrEnd;
    for (itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
         itr != itrEnd; ++itr)
    {
      uniform_sptr uniformPtr = itr->first;

      if (itr->second >= 0)
      { DoSet(uniCont[itr->second], *uniformPtr); }
      else
      {
        // LOG: Uniform cannot be set. Did you forget to call PrepareAllUniforms?
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  void ShaderOperator::
    EnableAllAttributes(const ShaderProgram& a_shaderProgram)
  {
    TLOC_ASSERT(a_shaderProgram.IsLinked(),
                "Shader not linked - did you forget to call Link()?");
    TLOC_ASSERT(m_flags.IsMarked(k_attributesCached),
      "Attributes not loaded - did you forget to call PrepareAllAttributes()?");

    const glsl_var_info_cont_type&
      attrCont = a_shaderProgram.GetAttributeInfoRef();

    attribute_cont_type::iterator itr, itrEnd;
    for (itr = m_attributes.begin(), itrEnd = m_attributes.end();
         itr != itrEnd; ++itr)
    {
      attribute_sptr attribPtr = itr->first;

      // If we already know which info to pick
      if (itr->second >= 0)
      { DoSet(attrCont[itr->second], *attribPtr); }
      else
      {
        // LOG: Attribute cannot be set. Did you forget to call EnableAllAttributes?
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
      const glsl_var_info_cont_type&
        attrCont = a_shaderProgram.GetAttributeInfoRef();

      ErrorAttribIndexPair errAndIndex = DoPrepareVariables(m_attributes, attrCont);
      retError = errAndIndex.first;

      if (errAndIndex.second >= 0)
      { m_enabledVertexAttrib.push_back(errAndIndex.second); }
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

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearAttributesCache()
  { m_flags.Unmark(k_attributesCached); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearUniformsCache()
  { m_flags.Unmark(k_uniformsCached); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ShaderOperator::
    ClearCache()
  {
    ClearAttributesCache();
    ClearUniformsCache();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ShaderOperator::
    IsAttributesCached()
  { return m_flags[k_attributesCached]; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ShaderOperator::
    IsUniformsCached()
  { return m_flags[k_uniformsCached]; }

  //------------------------------------------------------------------------
  // explicit instantiation

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(ShaderOperator);
  template class Array<uniform_sptr>;
  template class Array<attribute_sptr>;


};};};
