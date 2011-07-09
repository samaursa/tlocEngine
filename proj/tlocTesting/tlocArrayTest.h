namespace TestingArray
{
  struct ArrayFixture
  {
    int a, b, c, d, e, f;
    Array<int> ints;
  };

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/General",
                                                   "Test General functionality")
  {
    TLOC_ASSERT(NULL == NULL, "Test");

    ints.push_back(5);
    a = ints[0];
    CHECK(a == 5);

    ints.push_back(10);
    a = ints[0];
    CHECK(a == 5);
    b = ints[1];
    CHECK(b == 10);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Accessors",
                                                              "Test accessors")
  {
    for (u32 i = 0; i < 100; ++i)
    {
      ints.push_back(i);
    }

    Array<int>::iterator itr = ints.begin();
    Array<int>::iterator itrEnd = ints.end();

    int count = 0;
    while (itr != itrEnd)
    {
      CHECK(count++ == *itr);
      ++itr;
    }

    CHECK(ints.size() == 100);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Erase",
    "Test all erase functions")
  {
    //------------------------------------------------------------------------
    // Erase at position

    for (u32 i = 0; i < 10; ++i)
    {
      ints.push_back(i);
    }

    CHECK(ints.size() == 10);
    ints.erase(ints.begin() + 4);
    CHECK(ints.size() == 9);

    for (u32 i = 4; i < 9; ++i)
    {
      CHECK(ints[i] == (s32)i + 1);
    }

    //------------------------------------------------------------------------
    // Erase range

    ints.push_back(0);

    for (u32 i = 0; i < 10; ++i)
    {
      ints[i] = i;
    }

    CHECK(ints.size() == 10);
    u32 currCapacity = ints.capacity();
    ints.erase(ints.begin(), ints.end());
    CHECK(ints.size() == 0);
    CHECK(ints.capacity() == currCapacity);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Clear",
    "Test the clear function")
  {
    u32 sizeOfInts = 1000;
    for (u32 i = 0; i < sizeOfInts; ++i)
    {
      ints.push_back(i);
    }

    u32 currCapacity = ints.capacity();
    CHECK(ints.size() == sizeOfInts);
    ints.clear();
    CHECK(ints.size() == 0);
    CHECK(ints.capacity() == currCapacity);
  }

};
