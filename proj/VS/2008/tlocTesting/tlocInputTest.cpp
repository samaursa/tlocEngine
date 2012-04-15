#include "tlocTestCommon.h"

#include "tlocCore/tlocUtils.h"
#include "tlocCore/tlocTime.h"

#define private public
#define protected public
#include "tlocInput/tlocInput.h"
#include "tlocInput/tlocInputTypes.h"
#include "tlocInput/tlocKeyboard.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace TestingInput
{
  USING_TLOC;
  using namespace input;

  template <typename T_Keyboard>
  struct sampleInputObject
  {
    sampleInputObject(T_Keyboard* a_caller)
      : m_event(KeyboardEvent::none),
        m_caller(a_caller),
        m_keypresses(0),
        m_keyreleases(0) {}

    void OnKeyPress(const tl_size a_caller, const KeyboardEvent& a_event)
    {
      TLOC_UNUSED(a_event);
      CHECK(IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_keypresses++;
    }

    void OnKeyRelease(const tl_size a_caller, const KeyboardEvent& a_event)
    {
      TLOC_UNUSED(a_event);
      CHECK(IsSamePointer(m_caller, a_caller) == true);
      m_event = a_event;
      m_caller = (KeyboardBuff*)(void*)(a_caller);
      m_keyreleases++;
    }

    KeyboardEvent m_event;
    T_Keyboard* m_caller;
    u32 m_keypresses;
    u32 m_keyreleases;
  };

  TLOC_DEF_TYPE(sampleInputObject<Keyboard<> >);

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

  void TestKeyboardButton(InputManager<>* a_im, HWND a_wnd, WORD a_key)
  {
    TLOC_UNUSED_3(a_im, a_wnd, a_key);
    SendButtonPress(0x01);
    SendButtonRelease(0x01);

    core::Timer<> countDown;
    Keyboard<>* kb = a_im->GetHID<Keyboard<> >(hid::keyboard);

    sampleInputObject<Keyboard<> > callback(kb);
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

  TEST_CASE("Input/InputManager/General", "")
  {
    core::Timer<> countDown;

    HWND wnd = CreateWin32Window();

    InputParameterList<HWND> params;
    params.m_param1 = wnd;
    InputManager<> inputMgr(params);

    Keyboard<>* kb = inputMgr.CreateHID<Keyboard<> >(hid::keyboard);
    CHECK(kb != NULL);

    if (kb)
    {
      TestKeyboardButton(&inputMgr, wnd, 0x01);
      TestKeyboardButton(&inputMgr, wnd, 0x02);
      TestKeyboardButton(&inputMgr, wnd, 0x03);
      TestKeyboardButton(&inputMgr, wnd, 0x04);
      TestKeyboardButton(&inputMgr, wnd, 0x05);
      TestKeyboardButton(&inputMgr, wnd, 0x06);
      TestKeyboardButton(&inputMgr, wnd, 0x07);
      TestKeyboardButton(&inputMgr, wnd, 0x08);
      TestKeyboardButton(&inputMgr, wnd, 0x09);
      TestKeyboardButton(&inputMgr, wnd, 0x00);
    }
  }
};