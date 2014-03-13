#ifndef TLOC_KEYBOARD_IMPL_WIN_H
#define TLOC_KEYBOARD_IMPL_WIN_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocKeyboard.h>
#include <tlocInput/hid/tlocKeyboardImpl.h>

#include <tlocCore/platform/tlocPlatformSpecificIncludes.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <WinSDK/dinput.h>

// ///////////////////////////////////////////////////////////////////////
// ParamList

namespace tloc { namespace input {

  typedef ParamList<HWND, IDirectInput8*, param_options::value_type>
    windows_keyboard_param_type;

};};

//////////////////////////////////////////////////////////////////////////
// KeyboardImpl

namespace tloc { namespace input { namespace hid { namespace priv {

  template <typename T_ParentKeyboard>
  class KeyboardImpl
    : public KeyboardImplBase<T_ParentKeyboard, windows_keyboard_param_type>
  {
  public:
    typedef windows_keyboard_param_type            keyboard_param_type;
    typedef T_ParentKeyboard                       parent_type;
    typedef KeyboardImpl<parent_type>              this_type;
    typedef KeyboardImplBase
      <parent_type, keyboard_param_type>           base_type;

    typedef typename parent_type::platform_type       platform_type;
    typedef typename parent_type::policy_type         policy_type;
    typedef typename base_type::keycode_type          keycode_type;

    KeyboardImpl(parent_type& a_parent,
                 const keyboard_param_type& a_params);
    ~KeyboardImpl();

    ///-------------------------------------------------------------------------
    /// Query if 'a_key' is key down.
    ///
    /// @param  a_key The key.
    ///
    /// @return true if key is down, false if not.
    ///-------------------------------------------------------------------------
    bool IsKeyDown(keycode_type a_key) const;
    bool IsModifierDown(modifier_type a_key) const;

    ///-------------------------------------------------------------------------
    /// Process any keys that were pressed between this and the last update
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
    IDirectInputDevice8*  m_keyboard;
    HWND                  m_windowPtr;

    bool                  m_buffer[KeyboardEvent::Count];

    static const DWORD    s_bufferSize = 256;
    uchar8                m_rawBuffer[s_bufferSize];
  };

};};};};

#endif