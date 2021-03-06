#include "tlocTestCommon.h"

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/utilities/tlocPythagoras.h>

namespace TestingCircle
{
  using namespace tloc;
  using namespace tloc::math::types;

  typedef Circlef                   circle_type;
  typedef circle_type::value_type   value_type;
  typedef circle_type::point_type   point_type;

  TEST_CASE("Math/types/Circle/Ctors", "")
  {
    // Default constructor
    circle_type c;
    CHECK( c.GetRadius() == Approx(0.0f) );
    CHECK( ( c.GetPosition() == point_type(0, 0) ) );

    CHECK(c.IsValid() == false);

    // constructor with radius and position
    c = circle_type(circle_type::radius((value_type)1),
                    circle_type::position( point_type(1,1) ) );
    CHECK( c.GetRadius() == Approx(1.0f) );
    CHECK( ( c.GetPosition() == point_type(1, 1) ) );

    CHECK(c.IsValid() == true);

    // constructor with diameter
    c = circle_type(circle_type::diameter( (value_type)1) );
    CHECK(c.GetRadius() == Approx(0.5) );
    CHECK( ( c.GetPosition() == point_type(0, 0) ) );

    CHECK(c.IsValid() == true);

    // constructor with diameter and position
    c = circle_type(circle_type::diameter( (value_type)4 ),
                    circle_type::position( point_type(2, 2) ) );
    CHECK( c.GetRadius() == Approx(2.0f) );
    CHECK( (c.GetPosition() == point_type(2, 2) ) );

    CHECK(c.IsValid() == true);

    // copy ctor
    circle_type d(c);
    CHECK(d.IsValid() == true);
    CHECK( d.GetRadius() == Approx(2.0f) );
    CHECK( (d.GetPosition() == point_type(2, 2) ) );

    // assignment operator
    circle_type f( circle_type::radius(0.2f),
                   circle_type::position(point_type(1,1)) );
    d = f;
    CHECK(d.IsValid());
    CHECK(d.GetRadius() == Approx(0.2f));
    CHECK(d.GetPosition() == point_type(1, 1));

    f = circle_type(circle_type::radius(0.4f),
                    circle_type::position(point_type(2, 3)) );
    d.swap(f);
    CHECK(f.IsValid());
    CHECK(f.GetRadius() == Approx(0.2f));
    CHECK(f.GetPosition() == point_type(1, 1));

    CHECK(d.IsValid());
    CHECK(d.GetRadius() == Approx(0.4f));
    CHECK(d.GetPosition() == point_type(2, 3));

    swap(d, f);
    CHECK(d.IsValid());
    CHECK(d.GetRadius() == Approx(0.2f));
    CHECK(d.GetPosition() == point_type(1, 1));

    CHECK(f.IsValid());
    CHECK(f.GetRadius() == Approx(0.4f));
    CHECK(f.GetPosition() == point_type(2, 3));

    // different types
    Circlef32 circ;
    Circlef64 circ64(circ);
  }

  TEST_CASE("Math/types/Circle/Radius", "")
  {
    circle_type c;
    c.SetRadius( (value_type)1 );
    CHECK( c.GetRadius() == (value_type)1 );
    CHECK( c.IsValid() == true);
  }

  TEST_CASE("Math/types/Circle/Position", "")
  {
    circle_type c;
    c.SetPosition(point_type(0, 0) );
    CHECK( (c.GetPosition() == point_type(0, 0) ) );
  }

  TEST_CASE("Math/types/Circle/Contains_point", "")
  {
    circle_type c(circle_type::radius( (value_type)1 ) );
    CHECK(c.Contains(point_type(0, 0) ) == true );
    CHECK(c.Contains(point_type(0, 1) ) == true );
    CHECK(c.Contains(point_type(1, 1) ) == false);
  }

  TEST_CASE("Math/types/Circle/Contains_circle", "")
  {
    circle_type c(circle_type::radius( (value_type)2 ) );
    CHECK(c.Contains(c) == true); // Does contain itself

    circle_type c2(circle_type::radius( (value_type)1 ) );
    CHECK(c.Contains(c2) == true); // Does contain a smaller circle

    circle_type c3(circle_type::radius( (value_type)3 ) );
    CHECK(c.Contains(c3) == false); // Does not contain a bigger circle

    circle_type c4(circle_type::radius( (value_type)1 ),
                   circle_type::position( point_type(0, 1 ) ) );
    CHECK(c.Contains(c4) == true); // Does contain a smaller circle off centre
                                   // inside itself

    circle_type c5(circle_type::radius( (value_type)1 ),
      circle_type::position( point_type(0, 2 ) ) );
    CHECK(c.Contains(c5) == false); // Does not contain a smaller circle
                                    // partially intersecting

    circle_type c6(circle_type::radius( (value_type)1 ),
                   circle_type::position( point_type(0, 3 ) ) );
    CHECK(c.Contains(c6) == false); // Does not contain a smaller circle
                                    // outside itself
  }

