#if defined (__APPLE__) && defined (__OBJC__)
# import <Foundation/Foundation.h>
#endif

#include <tlocCore/tlocBase.h>
#include <tlocCore/memory/tlocLinkMe.cpp>

#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocCore/logging/tlocLogger.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("", "")
{
  tloc::graphics::GetLogger().SetSeverity(tloc::core_log::Log_I::k_warning);

  std::cout << "Testing tlocGraphics..." << std::endl;
}