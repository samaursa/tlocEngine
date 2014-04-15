#ifndef _TLOC_CORE_ASSERT_H_
#define _TLOC_CORE_ASSERT_H_

#include <tlocCore/tlocBase.h>
#include <3rdParty/loki/TypeTraits.h>
#include <stdio.h>

// ///////////////////////////////////////////////////////////////////////
// Runtime assert
//
// NOTES: We no longer use assert() because we want asserts to be enabled
//        in RelWithDebInfo builds which compilers prevent when compiling
//        release libraries with debug information
//
// NOTES: using while((void)0, 0) is necessary to placate visual studio
//        see: http://stackoverflow.com/a/1947233/368599

namespace tloc { namespace core { namespace assert {

  namespace exception {
    struct Assert { };
  };

  void  SetAssertThrow();
  void  SetAssertNoThrow();

  bool  NoThrowBreak();
  bool  AlwaysReturnFalse();

};};};

#define TLOC_ASSERT_DOES_NOT_THROW() \
  tloc::core::assert::SetAssertNoThrow()

#define TLOC_ASSERT_THROWS() \
  tloc::core::assert::SetAssertThrow()

#if defined(_MSC_VER)
  #include <intrin.h>
  #define TLOC_DEBUG_BREAK()  \
  do { \
    if(tloc::core::assert::NoThrowBreak())\
    { __debugbreak(); } \
    else\
    { throw tloc::core::assert::exception::Assert{}; } \
  } while((void)0, 0)
#else
  #include <stdlib.h>
  #define TLOC_DEBUG_BREAK()  \
  do { \
    if(tloc::core::assert::NoThrowBreak())\
    { abort(); } \
    else\
    { throw tloc::core::assert::exception::Assert{}; } \
  } while((void)0, 0)
#endif

#if defined(TLOC_DEBUG) || defined(TLOC_DEBUG_DLL) || defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBINFO_DLL)
  #define TLOC_ASSERTS_DEFINED 1 

  #define TLOC_ASSERT(_Expression, _Msg) \
  do {\
    if (!(_Expression))\
    {\
      printf("\n[E] Assertion (%s) FAILED: %s | %s(%i)", (#_Expression), _Msg, __FILE__, __LINE__);\
      TLOC_DEBUG_BREAK();\
    }\
  } while((void)0, 0)

  #define TLOC_ASSERT_WARN(_Expression, _Msg) \
    TLOC_ASSERT(_Expression, _Msg)

#else
  #define TLOC_ASSERTS_DEFINED 0 

  #define TLOC_ASSERT(_Expression, _Msg) 
  #define TLOC_ASSERT_WARN(_Expression, _Msg) 

#endif

# define TLOC_ASSERT_FALSE(_Msg) \
  TLOC_ASSERT(tloc::core::assert::AlwaysReturnFalse(), _Msg)

# define TLOC_ASSERT_WIP() \
  TLOC_ASSERT_FALSE("This function is unfinished (Work in progress)!")

# define TLOC_ASSERT_LOW_LEVEL_FALSE(_Msg) \
  TLOC_ASSERT_LOW_LEVEL(tloc::core::assert::AlwaysReturnFalse(), _Msg)

//------------------------------------------------------------------------
// Low level assertions
// Define TLOC_ENABLE_ASSERT_LOW_LEVEL in your project to catch low level asserts
// e.g. out of bounds access. These asserts are in areas that can be potentially
// performance sensitive (e.g. vector/matrix accessors).

#ifndef TLOC_DISABLE_ASSERT_LOW_LEVEL
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

#endif

// Other common asserts
#define TLOC_ASSERT_NOT_NULL(_Pointer_) TLOC_ASSERT(_Pointer_ != nullptr, #_Pointer_ " cannot be NULL")
#define TLOC_ASSERT_NULL(_Pointer_) TLOC_ASSERT(_Pointer_ == nullptr, #_Pointer_ " should be NULL")