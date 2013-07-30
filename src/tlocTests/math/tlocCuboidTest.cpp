#include "tlocTestCommon.h"

#include <tlocMath/types/tlocCuboid.h>

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/data_structures/tlocVariadic.inl.h>

namespace TestingCuboid
{
  using namespace tloc;
  using namespace tloc::math::types;

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

  TEST_CASE("Graphics/types/Cuboid/Size", "")
  {
    CHECK(sizeof(Cuboidf32) == sizeof(Cuboidf32::point_type) * 2);
    CHECK(sizeof(Cuboidf64) == sizeof(Cuboidf64::point_type) * 2);
  }

  TEST_CASE("Graphics/types/Cuboid", "")
  {
    TL_NESTED_FUNC_BEGIN(testBasics) void testBasics(Cuboidf& c)
    {
      CHECK(c.IsValid());
      CHECK(c.GetWidth() == Approx(2.0f));
      CHECK(c.GetHeight() == Approx(2.5f));
      CHECK(c.GetDepth() == Approx(3.0f));

      CHECK_VEC3F(c.GetPosition(), 0.0f, 0.25f, 0.5f);

      CHECK_VEC3F(c.GetCoord_TopLeftFront(), -1.0f, 1.5f, 2.0f);
      CHECK_VEC3F(c.GetCoord_TopRightFront(), 1.0f, 1.5f, 2.0f);
      CHECK_VEC3F(c.GetCoord_BottomLeftFront(), -1.0f, -1.0f, 2.0f);
      CHECK_VEC3F(c.GetCoord_BottomRightFront(), 1.0f, -1.0f, 2.0f);

      CHECK_VEC3F(c.GetCoord_TopLeftBack(), -1.0f, 1.5f, -1.0f);
      CHECK_VEC3F(c.GetCoord_TopRightBack(), 1.0f, 1.5f, -1.0f);
      CHECK_VEC3F(c.GetCoord_BottomLeftBack(), -1.0f, -1.0f, -1.0f);
      CHECK_VEC3F(c.GetCoord_BottomRightBack(), 1.0f, -1.0f, -1.0f);

      c.ResetPosition();

      CHECK_VEC3F(c.GetCoord_TopLeftFront(), -1.0f, 1.25f, 1.5f);
      CHECK_VEC3F(c.GetCoord_TopRightFront(), 1.0f, 1.25f, 1.5f);
      CHECK_VEC3F(c.GetCoord_BottomLeftFront(), -1.0f, -1.25f, 1.5f);
      CHECK_VEC3F(c.GetCoord_BottomRightFront(), 1.0f, -1.25f, 1.5f);

      CHECK_VEC3F(c.GetCoord_TopLeftBack(), -1.0f, 1.25f, -1.5f);
      CHECK_VEC3F(c.GetCoord_TopRightBack(), 1.0f, 1.25f, -1.5f);
      CHECK_VEC3F(c.GetCoord_BottomLeftBack(), -1.0f, -1.25f, -1.5f);
      CHECK_VEC3F(c.GetCoord_BottomRightBack(), 1.0f, -1.25f, -1.5f);

      c.Offset(Cuboidf::point_type(0.0f, 0.25f, 0.5f));

      CHECK_VEC3F(c.GetCoord_TopLeftFront(), -1.0f, 1.5f, 2.0f);
      CHECK_VEC3F(c.GetCoord_TopRightFront(), 1.0f, 1.5f, 2.0f);
      CHECK_VEC3F(c.GetCoord_BottomLeftFront(), -1.0f, -1.0f, 2.0f);
      CHECK_VEC3F(c.GetCoord_BottomRightFront(), 1.0f, -1.0f, 2.0f);

      CHECK_VEC3F(c.GetCoord_TopLeftBack(), -1.0f, 1.5f, -1.0f);
      CHECK_VEC3F(c.GetCoord_TopRightBack(), 1.0f, 1.5f, -1.0f);
      CHECK_VEC3F(c.GetCoord_BottomLeftBack(), -1.0f, -1.0f, -1.0f);
      CHECK_VEC3F(c.GetCoord_BottomRightBack(), 1.0f, -1.0f, -1.0f);
    }
    TL_NESTED_FUNC_END();

    SECTION("Basics", "")
    {
      Cuboidf c(Cuboidf::left(-1), Cuboidf::right(1),
                Cuboidf::top(1.5), Cuboidf::bottom(-1),
                Cuboidf::front(2), Cuboidf::back(-1));

      TL_NESTED_CALL(testBasics)(c);

      // same as above, this time with vector extents
      c = Cuboidf(Cuboidf::point_type(-1, -1, -1),
                  Cuboidf::point_type(1.0f, 1.5f, 2.0f));

      TL_NESTED_CALL(testBasics)(c);

      // same as above, this time with extents and position
      c = Cuboidf(Cuboidf::width(2.0f), Cuboidf::height(2.5f), Cuboidf::depth(3.0f));
      c.SetPosition(Cuboidf::point_type(0.0f, 0.25f, 0.5f));

      TL_NESTED_CALL(testBasics)(c);

      c = Cuboidf();
      CHECK_FALSE(c.IsValid());
    }

    SECTION("Contains", "")
    {
      Cuboidf c(Cuboidf::left(-1), Cuboidf::right(1),
                Cuboidf::top(1), Cuboidf::bottom(-1),
                Cuboidf::front(1), Cuboidf::back(-1));

      CHECK(c.Contains(Cuboidf::point_type(0, 0, 0)) );
      CHECK(c.Contains(Cuboidf::point_type(0.9f, 0.9f, -0.9f)) );
      CHECK(c.Contains(Cuboidf::point_type(1.0f, 0.9f, -0.9f)) );

      CHECK_FALSE(c.Contains(Cuboidf::point_type(1.1f, 0.9f, -0.9f)) );
      CHECK_FALSE(c.Contains(Cuboidf::point_type(0.9f, -1.1f, -0.9f)) );
      CHECK_FALSE(c.Contains(Cuboidf::point_type(0.9f, 0.9f, -1.1f)) );

      c.SetPosition(Cuboidf::point_type(0.6f, 0.6f, 0.6f));

      CHECK(c.Contains(Cuboidf::point_type(0, 0, 0)) );
      CHECK_FALSE(c.Contains(Cuboidf::point_type(0.9f, 0.9f, -0.9f)) );
      CHECK_FALSE(c.Contains(Cuboidf::point_type(1.0f, 0.9f, -0.9f)) );

      CHECK(c.Contains(Cuboidf::point_type(1.1f, 0.9f, 0.0f)) );
      CHECK_FALSE(c.Contains(Cuboidf::point_type(0.9f, -1.1f, 0.0f)) );
      CHECK(c.Contains(Cuboidf::point_type(0.9f, 0.9f, 1.1f)) );
    }

    SECTION("Intersects this_type", "")
    {
      Cuboidf c1(Cuboidf::left(-0.5f), Cuboidf::right(0.5f),
                 Cuboidf::top(0.5f), Cuboidf::bottom(-0.5f),
                 Cuboidf::front(0.5f), Cuboidf::back(-0.5f));

      Cuboidf c2(Cuboidf::left(-0.5f), Cuboidf::right(0.5f),
                 Cuboidf::top(0.5f), Cuboidf::bottom(-0.5f),
                 Cuboidf::front(0.5f), Cuboidf::back(-0.5f));

      CHECK(c1.Intersects(c2));

      Cuboidf intersect;
      CHECK(c1.Intersects(c2, intersect));
      CHECK(c1 == intersect);

      c2.SetPosition(Cuboidf::point_type(1.0f, 1.0f, 1.0f));
      CHECK_FALSE(c1.Intersects(c2));

      c2.SetPosition(Cuboidf::point_type(0.9f, 0.9f, 0.9f));
      CHECK(c1.Intersects(c2, intersect));
      CHECK(intersect.GetWidth() == Approx(0.1f));
      CHECK(intersect.GetHeight() == Approx(0.1f));
      CHECK(intersect.GetDepth() == Approx(0.1f));
    }

    SECTION("Intersects ray3d", "")
    {
      Cuboidf c(Cuboidf::left(-1), Cuboidf::right(1),
                Cuboidf::top(1), Cuboidf::bottom(-1),
                Cuboidf::front(1), Cuboidf::back(-1));

      Ray3f ray(Ray3f::origin(Vec3f(0, 0, 5)),
                Ray3f::direction(Vec3f(0, 0, -1)) );
      CHECK(c.Intersects(ray));

      Vec3f dir(0, -1, -1);
      dir.Normalize();
      ray = Ray3f(Ray3f::origin(Vec3f(0, 0, 5)),
                  Ray3f::direction(dir) );

      dir = Vec3f(0, -0.3f, -1.0f);
      dir.Normalize();

      ray = Ray3f(Ray3f::origin(Vec3f(0, 0, 5)),
                  Ray3f::direction(dir) );

      CHECK_FALSE(c.Intersects(ray));

      dir = Vec3f(0, -0.1f, -1.0f);
      dir.Normalize();

      ray = Ray3f(Ray3f::origin(Vec3f(0, 0, 5)),
                  Ray3f::direction(dir) );

      CHECK(c.Intersects(ray));
    }
  }
};