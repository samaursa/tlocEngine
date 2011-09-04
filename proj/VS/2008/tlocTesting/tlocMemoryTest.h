namespace TestingMemory
{
  TEST_CASE("Core/Memory", "Testing memory allocators")
  {
    int* a = new int();
    REQUIRE(a != NULL);
    delete a;
  }
};