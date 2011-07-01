#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include "tlocBase.h"
#include "tlocTypes.h"
#include <memory.h>

#ifndef TLOC_BASE_H
# error "Must include tlocBase.h before including tlocMemory.h"
#endif

#ifdef TLOC_USE_NED_MALLOC
// Check to make sure we are not using CRT memory
#   include <3rdParty/nedmalloc/nedmalloc.h>
#   define TL_ALLOC(tl_size)                  nedmalloc(tl_size)
#   define TL_CALLOC(tl_numElements, tl_size) nedcalloc(tl_numElements, tl_size)
#   define TL_REALLOC(tl_ptr, tl_size)        nedrealloc(tl_ptr, tl_size)
#   define TL_FREE(tl_ptr)                    nedfree(tl_ptr)

#else   // TLOC_USE_NED_MALLOC
#   include <memory.h>
#   define TL_ALLOC(tl_size)                  malloc(tl_size)
#   define TL_CALLOC(tl_numElements, tl_size) calloc(tl_numElements, tl_size)
#   define TL_REALLOC(tl_ptr, tl_size)        realloc(tl_ptr, tl_size)
#   define TL_FREE(tl_ptr)                    free(tl_ptr)
#endif  // TLOC_USE_NED_MALLOC

#endif  // TLOC_MEMORY_H