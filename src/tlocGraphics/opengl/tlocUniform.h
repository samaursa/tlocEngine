#ifndef _TLOC_GRAPHICS_GL_UNIFORM_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/matrix/tlocMatrix2.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  class ShaderProgram;

  class Uniform
  {
  public:
    typedef core::types::Any        value_type;
    typedef core::String            string_type;
    typedef u32                     gl_type;
  public:
    Uniform();
    ~Uniform();

    template <typename T>
    const T&  GetValueAs()
    {
      DoCheckTypeCompatibility();
      return m_value.Cast<T>();
    }

    template <typename T>
    Uniform& SetValueAs(const T& a_value)
    {
      DoCheckTypeCompatibility<T>();
      return DoSetValueAs(a_value);
    }

    Uniform& SetName(const string_type& a_value);

    TLOC_DECL_AND_DEF_GETTER(gl_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);

  private:
    template <typename T>
    void DoCheckTypeCompatibility()
    {
      type_traits::AssertTypeIsSupported
        <T,
         f32,
         math::Vec2f32,
         math::Vec3f32,
         math::Vec4f32,
         s32,
         core::Tuple2s32,
         core::Tuple3s32,
         core::Tuple4s32,
         math::Mat2f32,
         math::Mat3f32,
         math::Mat4f32>();
    }

    template <typename T>
    Uniform& DoSetValueAs(const T& a_value);

  private:
    gl_type       m_type;
    value_type    m_value;
    string_type   m_name;
  };

};};};

#endif