#include "tlocTestCommon.h"

#include <tlocCore/data_structures/tlocTable.h>
#include <tlocCore/data_structures/tlocTable.inl.h>

namespace TestingTable
{
  using namespace tloc;
  using namespace tloc::core::data_structs;

  typedef Tuple<tl_int, 3> tuple_int_type;
  typedef Tuple<s32, 3> tuple_int_type_32;
  typedef Tuple<s64, 3> tuple_int_type_64;

  struct Table3Fixture
  {
    Table3Fixture()
    {
      tuple_int_type row1;
      tuple_int_type row2;
      tuple_int_type row3;

      tuple_int_type col1;
      tuple_int_type col2;
      tuple_int_type col3;

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

    Table<tl_int, 3, 3> a, b, c, d;
  };

#define CHECK_TABLE(tab,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((tab[0]) == ((x1)) ); CHECK((tab[1]) == ((y1)) ); \
  CHECK((tab[2]) == ((z1)) ); CHECK((tab[3]) == ((x2)) ); \
  CHECK((tab[4]) == ((y2)) ); CHECK((tab[5]) == ((z2)) ); \
  CHECK((tab[6]) == ((x3)) ); CHECK((tab[7]) == ((y3)) ); \
  CHECK((tab[8]) == ((z3)) )

#define CHECK_TABLE_4(tab,x1,y1,z1,w1, x2,y2,z2,w2, x3,y3,z3, w3, x4, y4, z4, w4) \
  CHECK((tab[0]) == ((x1)) ); CHECK((tab[1]) == ((y1)) ); \
  CHECK((tab[2]) == ((z1)) ); CHECK((tab[3]) == ((w1)) );\
  \
  CHECK((tab[4]) == ((x2)) ); CHECK((tab[5]) == ((y2)) ); \
  CHECK((tab[6]) == ((z2)) ); CHECK((tab[7]) == ((w2)) );\
  \
  CHECK((tab[8]) == ((x3)) ); CHECK((tab[9]) == ((y3)) ); \
  CHECK((tab[10]) == ((z3)) ); CHECK((tab[11]) == ((w3)) );\
  \
  CHECK((tab[12]) == ((x4)) ); CHECK((tab[13]) == ((y4)) ); \
  CHECK((tab[14]) == ((z4)) ); CHECK((tab[15]) == ((w4)) )


  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/General",
    "Test general/basic functionality")
  {
    CHECK_TABLE(a, 1, 4, 7, 2, 5, 8, 3, 6, 9);
    CHECK_TABLE(b, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    Table<tl_uint, 3, 3> ut(a);
    CHECK_TABLE(ut, 1, 4, 7, 2, 5, 8, 3, 6, 9);
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

    tuple_int_type tup;

    a.GetRow(0, tup);
    CHECK(tup[0] == 1); CHECK(tup[1] == 2); CHECK(tup[2] == 3);

    tup.Set(0);
    tup = a.GetRow(0);
    CHECK(tup[0] == 1); CHECK(tup[1] == 2); CHECK(tup[2] == 3);

    a.GetRow(2, tup);
    CHECK(tup[0] == 7); CHECK(tup[1] == 8); CHECK(tup[2] == 9);

    tup.Set(0);
    tup = a.GetRow(2);
    CHECK(tup[0] == 7); CHECK(tup[1] == 8); CHECK(tup[2] == 9);

    a.GetCol(0, tup);
    CHECK(tup[0] == 1); CHECK(tup[1] == 4); CHECK(tup[2] == 7);

    tup.Set(0);
    tup = a.GetCol(0);
    CHECK(tup[0] == 1); CHECK(tup[1] == 4); CHECK(tup[2] == 7);

    // Col-major ordering
    CHECK( *(a.data() + 0) == 1);
    CHECK( *(a.data() + 1) == 4);
    CHECK( *(a.data() + 2) == 7);
  }

  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/Modifiers",
    "Test all modifiers functions")
  {
    c = a;
    CHECK_TABLE(c, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tuple_int_type row1;
    tuple_int_type row2;
    tuple_int_type row3;

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
    tl_int rawArray[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    // ROW_MAJOR means that the above array has vectors in a row major order
    // i.e. 9,8,7 is a row vector, 6,5,4 is a row vector and so on
    a.Set(rawArray, Table<tl_int, 3, 3>::k_RowMajor);
    CHECK_TABLE(a, 9, 6, 3, 8, 5, 2, 7, 4, 1);

    a.Set(0);
    a.Set(rawArray, Table<tl_int, 3, 3>::k_ColMajor);
    CHECK_TABLE(a, 9, 8, 7, 6, 5, 4, 3, 2, 1);
  }

  TEST_CASE_METHOD(Table3Fixture, "Core/DataStructures/Tables/Operators",
    "Test all operator functions")
  {
    c = a;
    CHECK( (a == c) == true);
    CHECK( (a != c) == false);

    c = a;
    CHECK(c[0] == 1); CHECK(c[1] == 4); CHECK(c[2] == 7);
    CHECK(c[3] == 2); CHECK(c[4] == 5); CHECK(c[5] == 8);
    CHECK(c[6] == 3); CHECK(c[7] == 6); CHECK(c[8] == 9);
  }

  TEST_CASE("Core/DataStructures/Table/Implicit conversion",
    "Conversion from different tables types")
  {
    Table<s32, 3, 3> table32;

    tuple_int_type_32 row1;
    tuple_int_type_32 row2;
    tuple_int_type_32 row3;

    row1[0] = 11; row1[1] = 21; row1[2] = 31;
    row2[0] = 41; row2[1] = 51; row2[2] = 61;
    row3[0] = 71; row3[1] = 81; row3[2] = 91;

    table32.SetRow(0, row1);
    table32.SetRow(1, row2);
    table32.SetRow(2, row3);

    Table<s64, 3, 3> table64(table32);

    CHECK_TABLE(table64, 11, 41, 71, 21, 51, 81, 31, 61, 91);

    table32 = table64.Cast<Table<s32, 3, 3> >();

    CHECK_TABLE(table32, 11, 41, 71, 21, 51, 81, 31, 61, 91);

    table32 = table32.Cast<Table<s32, 3, 3> >();

    CHECK_TABLE(table32, 11, 41, 71, 21, 51, 81, 31, 61, 91);
  }

  TEST_CASE("core/data_structures/Table/ConvertFrom", "")
  {
    Table<s32, 4, 4> table32;
    table32.Set(0, 0, 0);
    table32.Set(1, 0, 1);
    table32.Set(2, 0, 2);
    table32.Set(3, 0, 3);

    table32.Set(0, 1, 4);
    table32.Set(1, 1, 5);
    table32.Set(2, 1, 6);
    table32.Set(3, 1, 7);

    table32.Set(0, 2, 8);
    table32.Set(1, 2, 9);
    table32.Set(2, 2, 10);
    table32.Set(3, 2, 11);

    table32.Set(0, 3, 12);
    table32.Set(1, 3, 13);
    table32.Set(2, 3, 14);
    table32.Set(3, 3, 15);

    SECTION("ConvertFrom - 3x3", "")
    {
      Table<s32, 3, 3> table3x3;
      table3x3.ConvertFrom(table32);

      CHECK_TABLE(table3x3, 0, 1, 2, 4, 5, 6, 8, 9, 10);
    }

    SECTION("ConvertFrom - overflow_same", "")
    {
      Table<s32, 3, 3> table3x3(5);
      table32.ConvertFrom(table3x3, p_tuple::overflow_same());

      CHECK_TABLE_4(table32, 5, 5, 5, 3, 
                             5, 5, 5, 7, 
                             5, 5, 5, 11, 
                             12, 13, 14, 15);
    }

    SECTION("ConvertFrom - overflow_one", "")
    {
      Table<s32, 3, 3> table3x3(5);
      table32.ConvertFrom(table3x3, p_tuple::overflow_one());

      CHECK_TABLE_4(table32, 5, 5, 5, 1, 
                             5, 5, 5, 1, 
                             5, 5, 5, 1, 
                             1, 1, 1, 1);
    }

    SECTION("ConvertFrom - overflow_one", "")
    {
      Table<s32, 3, 3> table3x3(5);
      table32.ConvertFrom(table3x3, p_tuple::overflow_zero());

      CHECK_TABLE_4(table32, 5, 5, 5, 0, 
                             5, 5, 5, 0, 
                             5, 5, 5, 0, 
                             0, 0, 0, 0);
    }

    SECTION("ConvertTo - 3x3", "")
    {
      Table<s32, 3, 3> table3x3 = table32.ConvertTo<Table<s32, 3, 3> >();

      CHECK_TABLE(table3x3, 0, 1, 2, 4, 5, 6, 8, 9, 10);
    }

    SECTION("ConvertTo - overflow_same", "")
    {
      Table<s32, 3, 3> table3x3(5);

      table32 = table3x3.ConvertTo<Table<s32, 4, 4>, p_tuple::overflow_one>();

      CHECK_TABLE_4(table32, 5, 5, 5, 1, 
                             5, 5, 5, 1, 
                             5, 5, 5, 1, 
                             1, 1, 1, 1);
    }

    SECTION("ConvertTo - overflow_one", "")
    {
      Table<s32, 3, 3> table3x3(5);

      table32 = table3x3.ConvertTo<Table<s32, 4, 4>, p_tuple::overflow_zero>();

      CHECK_TABLE_4(table32, 5, 5, 5, 0, 
                             5, 5, 5, 0, 
                             5, 5, 5, 0, 
                             0, 0, 0, 0);
    }
  }

  TEST_CASE("core/data_structures/Table/Extract", "")
  {
    Table<s32, 4, 4> table32;
    table32.Set(0, 0, 0);
    table32.Set(1, 0, 1);
    table32.Set(2, 0, 2);
    table32.Set(3, 0, 3);

    table32.Set(0, 1, 4);
    table32.Set(1, 1, 5);
    table32.Set(2, 1, 6);
    table32.Set(3, 1, 7);

    table32.Set(0, 2, 8);
    table32.Set(1, 2, 9);
    table32.Set(2, 2, 10);
    table32.Set(3, 2, 11);

    table32.Set(0, 3, 12);
    table32.Set(1, 3, 13);
    table32.Set(2, 3, 14);
    table32.Set(3, 3, 15);

    SECTION("Extract - runtime", "")
    {
      Table<s32, 3, 3> table3x3 = table32.Extract<Table<s32, 3, 3> >(0, 0);
      CHECK_TABLE(table3x3, 0, 1, 2,
                            4, 5, 6,
                            8, 9, 10);

      table3x3 = table32.Extract<Table<s32, 3, 3> >(1, 1);
      CHECK_TABLE(table3x3, 5, 6, 7, 9, 10, 11, 13, 14, 15);

      Table<s32, 2, 1> table2x1 = table32.Extract<Table<s32, 2, 1> >(0, 0);
      CHECK(table2x1.Get(0, 0) == 0);
      CHECK(table2x1.Get(1, 0) == 1);

      Table<s32, 1, 2> table1x2 = table32.Extract<Table<s32, 1, 2> >(0, 0);
      CHECK(table1x2.Get(0, 0) == 0);
      CHECK(table1x2.Get(0, 1) == 4);

      TLOC_TEST_ASSERT
      {
        table32.Extract<Table<s32, 5, 5> >(0, 0);
      }
      TLOC_TEST_ASSERT_CHECK();

      TLOC_TEST_ASSERT
      {
        table32.Extract<Table<s32, 3, 3> >(2, 2);
      }
      TLOC_TEST_ASSERT_CHECK();
    }

    SECTION("Extract - compile time", "")
    {
      Table<s32, 3, 3> table3x3 = table32.Extract<Table<s32, 3, 3>, 0, 0>();
      CHECK_TABLE(table3x3, 0, 1, 2,
                            4, 5, 6,
                            8, 9, 10);

      table3x3 = table32.Extract<Table<s32, 3, 3>, 1, 1>();
      CHECK_TABLE(table3x3, 5, 6, 7, 9, 10, 11, 13, 14, 15);

      Table<s32, 2, 1> table2x1 = table32.Extract<Table<s32, 2, 1>, 0, 0>();
      CHECK(table2x1.Get(0, 0) == 0);
      CHECK(table2x1.Get(1, 0) == 1);

      Table<s32, 1, 2> table1x2 = table32.Extract<Table<s32, 1, 2>, 0, 0>();
      CHECK(table1x2.Get(0, 0) == 0);
      CHECK(table1x2.Get(0, 1) == 4);
    }
  }

};
