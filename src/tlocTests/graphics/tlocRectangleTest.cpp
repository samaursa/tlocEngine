#include "tlocTestCommon.h"

#include <tlocMath/data_types/tlocRectangle.h>

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/data_structures/tlocVariadic.inl>

namespace TestingRectangle
{
  using namespace tloc;
  using namespace tloc::math::types;

  TEST_CASE("Graphics/types/Rectangle", "")
  {
    Recti r;
    CHECK(r.GetCoord<Recti::left>()    == 0);
    CHECK(r.GetCoord<Recti::right>()   == 0);
    CHECK(r.GetCoord<Recti::top>()     == 0);
    CHECK(r.GetCoord<Recti::bottom>()  == 0);

    CHECK(r.IsValid() == false);
    CHECK(r.GetWidth() == 0);
    CHECK(r.GetHeight() == 0);

    r = Recti(Recti::left(0), Recti::right(2), Recti::top(5), Recti::bottom(0));
    CHECK(r.GetCoord<Recti::left>()    == 0);
    CHECK(r.GetCoord<Recti::right>()   == 2);
    CHECK(r.GetCoord<Recti::top>()     == 5);
    CHECK(r.GetCoord<Recti::bottom>()  == 0);
    CHECK(r.GetWidth() == 2);
    CHECK(r.GetHeight() == 5);

    CHECK(r.IsValid() == true);

    r.SetCoord<Recti::left>(-1);
    CHECK(r.GetCoord<Recti::left>() == -1);
    CHECK(r.IsValid() == true);
    CHECK(r.GetWidth() == 3);
    CHECK(r.GetHeight() == 5);

    r = Recti(Recti::left(0), Recti::right(5), Recti::top(2), Recti::bottom(0) );
    r.Offset(core::Variadic2i(2, 2) );
    CHECK(r.GetCoord<Recti::left>()    == 2);
    CHECK(r.GetCoord<Recti::right>()   == 7);
    CHECK(r.GetCoord<Recti::top>()     == 4);
    CHECK(r.GetCoord<Recti::bottom>()  == 2);
    CHECK(r.IsValid() == true);
    CHECK(r.GetWidth() == 5);
    CHECK(r.GetHeight() == 2);

    r = Recti(Recti::left(0), Recti::right(2), Recti::top(5), Recti::bottom(0) );
    CHECK(r.Contains(core::Variadic2i(1, 1)) );
    CHECK(r.Contains(core::Variadic2i(0, 0)) );
    CHECK(r.Contains(core::Variadic2i(2, 2)) );

    CHECK_FALSE(r.Contains(core::Variadic2i(3, 2)) );
    CHECK_FALSE(r.Contains(core::Variadic2i(1, 6)) );
    CHECK_FALSE(r.Contains(core::Variadic2i(-1, 2)));
    CHECK_FALSE(r.Contains(core::Variadic2i(1, -1)));

    r = Recti(Recti::left(0), Recti::right(2), Recti::top(5), Recti::bottom(0) );
    {
      Recti inter(Recti::left(1), Recti::right(2), Recti::top(4), Recti::bottom(1) );
      CHECK(r.Intersects(inter));

      Recti interRet;
      CHECK(r.Intersects(inter, interRet));
    }

    {
      Recti inter(Recti::left(-1), Recti::right(0), Recti::top(0), Recti::bottom(-1) );
      CHECK_FALSE(r.Intersects(inter));
    }

    r = Recti(Recti::half_width(1), Recti::half_height(2));
    CHECK(r.GetWidth() == 2);
    CHECK(r.GetHeight() == 4);
  }
};