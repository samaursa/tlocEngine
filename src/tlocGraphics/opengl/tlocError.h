#ifndef TLOC_GL_ERROR_H
#define TLOC_GL_ERROR_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace graphics { namespace gl {

  class Error
  {
  public:
    typedef s32                 value_type; // GLenum

  public:
    bool Succeeded();
    bool Failed();

    value_type GetError();
    template <typename T_String>
    void       GetLastErrorAsString(T_String& a_out);

  private:
    value_type          m_lastError;
    static const char*  s_lastErrorDesc;
  };

};};};

#endif