#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocList.inl.h>
#include <tlocCore/containers/tlocHashmap.h>
#include <tlocCore/containers/tlocHashmap.inl.h>

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
      onStack = 10;
      CHECK( (*onStack == 10 ) );
      CHECK( (*onStack.get() == 10) );

      int onStackCopy = *onStack;
      CHECK(onStackCopy == 10);

      {
        int_vso::pointer ptrToVSO(onStack.get());
        CHECK(*ptrToVSO == 10);

        *ptrToVSO = 30;
        CHECK(*ptrToVSO == 30);
        CHECK(*onStack == 30);
      } // if ptrToVSO is not destroyed, line 51 will throw an assertion

      int_vso onStack2(*onStack);
      CHECK( (*onStack2 == 30) );

      onStack2 = 10;
      CHECK(*onStack2 == 10);
      CHECK(*onStack == 30);

      onStack = onStack2;
      CHECK(*onStack2 == 10);
      CHECK(*onStack == 10);

    }

    SECTION("No default ctor", "")
    {
      VirtualStackObjectBase_TI<int, p_virtual_stack_object::default_ctor::NotAvail>
        onStack(20);
      CHECK( (*onStack == 20) );
    }

    SECTION("Memory address check", "")
    {
      int_vso onStack(10);
      tl_uintptr  memAddress = core_utils::GetMemoryAddress(onStack.get());

      int_vso::pointer ptrToVSO = onStack.get();
      CHECK(*ptrToVSO == 10);

      *ptrToVSO = 20;

      CHECK(*ptrToVSO == 20);
      CHECK(core_utils::GetMemoryAddress(ptrToVSO) == memAddress);
    }
  }

  struct NoDefCtor
  {
    NoDefCtor(tl_int a_num)
      : a(a_num)
      , b(a_num)
      , c(a_num)
    { }

    NoDefCtor(const NoDefCtor& a_other)
      : a(a_other.a)
      , b(a_other.b)
      , c(a_other.c)
    { }

    tl_int a, b, c;
  };

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR
    (NoDefCtor, no_def_ctor);

  struct NoCopyCtor
  {
    NoCopyCtor()
      : a(0)
      , b(0)
      , c(0)
    { }

    tl_int a, b, c;
  };

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR
    (NoCopyCtor, no_copy_ctor);

  struct NoDefCtorNoCopyCtor
    : public core_bclass::NonCopyable_I
  {
    // The only way to construct the object with an initial value
    NoDefCtorNoCopyCtor(tl_int a_num)
      : a(a_num)
    { }

    tl_int a;
  };

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(NoDefCtorNoCopyCtor, no_copy_no_def);

  TEST_CASE("core/smart_ptr/VirtualStackObject/ctor_types", "")
  {
    no_def_ctor_vso         ndc(no_def_ctor_vso(10));
    no_copy_ctor_vso        ncc;
    no_copy_no_def_vso      ncnd(10);
  }

  TEST_CASE("core/smart_ptr/VirtualStackObject/operators", "")
  {
    SECTION("comparison", "")
    {
      int_vso s1(10), s2(20), s3(10);
      CHECK( (*s1 == *s3) );
      CHECK( (*s1 != *s2) );
      CHECK_FALSE( (*s1 == *s2) );
    }

    SECTION("No equality", "")
    {
      no_def_ctor_vso onStack(50);
      CHECK(onStack->a == 50);

      // CHECK( (onStack == 20) ); // should be a compiler error
      // CHECK_FALSE( (onStack != 20) ); // should be a compiler error
    }
  }

  TLOC_EXPLICITLY_INSTANTIATE_ARRAY(int_vso);
  TLOC_EXPLICITLY_INSTANTIATE_ARRAY(int_vso);

  class IntComponent
  {
  public:
    typedef tl_int         value_type;

  public:
    IntComponent()
    { m_ctorCount++; }

    IntComponent(const IntComponent& a_other)
      : m_value(a_other.m_value)
    { m_ctorCount++; }

    ~IntComponent()
    { m_dtorCount++; }

    tl_int m_value;
    static tl_int m_dtorCount;
    static tl_int m_ctorCount;
  };

  tl_int IntComponent::m_dtorCount;
  tl_int IntComponent::m_ctorCount;

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(IntComponent, int_comp);
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(IntComponent);

#define RESET_CTOR_AND_DTOR_COUNT()\
    IntComponent::m_dtorCount = 0;\
    IntComponent::m_ctorCount = 0

  TEST_CASE("core/smart_ptr/VirtualStackObject/arrays", "")
  {
    SECTION("Array<>", "")
    {
      // BUGFIX: VSOs lose their pointer addresses when the memory is
      // reallocated e.g. in containers. This bug was fixed by forcing the
      // virtual pointers to grab the memory address again and perform
      // additional checks.
      core_conts::Array<int_comp_vso> arr;
      RESET_CTOR_AND_DTOR_COUNT();
      arr.resize(10);
      arr.resize(20);
      arr.resize(40);

      arr.clear();
      CHECK(IntComponent::m_ctorCount > 0);
      CHECK(IntComponent::m_dtorCount > 0);
      CHECK(IntComponent::m_dtorCount == IntComponent::m_ctorCount);

      RESET_CTOR_AND_DTOR_COUNT();
      arr.resize(100);
      arr.resize(300);

      CHECK(arr.size() == 300);

      // access all VSOs to populate their respective virtual pointers
      for(core_conts::Array<int_comp_vso>::iterator
          itr = arr.begin(), itrEnd = arr.end(); itr != itrEnd; ++itr)
      {
        int_comp_vso::pointer temp = itr->get();
      }
      // all temp pointers are destroyed and therefore we are no longer holding
      // on to any invalid pointers, the following resize and access of
      // pointers should work properly
      arr.resize(3000);
      CHECK(arr.size() == 3000);

      // access all VSOs to populate their respective virtual pointers
      for(core_conts::Array<int_comp_vso>::iterator
          itr = arr.begin(), itrEnd = arr.end(); itr != itrEnd; ++itr)
      {
        int_comp_vso::pointer temp = itr->get();
      }

      arr.clear();
      CHECK(IntComponent::m_ctorCount > 0);
      CHECK(IntComponent::m_dtorCount > 0);
      CHECK(IntComponent::m_dtorCount == IntComponent::m_ctorCount);
    }
  }

  TEST_CASE("core/smart_ptr/VirtualStackObject/ToVirtualPtr", "")
  {
    int_vso a(10);
    int_vso::pointer aVptr = ToVirtualPtr(a);
    CHECK( (aVptr == a.get()) );
  }

  TEST_CASE("core/smart_ptr/VirtualStackObject/algorithms", "")
  {
    SECTION("Compare::VirtualPtr", "")
    {
      typedef core_conts::Array<int_vso>      int_vso_cont;

      int_vso_cont intArray;
      intArray.push_back(int_vso(0));
      intArray.push_back(int_vso(1));
      intArray.push_back(int_vso(2));

      int_vso_cont::iterator itr =
        core::find_if_all(intArray,
          core_sptr::algos::compare::virtual_stack_object::
          MakeWithVirtualPtr(intArray[1].get()) );

      CHECK(*(*itr) == 1);

      int_vso temp(2);
      // even the number 2 exists in the container of VSOs, we are matching
      // against the VSO pointers and NOT the values
      itr =
        core::find_if_all(intArray,
          core_sptr::algos::compare::virtual_stack_object::
          MakeWithVirtualPtr(temp.get()) );

    }
  }
}