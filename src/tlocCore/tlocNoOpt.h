#ifndef TLOC_NO_OPT_H
#define TLOC_NO_OPT_H

// Include this to disabled optimizations for a particular source files in
// release mode. It should be added to *.cpp files for minimal impact on 
// overall program optimizations.

#ifndef TLOC_RELEASE
#ifdef _MSC_VER
#pragma optimize("", off);
#endif
#else
#warning "FwNoOpt.h included in a Release build!"
#endif

#endif