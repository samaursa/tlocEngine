#include "tlocTestCommon.h"

#include <tlocMath/types/tlocRectangle.h>

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/data_structures/tlocVariadic.inl.h>

#define CHECK_TUP(_pos1_, _pos2_) \
  CHECK(_pos1_[0] == Approx(_pos2_[0]));\
  CHECK(_pos1_[1] == Approx(_pos2_[1]))

namespace TestingRectangle
{
  using namespace tloc;
  using namespace tloc::math::types;

  using core_ds::MakeTuple;

  TEST_CASE("Graphics/types/Rectangle/Size", "")
  {
    CHECK(sizeof(Rectf32_bl) == sizeof(Rectf32_bl::point_type)*2 );
    CHECK(sizeof(Rectf64_bl) == sizeof(Rectf64_bl::point_type)*2 );
    
    CHECK(sizeof(Rectf32_c) == sizeof(Rectf32_c::point_type)*2 );
    CHECK(sizeof(Rectf64_c) == sizeof(Rectf64_c::point_type)*2 );
  }

  TEST_CASE("Graphics/types/Rectangle", "")
  {
    SECTION("Rectangle bottom left position left/right/top/bottom ctor", "")
    {
      typedef Rectf32_bl                        Rectf;

      Rectf r = Rectf( Rectf::left( -1 ), Rectf::right( 0 ),
                       Rectf::top( 0 ), Rectf::bottom( -1 ) );
      CHECK( r.IsValid() );
      CHECK( r.GetWidth() == Approx(1) );
      CHECK( r.GetHeight() == Approx(1) );
      CHECK( r.GetWidth() == Approx(1) );
      CHECK( r.GetHeight() == Approx(1) );
      CHECK( r.GetArea() == Approx(1) );

      CHECK_TUP( r.GetCenter(), Vec2f( -0.5f, -0.5f ) );
      CHECK_TUP( r.GetPosition(), Vec2f( -1.0f, -1.0f ) );

      r.SetWidth( 0.5f );
      r.SetHeight( 5.0f );
      CHECK( r.GetArea() == Approx(2.5f) );
      CHECK_TUP( r.GetCenter(), Vec2f( -0.75f, 1.5f ) );
      CHECK_TUP( r.GetPosition(), Vec2f( -1.0f, -1.0f ) );

      CHECK( r.GetWidth() == 0.5f );
      CHECK( r.GetHeight() == 5.0f );
      CHECK( r.GetValue<Rectf::left>() == Approx( -1.0f ) );
      CHECK( r.GetValue<Rectf::right>() == Approx( -0.5f ) );
      CHECK( r.GetValue<Rectf::top>() == Approx( 4.0f ) );
      CHECK( r.GetValue<Rectf::bottom>() == Approx( -1.0f ) );

      r = Rectf();
      CHECK( r.GetValue<Rectf::left>() == Approx(0) );
      CHECK( r.GetValue<Rectf::right>() == Approx(0) );
      CHECK( r.GetValue<Rectf::top>() == Approx(0) );
      CHECK( r.GetValue<Rectf::bottom>() == Approx(0) );
      CHECK( r.GetArea() == Approx(0) );

      CHECK_FALSE( r.IsValid() );
      CHECK( r.GetWidth() == Approx(0) );
      CHECK( r.GetHeight() == Approx(0) );

      Rectf::point_type center;
      center[0] = 0;
      center[1] = 0;
      CHECK( ( r.GetCenter() == center ) );

      r = Rectf( Rectf::left( 0 ), Rectf::right( 2 ), Rectf::top( 5 ), Rectf::bottom( 0 ) );
      CHECK( r.GetValue<Rectf::left>() == 0 );
      CHECK( r.GetValue<Rectf::right>() == 2 );
      CHECK( r.GetValue<Rectf::top>() == 5 );
      CHECK( r.GetValue<Rectf::bottom>() == 0 );
      CHECK( r.GetWidth() == 2 );
      CHECK( r.GetHeight() == 5 );

      Rectf rCopy( r );
      CHECK( r.GetValue<Rectf::left>() == 0 );
      CHECK( r.GetValue<Rectf::right>() == 2 );
      CHECK( r.GetValue<Rectf::top>() == 5 );
      CHECK( r.GetValue<Rectf::bottom>() == 0 );

      center[0] = 1.0f;
      center[1] = 2.5f;
      CHECK( ( r.GetCenter() == center ) );

      CHECK( r.IsValid() == true );

      r = Rectf( Rectf::left( 0 ), Rectf::right( 5 ), Rectf::top( 2 ), Rectf::bottom( 0 ) );
      r.MakeOffset( Vec2f( 2, 2 ) );
      CHECK( r.GetValue<Rectf::left>() == 2 );
      CHECK( r.GetValue<Rectf::right>() == 7 );
      CHECK( r.GetValue<Rectf::top>() == 4 );
      CHECK( r.GetValue<Rectf::bottom>() == 2 );
      CHECK( r.IsValid() == true );
      CHECK( r.GetWidth() == 5 );
      CHECK( r.GetHeight() == 2 );

      center[0] = 4.5f;
      center[1] = 3.0f;
      CHECK( ( r.GetCenter() == center ) );

      r = Rectf( Rectf::left( 0 ), Rectf::right( 2 ), Rectf::top( 5 ), Rectf::bottom( 0 ) );
      CHECK( r.Contains( Vec2f( 1, 1 ) ) );
      CHECK( r.Contains( Vec2f( 0, 0 ) ) );
      CHECK( r.Contains( Vec2f( 2, 2 ) ) );

      CHECK_FALSE( r.Contains( Vec2f( 3, 2 ) ) );
      CHECK_FALSE( r.Contains( Vec2f( 1, 6 ) ) );
      CHECK_FALSE( r.Contains( Vec2f( -1, 2 ) ) );
      CHECK_FALSE( r.Contains( Vec2f( 1, -1 ) ) );

      r = Rectf( Rectf::width( 1 ), Rectf::height( 2 ) );
      CHECK( r.GetWidth() == Approx( 1 ) );
      CHECK( r.GetHeight() == Approx( 2 ) );

      center[0] = 0.5f;
      center[1] = 1.0f;
      CHECK( ( r.GetCenter() == center ) );

      // assignment operator and swap
      Rectf s = Rectf( Rectf::width( 5 ), Rectf::height( 10 ) );
      s.SetPosition( MakeTuple( 5.0f, 9.0f ) );
      r = s;
      CHECK( r.GetWidth() == Approx( 5 ) );
      CHECK( r.GetHeight() == Approx( 10 ) );
      CHECK( r.GetCenter() == MakeTuple( 7.5f, 14.0f ) );

      s = Rectf( Rectf::width( 2 ), Rectf::height( 3 ) );
      s.SetPosition( MakeTuple( 1.0f, 8.0f ) );
      core::swap( s, r );

      CHECK( s.GetPosition() == Vec2f( 5, 9 ) );
      CHECK( s.GetWidth() == Approx( 5 ) );
      CHECK( s.GetHeight() == Approx( 10 ) );

      CHECK( s.GetCenter() == MakeTuple( 7.5f, 14.0f ) );

      CHECK( r.GetWidth() == Approx( 2 ) );
      CHECK( r.GetHeight() == Approx( 3 ) );
      CHECK( r.GetCenter() == MakeTuple( 2.0f, 9.5f ) );

      core::swap( s, r );

      CHECK( r.GetWidth() == Approx( 5 ) );
      CHECK( r.GetHeight() == Approx( 10 ) );
      CHECK( r.GetCenter() == MakeTuple( 7.5f, 14.0f ) );

      CHECK( s.GetWidth() == Approx( 2 ) );
      CHECK( s.GetHeight() == Approx( 3 ) );
      CHECK( s.GetCenter() == MakeTuple( 2.0f, 9.5f ) );

      // different types
      Rectf32_bl r32;
      Rectf64_bl r64( r32 );
    }

    SECTION("Rectangle center position", "")
    {
      typedef Rectf32_c                        Rectf;

      Rectf r = Rectf( Rectf::left( -1 ), Rectf::right( 0 ),
                       Rectf::top( 0 ), Rectf::bottom( -1 ) );
      CHECK( r.IsValid() );
      CHECK( r.GetWidth() == Approx(1) );
      CHECK( r.GetHeight() == Approx(1) );
      CHECK( r.GetWidth() == Approx(1) );
      CHECK( r.GetHeight() == Approx(1) );

      CHECK_TUP( r.GetCenter(), Vec2f( -0.5f, -0.5f ) );
      CHECK_TUP( r.GetPosition(), Vec2f( -0.5f, -0.5f ) );

      r.SetWidth( 0.5f );
      r.SetHeight( 5.0f );
      CHECK_TUP( r.GetCenter(), Vec2f( -0.5f, -0.5f ) );
      CHECK_TUP( r.GetPosition(), Vec2f( -0.5f, -0.5f ) );

      CHECK( r.GetWidth() == 0.5f );
      CHECK( r.GetHeight() == 5.0f );
      CHECK( r.GetValue<Rectf::left>() == Approx( -0.75f ) );
      CHECK( r.GetValue<Rectf::right>() == Approx( -0.25f ) );
      CHECK( r.GetValue<Rectf::top>() == Approx( 2.0f ) );
      CHECK( r.GetValue<Rectf::bottom>() == Approx( -3.0f ) );

      r = Rectf();
      CHECK( r.GetValue<Rectf::left>() == 0 );
      CHECK( r.GetValue<Rectf::right>() == 0 );
      CHECK( r.GetValue<Rectf::top>() == 0 );
      CHECK( r.GetValue<Rectf::bottom>() == 0 );

      CHECK_FALSE( r.IsValid() );
      CHECK( r.GetWidth() == Approx(0) );
      CHECK( r.GetHeight() == Approx(0) );

      Rectf::point_type center;
      center[0] = 0;
      center[1] = 0;
      CHECK( ( r.GetCenter() == center ) );

      r = Rectf( Rectf::left( 0 ), Rectf::right( 2 ), Rectf::top( 5 ), Rectf::bottom( 0 ) );
      CHECK( r.GetValue<Rectf::left>() == 0 );
      CHECK( r.GetValue<Rectf::right>() == 2 );
      CHECK( r.GetValue<Rectf::top>() == 5 );
      CHECK( r.GetValue<Rectf::bottom>() == 0 );
      CHECK( r.GetWidth() == 2 );
      CHECK( r.GetHeight() == 5 );

      Rectf rCopy( r );
      CHECK( r.GetValue<Rectf::left>() == 0 );
      CHECK( r.GetValue<Rectf::right>() == 2 );
      CHECK( r.GetValue<Rectf::top>() == 5 );
      CHECK( r.GetValue<Rectf::bottom>() == 0 );

      center[0] = 1.0f;
      center[1] = 2.5f;
      CHECK( ( r.GetCenter() == center ) );

      CHECK( r.IsValid() == true );

      r = Rectf( Rectf::left( 0 ), Rectf::right( 5 ), Rectf::top( 2 ), Rectf::bottom( 0 ) );
      r.MakeOffset( Vec2f( 2, 2 ) );
      CHECK( r.GetValue<Rectf::left>() == 2 );
      CHECK( r.GetValue<Rectf::right>() == 7 );
      CHECK( r.GetValue<Rectf::top>() == 4 );
      CHECK( r.GetValue<Rectf::bottom>() == 2 );
      CHECK( r.IsValid() == true );
      CHECK( r.GetWidth() == 5 );
      CHECK( r.GetHeight() == 2 );

      center[0] = 4.5f;
      center[1] = 3.0f;
      CHECK( ( r.GetCenter() == center ) );

      r = Rectf( Rectf::left(0), Rectf::right(2), Rectf::top(5), Rectf::bottom(0) );
      CHECK( r.Contains( Vec2f(1, 1) ) );
      CHECK( r.Contains( Vec2f(0, 0) ) );
      CHECK( r.Contains( Vec2f(2, 2) ) );

      CHECK_FALSE( r.Contains( Vec2f(3, 2) ) );
      CHECK_FALSE( r.Contains( Vec2f(1, 6) ) );
      CHECK_FALSE( r.Contains( Vec2f(-1, 2) ) );
      CHECK_FALSE( r.Contains( Vec2f(1, -1) ) );

      r = Rectf( Rectf::left(0), Rectf::right(2), Rectf::top(5), Rectf::bottom(0) );
      {
        Rectf inter( Rectf::left(1), Rectf::right(2), Rectf::top(4), Rectf::bottom(1) );
        CHECK( r.Intersects(inter) );

        Rectf interRet;
        CHECK( r.Intersects(inter, interRet) );
      }

      {
        Rectf inter( Rectf::left(-1), Rectf::right(0), Rectf::top(0), Rectf::bottom(-1) );
        CHECK_FALSE( r.Intersects(inter) );
      }

      r = Rectf( Rectf::width( 1 ), Rectf::height( 2 ) );
      CHECK( r.GetWidth() == Approx( 1 ) );
      CHECK( r.GetHeight() == Approx( 2 ) );

      center[0] = 0.0f;
      center[1] = 0.0f;
      CHECK_TUP( r.GetCenter(), center );

      // assignment operator and swap
      Rectf s = Rectf( Rectf::width( 5 ), Rectf::height( 10 ) );
      s.SetPosition( MakeTuple(5.0f, 9.0f) );
      r = s;
      CHECK( r.GetWidth() == Approx( 5 ) );
      CHECK( r.GetHeight() == Approx( 10 ) );
      CHECK_TUP( r.GetCenter(), MakeTuple( 5.0f, 9.0f ) );

      s = Rectf( Rectf::width( 2 ), Rectf::height( 3 ) );
      s.SetPosition( MakeTuple( 1.0f, 8.0f) );
      core::swap( s, r );

      CHECK_TUP( s.GetPosition(), Vec2f( 5, 9 ) );
      CHECK( s.GetWidth() == Approx( 5 ) );
      CHECK( s.GetHeight() == Approx( 10 ) );

      CHECK_TUP( s.GetCenter(), MakeTuple( 5.0f, 9.0f ) );

      CHECK( r.GetWidth() == Approx( 2 ) );
      CHECK( r.GetHeight() == Approx( 3 ) );
      CHECK_TUP( r.GetCenter(), MakeTuple( 1.0f, 8.0f ) );

      core::swap( s, r );

      CHECK( r.GetWidth() == Approx( 5 ) );
      CHECK( r.GetHeight() == Approx( 10 ) );
      CHECK_TUP( r.GetCenter(), MakeTuple( 5.0f, 9.0f ) );

      CHECK( s.GetWidth() == Approx( 2 ) );
      CHECK( s.GetHeight() == Approx( 3 ) );
      CHECK_TUP( s.GetCenter(), MakeTuple( 1.0f, 8.0f ) );

      // different types
      Rectf32_c r32;
      Rectf64_c r64( r32 );
    }
  }

