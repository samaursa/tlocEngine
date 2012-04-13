#include "tlocTestCommon.h"

#include "tlocCore/tlocUtils.h"

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
      : m_caller(a_caller), m_keypresses(0), m_keyreleases(0) {}

    void OnKeyPress(const tl_size a_caller, const KeyboardEvent& a_event)
    {
      TLOC_UNUSED(a_event);
      CHECK(IsSamePointer(m_caller, a_caller) == true);
      m_keypresses++;
    }

    void OnKeyRelease(const tl_size a_caller, const KeyboardEvent& a_event)
    {
      TLOC_UNUSED(a_event);
      CHECK(IsSamePointer(m_caller, a_caller) == true);
      m_keyreleases++;
    }

    T_Keyboard* m_caller;
    u32 m_keypresses;
    u32 m_keyreleases;
  };

  TLOC_DEF_TYPE(sampleInputObject<Keyboard<> >);

  void GenerateKey ( int vk , BOOL bExtended)
  {
    KEYBDINPUT  kb={0};
    INPUT    Input={0};
    // generate down
    if ( bExtended )
      kb.dwFlags  = KEYEVENTF_EXTENDEDKEY;
    kb.wVk  = (WORD)vk;
    Input.type  = INPUT_KEYBOARD;

    Input.ki  = kb;
    ::SendInput(1,&Input,sizeof(Input));

    // generate up
    ::ZeroMemory(&kb,sizeof(KEYBDINPUT));
    ::ZeroMemory(&Input,sizeof(INPUT));
    kb.dwFlags  =  KEYEVENTF_KEYUP;
    if ( bExtended )
      kb.dwFlags  |= KEYEVENTF_EXTENDEDKEY;

    kb.wVk    =  (WORD)vk;
    Input.type  =  INPUT_KEYBOARD;
    Input.ki  =  kb;
    ::SendInput(1,&Input,sizeof(Input));
  }

  TEST_CASE("Input/InputManager/General", "")
  {
    InputParameterList<HWND> params;
    params.m_param1 = GetConsoleWindow();
    InputManager<> inputMgr(params);

    Keyboard<>* testKeyboard = inputMgr.CreateHID<Keyboard<> >(hid::keyboard);
    TLOC_UNUSED(testKeyboard);

    sampleInputObject<Keyboard<> > callback(testKeyboard);
    testKeyboard->Register(&callback);

    // TODO: Fix this (GenerateKey doesn't work, but user key presses do)
    //while (callback.m_keypresses < 5)
    //{
    //  GenerateKey(VK_ESCAPE, FALSE);
    //  testKeyboard->Update();
    //}
  }
};