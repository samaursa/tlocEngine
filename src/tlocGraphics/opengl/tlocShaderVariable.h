#ifndef _TLOC_GRAPHICS_GL_SHADER_VARIABLE_H_
#define _TLOC_GRAPHICS_GL_SHADER_VARIABLE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  template <typename T_Derived>
  class ShaderVariable_TI
  {
  public:
    typedef core::types::Any              value_type;
    typedef core::String                  string_type;
    typedef u32                           gl_type;
    typedef T_Derived                     derived_type;
    typedef ShaderVariable_TI<derived_type>  this_type;

  public:
    ShaderVariable_TI();
    ~ShaderVariable_TI();

    template <typename T>
    const T&  GetValueAs()
    {
      static_cast<derived_type*>(this)->DoCheckTypeCompatibility<T>();
      return m_value.Cast<T>();
    }

    template <typename T>
    derived_type& SetValueAs(const T& a_value)
    {
      static_cast<derived_type*>(this)->DoCheckTypeCompatibility<T>();
      return DoSetValueAs(a_value);
    }

    derived_type& SetName(const string_type& a_value);

    TLOC_DECL_AND_DEF_GETTER(gl_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);

  private:
    template <typename T>
    derived_type& DoSetValueAs(const T& a_value);

  private:
    gl_type       m_type;
    value_type    m_value;
    string_type   m_name;
  };

};};};

#endif