  template <typename T_RectangleType>
  void TestFits()
  {
    typedef T_RectangleType                           rect_type;
    typedef typename rect_type::point_type            point_type;
    typedef typename point_type::value_type           vt;

    rect_type r = rect_type(rect_type::left(0), rect_type::right(4),
                            rect_type::top(5), rect_type::bottom(0));

    rect_type r2 = rect_type(rect_type::left(-1), rect_type::right(2),
                             rect_type::top(4), rect_type::bottom(1));

    rect_type r3 = rect_type(rect_type::left(1), rect_type::right(2),
                             rect_type::top(6), rect_type::bottom(3));

    rect_type r4 = rect_type(rect_type::left(1), rect_type::right(2),
                             rect_type::top(4), rect_type::bottom(1));

    rect_type r5 = rect_type(rect_type::left(0), rect_type::right(5),
                             rect_type::top(5), rect_type::bottom(0));

    rect_type r6 = rect_type(rect_type::left(0), rect_type::right(4),
                             rect_type::top(5), rect_type::bottom(-1));

    CHECK(r.Fits(r));
    CHECK(r.Fits(r2));
    CHECK(r.Fits(r3));
    CHECK(r.Fits(r4));
    CHECK_FALSE(r.Fits(r5));
    CHECK_FALSE(r.Fits(r6));
  }

