#ifndef TLOC_WINDOW_IMPL_H
#define TLOC_WINDOW_IMPL_H

namespace tloc { namespace graphics { namespace priv {

  ///-------------------------------------------------------------------------
  /// Window implementation that must be specialized for each platform
  ///-------------------------------------------------------------------------
  template <typename T_Platform> class WindowImpl;

};};};

#endif