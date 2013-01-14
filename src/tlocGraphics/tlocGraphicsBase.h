#ifndef _TLOC_GRAPHICS_BASE_H_
#define _TLOC_GRAPHICS_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that core uses should go here

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
    namespace view_proj        {};
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
  namespace gfx_vp       = graphics::view_proj;
  namespace gfx_win      = graphics::win;

};


#endif