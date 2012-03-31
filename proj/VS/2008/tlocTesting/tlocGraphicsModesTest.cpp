#include "tlocTestCommon.h"
#include "tlocGraphics/tlocGraphicsModes.h"

namespace TestingGraphicsModes
{
  USING_TLOC;
  using namespace graphics;

  TEST_CASE("Graphics/GraphicsModes/General", "")
  {
    GraphicsMode<> a(GraphicsMode<>::Properties(0, 0));
  }
};