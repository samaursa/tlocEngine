#ifndef TLOC_TEST_CORE_COMMON_H
#define TLOC_TEST_CORE_COMMON_H

#include <tlocCore/tlocBase.h>
#if defined (__APPLE__) && defined (__OBJC__)
# import <Foundation/Foundation.h>
#endif

#include <catch.hpp>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/tlocAssertCustomBreak.h>

#include "tlocAssetsPath.h"

namespace tloc { namespace tests {

  namespace exception {

    class Assert {};

  };

  class ThrowOnBreak
    : public tloc::core::assert::CustomBreak
  {
  public:
    ThrowOnBreak();
    
    void Break() const;
  };

  const core::assert::CustomBreak* GetThrowOnBreak();

};};

// -----------------------------------------------------------------------
// TLOC_TEST_ASSERT and TLOC_TEST_ASSERT_CHECK are used to test firing
// of assertions without invoking the debugger. In Release, we do not
// want such code to run because it will result in undefined behavior.

#if TLOC_ASSERTS_DEFINED == 1 && defined(TLOC_CPPUNWIND_ENABLED)
#define TLOC_TEST_ASSERT \
do {\
    tloc::core::assert::SetAssertCustomBreak(tloc::tests::GetThrowOnBreak());\
    bool exceptionThrown = false;\
    try

#define TLOC_TEST_ASSERT_CHECK()\
  catch(const tloc::tests::exception::Assert&)\
  {\
    exceptionThrown = true;\
  }\
  CHECK(exceptionThrown);\
  tloc::core::assert::SetAssertDefaultBreak();\
  } while((void)0, 0)

#define TLOC_TEST_ASSERT_REQUIRE()\
  catch(const tloc::tests::exception::Assert&)\
  {\
    exceptionThrown = true;\
  }\
  REQUIRE(exceptionThrown);\
  tloc::core::assert::SetAssertDefaultBreak();\
  } while((void)0, 0)
#else

#define TLOC_TEST_ASSERT \
do {\
  bool alwaysFalse = tloc::core::assert::AlwaysReturnFalse();\
  if (alwaysFalse)

#define TLOC_TEST_ASSERT_CHECK() } while((void)0, 0)

#define TLOC_TEST_ASSERT_REQUIRE() } while((void)0, 0)

#endif



#endif