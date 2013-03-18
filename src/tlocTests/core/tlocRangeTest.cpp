#include "tlocTestCommon.h"

#include <tlocCore/tlocRange.h>

namespace TestingRange
{
  using namespace tloc;
  using namespace core;

  // Tests are taken from https://bitbucket.org/AraK/range and modified where
  // appropriate

  TEST_CASE("core/range/ctors", "")
  {
    CHECK(Range().empty());

    Range r;
    r = Range(0, 10);
    r = Range(10, 10);
    r = Range(0, 0);

    r = Range(0, 10, Range::step_size(1));
    r = Range(0, 0, Range::step_size(2));

    Range r2(r);
    CHECK(r2 == r);
  }

  TEST_CASE("core/range/accessors", "")
  {
    Range r(0, 10);
    CHECK(r.front() == 0);
    CHECK(r.back() == 9);

    r = Range(0, 0);
    CHECK(r.front() == 0);
    CHECK(r.back() == 0);

    r = Range(5, 10);
    CHECK(r.front() == 5);
    CHECK(r.back() == 9);

    r = Range(0, 10, Range::step_size(2));
    CHECK(r.front() == 0);
    CHECK(r.back() == 8);

    r = Range(0, 10, Range::step_size(3));
    CHECK(r.front() == 0);
    CHECK(r.back() == 9);

    r = Range(0, 10, Range::step_size(4));
    CHECK(r.front() == 0);
    CHECK(r.back() == 8);

    r = Range(10, 50, Range::step_size(10));
    CHECK(r.front() == 10);
    CHECK(r.back() == 40);

    r = Range(10, 51, Range::step_size(10));
    CHECK(r.front() == 10);
    CHECK(r.back() == 50);
  }

  TEST_CASE("core/range/size", "")
  {
    Range r(0, 10);
    CHECK(r.size() == 10);
    r = Range(0, 10, Range::step_size(2));
    CHECK(r.size() == 5);
    r = Range(0, 10, Range::step_size(10));
    CHECK(r.size() == 1);
    r = Range(0, 10, Range::step_size(11));
    CHECK(r.size() == 1);
  }

  TEST_CASE("core/range/empty_full", "")
  {
    CHECK(Range().empty());
    Range r(150, 200);
    CHECK_FALSE(r.empty());
    r = Range(150, 150);
    CHECK(r.empty());
  }

  TEST_CASE("core/range/iterators", "")
  {
    Range r(0, 10);
    Range::iterator itr = r.begin();
    Range::reverse_iterator rItr = r.rbegin();

    bool testPassed = true;
    for (tl_int i = 0; i < 10; ++i)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    testPassed = true;
    for (tl_int i = 10; i > 0; --i)
    {
      if (*(rItr++) != i-1)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    rItr -= 10; // we were at rend, so we can go rback 10 indices
    CHECK(*rItr == 9);
    rItr += 9; // we were at rbegin, we can go rforward 9 indices
    CHECK(*rItr == 0);

    CHECK(*rItr-- == 0);
    CHECK(*rItr   == 1);
    CHECK(*--rItr == 2);

    CHECK(*rItr++ == 2);
    CHECK(*rItr   == 1);
    CHECK(*++rItr == 0);

    CHECK( *(rItr - 9) == 9);
    CHECK( *( (--rItr) + 1) == 0);

    r = Range(0, 10, Range::step_size(2));
    itr = r.begin();
    testPassed = true;
    for (tl_int i = 0; i < 10; i = i+2)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    r = Range(5, 6);
    itr = r.begin();
    testPassed = true;
    for (tl_int i = 5; i < 6; ++i)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    r = Range(5, 6, Range::step_size(10));
    itr = r.begin();
    testPassed = true;
    for (tl_int i = 5; i < 6; i = i + 10)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    r = Range(0, 50, Range::step_size(2));
    itr = r.begin();
    Range::iterator itrEnd = r.end();
    tl_int count = 0;
    for (; itr < itrEnd; ++itr)
    {
      ++count;
    }
    CHECK(count == 50/2);

    itr -= 25;
    CHECK(*itr == 0);
    itr += 10;
    CHECK(*itr == 20);

    CHECK(*itr++ == 20);
    CHECK(*itr   == 22);
    CHECK(*++itr == 24);

    CHECK(*itr == 24);

    CHECK(*itr-- == 24);
    CHECK(*itr   == 22);
    CHECK(*--itr == 20);

    CHECK( *(itr - 10) == 0);
    CHECK( *( (--itr) + 1) == 20);
  }
}
