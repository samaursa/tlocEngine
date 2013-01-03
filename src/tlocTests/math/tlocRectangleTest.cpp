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

    Rectf r = Rectf(Rectf::left(-1), Rectf::right(0),
              Rectf::top(0), Rectf::bottom(-1) );
    CHECK(r.IsValid());
    CHECK(r.GetWidth() == Approx(1));
    CHECK(r.GetHeight() == Approx(1));
    CHECK(r.GetPosition() == math::Vec2f(-0.5f, -0.5f));
    CHECK(r.GetWidth() == Approx(1));
    CHECK(r.GetHeight() == Approx(1));

    r = Rectf();
    r.SetWidth(0.5f);
    r.SetHeight(5.0f);
    CHECK(r.GetWidth() == 0.5f);
    CHECK(r.GetHeight() == 5.0f);
    CHECK(r.GetValue<Rectf::left>()   == Approx(-0.25f));
    CHECK(r.GetValue<Rectf::right>()  == Approx(0.25f));
    CHECK(r.GetValue<Rectf::top>()    == Approx(2.5f));
    CHECK(r.GetValue<Rectf::bottom>() == Approx(-2.5f));

    r = Rectf(Rectf::width(1.0f), Rectf::height(1.0f),
              Rectf::position(math::Vec2f(0.5f, 0.5f)) );
    CHECK(r.GetWidth() == 1.0f);
    CHECK(r.GetHeight() == 1.0f);
    CHECK(r.GetValue<Rectf::left>()   == Approx(0.0f));
    CHECK(r.GetValue<Rectf::right>()  == Approx(1.0f));
    CHECK(r.GetValue<Rectf::top>()    == Approx(1.0f));
    CHECK(r.GetValue<Rectf::bottom>() == Approx(0.0f));

    r = Rectf();
    CHECK(r.GetValue<Rectf::left>()    == 0);
    CHECK(r.GetValue<Rectf::right>()   == 0);
    CHECK(r.GetValue<Rectf::top>()     == 0);
    CHECK(r.GetValue<Rectf::bottom>()  == 0);

    CHECK_FALSE(r.IsValid());
    CHECK(r.GetWidth() == Approx(0) );
    CHECK(r.GetHeight() == Approx(0) );

    Rectf::point_type center;
    center[0] = 0;
    center[1] = 0;
    CHECK((r.GetPosition() == center));

    r = Rectf(Rectf::left(0), Rectf::right(2), Rectf::top(5), Rectf::bottom(0));
    CHECK(r.GetValue<Rectf::left>()    == 0);
    CHECK(r.GetValue<Rectf::right>()   == 2);
    CHECK(r.GetValue<Rectf::top>()     == 5);
    CHECK(r.GetValue<Rectf::bottom>()  == 0);
    CHECK(r.GetWidth() == 2);
    CHECK(r.GetHeight() == 5);

    Rectf rCopy(r);
    CHECK(r.GetValue<Rectf::left>()    == 0);
    CHECK(r.GetValue<Rectf::right>()   == 2);
    CHECK(r.GetValue<Rectf::top>()     == 5);
    CHECK(r.GetValue<Rectf::bottom>()  == 0);

    center[0] = 1.0f;
    center[1] = 2.5f;
    CHECK((r.GetPosition() == center));

    CHECK(r.IsValid() == true);

    r = Rectf(Rectf::left(0), Rectf::right(5), Rectf::top(2), Rectf::bottom(0) );
    r.Offset(math::Vec2f(2, 2) );
    CHECK(r.GetValue<Rectf::left>()    == 2);
    CHECK(r.GetValue<Rectf::right>()   == 7);
    CHECK(r.GetValue<Rectf::top>()     == 4);
    CHECK(r.GetValue<Rectf::bottom>()  == 2);
    CHECK(r.IsValid() == true);
    CHECK(r.GetWidth() == 5);
    CHECK(r.GetHeight() == 2);

    center[0] = 4.5f;
    center[1] = 3.0f;
    CHECK((r.GetPosition() == center));

    r = Rectf(Rectf::left(0), Rectf::right(2), Rectf::top(5), Rectf::bottom(0) );
    CHECK(r.Contains(math::Vec2f(1, 1)) );
    CHECK(r.Contains(math::Vec2f(0, 0)) );
    CHECK(r.Contains(math::Vec2f(2, 2)) );

    CHECK_FALSE(r.Contains(math::Vec2f(3, 2)) );
    CHECK_FALSE(r.Contains(math::Vec2f(1, 6)) );
    CHECK_FALSE(r.Contains(math::Vec2f(-1, 2)));
    CHECK_FALSE(r.Contains(math::Vec2f(1, -1)));

    r = Rectf(Rectf::left(0), Rectf::right(2), Rectf::top(5), Rectf::bottom(0) );
    {
      Rectf inter(Rectf::left(1), Rectf::right(2), Rectf::top(4), Rectf::bottom(1) );
      CHECK(r.Intersects(inter));

      Rectf interRet;
      CHECK(r.Intersects(inter, interRet));
    }

    {
      Rectf inter(Rectf::left(-1), Rectf::right(0), Rectf::top(0), Rectf::bottom(-1) );
      CHECK_FALSE(r.Intersects(inter));
    }

    r = Rectf(Rectf::width(1), Rectf::height(2));
    CHECK(r.GetWidth() == Approx(1));
    CHECK(r.GetHeight() == Approx(2));

    center[0] = 0;
    center[1] = 0;
    CHECK((r.GetPosition() == center));
  }
};