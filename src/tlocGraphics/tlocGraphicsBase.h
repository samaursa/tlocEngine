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

namespace tl_gfx          = tloc::graphics;
namespace tl_gfx_cs       = tloc::graphics::component_system;
namespace tl_gfx_err      = tloc::graphics::error;
namespace tl_gfx_med      = tloc::graphics::media;
namespace tl_gfx_gl       = tloc::graphics::gl;
namespace tl_gfx_rend     = tloc::graphics::renderer;
namespace tl_gfx_t        = tloc::graphics::types;
namespace tl_gfx_win      = tloc::graphics::win;

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// gfx's default logger
namespace tloc { namespace graphics {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_GFX_INFO()    TLOC_LOG_INFO(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_SUCCESS() TLOC_LOG_SUCCESS(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG()   TLOC_LOG_DEBUG(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN()    TLOC_LOG_WARN(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR()     TLOC_LOG_ERR(&tloc::graphics::GetLogger())

#define TLOC_LOG_GFX_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_SUCCESS_IF(_expr_) TLOC_LOG_SUCCESS_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::graphics::GetLogger())

#define TLOC_LOG_GFX_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_SUCCESS_FILENAME_ONLY() TLOC_LOG_SUCCESS_FILENAME_ONLY(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::graphics::GetLogger())

#define TLOC_LOG_GFX_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_SUCCESS_FILENAME_ONLY_IF(_expr_) TLOC_LOG_SUCCESS_FILENAME_ONLY_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::graphics::GetLogger())

#define TLOC_LOG_GFX_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_SUCCESS_NO_FILENAME() TLOC_LOG_SUCCESS_NO_FILENAME(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::graphics::GetLogger())

#define TLOC_LOG_GFX_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_SUCCESS_NO_FILENAME_IF(_expr_) TLOC_LOG_SUCCESS_NO_FILENAME_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::graphics::GetLogger())
#define TLOC_LOG_GFX_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::graphics::GetLogger())

#endif