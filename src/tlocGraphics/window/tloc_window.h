#ifndef _TLOC_GRAPHICS_INCLUDE_ALL_WINDOW_H_
#define _TLOC_GRAPHICS_INCLUDE_ALL_WINDOW_H_

#include <tlocGraphics/window/tlocContext.h>
#include <tlocGraphics/window/tlocGraphicsModes.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/window/tlocWindowImpl.h>
#include <tlocGraphics/window/tlocWindowImplWin.h>
#include <tlocGraphics/window/tlocWindowSettings.h>

namespace tloc {

  // TODO: Remove this temporary when we have the 'window' namespace
  namespace graphics { namespace win { }; };

  namespace gfx_win = graphics::win;

};

#endif