#include "tlocTestCommon.h"

#include <tlocMath/data_types/tlocCircle.h>
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
    CHECK( c.GetRadius() == (value_type)0 );
    CHECK( ( c.GetPosition() == point_type(0, 0) ) );

    CHECK(c.IsValid() == false);

    // constructor with radius and position
    c = circle_type(circle_type::radius((value_type)1),
                    circle_type::position( point_type(1,1) ) );
    CHECK( c.GetRadius() == (value_type)1 );
    CHECK( ( c.GetPosition() == point_type(1, 1) ) );

    CHECK(c.IsValid() == true);

    // constructor with diameter
    c = circle_type(circle_type::diameter( (value_type)1) );
    CHECK(c.GetRadius() == (value_type)0.5);
    CHECK( ( c.GetPosition() == point_type(0, 0) ) );

    CHECK(c.IsValid() == true);

    // constructor with diameter and position
    c = circle_type(circle_type::diameter( (value_type)4 ),
                    circle_type::position( point_type(2, 2) ) );
    CHECK( c.GetRadius() == (value_type)2 );
    CHECK( (c.GetPosition() == point_type(2, 2) ) );

    CHECK(c.IsValid() == true);
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
  }

  TEST_CASE("Math/types/Circle/GetCoord", "")
  {
    using tloc::math::utils::Pythagoras;

    circle_type c1(circle_type::radius(1.0f));

    {
      // Check against pythagoras
      Pythagoras pyth(math::Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      circle_type::point_type pFromC = c1.GetCoord(math::Degree(5.0f));

      // cos/sin accuracy is terrible
      CHECK(Mathf::Approx(pFromC[0], p[0], 0.01f));
      CHECK(Mathf::Approx(pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(math::Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      circle_type::point_type pFromC = c1.GetCoord(math::Degree(-5.0f));

      // cos/sin accuracy is terrible
      CHECK(Mathf::Approx(pFromC[0], p[0], 0.01f));
      CHECK(Mathf::Approx(-pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(math::Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::opposite>(),
                                pyth.GetSide<Pythagoras::base>() );
      circle_type::point_type pFromC = c1.GetCoord(math::Degree(85.0f));

      // cos/sin accuracy is terrible
      CHECK(Mathf::Approx(pFromC[0], p[0], 0.01f));
      CHECK(Mathf::Approx(pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(math::Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::opposite>(),
                                pyth.GetSide<Pythagoras::base>() );
      circle_type::point_type pFromC = c1.GetCoord(math::Degree(95.0f));

      // cos/sin accuracy is terrible
      CHECK(Mathf::Approx(-pFromC[0], p[0], 0.01f));
      CHECK(Mathf::Approx(pFromC[1], p[1], 0.01f));
    }

    {
      // Check against pythagoras
      Pythagoras pyth(math::Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      circle_type::point_type pFromC = c1.GetCoord(math::Degree(355.0f));

      // cos/sin accuracy is terrible
      CHECK(Mathf::Approx(pFromC[0], p[0], 0.01f));
      CHECK(Mathf::Approx(-pFromC[1], p[1], 0.01f));
    }

    circle_type c2(circle_type::radius(1.0f),
                   circle_type::position( math::Vec2f(1.0f, 1.0f) ));

    {
      // Check against pythagoras
      Pythagoras pyth(math::Degree(5.0f), Pythagoras::base(1.0f));

      circle_type::point_type p(pyth.GetSide<Pythagoras::base>(),
                                pyth.GetSide<Pythagoras::opposite>() );
      p += c2.GetPosition();
      circle_type::point_type pFromC = c2.GetCoord(math::Degree(5.0f));

      // cos/sin accuracy is terrible
      CHECK(Mathf::Approx(pFromC[0], p[0], 0.01f));
      CHECK(Mathf::Approx(pFromC[1], p[1], 0.01f));
    }


  }
};