//
//  tlocAllocators.h
//  tlocCore
//
//  Created by Skopworks Inc on 12-06-16.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TLOC_ALLOCATOR_H
#define TLOC_ALLOCATOR_H

#include <tlocCore/tlocBase.h>

#include <memory.h>
#include <new>

// Visual C++ does not implement checked exceptions, which is needed when
// overloading new and delete operators with the GCC compiler. 
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4290)
#endif

//////////////////////////////////////////////////////////////////////////
// C allocation

#ifdef TLOC_USING_NED_MALLOC
#   include <3rdParty/nedmalloc/nedmalloc.h>
#   define TL_MALLOC(tl_size)                 nedalloc::nedmalloc(tl_size)
#   define TL_CALLOC(tl_numElements, tl_size) nedalloc::nedcalloc(tl_numElements, tl_size)
#   define TL_REALLOC(tl_ptr, tl_size)        nedalloc::nedrealloc(tl_ptr, tl_size)
#   define TL_FREE(tl_ptr)                    nedalloc::nedfree(tl_ptr)

#else   // TLOC_USING_NED_MALLOC
#   include <memory.h>
#   define TL_MALLOC(tl_size)                 malloc(tl_size)
#   define TL_CALLOC(tl_numElements, tl_size) calloc(tl_numElements, tl_size)
#   define TL_REALLOC(tl_ptr, tl_size)        realloc(tl_ptr, tl_size)
#   define TL_FREE(tl_ptr)                    free(tl_ptr)
#endif  // TLOC_USING_NED_MALLOC

//////////////////////////////////////////////////////////////////////////
// C++ allocation
//
// All custom new/delete do not throw exceptions, regardless of parameters

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

void* operator new (std::size_t size) throw(std::bad_alloc);
void  operator delete (void* ptr) throw();
void* operator new (std::size_t size, const std::nothrow_t&) throw();
void  operator delete (void* ptr, const std::nothrow_t&) throw();

#endif // TLOC_USE_CUSTOM_NEW_DELETE

#if _MSC_VER
#pragma warning(pop)
#endif

#endif
