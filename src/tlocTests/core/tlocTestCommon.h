#ifndef TLOC_TEST_CORE_COMMON_H
#define TLOC_TEST_CORE_COMMON_H

#include <tlocCore/tlocBase.h>
#if defined (__APPLE__) && defined (__OBJC__)
# import <Foundation/Foundation.h>
#endif

#include <catch.hpp>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypes.h>

#include "tlocAssetsPath.h"

#define TLOC_TEST_ASSERT\
  TLOC_ASSERT_THROWS();\
  bool exceptionThrown = false;\
  try

#define TLOC_TEST_ASSERT_CHECK()\
  catch(const tloc::core::assert::exception::Assert&)\
  {\
    exceptionThrown = true;\
  }\
  CHECK(exceptionThrown);\
  TLOC_ASSERT_DOES_NOT_THROW()


#endif