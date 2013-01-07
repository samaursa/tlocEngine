#ifndef _TLOC_GRAPHICS_GL_SHADER_VARIABLE_H_
#define _TLOC_GRAPHICS_GL_SHADER_VARIABLE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/string/tlocString.h>

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocCore/containers/tlocContainers.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_shader_variable_ti
  {
    struct CopyArray {};
    struct SwapArray {};
  };

  template <typename T_Derived>
  class ShaderVariable_TI
  {
  public:
    typedef core::types::Any                 value_type;
    typedef core::string::String             string_type;
    typedef u32                              gl_type;
    typedef T_Derived                        derived_type;
    typedef ShaderVariable_TI<derived_type>  this_type;

    typedef p_shader_variable_ti::CopyArray  copy_array_policy;
    typedef p_shader_variable_ti::SwapArray  swap_array_policy;

  public:
    ShaderVariable_TI();
    ~ShaderVariable_TI();

    template <typename T>
    void GetValueAs(T& a_out) const
    {
      static_cast<derived_type*>(this)->DoCheckTypeCompatibility<T>();
      a_out = m_value.Cast<T>();
    }

    template <typename T>
    const T&  GetValueAs() const
    {
      static_cast<derived_type const*>(this)->DoCheckTypeCompatibility<T>();
      return m_value.Cast<T>();
    }

    template <typename T>
    derived_type& SetValueAs(const T& a_value)
    {
      static_cast<derived_type*>(this)->DoCheckNonArrayTypes<T>();
      return DoSetValueAs(a_value);
    }

    template <typename T, typename T_Technique>
    derived_type&
      SetValueAs(core::containers::Array<T>& a_array, T_Technique)
    {
      static_cast<derived_type*>(this)->DoCheckArrayTypes<T>();
      return DoSetValueAs(a_array, T_Technique());
    }

    derived_type& SetName(const string_type& a_value);

    TLOC_DECL_AND_DEF_GETTER(gl_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(bool, IsArray, m_isArray);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);

  private:
    template <typename T>
    derived_type& DoSetValueAs(const T& a_value);

    template <typename T>
    derived_type& DoSetValueAs(const core::containers::Array<T>& a_array,
                               copy_array_policy);

    template <typename T>
    derived_type& DoSetValueAs(core::containers::Array<T>& a_array,
                               swap_array_policy);

  private:
    gl_type       m_type;
    bool          m_isArray;
    value_type    m_value;
    string_type   m_name;
  };

};};};

#endif