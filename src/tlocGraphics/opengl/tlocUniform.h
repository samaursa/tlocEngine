#ifndef _TLOC_GRAPHICS_GL_UNIFORM_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl>
#include <tlocCore/string/tlocString.h>

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
      //TLOC_ASSERT( (m_value.IsSameType(value_type(), "Type mismatch!");
      return m_value.Cast<T>();
    }

    template <typename T>
    Uniform& SetValueAs(const T& a_value);
    Uniform& SetName(const string_type& a_value);

    TLOC_DECL_AND_DEF_GETTER(gl_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);

  private:
    gl_type       m_type;
    value_type    m_value;
    string_type   m_name;
  };

};};};

#endif