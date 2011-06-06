namespace TestingTuple
{

  TEST_CASE("Core/DataStructures/Tuple", "Testing the Tuple<T, size> class")
  {
    Tuple<int, 4> p(0);

    p.operator[](0) = 1;
  }

};