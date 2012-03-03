#ifndef TLOC_WINDOW_H
#define TLOC_WINDOW_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocNonCopyable.h"

namespace tloc { namespace graphics {

  ///-------------------------------------------------------------------------
  /// A window to render to.
  ///
  /// Notes: The initial implementation was influenced by SFML
  ///
  /// @sa tloc::core::NonCopyable
  ///-------------------------------------------------------------------------
  class Window : public core::NonCopyable
  {
  public:
    struct Parameters
    {
      u32 m_width;
      u32 m_height;
      u32 m_bitsPerPixel;
    };

  public:
    Window();

    void Create();



  protected:
  };

};};

#endif