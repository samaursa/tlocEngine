#ifndef TLOC_CONTEXT_H
#define TLOC_CONTEXT_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocNonCopyable.h"

namespace tloc { namespace graphics {

  template <class T_ParentWindow> class WindowImpl;

};};

namespace tloc { namespace graphics { namespace priv {

  ///-------------------------------------------------------------------------
  /// This class is taken from SFML. We don't know about threading issues with
  /// contexts yet so we will trust SFML's implementation.
  ///
  /// @sa tloc::core::NonCopyable
  ///-------------------------------------------------------------------------
  class Context : public core::NonCopyable
  {
  public:

    ///-------------------------------------------------------------------------
    /// Default constructor.
    ///-------------------------------------------------------------------------
    Context();

    ///-------------------------------------------------------------------------
    /// Destructor.
    ///-------------------------------------------------------------------------
    ~Context();

    ///-------------------------------------------------------------------------
    /// Activate/de-activate context
    ///
    /// @param  a_active true to activate context
    ///-------------------------------------------------------------------------
    void SetActive(bool a_active);

    ///-------------------------------------------------------------------------
    /// Check if a context is bound to the current thread
    ///
    /// @return true if a context is active, false if not.
    ///-------------------------------------------------------------------------
    static bool IsContextActive();

    ///-------------------------------------------------------------------------
    /// Gets the global context
    ///
    /// @return The global context
    ///-------------------------------------------------------------------------
    static Context& GetGlobal();
  };

};};};

#endif