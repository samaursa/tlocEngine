#ifndef TLOC_GRAPHICS_RENDERER_H
#define TLOC_GRAPHICS_RENDERER_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/platform/tlocPlatform.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics {

  template <typename T_Derived>
  class RendererBase : core::utils::ObjectCounter<RendererBase<T_Derived> >
  {
  public:
    typedef T_Derived                               derived_type;
    typedef RendererBase<derived_type>              this_type;
    typedef core::utils::ObjectCounter<this_type>   base_type;
    typedef core::error::Error                      error_type;
    typedef core::utils::Checkpoints                check_type;

  public:
    RendererBase();
    error_type  Initialize();
    static bool IsInitialized();

    using base_type::GetCurrentObjectCount;

  protected:
    check_type  m_flags;

  };

  //------------------------------------------------------------------------
  // Generic Implementation

  template <typename T_Platform>
  class Renderer_T;

  template <typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Renderer_T : public RendererBase<Renderer_T<T_Platform> >
  {
  public:
    template <class T> friend class RendererBase;

    typedef T_Platform                  platform_type;
    typedef Renderer_T<platform_type>   this_type;
    typedef RendererBase<this_type>     base_type;

    typedef typename base_type::error_type  error_type;

  public:
    using base_type::Initialize;
    using base_type::IsInitialized;

  protected:
    using base_type::m_flags;

  private:
    error_type DoInitialize();

  };

  //------------------------------------------------------------------------
  // Windows Implementation

  template <>
  class Renderer_T<core::Platform_win> :
    public RendererBase<Renderer_T<core::Platform_win> >
  {
  public:
    template <class T> friend class RendererBase;

    typedef core::Platform_win          platform_type;
    typedef Renderer_T<platform_type>   this_type;
    typedef RendererBase<this_type>     base_type;

    typedef typename base_type::error_type  error_type;

  public:
    using base_type::Initialize;
    using base_type::IsInitialized;

  protected:
    using base_type::m_flags;

  private:
    error_type DoInitialize();

  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Renderer_T<>    Renderer;

};};

#endif