#include "tlocTestCommon.h"

#include "tlocGraphics/tlocWindow.h"

namespace TestingWindow
{
  USING_TLOC;
  using namespace graphics;

  TEST_CASE("Graphics/Window/General", "")
  {
    Window<> newWindow;
    newWindow.Create();
  }
};