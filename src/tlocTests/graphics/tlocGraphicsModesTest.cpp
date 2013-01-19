#include "tlocTestCommon.h"
#include <tlocGraphics/window/tlocGraphicsModes.h>

namespace TestingGraphicsModes
{
  using namespace tloc;
  using namespace graphics;

  TEST_CASE("Graphics/GraphicsModes/General", "")
  {
    win::GraphicsMode<> a(win::GraphicsMode<>::Properties(0, 0));
  }
};