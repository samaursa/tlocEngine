#ifndef _TLOC_GRAPHICS_GL_UNIFORM_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/string/tlocString.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  class ShaderProgram;

  template <typename T>
  class Uniform
  {
  public:
    typedef T                       value_type;
    typedef String                  string_type;
  public:
    Uniform(const char* a_name, const T& a_val)
      : m_value(a_val), m_name(a_name)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetValue, m_value);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);

  private:
    value_type    m_value;
    string_type   m_name;
  };

};};};

#endif