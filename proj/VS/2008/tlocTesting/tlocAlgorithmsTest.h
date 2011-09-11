namespace TestingAlgorithms
{
  struct AlgorithmFixture
  {

  };

  TEST_CASE("Core/Algorithms/Swap", "Test the min() functions")
  {
    u32 i = 10, j = 15;
    u32 minimum = tlMin(i, j);
    CHECK(minimum == i);
  }

  TEST_CASE("Core/Algorithms/Swap", "Test the swap() functions")
  {
    u32 i = 10, j = 15;
    tlSwap(i, j);
    CHECK(i == 15);
    CHECK(j == 10);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Copy",
    "Test the copy() functions")
  {
    { // tlCopy arithmetic types
      const char8* testString = "This is a test string"; // 21 chars including /0
      const char8* stringEnd = testString + 22; // copy does not include stringEnd
      char8* copiedString = new char8[stringEnd - testString];

      tlCopy(testString, stringEnd, copiedString);

      for (u32 i = 0; i < (u32)(stringEnd - testString); ++i)
      {
        CHECK(copiedString[i] == testString[i]);
      }
    }

    { // tlCopy complex types
      typedef struct copyTest
      {
        int a;
        int b;
      }copyTest;

      copyTest testStruct = {1, 5};
      copyTest arrayStructs[5];
      copyTest copiedStructs[5];

      for (u32 i = 0; i < 5; ++i)
      {
        arrayStructs[i] = testStruct;
      }

      tlCopy(arrayStructs, arrayStructs + 5, copiedStructs);

      for (u32 i = 0; i < 5; ++i)
      {
        CHECK(copiedStructs[i].a == testStruct.a);
        CHECK(copiedStructs[i].b == testStruct.b);
      }
    }

    {// tlCopyBackward
      char8 testString[] = "0123456789"; // 10 chars including /0

      tlCopy_Backward(testString, testString + 6, testString + 10);

      CHECK( testString[0] == '0');
      CHECK( testString[1] == '1');
      CHECK( testString[2] == '2');
      CHECK( testString[3] == '3');
      CHECK( testString[4] == '0');
      CHECK( testString[5] == '1');
      CHECK( testString[6] == '2');
      CHECK( testString[7] == '3');
      CHECK( testString[8] == '4');
      CHECK( testString[9] == '5');
    }
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Fill",
    "Test the fill() functions")
  {
    { // tlFill char (tlFill has specialization for tlFill<char>() )
      char8 testArray[100] = {0};

      tlFill(testArray, testArray + 100, 'T');

      for (u32 i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 'T');
      }
    }

    { // tlFill other types
      u64 testArray[100] = {0};

      tlFill(testArray, testArray + 100, 50);

      for (u32 i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 50);
      }
    }
  }
};
