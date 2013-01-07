#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocPointerUtils.h>
#include <tlocCore/time/tlocTime.h>

#define private public
#define protected public
#include <tlocInput/tlocInput.h>
#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/HIDs/tlocKeyboard.h>
#include <tlocInput/HIDs/tlocMouse.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <dinput.h>

namespace TestingInput
{
  USING_TLOC;
  using namespace input;

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
  }; TLOC_DEF_TYPE(sampleInputKeyboard<Keyboard<> >);

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
  }; TLOC_DEF_TYPE(sampleInputMouse<Mouse<> >);


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

  void TestKeyboardButton(InputManager<>* a_im, HWND a_wnd, WORD a_key)
  {
    core::time::Timer_T<> countDown;
    Keyboard<>* kb = a_im->GetHID<Keyboard<> >(hid::keyboard);

    CHECK(kb != NULL);

    if (kb)
    {
      sampleInputKeyboard<Keyboard<> > callback(kb);
      kb->Register(&callback);

      while ( countDown.ElapsedMilliSeconds() < 1000 &&
        (callback.m_keypresses < 1 || callback.m_keyreleases < 1) )
      {
        UpdateWin32Window(a_wnd);
        SendButtonPress(a_key);
        SendButtonRelease(a_key);
        a_im->Update();
      }

      kb->UnRegister(&callback);

      CHECK(callback.m_keypresses > 0);
      CHECK(callback.m_keyreleases > 0);
      if (callback.m_keypresses == 0 || callback.m_keyreleases == 0)
      {
        WARN(a_key);
      }
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

  void TestMouseButton(InputManager<>* a_im, HWND a_wnd, WORD a_buttonDown,
                       WORD a_buttonUp, WORD a_extraData)
  {
    core::time::Timer_T<> countDown;
    Mouse<>* mouse = a_im->GetHID<Mouse<> >(hid::mouse);

    CHECK(mouse != NULL);

    if (mouse)
    {
      sampleInputMouse<Mouse<> > callback(mouse);
      mouse->Register(&callback);

      while ( countDown.ElapsedMilliSeconds() < 1000 &&
        (callback.m_buttonPresses < 1 || callback.m_buttonReleases < 1) )
      {
        UpdateWin32Window(a_wnd);
        SendMousePress(a_buttonDown, a_extraData);
        SendMousePress(a_buttonUp, a_extraData);
        a_im->Update();
      }

      mouse->UnRegister(&callback);

      CHECK(callback.m_buttonPresses > 0);
      CHECK(callback.m_buttonReleases > 0);
      if (callback.m_buttonPresses == 0 || callback.m_buttonReleases == 0)
      {
        WARN(a_buttonDown);
      }
    }
  }

  MouseEvent TestMouseMove(InputManager<>* a_im, HWND a_wnd, WORD a_axis,
                     tl_int a_x, tl_int a_y, WORD a_data)
  {
    core::time::Timer_T<> countDown;
    Mouse<>* mouse = a_im->GetHID<Mouse<> >(hid::mouse);

    CHECK(mouse != NULL);

    if (mouse)
    {
      sampleInputMouse<Mouse<> > callback(mouse);
      mouse->Register(&callback);

      SendMousePress(a_axis, a_data,
                     static_cast<LONG>(a_x), static_cast<LONG>(a_y));

      while (countDown.ElapsedMilliSeconds() < 1000 &&
             callback.m_movementEvents == 0)
      {
        UpdateWin32Window(a_wnd);
        a_im->Update();
      }

      mouse->UnRegister(&callback);
      CHECK(callback.m_movementEvents > 0);

      return callback.m_event;
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

  TEST_CASE("Input/InputManager/General", "")
  {
    core::time::Timer_T<> countDown;

    HWND wnd = CreateWin32Window();

    InputParameterList<HWND> params;
    params.m_param1 = wnd;
    InputManager<> inputMgr(params);

    Keyboard<>* kb = inputMgr.CreateHID<Keyboard<> >(hid::keyboard);
    CHECK(kb != NULL);

    if (kb)
    {
      TestKeyboardButton(&inputMgr, wnd, DIK_ESCAPE);
      TestKeyboardButton(&inputMgr, wnd, DIK_1);
      TestKeyboardButton(&inputMgr, wnd, DIK_2);
      TestKeyboardButton(&inputMgr, wnd, DIK_3);
      TestKeyboardButton(&inputMgr, wnd, DIK_4);
      TestKeyboardButton(&inputMgr, wnd, DIK_5);
      TestKeyboardButton(&inputMgr, wnd, DIK_6);
      TestKeyboardButton(&inputMgr, wnd, DIK_7);
      TestKeyboardButton(&inputMgr, wnd, DIK_8);
      TestKeyboardButton(&inputMgr, wnd, DIK_9);
      TestKeyboardButton(&inputMgr, wnd, DIK_0);
      TestKeyboardButton(&inputMgr, wnd, DIK_MINUS);
      TestKeyboardButton(&inputMgr, wnd, DIK_EQUALS);
      TestKeyboardButton(&inputMgr, wnd, DIK_BACK);
      TestKeyboardButton(&inputMgr, wnd, DIK_TAB);
      TestKeyboardButton(&inputMgr, wnd, DIK_Q);
      TestKeyboardButton(&inputMgr, wnd, DIK_W);
      TestKeyboardButton(&inputMgr, wnd, DIK_E);
      TestKeyboardButton(&inputMgr, wnd, DIK_R);
      TestKeyboardButton(&inputMgr, wnd, DIK_T);
      TestKeyboardButton(&inputMgr, wnd, DIK_Y);
      TestKeyboardButton(&inputMgr, wnd, DIK_U);
      TestKeyboardButton(&inputMgr, wnd, DIK_I);
      TestKeyboardButton(&inputMgr, wnd, DIK_O);
      TestKeyboardButton(&inputMgr, wnd, DIK_P);
      TestKeyboardButton(&inputMgr, wnd, DIK_LBRACKET);
      TestKeyboardButton(&inputMgr, wnd, DIK_RBRACKET);
      TestKeyboardButton(&inputMgr, wnd, DIK_RETURN);
      TestKeyboardButton(&inputMgr, wnd, DIK_LCONTROL);
      TestKeyboardButton(&inputMgr, wnd, DIK_A);
      TestKeyboardButton(&inputMgr, wnd, DIK_S);
      TestKeyboardButton(&inputMgr, wnd, DIK_D);
      TestKeyboardButton(&inputMgr, wnd, DIK_F);
      TestKeyboardButton(&inputMgr, wnd, DIK_G);
      TestKeyboardButton(&inputMgr, wnd, DIK_H);
      TestKeyboardButton(&inputMgr, wnd, DIK_J);
      TestKeyboardButton(&inputMgr, wnd, DIK_K);
      TestKeyboardButton(&inputMgr, wnd, DIK_L);
      TestKeyboardButton(&inputMgr, wnd, DIK_SEMICOLON);
      TestKeyboardButton(&inputMgr, wnd, DIK_APOSTROPHE);
      TestKeyboardButton(&inputMgr, wnd, DIK_GRAVE);
      TestKeyboardButton(&inputMgr, wnd, DIK_LSHIFT);
      TestKeyboardButton(&inputMgr, wnd, DIK_BACKSLASH);
      TestKeyboardButton(&inputMgr, wnd, DIK_Z);
      TestKeyboardButton(&inputMgr, wnd, DIK_X);
      TestKeyboardButton(&inputMgr, wnd, DIK_C);
      TestKeyboardButton(&inputMgr, wnd, DIK_V);
      TestKeyboardButton(&inputMgr, wnd, DIK_B);
      TestKeyboardButton(&inputMgr, wnd, DIK_N);
      TestKeyboardButton(&inputMgr, wnd, DIK_M);
      TestKeyboardButton(&inputMgr, wnd, DIK_COMMA);
      TestKeyboardButton(&inputMgr, wnd, DIK_PERIOD);
      TestKeyboardButton(&inputMgr, wnd, DIK_SLASH);
      TestKeyboardButton(&inputMgr, wnd, DIK_RSHIFT);
      TestKeyboardButton(&inputMgr, wnd, DIK_MULTIPLY);
      TestKeyboardButton(&inputMgr, wnd, DIK_LMENU);
      TestKeyboardButton(&inputMgr, wnd, DIK_SPACE);
      TestKeyboardButton(&inputMgr, wnd, DIK_CAPITAL);
      TestKeyboardButton(&inputMgr, wnd, DIK_F1);
      TestKeyboardButton(&inputMgr, wnd, DIK_F2);
      TestKeyboardButton(&inputMgr, wnd, DIK_F3);
      TestKeyboardButton(&inputMgr, wnd, DIK_F4);
      TestKeyboardButton(&inputMgr, wnd, DIK_F5);
      TestKeyboardButton(&inputMgr, wnd, DIK_F6);
      TestKeyboardButton(&inputMgr, wnd, DIK_F7);
      TestKeyboardButton(&inputMgr, wnd, DIK_F8);
      TestKeyboardButton(&inputMgr, wnd, DIK_F9);
      TestKeyboardButton(&inputMgr, wnd, DIK_F10);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMLOCK);
      TestKeyboardButton(&inputMgr, wnd, DIK_SCROLL);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD7);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD8);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD9);
      TestKeyboardButton(&inputMgr, wnd, DIK_SUBTRACT);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD4);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD5);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD6);
      TestKeyboardButton(&inputMgr, wnd, DIK_ADD);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD1);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD2);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD3);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPAD0);
      TestKeyboardButton(&inputMgr, wnd, DIK_DECIMAL);
      TestKeyboardButton(&inputMgr, wnd, DIK_F11);
      TestKeyboardButton(&inputMgr, wnd, DIK_F12);
      //TestKeyboardButton(&inputMgr, wnd, DIK_F13); // Not on most KBs
      //TestKeyboardButton(&inputMgr, wnd, DIK_F14); // Not on most KBs
      //TestKeyboardButton(&inputMgr, wnd, DIK_F15); // Not on most KBs
      TestKeyboardButton(&inputMgr, wnd, DIK_NEXTTRACK);
      TestKeyboardButton(&inputMgr, wnd, DIK_NUMPADENTER);
      TestKeyboardButton(&inputMgr, wnd, DIK_RCONTROL);
      TestKeyboardButton(&inputMgr, wnd, DIK_MUTE);
      TestKeyboardButton(&inputMgr, wnd, DIK_CALCULATOR);
      TestKeyboardButton(&inputMgr, wnd, DIK_PLAYPAUSE);
      TestKeyboardButton(&inputMgr, wnd, DIK_MEDIASTOP);
      TestKeyboardButton(&inputMgr, wnd, DIK_VOLUMEDOWN);
      TestKeyboardButton(&inputMgr, wnd, DIK_VOLUMEUP);
      TestKeyboardButton(&inputMgr, wnd, DIK_WEBHOME);
      TestKeyboardButton(&inputMgr, wnd, DIK_DIVIDE);
      TestKeyboardButton(&inputMgr, wnd, DIK_SYSRQ);
      TestKeyboardButton(&inputMgr, wnd, DIK_RMENU);
      TestKeyboardButton(&inputMgr, wnd, DIK_PAUSE);
      TestKeyboardButton(&inputMgr, wnd, DIK_HOME);
      TestKeyboardButton(&inputMgr, wnd, DIK_UP);
      TestKeyboardButton(&inputMgr, wnd, DIK_PRIOR);
      TestKeyboardButton(&inputMgr, wnd, DIK_LEFT);
      TestKeyboardButton(&inputMgr, wnd, DIK_RIGHT);
      TestKeyboardButton(&inputMgr, wnd, DIK_END);
      TestKeyboardButton(&inputMgr, wnd, DIK_DOWN);
      TestKeyboardButton(&inputMgr, wnd, DIK_NEXT);
      TestKeyboardButton(&inputMgr, wnd, DIK_INSERT);
      TestKeyboardButton(&inputMgr, wnd, DIK_DELETE);
      TestKeyboardButton(&inputMgr, wnd, DIK_LWIN);
      TestKeyboardButton(&inputMgr, wnd, DIK_RWIN);
      TestKeyboardButton(&inputMgr, wnd, DIK_POWER);
      TestKeyboardButton(&inputMgr, wnd, DIK_SLEEP);
      TestKeyboardButton(&inputMgr, wnd, DIK_WAKE);
    }

    Mouse<>* mouse = inputMgr.CreateHID<Mouse<> >(hid::mouse);
    CHECK(mouse != NULL);

    if (mouse)
    {
      TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_LEFTDOWN,
                                      MOUSEEVENTF_LEFTUP, NULL);
      TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_RIGHTDOWN,
                                      MOUSEEVENTF_RIGHTUP, NULL);
      TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_MIDDLEDOWN,
                                      MOUSEEVENTF_MIDDLEUP, NULL);
      TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_XDOWN,
                                      MOUSEEVENTF_XUP, XBUTTON1);
      TestMouseButton(&inputMgr, wnd, MOUSEEVENTF_XDOWN,
                                      MOUSEEVENTF_XUP, XBUTTON2);

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

      evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_WHEEL, 0, 0, 1);
      CHECK(evt.m_Y.m_rel() == 0);
      CHECK(evt.m_Y.m_rel() == 0);
      CHECK(evt.m_Z.m_rel() == 1);
      CHECK(evt.m_Z.m_abs() == 1);

      evt = TestMouseMove(&inputMgr, wnd, MOUSEEVENTF_WHEEL, 0, 0, 1);
      CHECK(evt.m_Y.m_rel() == 0);
      CHECK(evt.m_Y.m_rel() == 0);
      CHECK(evt.m_Z.m_rel() == 1);
      CHECK(evt.m_Z.m_abs() == 2);
    }
  }
};