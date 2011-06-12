namespace TestingTuple
{

  TEST_CASE("Core/DataStructures/Tuple", "Testing the Tuple<T, size> class")
  {
    Tuple<int, 4> p(0);

    p[0] = 0; p[1] = 1; p[2] = 2; p[3] = 3;
  }

};