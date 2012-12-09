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

//////////////////////////////////////////////////////////////////////////
// Macros

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

// Convenience Macro

#if defined (TLOC_WIN32) || defined (TLOC_WIN64)
# define TLOC_OS_WIN
#endif

#endif
