#pragma once

#ifndef TLOC_BASE_H
#define TLOC_BASE_H

#include <assert.h>

//////////////////////////////////////////////////////////////////////////
// Common macros
#define _CRT_SECURE_NO_WARNINGS 1

//////////////////////////////////////////////////////////////////////////
// TLOC Engine No source
//
// The following macro can be commented out when compiling the engine which
// allows safe removal of inline files altogether

#ifndef TLOC_NO_SOURCE
  #define TLOC_FULL_SOURCE
#endif

//------------------------------------------------------------------------
// The following macros can be enabled to increase the size of the template
// instantiations (that many more template types will be instantiated).
// For example, with TLOC_TEMPLATE_TYPES_SIZE_20 defined, Table<>,
// Matrix<>, Vector<> etc. classes will be instantiated such that they have
// have a size of at least 20 rows and cols (if any). Note that for types
// such as Table<> this will require a large type generation.
//
// NOTE : Only useful if giving out the code without source
// NOTE2: If you want size to be 20, you must also define SIZE_15

#ifndef TLOC_FULL_SOURCE
//#define TLOC_TEMPLATE_TYPES_SIZE_15
//#define TLOC_TEMPLATE_TYPES_SIZE_20
#endif

//////////////////////////////////////////////////////////////////////////
// Platform specific

#if defined(_WIN32) || defined(WIN32)
# ifndef WIN32
#   define WIN32
# endif
# ifndef _WIN32
#   define _WIN32
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// Compiler specific

#if defined(_MSC_VER)

  //------------------------------------------------------------------------
  // Compiler specific checks
# ifndef TLOC_DISABLE_ALL_COMPILER_CHECKS
    //------------------------------------------------------------------------
    // Check for exception handling
#   if defined(_CPPUNWIND) && !defined(TLOC_ENABLE_CPPUNWIND)
#     error "Exception handling must be disabled for this project."
#   endif
    //------------------------------------------------------------------------
    // Check for RTTI
#   if defined(_CPPRTTI) && !defined(TLOC_ENABLE_CPPRTTI)
#     error "RTTI must be disabled for this project."
#   endif
# endif

  //------------------------------------------------------------------------
  // Optimizations
# ifndef TLOC_DEBUG
#   pragma inline_recursion( on )
#   pragma auto_inline( on )
# endif

#endif

//////////////////////////////////////////////////////////////////////////
// Memory
//
// Notes: The default memory allocator used is the nedmalloc which is a
// derivation of doug lea malloc:
//
// http://www.nedprod.com/programs/portable/nedmalloc/
//
// If all of the following macros are commented out, the system defaults
// to using the definitions contained in <memory.h>. To enable seamless
// transitions, there are helper macros defined in <tlocMemory.h>
//
// Supported macros:
// TLOC_USE_NED_MALLOC

// Use nedmalloc
#ifndef TLOC_USE_STD_ALLOC
  #define TLOC_USE_NED_MALLOC
#endif

// Use custom new/delete (if using custom MALLOCs above, this will allow
// new/delete to take advantage of them)
#define TLOC_USE_CUSTOM_NEW_DELETE

#ifdef TLOC_DEBUG
# ifndef DEBUG
#   define DEBUG
# endif
#else
# ifndef NDEBUG
#   define NDEBUG
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// For DLL support

#ifndef TLOC_STATIC_LIB
# if defined TLOC_DLL_EXPORT
#   define tlocDLL __declspec(dllexport)
# else
#   define tlocDLL __declspec(dllimport)
# endif
#else
# define tlocDLL
#endif

//////////////////////////////////////////////////////////////////////////
// 2LoC Configurations

#if !defined(TLOC_DEBUG) && !defined(TLOC_DEBUG_DLL) && !defined(TLOC_RELEASE) && !defined(TLOC_RELEASE_DLL) && !defined(TLOC_RELEASE_DEBUGINFO) && !defined(TLOC_RELEASE_DEBUGINFO_DLL)
# error "Project must define TLOC_DEBUG or TLOC_DEBUG_DLL or TLOC_RELEASE or TLOC_RELEASE_DLL or TLOC_RELEASE_DEBUGINFO or TLOC_RELEASE_DEBUGINFO_DLL"

#elif defined(TLOC_DEBUG)
# if defined(TLOC_DEBUG_DLL) || defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DLL) || defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
#   error "Project has mixed configurations!"
# endif

#elif defined(TLOC_DEBUG_DLL)
# if defined(TLOC_DEBUG) || defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DLL) || defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
#   error "Project has mixed configurations!"
#endif

#elif defined(TLOC_RELEASE)
# if defined(TLOC_DEBUG) || defined(TLOC_DEBUG_DLL) || defined(TLOC_RELEASE_DLL) || defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
#   error "Project has mixed configurations!"
# endif

