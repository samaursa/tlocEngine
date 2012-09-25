#include "tlocTestCommon.h"

#include <tlocGraphics/data_types/tlocRectangle.h>

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/data_structures/tlocVariadic.inl>

namespace TestingRectangle
{
  using namespace tloc;
  using namespace tloc::graphics::types;

  TEST_CASE("Graphics/types/Rectangle", "")
  {
    RectangleInt r;
    CHECK(r.GetCoord(RectangleInt::left) == 0);
    CHECK(r.GetCoord(RectangleInt::right) == 0);
    CHECK(r.GetCoord(RectangleInt::top) == 0);
    CHECK(r.GetCoord(RectangleInt::bottom) == 0);

    CHECK(r.IsValid() == false);
    CHECK(r.GetWidth() == 0);
    CHECK(r.GetHeight() == 0);

    r = RectangleInt(0, 2, 5, 0);
    CHECK(r.GetCoord(RectangleInt::left) == 0);
    CHECK(r.GetCoord(RectangleInt::right) == 2);
    CHECK(r.GetCoord(RectangleInt::top) == 5);
    CHECK(r.GetCoord(RectangleInt::bottom) == 0);
    CHECK(r.GetWidth() == 2);
    CHECK(r.GetHeight() == 5);

    CHECK(r.IsValid() == true);

    r.SetCoord(RectangleInt::left, -1);
    CHECK(r.GetCoord(RectangleInt::left) == -1);
    CHECK(r.IsValid() == true);
    CHECK(r.GetWidth() == 3);
    CHECK(r.GetHeight() == 5);

    r = RectangleInt(0, 2, 5, 0);
    r.Offset(core::Variadic2i(2, 2) );
    CHECK(r.GetCoord(RectangleInt::left) == 2);
    CHECK(r.GetCoord(RectangleInt::right) == 4);
    CHECK(r.GetCoord(RectangleInt::top) == 7);
    CHECK(r.GetCoord(RectangleInt::bottom) == 2);
    CHECK(r.IsValid() == true);
    CHECK(r.GetWidth() == 2);
    CHECK(r.GetHeight() == 5);

    r = RectangleInt(0, 2, 5, 0);
    CHECK(r.Contains(core::Variadic2i(1, 1)) == true);
    CHECK(r.Contains(core::Variadic2i(0, 0)) == true);
    CHECK(r.Contains(core::Variadic2i(2, 2)) == true);
    CHECK(r.Contains(core::Variadic2i(3, 2)) == false);
    CHECK(r.Contains(core::Variadic2i(1, 6)) == false);
    CHECK(r.Contains(core::Variadic2i(-1, 2)) == false);
    CHECK(r.Contains(core::Variadic2i(1, -1)) == false);

    r = RectangleInt(0, 2, 5, 0);
    {
      RectangleInt inter(1, 2, 4, 1);
      CHECK(r.Intersects(inter) == true);

      RectangleInt interRet;
      r.Intersects(inter, interRet);
      CHECK(interRet == inter);
    }
    {
      RectangleInt inter(-1, 0, -1, 0);
      CHECK(r.Intersects(inter) == false);
    }
  }
};