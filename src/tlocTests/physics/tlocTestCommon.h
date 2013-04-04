#ifndef TLOC_TEST_COMMON_H
#define TLOC_TEST_COMMON_H

#include <tlocCore/tlocBase.h>
#if defined (__APPLE__) && defined (__OBJC__)
# import <Foundation/Foundation.h>
#endif

#include <catch.hpp>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypes.h>

extern const char* g_assetPath;

#endif