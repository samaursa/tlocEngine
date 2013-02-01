#include "tlocTestCommon.h"

#include <tlocCore/types/tlocTemplateParams.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocPointerUtils.h>
#include <tlocCore/time/tlocTime.h>

#include <tlocInput/tlocInputManager.h>
#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocKeyboard.h>
#include <tlocInput/hid/tlocMouse.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <dinput.h>

namespace TestingInput
{
  using namespace tloc;
  using namespace input;
  using namespace input_hid;

  template <typename T_Keyboard>
  struct sampleInputKeyboard
  {
    sampleInputKeyboard(T_Keyboard* a_caller)
      : m_event(KeyboardEvent::none),
        m_caller(a_caller),
        m_keypresses(0),
        m_keyreleases(0) {}

    bool OnKeyPress(const tl_size a_caller, const KeyboardEvent& a_event)
    {
      CHECK(core::utils::IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_keypresses++;

      return true; // Veto all later keypresses - does nothing here, just an e.g.
    }

    bool OnKeyRelease(const tl_size a_caller, const KeyboardEvent& a_event)
    {
      CHECK(core::utils::IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_keyreleases++;

      return true; // Veto all later keypresses - does nothing here, just an e.g.
    }

    KeyboardEvent m_event;
    T_Keyboard*   m_caller;
    u32           m_keypresses;
    u32           m_keyreleases;
  }; TLOC_DEF_TYPE(sampleInputKeyboard<KeyboardB>);

  template <typename T_Mouse>
  struct sampleInputMouse
  {
    sampleInputMouse(T_Mouse* a_caller)
      : m_event(MouseEvent::none)
      , m_caller(a_caller)
      , m_buttonPresses(0)
      , m_buttonReleases(0)
      , m_movementEvents(0) {}

    bool OnButtonPress(const tl_size a_caller, const MouseEvent& a_event)
    {
      CHECK(core::utils::IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_buttonPresses++;

      return false;
    }

    bool OnButtonRelease(const tl_size a_caller, const MouseEvent& a_event)
    {
      CHECK(core::utils::IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_buttonReleases++;

      return false;
    }

    bool OnMouseMove(const tl_size a_caller, const MouseEvent& a_event)
    {
      CHECK(core::utils::IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_movementEvents++;
      return false;
    }

    MouseEvent  m_event;
    T_Mouse*    m_caller;
    u32         m_buttonPresses;
    u32         m_buttonReleases;
    u32         m_movementEvents;
  }; TLOC_DEF_TYPE(sampleInputMouse<hid::MouseB>);


  LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  HWND CreateWin32Window()
  {
    WNDCLASSW wcex;

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = GetModuleHandle(NULL);
    wcex.hIcon          = NULL;
    wcex.hCursor        = 0;
    wcex.hbrBackground  = 0;
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = L"tloc_testing_input";

    if (!RegisterClassW(&wcex)) { return NULL; }

    HWND wnd = CreateWindowW(wcex.lpszClassName, L"Testing Input",
      WS_POPUP | WS_DISABLED, 0, 0, 10, 10, NULL, NULL, GetModuleHandle(NULL),
      NULL);

    if (!wnd) { return NULL; }

    ShowWindow(wnd, SW_SHOW);
    UpdateWindow(wnd);
    return wnd;
  }

  void UpdateWin32Window(HWND a_wnd)
  {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    TLOC_UNUSED(a_wnd);
    //SetForegroundWindow(a_wnd);
  }

  //------------------------------------------------------------------------
  // Keyboard specific

  static void SendButtonPress(WORD input_code_set)
  {
    INPUT inp[1];
    memset(inp, 0, sizeof(INPUT));
    inp[0].type = INPUT_KEYBOARD;
    inp[0].ki.wScan = input_code_set;
    SendInput(1, inp, sizeof(INPUT));
  }

  static void SendButtonRelease(WORD input_code_set)
  {
    INPUT inp[1];
    memset(inp, 0, sizeof(INPUT));
    inp[0].type = INPUT_KEYBOARD;
    inp[0].ki.dwFlags |= KEYEVENTF_KEYUP;
    inp[0].ki.wScan = input_code_set;
    SendInput(1, inp, sizeof(INPUT));
  }

  template <typename T_InputManagerType, typename T_KeyboardType>
  void TestKeyboardType(T_InputManagerType* a_im, T_KeyboardType* kb,
    HWND a_wnd, WORD a_key, hid::KeyboardEvent::key_code_type a_ourKey,
    input::InputPolicy::Buffered)
  {
    core::time::Timer countDown;

    sampleInputKeyboard<KeyboardB> callback(kb);
    kb->Register(&callback);

    while ( countDown.ElapsedMilliSeconds() < 1000 && callback.m_keypresses < 1 )
    {
      UpdateWin32Window(a_wnd);
      SendButtonPress(a_key);
      a_im->Update();
    }

    CHECK(callback.m_keypresses > 0);
    CHECK(callback.m_event.m_keyCode == a_ourKey);

    SCOPED_INFO("The keyboard key: " << a_key << " vs our key: " << a_ourKey);
    CHECK(kb->IsKeyDown(a_ourKey));

    countDown.Reset();
    while ( countDown.ElapsedMilliSeconds() < 1000 && callback.m_keyreleases < 1)
    {
      UpdateWin32Window(a_wnd);
      SendButtonRelease(a_key);
      a_im->Update();
    }

    CHECK(callback.m_keyreleases > 0);
    CHECK_FALSE(kb->IsKeyDown(a_ourKey));

    kb->UnRegister(&callback);
  }

  template <typename T_InputManagerType, typename T_KeyboardType>
  void TestKeyboardType(T_InputManagerType* a_im, T_KeyboardType* kb, HWND a_wnd, WORD a_key,
    hid::KeyboardEvent::key_code_type a_ourKey, input::InputPolicy::Immediate)
  {
    core::time::Timer countDown;

    // This is in the while loop just so that can we can 'capture' the keystroke
    while(countDown.ElapsedMilliSeconds() < 1000)
    {
      UpdateWin32Window(a_wnd);
      SendButtonPress(a_key);
      a_im->Update();

      if (kb->IsKeyDown(a_ourKey))
      {
        break;
      }
    }
    CHECK(kb->IsKeyDown(a_ourKey));
  }

  template <typename T_InputManagerType>
  void TestKeyboardButton(T_InputManagerType* a_im, HWND a_wnd, WORD a_key,
                          hid::KeyboardEvent::key_code_type a_ourKey)
  {
    typedef typename T_InputManagerType::policy_type  policy_type;

    Keyboard<policy_type>* kb = a_im->GetHID<Keyboard<policy_type> >();

    CHECK(kb != NULL);

    if (kb)
    {
      TestKeyboardType(a_im, kb, a_wnd, a_key, a_ourKey, policy_type());
    }
  }

  //------------------------------------------------------------------------
  // Mouse specific

  static void SendMousePress(WORD input_code_set, WORD mouse_data,
                             LONG coordX = 0, LONG coordY = 0)
  {
    INPUT inp = {0};
    inp.type = INPUT_MOUSE;
    inp.mi.dwFlags = input_code_set;
    inp.mi.mouseData = mouse_data;
    inp.mi.dx = coordX;
    inp.mi.dy = coordY;
    SendInput(1, &inp, sizeof(INPUT));
  }

  template <typename T_InputManagerType, typename T_MouseType>
  void TestMouseType (T_InputManagerType* a_im, T_MouseType* mouse, HWND a_wnd,
    WORD a_buttonDown, WORD a_buttonUp, WORD a_extraData,
    hid::MouseEvent::button_code_type a_ourButton, input::InputPolicy::Buffered)
  {
    core::time::Timer_T<> countDown;

    CHECK(mouse != NULL);

    if (mouse)
    {
      sampleInputMouse<MouseB> callback(mouse);
      mouse->Register(&callback);

      while (countDown.ElapsedMilliSeconds() < 1000 &&
             callback.m_buttonPresses < 1)
      {
        UpdateWin32Window(a_wnd);
        SendMousePress(a_buttonDown, a_extraData);
        a_im->Update();
      }

      SCOPED_INFO("The mouse button: " << a_buttonDown << " vs our button: "
        << a_ourButton);
      CHECK(mouse->IsButtonDown(a_ourButton));
      CHECK(a_ourButton == callback.m_event.m_buttonCode);

      countDown.Reset();
      while (countDown.ElapsedMilliSeconds() < 1000 &&
             callback.m_buttonReleases < 1)
      {
        UpdateWin32Window(a_wnd);
        SendMousePress(a_buttonUp, a_extraData);
        a_im->Update();
      }

      CHECK_FALSE(mouse->IsButtonDown(a_ourButton));

      mouse->UnRegister(&callback);

      CHECK(callback.m_buttonPresses > 0);
      CHECK(callback.m_buttonReleases > 0);
    }
  }

  template <typename T_InputManagerType, typename T_MouseType>
  void TestMouseType (T_InputManagerType* a_im, T_MouseType* mouse, HWND a_wnd,
    WORD a_buttonDown, WORD a_buttonUp, WORD a_extraData,
    hid::MouseEvent::button_code_type a_ourButton, input::InputPolicy::Immediate)
  {
    core::time::Timer_T<> countDown;

    CHECK(mouse != NULL);

    if (mouse)
    {
      while ( countDown.ElapsedMilliSeconds() < 1000)
      {
        UpdateWin32Window(a_wnd);
        SendMousePress(a_buttonDown, a_extraData);
        UpdateWin32Window(a_wnd);
        SendMousePress(a_buttonUp, a_extraData);
        a_im->Update();

        if(mouse->IsButtonDown(a_ourButton))
        { break; }
      }

      SCOPED_INFO("The mouse button: " << a_buttonDown << " vs our button: "
        << a_ourButton);
      CHECK(mouse->IsButtonDown(a_ourButton));
    }
  }

  template <typename T_InputManagerType>
  void TestMouseButton(T_InputManagerType* a_im, HWND a_wnd, WORD a_buttonDown,
                       WORD a_buttonUp, WORD a_extraData,
                       hid::MouseEvent::button_code_type a_ourButton)
  {
    typedef typename T_InputManagerType::policy_type  policy_type;

    Mouse<policy_type>* mouse = a_im->GetHID<Mouse<policy_type> >();

    CHECK(mouse != NULL);

    if (mouse)
    {
      TestMouseType(a_im, mouse, a_wnd, a_buttonDown, a_buttonUp, a_extraData,
                    a_ourButton, policy_type());
    }
  }

  template <typename T_InputManagerType, typename T_MouseType>
  MouseEvent TestMouseState(T_InputManagerType* a_im, T_MouseType* a_mouse,
    HWND a_wnd, WORD a_axis, tl_int a_x, tl_int a_y, WORD a_data,
    input::InputPolicy::Buffered)
  {
    core::time::Timer countDown;

    sampleInputMouse<MouseB> callback(a_mouse);
    a_mouse->Register(&callback);

    SendMousePress(a_axis, a_data,
      static_cast<LONG>(a_x), static_cast<LONG>(a_y));

    while (countDown.ElapsedMilliSeconds() < 1000 &&
           callback.m_movementEvents == 0)
    {
      UpdateWin32Window(a_wnd);
      a_im->Update();
    }

    a_mouse->UnRegister(&callback);
    CHECK(callback.m_movementEvents > 0);

    return callback.m_event;
  }

  template <typename T_InputManagerType, typename T_MouseType>
  MouseEvent TestMouseState(T_InputManagerType* a_im, T_MouseType* a_mouse,
    HWND a_wnd, WORD a_axis, tl_int a_x, tl_int a_y, WORD a_data,
    input::InputPolicy::Immediate)
  {
    core::time::Timer countDown;

    SendMousePress(a_axis, a_data,
      static_cast<LONG>(a_x), static_cast<LONG>(a_y));

    UpdateWin32Window(a_wnd);
    a_im->Update();

    return a_mouse->GetState();
  }

  template <typename T_InputManagerType>
  MouseEvent TestMouseMove(T_InputManagerType* a_im, HWND a_wnd, WORD a_axis,
                           tl_int a_x, tl_int a_y, WORD a_data)
  {
    typedef typename T_InputManagerType::policy_type  policy_type;

    Mouse<policy_type>* mouse = a_im->GetHID<Mouse<policy_type> >();

    CHECK(mouse != NULL);

    if (mouse)
    {
      return TestMouseState(a_im, mouse, a_wnd, a_axis, a_x, a_y, a_data,
                            policy_type());
    }

    return MouseEvent(MouseEvent::none);
  }

  //------------------------------------------------------------------------
  // Tests

  struct InputDeviceInfo
  {
    bool                  m_available;
    GUID                  m_productGuid;
    GUID                  m_deviceGuid;
    core::string::String  m_deviceName;
    void*                 m_devicePtr;
  };

  template <typename T_InputManagerType>
  void TestKeyboard(T_InputManagerType& inputMgr, HWND wnd)
  {
    typedef input_hid::KeyboardEvent  ke;

    TestKeyboardButton(&inputMgr, wnd, DIK_ESCAPE, ke::escape);
    TestKeyboardButton(&inputMgr, wnd, DIK_1, ke::n1);
    TestKeyboardButton(&inputMgr, wnd, DIK_2, ke::n2);
    TestKeyboardButton(&inputMgr, wnd, DIK_3, ke::n3);
    TestKeyboardButton(&inputMgr, wnd, DIK_4, ke::n4);
    TestKeyboardButton(&inputMgr, wnd, DIK_5, ke::n5);
    TestKeyboardButton(&inputMgr, wnd, DIK_6, ke::n6);
    TestKeyboardButton(&inputMgr, wnd, DIK_7, ke::n7);
    TestKeyboardButton(&inputMgr, wnd, DIK_8, ke::n8);
    TestKeyboardButton(&inputMgr, wnd, DIK_9, ke::n9);
    TestKeyboardButton(&inputMgr, wnd, DIK_0, ke::n0);
    TestKeyboardButton(&inputMgr, wnd, DIK_MINUS, ke::minus_main);
    TestKeyboardButton(&inputMgr, wnd, DIK_EQUALS, ke::equals);
    TestKeyboardButton(&inputMgr, wnd, DIK_BACK, ke::backspace);
    TestKeyboardButton(&inputMgr, wnd, DIK_TAB, ke::tab);
    TestKeyboardButton(&inputMgr, wnd, DIK_Q, ke::q);
    TestKeyboardButton(&inputMgr, wnd, DIK_W, ke::w);
    TestKeyboardButton(&inputMgr, wnd, DIK_E, ke::e);
    TestKeyboardButton(&inputMgr, wnd, DIK_R, ke::r);
    TestKeyboardButton(&inputMgr, wnd, DIK_T, ke::t);
    TestKeyboardButton(&inputMgr, wnd, DIK_Y, ke::y);
    TestKeyboardButton(&inputMgr, wnd, DIK_U, ke::u);
    TestKeyboardButton(&inputMgr, wnd, DIK_I, ke::i);
    TestKeyboardButton(&inputMgr, wnd, DIK_O, ke::o);
    TestKeyboardButton(&inputMgr, wnd, DIK_P, ke::p);
    TestKeyboardButton(&inputMgr, wnd, DIK_LBRACKET, ke::left_bracket);
    TestKeyboardButton(&inputMgr, wnd, DIK_RBRACKET, ke::right_bracket);
    TestKeyboardButton(&inputMgr, wnd, DIK_RETURN, ke::enter_main);
    TestKeyboardButton(&inputMgr, wnd, DIK_LCONTROL, ke::left_control);
    TestKeyboardButton(&inputMgr, wnd, DIK_A, ke::a);
    TestKeyboardButton(&inputMgr, wnd, DIK_S, ke::s);
    TestKeyboardButton(&inputMgr, wnd, DIK_D, ke::d);
    TestKeyboardButton(&inputMgr, wnd, DIK_F, ke::f);
    TestKeyboardButton(&inputMgr, wnd, DIK_G, ke::g);
    TestKeyboardButton(&inputMgr, wnd, DIK_H, ke::h);
    TestKeyboardButton(&inputMgr, wnd, DIK_J, ke::j);
    TestKeyboardButton(&inputMgr, wnd, DIK_K, ke::k);
    TestKeyboardButton(&inputMgr, wnd, DIK_L, ke::l);
    TestKeyboardButton(&inputMgr, wnd, DIK_SEMICOLON, ke::semicolon);
    TestKeyboardButton(&inputMgr, wnd, DIK_APOSTROPHE, ke::apostrophe);
    TestKeyboardButton(&inputMgr, wnd, DIK_GRAVE, ke::grave);
    TestKeyboardButton(&inputMgr, wnd, DIK_LSHIFT, ke::left_shift);
    TestKeyboardButton(&inputMgr, wnd, DIK_BACKSLASH, ke::backslash);
    TestKeyboardButton(&inputMgr, wnd, DIK_Z, ke::z);
    TestKeyboardButton(&inputMgr, wnd, DIK_X, ke::x);
    TestKeyboardButton(&inputMgr, wnd, DIK_C, ke::c);
    TestKeyboardButton(&inputMgr, wnd, DIK_V, ke::v);
    TestKeyboardButton(&inputMgr, wnd, DIK_B, ke::b);
    TestKeyboardButton(&inputMgr, wnd, DIK_N, ke::n);
    TestKeyboardButton(&inputMgr, wnd, DIK_M, ke::m);
    TestKeyboardButton(&inputMgr, wnd, DIK_COMMA, ke::comma);
    TestKeyboardButton(&inputMgr, wnd, DIK_PERIOD, ke::period_main);
    TestKeyboardButton(&inputMgr, wnd, DIK_SLASH, ke::slash);
    TestKeyboardButton(&inputMgr, wnd, DIK_RSHIFT, ke::right_shift);
    TestKeyboardButton(&inputMgr, wnd, DIK_MULTIPLY, ke::multiply_keypad);
    TestKeyboardButton(&inputMgr, wnd, DIK_LMENU, ke::left_alt);
    TestKeyboardButton(&inputMgr, wnd, DIK_SPACE, ke::space);
    TestKeyboardButton(&inputMgr, wnd, DIK_CAPITAL, ke::capital);
    TestKeyboardButton(&inputMgr, wnd, DIK_F1, ke::f1);
    TestKeyboardButton(&inputMgr, wnd, DIK_F2, ke::f2);
    TestKeyboardButton(&inputMgr, wnd, DIK_F3, ke::f3);
    TestKeyboardButton(&inputMgr, wnd, DIK_F4, ke::f4);
    TestKeyboardButton(&inputMgr, wnd, DIK_F5, ke::f5);
    TestKeyboardButton(&inputMgr, wnd, DIK_F6, ke::f6);
    TestKeyboardButton(&inputMgr, wnd, DIK_F7, ke::f7);
    TestKeyboardButton(&inputMgr, wnd, DIK_F8, ke::f8);
    TestKeyboardButton(&inputMgr, wnd, DIK_F9, ke::f9);
    TestKeyboardButton(&inputMgr, wnd, DIK_F10, ke::f10);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMLOCK, ke::numlock);
    TestKeyboardButton(&inputMgr, wnd, DIK_SCROLL, ke::scroll_lock);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD7, ke::num7);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD8, ke::num8);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD9, ke::num9);
    TestKeyboardButton(&inputMgr, wnd, DIK_SUBTRACT, ke::minus_keypad);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD4, ke::num4);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD5, ke::num5);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD6, ke::num6);
    TestKeyboardButton(&inputMgr, wnd, DIK_ADD, ke::add_keypad);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD1, ke::num1);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD2, ke::num2);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD3, ke::num3);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD0, ke::num0);
    TestKeyboardButton(&inputMgr, wnd, DIK_DECIMAL, ke::period_keypad);
    TestKeyboardButton(&inputMgr, wnd, DIK_F11, ke::f11);
    TestKeyboardButton(&inputMgr, wnd, DIK_F12, ke::f12);
    //TestKeyboardButton(&inputMgr, wnd, DIK_F13); // Not on most KBs
    //TestKeyboardButton(&inputMgr, wnd, DIK_F14); // Not on most KBs
    //TestKeyboardButton(&inputMgr, wnd, DIK_F15); // Not on most KBs
    TestKeyboardButton(&inputMgr, wnd, DIK_PREVTRACK, ke::prev_track);
    TestKeyboardButton(&inputMgr, wnd, DIK_NEXTTRACK, ke::next_track);
    TestKeyboardButton(&inputMgr, wnd, DIK_NUMPADENTER, ke::enter_keypad);
    TestKeyboardButton(&inputMgr, wnd, DIK_RCONTROL, ke::right_control);
    TestKeyboardButton(&inputMgr, wnd, DIK_MUTE, ke::mute);
    TestKeyboardButton(&inputMgr, wnd, DIK_CALCULATOR, ke::calculator);
    TestKeyboardButton(&inputMgr, wnd, DIK_PLAYPAUSE, ke::play_pause);
    TestKeyboardButton(&inputMgr, wnd, DIK_MEDIASTOP, ke::media_stop);
    TestKeyboardButton(&inputMgr, wnd, DIK_VOLUMEDOWN, ke::volume_down);
    TestKeyboardButton(&inputMgr, wnd, DIK_VOLUMEUP, ke::volume_up);
    TestKeyboardButton(&inputMgr, wnd, DIK_WEBHOME, ke::web_home);
    TestKeyboardButton(&inputMgr, wnd, DIK_DIVIDE, ke::divide_keypad);
    TestKeyboardButton(&inputMgr, wnd, DIK_SYSRQ, ke::sysrq);
    TestKeyboardButton(&inputMgr, wnd, DIK_RMENU, ke::right_alt);
    TestKeyboardButton(&inputMgr, wnd, DIK_PAUSE, ke::pause);
    TestKeyboardButton(&inputMgr, wnd, DIK_HOME, ke::home);
    TestKeyboardButton(&inputMgr, wnd, DIK_UP, ke::up);
    TestKeyboardButton(&inputMgr, wnd, DIK_PRIOR, ke::page_up);
    TestKeyboardButton(&inputMgr, wnd, DIK_LEFT, ke::left);
    TestKeyboardButton(&inputMgr, wnd, DIK_RIGHT, ke::right);
    TestKeyboardButton(&inputMgr, wnd, DIK_END, ke::end);
    TestKeyboardButton(&inputMgr, wnd, DIK_DOWN, ke::down);
    TestKeyboardButton(&inputMgr, wnd, DIK_NEXT, ke::page_down);
    TestKeyboardButton(&inputMgr, wnd, DIK_INSERT, ke::insert);
    TestKeyboardButton(&inputMgr, wnd, DIK_DELETE, ke::delete_main);
    TestKeyboardButton(&inputMgr, wnd, DIK_LWIN, ke::left_sys);
    TestKeyboardButton(&inputMgr, wnd, DIK_RWIN, ke::right_sys);
    TestKeyboardButton(&inputMgr, wnd, DIK_POWER, ke::power_sys);
    TestKeyboardButton(&inputMgr, wnd, DIK_SLEEP, ke::sleep_sys);
    TestKeyboardButton(&inputMgr, wnd, DIK_WAKE, ke::wake_sys);
  }

  template <typename T_InputManagerType>
  void TestMouse(T_InputManagerType& inputMgr, HWND wnd)
  {
    typedef input_hid::MouseEvent me;

    TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_LEFTDOWN,
      MOUSEEVENTF_LEFTUP, NULL, me::left);

    TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_RIGHTDOWN,
      MOUSEEVENTF_RIGHTUP, NULL, me::right);

    TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_MIDDLEDOWN,
      MOUSEEVENTF_MIDDLEUP, NULL, me::middle);

    TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_XDOWN,
      MOUSEEVENTF_XUP, XBUTTON1, me::button4);

    TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_XDOWN,
      MOUSEEVENTF_XUP, XBUTTON2, me::button5);

    MouseEvent evt;

    evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_MOVE, 5, 0, 0);
    CHECK(evt.m_X.m_rel() == 5);
    CHECK(evt.m_Y.m_rel() == 0);
    CHECK(evt.m_X.m_abs().Get() == 5);
    CHECK(evt.m_Y.m_abs().Get() == 0);

    evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_MOVE, 5, 0, 0);
    CHECK(evt.m_X.m_rel() == 5);
    CHECK(evt.m_Y.m_rel() == 0);
    CHECK(evt.m_X.m_abs().Get() == 10);
    CHECK(evt.m_Y.m_abs().Get() == 0);

    evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_MOVE, 0, 5, 0);
    CHECK(evt.m_X.m_rel() == 0);
    CHECK(evt.m_Y.m_rel() == 5);
    CHECK(evt.m_X.m_abs().Get() == 10);
    CHECK(evt.m_Y.m_abs().Get() == 5);

    evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_MOVE, 0, 5, 0);
    CHECK(evt.m_X.m_rel() == 0);
    CHECK(evt.m_Y.m_rel() == 5);
    CHECK(evt.m_X.m_abs().Get() == 10);
    CHECK(evt.m_Y.m_abs().Get() == 10);

    evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_WHEEL, -5, -5, 1);
    CHECK(evt.m_X.m_rel() == -5);
    CHECK(evt.m_Y.m_rel() == -5);
    CHECK(evt.m_Z.m_rel() == 1);
    CHECK(evt.m_Z.m_abs() == 1);
    CHECK(evt.m_X.m_abs().Get() == 5);
    CHECK(evt.m_Y.m_abs().Get() == 5);

    evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_WHEEL, -10, -20, 1);
    CHECK(evt.m_X.m_rel() == -10);
    CHECK(evt.m_Y.m_rel() == -20);
    CHECK(evt.m_Z.m_rel() == 1);
    CHECK(evt.m_Z.m_abs() == 2);
    CHECK(evt.m_X.m_abs().Get() == -5);
    CHECK(evt.m_Y.m_abs().Get() == -15);

    // Reset the positions
    TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_MOVE, 5, 15, 0);
  }

  TEST_CASE("Input/InputManager/General", "")
  {
    core::time::Timer_T<> countDown;

    HWND wnd = CreateWin32Window();

    ParamList<HWND> params;
    params.m_param1 = wnd;
    InputManagerB inputMgr(params);
    InputManagerI inputMgrImm(params);

    KeyboardB* kb = inputMgr.CreateHID<KeyboardB>();
    CHECK(kb != NULL);

    KeyboardI* kbImm = inputMgrImm.CreateHID<KeyboardI>();
    CHECK(kbImm != NULL);

    if (kb)
    {
      TestKeyboard(inputMgr, wnd);
    }
    if (kbImm)
    {
      TestKeyboard(inputMgrImm, wnd);
    }

    using hid::MouseB;

    MouseB* mouse = inputMgr.CreateHID<MouseB>();
    CHECK(mouse != NULL);

    MouseI* mouseImm = inputMgrImm.CreateHID<MouseI>();
    CHECK(mouseImm != NULL);

    if (mouse)
    {
      TestMouse(inputMgr, wnd);
    }
    if (mouseImm)
    {
      // Intentioanlly commented out - test is very fragile
      //TestMouse(inputMgrImm, wnd);
    }
  }
};