  TEST_CASE("Math/types/Circle/Intersects", "")
  {
    circle_type c(circle_type::radius( (value_type)2 ) );
    CHECK(c.Intersects(c) == true); // Does intersect itself

    circle_type c2(circle_type::radius( (value_type)1 ) );
    CHECK(c.Intersects(c2) == true); // Does intersect a smaller circle

    circle_type c3(circle_type::radius( (value_type)3 ) );
    CHECK(c.Intersects(c3) == true); // Does intersect a bigger circle

    circle_type c4(circle_type::radius( (value_type)1 ),
      circle_type::position( point_type(0, 1 ) ) );
    CHECK(c.Intersects(c4) == true); // Does intersect a smaller circle off
                                     // centre inside itself

    circle_type c5(circle_type::radius( (value_type)1 ),
      circle_type::position( point_type(0, 2 ) ) );
    CHECK(c.Intersects(c5) == true); // Does intersect a smaller circle
                                      // partially intersecting

    circle_type c6(circle_type::radius( (value_type)1 ),
      circle_type::position( point_type(0, 3 ) ) );
    CHECK(c.Intersects(c6) == false); // Does not intersect a smaller circle
                                      // outside itself

    Ray2f ray( Ray2f::origin(Vec2f(0, 0)) );
    circle_type c7(circle_type::radius( (value_type)1 ) );
    CHECK(c7.Intersects(ray));

    c7.SetPosition(Vec2f(2.0f, 0.0f));
    CHECK_FALSE(c7.Intersects(ray));

    c7.SetPosition(Vec2f(0.5f, 0.8f));
    CHECK(c7.Intersects(ray));

    ray = Ray2f(Ray2f::origin(Vec2f(0.5f, 0.8f)) );
    CHECK(c7.Intersects(ray));
    c7.SetPosition(Vec2f(-0.5f, 0.8f));
    CHECK_FALSE(c7.Intersects(ray));
    c7.SetPosition(Vec2f(0.5f, -0.8f));
    CHECK_FALSE(c7.Intersects(ray));

  }

  TEST_CASE("Math/types/Circle/GetCoord", "")
  {
    using math::types::Degree;
    using tloc::math::utils::Pythagoras;

    circle_type c1(circle_type::radius(1.0f));

    {
      // Check against pythagoras
      Pythagoras pyth(Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      circle_type::point_type pFromC = c1.GetCoord(Degree(5.0f));

      // cos/sin accuracy is terrible
      CHECK(math::ApproxRelative(pFromC[0], p[0], 0.01f));
      CHECK(math::ApproxRelative(pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      circle_type::point_type pFromC = c1.GetCoord(Degree(-5.0f));

      // cos/sin accuracy is terrible
      CHECK(math::ApproxRelative(pFromC[0], p[0], 0.01f));
      CHECK(math::ApproxRelative(-pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::opposite>(),
                                pyth.GetSide<Pythagoras::base>() );
      circle_type::point_type pFromC = c1.GetCoord(Degree(85.0f));

      // cos/sin accuracy is terrible
      CHECK(math::ApproxRelative(pFromC[0], p[0], 0.01f));
      CHECK(math::ApproxRelative(pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::opposite>(),
                                pyth.GetSide<Pythagoras::base>() );
      circle_type::point_type pFromC = c1.GetCoord(Degree(95.0f));

      // cos/sin accuracy is terrible
      CHECK(math::ApproxRelative(-pFromC[0], p[0], 0.01f));
      CHECK(math::ApproxRelative(pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      circle_type::point_type pFromC = c1.GetCoord(Degree(355.0f));

      // cos/sin accuracy is terrible
      CHECK(math::ApproxRelative(pFromC[0], p[0], 0.01f));
      CHECK(math::ApproxRelative(-pFromC[1], p[1], 0.01f));
    }

    circle_type c2(circle_type::radius(1.0f),
                   circle_type::position(Vec2f(1.0f, 1.0f) ));

    {
      // Check against pythagoras
      Pythagoras pyth(Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      p += c2.GetPosition();
      circle_type::point_type pFromC = c2.GetCoord(Degree(5.0f));

      // cos/sin accuracy is terrible
      CHECK(math::ApproxRelative(pFromC[0], p[0], 0.01f));
      CHECK(math::ApproxRelative(pFromC[1], p[1], 0.01f));
    }
  }
};