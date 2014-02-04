#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

using namespace tloc;
using namespace core_sptr;

TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(int, int);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(int);

namespace TestingVirtualStackObject
{
  TEST_CASE("core/smart_ptr/VirtualStackObject/ctors", "")
  {
    SECTION("All ctors", "")
    {
      int_vso onStack;
      *onStack = 10;
      CHECK( (onStack == 10 ) );

      int onStackCopy = *onStack;
      CHECK(onStackCopy == 10);

      int_vso::ptr_type ptrToVSO = onStack.get();
      CHECK(*ptrToVSO == 10);

      int_vso onStack2(*onStack);
      CHECK( (onStack2 == 10) );
    }

    SECTION("No default ctor", "")
    {
      VirtualStackObject_T<int, p_virtual_stack_object::default_ctor::NotAvail>
        onStack(20);
      CHECK( (onStack == 20) );
    }
  }

  struct NoDefCtorOrEqualOper
  {
    NoDefCtorOrEqualOper(tl_int a_num)
      : a(a_num)
      , b(a_num)
      , c(a_num)
    { }

    tl_int a, b, c;
  };

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR_AND_EQUALITY
    (NoDefCtorOrEqualOper, no_def_ctor_or_equal_oper);
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR_AND_EQUALITY
    (NoDefCtorOrEqualOper);

  struct NonCopyableNoDefaultNoEquality
    : public core_bclass::NonCopyable_I
  {
    // The only way to construct the object with an initial value
    NonCopyableNoDefaultNoEquality(int)
    { }

    // Required by VSO to be able to initialize the object with an initial value
    explicit NonCopyableNoDefaultNoEquality(const NonCopyableNoDefaultNoEquality&)
    { }
  };

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR_AND_EQUALITY(NonCopyableNoDefaultNoEquality, nocopy);
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR_AND_EQUALITY(NonCopyableNoDefaultNoEquality);

  TEST_CASE("core/smart_ptr/VirtualStackObject/operators", "")
  {
    SECTION("comparison", "")
    {
      int_vso s1(10), s2(20), s3(10);
      CHECK( (s1 == s3) );
      CHECK( (s1 != s2) );
      CHECK_FALSE( (s1 == s2) );
    }

    SECTION("No equality", "")
    {
      VirtualStackObject_T<NoDefCtorOrEqualOper,
                           p_virtual_stack_object::default_ctor::NotAvail,
                           p_virtual_stack_object::equality::NotAvail>
      onStack(50);
      CHECK(onStack->a == 50);

      // CHECK( (onStack == 20) ); // should be a compiler error
      // CHECK_FALSE( (onStack != 20) ); // should be a compiler error
    }
  }
}