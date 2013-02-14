#ifndef _TLOC_PREFAB_INCLUDE_ALL_INL_
#define _TLOC_PREFAB_INCLUDE_ALL_INL_

#ifndef _TLOC_PREFAB_INCLUDE_ALL_H_
#error "Must include header before including the inline file"
#endif

#include <tlocPrefab/core/tloc_core.inl>
#include <tlocPrefab/graphics/tloc_graphics.inl>
#include <tlocPrefab/input/tloc_input.inl>
#include <tlocPrefab/math/tloc_math.inl>

#if !defined (TLOC_OS_IPHONE) //TODO: Temp - Remove when Iphone port has tlocPhysics
# include <tlocPrefab/physics/tloc_physics.inl>
#endif

#endif