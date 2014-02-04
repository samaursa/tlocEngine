#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

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

  TLOC_TYPEDEF_VIRTUAL_PTR(SharedStruct, shared_struct);
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(SharedStruct);

  // ///////////////////////////////////////////////////////////////////////
  // generic test functions for different builds (Debug/Release)

  template <typename T_VirtualPointer, typename T_BuildConfig>
  bool CheckUseCount(const T_VirtualPointer& a_vp, tl_long a_expectedCount, T_BuildConfig)
  { return a_vp.use_count() == a_expectedCount; }

  template <typename T_VirtualPointer>
  bool CheckUseCount(const T_VirtualPointer& a_vp, tl_long , core_cfg::p_build_config::Release)
  {
    // In Release, the use_count of VPs is always 1
    return a_vp.use_count() == 1;
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

      {
        VirtualPtr<int> p(a);
        CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );
        CHECK( (p.get() == a) );

        //delete a; // should fire an assertion
      }

      delete a; // no assertion should be fired
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
      p.reset();

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
      p.reset();

      delete s;
    }

    SECTION("SharedPtr<> copy ctor", "")
    {
      SharedPtr<int> sptr(new int(10));

      {
        VirtualPtr<int> p(sptr);
        // sptr.reset(); // should throw an assertion
      }

      sptr.reset();
    }

    SECTION("UniquePtr<> copy ctor", "")
    {
      UniquePtr<int> sptr(new int(10));

      {
        VirtualPtr<int> p(sptr);
        // sptr.reset(); // should throw an assertion
      }

      sptr.reset();
    }
  }

  TEST_CASE("core/smart_ptr/VirtualPtr/operators", "")
  {
    SECTION("operator=(this_type)", "")
    {
      VirtualPtr<int> vp;
      vp = VirtualPtr<int>(new int(10));

      CHECK(*vp == 10);
    }

    SECTION("operator=(SharedPtr)", "")
    {
      SharedPtr<int>      sp(new int(20));
      VirtualPtr<int> vp;
      vp = sp;

      CHECK(*vp == 20);

      VirtualPtr<int> vp2; // vp2 needs to be reset before sp2 deletes when
                               // it goes out of scope
      SharedPtr<int>      sp2(new int(30));
      vp2 = sp2;

      vp2.reset();

      // No crash should occur when sp2 goes out of scope and deletes its raw
      // pointer
    }

    SECTION("operator=(UniquePtr)", "")
    {
      UniquePtr<int>      sp(new int(20));
      VirtualPtr<int> vp;
      vp = sp;

      CHECK(*vp == 20);

      VirtualPtr<int> vp2; // vp2 needs to be reset before sp2 deletes when
                               // it goes out of scope
      UniquePtr<int>      sp2(new int(30));
      vp2 = sp2;

      vp2.reset();

      // No crash should occur when sp2 goes out of scope and deletes its raw
      // pointer
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
    SECTION("static_pointer_cast<>()", "")
    {
      SharedStruct localVar(2);

      VirtualPtr<BaseStruct> vp1(&localVar);

      VirtualPtr<SharedStruct> vp2 = core_sptr::static_pointer_cast<SharedStruct>(vp1);
      CHECK(vp2->m_value == 2);

      CheckUseCount(vp2, 2, core_cfg::BuildConfig::build_config_type());
    }

    SECTION("static_pointer_cast<>()", "")
    {
      SharedStruct localVar(2);

      const VirtualPtr<const SharedStruct> vp1(&localVar);

      VirtualPtr<SharedStruct> vp2 = core_sptr::const_pointer_cast<SharedStruct>(vp1);
      CHECK(vp2->m_value == 2);

      CheckUseCount(vp2, 2, core_cfg::BuildConfig::build_config_type());
    }
  }
}