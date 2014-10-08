#ifndef _TLOC_CORE_PLATFORM_PLATFORM_SPECIFIC_INCLUDES
#define _TLOC_CORE_PLATFORM_PLATFORM_SPECIFIC_INCLUDES

// -----------------------------------------------------------------------
// Windows
#if defined(TLOC_OS_WIN)
#ifndef NOMINMAX
  #define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif

#endif