  TEST_CASE("Graphics/types/Rectangle/Fits", "Other rectangles")
  {
    TestFits<Rects32_bl>();
    TestFits<Rectf32_c>();
    TestFits<Rectf32_bl>();
  }

  template <typename T_RectangleType>
  void TestContains()
  {
    typedef T_RectangleType                           rect_type;
    typedef typename rect_type::point_type            point_type;
    typedef typename point_type::value_type           vt;

    rect_type r = rect_type(rect_type::left(0), rect_type::right(4),
                            rect_type::top(5), rect_type::bottom(0));

    rect_type r2 = rect_type(rect_type::left(-1), rect_type::right(2),
                             rect_type::top(4), rect_type::bottom(1));

    rect_type r3 = rect_type(rect_type::left(1), rect_type::right(2),
                             rect_type::top(6), rect_type::bottom(3));

    rect_type r4 = rect_type(rect_type::left(1), rect_type::right(2),
                             rect_type::top(4), rect_type::bottom(1));

    rect_type r5(r);

    CHECK_FALSE(r.Contains(r2));
    CHECK_FALSE(r.Contains(r3));
    CHECK(r.Contains(r4));
    CHECK(r.Contains(r5));

    r4.MakeOffset(point_type( core_ds::MakeTuple(vt(-2), vt(-2)) ));
    r5.MakeOffset(point_type( core_ds::MakeTuple(vt(-1), vt(0)) ));
    CHECK_FALSE(r.Contains(r4));
    CHECK_FALSE(r.Contains(r5));

    r5.MakeOffset(point_type( core_ds::MakeTuple(vt(1), vt(0)) ));
    CHECK(r.Contains(r5));

    r5.MakeOffset(point_type( core_ds::MakeTuple(vt(0), vt(1)) ));
    CHECK_FALSE(r.Contains(r5));
  }

