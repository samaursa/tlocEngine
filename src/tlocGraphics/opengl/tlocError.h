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
    Error();

    bool Succeeded();
    bool Failed();

    value_type GetError() const;
    template <typename T_String>
    void        GetLastErrorAsString(T_String& a_out) const;
    const char* GetLastErrorAsString() const;

    static void  IgnoreAllErrors(bool a_ignoreAllErrors = true);

    static TLOC_DECL_AND_DEF_GETTER_NON_CONST(bool, IsIgnoreAllErrors, 
                                              s_ignoreAllErrors);
  private:
    mutable value_type  m_lastError;
    static value_type   s_lastError;
    static const char*  s_lastErrorDesc;
    static bool         s_ignoreAllErrors;
  };

};};};

#include <tlocCore/logging/tlocLog.h>

namespace tloc { namespace core {

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig>
    const Log_T<T_Logger, T_BuildConfig>&
      operator << (const Log_T<T_Logger, T_BuildConfig>& a_log,
                   const gfx_gl::Error& a_err)
    {
      a_log << "OpenGL Error: " << a_err.GetLastErrorAsString() << "[" 
        << a_err.GetError() << "]";

      return a_log;
    }

  };

};};

#endif