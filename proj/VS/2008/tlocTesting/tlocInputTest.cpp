#include "tlocTestCommon.h"

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

  struct sampleInputObject
  {
  };

  TLOC_DEF_TYPE(sampleInputObject);

  TEST_CASE("Input/InputManager/General", "")
  {
    InputParameterList<HWND> params;
    params.m_param1 = GetConsoleWindow();
    InputManager<InputPolicy::Buffered, core::PlatformInfo<>::platform_type> inputMgr(params);

    Keyboard<>* testKeyboard = inputMgr.CreateHID<Keyboard<> >(hid::keyboard);
    TLOC_UNUSED(testKeyboard);
  }
};