#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocVirtualPointer.h>
#include <tlocCore/smart_ptr/tlocVirtualPointer.inl.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace TestingVirtualPtr
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  using tloc::core::smart_ptr::VirtualPointer;
  using tloc::core::smart_ptr::SharedPtr;

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
  bool CheckUseCount(const T_VirtualPointer& , tl_long , core_cfg::p_build_config::Release)
  { return true; }

  // ///////////////////////////////////////////////////////////////////////
  // tests

  TEST_CASE("core/smart_ptr/VirtualPointer/ctors", "")
  {
    SECTION("default ctor", "")
    {
      VirtualPointer<int> p;
      CHECK( CheckUseCount(p, 0, core_cfg::BuildConfig::build_config_type()) );
      CHECK( (p.get() == nullptr) );
    }

    SECTION("nullptr ctor", "")
    {
      VirtualPointer<int> p(nullptr);
      CHECK( CheckUseCount(p, 0, core_cfg::BuildConfig::build_config_type()) );
      CHECK( (p.get() == nullptr) );
    }

    SECTION("raw pointer ctor", "")
    {
      int* a = new int();

      {
        VirtualPointer<int> p(a);
        CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );
        CHECK( (p.get() == a) );

        //delete a; // should fire an assertion
      }

      delete a; // no assertion should be fired
    }

    SECTION("this_type copy ctor", "")
    {
      int* a = new int();

      VirtualPointer<int> p(a);
      CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );

      {
        VirtualPointer<int> pLocal(p);
        CHECK( CheckUseCount(p, 2, core_cfg::BuildConfig::build_config_type()) );
        CHECK( CheckUseCount(pLocal, 2, core_cfg::BuildConfig::build_config_type()) );
        CHECK( (p.get() == pLocal.get() && p.get() == a) );
      }

      CHECK( CheckUseCount(p, 1, core_cfg::BuildConfig::build_config_type()) );
      p.reset();

      delete a;
    }

    SECTION("VirtualPointer<T_Other> copy ctor", "")
    {
      SharedStruct* s = new SharedStruct(10);

      VirtualPointer<SharedStruct> p(s);

      {
        VirtualPointer<BaseStruct> pLocal(p);
      }

      CHECK( p->m_value == 10);
      p.reset();

      delete s;
    }

    SECTION("SharedPtr<> copy ctor", "")
    {
      SharedPtr<int> sptr(new int(10));

      {
        VirtualPointer<int> p(sptr);
        // sptr.reset(); // should throw an assertion
      }

      sptr.reset();
    }
  }

  TEST_CASE("core/smart_ptr/VirtualPointer/operators", "")
  {
    SECTION("operator=(this_type)", "")
    {
      VirtualPointer<int> vp;
      vp = VirtualPointer<int>(new int(10));

      CHECK(*vp == 10);
    }

    SECTION("operator=(SharedPtr)", "")
    {
      SharedPtr<int>      sp(new int(20));
      VirtualPointer<int> vp;
      vp = sp;

      CHECK(*vp == 20);

      VirtualPointer<int> vp2; // vp2 needs to be reset before sp2 deletes when
                               // it goes out of scope
      SharedPtr<int>      sp2(new int(30));
      vp2 = sp2;

      vp2.reset();

      // No crash should occur when sp2 goes out of scope and deletes its raw
      // pointer
    }
  }

  TEST_CASE("core/smart_ptr/VirtualPointer/reset", "")
  {
    SharedStruct::m_numCtors = 0;
    SharedStruct::m_numDtors = 0;

    SharedStruct s1(50), s2(20);
    CHECK(SharedStruct::m_numCtors == 2);

    VirtualPointer<SharedStruct> vp(&s1);
    CHECK(vp->m_value == 50);

    vp.reset(&s2);
    CHECK(vp->m_value == 20);

    vp.reset();

    CHECK(SharedStruct::m_numCtors == 2);
    CHECK(SharedStruct::m_numDtors == 0);
  }

  TEST_CASE("core/smart_ptr/VirtualPointer/casts", "")
  {
    SECTION("static_pointer_cast<>()", "")
    {
      SharedStruct localVar(2);

      VirtualPointer<BaseStruct> vp1(&localVar);

      VirtualPointer<SharedStruct> vp2 = core_sptr::static_pointer_cast<SharedStruct>(vp1);
      CHECK(vp2->m_value == 2);

      CheckUseCount(vp2, 2, core_cfg::BuildConfig::build_config_type());
    }

    SECTION("static_pointer_cast<>()", "")
    {
      SharedStruct localVar(2);

      const VirtualPointer<const SharedStruct> vp1(&localVar);

      VirtualPointer<SharedStruct> vp2 = core_sptr::const_pointer_cast<SharedStruct>(vp1);
      CHECK(vp2->m_value == 2);

      CheckUseCount(vp2, 2, core_cfg::BuildConfig::build_config_type());
    }
  }
}