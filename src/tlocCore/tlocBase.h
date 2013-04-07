#pragma once

#ifndef TLOC_BASE_H
#define TLOC_BASE_H

//////////////////////////////////////////////////////////////////////////
// Macros that have to be included before any other file

#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#  endif
#endif

//////////////////////////////////////////////////////////////////////////
// Header files that will be included in almost every file in the engine.
// Avoid including extra headers here

#include <assert.h>
#include <tlocCore/types/tlocNullptr.h>
#include <tlocCore/tlocStaticAssert.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/platform/tlocPlatformDefines.h>

#include <3rdParty/loki/TypeTraits.h>

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
# ifdef _SECURE_SCL
# undef _SECURE_SCL
# endif

# define _SECURE_SCL 0  // turn of checked iterators
# pragma inline_depth( 255 ) // unlimited inline depth - change if causing problems
# pragma inline_recursion( on )

#endif

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

#if defined(TLOC_OS_WIN)
# define TLOC_MAIN main
#elif defined(TLOC_OS_IPHONE)
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
#if defined(_MSC_VER)
  //------------------------------------------------------------------------
  // Check for exception handling
# if defined(_CPPUNWIND)
#   define TLOC_CPPUNWIND_ENABLED
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
# error WIP
#endif


  //------------------------------------------------------------------------
  // Typedef fix for compilers
  // This fix is temporary until we can figure out a way to remove typename
  // limitations from VS
#if defined(_MSC_VER)
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
// TLOC_USING_NED_MALLOC

// Use nedmalloc
#ifndef TLOC_USING_STD_ALLOC
  #define TLOC_USING_NED_MALLOC
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

#define TLOC_INLINE inline
#define TL_I TLOC_INLINE

//------------------------------------------------------------------------
// Define force inline for the VC++ compiler
#if defined (_MSC_VER)
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
// Assertions

#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)

//````````````````````````````````````````````````````````````````````````
// Run-time

#if defined(TLOC_DEBUG) || defined(TLOC_RELEASE_DEBUGINFO)

// Sometimes VS gives the warning C4127: conditional expression is constant. To
// circumvent that, TLOC_ASSERT for VS is slightly different.
#if defined(_MSC_VER)
  #define TLOC_ASSERT(_Expression, _Msg) \
  assert( (_Msg, _Expression) )
#else
  #define TLOC_ASSERT(_Expression, _Msg) \
  assert(_Expression && _Msg)
#endif

// Use this macro when warning the user of a potential problem that the user may
// have overlooked. These can be safely disabled, i.e. the function guarantees
// it will work properly with these asserts disabled
#   ifndef TLOC_DISABLE_ASSERT_WARNINGS
#     define TLOC_ASSERT_WARN(_Expression, _Msg) TLOC_ASSERT(_Expression, "[WARN] " #_Msg)
#   else
#     define TLOC_ASSERT_WARN(_Expression, _Msg) TLOC_UNUSED(_Expression); TLOC_UNUSED(_Msg)
#   endif

#else
#define TLOC_ASSERT(_Expression, _Msg)
#define TLOC_ASSERT_WARN(_Expression, _Msg)
#endif

// Other common asserts
#define TLOC_ASSERT_NOT_NULL(_Pointer_) TLOC_ASSERT(_Pointer_ != nullptr, #_Pointer_ " cannot be NULL")
#define TLOC_ASSERT_NULL(_Pointer_) TLOC_ASSERT(_Pointer_ == nullptr, #_Pointer_ " should be NULL")

//````````````````````````````````````````````````````````````````````````
// Compile time

// TODO: solve static assert problems on LLVM
#ifndef TLOC_DISABLE_STATIC_ASSERT
# define TLOC_STATIC_ASSERT(_Expression, _Msg) STATIC_ASSERT(_Expression, _Msg##_xxxxxxxxxxxxx_)
#else
# define TLOC_STATIC_ASSERT(_Expression, _Msg)
#endif

# define TLOC_STATIC_ASSERT_FALSE(_type_, _Msg) \
  TLOC_STATIC_ASSERT((Loki::IsSameType<_type_, UniqueDummyStruct>::value), _Msg)

# define TLOC_STATIC_ASSERT_WIP() \
  TLOC_STATIC_ASSERT(false, This_Function_Is_Unfinished)
# define TLOC_ASSERT_WIP() \
  TLOC_ASSERT(false, "This function is unfinished (Work in progress)!")

# define TLOC_STATIC_ASSERT_IS_POINTER(_Type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_Type_>::isPointer, Type_must_be_a_POINTER);
# define TLOC_STATIC_ASSERT_IS_NOT_POINTER(_Type_) \
  TLOC_STATIC_ASSERT( (!Loki::TypeTraits<_Type_>::isPointer), Type_CANNOT_be_a_pointer);
# define TLOC_STATIC_ASSERT_IS_REFERENCE(_Type_) \
  TLOC_STATIC_ASSERT( (Loki::TypeTraits<_Type_>::isReference), Type_must_be_a_REFERENCE);
# define TLOC_STATIC_ASSERT_IS_NOT_REFERENCE(_Type_) \
  TLOC_STATIC_ASSERT( (!Loki::TypeTraits<_Type_>::isReference), Type_CANNOT_be_a_reference);

# define TLOC_STATIC_ASSERT_IS_FLOAT(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isFloat, Type_must_be_a_FLOAT);
# define TLOC_STATIC_ASSERT_IS_ARITH(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isArith, Type_must_be_an_ARITHMETIC);
# define TLOC_STATIC_ASSERT_IS_INTEGRAL(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isIntegral, Type_must_be_an_INTEGRAL);
# define TLOC_STATIC_ASSERT_IS_INTEGRAL(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isIntegral, Type_must_be_an_INTEGRAL);

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

//////////////////////////////////////////////////////////////////////////
// Logging

#define TLOC_LOG_ERRORBOX ""
#define TLOC_LOG_CHECKBOX ""

//////////////////////////////////////////////////////////////////////////
// Miscellaneous

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
#define TLOC_UNUSED_7(variable1, variable2, variable3, variable4, variable5, variable6, variable7) TLOC_UNUSED_5(variable1, variable2, variable3, variable4, variable5, variable6); TLOC_UNUSED(variable7)

// If a source file is empty (usually because of #ifdef) then the linker will
// generate the LNK4221 warning complaining that no symbols were found and hence
// the archive member (in the library) will be inaccessible. In most cases, we
// are intentionally leaving the source file empty. In those cases, the following
// define can be used (taken from: http://stackoverflow.com/questions/1822887/what-is-the-best-way-to-eliminate-ms-visual-c-linker-warning-warning-lnk4221/1823024#1823024

#ifdef _MSC_VER
# define TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE() \
    namespace { char NoEmptyFileDummy##__LINE__; }
# define TLOC_NOT_EMPTY_SOURCE_FILE() \
    namespace { char NoEmptyFileDummy##__LINE__; }
#else
# define TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE()
# define TLOC_NOT_EMPTY_SOURCE_FILE()
#endif

///-------------------------------------------------------------------------
/// @brief This struct is used to diagnose template types.
///-------------------------------------------------------------------------
template <typename T>
struct TemplateDiagnose;

template <typename T>
struct DiagnoseTemplate;


// Punctuation - useful in macros using templates
#ifndef COMMA
# define COMMA() ,
#endif


#endif
