#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocAllocators.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace TestingAllocators
{
  using namespace tloc;
  using namespace core::memory::tracking::priv;

  // -----------------------------------------------------------------------
  // complex inheritance test classes

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
    int d; 
  };

  class Derived
    : public Base2
  { 
  public:
    int e; 
  };

  // -----------------------------------------------------------------------
  // helper functions that get selected at compile time

  template <typename T, typename T_BuildConfig>
  void
    IsMemoryAddressTracked( T* a_memAddress, bool a_expectedResult, 
                            T_BuildConfig )
  {
    if (a_expectedResult)
    { CHECK( DoIsMemoryAddressTracked( (void*) a_memAddress ) ); }
    else
    { CHECK_FALSE( DoIsMemoryAddressTracked( (void*) a_memAddress ) ); }
  }

  template <typename T, typename T_BuildConfig>
  void
    IsPointerToValidMemoryAddress( T* a_ptrAddress, bool a_expectedResult, 
                                   T_BuildConfig )
  {
    if (a_expectedResult)
    { CHECK( DoIsPointerToValidMemoryAddress( (void*) a_ptrAddress ) ); }
    else
    { CHECK_FALSE( DoIsPointerToValidMemoryAddress( (void*) a_ptrAddress ) ); }

  }

  template <typename T, typename T_BuildConfig>
  void
    IsNumberOfPointerToMemoryAddresses( T* a_memAddress, size_t a_expectedNumber, 
                                        T_BuildConfig)
  {
    CHECK( DoGetNumberOfPointersToMemoryAddress( (void*) a_memAddress ) == a_expectedNumber );
  }

  template <typename T>
  void
    IsMemoryAddressTracked( T* a_memAddress, bool , 
                            core_cfg::p_build_config::Release)
  {
    CHECK( DoIsMemoryAddressTracked( (void*) a_memAddress ) );
  }

  template <typename T>
  void
    IsPointerToValidMemoryAddress( T* a_ptrAddress, bool , 
                                   core_cfg::p_build_config::Release )
  {
    CHECK( DoIsPointerToValidMemoryAddress( (void*) a_ptrAddress ) );
  }

  template <typename T, typename T_BuildConfig>
  void
    IsNumberOfPointerToMemoryAddresses( T* a_memAddress, size_t , 
                                        core_cfg::p_build_config::Release )
  { 
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*) a_memAddress ) == 0);
  }

  // -----------------------------------------------------------------------
  // tests

  core_cfg::BuildConfig::build_config_type  bc;

  const tl_size g_repCount = 10;

  TEST_CASE("core/memory/priv/MemoryTracker", "")
  {
    SECTION("Tracking/Untracking memory addresses", "")
    {
      for (tl_size i = 0; i < g_repCount; ++i)
      {
        tl_int* rawPtr = new tl_int( 10 );

        DoTrackMemoryAddress( (void*) rawPtr );
        IsMemoryAddressTracked( rawPtr, true, bc );

        DoUntrackMemoryAddress( (void*) rawPtr );
        IsMemoryAddressTracked( rawPtr, false, bc );

        delete rawPtr;
      }
    }

    SECTION("Tracking connected memory addresses", "")
    {
      for (tl_size i = 0; i < g_repCount; ++i)
      {
        Derived* d = new Derived();
        Base* b = new Base();
        Base* b2 = new Derived();

        DoTrackMemoryAddress( (void*)d );
        DoTrackMemoryAddress( (void*)b );
        DoTrackMemoryAddress( (void*)b2 );

        Base*     b_d = d;
        Derived*  d_b = static_cast<Derived*>( b2 );

        if ( (tl_uintptr) b_d != (tl_uintptr) d )
        {
          DoTrackConnectedMemoryAddress( (void*) d, (void*) b_d );
        }

        if ( (tl_uintptr) d_b != (tl_uintptr) b2 )
        {
          DoTrackConnectedMemoryAddress( (void*) b2, (void*) d_b );
        }

        DoUntrackMemoryAddress( (void*)d );
        DoUntrackMemoryAddress( (void*)b );
        DoUntrackMemoryAddress( (void*)b2 );

        delete d;
        delete b;
        delete b2;
      }
    }
  }
};