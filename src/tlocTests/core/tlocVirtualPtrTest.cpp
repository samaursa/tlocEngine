#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace TestingVirtualPtr
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  using tloc::core::smart_ptr::VirtualPtr;
  using tloc::core::smart_ptr::SharedPtr;
  using tloc::core::smart_ptr::UniquePtr;

  struct BaseStruct
  { };

  struct SharedStruct
    : public BaseStruct
  {
    SharedStruct(tl_int a_value) : m_value(a_value)
    { ++m_numCtors; }

    ~SharedStruct()
    { ++m_numDtors; }

    tl_int m_value;

    static tl_int m_numCtors;
    static tl_int m_numDtors;
  };

  tl_int SharedStruct::m_numCtors;
  tl_int SharedStruct::m_numDtors;

  // ///////////////////////////////////////////////////////////////////////
  // generic test functions for different builds (Debug/Release)

  template <typename T_VirtualPointer, typename T_BuildConfig>
  bool CheckUseCount(const T_VirtualPointer& a_vp, tl_long a_expectedCount, T_BuildConfig)
  { return a_vp.use_count() == a_expectedCount; }

  template <typename T_VirtualPointer>
  bool CheckUseCount(const T_VirtualPointer& a_vp, tl_long , core_cfg::p_build_config::Release)
  {
    // In Release, the use_count of VPs is always 1
    return a_vp ? a_vp.use_count() == 1 : a_vp.use_count() == 0;
  }

  // ///////////////////////////////////////////////////////////////////////
  // tests

  TEST_CASE("core/smart_ptr/VirtualPtr/ctors", "")
  {
    SECTION("default ctor", "")
    {
      VirtualPtr<int> p;
      CHECK( CheckUseCount(p, 0, core_cfg::BuildConfig::build_config_type()) );
      CHECK( (p.get() == nullptr) );
    }

    SECTION("nullptr ctor", "")
    {
      VirtualPtr<int> p(nullptr);
      CHECK( CheckUseCount(p, 0, core_cfg::BuildConfig::build_config_type()) );
      CHECK( (p.get() == nullptr) );
    }

    SECTION("raw pointer ctor", "")
    {
      int* a = new int();

      VirtualPtr<int> p(a);
      CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );
      CHECK( (p.get() == a) );

      delete a;

      TLOC_TEST_ASSERT
      {
        a = p.get();
      }
      TLOC_TEST_ASSERT_CHECK();
    }

    SECTION("raw pointer ctor", "")
    {
      int* a = new int[2];

      VirtualPtr<int> p(a);
      CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );
      CHECK( (p.get() == a) );

      delete[] a;

      TLOC_TEST_ASSERT
      {
        a = p.get();
      }
      TLOC_TEST_ASSERT_CHECK();
    }

    SECTION("this_type copy ctor", "")
    {
      int* a = new int();

      VirtualPtr<int> p(a);
      CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );

      {
        VirtualPtr<int> pLocal(p);
        CHECK( CheckUseCount(p, 2, core_cfg::BuildConfig::build_config_type()) );
        CHECK( CheckUseCount(pLocal, 2, core_cfg::BuildConfig::build_config_type()) );
        CHECK( (p.get() == pLocal.get() && p.get() == a) );
      }

      CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );

      delete a;
    }

    SECTION("VirtualPtr<T_Other> copy ctor", "")
    {
      SharedStruct* s = new SharedStruct(10);

      VirtualPtr<SharedStruct> p(s);

      {
        VirtualPtr<BaseStruct> pLocal(p);
      }

      CHECK( p->m_value == 10);

      delete s;
    }

    SECTION("SharedPtr<> copy ctor", "")
    {
      SharedPtr<int> sptr(new int(10));

      VirtualPtr<int> p(sptr);
      CHECK(*p == 10);

      sptr.reset();

      TLOC_TEST_ASSERT
      { *p.get(); }
      TLOC_TEST_ASSERT_CHECK();
    }

    SECTION("UniquePtr<> copy ctor", "")
    {
      UniquePtr<int> sptr(new int(10));

      VirtualPtr<int> p(sptr);
      CHECK(*p == 10);

      sptr.reset();

      TLOC_TEST_ASSERT
      { *p.get(); }
      TLOC_TEST_ASSERT_CHECK();
    }
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/operators", "")
  {
    SECTION("operator=(this_type)", "")
    {
      VirtualPtr<int> vp;
      vp = VirtualPtr<int>(new int(10));

      CHECK(*vp == 10);
      core_sptr::algos::virtual_ptr::DeleteAndReset()(vp);

      vp.reset(new int(20));
      CHECK(*vp == 20);
      core_sptr::algos::virtual_ptr::DeleteAndReset()(vp);
    }

    SECTION("operator=(SharedPtr)", "")
    {
      SharedPtr<int>      sp(new int(20));
      VirtualPtr<int>     vp;

      vp = sp;
      CHECK(*vp == 20);

      VirtualPtr<int>     vp2;
      SharedPtr<int>      sp2(new int(30));

      vp2 = sp2;
      CHECK(*vp2.get() == 30);

      sp2.reset();

      TLOC_TEST_ASSERT
      { *vp2.get(); }
      TLOC_TEST_ASSERT_CHECK();
    }

    SECTION("operator=(UniquePtr)", "")
    {
      UniquePtr<int>      sp(new int(20));
      VirtualPtr<int>     vp;

      vp = sp;
      CHECK(*vp == 20);

      VirtualPtr<int>     vp2;
      UniquePtr<int>      sp2(new int(30));

      vp2 = sp2;
      CHECK(*vp2.get() == 30);

      sp2.reset();

      TLOC_TEST_ASSERT
      { *vp2.get(); }
      TLOC_TEST_ASSERT_CHECK();
    }

    SECTION("operator==", "")
    {
      VirtualPtr<int> vp;
      CHECK( (vp == nullptr) );
      CHECK_FALSE( (vp != nullptr) );

      int temp = 10;
      vp.reset(&temp);
      CHECK( (vp != nullptr) );
      CHECK( (nullptr != vp) );

      vp.reset();
      CHECK( (vp == nullptr) );
      CHECK( (nullptr == vp) );
    }
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/reset", "")
  {
    SharedStruct::m_numCtors = 0;
    SharedStruct::m_numDtors = 0;

    SharedStruct s1(50), s2(20);
    CHECK(SharedStruct::m_numCtors == 2);

    VirtualPtr<SharedStruct> vp(&s1);
    CHECK(vp->m_value == 50);

    vp.reset(&s2);
    CHECK(vp->m_value == 20);

    vp.reset();

    CHECK(SharedStruct::m_numCtors == 2);
    CHECK(SharedStruct::m_numDtors == 0);
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/casts", "")
  {
    //SECTION("static_pointer_cast<>()", "")
    {
      SharedStruct localVar(2);

      VirtualPtr<BaseStruct> vp1(&localVar);

      VirtualPtr<SharedStruct> vp2 = core_sptr::static_pointer_cast<SharedStruct>(vp1);
      CHECK(vp2->m_value == 2);

      CheckUseCount(vp2, 2, core_cfg::BuildConfig::build_config_type());
    }

    //SECTION("const_pointer_cast<>()", "")
    {
      SharedStruct localVar(2);

      const VirtualPtr<const SharedStruct> vp1(&localVar);

      VirtualPtr<SharedStruct> vp2 = core_sptr::const_pointer_cast<SharedStruct>(vp1);
      CHECK(vp2->m_value == 2);

      CheckUseCount(vp2, 2, core_cfg::BuildConfig::build_config_type());
    }
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/containers", "")
  {
    core_conts::Array<VirtualPtr<int> > vptrContainer;
    int a = 10;
    vptrContainer.resize(100, VirtualPtr<int>(&a));
    vptrContainer.resize(500,VirtualPtr<int>(&a));
    vptrContainer.resize(1000, VirtualPtr<int>(&a));
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/Algorithms", "")
  {
    core_conts::Array<VirtualPtr<int> > vptrContainer;

    for (tl_int i = 0; i < 10; ++i)
    {
      vptrContainer.push_back(VirtualPtr<int>(new int(10)) );
    }

    core::for_each_all(vptrContainer,
                       core_sptr::algos::virtual_ptr::DeleteAndReset());
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/GetUseCount", "")
  {
    VirtualPtr<tl_int> vp;
    CHECK(GetUseCount(vp) == 0);

    tl_int temp(10);
    vp.reset(&temp);
    CHECK(GetUseCount(vp) == 1);
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/ToVirtualPtr", "")
  {
    SharedPtr<tl_int>                                   sptr(new tl_int(10));
    UniquePtr<tl_int>                                   uptr(new tl_int(20));
    core_sptr::VirtualStackObjectBase_TI<tl_int>        vso; *vso = 30;
    const core_sptr::VirtualStackObjectBase_TI<tl_int>  constVso = vso;

    //SECTION("ToConvert(SharedPtr)", "")
    {
      VirtualPtr<tl_int> vp = core_sptr::ToVirtualPtr(sptr);
      CHECK(*vp == 10);
    }

    //SECTION("ToConvert(UniquePtr)", "")
    {
      VirtualPtr<tl_int> vp = core_sptr::ToVirtualPtr(uptr);
      CHECK(*vp == 20);
    }

    //SECTION("ToConvert(VirtualStackObject)", "")
    {
      VirtualPtr<tl_int> vp = core_sptr::ToVirtualPtr(vso);
      CHECK(*vp == 30);
    }

    //SECTION("ToConvert(VirtualStackObject)", "")
    {
      VirtualPtr<const tl_int> vp = core_sptr::ToVirtualPtr(constVso);
      CHECK(*vp == 30);
    }

    //SECTION("ToConvert(VirtualPtr)", "")
    {
      VirtualPtr<const tl_int> vp = core_sptr::ToVirtualPtr(constVso);
      vp = core_sptr::ToVirtualPtr(vp);
      CHECK(*vp == 30);
    }
  }

  // -----------------------------------------------------------------------

  class Foo1
  {
  public:
    virtual ~Foo1() {}
  };

  class Foo2
  {
  public:
    virtual ~Foo2() {}
  };

  class Base
    : public Foo1
  {
  public:
    virtual ~Base() {}
    int c;
  };

  class Base2
    : public Foo2
    , public Base
  {
  public:
    virtual ~Base2() {}
    int d;
  };

  class Derived
    : public Base2
  {
  public:
    virtual ~Derived() {}
    int e;
  };

  template <typename T_BuildConfig>
  void DoCheckVPtrCount(void* a_pointer, tl_size a_count, T_BuildConfig)
  {
    CHECK( a_count ==
           core_mem::tracking::priv::DoGetNumberOfPointersToMemoryAddress( a_pointer ) );
  }

  void DoCheckVPtrCount(void* , tl_size , core_cfg::p_build_config::Release)
  { }

  template <typename T_BuildConfig>
  void DoCheckMemoryAddressIsTracked(void* a_pointer, bool a_expected, T_BuildConfig)
  {
    CHECK( core_mem::tracking::priv::DoIsMemoryAddressTracked(a_pointer) == a_expected);
  }

  void DoCheckMemoryAddressIsTracked(void* , bool , core_cfg::p_build_config::Release)
  { }

  TEST_CASE("core/smart_ptr/VirtualPtr/MultipleInheritance",
    "In certain cases with multiple inheritance where the base class may be "
    "ambiguous, the pointer addresses no longer match when casting from derived "
    "to base. In this case, the vptr fails in a way that is difficult to track "
    "down. This 'bug' has been fixed and these are the tests for it.")
  {
    core_sptr::VirtualStackObjectBase_TI<Derived> dStack;

    DoCheckVPtrCount((void*)&*dStack, 0, core_cfg::BuildConfig::build_config_type());

    core_sptr::VirtualPtr<Derived>  d = dStack.get();

    DoCheckVPtrCount((void*)&*dStack, 1, core_cfg::BuildConfig::build_config_type());

    // Due to the multiple inherited hierarchy, the cast results in a different
    // pointer address. VirtualPtr and SmartPtrTracker compensate for this.
    core_sptr::VirtualPtr<Base> b(d);
    core_sptr::VirtualPtr<Base> bb(d);

    // These casts are independent and will ADD to the total ref count of
    // the original pointer in the SmartPtrTracker.
    DoCheckVPtrCount((void*)&*dStack, 3, core_cfg::BuildConfig::build_config_type());

    d.reset(); // does not change anything due to the cached pointer in VSO

    // b and bb counted as 2 references + 1 in VSO
    DoCheckVPtrCount((void*)&*dStack, 3, core_cfg::BuildConfig::build_config_type());
    b.reset(); // should not crash

    // bb counted as 1 ref
    DoCheckVPtrCount((void*)&*dStack, 2, core_cfg::BuildConfig::build_config_type());

    bb.reset();
    DoCheckVPtrCount((void*)&*dStack, 1, core_cfg::BuildConfig::build_config_type());

    dStack = core_sptr::VirtualStackObjectBase_TI<Derived>();
    DoCheckVPtrCount((void*)&*dStack, 0, core_cfg::BuildConfig::build_config_type());
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/force tracking", "Bug fix in d5d52a045a35")
  {
    /*
    A VirtualPtr may track an address that is not already tracked but then it
    has no mechanism to untrack that address. This is now fixed by untracking
    the memory address if it is marked as such.
    */

    tl_int varOnStack;
    DoCheckMemoryAddressIsTracked((void*)&varOnStack, false,
      core_cfg::BuildConfig::build_config_type());

    {
      core_sptr::VirtualPtr<tl_int> vptr(&varOnStack);
      DoCheckMemoryAddressIsTracked((void*)&varOnStack, true,
        core_cfg::BuildConfig::build_config_type());
    }

    // now we force track the address, this should not crash
    core_mem::tracking::priv::DoTrackMemoryAddress(&varOnStack);

    // and then untrack
    core_mem::tracking::priv::DoUntrackMemoryAddress(&varOnStack);
  }
}


TLOC_TYPEDEF_VIRTUAL_PTR(TestingVirtualPtr::SharedStruct, shared_struct);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(TestingVirtualPtr::SharedStruct);
