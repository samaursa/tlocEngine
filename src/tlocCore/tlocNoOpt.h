#ifndef TLOC_NO_OPT_H
#define TLOC_NO_OPT_H

// Include this to disabled optimizations for a particular source files in
// release mode. It should be added to *.cpp files for minimal impact on
// overall program optimizations.

#if !defined(TLOC_RELEASE) && !defined(TLOC_RELEASE_DLL)
# ifdef _MSC_VER
#   pragma optimize("", off)
#   define _SECURE_SCL 0
#   pragma inline_depth( 0 )
#   pragma inline_recursion( off )
#   pragma auto_inline( off )
# endif
#endif
#else
# warning "FwNoOpt.h included in a Release build!"
#endif

#endif