//////////////////////////////////////////////////////////////////////////
// Link this file when using custom memory allocators

#ifdef TLOC_USING_NED_MALLOC

// nedmalloc defines this without checking
#ifdef _CRT_SECURE_NO_WARNINGS
  #undef _CRT_SECURE_NO_WARNINGS
#endif
# include <tlocCore/memory/tlocAllocators.h>
# include <3rdParty/nedmalloc/nedmalloc.c>
#endif