  TEST_CASE("Graphics/types/Rectangle/Contains", "Other rectangles")
  {
    TestContains<Rects32_bl>();
    TestContains<Rectf32_c>();
    TestContains<Rectf32_bl>();
  }

  template <typename T_RectangleType>
  void TestFlipCenter()
  {
    typedef T_RectangleType                          rect_type;

    rect_type r = rect_type(rect_type::left(0), rect_type::right(4),
                            rect_type::top(6), rect_type::bottom(0));
    r.MakeFlip();

    CHECK_TUP(r.GetCoord_TopLeft(), MakeTuple(-1, 5));
    CHECK_TUP(r.GetCoord_TopRight(), MakeTuple(5, 5));
    CHECK_TUP(r.GetCoord_BottomRight(), MakeTuple(5, 1));
    CHECK_TUP(r.GetCoord_BottomLeft(), MakeTuple(-1, 1));
  }

  template <typename T_RectangleType>
  void TestFlipBottomLeft()
  {
    typedef T_RectangleType                          rect_type;

    rect_type r = rect_type(rect_type::left(0), rect_type::right(4),
                            rect_type::top(5), rect_type::bottom(0));
    r.MakeFlip();

    CHECK_TUP(r.GetCoord_TopLeft(), MakeTuple(0, 4));
    CHECK_TUP(r.GetCoord_TopRight(), MakeTuple(5, 4));
    CHECK_TUP(r.GetCoord_BottomRight(), MakeTuple(5, 0));
    CHECK_TUP(r.GetCoord_BottomLeft(), MakeTuple(0, 0));
  }

