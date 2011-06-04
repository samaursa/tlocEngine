#pragma once

#ifndef TLOC_BASE_H
#define TLOC_BASE_H

//////////////////////////////////////////////////////////////////////////
// Common macros
#define _CRT_SECURE_NO_WARNINGS

//////////////////////////////////////////////////////////////////////////
// For DLL support

#ifndef TLOC_STATIC_LIB
#if defined TLOC_DLL_EXPORT
#define tlocDLL __declspec(dllexport)
#else
#define tlocDLL __declspec(dllimport)
#endif
#else
#define tlocDLL
#endif

//////////////////////////////////////////////////////////////////////////
// Configurations

#if !defined(TLOC_DEBUG) && !defined(TLOC_RELEASE) && !defined(TLOC_RELEASE_DEBUGINFO)
#error "Project must #define TLOC_DEBUG, TLOC_RELEASE or TLOC_RELEASE_DEBUGINFO"
#elif defined(TLOC_DEBUG)
#if defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DEBUGINFO)
#error "Project has mixed configurations!"
#endif
#elif defined(TLOC_RELEASE)
#if defined(TLOC_DEBUG) || defined(TLOC_RELEASE_DEBUGINFO)
#error "Project has mixed configurations!"
#endif
#elif defined(TLOC_RELEASE_DEBUGINFO)
#if defined(TLOC_DEBUG) || defined(TLOC_RELEASE)
#error "Project has mixed configurations!"
#endif
#endif

//////////////////////////////////////////////////////////////////////////
// Inlining

#define TLOC_INLINE inline

#define TLOC_FORCE_INLINE __forceinline
#define TL_FI TLOC_FORCE_INLINE

//////////////////////////////////////////////////////////////////////////
// FwTypes

#include "tlocTypes.h"

//////////////////////////////////////////////////////////////////////////
// Assertions

#include <stlsoft/stlsoft.h>

// Deprecated macros
#pragma deprecated("FWASSERT") // Consider using TLOC_ASSERT
#pragma deprecated("FwAssert") // Consider using TLOC_ASSERT

#if defined(TLOC_DEBUG) || defined(TLOC_RELEASE_DEBUGINFO)
#define FwAssert(_Expression, _Msg) (void)( (!!(_Expression)) || \
  (_wassert(_Msg, _CRT_WIDE(__FILE__), __LINE__), 0) )
#define FWASSERT(_Expression, _Msg) (void)( (!!(_Expression)) || \
  (_wassert(_CRT_WIDE(_Msg), _CRT_WIDE(__FILE__), __LINE__), 0) )
#define TLOC_ASSERT(_Expression, _Msg) STLSOFT_MESSAGE_ASSERT(_Msg, _Expression)

#else
#define FwAssert(_Expression, _Msg)
#define FWASSERT(_Expression, _Msg)
#define TLOC_ASSERT(_Expression, _Msg)
#endif

//////////////////////////////////////////////////////////////////////////
// Logging

#define LOG_ERRORBOX ""
#define LOG_CHECKBOX ""

#endif