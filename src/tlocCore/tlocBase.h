#pragma once

#ifndef TLOC_BASE_H
#define TLOC_BASE_H

//////////////////////////////////////////////////////////////////////////
// Macros that have to be included before any other file

#ifdef TLOC_COMPILER_VISUAL_CPP
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#  endif
#endif

//////////////////////////////////////////////////////////////////////////
// Header files that will be included in almost every file in the engine.
// Avoid including extra headers here

#include <tlocCore/types/tlocNullptr.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/platform/tlocPlatformDefines.h>

//////////////////////////////////////////////////////////////////////////
// Make sure we are not using standard containers

#ifndef TLOC_USING_STL
# if defined(_VECTOR_) || defined(_MAP_) || defined(_LIST_) || defined(_BITSET_) || defined (_DEQUE_) || defined(_QUEUE_) || defined(_SET_) || defined(_STACK_) || defined (_ALGORITHM_) || defined (_STRING_)
#   error "STL use is prohibited. To enable usage of STL, compile with TLOC_USING_STL"
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// Common macros

#if defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DLL) || defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
# if defined (TLOC_COMPI)
#   ifdef _SECURE_SCL
#     undef _SECURE_SCL
#   endif
#   define _SECURE_SCL 0  // turn of checked iterators
#   pragma inline_depth( 255 ) // unlimited inline depth - change if causing problems
#   pragma inline_recursion( on )
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// NULL
// We disallow the use of NULL but some APIs require 0 as an input argument
// which can be easily overlooked. Passing NULL in those cases is preferred.
// We provide TLOC_NULL which should be used instead of NULL. This is to show
// that the use of NULL was deliberate and that nullptr could not be used.

#define TLOC_NULL NULL

//////////////////////////////////////////////////////////////////////////
// Platform specific

#if defined(TLOC_OS_WIN)
# define TLOC_MAIN main
#elif defined(TLOC_OS_IPHONE)
  // This is a function declaration for TLOC_MAIN (note that TLOC_MAIN is
  // no longer a macro name on iOS). If you get an unresolved linking error wrt
  // TLOC_MAIN make sure to define: int TLOC_MAIN(int argc, char** argv){}
  // and of course, put your 'main' code in that function
  int TLOC_MAIN(int argc, char** argv);
#endif

#if defined(TLOC_OS_WIN)
# ifndef WIN32
#   define WIN32
# endif
# ifndef _WIN32
#   define _WIN32
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// Compiler specific

//------------------------------------------------------------------------
// Microsoft Visual C++ compiler
#if defined(TLOC_COMPILER_VISUAL_CPP)
  //------------------------------------------------------------------------
  // Check for exception handling
# if defined(_CPPUNWIND)
#   define TLOC_CPPUNWIND_ENABLED
#   define TLOC_THROW() throw
# else
#   define TLOC_THROW()
# endif
  //------------------------------------------------------------------------
  // Check for RTTI
# if defined(_CPPRTTI)
#   define TLOC_RTTI_ENABLED
# endif
  //------------------------------------------------------------------------
  // Optimizations
# ifndef TLOC_DEBUG
#   pragma inline_recursion( on )
#   pragma auto_inline( on )
# endif

//------------------------------------------------------------------------
// GCC compiler
#elif defined (__GNUC__) || defined(__clang__)
  //------------------------------------------------------------------------
  // Check for exception handling
# if defined (__EXCEPTIONS)
#   define TLOC_CPPUNWIND_ENABLED
# endif
  //------------------------------------------------------------------------
  // Check for RTTI
# if defined (__GXX_RTTI)
#   define TLOC_RTTI_ENABLED
# endif

#else
  // unsupported compiler
# error WIP
#endif


  //------------------------------------------------------------------------
  // Typedef fix for compilers
  // This fix is temporary until we can figure out a way to remove typename
  // limitations from VS (i.e. adding typedef to VS fails to compile, while
  // removing typedef fails to compile on LLVM)
#if defined(TLOC_COMPILER_VISUAL_CPP)
# define TLOC_COMPILER_TYPEDEF(_type_, _alias_)\
  typedef _type_ _alias_
#else // For GCC and Clang
# define TLOC_COMPILER_TYPEDEF(_type_, _alias_)\
  typedef typename _type_ _alias_
#endif

//////////////////////////////////////////////////////////////////////////
// Exceptions

#ifndef TLOC_DISABLE_ALL_COMPILER_CHECKS
# if defined (TLOC_CPPUNWIND_ENABLED) && !defined (TLOC_ENABLE_CPPUNWIND)
#   error "Exception handling must be disabled for this project."
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// RTTI

#ifndef TLOC_DISABLE_ALL_COMPILER_CHECKS
# if defined (TLOC_RTTI_ENABLED) && !defined (TLOC_ENABLE_CPPRTTI)
#   error "RTTI must be disabled for this project."
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// Memory

// Use custom new/delete (if using custom MALLOCs above, this will allow
// new/delete to take advantage of them)
#ifndef TLOC_DISABLE_CUSTOM_NEW_DELETE
# define TLOC_USE_CUSTOM_NEW_DELETE
#endif

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

#define TLOC_INLINE inline
#define TL_I TLOC_INLINE