  TEST_CASE("Graphics/types/Rectangle/Flip", "Other rectangles")
  {
    SECTION("Rectangle int, center position", "")
    {
      TestFlipCenter<Rectf_c>();
      TestFlipCenter<Rects_c>();
    }

    SECTION("Rectangle int, center position", "")
    {
      TestFlipBottomLeft<Rectf_bl>();
      TestFlipBottomLeft<Rects_bl>();
    }
  }

  template <typename T_RectangleType>
  void TestIntersection()
  {
    typedef T_RectangleType                        Rectf;

    Rectf r = Rectf(Rectf::left(0), Rectf::right(2),
                    Rectf::top(5), Rectf::bottom(0));
    {
      Rectf inter(Rectf::left(1), Rectf::right(2),
                  Rectf::top(4), Rectf::bottom(1));
      CHECK(r.Intersects(inter));

      Rectf interRet;
      CHECK(r.Intersects(inter, interRet));
    }

    {
      Rectf inter(Rectf::left(-1), Rectf::right(0),
                  Rectf::top(0), Rectf::bottom(-1));
      CHECK_FALSE(r.Intersects(inter));
    }
  }

  TEST_CASE("Graphics/types/Rectangle/Intersects", "With other rectangles")
  {
    TestIntersection<Rects32_bl>();
    TestIntersection<Rectf32_c>();
    TestIntersection<Rectf32_bl>();
  }

