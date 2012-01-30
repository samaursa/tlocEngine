#include "tlocTestCommon.h"

#include "tlocCore/tlocForwardList.h"
#include "tlocCore/tlocForwardList.inl"

namespace TestingForwardList
{
  USING_TLOC;
  using namespace core;

#define CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(forwardListBegin, \
                                                     forwardListEnd, \
                                                     value) \
  for (/* */; forwardListBegin != forwardListEnd; ++forwardListBegin)\
  {\
  CHECK((*forwardListBegin) == value);\
  }

#define FILL_FORWARD_LIST_BY_PUSH(forwardListName, nFrom, nTo) \
  for (u32 i = nFrom; i < nTo; ++i)\
  {\
    forwardListName.push_back(i);\
  }

  struct ForwardListFixture
  {
    typedef ForwardList<s32>::type intForwardList;
    typedef ArrayForwardList<s32>::type arrayIntForwardList;
  };

  template <typename T_ForwardListType>
  void testCtors()
  {
    T_ForwardListType first;
    T_ForwardListType second(10,20);
    T_ForwardListType third (second.begin(), second.end());
    T_ForwardListType fourth (third);

    T_ForwardListType::iterator itr = second.begin();
    T_ForwardListType::iterator itrEnd = second.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 20);

    itr = third.begin();
    itrEnd = third.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 20);

    itr = fourth.begin();
    itrEnd = fourth.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 20);

    s32 myInts[] = {37, 14, 94, 100};
    T_ForwardListType fifth (myInts, myInts + sizeof(myInts) / sizeof(s32));

    itr = fifth.begin();

    CHECK(*itr++ == 37);
    CHECK(*itr++ == 14);
    CHECK(*itr++ == 94);
    CHECK(*itr++ == 100);
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/Ctors" , "")
  {
    testCtors<intForwardList>();
    testCtors<arrayIntForwardList>();
  }
};