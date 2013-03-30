#ifndef TLOC_MOUSE_IMPL_WIN_H
#define TLOC_MOUSE_IMPL_WIN_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocMouse.h>
#include <tlocInput/hid/tlocMouseImpl.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <WinSDK/dinput.h>

namespace tloc { namespace input {

  typedef ParamList<HWND, IDirectInput8*, parameter_options::Type>
    windows_mouse_param_type;

};};

namespace tloc { namespace input { namespace hid { namespace priv {

  template <typename T_ParentMouse>
  class MouseImpl
    : public MouseImplBase<T_ParentMouse, windows_mouse_param_type>
  {
  public:
    typedef windows_mouse_param_type            mouse_param_type;
    typedef T_ParentMouse                       parent_type;
    typedef MouseImpl<parent_type>              this_type;
    typedef MouseImplBase
      <parent_type, mouse_param_type>           base_type;

    typedef typename parent_type::platform_type    platform_type;
    typedef typename parent_type::policy_type      policy_type;
    typedef typename base_type::button_code_type   button_code_type;

    MouseImpl(parent_type* a_parent, const mouse_param_type& a_params);
    ~MouseImpl();

    ///-------------------------------------------------------------------------
    /// Query if 'a_button' is down.
    ///
    /// @param  a_button The button.
    ///
    /// @return true if button is down, false if not.
    ///-------------------------------------------------------------------------
    bool        IsButtonDown(button_code_type a_button) const;
    MouseEvent  GetState() const;

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update();
    void Reset();

  private:

    void        DoInitialize();
    // Buffered input requires extra initialization
    bool        DoInitializeExtra(InputPolicy::Buffered);
    // Immediate mode does not require anything special
    bool        DoInitializeExtra(InputPolicy::Immediate) { return true; }

    void        DoUpdate(InputPolicy::Buffered);
    void        DoUpdate(InputPolicy::Immediate);

    void        DoReset(InputPolicy::Buffered);
    void        DoReset(InputPolicy::Immediate);

  private:

    IDirectInput8*        m_directInput;
    IDirectInputDevice8*  m_mouse;
    DIMOUSESTATE2         m_mouseBuffer;
    HWND                  m_windowPtr;

    MouseEvent              m_currentState;
    static const size_type  s_bufferSize = sizeof(DIMOUSESTATE2);
  };

};};};};

#endif