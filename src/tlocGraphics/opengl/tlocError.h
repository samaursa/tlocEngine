#ifndef TLOC_GL_ERROR_H
#define TLOC_GL_ERROR_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/utilities/tlocUtils.h>

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

    static void  IgnoreAllErrors(bool a_ignoreAllErrors = true);

    static TLOC_DECL_AND_DEF_GETTER_NON_CONST(bool, IsIgnoreAllErrors, 
                                              s_ignoreAllErrors);
  private:
    value_type          m_lastError;
    static value_type   s_lastError;
    static const char*  s_lastErrorDesc;
    static bool         s_ignoreAllErrors;
  };

};};};

#endif