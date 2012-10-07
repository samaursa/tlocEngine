#ifndef TLOC_KEYBOARD_IMPL_IPHONE_H
#define TLOC_KEYBOARD_IMPL_IPHONE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/HIDs/tlocKeyboard.h>
#include <tlocInput/HIDs/tlocKeyboardImpl.h>

#import <tlocGraphics/window/tlocOpenGLViewIphone.h>

namespace tloc { namespace input {

  // TODO: Fix this so it actually has the correct params associated (such as the UIWindow)
  typedef ParamList<OpenGLView*> iphone_keyboard_param_type;

};};

namespace tloc { namespace input { namespace priv {

  template <typename T_ParentKeyboard>
  class KeyboardImpl
    : public KeyboardImplBase<T_ParentKeyboard, iphone_keyboard_param_type>
  {
  public:
    typedef iphone_keyboard_param_type            keyboard_param_type;
    typedef T_ParentKeyboard                       parent_type;
    typedef KeyboardImpl<parent_type>              this_type;
    typedef KeyboardImplBase
      <parent_type, keyboard_param_type>           base_type;

    typedef typename parent_type::platform_type       platform_type;
    typedef typename parent_type::policy_type         policy_type;
    typedef typename base_type::keycode_type          keycode_type;
    typedef typename base_type::size_type             size_type;

    KeyboardImpl(parent_type* a_parent,
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

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update();

  private:

    void        DoInitialize();
    // Buffered input requires extra initialization
    bool        DoInitializeExtra(InputPolicy::Buffered);
    // Immediate mode does not require anything special
    bool        DoInitializeExtra(InputPolicy::Immediate) { return true; }

    void        DoUpdate(InputPolicy::Buffered);
    void        DoUpdate(InputPolicy::Immediate);

  private:

    bool                   m_buffer[KeyboardEvent::Count];

    static const size_type s_bufferSize = 256;
    uchar8                  m_rawBuffer[s_bufferSize];
  };

};};};

#endif