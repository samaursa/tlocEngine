#include "tlocTestCommon.h"

#include "tlocCore/tlocTable.h"
#include "tlocCore/tlocTable.inl"

namespace TestingTable
{
  USING_TLOC;

  struct Table3Fixture
  {
    Table3Fixture()
    {
      tloc::core::Tuple<s32, 3> row1;
      tloc::core::Tuple<s32, 3> row2;
      tloc::core::Tuple<s32, 3> row3;

      tloc::core::Tuple<s32 ,3> col1;
      tloc::core::Tuple<s32 ,3> col2;
      tloc::core::Tuple<s32 ,3> col3;

      row1[0] = 1; row1[1] = 2; row1[2] = 3;
      row2[0] = 4; row2[1] = 5; row2[2] = 6;
      row3[0] = 7; row3[1] = 8; row3[2] = 9;

      col1[0] = 1; col1[1] = 2; col1[2] = 3;
      col2[0] = 4; col2[1] = 5; col2[2] = 6;
      col3[0] = 7; col3[1] = 8; col3[2] = 9;

      a.SetRow(0, row1);
      a.SetRow(1, row2);
      a.SetRow(2, row3);

      b.SetCol(0, col1);
      b.SetCol(1, col2);
      b.SetCol(2, col3);
    }

    tloc::core::Table<s32, 3, 3> a, b, c, d;
  };

#define CHECK_TABLE(tab,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((tab[0]) == ((x1)) ); CHECK((tab[1]) == ((y1)) ); \
  CHECK((tab[2]) == ((z1)) ); CHECK((tab[3]) == ((x2)) ); \
  CHECK((tab[4]) == ((y2)) ); CHECK((tab[5]) == ((z2)) ); \
  CHECK((tab[6]) == ((x3)) ); CHECK((tab[7]) == ((y3)) ); \
  CHECK((tab[8]) == ((z3)) );


  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/General",
    "Test general/basic functionality")
  {
    CHECK_TABLE(a, 1, 4, 7, 2, 5, 8, 3, 6, 9);
    CHECK_TABLE(b, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  }

  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/Accessors",
    "Test all accessor functions")
  {
    CHECK(a(0, 0) == 1);
    CHECK(a(0, 1) == 2);
    CHECK(a(2, 2) == 9);

    CHECK(b(0, 0) == 1);
    CHECK(b(0, 1) == 4);
    CHECK(b(2, 2) == 9);

    CHECK(a.Get(0, 0) == 1);
    CHECK(a.Get(0, 1) == 2);
    CHECK(a.Get(2, 2) == 9);

    CHECK(b.Get(0, 0) == 1);
    CHECK(b.Get(0, 1) == 4);
    CHECK(b.Get(2, 2) == 9);

    core::Tuple<s32, 3> tup;

    a.GetRow(0, tup);
    CHECK(tup[0] == 1); CHECK(tup[1] == 2); CHECK(tup[2] == 3);

    a.GetRow(2, tup);
    CHECK(tup[0] == 7); CHECK(tup[1] == 8); CHECK(tup[2] == 9);

    a.GetCol(0, tup);
    CHECK(tup[0] == 1); CHECK(tup[1] == 4); CHECK(tup[2] == 7);

    // Col-major ordering
    CHECK( *(a + 0) == 1); CHECK( *(a + 1) == 4); CHECK( *(a + 2) == 7);
  }

  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/Modifiers",
    "Test all modifiers functions")
  {
    c = a;
    CHECK_TABLE(c, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tloc::core::Tuple<s32, 3> row1;
    tloc::core::Tuple<s32, 3> row2;
    tloc::core::Tuple<s32, 3> row3;

    row1[0] = 11; row1[1] = 21; row1[2] = 31;
    row2[0] = 41; row2[1] = 51; row2[2] = 61;
    row3[0] = 71; row3[1] = 81; row3[2] = 91;

    a.SetRow(0, row1);
    CHECK_TABLE(a, 11, 4, 7, 21, 5, 8, 31, 6, 9);
    a.SetCol(2, row3);
    CHECK_TABLE(a, 11, 4, 7, 21, 5, 8, 71, 81, 91);

    a.Set(2, 2, 100);
    CHECK_TABLE(a, 11, 4, 7, 21, 5, 8, 71, 81, 100);

    a.Set(0);
    CHECK_TABLE(a, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    s32 rawArray[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    // ROW_MAJOR means that the above array has vectors in a row major order
    // i.e. 9,8,7 is a row vector, 6,5,4 is a row vector and so on
    a.Set(rawArray, tloc::core::Table<s32, 3, 3>::k_RowMajor);
    CHECK_TABLE(a, 9, 6, 3, 8, 5, 2, 7, 4, 1);

    a.Set(0);
    a.Set(rawArray, tloc::core::Table<s32, 3, 3>::k_ColMajor);
    CHECK_TABLE(a, 9, 8, 7, 6, 5, 4, 3, 2, 1);
  }

  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/Operators",
    "Test all operator functions")
  {
    a = c;
    CHECK( (a == c) == true);
    CHECK( (a != c) == false);
  }
};
