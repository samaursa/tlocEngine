#ifndef TLOC_HASH_MAP_H 
#define TLOC_HASH_MAP_H 

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocAlgorithms.h"
#include "tlocIterator.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_HASH_MAP
# define TLOC_ASSERT_HASH_MAP(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_HASH_MAP(_Expression, _Msg)
#endif

namespace tloc { namespace core {



};};
