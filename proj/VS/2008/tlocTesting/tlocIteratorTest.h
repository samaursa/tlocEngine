namespace TestingIterator
{
  USING_TLOC;

  TEST_CASE("Core/Iteraor/back_insert_iterator", "")
  {
    Array<s32> firstvector, secondvector;
    for (s32 i=1; i<=5; i++)
    { firstvector.push_back(i); secondvector.push_back(i*10); }

    back_insert_iterator< Array<s32> > back_it (firstvector);

    copy (secondvector.begin(),secondvector.end(),back_it);

    CHECK(firstvector[0] == 1); CHECK(firstvector[1] == 2);
    CHECK(firstvector[2] == 3); CHECK(firstvector[3] == 4);
    CHECK(firstvector[4] == 5);
    CHECK(firstvector[5] == 10); CHECK(firstvector[6] == 20);
    CHECK(firstvector[7] == 30); CHECK(firstvector[8] == 40);
    CHECK(firstvector[9] == 50);

  }

  TEST_CASE("Core/Iteraor/front_insert_iterator", "")
  {
    // TODO: Test after implementing tlocList
  }

  TEST_CASE("Core/Iteraor/insert_iterator", "")
  {
    Array<s32> firstlist, secondlist;
    for (s32 i=1; i<=5; i++)
    { firstlist.push_back(i); secondlist.push_back(i*10); }

    Array<s32>::iterator it;
    it = firstlist.begin(); advance (it,3);

    insert_iterator< Array<s32> > insert_it (firstlist,it);

    copy (secondlist.begin(),secondlist.end(),insert_it);

    CHECK(firstlist[0] == 1); CHECK(firstlist[1] == 2);
    CHECK(firstlist[2] == 3); CHECK(firstlist[3] == 10);
    CHECK(firstlist[4] == 20); CHECK(firstlist[5] == 30);
    CHECK(firstlist[6] == 40); CHECK(firstlist[7] == 50);
    CHECK(firstlist[8] == 4); CHECK(firstlist[9] == 5);
  }
};
