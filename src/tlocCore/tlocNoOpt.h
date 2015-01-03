#ifndef TLOC_NO_OPT_H
#define TLOC_NO_OPT_H

// Include this to disabled optimizations for a particular source files in
// release mode. It should be added to *.cpp files for minimal impact on
// overall program optimizations.

#if defined(TLOC_RELEASE_DEBUGINFO) || defined(TLOC_RELEASE_DEBUGINFO_DLL)
# ifdef TLOC_COMPILER_VISUAL_CPP
#   pragma warning(disable:4748)
#   pragma optimize("", off)
#   define _SECURE_SCL 0
#   pragma inline_depth( 0 )
#   pragma inline_recursion( off )
#   pragma auto_inline( off )
# endif
#elif defined(TLOC_RELEASE) || defined(TLOC_RELEASE_DLL)
# ifndef TLOC_FORCE_NO_OPT_H
#   error "tlocNoOpt.h included in a Release build!"
# endif
#endif

#endif