#elif defined(TLOC_RELEASE_DLL)
# if defined(TLOC_DEBUG) || defined(TLOC_DEBUG_DLL) || defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
  # error "Project has mixed configurations!"
#endif

#elif defined(TLOC_RELEASE_DEBUGINFO)
# if defined(TLOC_DEBUG) || defined(TLOC_DEBUG_DLL) || defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DLL) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
#   error "Project has mixed configurations!"
# endif

#elif defined(TLOC_RELEASE_DEBUGINFO_DLL)
# if defined(TLOC_DEBUG) || defined(TLOC_DEBUG_DLL) || defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DLL) || defined(TLOC_RELEASE_DEBUGINFO)
#   error "Project has mixed configurations!"
# endif

#endif

//////////////////////////////////////////////////////////////////////////
// Inlining

#ifndef TLOC_DEBUG
# define TLOC_INLINE inline
# define TL_I TLOC_INLINE

# define TLOC_FORCE_INLINE __forceinline
# define TL_FI TLOC_FORCE_INLINE
#else
# define TLOC_INLINE
# define TL_I

# define TLOC_FORCE_INLINE
# define TL_FI
#endif

#ifdef TLOC_FULL_SOURCE
# define TL_STATIC_I  static  TLOC_INLINE
# define TL_STATIC_FI static TLOC_FORCE_INLINE
#else
# define TL_STATIC_I  static
# define TL_STATIC_FI static
#endif

//////////////////////////////////////////////////////////////////////////
// FwTypes

#include "tlocTypes.h"

//////////////////////////////////////////////////////////////////////////
// Assertions

#if defined(TLOC_DEBUG) || defined(TLOC_RELEASE_DEBUGINFO)

// Supported assert macros
# define TLOC_ASSERT_MESSAGE(msg)\
  (_CRT_WIDE(msg) L" (" _CRT_WIDE(__FUNCTION__) L")")
# define TLOC_ASSERT_MESSAGEW(msg)\
  (msg L" (" _CRT_WIDE(__FUNCTION__) L")")
# define TLOC_ASSERT(_Expression, _Msg) (void)( (!!(_Expression)) || \
  (_wassert(TLOC_ASSERT_MESSAGE(_Msg), _CRT_WIDE(__FILE__), __LINE__), 0) )
# define TLOC_ASSERTW(_Expression, _Msg) (void)( (!!(_Expression)) || \
  (_wassert(TLOC_ASSERT_MESSAGEW(_Msg), _CRT_WIDE(__FILE__), __LINE__), 0) )
#else
#define FwAssert(_Expression, _Msg)
#define FWASSERT(_Expression, _Msg)
#define TLOC_ASSERT(_Expression, _Msg)
#define TLOC_ASSERTW(_Expression, _Msg)
#endif

//------------------------------------------------------------------------
// Low level assertions
// Define TLOC_ENABLE_ASSERT_LOW_LEVEL in your project to catch low level asserts
// e.g. out of bounds access. These asserts are in areas that can be potentially
// performance sensitive (e.g. vector/matrix accessors).

#ifdef TLOC_ENABLE_ASSERT_LOW_LEVEL
# define TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg) TLOC_ASSERT(_Expression, _Msg)
#else
# define TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#endif

//------------------------------------------------------------------------
// Container assertions
// Define TLOC_DISABLE_ASSERT_CONTAINERS in your project to disable assertions
// for containers. These asserts are on by default in all configurations except
// release WITHOUT debug info

#if !defined(TLOC_DISABLE_ASSERT_CONTAINERS) && !defined(TLOC_RELEASE) && !defined(TLOC_RELEASE_DLL)
# define TLOC_ASSERT_CONTAINERS(_Expression, _Msg) TLOC_ASSERT(_Expression, _Msg)
#else
# define TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#endif

//////////////////////////////////////////////////////////////////////////
// Logging

#define LOG_ERRORBOX ""
#define LOG_CHECKBOX ""

//////////////////////////////////////////////////////////////////////////
// Miscellaneous

// Idea taken from WildMagic5
// Avoid warnings about unused variables.  This is designed for variables
// that are exposed in debug configurations but are hidden in release
// configurations.
#define TLOC_UNUSED(variable) (void)variable;

// If a source file is empty (usually because of #ifdef) then the linker will
// generate the LNK4221 warning complaining that no symbols were found and hence
// the archive member (in the library) will be inaccessible. In most cases, we
// are intentionally leaving the source file empty. In those cases, the following
// define can be used (taken from: http://stackoverflow.com/questions/1822887/what-is-the-best-way-to-eliminate-ms-visual-c-linker-warning-warning-lnk4221/1823024#1823024

#define IntentionallyEmptySourceFile() namespace { char NoEmptyFileDummy##__LINE__; }

#endif