//------------------------------------------------------------------------
// Define force inline for the VC++ compiler
#if defined (TLOC_COMPILER_VISUAL_CPP)
# pragma warning(disable : 4714)
// NOTE: __forceinline increases build times substantially
# define TLOC_FORCE_INLINE inline /*__forceinline*/
//------------------------------------------------------------------------
// Define force inline for the GCC and clang compilers. Since the
// attribute always_inline, inlines regardless of optimization level
// always_inline is removed in debug builds, and replaced with inline.
#elif defined (__GNUC__) || defined(__clang__)
# if defined (TLOC_DEBUG)
#   define TLOC_FORCE_INLINE inline
# else
#   define TLOC_FORCE_INLINE inline __attribute__ ((always_inline))
# endif
//------------------------------------------------------------------------
// Define force inline as a normal inline for an unsupported compiler
#else
#  define TLOC_FORCE_INLINE inline
#endif
#define TL_FI TLOC_FORCE_INLINE

#ifdef TLOC_FULL_SOURCE
# define TL_STATIC_I  static TLOC_INLINE
# define TL_STATIC_FI static TLOC_FORCE_INLINE
#else
# define TL_STATIC_I  static
# define TL_STATIC_FI static
#endif

//////////////////////////////////////////////////////////////////////////
// Miscellaneous

// Sometimes we have to pass templates in macros where commas don't work.
// There we'll have to use this macro
#define TLOC_COMMA ,

// Idea taken from WildMagic5
// Avoid warnings about unused variables.  This is designed for variables
// that are exposed in debug configurations but are hidden in release
// configurations.
#define TLOC_UNUSED(variable) (void)variable
#define TLOC_UNUSED_2(variable1, variable2) TLOC_UNUSED(variable1); TLOC_UNUSED(variable2)
#define TLOC_UNUSED_3(variable1, variable2, variable3) TLOC_UNUSED_2(variable1, variable2); TLOC_UNUSED(variable3)
#define TLOC_UNUSED_4(variable1, variable2, variable3, variable4) TLOC_UNUSED_3(variable1, variable2, variable3); TLOC_UNUSED(variable4)
#define TLOC_UNUSED_5(variable1, variable2, variable3, variable4, variable5) TLOC_UNUSED_4(variable1, variable2, variable3, variable4); TLOC_UNUSED(variable5)
#define TLOC_UNUSED_6(variable1, variable2, variable3, variable4, variable5, variable6) TLOC_UNUSED_5(variable1, variable2, variable3, variable4, variable5); TLOC_UNUSED(variable6)
#define TLOC_UNUSED_7(variable1, variable2, variable3, variable4, variable5, variable6, variable7) TLOC_UNUSED_6(variable1, variable2, variable3, variable4, variable5, variable6); TLOC_UNUSED(variable7)

#define TLOC_UNUSED_RELEASE(variable) (void)variable

// If a source file is empty (usually because of #ifdef) then the linker will
// generate the LNK4221 warning complaining that no symbols were found and hence
// the archive member (in the library) will be inaccessible. In most cases, we
// are intentionally leaving the source file empty. In those cases, the following
// define can be used (taken from: http://stackoverflow.com/questions/1822887/what-is-the-best-way-to-eliminate-ms-visual-c-linker-warning-warning-lnk4221/1823024#1823024

#ifdef TLOC_COMPILER_VISUAL_CPP 
# define TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE() \
    namespace { char NoEmptyFileDummy##__LINE__; }
# define TLOC_NOT_EMPTY_SOURCE_FILE() \
    namespace { char NoEmptyFileDummy##__LINE__; }
#else
# define TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE()
# define TLOC_NOT_EMPTY_SOURCE_FILE()
#endif

// -----------------------------------------------------------------------
// This macro returns the file instead of the full path from the macro
// __FILE__

#define TLOC_DEFINE_THIS_FILE_NAME() \
  namespace {\
  const char*\
    LocalStrRChr(const char* a_string, char a_charToLocate)\
  {\
    const char* currChar = a_string;\
    const char* charToRet = nullptr;\
\
    while(*currChar != 0)\
    {\
      if (*currChar == a_charToLocate)\
      { charToRet = currChar; }\
\
      ++currChar;\
    }\
\
    if (*currChar == a_charToLocate)\
    { charToRet = currChar; }\
\
    return charToRet;\
  }\
\
  static const char* const TLOC_THIS_FILE_NAME = \
  LocalStrRChr(__FILE__, '/') ? LocalStrRChr(__FILE__, '/') + 1 : \
  (LocalStrRChr(__FILE__, '\\') ? LocalStrRChr(__FILE__, '\\') + 1 : __FILE__);\
  }

///-------------------------------------------------------------------------
/// @brief This struct is used to diagnose template types.
///-------------------------------------------------------------------------
template <typename T>
struct TemplateDiagnose;

template <typename T>
struct DiagnoseTemplate;


// -----------------------------------------------------------------------
// Punctuation - useful in macros using templates

#ifndef COMMA
# define COMMA() ,
#endif

// -----------------------------------------------------------------------
// extern templates

// Visual Studio 2010 supports extern template but requires the explicit
// instantiation to NOT follow it, which makes it next to useless for us. So
// we turn it off.
#if !defined(TLOC_CXX03) && !defined(TLOC_NO_EXTERN_TEMPLATE) && TLOC_COMPILER_VISUAL_CPP >= 1700
# define TLOC_EXTERN_TEMPLATE_CLASS(_class_with_type_)\
    extern template class _class_with_type_

# define TLOC_EXTERN_TEMPLATE_STRUCT(_struct_with_type_)\
    extern template struct _struct_with_type_
#else
# define TLOC_EXTERN_TEMPLATE_CLASS(_class_with_type_)
# define TLOC_EXTERN_TEMPLATE_STRUCT(_class_with_type_)
#endif

#endif // header guard