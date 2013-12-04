#ifndef _TLOC_GRAPHICS_BASE_H_
#define _TLOC_GRAPHICS_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that graphics uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace graphics
  {
    namespace component_system {};
    namespace error            {};
    namespace media            {};
    namespace gl               {};
    namespace renderer         {};
    namespace types            {};
    namespace win              {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace gfx          = graphics;
  namespace gfx_cs       = graphics::component_system;
  namespace gfx_err      = graphics::error;
  namespace gfx_med      = graphics::media;
  namespace gfx_gl       = graphics::gl;
  namespace gfx_rend     = graphics::renderer;
  namespace gfx_t        = graphics::types;
  namespace gfx_win      = graphics::win;
};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// gfx's default logger
namespace tloc { namespace graphics {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_GFX_INFO()    TLOC_LOG_INFO(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG()   TLOC_LOG_DEBUG(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN()    TLOC_LOG_WARN(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR()     TLOC_LOG_ERR(&tloc::graphics::GetLogger())

#endif