  TEST_CASE("Graphics/types/Rectangle/GetCoord", "")
  {
    typedef Rectf_c Rectf;

    Rectf r = Rectf(Rectf::width(1), Rectf::height(2));
    CHECK_TUP(( r.GetCoord<Rectf::top, Rectf::left>() ), Vec2f(-0.5f, 1.0f));
    CHECK_TUP(( r.GetCoord<Rectf::top, Rectf::right>() ), Vec2f(0.5f, 1.0f));
    CHECK_TUP(( r.GetCoord<Rectf::bottom, Rectf::left>() ), Vec2f(-0.5f, -1.0f));
    CHECK_TUP(( r.GetCoord<Rectf::bottom, Rectf::right>() ), Vec2f(0.5f, -1.0f));

    CHECK_TUP(( r.GetCoord_TopLeft() ), Vec2f(-0.5f, 1.0f));
    CHECK_TUP(( r.GetCoord_TopRight() ), Vec2f(0.5f, 1.0f));
    CHECK_TUP(( r.GetCoord_BottomLeft() ), Vec2f(-0.5f, -1.0f));
    CHECK_TUP(( r.GetCoord_BottomRight() ), Vec2f(0.5f, -1.0f));
  }

  TEST_CASE("Graphics/types/Rectangle/RayIntersection_2d", "")
  {
    typedef Rectf_c  Rectf;

    // NOTE: Rectangle origin is at its center
    Rectf r = Rectf(Rectf::width(1), Rectf::height(2));
    Ray2f ray(Ray2f::origin(Vec2f(0, 0)) );
    CHECK(r.Intersects(ray));

    r.SetPosition(Vec2f(3, 2));
    CHECK_FALSE(r.Intersects(ray));

    ray = Ray2f(Ray2f::origin(Vec2f(2.5, 1.0f)) );
    CHECK(r.Intersects(ray));
    r.SetPosition(Vec2f(3.1f, 2.0f));
    CHECK_FALSE(r.Intersects(ray));
    r.SetPosition(Vec2f(3.0f, 3.0f));
    CHECK_FALSE(r.Intersects(ray));
  }

