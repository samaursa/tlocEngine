//
//  tlocPlatformDefines.h
//  tlocCore
//
//  Created by Skopworks Inc on 12-08-16.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TLOC_PLATFORM_DEFINES_H
#define TLOC_PLATFORM_DEFINES_H

#ifdef __APPLE__
# include "TargetConditionals.h"
#endif

// ///////////////////////////////////////////////////////////////////////
// playform macros

#if defined(_WIN64)
# define TLOC_WIN64
#elif defined(WIN32) || defined(_WIN32)
# define TLOC_WIN32
#elif defined(TARGET_OS_IPHONE)
# define TLOC_OS_IPHONE
#elif defined(TARGET_OS_MAC)
# define TLOC_OS_MAC
#elif defined(__linux__)
# define TLOC_OS_LINUX
#else
# error "Unsupported Platform"
#endif

// ///////////////////////////////////////////////////////////////////////
// compiler macros

#if defined(_MSC_VER)
# define TLOC_COMPILER_VISUAL_CPP
#elif defined (__GNUC__)
# define TLOC_COMPILER_GCC
#elif defined (__clang__)
# define TLOC_COMPILER _CLANG
#endif

// Convenience Macro

#if defined (TLOC_WIN32) || defined (TLOC_WIN64)
# define TLOC_OS_WIN
#endif

#endif
