#ifndef _TLOC_GRAPHICS_INCLUDE_ALL_WINDOW_H_
#define _TLOC_GRAPHICS_INCLUDE_ALL_WINDOW_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocGraphics/window/tlocContext.h>
#include <tlocGraphics/window/tlocGraphicsModes.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/window/tlocWindowImpl.h>
#include <tlocGraphics/window/tlocWindowSettings.h>

# if defined (TLOC_OS_WIN)
#   include <tlocGraphics/window/tlocWindowImplWin.h>
# elif defined (TLOC_OS_IPHONE)
#   include <tlocGraphics/window/tlocWindowImplIphone.h>
# else
#   error "WIP"
# endif

#endif