  TEST_CASE("Graphics/types/Rectangle/RayIntersection_3d", "")
  {
    typedef Rectf_c  Rectf;

    Rectf r = Rectf(Rectf::width(1), Rectf::height(2));

    math_t::Vec3f dir(0, 0, -1.0f);

    Ray3f ray(Ray3f::origin(Vec3f(0, 0, 5.0f)),
              Ray3f::direction(dir) );
    CHECK(r.Intersects(ray).first);
    CHECK(r.Intersects(ray).second[0] == Approx(0.0f));
    CHECK(r.Intersects(ray).second[1] == Approx(0.0f));
    CHECK(r.Intersects(ray).second[2] == Approx(0.0f));

    dir = Vec3f(0, 1.0f, -1.0f);
    dir.Normalize();
    ray = Ray3f( Ray3f::origin(Vec3f(0, 0, 5.0f)),
                 Ray3f::direction(dir) );
    CHECK_FALSE(r.Intersects(ray).first);
    CHECK(r.Intersects(ray).second[0] == Approx(0.0f));
    CHECK(r.Intersects(ray).second[1] == Approx(5.0f));
    CHECK(r.Intersects(ray).second[2] == Approx(0.0f));

    dir = Vec3f(0, 0.1f, -1.0f);
    dir.Normalize();
    ray = Ray3f( Ray3f::origin(Vec3f(0, 0, 5.0f)),
                 Ray3f::direction(dir) );
    CHECK(r.Intersects(ray).first);
    CHECK(r.Intersects(ray).second[0] == Approx(0.0f));
    CHECK(r.Intersects(ray).second[1] == Approx(0.5f));
    CHECK(r.Intersects(ray).second[2] == Approx(0.0f));

    dir = Vec3f(0, 0.1f, -1.0f);
    dir.Normalize();
    ray = Ray3f( Ray3f::origin(Vec3f(0, 0, -5.0f)),
                 Ray3f::direction(dir) );
    CHECK_FALSE(r.Intersects(ray).first);
    CHECK(r.Intersects(ray, Rectf::from_origin(false)).first);

    dir = Vec3f(0, 0.1f, 1.0f);
    dir.Normalize();
    ray = Ray3f( Ray3f::origin(Vec3f(0, 0, -5.0f)),
                 Ray3f::direction(dir) );
    CHECK_FALSE(r.Intersects(ray).first);
    CHECK_FALSE(r.Intersects(ray, Rectf::from_origin(false)).first);
    CHECK(r.Intersects(ray,
                       Rectf::from_origin(false),
                       Rectf::double_sided(true)).first);
  }

  TEST_CASE("Graphics/types/Rectangle/algos", "")
  {
    typedef Rectf_c  Rectf;

    Rectf r1 = Rectf(Rectf::width(5.0f), Rectf::height(10.0f));
    Rectf r2 = Rectf(Rectf::width(4.0f), Rectf::height(15.0f));

    using namespace math_t::algos::rectangle;

    SECTION("compare/Width", "")
    {
      CHECK(compare::MakeWidth(r1, compare::Equal())(r1));
      CHECK(compare::MakeWidth(r1, compare::GreaterEqual())(r1));
      CHECK(compare::MakeWidth(r1, compare::LessEqual())(r1));

      CHECK_FALSE(compare::MakeWidth(r1, compare::Equal())(r2));
      CHECK_FALSE(compare::MakeWidth(r1, compare::Less())(r2));
      CHECK(compare::MakeWidth(r1, compare::Greater())(r2));
      CHECK_FALSE(compare::MakeWidth(r1, compare::LessEqual())(r2));
      CHECK(compare::MakeWidth(r1, compare::GreaterEqual())(r2));
    }

    SECTION("compare/Height", "")
    {
      CHECK(compare::MakeHeight(r1, compare::Equal())(r1));
      CHECK(compare::MakeHeight(r1, compare::GreaterEqual())(r1));
      CHECK(compare::MakeHeight(r1, compare::LessEqual())(r1));

      CHECK_FALSE(compare::MakeHeight(r1, compare::Equal())(r2));
      CHECK(compare::MakeHeight(r1, compare::Less())(r2));
      CHECK_FALSE(compare::MakeHeight(r1, compare::Greater())(r2));
      CHECK(compare::MakeHeight(r1, compare::LessEqual())(r2));
      CHECK_FALSE(compare::MakeHeight(r1, compare::GreaterEqual())(r2));
    }

    SECTION("compare/Area", "")
    {
      CHECK(compare::MakeArea(r1, compare::Equal())(r1));
      CHECK(compare::MakeArea(r1, compare::GreaterEqual())(r1));
      CHECK(compare::MakeArea(r1, compare::LessEqual())(r1));

      CHECK_FALSE(compare::MakeArea(r1, compare::Equal())(r2));
      CHECK(compare::MakeArea(r1, compare::Less())(r2));
      CHECK_FALSE(compare::MakeArea(r1, compare::Greater())(r2));
      CHECK(compare::MakeArea(r1, compare::LessEqual())(r2));
      CHECK_FALSE(compare::MakeArea(r1, compare::GreaterEqual())(r2));
    }
  }
};