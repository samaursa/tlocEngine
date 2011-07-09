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
      CHECK(ints[i] == i);
    }

    CHECK(ints.size() == 100);
  }
};
