#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocContainerUtils.h>

namespace TestingContainerUtilsTest
{
  using namespace tloc;
  using namespace core_utils;

  TEST_CASE("core/containers/ContainerUtils", "")
  {
    SECTION("ArraySize", "")
    {
      tl_int            a1[10];
      const tl_float    f1[22] = {0};
      const tl_double   d1[1] = {0};

      CHECK(ArraySize(a1) == 10);
      CHECK(ArraySize(f1) == 22);
      CHECK(ArraySize(d1) == 1);
    }

    SECTION("Index2D", "")
    {
      CHECK( (Index2D<10, 10, 0, 0>::k_value == 0) );
      CHECK( (Index2D<10, 10, 1, 0>::k_value == 1) );
      CHECK( (Index2D<10, 10, 9, 0>::k_value == 9) );
      CHECK( (Index2D<10, 10, 0, 1>::k_value == 10) );

      CHECK( (Index2D<10, 5, 0, 0>::k_value == 0) );
      CHECK( (Index2D<10, 5, 1, 0>::k_value == 1) );
      CHECK( (Index2D<10, 5, 9, 0>::k_value == 9) );
      CHECK( (Index2D<10, 5, 0, 1>::k_value == 10) );

      CHECK( (Index2D<5, 10, 0, 0>::k_value == 0) );
      CHECK( (Index2D<5, 10, 1, 0>::k_value == 1) );
      CHECK( (Index2D<5, 10, 4, 0>::k_value == 4) );
      CHECK( (Index2D<5, 10, 0, 1>::k_value == 5) );
    }

    SECTION("Index2D Compile and Runtime", "")
    {
      CHECK( (Index2D<10, 10>::Get(0, 0) == 0) );
      CHECK( (Index2D<10, 10>::Get(1, 0) == 1) );
      CHECK( (Index2D<10, 10>::Get(9, 0) == 9) );
      CHECK( (Index2D<10, 10>::Get(0, 1) == 10) );

      CHECK( (Index2D<10, 5>::Get(0, 0) == 0) );
      CHECK( (Index2D<10, 5>::Get(1, 0) == 1) );
      CHECK( (Index2D<10, 5>::Get(9, 0) == 9) );
      CHECK( (Index2D<10, 5>::Get(0, 1) == 10) );

      CHECK( (Index2D<5, 10>::Get(0, 0) == 0) );
      CHECK( (Index2D<5, 10>::Get(1, 0) == 1) );
      CHECK( (Index2D<5, 10>::Get(4, 0) == 4) );
      CHECK( (Index2D<5, 10>::Get(0, 1) == 5) );
    }

    SECTION("Index2D Runtime", "")
    {
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10),
                       core_ds::MakeTuple(0, 0)) == 0) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10),
        							 core_ds::MakeTuple(1, 0)) == 1) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10),
        							 core_ds::MakeTuple(9, 0)) == 9) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10),
        							 core_ds::MakeTuple(0, 1)) == 10) );

      CHECK( (GetIndex(core_ds::MakeTuple(10, 5),
        							 core_ds::MakeTuple(0, 0)) == 0) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 5),
        							 core_ds::MakeTuple(1, 0)) == 1) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 5),
        							 core_ds::MakeTuple(9, 0)) == 9) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 5),
        							 core_ds::MakeTuple(0, 1)) == 10) );

      CHECK( (GetIndex(core_ds::MakeTuple(5, 10),
        							 core_ds::MakeTuple(0, 0)) == 0) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10),
        							 core_ds::MakeTuple(1, 0)) == 1) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10),
        							 core_ds::MakeTuple(4, 0)) == 4) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10),
        							 core_ds::MakeTuple(0, 1)) == 5) );
    }

    SECTION("Index3D", "")
    {
      CHECK( (Index3D<10, 10, 10, 0, 0, 0>::k_value == 0) );
      CHECK( (Index3D<10, 10, 10, 1, 0, 0>::k_value == 1) );
      CHECK( (Index3D<10, 10, 10, 9, 0, 0>::k_value == 9) );
      CHECK( (Index3D<10, 10, 10, 0, 1, 0>::k_value == 10) );
      CHECK( (Index3D<10, 10, 10, 0, 0, 1>::k_value == 100) );

      CHECK( (Index3D<5, 10, 10, 0, 0, 0>::k_value == 0) );
      CHECK( (Index3D<5, 10, 10, 1, 0, 0>::k_value == 1) );
      CHECK( (Index3D<5, 10, 10, 4, 0, 0>::k_value == 4) );
      CHECK( (Index3D<5, 10, 10, 0, 1, 0>::k_value == 5) );
      CHECK( (Index3D<5, 10, 10, 0, 0, 1>::k_value == 50) );
    }

    SECTION("Index3D Compile and Runtime", "")
    {
      CHECK( (Index3D<10, 10, 10>::Get(0, 0, 0) == 0) );
      CHECK( (Index3D<10, 10, 10>::Get(1, 0, 0) == 1) );
      CHECK( (Index3D<10, 10, 10>::Get(9, 0, 0) == 9) );
      CHECK( (Index3D<10, 10, 10>::Get(0, 1, 0) == 10) );
      CHECK( (Index3D<10, 10, 10>::Get(0, 0, 1) == 100) );

      CHECK( (Index3D<5, 10, 10>::Get(0, 0, 0) == 0) );
      CHECK( (Index3D<5, 10, 10>::Get(1, 0, 0) == 1) );
      CHECK( (Index3D<5, 10, 10>::Get(4, 0, 0) == 4) );
      CHECK( (Index3D<5, 10, 10>::Get(0, 1, 0) == 5) );
      CHECK( (Index3D<5, 10, 10>::Get(0, 0, 1) == 50) );
    }

    SECTION("Index3D Runtime", "")
    {
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10, 10),
                       core_ds::MakeTuple(0, 0, 0)) == 0) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10, 10),
        							 core_ds::MakeTuple(1, 0, 0)) == 1) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10, 10),
        							 core_ds::MakeTuple(9, 0, 0)) == 9) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10, 10),
        							 core_ds::MakeTuple(0, 1, 0)) == 10) );
      CHECK( (GetIndex(core_ds::MakeTuple(10, 10, 10),
        							 core_ds::MakeTuple(0, 0, 1)) == 100) );

      CHECK( (GetIndex(core_ds::MakeTuple(5, 10, 10),
        							 core_ds::MakeTuple(0, 0, 0)) == 0) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10, 10),
        							 core_ds::MakeTuple(1, 0, 0)) == 1) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10, 10),
        							 core_ds::MakeTuple(4, 0, 0)) == 4) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10, 10),
        							 core_ds::MakeTuple(0, 1, 0)) == 5) );
      CHECK( (GetIndex(core_ds::MakeTuple(5, 10, 10),
        							 core_ds::MakeTuple(0, 0, 1)) == 50) );
    }

    SECTION("Coord2D", "")
    {
      CHECK( (Coord2D<10, 10, 0>::k_x == 0) );
      CHECK( (Coord2D<10, 10, 0>::k_y == 0) );

      CHECK( (Coord2D<10, 10, 1>::k_x == 1) );
      CHECK( (Coord2D<10, 10, 1>::k_y == 0) );

      CHECK( (Coord2D<10, 10, 9>::k_x == 9) );
      CHECK( (Coord2D<10, 10, 9>::k_y == 0) );

      CHECK( (Coord2D<10, 10, 10>::k_x == 0) );
      CHECK( (Coord2D<10, 10, 10>::k_y == 1) );

      CHECK( (Coord2D<5, 10, 0>::k_x == 0) );
      CHECK( (Coord2D<5, 10, 0>::k_y == 0) );

      CHECK( (Coord2D<5, 10, 1>::k_x == 1) );
      CHECK( (Coord2D<5, 10, 1>::k_y == 0) );

      CHECK( (Coord2D<5, 10, 4>::k_x == 4) );
      CHECK( (Coord2D<5, 10, 4>::k_y == 0) );

      CHECK( (Coord2D<5, 10, 5>::k_x == 0) );
      CHECK( (Coord2D<5, 10, 5>::k_y == 1) );
    }

    SECTION("Coord2D Compile and Runtime", "")
    {
      CHECK( (Coord2D<10, 10>::Get(0)[0] == 0) );
      CHECK( (Coord2D<10, 10>::Get(0)[1] == 0) );

      CHECK( (Coord2D<10, 10>::Get(1)[0] == 1) );
      CHECK( (Coord2D<10, 10>::Get(1)[1] == 0) );

      CHECK( (Coord2D<10, 10>::Get(9)[0] == 9) );
      CHECK( (Coord2D<10, 10>::Get(9)[1] == 0) );

      CHECK( (Coord2D<10, 10>::Get(10)[0] == 0) );
      CHECK( (Coord2D<10, 10>::Get(10)[1] == 1) );

      CHECK( (Coord2D<5, 10>::Get(0)[0] == 0) );
      CHECK( (Coord2D<5, 10>::Get(0)[1] == 0) );

      CHECK( (Coord2D<5, 10>::Get(1)[0] == 1) );
      CHECK( (Coord2D<5, 10>::Get(1)[1] == 0) );

      CHECK( (Coord2D<5, 10>::Get(4)[0] == 4) );
      CHECK( (Coord2D<5, 10>::Get(4)[1] == 0) );

      CHECK( (Coord2D<5, 10>::Get(5)[0] == 0) );
      CHECK( (Coord2D<5, 10>::Get(5)[1] == 1) );
    }

    SECTION("Coord2D Runtime", "")
    {
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 0)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 0)[1] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 1)[0] == 1) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 1)[1] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 9)[0] == 9) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 9)[1] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 10)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10), 10)[1] == 1) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 0)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 0)[1] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 1)[0] == 1) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 1)[1] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 4)[0] == 4) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 4)[1] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 5)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10), 5)[1] == 1) );
    }

    SECTION("Coord3D", "")
    {
      CHECK( (Coord3D<10, 10, 10, 0>::k_x == 0) );
      CHECK( (Coord3D<10, 10, 10, 0>::k_y == 0) );
      CHECK( (Coord3D<10, 10, 10, 0>::k_z == 0) );

      CHECK( (Coord3D<10, 10, 10, 1>::k_x == 1) );
      CHECK( (Coord3D<10, 10, 10, 1>::k_y == 0) );
      CHECK( (Coord3D<10, 10, 10, 1>::k_z == 0) );

      CHECK( (Coord3D<10, 10, 10, 9>::k_x == 9) );
      CHECK( (Coord3D<10, 10, 10, 9>::k_y == 0) );
      CHECK( (Coord3D<10, 10, 10, 9>::k_z == 0) );

      CHECK( (Coord3D<10, 10, 10, 10>::k_x == 0) );
      CHECK( (Coord3D<10, 10, 10, 10>::k_y == 1) );
      CHECK( (Coord3D<10, 10, 10, 10>::k_z == 0) );

      CHECK( (Coord3D<10, 10, 10, 100>::k_x == 0) );
      CHECK( (Coord3D<10, 10, 10, 100>::k_y == 0) );
      CHECK( (Coord3D<10, 10, 10, 100>::k_z == 1) );

      CHECK( (Coord3D<5, 10, 10, 0>::k_x == 0) );
      CHECK( (Coord3D<5, 10, 10, 0>::k_y == 0) );
      CHECK( (Coord3D<5, 10, 10, 0>::k_z == 0) );

      CHECK( (Coord3D<5, 10, 10, 1>::k_x == 1) );
      CHECK( (Coord3D<5, 10, 10, 1>::k_y == 0) );
      CHECK( (Coord3D<5, 10, 10, 1>::k_z == 0) );

      CHECK( (Coord3D<5, 10, 10, 4>::k_x == 4) );
      CHECK( (Coord3D<5, 10, 10, 4>::k_y == 0) );
      CHECK( (Coord3D<5, 10, 10, 4>::k_z == 0) );

      CHECK( (Coord3D<5, 10, 10, 5>::k_x == 0) );
      CHECK( (Coord3D<5, 10, 10, 5>::k_y == 1) );
      CHECK( (Coord3D<5, 10, 10, 5>::k_z == 0) );

      CHECK( (Coord3D<5, 10, 10, 50>::k_x == 0) );
      CHECK( (Coord3D<5, 10, 10, 50>::k_y == 0) );
      CHECK( (Coord3D<5, 10, 10, 50>::k_z == 1) );
    }

    SECTION("Coord3D Compile and Runtime", "")
    {
      CHECK( (Coord3D<10, 10, 10>::Get(0)[0] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(0)[1] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(0)[2] == 0) );

      CHECK( (Coord3D<10, 10, 10>::Get(1)[0] == 1) );
      CHECK( (Coord3D<10, 10, 10>::Get(1)[1] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(1)[2] == 0) );

      CHECK( (Coord3D<10, 10, 10>::Get(9)[0] == 9) );
      CHECK( (Coord3D<10, 10, 10>::Get(9)[1] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(9)[2] == 0) );

      CHECK( (Coord3D<10, 10, 10>::Get(10)[0] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(10)[1] == 1) );
      CHECK( (Coord3D<10, 10, 10>::Get(10)[2] == 0) );

      CHECK( (Coord3D<10, 10, 10>::Get(100)[0] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(100)[1] == 0) );
      CHECK( (Coord3D<10, 10, 10>::Get(100)[2] == 1) );

      CHECK( (Coord3D<5, 10, 10>::Get(0)[0] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(0)[1] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(0)[2] == 0) );

      CHECK( (Coord3D<5, 10, 10>::Get(1)[0] == 1) );
      CHECK( (Coord3D<5, 10, 10>::Get(1)[1] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(1)[2] == 0) );

      CHECK( (Coord3D<5, 10, 10>::Get(4)[0] == 4) );
      CHECK( (Coord3D<5, 10, 10>::Get(4)[1] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(4)[2] == 0) );

      CHECK( (Coord3D<5, 10, 10>::Get(5)[0] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(5)[1] == 1) );
      CHECK( (Coord3D<5, 10, 10>::Get(5)[2] == 0) );

      CHECK( (Coord3D<5, 10, 10>::Get(50)[0] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(50)[1] == 0) );
      CHECK( (Coord3D<5, 10, 10>::Get(50)[2] == 1) );
    }

    SECTION("Coord3D Runtime", "")
    {
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 0)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 0)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 0)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 1)[0] == 1) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 1)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 1)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 9)[0] == 9) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 9)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 9)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 10)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 10)[1] == 1) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 10)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 100)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 100)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(10, 10, 10), 100)[2] == 1) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 0)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 0)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 0)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 1)[0] == 1) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 1)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 1)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 4)[0] == 4) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 4)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 4)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 5)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 5)[1] == 1) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 5)[2] == 0) );

      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 50)[0] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 50)[1] == 0) );
      CHECK( (GetCoord(core_ds::MakeTuple(5, 10, 10), 50)[2] == 1) );
    }
  }
}